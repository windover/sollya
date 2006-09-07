#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>

#include "main.h"
#include "pari_utils.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>


GEN mpfr_to_PARI(mpfr_t x) {
  mp_exp_t e;
  mp_prec_t prec,q,r;
  mpz_t m;
  int s;
  GEN res;

  prec = mpfr_get_prec(x);
  r = prec % BITS_IN_LONG;
  q = prec/BITS_IN_LONG;

  if (!mpfr_number_p(x)) {
    fprintf(stderr,"Error: cannot convert Inf or Nan to PARI.\n");
    recoverFromError();
  }
  if (mpfr_zero_p(x)) {
    res = cgetr(q+3);
    setsigne(res,0);
    res[2] = 0;
    return res;
  }  


  mpz_init(m);
  s = mpfr_sgn(x);
  e = mpfr_get_z_exp(m,x);
  if (s<0) mpz_neg(m,m);
  if (r==0) { r = BITS_IN_LONG; q--; } 
  mpz_mul_2exp(m, m, BITS_IN_LONG-r);
  res = cgetr(q+3);
  mpz_export(&(res[2]),NULL,1,BITS_IN_LONG/8,0,0,m);

  if ((long int)(prec)+e-1 < 3-HIGHEXPOBIT) {
    printMessage(1,"Warning: an underflow occured during a conversion.\n");
    setsigne(res,0);
    res[2]=0;
  }
  else {
    if ((long int)(prec)+e-1 >= HIGHEXPOBIT) {
      fprintf(stderr,"Error: an overflow occured during a conversion.\n");
      recoverFromError();
    }
    else {
      setexpo(res,prec+e-1);
      setsigne(res,s);
    }
  }

  mpz_clear(m);
  return res;
}


// No check of the type of x is made (t_REAL or t_INT)
void PARI_to_mpfr(mpfr_t y, GEN x, mp_rnd_t rnd) {
  long length;
  mpz_t m;
  int s;

  s = gsigne(x);

  if (s==0) {
    mpfr_set_d(y,0.,GMP_RNDN);
    return;
  }

  if (gexpo(x)+1 > mpfr_get_emax()) {
    printMessage(1,"Warning: generating Inf in a conversion.\n");
    mpfr_set_inf(y, s);
    return;
  }

  if (gexpo(x)+1 < mpfr_get_emin()) {
    printMessage(1,"Warning: generating zero in a conversion.\n");
    mpfr_set_d(y,0.,GMP_RNDN);
    return;
  }

  mpz_init(m);

  length = lg(x)-2;
  mpz_import(m,length,1,BITS_IN_LONG/8,0,0,&(x[2]));

  mpfr_set_z(y,m,rnd);
  mpfr_set_exp(y,(mp_prec_t)(gexpo(x)+1));
  if (s<0) mpfr_neg(y,y,GMP_RNDN);

  mpz_clear(m);
  return;
}


GEN evaluate_to_PARI(node *tree, GEN x, mp_prec_t prec) {
  GEN res;
  mpfr_t res_mpfr, x_mpfr;
 
  mpfr_init2(x_mpfr, prec);
  mpfr_init2(res_mpfr, prec);

  PARI_to_mpfr(x_mpfr, x, GMP_RNDN);
  evaluate(res_mpfr, tree, x_mpfr, prec);
  res = mpfr_to_PARI(res_mpfr);

  mpfr_clear(x_mpfr);
  mpfr_clear(res_mpfr);
  return res;
}
