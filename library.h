#ifndef LIBRARY_H
#define LIBRARY_H

#include <mpfr.h>
#include <mpfi.h>
#include <dlfcn.h>
#include "expression.h"
#include "chain.h"

typedef struct libraryHandleStruct libraryHandle;
struct libraryHandleStruct 
{
  char *libraryName;
  void *libraryDescriptor;
  chain *functionList;
};

typedef struct libraryFunctionStruct libraryFunction;
struct libraryFunctionStruct 
{
  char *functionName;
  int (*code)(mpfi_t, mpfi_t, int);
};


libraryFunction *bindFunction(char* libraryName, char *functionName);
libraryFunction *getFunction(char *functionName);
void freeLibraries();

#endif /* ifdef LIBRARY_H*/
