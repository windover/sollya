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
#include <mpfr.h>
#include "chain.h"
#include "general.h"




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

chain *copyChainWithoutReversal(chain *c, void * (*f) (void *)) {
  void **array;
  int len, i; 
  chain *curr, *copy;

  if (c == NULL) return NULL;

  len = lengthChain(c);
  array = (void *) safeCalloc(len,sizeof(void *));
  curr = c; i = 0;
  while (curr != NULL) {
    array[i++] = curr->value;
    curr = curr->next;
  }
  copy = NULL;
  for (i=len-1;i>=0;i--) {
    copy = addElement(copy,f(array[i]));
  }
  free(array);
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


// Removes the first occurence of n in a chain containing int values
// The chain c is modified.
// If n is not the first element of the chain, the returned pointer
// points at the same place as c
chain *removeInt(chain *c, int n) {
  chain *curr;
  int i;

  if(c==NULL) return c;
  //else

  curr = c;
  i = *(int *)(curr->value);
  if(i==n) {
    curr=c->next;
    free(c->value);
    free(c);
    return curr;
  }
  else {
    curr = removeInt(c->next, n);
    c->next=curr;
    return c;
  }
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
  for (i=n;i>=m;i--) {
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

void printIntChain(chain *c) {
  chain *curr=c;
  printf("[");
  while(curr!=NULL) {
    printf(" %d ", *(int *)(curr->value));
    curr=curr->next;
  }
  printf("]\n");
  return;
}

void *accessInList(chain *c, int index) {
  chain *curr;
  int i;

  if (index < 0) return NULL;

  curr = c; i = 0;
  while (curr != NULL) {
    if (i == index) return curr->value;
    i++;
    curr = curr->next;
  }

  return NULL;
}

chain *copyChainAndReplaceNth(chain *c, int k, void *obj, void * (*f) (void *)) {
  void **array;
  int len, i; 
  chain *curr, *copy;

  if (c == NULL) return NULL;

  len = lengthChain(c);
  array = (void *) safeCalloc(len,sizeof(void *));
  curr = c; i = 0;
  while (curr != NULL) {
    array[i++] = curr->value;
    curr = curr->next;
  }

  if ((k >= 0) && (k < len)) {
    array[k] = obj;
  }

  copy = NULL;
  for (i=len-1;i>=0;i--) {
    copy = addElement(copy,f(array[i]));
  }
  free(array);
  return copy;
}

int isEqualChain(chain *c, chain *c2, int (*f) (void *, void *)) {
  chain *curr, *curr2;

  if (lengthChain(c) != lengthChain(c2)) return 0;

  curr = c; curr2 = c2;
  while (curr != NULL) {
    if (!f(curr->value,curr2->value)) return 0;
    curr = curr->next;
    curr2 = curr2->next;
  }
  return 1;
}
