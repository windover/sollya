#include <gmp.h>
#include <mpfr.h>
#include "expansion.h"



void mpfr_to_double(double *dh, mpfr_t op) {
  *dh = mpfr_get_d(op, GMP_RNDN);
}

void mpfr_to_doubledouble(double *dh, double *dm, mpfr_t op) {
  mpfr_t rest, temp;

  mpfr_init2(rest,mpfr_get_prec(op));
  mpfr_init2(temp,mpfr_get_prec(op));

  mpfr_set(rest,op,GMP_RNDN);

  *dh = mpfr_get_d(rest, GMP_RNDN);
  mpfr_set_d(temp,*dh,GMP_RNDN);
  mpfr_sub(rest,rest,temp,GMP_RNDN);
  
  *dm = mpfr_get_d(rest, GMP_RNDN);
  mpfr_set_d(temp,*dm,GMP_RNDN);
  mpfr_sub(rest,rest,temp,GMP_RNDN);

  mpfr_clear(rest);
  mpfr_clear(temp);
}

void mpfr_to_tripledouble(double *dh, double *dm, double *dl, mpfr_t op) {
  mpfr_t rest, temp;

  mpfr_init2(rest,mpfr_get_prec(op));
  mpfr_init2(temp,mpfr_get_prec(op));

  mpfr_set(rest,op, GMP_RNDN);

  *dh = mpfr_get_d(rest, GMP_RNDN);
  mpfr_set_d(temp,*dh,GMP_RNDN);
  mpfr_sub(rest,rest,temp,GMP_RNDN);
  
  *dm = mpfr_get_d(rest, GMP_RNDN);
  mpfr_set_d(temp,*dm,GMP_RNDN);
  mpfr_sub(rest,rest,temp,GMP_RNDN);

  *dl = mpfr_get_d(rest, GMP_RNDN);
  mpfr_set_d(temp,*dl,GMP_RNDN);
  mpfr_sub(rest,rest,temp,GMP_RNDN);

  mpfr_clear(rest);
  mpfr_clear(temp);
}

void double_to_mpfr(mpfr_t rop, double dh) {
  mpfr_set_d(rop,dh,GMP_RNDN);
}

void doubledouble_to_mpfr(mpfr_t rop, double dh, double dm) {
  mpfr_t temp;
  mp_prec_t prec;

  prec = mpfr_get_prec(rop);
  
  if (prec < 53) prec = 53;

  mpfr_init2(temp, prec);
  
  mpfr_set_d(rop, dh, GMP_RNDN);
  
  mpfr_set_d(temp, dm, GMP_RNDN);
  mpfr_add(rop, rop, temp, GMP_RNDN);
  
  mpfr_clear(temp);
}

void tripledouble_to_mpfr(mpfr_t rop, double dh, double dm, double dl) {
  mpfr_t temp;
  mp_prec_t prec;

  prec = mpfr_get_prec(rop);
  
  if (prec < 53) prec = 53;

  mpfr_init2(temp, prec);
  
  mpfr_set_d(rop, dh, GMP_RNDN);
  
  mpfr_set_d(temp, dm, GMP_RNDN);
  mpfr_add(rop, rop, temp, GMP_RNDN);

  mpfr_set_d(temp, dl, GMP_RNDN);
  mpfr_add(rop, rop, temp, GMP_RNDN);

  
  mpfr_clear(temp);
}

