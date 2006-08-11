#ifndef INFNORM_H
#define INFNORM_H


#include <mpfr.h>
#include <mpfi.h>
#include <stdio.h>
#include "expression.h"
#include "chain.h"


rangetype infnorm(node *func, rangetype range, chain *excludes, mp_prec_t prec, mpfr_t diam, FILE *proof);
chain* findZerosFunction(node *func, rangetype range, mp_prec_t prec, mpfr_t diam);
void uncertifiedInfnorm(mpfr_t result, node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);
void evaluateRangeFunction(rangetype yrange, node *func, rangetype xrange, mp_prec_t prec);
void evaluateRangeFunctionFast(rangetype yrange, node *func, node *deriv, rangetype xrange, mp_prec_t prec);
void fprintInterval(FILE *fd, mpfi_t interval);
void freeMpfiPtr(void *i);
void *copyMpfiPtr(void *ptr);
chain *joinAdjacentIntervalsMaximally(chain *intervals);
int checkInfnorm(node *func, rangetype range, mpfr_t infnormval, mpfr_t diam, mp_prec_t prec);

#endif /* ifdef INFNORM_H*/
