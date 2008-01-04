/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.fr
sylvain.chevillard@ens-lyon.fr
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinite norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*/

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
#include "execute.h"

chain *openedLibraries = NULL;
chain *openedProcLibraries = NULL;

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




procLibraryHandle *getProcLibraryHandle(char *libraryName) {
  chain *curr;
  procLibraryHandle *currHandle;
  void *dlfcnHandle;

  curr = openedProcLibraries;
  while (curr != NULL) {
    currHandle = (procLibraryHandle *) curr->value;
    if (strcmp(currHandle->procLibraryName,libraryName) == 0) 
      return currHandle;
    curr = curr->next;
  }

  dlerror(); 
  dlfcnHandle = dlopen(libraryName, RTLD_LOCAL | RTLD_NOW);
  if (dlfcnHandle == NULL) 
    return NULL;

  currHandle = (procLibraryHandle *) safeMalloc(sizeof(procLibraryHandle));
  currHandle->procLibraryName = (char *) safeCalloc(strlen(libraryName)+1,sizeof(char));
  strcpy(currHandle->procLibraryName,libraryName);
  currHandle->procLibraryDescriptor = dlfcnHandle;
  currHandle->procedureList = NULL;
  openedProcLibraries = addElement(openedProcLibraries,currHandle);

  return currHandle;
}



libraryProcedure *bindProcedure(char* libraryName, char *procedureName, chain *signature) {
  procLibraryHandle *libHandle;
  libraryProcedure *currProc;
  char *error;
  void *myFunction;

  currProc = getProcedure(procedureName);
  if (currProc != NULL) {
    printMessage(1,"Warning: a procedure named \"%s\" has already been bound.\n",procedureName);
    return currProc;
  }

  libHandle = getProcLibraryHandle(libraryName);
  if (libHandle == NULL) {
    fprintf(stderr,"Error: could not open library \"%s\" for binding \"%s\": %s\n",libraryName,procedureName,dlerror());
    return NULL;
  }
    
  dlerror();
  myFunction = dlsym(libHandle->procLibraryDescriptor, procedureName);
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "Error: could not find procedure \"%s\" in library \"%s\" for binding: %s\n",procedureName,libraryName,error);
    return NULL;
  }
  
  currProc = (libraryProcedure *) safeMalloc(sizeof(libraryProcedure));
  currProc->procedureName = (char *) safeCalloc(strlen(procedureName),sizeof(char));
  strcpy(currProc->procedureName,procedureName);
  currProc->code = myFunction;
  currProc->signature = copyChainWithoutReversal(signature, copyIntPtrOnVoid);
  
  
  libHandle->procedureList = addElement(libHandle->procedureList,currProc);

  return currProc;
} 


libraryProcedure *getProcedure(char *procedureName) {
  chain *currLibList, *currProcList;
  libraryProcedure *currProc;
  procLibraryHandle *currLibHandle;

  currLibList = openedProcLibraries;
  while (currLibList != NULL) {
    currLibHandle = (procLibraryHandle *) currLibList->value;
    currProcList = currLibHandle->procedureList;
    while (currProcList != NULL) {
      currProc = (libraryProcedure *) currProcList->value;
      if (strcmp(currProc->procedureName,procedureName) == 0)
	return currProc;
      currProcList = currProcList->next;
    }
    currLibList = currLibList->next;
  }

  return NULL;
}


void freeProcLibraries() {
  chain *currLibList, *currProcList, *prevProcList, *prevLibList;
  libraryProcedure *currProc;
  procLibraryHandle *currLibHandle;

  currLibList = openedProcLibraries;
  while (currLibList != NULL) {
    currLibHandle = (procLibraryHandle *) currLibList->value;
    currProcList = currLibHandle->procedureList;
    while (currProcList != NULL) {
      currProc = (libraryProcedure *) currProcList->value;
      free(currProc->procedureName);
      freeChain(currProc->signature,freeIntPtr);
      free(currProcList->value);
      prevProcList = currProcList;
      currProcList = currProcList->next;
      free(prevProcList);
    }
    dlerror();
    if (dlclose(currLibHandle->procLibraryDescriptor) != 0) 
      printMessage(1,"Warning: could not close libary \"%s\": %s\n",currLibHandle->procLibraryName,dlerror());
    free(currLibHandle->procLibraryName);
    prevLibList = currLibList;
    currLibList = currLibList->next;
    free(prevLibList);
  }
  openedProcLibraries = NULL;
}
