#ifndef DOUBLE_H
#define DOUBLE_H

#include <mpfr.h>
#include "expression.h"
#include "chain.h"

int round_to_format(mpfr_t rop, mpfr_t op, int prec, mp_rnd_t mode);
int mpfr_round_to_double(mpfr_t rop, mpfr_t op);
int mpfr_round_to_doubledouble(mpfr_t rop, mpfr_t op);
int mpfr_round_to_tripledouble(mpfr_t rop, mpfr_t op);
int mpfr_round_to_doubleextended(mpfr_t rop, mpfr_t op);
int printDoubleInHexa(mpfr_t x);
int readHexa(mpfr_t res, char *c);
node *roundPolynomialCoefficients(node *poly, chain *formats, mp_prec_t prec);
int printDoubleExpansion(mpfr_t x);
int printPolynomialAsDoubleExpansion(node *poly, mp_prec_t prec);
void mpfr_round_to_format(mpfr_t rop, mpfr_t op, int format);
int mpfr_mant_exp(mpfr_t rop, mp_exp_t *expo, mpfr_t op);

#endif /* ifdef DOUBLE_H*/
