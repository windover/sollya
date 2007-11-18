#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chain.h"
#include "assignment.h"
#include "expression.h"
#include "general.h"


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


void freeNothing(void *thing) {
  return;
}

void freeDeclaredSymbolTable(chain *declSymTbl, void (*f) (void *)) {
  chain *curr;

  curr = declSymTbl;
  while (curr != NULL) {
    freeSymbolTable((chain *) (curr->value), f);
    curr->value = NULL;
    curr = curr->next;
  }

  freeChain(declSymTbl, freeNothing);
}

chain *pushFrame(chain *declSymTbl) {

  return addElement(declSymTbl, NULL);

}

chain *popFrame(chain *declSymTbl, void (*f) (void *)) {
  chain *newDeclSymTbl;

  if (declSymTbl == NULL) return NULL;

  newDeclSymTbl = declSymTbl->next;

  freeSymbolTable((chain *) (declSymTbl->value), f);

  free(declSymTbl);

  return newDeclSymTbl;
}

chain *declareNewEntry(chain *declSymTbl, char *name, void *value, void * (*copyValue) (void *)) {
  chain *newValue;

  if (declSymTbl == NULL) return NULL;

  if (containsEntry((chain *) (declSymTbl->value), name)) return declSymTbl;

  newValue = addEntry((chain *) (declSymTbl->value), name, value, copyValue);

  declSymTbl->value = newValue;

  return declSymTbl;
}

chain *replaceDeclaredEntry(chain *declSymTbl, char *name, void *value, void * (*copyValue) (void *), void (*freeValue) (void *)) {
  chain *curr;
  chain *newValue;

  if (declSymTbl == NULL) return NULL;

  curr = declSymTbl;
  while (curr != NULL) {
    if (containsEntry((chain *) (curr->value), name)) {
      newValue = removeEntry((chain *) (curr->value), name, freeValue);
      curr->value = newValue;
      newValue = addEntry((chain *) (curr->value), name, value, copyValue);
      curr->value = newValue;
      break;
    }
    curr = curr->next;
  }
  
  return declSymTbl;
}

int containsDeclaredEntry(chain *declSymTbl, char *name) {
  chain *curr;

  curr = declSymTbl;
  while (curr != NULL) {
    if (containsEntry((chain *) (curr->value), name)) return 1;
    curr = curr->next;
  }

  return 0;
}

void *getDeclaredEntry(chain *declSymTbl, char *name, void * (*copyValue) (void *)) {
  chain *curr;

  curr = declSymTbl;
  while (curr != NULL) {
    if (containsEntry((chain *) (curr->value), name)) return getEntry((chain *) (curr->value), name, copyValue);
    curr = curr->next;
  }

  return NULL;
}



chain *assignDeclaredEntry(chain *declSymTbl, char *name, void *value, void * (*copyValue) (void *), void (*freeValue) (void *)) {
  chain *newDeclSymTbl;

  if (containsDeclaredEntry(declSymTbl, name)) 
    newDeclSymTbl = replaceDeclaredEntry(declSymTbl, name, value, copyValue, freeValue);
  else 
    newDeclSymTbl = declareNewEntry(declSymTbl, name, value, copyValue);

  return newDeclSymTbl; 
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

