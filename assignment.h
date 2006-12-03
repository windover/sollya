#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "expression.h"
#include "chain.h"


typedef struct entryStruct entry;

struct entryStruct 
{
  char *name;
  void *value;
};


chain *addEntry(chain *symTbl, char *name, void *value, void * (*copyValue) (void *));
int containsEntry(chain *symTbl, char *name);
void *getEntry(chain *symTbl, char *name, void * (*copyValue) (void *));
chain *removeEntry(chain *symTbl, char *name, void (*f) (void *));
void freeSymbolTable(chain *symTbl, void (*f) (void *));
void *copyString(void *oldString);
void freeStringPtr(void *aString);



#endif /* ifdef ASSIGNMENT_H*/
