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
chain *removeInt(chain *c, int n);
void *first(chain *c);
chain *tail(chain *c);
chain *copyChain(chain *c, void * (*f) (void *));
chain *copyChainWithoutReversal(chain *c, void * (*f) (void *));
chain *concatChains(chain *c1, chain *c2);
void freeIntPtr(void *ptr);
chain *makeIntPtrChain(int n);
chain *makeIntPtrChainFromTo(int m, int n);
int lengthChain(chain *c);
void sortChain(chain *c,  int (*f) (void *, void *));
int cmpIntPtr(void *a, void *b);
int cmpMpfrPtr(void *a, void *b);
void printIntChain(chain *c);
void *accessInList(chain *, int);
chain *copyChainAndReplaceNth(chain *c, int k, void *obj, void * (*f) (void *));
int isEqualChain(chain *c, chain *c2, int (*f) (void *, void *));

#endif /* ifdef CHAIN_H*/
