#ifndef INTEGRAL_H
#define INTEGRAL_H


#include <mpfr.h>
#include "expression.h"

rangetype integral(node *func, mpfr_t a, mpfr_t b, mp_prec_t prec, mpfr_t diam);

#endif /* ifdef INTEGRAL_H*/
