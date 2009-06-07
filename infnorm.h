/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.org
sylvain.chevillard@ens-lyon.org
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinity norm, an automatic polynomial
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

chain *joinAdjacentIntervalsMaximally(chain *intervals);
int checkInfnorm(node *func, rangetype range, mpfr_t infnormval, mpfr_t diam, mp_prec_t prec);
void evaluateConstantWithErrorEstimate(mpfr_t res, mpfr_t err, node *func, mpfr_t x, mp_prec_t prec);
chain* fpFindZerosFunction(node *func, rangetype range, mp_prec_t prec);
chain *uncertifiedZeroDenominators(node *tree, mpfr_t a, mpfr_t b, mp_prec_t prec);
int isEvaluable(node *func, mpfr_t x, mpfr_t *y, mp_prec_t prec);
int evaluateWithAccuracy(node *func, mpfr_t x, mpfr_t y, mpfr_t accur, 
			 mp_prec_t minprec, mp_prec_t maxprec, mp_prec_t *needPrec);
int evaluateFaithfulOrFail(node *func, mpfr_t x, mpfr_t y, unsigned int precFactor, mp_prec_t *needPrec);
int evaluateFaithful(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec);
int accurateInfnorm(mpfr_t result, node *func, rangetype range, chain *excludes, mp_prec_t startPrec);
int evaluateFaithfulWithCutOff(mpfr_t result, node *func, mpfr_t x, mpfr_t cutoff, mp_prec_t startprec);
int evaluateFaithfulWithCutOffFast(mpfr_t result, node *func, node *deriv, mpfr_t x, mpfr_t cutoff, mp_prec_t startprec);

int newtonMPFR(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec);
int evaluateSign(int *s, node *rawFunc);
int compareConstant(int *cmp, node *func1, node *func2);

void mpfi_pow(mpfi_t z, mpfi_t x, mpfi_t y);
void special_mpfi_div(mpfi_t rop, mpfi_t a, mpfi_t b);
void special_mpfi_div(mpfi_t rop, mpfi_t a, mpfi_t b);
void mpfi_round_to_double(mpfi_t rop, mpfi_t op);
void mpfi_round_to_doubledouble(mpfi_t rop, mpfi_t op);
void mpfi_round_to_tripledouble(mpfi_t rop, mpfi_t op);
void mpfi_round_to_doubleextended(mpfi_t rop, mpfi_t op);
void mpfi_erf(mpfi_t rop, mpfi_t op);
void mpfi_erfc(mpfi_t rop, mpfi_t op);
void mpfi_ceil(mpfi_t rop, mpfi_t op);
void mpfi_floor(mpfi_t rop, mpfi_t op);

#endif /* ifdef INFNORM_H*/
