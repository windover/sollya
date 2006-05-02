#ifndef INFNORM_H
#define INFNORM_H


#include <mpfr.h>
#include "expression.h"

rangetype infnorm(node *func, rangetype range, mp_prec_t prec, mpfr_t diam);


#endif /* ifdef REMEZ_H*/
