#include <gmp.h>
#include <mpfr.h>
#include <fpu_control.h>
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


void f(mpfr_t y, mpfr_t xMpfr) {
  unsigned short oldcw, cw;
#if defined(D_TO_D)
  double x;
  double resh;
#elif defined(D_TO_DD)
  double x;
  double resh, resm;
#elif defined(D_TO_TD)
  double x;
  double resh, resm, resl;
#elif defined(DD_TO_DD)
  double xh, xm;
  double resh, resm;
#elif defined(DD_TO_TD)
  double xh, xm;
  double resh, resm, resl;
#elif defined (TD_TO_TD)
  double xh, xm, xl;
  double resh, resm, resl;
#endif

  _FPU_GETCW(oldcw);
  cw = (_FPU_DEFAULT & ~_FPU_EXTENDED)|_FPU_DOUBLE;
  _FPU_SETCW(cw);

#if defined(D_TO_D)
  mpfr_to_double(&x, xMpfr);     
  p(&resh, x);
  double_to_mpfr(y, resh);
#elif defined(D_TO_DD)
  mpfr_to_double(&x, xMpfr);
  p(&resh, &resm, x);
  doubledouble_to_mpfr(y, resh, resm);
#elif defined(D_TO_TD)
  mpfr_to_double(&x, xMpfr);
  p(&resh, &resm, &resl, x);
  tripledouble_to_mpfr(y, resh, resm, resl);
#elif defined(DD_TO_DD)
  mpfr_to_doubledouble(&xh, &xm, xMpfr);
  p(&resh, &resm, xh, xm);
  doubledouble_to_mpfr(y, resh, resm);
#elif defined(DD_TO_TD)
  mpfr_to_doubledouble(&xh, &xm, xMpfr);
  p(&resh, &resm, &resl, xh, xm);
  tripledouble_to_mpfr(y, resh, resm, resl);
#elif defined(TD_TO_TD)
  mpfr_to_tripledouble(&xh, &xm, &xl, xMpfr);
  p(&resh, &resm, &resl, xh, xm, xl);
  tripledouble_to_mpfr(y, resh, resm, resl);
#else
#warning You must define one of the macros for the argument and result formats
  mpfr_set(y,xMpfr,GMP_RNDN);
#endif

  _FPU_SETCW(oldcw);

}
