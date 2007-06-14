#ifndef REMEZ_H
#define REMEZ_H



#include <mpfr.h>
#include "expression.h"
#include "remez.h"
#include "chain.h"
#include "infnorm.h"

chain *uncertifiedFindZeros(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);

node* remez(node *func, node *weight, chain* monom, mpfr_t a, mpfr_t b, mpfr_t *requestedQuality, mp_prec_t prec);
node* remezWithWeight(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec);

rangetype guessDegree(node *func, node *weight, mpfr_t a, mpfr_t b, mpfr_t eps);


#endif /* ifdef REMEZ_H*/
