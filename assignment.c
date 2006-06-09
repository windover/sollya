#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"
#include "assignment.h"
#include "expression.h"
#include "main.h"


chain *addEntry(chain *symTbl, char *name, node *value) {
  entry *newEntry;

  if (containsEntry(symTbl,name)) return symTbl;

  newEntry = (entry *) safeMalloc(sizeof(entry));
  newEntry->name = (char *) safeCalloc(strlen(name)+1,sizeof(char));
  strcpy(newEntry->name,name);
  newEntry->value = copyTree(value);

  symTbl = addElement(symTbl,newEntry);   
  return symTbl;
}

int containsEntry(chain *symTbl, char *name) {
  chain *curr;

  curr = symTbl;
  while (curr != NULL) {
    if (strcmp(((entry *) (curr->value))->name,name) == 0) return 1;
    curr = curr->next;
  }

  return 0;
}

node *getEntry(chain *symTbl, char *name) {
  chain *curr;
  node *result;

  result = NULL;
  curr = symTbl;
  while (curr != NULL) {
    if (strcmp(((entry *) (curr->value))->name,name) == 0) {
      result = copyTree(((entry *) curr->value)->value);
      break;
    }
    curr = curr->next;
  }

  return result;
}



void freeEntry(void *e) {
  free_memory(((entry *) e)->value);
  free(((entry *) e)->name);
  free(e);
}

void freeSymbolTable(chain *symTbl) {
  if (symTbl != NULL) freeChain(symTbl,freeEntry);
}
