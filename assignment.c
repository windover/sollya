#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"
#include "assignment.h"
#include "expression.h"
#include "main.h"


chain *addEntry(chain *symTbl, char *name, void *value, void * (*copyValue) (void *)) {
  entry *newEntry;

  if (containsEntry(symTbl,name)) return symTbl;

  newEntry = (entry *) safeMalloc(sizeof(entry));
  newEntry->name = (char *) safeCalloc(strlen(name)+1,sizeof(char));
  strcpy(newEntry->name,name);
  newEntry->value = copyValue(value);

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

void *getEntry(chain *symTbl, char *name, void * (*copyValue) (void *)) {
  chain *curr;
  void *result;

  result = NULL;
  curr = symTbl;
  while (curr != NULL) {
    if (strcmp(((entry *) (curr->value))->name,name) == 0) {
      result = copyValue(((entry *) curr->value)->value);
      break;
    }
    curr = curr->next;
  }

  return result;
}

void freeEntry(void *e, void (*f) (void *)) {
  f(((entry *) e)->value);
  free(((entry *) e)->name);
  free(e);
}


chain *removeEntry(chain *symTbl, char *name, void (*f) (void *)) {
  chain *curr, *prev, *newSymTbl;

  curr = symTbl; prev = NULL;
  while (curr != NULL) {
    if (strcmp(((entry *) (curr->value))->name,name) == 0) {
      if ((prev == NULL) && (curr->next == NULL)) {
	newSymTbl = NULL;
      } else {
	if (prev == NULL) {
	  newSymTbl = curr->next;
	} else {
	  prev->next = curr->next;
	  newSymTbl = symTbl;
	}
      }
      freeEntry(((entry *) curr->value),f);
      return newSymTbl;
    }
    prev = curr;
    curr = curr->next;
  }

  return symTbl;
}


void freeSymbolTable(chain *symTbl, void (*f) (void *)) {
  if (symTbl != NULL) {
    if (symTbl->next != NULL) freeSymbolTable(symTbl->next,f);
    freeEntry(symTbl->value,f);
    free(symTbl);
  }
}

void *copyString(void *oldString) {
  char *newString;

  newString = (char *) safeCalloc(strlen((char *) oldString) + 1,sizeof(char));
  strcpy(newString,(char *) oldString);
  return (void *) newString;
}

void freeStringPtr(void *aString) {
  free((char *) aString);
}
