#include <gmp.h>
#include <mpfr.h>
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <errno.h>
#include "expression.h"
#include "double.h"
#include "main.h"




int mpfr_round_to_double(mpfr_t rop, mpfr_t op) {
  double d;
  int res;

  if (mpfr_get_prec(op) < 53) {
    printMessage(1,"Warning: rounding a value computed on less than 53 bits to double precision.\n");
  }

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(rop,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double precision rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }
  
  res = mpfr_cmp(rop,op);

  return res;
}

int mpfr_round_to_doubledouble(mpfr_t rop, mpfr_t op) {
  double d;
  mpfr_t accu, temp, rest;
  mp_prec_t prec;
  int res;

  prec = mpfr_get_prec(op);
  if (prec < 106) {
    printMessage(1,"Warning: rounding a value computed on less than 106 bits to double-double precision.\n");
    prec = 106;
  }

  mpfr_init2(accu, prec);
  mpfr_init2(temp, prec);
  mpfr_init2(rest, prec);

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(accu,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_set(rop,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }

  res = mpfr_cmp(rop,op);

  mpfr_clear(accu);
  mpfr_clear(temp);
  mpfr_clear(rest);
  return res;
}

int mpfr_round_to_tripledouble(mpfr_t rop, mpfr_t op) {
  double d;
  mpfr_t accu, temp, rest;
  mp_prec_t prec;
  int res;

  prec = mpfr_get_prec(op);
  if (prec < 159) {
    printMessage(1,"Warning: rounding a value computed on less than 159 bits to triple-double precision\n");
    prec = 159;
  }

  mpfr_init2(accu, prec);
  mpfr_init2(temp, prec);
  mpfr_init2(rest, prec);

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(accu,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_set(rop,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }

  res = mpfr_cmp(rop,op);

  mpfr_clear(accu);
  mpfr_clear(temp);
  mpfr_clear(rest);

  return res;
}
