#ifndef DOUBLE_H
#define DOUBLE_H

#include <mpfr.h>
#include "expression.h"
#include "chain.h"

int mpfr_round_to_double(mpfr_t rop, mpfr_t op);
int mpfr_round_to_doubledouble(mpfr_t rop, mpfr_t op);
int mpfr_round_to_tripledouble(mpfr_t rop, mpfr_t op);
int printDoubleInHexa(mpfr_t x);
int readHexa(mpfr_t res, char *c);
node *roundPolynomialCoefficients(node *poly, chain *formats, mp_prec_t prec);

#endif /* ifdef DOUBLE_H*/
