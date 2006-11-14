#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include "chain.h"
#include "main.h"




void freeChain(chain *c, void (*f) (void *)) {
  chain *curr, *prev;
  if (c == NULL) return;
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

  newChain = (chain *) safeMalloc(sizeof(chain));
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


chain* concatChains(chain *c1, chain *c2) {
  chain *curr;

  if (c1 == NULL) return c2;

  curr = c1;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = c2;

  return c1;
}

void freeIntPtr(void *ptr) {
  if (ptr == NULL) return;
  free(ptr);
}

chain *makeIntPtrChain(int n) {
  return makeIntPtrChainFromTo(0,n);
}

chain *makeIntPtrChainFromTo(int m, int n) {
  int i;
  int *elem;
  chain *c;
  
  c = NULL;
  for (i=m;i<=n;i++) {
    elem = (int *) safeMalloc(sizeof(int));
    *elem = i;
    c = addElement(c,elem);
  }

  return c;
}



int lengthChain(chain *c) {
  int i;
  chain *curr;

  i = 0;
  curr = c;
  while (curr != NULL) {
    i++;
    curr = curr->next;
  }

  return i;
}


void sortChain(chain *c,  int (*f) (void *, void *)) {
  chain *curr1, *curr2;
  void *t;

  if (c==NULL) return;
  if (c->next == NULL) return;

  /* else... */
  
  curr1 = c;
  while (curr1 != NULL) {
    curr2 = curr1->next;
    while (curr2 != NULL) {
      if (f(curr1->value, curr2->value)>=0) {
	t = curr1->value;
	curr1->value = curr2->value;
	curr2->value = t;
      }
      curr2 = curr2->next;
    }
    curr1 = curr1->next;
  }
  return;
}

int cmpIntPtr(void *a, void *b) {
  return (*((int *) a) - *((int *) b));
}

int cmpMpfrPtr(void *a, void *b) {
  int res;
  res = -mpfr_cmp(*((mpfr_t *) a), *((mpfr_t *) b));
  return res; 
}
