#ifndef INTEGRAL_H
#define INTEGRAL_H


#include <mpfr.h>
#include "expression.h"

rangetype integral(node *func, rangetype range, mp_prec_t prec, mpfr_t diam);
void uncertifiedIntegral(mpfr_t result, node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);

#endif /* ifdef INTEGRAL_H*/
