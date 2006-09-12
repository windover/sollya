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

  if ((long int)(prec)+e-1 < 94-(long int)(HIGHEXPOBIT)) {
    printMessage(1,"Warning: an underflow occured during a conversion.\n");
    setsigne(res,0);
    res[2]=0;
  }
  else {
    if ((long int)(prec)+e-1 >= (long int)(HIGHEXPOBIT)) {
      fprintf(stderr,"Error: an overflow occured during a conversion.\n");
      recoverFromError();
    }
    else {
      setexpo(res,prec+e-1);
      if (s>0) setsigne(res,1); else setsigne(res,-1);
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


void testPari(void) {
  mp_exp_t e;
  mpz_t m;
  int s, i;
  mpfr_t am, bm, cm, dm, em, y, z;
  GEN ap, bp, cp, dp, ep, x;

  mpfr_init2(am, 5);
  mpfr_init2(bm, 8);
  mpfr_init2(cm, 64);
  mpfr_init2(dm, 100);
  mpfr_init2(em, 100);
  mpfr_init2(y, 1000);
  mpfr_init2(z, 1000);

  /* em is set to the number 110.0110...01 with 60 zeros between the ones */
  mpfr_set_ui(em, 51, GMP_RNDN); //exact
  mpfr_div_2ui(em, em, 3, GMP_RNDN); //exact
  mpfr_set_ui(am, 1, GMP_RNDN); //exact
  mpfr_div_2ui(am, am, 64, GMP_RNDN); //exact
  mpfr_add(em, em, am, GMP_RNDN); //exact

  /* other variable are set to several approximations of pi */
  mpfr_const_pi(am, GMP_RNDN);
  mpfr_const_pi(bm, GMP_RNDN);
  mpfr_const_pi(cm, GMP_RNDN);
  mpfr_const_pi(dm, GMP_RNDN);

  /* LOGS */
  fprintf(stderr, "Bits in long : %ld\nSize of long : %ld\nHig expo bit : %ld\n\n", BITS_IN_LONG, (long int)sizeof(long), (long int) HIGHEXPOBIT);
  
  /* Value of pi in PARI */
  x = mppi(10);
  fprintf(stderr, "Pi in PARI : sign %d, exponent %ld, mantissa : ",gsigne(x),gexpo(x));
  for(i=2;i<=lg(x)-1;i++) fprintf(stderr, "%lx ", x[i]);

  fprintf(stderr, "\n");
  outbeaut(x);
  fprintf(stderr, "\n");
  /* end */
  

  /* am */
  ap = mpfr_to_PARI(am);
  mpz_init(m);
  s = mpfr_sgn(am);
  e = mpfr_get_z_exp(m,am);
  fprintf(stderr, "am : sign %d, exponent %d, mantissa : ",s,(int)e);
  mpz_out_str(stderr, 2, m);
  fprintf(stderr, "\n");
  fprintf(stderr, "ap : sign %d, exponent %ld, mantissa : ",gsigne(ap),gexpo(ap));
  for(i=2;i<=lg(ap)-1;i++) fprintf(stderr, "%lx ", ap[i]);

  fprintf(stderr, "\n");
  outbeaut(ap);
  fprintf(stderr, "\n");
  /* end */

  /* bm */
  bp = mpfr_to_PARI(bm);
  mpz_init(m);
  s = mpfr_sgn(bm);
  e = mpfr_get_z_exp(m,bm);
  fprintf(stderr, "bm : sign %d, exponent %d, mantissa : ",s,(int)e);
  mpz_out_str(stderr, 2, m);
  fprintf(stderr, "\n");
  fprintf(stderr, "bp : sign %d, exponent %ld, mantissa : ",gsigne(bp),gexpo(bp));
  for(i=2;i<=lg(bp)-1;i++) fprintf(stderr, "%lx ", bp[i]);

  fprintf(stderr, "\n");
  outbeaut(bp);
  fprintf(stderr, "\n");
  /* end */

  /* cm */
  cp = mpfr_to_PARI(cm);
  mpz_init(m);
  s = mpfr_sgn(cm);
  e = mpfr_get_z_exp(m,cm);
  fprintf(stderr, "cm : sign %d, exponent %d, mantissa : ",s,(int)e);
  mpz_out_str(stderr, 2, m);
  fprintf(stderr, "\n");
  fprintf(stderr, "cp : sign %d, exponent %ld, mantissa : ",gsigne(cp),gexpo(cp));
  for(i=2;i<=lg(cp)-1;i++) fprintf(stderr, "%lx ", cp[i]);

  fprintf(stderr, "\n");
  outbeaut(cp);
  fprintf(stderr, "\n");
  /* end */

  /* dm */
  dp = mpfr_to_PARI(dm);
  mpz_init(m);
  s = mpfr_sgn(dm);
  e = mpfr_get_z_exp(m,dm);
  fprintf(stderr, "dm : sign %d, exponent %d, mantissa : ",s,(int)e);
  mpz_out_str(stderr, 2, m);
  fprintf(stderr, "\n");
  fprintf(stderr, "dp : sign %d, exponent %ld, mantissa : ",gsigne(dp),gexpo(dp));
  for(i=2;i<=lg(dp)-1;i++) fprintf(stderr, "%lx ", dp[i]);

  fprintf(stderr, "\n");
  outbeaut(dp);
  fprintf(stderr, "\n");
  /* end */

  /* em */
  ep = mpfr_to_PARI(em);
  mpz_init(m);
  s = mpfr_sgn(em);
  e = mpfr_get_z_exp(m,em);
  fprintf(stderr, "em : sign %d, exponent %d, mantissa : ",s,(int)e);
  mpz_out_str(stderr, 2, m);
  fprintf(stderr, "\n");
  fprintf(stderr, "ep : sign %d, exponent %ld, mantissa : ",gsigne(ep),gexpo(ep));
  for(i=2;i<=lg(ep)-1;i++) fprintf(stderr, "%lx ", ep[i]);

  fprintf(stderr, "\n");
  outbeaut(ep);
  fprintf(stderr, "\n");
  /* end */

  /* Over- and under- flow in PARI */
  x = gp_read_str("0.5");
  fprintf(stderr, "1/2: sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("1.");
  fprintf(stderr, "+1 : sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("2.");
  fprintf(stderr, "+2 : sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("0.");
  setexpo(x,0);  
  fprintf(stderr, "+0 : sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("-0.5");
  fprintf(stderr, "-0.5 sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("-1.");
  fprintf(stderr, "-1 : sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("-2.");
  fprintf(stderr, "-2 : sign %d, exponent %ld, corresponding long %lx ",gsigne(x),gexpo(x), x[1]);
  fprintf(stderr, "\n");

  x = gp_read_str("2.");
  setexpo(x, (long int)(HIGHEXPOBIT)-1);
  fprintf(stderr, "x = 2^HEB : "); outbeaut(x);
  //gmulz(x, gen_2, ep);

  x = gp_read_str("2.");
  setexpo(x, (long int)(94)-(long int)(HIGHEXPOBIT));
  fprintf(stderr, "x = 2^(-HEB+3) : "); outbeaut(x);printf("\n");
  // gdivz(x, gen_2, ep);
  // fprintf(stderr, "x = 2^(-HEB+3) : "); outbeaut(ep);printf("\n");

  /* Verifying that the functions work well */
  x = mppi(12);
  PARI_to_mpfr(y, x, GMP_RNDN);
  if (gequal(mpfr_to_PARI(y), x)) fprintf(stderr, "Test 1 : OK\n");
  else fprintf(stderr, "Test 1 : FAILED\n");

  setsigne(x, -1);
  PARI_to_mpfr(y, x, GMP_RNDN);
  if (gequal(mpfr_to_PARI(y), x)) fprintf(stderr, "Test 2 : OK\n");
  else fprintf(stderr, "Test 2 : FAILED\n");

  mpfr_const_pi(y, GMP_RNDN);
  x = mpfr_to_PARI(y);
  PARI_to_mpfr(z, x, GMP_RNDN);
  if (mpfr_equal_p(y,z)) fprintf(stderr, "Test 3 : OK \n");
  else fprintf(stderr, "Test 3 : FAILED !\n");

  mpfr_neg(y, y, GMP_RNDN);
  x = mpfr_to_PARI(y);
  PARI_to_mpfr(z, x, GMP_RNDN);
  if (mpfr_equal_p(y,z)) fprintf(stderr, "Test 4 : OK \n");
  else fprintf(stderr, "Test 4 : FAILED !\n");

  mpz_clear(m);
  mpfr_clear(am);
  mpfr_clear(bm);
  mpfr_clear(cm);
  mpfr_clear(dm);
  mpfr_clear(em);
  mpfr_clear(y);
  mpfr_clear(z);
}

