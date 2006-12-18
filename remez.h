#ifndef REMEZ_H
#define REMEZ_H



#include <mpfr.h>
#include "expression.h"
#include "remez.h"
#include "chain.h"
#include "infnorm.h"

node* remez(node *func, chain* monom, mpfr_t a, mpfr_t b, mp_prec_t prec);
node* remezWithWeight(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec);

#endif /* ifdef REMEZ_H*/
