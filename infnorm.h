#ifndef INFNORM_H
#define INFNORM_H


#include <mpfr.h>
#include <mpfi.h>
#include <stdio.h>
#include "expression.h"
#include "chain.h"


#define ISFLOATINGPOINTEVALUABLE 0
#define ISHOPITALEVALUABLE 1
#define ISNOTEVALUABLE 2

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
void evaluateConstantWithErrorEstimate(mpfr_t res, mpfr_t err, node *func, mpfr_t x, mp_prec_t prec);
chain* fpFindZerosFunction(node *func, rangetype range, mp_prec_t prec);
chain *uncertifiedZeroDenominators(node *tree, mpfr_t a, mpfr_t b, mp_prec_t prec);
int isEvaluable(node *func, mpfr_t x, mpfr_t *y, mp_prec_t prec);
int evaluateWithAccuracy(node *func, mpfr_t x, mpfr_t y, mpfr_t accur, 
			 mp_prec_t minprec, mp_prec_t maxprec, mp_prec_t *needPrec);

#endif /* ifdef INFNORM_H*/
