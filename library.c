#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"
#include "general.h"
#include "library.h"
#include "chain.h"

chain *openedLibraries = NULL;


libraryHandle *getLibraryHandle(char *libraryName) {
  chain *curr;
  libraryHandle *currHandle;
  void *dlfcnHandle;

  curr = openedLibraries;
  while (curr != NULL) {
    currHandle = (libraryHandle *) curr->value;
    if (strcmp(currHandle->libraryName,libraryName) == 0) 
      return currHandle;
    curr = curr->next;
  }

  dlerror(); 
  dlfcnHandle = dlopen(libraryName, RTLD_LOCAL | RTLD_NOW);
  if (dlfcnHandle == NULL) 
    return NULL;

  currHandle = (libraryHandle *) safeMalloc(sizeof(libraryHandle));
  currHandle->libraryName = (char *) safeCalloc(strlen(libraryName)+1,sizeof(char));
  strcpy(currHandle->libraryName,libraryName);
  currHandle->libraryDescriptor = dlfcnHandle;
  currHandle->functionList = NULL;
  openedLibraries = addElement(openedLibraries,currHandle);

  return currHandle;
}


libraryFunction *bindFunction(char* libraryName, char *functionName) {
  libraryHandle *libHandle;
  libraryFunction *currFunct;
  int (*myFunction)(mpfi_t, mpfi_t, int);
  char *error;
  mpfi_t op, rop;

  currFunct = getFunction(functionName);
  if (currFunct != NULL) {
    printMessage(1,"Warning: a function named \"%s\" has already been bound.\n",functionName);
    return currFunct;
  }

  libHandle = getLibraryHandle(libraryName);
  if (libHandle == NULL) {
    fprintf(stderr,"Error: could not open library \"%s\" for binding \"%s\": %s\n",libraryName,functionName,dlerror());
    return NULL;
  }
    
  dlerror();
  myFunction = (int (*)(mpfi_t, mpfi_t, int)) dlsym(libHandle->libraryDescriptor, functionName);
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "Error: could not find function \"%s\" in library \"%s\" for binding: %s\n",functionName,libraryName,error);
    return NULL;
  }
  
  mpfi_init2(rop,12);
  mpfi_init2(op,12);
  mpfi_set_d(op,1.0);

  myFunction(rop,op,0);

  mpfi_clear(rop);
  mpfi_clear(op);

  currFunct = (libraryFunction *) safeMalloc(sizeof(libraryFunction));
  currFunct->functionName = (char *) safeCalloc(strlen(functionName),sizeof(char));
  strcpy(currFunct->functionName,functionName);
  currFunct->code = myFunction;
  
  libHandle->functionList = addElement(libHandle->functionList,currFunct);

  return currFunct;
} 


libraryFunction *getFunction(char *functionName) {
  chain *currLibList, *currFunList;
  libraryFunction *currFunct;
  libraryHandle *currLibHandle;

  currLibList = openedLibraries;
  while (currLibList != NULL) {
    currLibHandle = (libraryHandle *) currLibList->value;
    currFunList = currLibHandle->functionList;
    while (currFunList != NULL) {
      currFunct = (libraryFunction *) currFunList->value;
      if (strcmp(currFunct->functionName,functionName) == 0)
	return currFunct;
      currFunList = currFunList->next;
    }
    currLibList = currLibList->next;
  }

  return NULL;
}


void freeLibraries() {
  chain *currLibList, *currFunList, *prevFunList, *prevLibList;
  libraryFunction *currFunct;
  libraryHandle *currLibHandle;

  currLibList = openedLibraries;
  while (currLibList != NULL) {
    currLibHandle = (libraryHandle *) currLibList->value;
    currFunList = currLibHandle->functionList;
    while (currFunList != NULL) {
      currFunct = (libraryFunction *) currFunList->value;
      free(currFunct->functionName);
      free(currFunList->value);
      prevFunList = currFunList;
      currFunList = currFunList->next;
      free(prevFunList);
    }
    dlerror();
    if (dlclose(currLibHandle->libraryDescriptor) != 0) 
      printMessage(1,"Warning: could not close libary \"%s\": %s\n",currLibHandle->libraryName,dlerror());
    free(currLibHandle->libraryName);
    prevLibList = currLibList;
    currLibList = currLibList->next;
    free(prevLibList);
  }
  openedLibraries = NULL;
}
