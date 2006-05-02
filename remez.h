#ifndef REMEZ_H
#define REMEZ_H



#include <mpfr.h>
#include "expression.h"
#include "remez.h"


node* remez(node *func, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec);


#endif /* ifdef REMEZ_H*/
