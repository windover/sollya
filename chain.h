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
chain *concat(chain *c1, chain *c2);






#endif /* ifdef CHAIN_H*/
