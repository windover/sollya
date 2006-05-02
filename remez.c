#include <mpfr.h>
#include "expression.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>




node* remez(node *func, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t x,y;

  mpfr_init2(x,prec);
  mpfr_init2(y,prec);
  mpfr_set(x,a,GMP_RNDN);
  mpfr_set(y,b,GMP_RNDN);
  printf("Invoked remez with degree %d on range [",deg);
  printValue(&x,prec);
  printf(";");
  printValue(&y,prec);
  printf("]\n");
  mpfr_clear(x);
  mpfr_clear(y);
  return copyTree(func);
}



