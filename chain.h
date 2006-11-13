#ifndef CHAIN_H
#define CHAIN_H

typedef struct chainStruct chain;

struct chainStruct 
{
  void *value;
  chain *next;
};


void freeChain(chain *c, void (*f) (void *));
chain *addElement(chain *c, void *elem);
void *first(chain *c);
chain *tail(chain *c);
chain *copyChain(chain *c, void * (*f) (void *));
chain *concatChains(chain *c1, chain *c2);
void freeIntPtr(void *ptr);
chain *makeIntPtrChain(int n);
chain *makeIntPtrChainFromTo(int m, int n);
int lengthChain(chain *c);
void sortChain(chain *c,  int (*f) (void *, void *));
int cmpIntPtr(void *a, void *b);
int cmpMpfrPtr(void *a, void *b);

#endif /* ifdef CHAIN_H*/
