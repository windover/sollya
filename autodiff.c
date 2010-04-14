/*

Copyright 2008-2010 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

and by

LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2)

Contributors S. Chevillard, M. Joldes, Ch. Lauter

sylvain.chevillard@ens-lyon.org
mioara.joldes@ens-lyon.fr
christoph.lauter@ens-lyon.org

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinity norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*/

#include "autodiff.h"
#include "general.h"
#include <stdlib.h>

/* The functions in AD manipulate arrays of size (n+1): [u0...un] */
/* Each array is supposed to represent a function u at a given    */
/* point x0. The value ui is a small mpfi_t such that             */
/*            u^(i)(x0)/i!  belongs to ui                         */


/* Apply Leibniz' formula: (uv)_p = sum(i=0..p, u_i * v_(p-i))    */
void multiplication_AD(mpfi_t *res, mpfi_t *f, mpfi_t *g, int n) {
  int i,j,p;
  mpfi_t temp;
  mp_prec_t prec;
  mpfi_t *temp_array;

  prec = getToolPrecision();
  mpfi_init2(temp, prec);

  temp_array = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
  for(p=0;p<=n;p++) mpfi_init2(temp_array[p], prec);

  for(p=0; p<=n; p++) {
    mpfi_set_ui(temp_array[p], 0);
    i=0; j=p; 
    while(i<=p) {
      mpfi_mul(temp, f[i], g[j]);
      mpfi_add(temp_array[p], temp_array[p], temp);
      i++; j--;
    }
  }

  for(p=0; p<=n; p++) {
    mpfi_set(res[p], temp_array[p]);
    mpfi_clear(temp_array[p]);
  }
  free(temp_array);
  mpfi_clear(temp);
  return;
}

/* Generic recursive algorithm for the successive derivation of (g o f)  */
/* The array [f0...fn] represents a function f at point x0               */
/* The array [g0...gn] represents a function g at point f(x0)            */
/* Algo:                                                                 */
/*    If n==0, return [g0]                                               */
/*    Else, (g o f)^(i+1) = ((g o f)')^(i) = (f' * (g' o f))^(i) = h^(i) */
/*      So (g o f)^(i+1) / (i+1)! = (1/(i+1)) * h^(i)/i!                 */
/*      So we compute the array [w0 ... w(n-1)] corresponding to         */
/*      (g' o f), up to order (n-1) (by a recursive call)                */
/*      We apply multiplication_AD to w and [(1*f1) ... (n*fn)]          */
/*      (we remark that [(1*f1) ... (n*fn)] corresponds to f')           */
/*      This leads to an array [h0...h(n-1)] corresponding to h          */
/*      Finally, we return [g0 (h0/1) ... (h(n-1)/n)]                    */
void composition_AD(mpfi_t *res, mpfi_t *g, mpfi_t *f, int n) {
  mpfi_t *fprime, *gprime;
  mpfi_t *temp_array;
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();
  if(n==0) mpfi_set(res[0], g[0]);
  else {
    temp_array = (mpfi_t *)safeCalloc(n,sizeof(mpfi_t));
    fprime = (mpfi_t *)safeCalloc(n,sizeof(mpfi_t));
    gprime = (mpfi_t *)safeCalloc(n,sizeof(mpfi_t));
    for(i=0;i<=n-1;i++) {
      mpfi_init2(temp_array[i], prec);
      mpfi_init2(fprime[i], prec);
      mpfi_init2(gprime[i], prec);

      mpfi_mul_ui(fprime[i], f[i+1], i+1);
      mpfi_mul_ui(gprime[i], g[i+1], i+1);
    }
    
    composition_AD(temp_array, gprime, f, n-1);
    multiplication_AD(res+1, temp_array, fprime, n-1);

    mpfi_set(res[0], g[0]);
    for(i=1; i<=n; i++) mpfi_div_ui(res[i], res[i], i);
    for(i=0; i<=n-1; i++) {
      mpfi_clear(temp_array[i]);
      mpfi_clear(fprime[i]);
      mpfi_clear(gprime[i]);
    }

    free(temp_array);
    free(fprime);
    free(gprime);
  }

  return ;
}


void binary_function_diff(mpfi_t *res, int nodeType, mpfi_t x0, node *f, node *g, int n) {
  int i;
  mpfi_t *res1, *res2, *temp_array;
  mpfr_t minusOne;
  mp_prec_t prec;

  prec = getToolPrecision();
  res1 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
  res2 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
  for(i=0;i<=n;i++) {
    mpfi_init2(res1[i], prec);
    mpfi_init2(res2[i], prec);
  }
  auto_diff_scaled(res1, f, x0, n);
  auto_diff_scaled(res2, g, x0, n);

  switch(nodeType) {
  case ADD: 
    for(i=0; i<=n; i++) mpfi_add(res[i], res1[i], res2[i]);
    break;
  case SUB:
    for(i=0; i<=n; i++) mpfi_sub(res[i], res1[i], res2[i]);
    break;
  case MUL:
    multiplication_AD(res, res1, res2, n);
    break;
  case DIV: /* We compute it by g/h = g * h^{-1} */
    temp_array = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
    for(i=0;i<=n;i++) mpfi_init2(temp_array[i], prec);

    /* temp_array corresponds to x->1/x at point h(x0) */
    mpfr_init2(minusOne, prec);  mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(temp_array, res2[0], minusOne, n);
    mpfr_clear(minusOne);

    /* temp_array corresponds to (x->1/x)(h) = 1/h */
    composition_AD(temp_array, temp_array, res2, n);

    /* res corresponds to g * 1/h */
    multiplication_AD(res, res1, temp_array, n);

    for(i=0;i<=n;i++) mpfi_clear(temp_array[i]);
    free(temp_array);
    break;

  default:
    fprintf(stderr, "Error in autodiff: unknown binary operator (%d)\n", nodeType);
    return;
  }
  
  for(i=0;i<=n;i++) {
    mpfi_clear(res1[i]);
    mpfi_clear(res2[i]);
  }
  free(res1);
  free(res2);
}


/* Computes the successive derivatives of y -> y^p at point x          */ 
/* [x^p/0!    p*x^(p-1)/1!   ...   p*(p-1)*...*(p-n+1)*x^(p-n)/n! ]    */
void constantPower_diff(mpfi_t *res, mpfi_t x, mpfr_t p, int n) {
  mpfi_t expo, acc;
  mp_prec_t prec_expo, prec;
  int i;
  
  prec = getToolPrecision();
  prec_expo = (prec > mpfr_get_prec(p))?prec:mpfr_get_prec(p);

  mpfi_init2(expo, prec_expo);
  mpfi_init2(acc, prec);
  
  mpfi_set_fr(expo, p);
  mpfi_set_ui(acc, 1);
  
  for(i=0; i<=n; i++) {
    if (mpfi_is_zero(acc)) mpfi_set_ui(res[i],0);
    else {
      mpfi_pow(res[i], x, expo);
      mpfi_mul(res[i], res[i], acc);
      
      mpfi_mul(acc, acc, expo);
      mpfi_div_ui(acc, acc, i+1);
      mpfi_sub_ui(expo, expo, 1);
    }
  }

  mpfi_clear(expo);
  mpfi_clear(acc);

  return;
}


/* the power function is: p^x, where p is a positive constant */
/* [p^x/0!, log(p)p^x/1!, ... , log(p)^n p^x / n! ] */
void powerFunction_diff(mpfi_t *res, mpfr_t p, mpfi_t x, int n) {
  int i;
  mpfi_t temp1,temp2;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(temp1, prec);
  mpfi_init2(temp2, prec);

  mpfi_set_fr(temp1,p);

  mpfi_pow(temp2, temp1, x); /* temp2 = p^x */
  mpfi_log(temp1,temp1); /* temp1 = log(p) */

  for(i=0;i<=n;i++) {
    mpfi_set(res[i], temp2);
    mpfi_mul(temp2,temp2,temp1);
    mpfi_div_ui(temp2, temp2, i+1);
  }

  mpfi_clear(temp1);
  mpfi_clear(temp2);
  return;
}

void exp_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(temp, prec);

  mpfi_exp(temp, x);
  for(i=0;i<=n;i++) {
    mpfi_set(res[i], temp);
    mpfi_div_ui(temp, temp, i+1);
  }

  mpfi_clear(temp);
  return;
}

void expm1_diff(mpfi_t *res, mpfi_t x, int n) {
  exp_diff(res, x, n);
  mpfi_sub_ui(res[0], res[0], 1);
  return;
}


void log_diff(mpfi_t *res, mpfi_t x, int n) {
  mpfr_t minusOne;
  mp_prec_t prec;
  int i;

  prec = getToolPrecision();

  mpfi_log(res[0], x);

  if(n>=1) {
    mpfr_init2(minusOne, prec);
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(res+1, x, minusOne, n-1);
    mpfr_clear(minusOne);
  }
  for(i=1;i<=n;i++) mpfi_div_ui(res[i], res[i], i);
  return;
}

void log1p_diff(mpfi_t *res, mpfi_t x, int n) {
  mpfr_t minusOne;
  mpfi_t u;
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();
  
  mpfi_log1p(res[0], x);

  if(n>=1) {
    mpfi_init2(u, prec);
    mpfi_add_ui(u, x, 1);
    mpfr_init2(minusOne, prec);
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(res+1, u, minusOne, n-1);
    mpfr_clear(minusOne);
    mpfi_clear(u);
  }

  for(i=1;i<=n;i++) mpfi_div_ui(res[i], res[i], i);

  return;
}

/* log2(x) = log(x) * (1/log(2)) */
void log2_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t log2;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(log2, prec);

  mpfi_set_ui(log2, 2); mpfi_log(log2, log2);
  log_diff(res,x,n);
  for(i=0;i<=n;i++) mpfi_div(res[i], res[i], log2);

  mpfi_clear(log2);
  return;
}

/* idem */
void log10_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t log10;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(log10, prec);

  mpfi_set_ui(log10, 10); mpfi_log(log10, log10);
  log_diff(res,x,n);
  for(i=0;i<=n;i++) mpfi_div(res[i], res[i], log10);

  mpfi_clear(log10);
  return;
}

void sin_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();

  mpfi_sin(res[0], x); 
  for(i=2; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
  for(i=2; i<=n; i +=4) mpfi_neg(res[i], res[i]);

  if(n>=1) {
    mpfi_cos(res[1], x); 
    for(i=3; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
    for(i=3; i<=n; i +=4) mpfi_neg(res[i], res[i]);
  }

  return;
}

void cos_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();

  mpfi_cos(res[0], x); 
  for(i=2; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
  for(i=2; i<=n; i +=4) mpfi_neg(res[i], res[i]);

  if(n>=1) {
    mpfi_sin(res[1], x); 
    for(i=3; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
    for(i=1; i<=n; i +=4) mpfi_neg(res[i], res[i]);
  }

  return;
}

void sinh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();

  mpfi_sinh(res[0], x); 
  for(i=2; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);

  if(n>=1) {
    mpfi_cosh(res[1], x); 
    for(i=3; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
  }

  return;
}

void cosh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mp_prec_t prec;

  prec = getToolPrecision();

  mpfi_cosh(res[0], x); 
  for(i=2; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);

  if(n>=1) {
    mpfi_sinh(res[1], x); 
    for(i=3; i<=n; i+=2) mpfi_div_ui(res[i], res[i-2], (i-1)*i);
  }

  return;
}


/* Takes a polynomial given by the array of its coefficients [p0...pn] 
   and differentiates it (returns the array of the derivative) */

/* It IS safe to use the same pointer for res and coeff_array */
/* (in-place computation) */
void symbolic_poly_diff(mpfi_t *res, mpfi_t *coeff_array, int degree) {
  int i;

  for(i=0;i<=degree-1;i++) mpfi_mul_ui(res[i], coeff_array[i+1], i+1);
}

/* Evaluates a symbolic polynomial at point x by Horner scheme */
void symbolic_poly_evaluation_horner(mpfi_t res, mpfi_t *coeffs_array, mpfi_t x, int degree) {
  int i;
  mpfi_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(temp, prec);

  mpfi_set(temp, coeffs_array[degree]);
  for(i=degree-1;i>=0;i--) {
    mpfi_mul(temp, temp, x);
    mpfi_add(temp, temp, coeffs_array[i]);
  }
  mpfi_set(res, temp);
  mpfi_clear(temp);
}

/* Evaluates a symbolic polynomial at point x by computing successive powers */
void symbolic_poly_evaluation_powers(mpfi_t res, mpfi_t *coeffs_array, mpfi_t *powers_array, mpfi_t x, int degree) {
  int i;
  mpfi_t temp, acc;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(temp, prec);
  mpfi_init2(acc, prec);

  mpfi_set_ui(acc, 0);
  for(i=0;i<=degree;i++) {
    mpfi_mul(temp, coeffs_array[i], powers_array[i]);
    mpfi_add(acc, acc, temp);
  }
  mpfi_set(res, acc);

  mpfi_clear(temp);
  mpfi_clear(acc);
}


/*  u=tan(x), tan^(n) / n! = p_(n)(u) with
    p_0 = u;

recurrence formula: p_(n+1)(u) = (p_n(u))' / (n+1) = p'_n(u) * (1+u^2) / (n+1)
   -> p_n of degree n+1
*/

void tan_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array;
  mpfi_t u;
  mp_prec_t prec;

  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( (n+2),sizeof(mpfi_t));

  for (index=0; index<=n+1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_set_ui(coeffs_array[index], 0);
  }
  mpfi_init2(u, prec);

  mpfi_tan(u, x);
  mpfi_set_ui(coeffs_array[0], 0);
  mpfi_set_ui(coeffs_array[1], 1);
  
  mpfi_set(res[0], u);

  for(index=1; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array, coeffs_array, index);
    mpfi_set_ui(coeffs_array[index], 0);
    /* now it represents p_(index-1)' */

    for(i=index+1; i>=2; i--) {
      mpfi_add(coeffs_array[i], coeffs_array[i], coeffs_array[i-2]);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, u, index+1);
  }
    
  for (index=0; index<=n+1; index++){
    mpfi_clear(coeffs_array[index]);
  }
  mpfi_clear(u);
  free(coeffs_array);
  
  return;
}

/*  u=tanh(x), tanh^(n) / n! = p_(n)(u) with
    p_0 = u;

recurrence formula: p_(n+1)(u) = (p_n(u))' / (n+1) = p'_n(u) * (1-u^2) / (n+1)
   -> p_n of degree n+1
*/

void tanh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array;
  mpfi_t u;
  mp_prec_t prec;

  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( (n+2),sizeof(mpfi_t));

  for (index=0; index<=n+1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_set_ui(coeffs_array[index], 0);
  }
  mpfi_init2(u, prec);

  mpfi_tanh(u, x);
  mpfi_set_ui(coeffs_array[0], 0);
  mpfi_set_ui(coeffs_array[1], 1);
  
  mpfi_set(res[0], u);

  for(index=1; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array, coeffs_array, index);
    mpfi_set_ui(coeffs_array[index], 0);
    /* now it represents p_(index-1)' */

    for(i=index+1; i>=2; i--) {
      mpfi_sub(coeffs_array[i], coeffs_array[i], coeffs_array[i-2]);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, u, index+1);
  }
    
  for (index=0; index<=n+1; index++){
    mpfi_clear(coeffs_array[index]);
  }
  mpfi_clear(u);
  free(coeffs_array);
  
  return;
}


/* atan_diff : reccurence formula: p_(n+1) = (p'_n * (1+x^2) - 2nx * p_n) / (n+1)
   atan^(0) = atan(x)
   atan^(n) / n! = p_(n)(x)/((1+x^2)^n)
   p_1=1;

   --> degree of p_n is (n-1)
*/
void atan_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_atan(res[0], x);

  if(n>=1) {
    mpfi_sqr(u, x);
    mpfi_add_ui(u, u, 1);

    mpfi_inv(res[1], u);

    mpfi_set_ui(coeffs_array[0], 1);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=2; i--) {
      mpfi_add(coeffs_array[i], coeffs_array_diff[i], coeffs_array_diff[i-2]);
      mpfi_mul_ui(temp, coeffs_array[i-1], 2*(index-1));
      mpfi_sub(coeffs_array[i], coeffs_array[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_mul_ui(temp, coeffs_array[0], 2*(index-1));
    mpfi_sub(coeffs_array[1], coeffs_array_diff[1], temp);
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);

    mpfi_set(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_set_ui(temp, index);
    mpfi_pow(temp, u, temp);
    mpfi_div(res[index], res[index], temp);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;
}


/* atanh_diff : reccurence formula: p_(n+1) = (p'_n * (1-x^2) + 2nx * p_n)/ (n+1)
   atanh^(0) = atanh(x)
   atanh^(n)/n! = p_(n)(x)/((1-x^2)^n)
   p_1=1;

   --> degree of p_n is (n-1)
*/
void atanh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_atanh(res[0], x);

  if(n>=1) {
    mpfi_sqr(u, x);
    mpfi_sub_ui(u, u, 1); /* TODO: FIX IT when MPFI is patched */
    mpfi_neg(u, u);

    mpfi_inv(res[1], u);

    mpfi_set_ui(coeffs_array[0], 1);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=2; i--) {
      mpfi_sub(coeffs_array[i], coeffs_array_diff[i], coeffs_array_diff[i-2]);
      mpfi_mul_ui(temp, coeffs_array[i-1], 2*(index-1));
      mpfi_add(coeffs_array[i], coeffs_array[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_mul_ui(temp, coeffs_array[0], 2*(index-1));
    mpfi_add(coeffs_array[1], coeffs_array_diff[1], temp);
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);

    mpfi_set(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_set_ui(temp, index);
    mpfi_pow(temp, u, temp);
    mpfi_div(res[index], res[index], temp);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;
}



/* asin_diff : recurrence formula: p_(n+1)= (p'_n * (1-x^2) + (2n-1)x * p_n)/(n+1)
   asin^(0) = asin(x)
   asin^(n) / n! = p_(n)(x) / (1-x^2)^((2n-1)/2)
   p_1=1;

   --> degree of p_n is (n-1)
*/
void asin_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_asin(res[0], x);

  if(n>=1) {
    mpfi_sqr(u, x);
    mpfi_sub_ui(u, u, 1); /* TODO: FIX IT when MPFI is patched */
    mpfi_neg(u, u);
    mpfi_sqrt(u, u);

    mpfi_inv(res[1], u);

    mpfi_set_ui(coeffs_array[0], 1);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=2; i--) {
      mpfi_sub(coeffs_array[i], coeffs_array_diff[i], coeffs_array_diff[i-2]);
      mpfi_mul_ui(temp, coeffs_array[i-1], 2*(index-1)-1);
      mpfi_add(coeffs_array[i], coeffs_array[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_mul_ui(temp, coeffs_array[0], 2*(index-1)-1);
    mpfi_add(coeffs_array[1], coeffs_array_diff[1], temp);
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);

    mpfi_set(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_set_ui(temp, 2*index-1);
    mpfi_pow(temp, u, temp);
    mpfi_div(res[index], res[index], temp);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;
}


/* acos_diff : except for the res[0], all the terms are equal to -asin^(n)(x)/n! */
void acos_diff(mpfi_t *res, mpfi_t x, int n) {
  int i; 

  asin_diff(res,x,n);

  mpfi_acos(res[0], x);

  for (i=1; i<=n;i++)  mpfi_neg(res[i], res[i]);

  return;
}


/* asinh_diff : recurrence formula: p_(n+1) = (p'_n * (1+x^2) - (2n-1)x * p_n) / (n+1) 
   asinh^(0) = asinh(x)
   asinh^(n)/n! = p_(n)(x) / (1+x^2)^((2n-1)/2)
   p_1=1;

   --> degree of p_n is (n-1)
*/
void asinh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_asinh(res[0], x);

  if(n>=1) {
    mpfi_sqr(u, x);
    mpfi_add_ui(u, u, 1);
    mpfi_sqrt(u, u);

    mpfi_inv(res[1], u);

    mpfi_set_ui(coeffs_array[0], 1);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=2; i--) {
      mpfi_add(coeffs_array[i], coeffs_array_diff[i], coeffs_array_diff[i-2]);
      mpfi_mul_ui(temp, coeffs_array[i-1], 2*(index-1)-1);
      mpfi_sub(coeffs_array[i], coeffs_array[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_mul_ui(temp, coeffs_array[0], 2*(index-1)-1);
    mpfi_sub(coeffs_array[1], coeffs_array_diff[1], temp);
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);

    mpfi_set(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_set_ui(temp, 2*index-1);
    mpfi_pow(temp, u, temp);
    mpfi_div(res[index], res[index], temp);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;
}


/* acosh_diff : recurrence formula: p_(n+1) = (p'_n * (x^2-1) - (2n-1)x * p_n) / (n+1)
   acosh^(0) = acosh(x)
   acosh^(n)/n! = p_(n)(x) / (x^2-1)^((2n-1)/2)
   p_1=1;

   --> degree of p_n is (n-1)
*/
void acosh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_acosh(res[0], x);

  if(n>=1) {
    mpfi_sqr(u, x);
    mpfi_sub_ui(u, u, 1);
    mpfi_sqrt(u, u);

    mpfi_inv(res[1], u);

    mpfi_set_ui(coeffs_array[0], 1);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=2; i--) {
      mpfi_sub(coeffs_array[i], coeffs_array_diff[i-2], coeffs_array_diff[i]);
      mpfi_mul_ui(temp, coeffs_array[i-1], 2*(index-1)-1);
      mpfi_sub(coeffs_array[i], coeffs_array[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_mul_ui(temp, coeffs_array[0], 2*(index-1)-1);
    mpfi_add(coeffs_array[1], temp, coeffs_array_diff[1]);
    mpfi_neg(coeffs_array[1], coeffs_array[1]);
    mpfi_div_ui(coeffs_array[1], coeffs_array[1], index);

    mpfi_neg(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_set_ui(temp, 2*index-1);
    mpfi_pow(temp, u, temp);
    mpfi_div(res[index], res[index], temp);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;
}

/* erf^(n)(x)/n! = p_n(x)*e^(-x^2)             */
/* with p_1(x) = 2/sqrt(pi)                    */
/* and p_(n+1)(x) = (p_n'(x) - 2xp_n(x))/(n+1) */
/*  -> degree of p_n is n-1                    */
void erf_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *coeffs_array_diff;
  mpfi_t u, temp;

  mp_prec_t prec;
    
  prec = getToolPrecision();
  coeffs_array = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));
  coeffs_array_diff = (mpfi_t *)safeCalloc( n,sizeof(mpfi_t));

  for (index=0; index<=n-1; index++) {
    mpfi_init2(coeffs_array[index], prec);
    mpfi_init2(coeffs_array_diff[index], prec);

    mpfi_set_ui(coeffs_array[index], 0);
    mpfi_set_ui(coeffs_array_diff[index], 0);
  }

  mpfi_init2(u, prec);
  mpfi_init2(temp, prec);

  mpfi_erf(res[0], x);

  if(n>=1) {
    mpfi_const_pi(temp);
    mpfi_sqrt(temp, temp);
    mpfi_ui_div(temp, 2, temp);

    mpfi_sqr(u, x);
    mpfi_neg(u, u);
    mpfi_exp(u, u);

    mpfi_mul(res[1], temp, u);

    mpfi_set(coeffs_array[0], temp);
  }

  for(index=2; index<=n; index++) {
    /* coeffs_array represents p_(index-1) */
    
    symbolic_poly_diff(coeffs_array_diff, coeffs_array, index-2);
    mpfi_set_ui(coeffs_array_diff[index-2], 0);
    /* now it represents p_(index-1)' */

    for(i=index-1; i>=1; i--) {
      mpfi_mul_ui(temp, coeffs_array[i-1], 2);
      mpfi_sub(coeffs_array[i], coeffs_array_diff[i], temp);
      mpfi_div_ui(coeffs_array[i], coeffs_array[i], index);
    }

    mpfi_set(coeffs_array[0], coeffs_array_diff[0]);
    mpfi_div_ui(coeffs_array[0], coeffs_array[0], index);
    /* now it represents p_(index) */

    symbolic_poly_evaluation_horner(res[index], coeffs_array, x, index-1);
    mpfi_mul(res[index], res[index], u);
  }
    
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(coeffs_array_diff[index]);
  }
  mpfi_clear(u);
  mpfi_clear(temp);
  free(coeffs_array);
  free(coeffs_array_diff);
  
  return;  
}

void erfc_diff(mpfi_t *res, mpfi_t x, int n) {
  int i; 

  erf_diff(res,x,n);

  mpfi_erfc(res[0], x);

  for (i=1; i<=n;i++)  mpfi_neg(res[i],res[i]);

  return;
}

void abs_diff(mpfi_t *res, mpfi_t x, int n) {
  int s, i;
  mpfi_t temp;
  mpfr_t temp2;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfi_init2(temp, prec);

  mpfi_abs(res[0], x);
  if(n >= 1) {
    if (mpfi_has_zero(x))  mpfi_interv_si(res[1], -1, 1);
    else mpfi_set_si(res[1], mpfi_is_pos(x) ? 1 : (-1));
  }

  if(n >= 2) {
    mpfr_init2(temp2, prec);
    mpfr_set_nan(temp2);

    printMessage(1, "Warning: the absolute value is not twice differentiable.\n");
    printMessage(1, "Will return [@NaN@, @NaN@].\n");
    for(i=2;i<=n;i++) mpfi_set_fr(res[i], temp2);
    mpfr_clear(temp2);
  }

  return;
}

void single_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the single rounding operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void double_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the double rounding operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void double_double_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the doubledouble rounding operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void triple_double_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the tripledouble rounding operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void double_extended_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the doubleextended rounding operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void ceil_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the ceil operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void floor_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the floor operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void nearestint_diff(mpfi_t *res, mpfi_t x, int n){
  int i;
  mpfr_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();
  mpfr_init2(temp, prec);
  mpfr_set_nan(temp);

  printMessage(1, "Warning: the nearestint operator is not differentiable.\n");
  printMessage(1, "Will return [@NaN@, @NaN@].\n");
  for(i=0;i<=n;i++) mpfi_set_fr(res[i], temp);
  mpfr_clear(temp);
}

void libraryFunction_diff(mpfi_t *res, node *f, mpfi_t x, int n) {
  mpfi_t fact;
  mp_prec_t prec;
  int i;

  prec = getToolPrecision();
  mpfi_init2(fact, prec);
  mpfi_set_ui(fact, 1);

  for(i=0;i<=n;i++) {
    f->libFun->code(res[i], x, f->libFunDeriv + i);
    mpfi_div(res[i], res[i], fact);
    mpfi_mul_ui(fact, fact, i+1);
  }
  mpfi_clear(fact);
}

void baseFunction_diff(mpfi_t *res, int nodeType, mpfi_t x, int n) {
  mpfr_t oneHalf;
  mp_prec_t prec;
  prec = getToolPrecision();

  int i;
  switch(nodeType) {
  case NEG: /* This case is useless since it is handled separately in auto_diff_scaled */
            /* However, since x->(-x) could be seen as a base function, and since      */
            /* baseFunction_diff could be used in another context, we implement it.    */
    mpfi_neg(res[0], x);
    if(n>=1) {
      mpfi_set_si(res[1], -1);
      for(i=2;i<=n;i++) mpfi_set_ui(res[i], 0);
    }
    break;
  case SQRT:
    mpfr_init2(oneHalf, prec);
    mpfr_set_d(oneHalf, 0.5, GMP_RNDN);
    constantPower_diff(res, x, oneHalf, n);
    mpfr_clear(oneHalf);
    break;
  case ERF:
    erf_diff(res, x, n);
    break;
  case ERFC:
    erfc_diff(res, x, n);
    break;
  case EXP:
    exp_diff(res, x, n);
    break;
  case EXP_M1:
    expm1_diff(res,x,n);
    break;
  case LOG_1P:
    log1p_diff(res, x, n);
    break;
  case LOG:
    log_diff(res,x,n);
    break;
  case LOG_2:
    log2_diff(res,x,n);
    break;
  case LOG_10:
    log10_diff(res,x,n);
    break;
  case SIN:
    sin_diff(res,x,n);
    break;
  case COS:
    cos_diff(res,x,n);
    break;
  case TAN:
    tan_diff(res,x,n);
    break;
  case ASIN:
    asin_diff(res,x,n);
    break;
  case ACOS:
    acos_diff(res,x,n);
    break;
  case ATAN:
     atan_diff(res,x,n);
    break;
  case SINH:
    sinh_diff(res,x,n);
    break;
  case COSH:
    cosh_diff(res,x,n);
    break;
  case TANH:
    tanh_diff(res,x,n);
    break;
  case ASINH:
    asinh_diff(res,x,n);
    break;
  case ACOSH:
    acosh_diff(res,x,n);
    break;
  case ATANH:
    atanh_diff(res,x,n);
    break;
  case ABS:
    abs_diff(res, x, n);
    break;
  case SINGLE:
    single_diff(res, x, n);
    break;
  case DOUBLE:
    double_diff(res, x, n);
    break;
  case DOUBLEDOUBLE:
    double_double_diff(res, x, n);
    break;
  case TRIPLEDOUBLE:
    triple_double_diff(res, x, n);
    break;
  case DOUBLEEXTENDED:
    double_extended_diff(res, x, n);
    break;
  case CEIL:
    ceil_diff(res, x, n);
    break;
  case FLOOR:
    floor_diff(res, x, n);
    break;
  case NEARESTINT:
    nearestint_diff(res, x, n);
    break;
  default:
    fprintf(stderr,"Error: AD: unknown unary function (%d) in the tree\n", nodeType);
  }

  return;
}


/* res is a reserved space for n+1 mpfi_t such that: */
/*               res_i = f^(i)(x0)/i!                */
/* We proceed recursively on the structure.          */
void auto_diff_scaled(mpfi_t* res, node *f, mpfi_t x0, int n) {
  int i;
  mpfi_t *res1, *res2;
  mpfr_t minusOne;
  node *simplifiedChild1, *simplifiedChild2, *tempTree;
  mpfi_t temp1, temp2;
  mp_prec_t prec;

  prec = getToolPrecision();
  switch (f->nodeType) {
  case VARIABLE:
    mpfi_set(res[0], x0);
    if(n>=1) {
      mpfi_set_ui(res[1], 1);
      for(i=2; i<=n; i++) mpfi_set_ui(res[i], 0);
    }
    break;

  case PI_CONST:
    mpfi_const_pi(res[0]);
    for(i=1; i<=n; i++) mpfi_set_ui(res[i], 0);
    break;

  case CONSTANT:
    mpfi_set_fr(res[0], *(f->value));
    for(i=1; i<=n; i++) mpfi_set_ui(res[i], 0);
    break;

  case NEG:
    auto_diff_scaled(res, f->child1, x0, n);
    for(i=0;i<=n;i++) mpfi_neg(res[i], res[i]);
    break;

  case ADD:
  case SUB:
  case MUL:
  case DIV:
    binary_function_diff(res, f->nodeType, x0, f->child1, f->child2, n);
    break;

  case SQRT:
  case EXP:
  case LOG:
  case LOG_2:
  case LOG_10:
  case SIN:
  case COS:
  case TAN:
  case ASIN:
  case ACOS:
  case ATAN:
  case SINH:
  case COSH:
  case TANH:
  case ASINH:
  case ACOSH:
  case ATANH:
  case ABS:
  case SINGLE:
  case DOUBLE:
  case DOUBLEEXTENDED:
  case DOUBLEDOUBLE:
  case TRIPLEDOUBLE:
  case ERF: 
  case ERFC:
  case LOG_1P:
  case EXP_M1:
  case CEIL:
  case FLOOR:
  case NEARESTINT:
  case LIBRARYFUNCTION:
    res1 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
    res2 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], prec);
      mpfi_init2(res2[i], prec);
    }

    auto_diff_scaled(res1, f->child1, x0, n);
    if(f->nodeType==LIBRARYFUNCTION) libraryFunction_diff(res2, f, res1[0], n);
    else baseFunction_diff(res2, f->nodeType, res1[0], n);
    composition_AD(res, res2, res1, n);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
    }
    free(res1);
    free(res2);
    break;

  case POW:    
    simplifiedChild2 = simplifyTreeErrorfree(f->child2);
    simplifiedChild1 = simplifyTreeErrorfree(f->child1);
    
    /* x^p case */
    if ( (simplifiedChild1->nodeType == VARIABLE) &&
	 (simplifiedChild2->nodeType == CONSTANT) ) {
      constantPower_diff(res, x0, *(simplifiedChild2->value), n);
    }

    /* p^x case */
    else if ( (simplifiedChild1->nodeType == CONSTANT) &&
	      (simplifiedChild2->nodeType == VARIABLE) ) {
      powerFunction_diff(res, *(simplifiedChild1->value), x0, n);
    }

    /* p^q case */
    else if ( (simplifiedChild1->nodeType == CONSTANT) &&
	      (simplifiedChild2->nodeType == CONSTANT) ) {
      mpfi_init2(temp1, prec);
      mpfi_set_fr(temp1, *(simplifiedChild1->value));
      mpfi_init2(temp2, prec);
      mpfi_set_fr(temp2, *(simplifiedChild2->value));
      mpfi_pow(res[0], temp1, temp2);
      for(i=1; i<=n; i++) mpfi_set_ui(res[i], 0);
      
      mpfi_clear(temp1);
      mpfi_clear(temp2);
    }
    
    /* p^f or f^p case */
    else if ( (simplifiedChild1->nodeType==CONSTANT) ||
	      (simplifiedChild2->nodeType==CONSTANT) ) {
      
      res1 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
      res2 = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
      for(i=0;i<=n;i++) {
	mpfi_init2(res1[i], prec);
	mpfi_init2(res2[i], prec);
      }
      
      if (simplifiedChild1->nodeType == CONSTANT) { /* p^f */
	auto_diff_scaled(res1, simplifiedChild2, x0, n);
	powerFunction_diff(res2, *(simplifiedChild1->value), res1[0], n);
      }
      else { /* f^p */
	auto_diff_scaled(res1, simplifiedChild1, x0, n);
	constantPower_diff(res2, res1[0], *(simplifiedChild2->value), n);
      }
      
      composition_AD(res, res2, res1, n); 
      
      for(i=0; i<=n; i++) {
	mpfi_clear(res1[i]);
	mpfi_clear(res2[i]); 
      }
      free(res1);
      free(res2);    
    } 

    /*  f^g case */
    /* f^g = exp(g*log(f)) */
    else {
      tempTree = makeExp(makeMul(copyTree(simplifiedChild2), makeLog(copyTree(simplifiedChild1))));
      auto_diff_scaled(res, tempTree, x0, n);
      free_memory(tempTree);
    }

    free_memory(simplifiedChild1);
    free_memory(simplifiedChild2);
    break;
    
  default:
   fprintf(stderr,"Error in autodiff: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }

  return;
}

/* res is a reserved space for n+1 mpfi_t such that: */
/*               res_i = f^(i)(x0)                   */
void auto_diff(mpfi_t* res, node *f, mpfi_t x0, int n) {
  int i;
  mpfi_t fact;
  mp_prec_t prec;

  prec = getToolPrecision();

  mpfi_init2(fact, prec);
  mpfi_set_ui(fact, 1);

  auto_diff_scaled(res, f, x0, n);
  for(i=1;i<=n;i++) {
    mpfi_mul_ui(fact, fact, i);
    mpfi_mul(res[i], res[i], fact);
  }
  
  mpfi_clear(fact);
}
