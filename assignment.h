#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "expression.h"
#include "chain.h"


typedef struct entryStruct entry;

struct entryStruct 
{
  char *name;
  node *value;
};



chain* addEntry(chain *symTbl, char *name, node *value);
int containsEntry(chain *symTbl, char *name);
node *getEntry(chain *symTbl, char *name); 
void freeSymbolTable(chain *symTbl);






#endif /* ifdef ASSIGNMENT_H*/
