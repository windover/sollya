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

typedef struct procLibraryHandleStruct procLibraryHandle;
struct procLibraryHandleStruct 
{
  char *procLibraryName;
  void *procLibraryDescriptor;
  chain *procedureList;
};

typedef struct libraryProcedureStruct libraryProcedure;
struct libraryProcedureStruct 
{
  char *procedureName;
  void *code;
  chain *signature;
};


#define VOID_TYPE 0
#define CONSTANT_TYPE 1
#define FUNCTION_TYPE 2
#define RANGE_TYPE 3
#define INTEGER_TYPE 4
#define STRING_TYPE 5
#define BOOLEAN_TYPE 6
#define CONSTANT_LIST_TYPE 7
#define FUNCTION_LIST_TYPE 8
#define RANGE_LIST_TYPE 9
#define INTEGER_LIST_TYPE 10
#define STRING_LIST_TYPE 11
#define BOOLEAN_LIST_TYPE 12


libraryFunction *bindFunction(char* libraryName, char *functionName);
libraryFunction *getFunction(char *functionName);
void freeLibraries();

libraryProcedure *bindProcedure(char* libraryName, char *procedureName, chain *signature);
libraryProcedure *getProcedure(char *procedureName);
void freeProcLibraries();

#endif /* ifdef LIBRARY_H*/
