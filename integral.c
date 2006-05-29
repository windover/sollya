#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"
#include "infnorm.h"
#include "integral.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define DEBUG 0
#define DEBUGMPFI 0



rangetype integral(node *func, rangetype interval, mp_prec_t prec, mpfr_t diam) {
  node *deriv;

  deriv = differentiate(func);
  
  rangetype x,y;
  mpfr_t x1,x2,y1,y2;
  mpfi_t temp, val;

  rangetype sum;
  sum.a = (mpfr_t*) malloc(sizeof(mpfr_t));
  sum.b = (mpfr_t*) malloc(sizeof(mpfr_t));
  mpfr_init2(*(sum.a),prec);
  mpfr_init2(*(sum.b),prec);
  mpfr_set_d(*(sum.a),0.,GMP_RNDD);
  mpfr_set_d(*(sum.b),0.,GMP_RNDU);
  
  
  if (mpfr_equal_p(*(interval.a),*(interval.b))) {
    printf("Warning: the given interval is reduced to one point.\n");
    return sum;
  }

  if (mpfr_less_p(*(interval.b),*(interval.a))) {
    printf("Error: the interval is empty.\n");
    return sum;
  }

  mpfi_init2(temp,prec);
  mpfi_init2(val,prec);

  mpfr_init2(x1,prec);
  mpfr_init2(x2,prec);
  mpfr_set(x1, *(interval.a),GMP_RNDD);
  mpfr_add(x2, x1, diam, GMP_RNDN);
  x.a = &x1;
  x.b = &x2;
  
  mpfr_init2(y1,prec);
  mpfr_init2(y2,prec);
  y.a = &y1;
  y.b = &y2;


  while(mpfr_less_p(x2,*(interval.b))) {
    evaluateRangeFunctionFast(y, func, deriv, x, prec);

    mpfi_set_fr(temp, x1);
    mpfi_set_fr(val, x2);
    mpfi_sub(temp, val, temp);
    
    mpfi_interv_fr(val, *(y.a), *(y.b));
    mpfi_mul(temp, temp, val);
    
    mpfi_get_left(y1, temp);
    mpfi_get_right(y2, temp);
    mpfr_add(*(sum.a), *(sum.a), y1, GMP_RNDD);
    mpfr_add(*(sum.b), *(sum.b), y2, GMP_RNDU);
    
    mpfr_set(x1,x2,GMP_RNDD); // exact
    mpfr_add(x2, x1, diam, GMP_RNDN);
  }

  mpfr_set(x2,*(interval.b),GMP_RNDU);
  evaluateRangeFunction(y, func, x, prec);

  mpfi_set_fr(temp, x1);
  mpfi_set_fr(val, x2);
  mpfi_sub(temp, val, temp);
    
  mpfi_interv_fr(val, *(y.a), *(y.b));
  mpfi_mul(temp, temp, val);
    
  mpfi_get_left(y1, temp);
  mpfi_get_right(y2, temp);
  mpfr_add(*(sum.a), *(sum.a), y1, GMP_RNDD);
  mpfr_add(*(sum.b), *(sum.b), y2, GMP_RNDU);
  
 
  free_memory(deriv);
  mpfi_clear(val); mpfi_clear(temp);
  mpfr_clear(x1); mpfr_clear(x2);  
  mpfr_clear(y1); mpfr_clear(y2);
  
  return sum;
}

void uncertifiedIntegral(mpfr_t result, node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec) {
  mpfr_t sum, temp, x, y1, y2, step;

  mpfr_init2(step, prec);

  mpfr_sub(step, b, a, GMP_RNDN);
  mpfr_div_ui(step, step, points, GMP_RNDN);
 
  if (mpfr_sgn(step) == 0) {
    printf("Warning: the given interval is reduced to one point.\n");
    mpfr_set_d(result,0.,GMP_RNDN);
    mpfr_clear(step);
    return;
  }

  if (mpfr_sgn(step) < 0) {
    printf("Error: the interval is empty.\n");
    mpfr_set_d(result,0.,GMP_RNDN);
    mpfr_clear(step);
    return;
  }

  mpfr_init2(x, prec);
  mpfr_init2(y1, prec);
  mpfr_init2(y2, prec);
  mpfr_init2(temp, prec);
  mpfr_init2(sum, prec);

  mpfr_set_d(sum,0.,GMP_RNDN);

  mpfr_set(x,a,GMP_RNDN);
  evaluate(y1,tree,x,prec);

  mpfr_add(x,x,step,GMP_RNDU);
  if (mpfr_greater_p(x,b)) {
    mpfr_sub(x, x, step, GMP_RNDN);
    mpfr_sub(step, b, x, GMP_RNDN);
    mpfr_set(x,b,GMP_RNDN);
  }
  evaluate(y2,tree,x,prec);

  while(mpfr_lessequal_p(x,b)) {
    mpfr_add(temp, y1, y2, GMP_RNDN);
    mpfr_div_2ui(temp, temp, 1, GMP_RNDN);
    mpfr_mul(temp, temp, step, GMP_RNDN);
    mpfr_add(sum,sum,temp, GMP_RNDN);

    mpfr_set(y1, y2, GMP_RNDN);

    if (mpfr_equal_p(x,b)) break;

    mpfr_add(x,x,step,GMP_RNDU);
    if (mpfr_greater_p(x,b)) {
      mpfr_sub(x, x, step, GMP_RNDN);
      mpfr_sub(step, b, x, GMP_RNDN);
      mpfr_set(x,b,GMP_RNDN);
    }
    evaluate(y2,tree,x,prec);
  }

  mpfr_set(result,sum,GMP_RNDU);

  mpfr_clear(x); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(step);
  mpfr_clear(sum); mpfr_clear(temp); 
  return;
}
