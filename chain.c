#include <stdio.h>
#include <stdlib.h>
#include "chain.h"





void freeChain(chain *c, void (*f) (void *)) {
  chain *curr, *prev;
  curr = c;
  while (curr != NULL) {
    f(curr->value);
    prev = curr;
    curr = curr->next;
    free(prev);
  }
}


chain *addElement(chain *c, void *elem) {
  chain *newChain;

  newChain = (chain *) malloc(sizeof(chain));
  newChain->next = c;
  newChain->value = elem;
  return newChain;
}

void *first(chain *c) {
  return c->value;
}

chain *tail(chain *c) {
  return c->next;
}


chain *copyChain(chain *c, void *(*f) (void *)) {
  chain *copy, *curr;

  copy = NULL;
  curr = c;
  while (curr != NULL) {
    copy = addElement(copy,f(curr->value));
    curr = curr->next;
  }
  return copy;
}


chain* concat(chain *c1, chain *c2) {
  chain *curr;

  if (c1 == NULL) return c2;

  curr = c1;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = c2;

  return c1;
}
