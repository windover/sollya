/*

Copyright 2009-2010 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

and by

LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2)

Contributors S. Chevillard, M. Joldes

sylvain.chevillard@ens-lyon.fr
mioara.joldes@ens-lyon.fr

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


#include "taylorform.h"
#include "external.h"
#include "infnorm.h"
#include "autodiff.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>

  
/* This function creates an empty taylor model */
tModel* createEmptytModel(int n,  mpfi_t x0, mpfi_t x){
  tModel* t;
  mp_prec_t prec;
  int i;
  
  prec = getToolPrecision();
 
  t= (tModel *)safeMalloc(sizeof(tModel));
  mpfi_init2(t->rem_bound, prec);
  mpfi_init2(t->poly_bound, prec);
  mpfi_init2(t->x, prec);
  mpfi_set(t->x, x);
  mpfi_init2(t->x0, prec);
  mpfi_set(t->x0, x0);
  t->n = n;
  t->poly_array = (mpfi_t *)safeCalloc(n,sizeof(mpfi_t));
  for(i=0;i<n;i++){
    mpfi_init2(t->poly_array[i], prec);
  }

  return t;
}

/* This function dealocates a taylor model */
void cleartModel(tModel *t){
  int i;
  for(i=0;i<t->n;i++) mpfi_clear(t->poly_array[i]);
  free(t->poly_array);
  mpfi_clear(t->rem_bound);
  mpfi_clear(t->poly_bound);  
  mpfi_clear(t->x);
  mpfi_clear(t->x0);
  free(t);
}

/* This function pretty prints a taylor model */
void printtModel(tModel *t){
  int i;
  sollyaPrintf("\nTaylor model of order, %d expanded in ", t->n);
  printInterval(t->x0);
  sollyaPrintf("over ");
  printInterval(t->x);
  sollyaPrintf("\nCoeffs:");
  for(i=0;i<t->n;i++) {
    printInterval(t->poly_array[i]);
    if (i<(t->n)-1) sollyaPrintf(", ");
  } 
  sollyaPrintf("\nremainder = ");
  printInterval(t->rem_bound);
  sollyaPrintf(",\nbound = ");
  printInterval(t->poly_bound);  
  sollyaPrintf("\n");  
}


/* The convention for all the following functions is:
the tmodel given as parameter has to be created previously 
*/

/* This function sets the taylor model t with constant ct */
void consttModel(tModel*t, mpfi_t ct){ 
  int i,n;
  n=t->n;
  
  for(i=1;i<n;i++){
     mpfi_set_ui(t->poly_array[i], 0);
  }
  
  mpfi_set(t->poly_array[0], ct);
  mpfi_set(t->poly_bound, ct);
  mpfi_set_ui(t->rem_bound, 0); 
}



/* Check that models are compatible one with another: i.e. they can be added, mulitplied, copied, etc. */
int tModelsAreCompatible(tModel *t1, tModel *t2) {
    return ((t1 != NULL) && (t2 != NULL) && 
            (mpfi_equal_p(t1->x, t2->x) || (mpfi_nan_p(t1->x) && mpfi_nan_p(t2->x))) &&
            (mpfi_equal_p(t1->x0, t2->x0) || (mpfi_nan_p(t1->x0) && mpfi_nan_p(t2->x0))) &&
            (t1->n == t2->n));
}

/* This function returns a copy of the taylor model tt */
void copytModel(tModel *t, tModel *tt){
  int i;

  if (!tModelsAreCompatible(t, tt)) {
    sollyaFprintf(stderr, "Error in taylorform: trying to copy incompatible models.\n");
    sollyaFprintf(stderr, "No modification is made.\n");
    return;
  }

  for(i=0;i<tt->n;i++) {
    mpfi_set(t->poly_array[i], tt->poly_array[i]);
  }  
  mpfi_set(t->rem_bound, tt->rem_bound);
  mpfi_set(t->poly_bound, tt->poly_bound);  
  
  return;
}


/* Bound p(x-x0) over I, where p is a polynomial of degree n, given by the list of its coefficients */
void boundTranslatedPolynomialByHorner(mpfi_t bound, int n, mpfi_t *coeffs, mpfi_t x0, mpfi_t I){
  mpfi_t temp;
  mp_prec_t prec;
  prec = getToolPrecision();
  mpfi_init2(temp, prec);
  mpfi_sub(temp, I, x0);
  symbolic_poly_evaluation_horner(bound, coeffs, temp, n);
  mpfi_clear(temp);
}


/* This function computes an interval bound for a polynomial  */
/* Maybe, it will be smarter than just Horner, one day        */
/* For testing purpose, is is possible to plug an uncertified */
/* polynomialBound function instead of Horner here            */
void polynomialBoundSharp(mpfi_t *bound, int n, mpfi_t *coeffs, mpfi_t x0, mpfi_t I){
 boundTranslatedPolynomialByHorner(*bound,n,coeffs,x0,I);
}


/* This function transforms a polynomial with interval coeffs
into a poly with mpfr coeffs and a small remainder
Parameters:
-- input: n  - degree of poly
         p - array of given coeffs
         x0 - expansion point
         x  - interval
-- output: rc - mpfr coeffs
           errors - errors around the coeffs rc
           rest - remainder  
*/
void mpfr_get_poly(mpfr_t *rc, mpfi_t *errors_array, mpfi_t rest, int n, mpfi_t *p, mpfi_t x0, mpfi_t x){
  int i;
  mpfi_t *errors;
  mpfi_t temp;
  mp_prec_t prec;

  prec = getToolPrecision();

  errors = (mpfi_t *)safeCalloc((n+1),sizeof(mpfi_t));
  for (i=0; i<=n; i++) mpfi_init2(errors[i], prec);

  mpfi_init2(temp, prec);

  for (i=0; i<=n; i++){
    mpfi_mid(rc[i], p[i]);
    mpfi_sub_fr(errors[i], p[i], rc[i]);
    if (errors_array != NULL) mpfi_set(errors_array[i], errors[i]);
  }
  mpfi_sub(temp, x, x0);
  symbolic_poly_evaluation_horner(rest, p, temp, n);
  
  for (i=0; i<=n; i++)  mpfi_clear(errors[i]);  
  free(errors);
  mpfi_clear(temp);

  return;
}


void multiplication_TM(tModel *t, tModel *t1, tModel *t2, int mode){
  /* We will multiply two taylor models of order n; and obtain a new taylor model of order n */
  int n,i,j;
  mpfi_t *r; /* used to store the least significant coeffs of the product */
  tModel *tt;
  mpfi_t temp1, temp2;
  mpfi_t bound1, bound2, bound3;
  mp_prec_t prec;

  prec = getToolPrecision();

  if ( (!tModelsAreCompatible(t1, t2)) || (!tModelsAreCompatible(t, t1)) ) {
    sollyaFprintf(stderr, "Error in taylorform: trying to multiply incompatible models.\n");
    sollyaFprintf(stderr, "No modification is made.\n");
    return;
  }

  n = t->n;
  
  /* aux tm for doing the multiplications */
  tt = createEmptytModel(n, t->x0, t->x);
  for(i=0; i<=n-1; i++){
    mpfi_set_ui(tt->poly_array[i], 0);
  }
  
  mpfi_init2(temp1, prec);
  mpfi_init2(temp2, prec);
  mpfi_init2(bound1, prec);
  mpfi_init2(bound2, prec);
  mpfi_init2(bound3, prec);

  /* bound1 <- delta2*B(T1) + delta1*B(T2) */
  mpfi_mul(temp1, t1->poly_bound, t2->rem_bound);
  mpfi_mul(temp2, t1->rem_bound, t2->poly_bound);
  mpfi_add(bound1, temp1, temp2);


  /**************************************************************************************/
  /*                    Compute the product of the two polynomials                      */
  /*                                                                                    */
  /* The product has degree 2n-2: the first n coefficients are stored in tt->poly_array */
  /* and the (n-1) remaining coefficients are stored in r.                              */
  /* When mode = ABSOLUTE, r = [0, 0 ...., 0, r0, ..., r(n-2)]                          */
  /*              it represents the polynomial T1*T2|[n....2n-2]                        */
  /* When mode = RELATIVE, r = [r0, ..., r(n-2), 0, 0, ....]                            */
  /*              it represents the polynomial T1*T2|[n....2n-2] / (x-x0)^n             */
  /**************************************************************************************/
  r = (mpfi_t *)safeCalloc((2*n-1),sizeof(mpfi_t));
  for(i=0; i < 2*n-1; i++){
    mpfi_init2(r[i], prec);
    mpfi_set_ui(r[i],0);
  }
   
  for(i=0; i<n; i++) {
    for (j=0; j<n; j++){
      mpfi_mul(temp1, t1->poly_array[i], t2->poly_array[j]);
      if ( (i+j) < n )
	mpfi_add(tt->poly_array[i+j], tt->poly_array[i+j], temp1);
      else
	if (mode==RELATIVE) mpfi_add(r[i+j-n], r[i+j-n], temp1);
	else mpfi_add(r[i+j], r[i+j], temp1);
    }
  }

  /* bound2 <- B(T1*T2|[n....2n-2]) or B(T1*T2|[n....2n-2]/(x-x0)^n) depending on the mode */
  if (mode == RELATIVE) polynomialBoundSharp(&bound2, n-2, r, t->x0, t->x);
  else polynomialBoundSharp(&bound2, 2*n-2, r, t->x0, t->x);

  /* bound3 <- delta1*delta2*B((x-x0)^n) or delta1*delta2 depending on the mode */
  mpfi_mul(bound3, t1->rem_bound, t2->rem_bound);
  if (mode == RELATIVE) {
    mpfi_sub(temp1,t->x,t->x0);
    mpfi_set_ui(temp2, n);
    mpfi_pow(temp1, temp1, temp2);
    mpfi_mul(bound3, bound3, temp1);
  }

  /* We are multiplying taylor models:
    *considering the RELATIVE error
         We are given:  (T1,delta1*(x-x0)^n
                        (T2,delta2*(x-x0)^n
               
         The product is:
      (T1*T2|[0...n-1], {delta1*B(T2)+delta2*B(T1)+delta1*delta2*B((x-x0)^n)+B(T1*T2|[n...2*n-2]/(x-x0)^n)}  *(x-x0)^n 

    *considering the ABSOLUTE error
         We are given:  (T1,delta1)
                        (T2,delta2)
               
         The product is: (T1*T2|[0...n-1], {delta1*B(T2)+delta2*B(T1)+delta1*delta2+B(T1*T2|[n...2*n-2])} */
 
  mpfi_add(tt->rem_bound, bound1, bound2); 
  mpfi_add(tt->rem_bound, tt->rem_bound, bound3); /* now the remainder bound is completely computed */
   
  /* we compute the new polynomial bound for the new model */
  polynomialBoundSharp(&temp1, n-1,tt->poly_array,t->x0,t->x);   
  mpfi_set(tt->poly_bound,temp1);
     
  for(i=0;i<2*n-1;i++)  mpfi_clear(r[i]);
  free(r); 
  
  mpfi_clear(temp1);
  mpfi_clear(temp2);
  mpfi_clear(bound1);
  mpfi_clear(bound2);
  mpfi_clear(bound3);

  copytModel(t,tt);
  cleartModel(tt);
  return;
}


/* This function computes the tm for addition of two given tm's 
The addition of two taylor models is the same, regardless the mode, 
absolute or relative - We put the parameter just to have some coherence
with the other functions
*/
void addition_TM(tModel *t,tModel *t1, tModel *t2, int mode){
  int i;
  int n;
  tModel *tt;

  if ( (!tModelsAreCompatible(t1, t2)) || (!tModelsAreCompatible(t, t1)) ) {
    sollyaFprintf(stderr, "Error in taylorform: trying to multiply incompatible models.\n");
    sollyaFprintf(stderr, "No modification is made.\n");
    return;
  }

  n=t->n;
  tt=createEmptytModel(n,t->x0,t->x);
  for(i=0;i<n;i++)  
    mpfi_add(tt->poly_array[i], t1->poly_array[i], t2->poly_array[i]);
  
  mpfi_add(tt->rem_bound, t1->rem_bound, t2->rem_bound);
  polynomialBoundSharp(&tt->poly_bound, n-1, tt->poly_array, t->x0, t->x);   
  copytModel(t,tt);
  cleartModel(tt);
  return;
}



/* This function computes the tm for multiplication by a constant */
void ctMultiplication_TM(tModel*d, tModel*s, mpfi_t c,int mode){
  int i;
  int n;
  tModel *tt;

  n=s->n;
  tt=createEmptytModel(n, s->x0, s->x);
  
  for(i=0; i<n; i++)  mpfi_mul(tt->poly_array[i], s->poly_array[i], c);
  mpfi_mul(tt->rem_bound, s->rem_bound, c);
  mpfi_mul(tt->poly_bound, s->poly_bound, c);

  copytModel(d,tt);
  cleartModel(tt);
}

#define MONOTONE_REMAINDER_BASE_FUNCTION 0
#define MONOTONE_REMAINDER_LIBRARY_FUNCTION 1
#define MONOTONE_REMAINDER_INV 2
#define MONOTONE_REMAINDER_CONSTPOWERVAR 3
#define MONOTONE_REMAINDER_VARCONSTPOWER 4
#define MONOTONE_REMAINDER_PROCEDURE_FUNCTION 5

/* This function computes a taylor remainder for a function on an interval, assuming
   the n-th derivative is monotone.
   typeOfFunction is used to separate the cases:
   * MONOTONE_REMAINDER_BASE_FUNCTION --> we consider a base function, represented by its nodeType (p and f are useless)
   * MONOTONE_REMAINDER_LIBRARY_FUNCTION --> we consider a base function, represented by its nodeType (p and nodeType are useless)
   * MONOTONE_REMAINDER_PROCEDURE_FUNCTION --> we consider a base function, represented by its nodeType (p and nodeType are useless)
   * MONOTONE_REMAINDER_INV  --> we consider (x -> 1/x) (nodeType, f, and p are useless)
   * MONOTONE_REMAINDER_CONSTPOWERVAR --> we consider (x -> p^x) (nodeType and f are useless)
   * MONOTONE_REMAINDER_VARCONSTPOWER --> we consider (x -> x^p) (nodeType and f are useless)

   The coeffs of the series
   expansion are given as an array of mpfi's, developed over x, in x0.
   For more details, see Lemmas 5.11 and following from Roland Zumkeller's thesis.
*/

/* FIXME: maybe boundx0 can be safely replaced by [0] */
void computeMonotoneRemainder(mpfi_t *bound, int typeOfFunction, int nodeType, node *f, mpfr_t p,
                              int n, mpfi_t *poly_array, mpfi_t x0, mpfi_t x, int *silent){
  mpfi_t xinf, xsup;
  mpfr_t xinfFr, xsupFr;
  mpfi_t bound1, bound2, boundx0, boundf1, boundf2, boundfx0;
  mpfi_t p_interv;
  mp_prec_t prec;

  prec = getToolPrecision();
  
  mpfi_init2(xinf, prec);  mpfi_init2(xsup, prec);
  mpfr_init2(xinfFr, prec);   mpfr_init2(xsupFr, prec);
  mpfi_init2(bound1, prec);  mpfi_init2(bound2, prec);  mpfi_init2(boundx0, prec);  
  mpfi_init2(boundf1, prec);  mpfi_init2(boundf2, prec); mpfi_init2(boundfx0, prec); 
  mpfi_init2(p_interv, prec);

  mpfi_get_left(xinfFr,x);  mpfi_get_right(xsupFr,x); 
  mpfi_set_fr(xinf, xinfFr);  mpfi_set_fr(xsup, xsupFr);  
  
  polynomialBoundSharp(&bound1, n-1, poly_array, x0, xinf); /* enclosure of p(xinf-x0) */
  polynomialBoundSharp(&bound2, n-1, poly_array, x0, xsup); /* enclosure of p(xsup-x0) */
  if (((n-1)%2)!=0)  polynomialBoundSharp(&boundx0, n-1, poly_array, x0, x0); /* enclosure of p(x0-x0) */


  /* enclosure of f(xinf) and f(xsup) */
  switch(typeOfFunction) {
  case MONOTONE_REMAINDER_BASE_FUNCTION:
    baseFunction_diff(&boundf1,nodeType,xinf,0, silent);
    baseFunction_diff(&boundf2,nodeType,xsup,0, silent);
    if (((n-1)%2)!=0)   baseFunction_diff(&boundfx0,nodeType,x0,0, silent);
    break;
  case MONOTONE_REMAINDER_LIBRARY_FUNCTION:
    libraryFunction_diff(&boundf1, f, xinf, 0, silent);
    libraryFunction_diff(&boundf2, f, xsup, 0, silent);
    if (((n-1)%2)!=0) libraryFunction_diff(&boundfx0, f, x0, 0, silent);
    break;
  case MONOTONE_REMAINDER_PROCEDURE_FUNCTION:
    procedureFunction_diff(&boundf1, f, xinf, 0, silent);
    procedureFunction_diff(&boundf2, f, xsup, 0, silent);
    if (((n-1)%2)!=0) procedureFunction_diff(&boundfx0, f, x0, 0, silent);
    break;
  case MONOTONE_REMAINDER_INV:
    mpfi_inv(boundf1, xinf);
    mpfi_inv(boundf2, xsup);
    if (((n-1)%2)!=0)   mpfi_inv(boundfx0, x0);
    break;
  case MONOTONE_REMAINDER_CONSTPOWERVAR:
    mpfi_set_fr(p_interv, p);
    mpfi_pow(boundf1, xinf, p_interv);
    mpfi_pow(boundf2, xsup, p_interv);
    if (((n-1)%2)!=0)  mpfi_pow(boundfx0, x0, p_interv);
    break;
  case MONOTONE_REMAINDER_VARCONSTPOWER:
    mpfi_set_fr(p_interv,p);
    mpfi_pow(boundf1, p_interv, xinf);
    mpfi_pow(boundf2, p_interv, xsup);
    if (((n-1)%2)!=0)  mpfi_pow(boundfx0, p_interv, x0);
    break;
  default:
    sollyaFprintf(stderr, "Error in taylorform: unkown type of function used with Zumkeller's technique\n");
    return;
  }
  
  
  mpfi_sub(bound1,boundf1,bound1);                          /* enclosure of f(xinf)-p(xinf-x0) */
  mpfi_sub(bound2,boundf2,bound2);                          /* enclosure of f(xsup)-p(xsup-x0) */

  /* in the case when n-1 is even, the remainder is 
     bounded by the values it takes on the two extremas of the interval */
  mpfi_union(*bound, bound1, bound2);
  
  /* in the case when n-1 is odd, the remainder is 
     in the convex hull determined by the two extremas and the value in x0 (which is 0, theoretically,
     but since x0 is a small interval... */
  if (((n-1)%2)!=0){
    mpfi_union(*bound,*bound,boundx0);
  }
  
  mpfr_clear(xinfFr); mpfr_clear(xsupFr);
  mpfi_clear(xinf); mpfi_clear(xsup);
  mpfi_clear(bound1); mpfi_clear(bound2); mpfi_clear(boundx0);  
  mpfi_clear(boundf1);  mpfi_clear(boundf2); mpfi_clear(boundfx0);
  mpfi_clear(p_interv);
  return;
}


/* This function computes a taylor model for a function, with the same convention
   as with computeMonotoneRemainder */
void base_TMAux(tModel *t, int typeOfFunction, int nodeType, node *f, mpfr_t p, int n, mpfi_t x0, mpfi_t x, int mode, int *silent){
  int i;
  tModel *tt;
  mpfi_t *nDeriv, *nDeriv2;
  mpfi_t temp, pow;
  mpfr_t minusOne;
  mp_prec_t prec;

  prec = getToolPrecision();
  tt = createEmptytModel(n,x0,x);

  /* We use AD for computing bound on the derivatives up to (n+1)th derivative */
  nDeriv= (mpfi_t *)safeCalloc((n+2),sizeof(mpfi_t));
  for(i=0;i<=n+1;i++) mpfi_init2(nDeriv[i], prec);

  switch(typeOfFunction) {
  case MONOTONE_REMAINDER_BASE_FUNCTION:
    baseFunction_diff(tt->poly_array,nodeType,x0, n-1, silent);
    baseFunction_diff(nDeriv, nodeType, x, n+1, silent);
    break;
  case MONOTONE_REMAINDER_LIBRARY_FUNCTION:
    libraryFunction_diff(tt->poly_array, f, x0, n-1, silent);
    libraryFunction_diff(nDeriv, f, x, n+1, silent);
    break;
  case MONOTONE_REMAINDER_PROCEDURE_FUNCTION:
    procedureFunction_diff(tt->poly_array, f, x0, n-1, silent);
    procedureFunction_diff(nDeriv, f, x, n+1, silent);
    break;
  case MONOTONE_REMAINDER_INV: 
    mpfr_init2(minusOne, prec);
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(tt->poly_array, x0, minusOne, n-1, silent);
    constantPower_diff(nDeriv, x, minusOne, n+1, silent);
    mpfr_clear(minusOne);
    break;
  case MONOTONE_REMAINDER_CONSTPOWERVAR:
    constantPower_diff(tt->poly_array, x0, p, n-1, silent);
    constantPower_diff(nDeriv, x, p, n+1, silent);
    break;
  case MONOTONE_REMAINDER_VARCONSTPOWER:
    powerFunction_diff(tt->poly_array, p, x0, n-1, silent);
    powerFunction_diff(nDeriv, p, x, n+1, silent);
    break;
  default: 
    sollyaFprintf(stderr, "Error in taylorform: unkown type of function used with Zumkeller's technique\n");
    return;
  }
  
  /* Use Zumkeller technique to improve the bound in the absolute case,
     when the (n+1)th derivative has constant sign */
  if((mode==ABSOLUTE)&&((mpfi_is_nonpos(nDeriv[n+1]) > 0)||(mpfi_is_nonneg(nDeriv[n+1]) > 0))){ 
    computeMonotoneRemainder(&tt->rem_bound, typeOfFunction, nodeType, f, p, n, tt->poly_array, x0,x, silent);
  }
  else{
    /* just keep the bound obtained using AD */
    mpfi_set(tt->rem_bound, nDeriv[n]);
  
    /* if we are in the case of the absolute error,
      we have to multiply by (x-x0)^n */
    
    if (mode==ABSOLUTE) {
      mpfi_init2(pow, prec);
      mpfi_set_ui(pow, n);
      mpfi_init2(temp, prec);
      mpfi_sub(temp,x,x0);
      mpfi_pow(temp, temp, pow);
      
      mpfi_mul(tt->rem_bound,tt->rem_bound,temp);
      
      mpfi_clear(pow);
      mpfi_clear(temp);
    }
  }
  
  /* bound the polynomial obtained */
  polynomialBoundSharp(&tt->poly_bound, n-1,tt->poly_array,t->x0,t->x);   
  
  copytModel(t,tt);
  cleartModel(tt);
  
  for(i=0;i<=n+1;i++)  mpfi_clear(nDeriv[i]);
  free(nDeriv);  
}

/* composition: g o f
   VERY IMPORTANT ASSUMPTIONS:
   We are given a taylor model for the function f in x0, over x, order n
   and a taylor model for basic function g in y0 over y, order n with:
       f->poly_array[0] \subseteq y0
       range(f->poly)+ f->rem_bound \subseteq y

   Note that these assumptions ARE NOT CHECKED inside the function.
   If these assumptions are true, it returns a valid taylor model for g(f(x)) in x0 over x. */
void composition_TM(tModel *t,tModel *g, tModel *f, int mode){
  int i;
  int n;
  tModel *tt, *partial_tmul,*tinterm,*tmul ;
  mp_prec_t prec;
  mpfi_t temp;

  prec = getToolPrecision();
  n=f->n;
  
  /* create a taylor model equal to the model of f, but the constant coeff, which is zero */
  tmul = createEmptytModel(n, f->x0, f->x);
  copytModel(tmul,f);
  mpfi_set_ui(tmul->poly_array[0],0);
  
  /* partial_tmul is used to represent the successive powers of tmul */
  partial_tmul=createEmptytModel(n,f->x0,f->x);
  copytModel(partial_tmul, tmul);  
  
  /* initialize a temporary model */
  tinterm = createEmptytModel(n, f->x0, f->x);

  /* Constructs the model to be returned */
  tt=createEmptytModel(n, f->x0, f->x);

  consttModel(tt, g->poly_array[0]);
  for(i=1; i<n; i++){
    ctMultiplication_TM(tinterm, partial_tmul, g->poly_array[i], mode); 
    addition_TM(tt, tt, tinterm, mode);
    multiplication_TM(partial_tmul, partial_tmul, tmul, mode);
  }
  
  /* Now, partial_tmul represents tmul^n */ 
  if (mode==RELATIVE) {
    mpfi_init2(temp, prec);
    mpfi_mul(temp, partial_tmul->rem_bound, g->rem_bound);
    mpfi_add(tt->rem_bound, tt->rem_bound, temp);
    mpfi_clear(temp);
  }
  else  mpfi_add(tt->rem_bound,tt->rem_bound,g->rem_bound);
  
  polynomialBoundSharp(&tt->poly_bound, n-1, tt->poly_array, tt->x0, tt->x);   
  copytModel(t,tt);

  cleartModel(tt);
  cleartModel(partial_tmul);
  cleartModel(tmul);
  cleartModel(tinterm);
}


/* This function computes a tm of order n from a given tm of higher order */
void reduceOrder_TM(tModel*d, tModel*s, int n){
  int i;
  int oldn;
  mpfi_t *remTerms;
  tModel *tt;
  mpfi_t pow;
  mpfi_t temp, temp2;
  mp_prec_t prec;

  oldn=s->n;
  prec = getToolPrecision();

  if (n>oldn) {
    sollyaFprintf(stderr, "Error: taylorform: trying to increase the order of a TM\n");
    return;
  }
  
  tt=createEmptytModel(n,s->x0,s->x);
  for(i=0;i<n;i++) mpfi_set(tt->poly_array[i], s->poly_array[i]);

  /* we are left with terms from n up to oldn-1 */
  remTerms= (mpfi_t *)safeCalloc((oldn-n),sizeof(mpfi_t));
  for(i=n;i<oldn;i++){
    mpfi_init2(remTerms[i-n], prec);
    mpfi_set(remTerms[i-n], s->poly_array[i]);
  }
    
  mpfi_init2(temp, prec);  
  polynomialBoundSharp(&temp, oldn-n-1, remTerms, tt->x0, tt->x);     
      
  polynomialBoundSharp(&tt->poly_bound, n-1,tt->poly_array,tt->x0,tt->x);     
  
  mpfi_init2(pow, prec);  
  mpfi_init2(temp2, prec);  
  mpfi_set_ui(pow,oldn-n);
  mpfi_sub(temp2,tt->x,tt->x0);
  mpfi_pow(temp2,temp2,pow);
  
  mpfi_mul(temp2,temp2,s->rem_bound);
  mpfi_add(tt->rem_bound,temp2,temp);
  
  copytModel(d,tt);
  cleartModel(tt);
  mpfi_clear(temp);
  mpfi_clear(temp2);
  mpfi_clear(pow);
  for(i=0;i<oldn-n;i++){
     mpfi_clear(remTerms[i]);
  }
  free(remTerms);
  
}

/*This function removes coeffs s_0...s_l from a tm s,
returns a tm of order n-l-1*/
void removeCoeffs_TM(tModel*d,tModel*s, int l){
  int i;
  int oldn,newn;
   
  tModel *tt;
    
  //we know that s_0,...,s_l are 0;
  //we create a tm of order oldOrder - (l+1)
  oldn=s->n;
  newn=oldn-l-1;
  tt=createEmptytModel(newn,s->x0,s->x);
  
  for (i=l+1;i<oldn;i++){
    mpfi_set(tt->poly_array[i-l-1],s->poly_array[i]);
  }
  
  //remainder: it is the same, since this remove coeffs is equivalent to a formal simplification
  //by (x-x0)^(oldn-newn)
  //Delta * (x-x0)^oldn --> Delta*(x-x0)^newn 
  
  mpfi_set(tt->rem_bound,s->rem_bound);
    
  polynomialBoundSharp(&tt->poly_bound, newn-1,tt->poly_array,tt->x0,tt->x);     
  
  copytModel(d,tt);
  cleartModel(tt);
  
}



void taylor_model(tModel *t, node *f, int n, mpfi_t x0, mpfi_t x, int mode) {
  int i;
  
  node *simplifiedChild1, *simplifiedChild2;
  mpfi_t temp1,temp2;
  node **coefficients;
  mpfi_t *rpoly, *boundRpoly;
  tModel *tt,*tPoly, *child1_tm, *child2_tm, *ctPowVar_tm, *varCtPower_tm, *logx_tm, *expx_tm, *logf_tm;
  
  /*used by division*/
  mpfi_t gx0,rangeg;
  tModel *ttt, *inv_tm, *child1Extended_tm, *child2Extended_tm, *child1RemoveCoeffs_tm,*child2RemoveCoeffs_tm; 
  int orderUpperBound;  
  int d;
  int silent = 0;
  mpfi_t powx,powy;
  mpfi_t ct, minusOne;
  mpfr_t zero;
  /*used by base functions*/
  mpfi_t fx0,rangef,pow;
  
  switch (f->nodeType) {
  
  case VARIABLE:
  
  tt=createEmptytModel(n,x0,x); 
  mpfi_set(tt->poly_array[0],x0);
  if (n==1){
    if (mode==RELATIVE){
      mpfi_set_ui(tt->rem_bound,1);
      mpfi_set(tt->poly_bound,x0);
    }
    else{ /*absolute*/
      mpfi_sub(tt->rem_bound,x,x0);
      mpfi_set(tt->poly_bound,x0);
    }
  }
  else{
    mpfi_set_ui(tt->rem_bound,0);
    mpfi_set_ui(tt->poly_array[1],1);
    for (i=2;i<n;i++){
      mpfi_set_ui(tt->poly_array[i],0);
    }
    mpfi_set(tt->poly_bound,x);
  }
  copytModel(t,tt);
  cleartModel(tt);
  break;
  
  case PI_CONST:
  case CONSTANT:
  
  mpfi_init2(ct, getToolPrecision());
  tt=createEmptytModel(n,x0,x); 
  if (f->nodeType == PI_CONST) mpfi_const_pi(ct);
  else mpfi_set_fr(ct, *(f->value));

  consttModel(tt,ct);
  mpfi_set_ui(tt->rem_bound,0);
  mpfi_set(tt->poly_bound,ct);
  copytModel(t,tt);
  cleartModel(tt);
  mpfi_clear(ct);
  break;
  
  case NEG:
  
    tt=createEmptytModel(n,x0,x);
    //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, x0, x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1,n,x0,x,mode);
    //do the necessary chages from child to parent
    for(i=0;i<n;i++) 
    mpfi_neg(tt->poly_array[i], child1_tm->poly_array[i]);
    
    mpfi_neg(tt->rem_bound,child1_tm->rem_bound);
    mpfi_neg(tt->poly_bound,child1_tm->poly_bound);
    copytModel(t,tt);
    //clear old taylor models
    cleartModel(child1_tm);
    cleartModel(tt);
    break;

  case ADD:
  
  //create a new empty taylor model the children
    tt=createEmptytModel(n,x0,x); 
    child1_tm=createEmptytModel(n, x0,x);
    child2_tm=createEmptytModel(n, x0,x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1,n,x0,x,mode);
    taylor_model(child2_tm, f->child2,n,x0,x,mode);
    
    addition_TM(tt,child1_tm, child2_tm,mode);
    copytModel(t,tt);
    //clear old taylor model
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    cleartModel(tt);
    break;

  case SUB:
    
    tt=createEmptytModel(n,x0,x); 
    //create a new empty taylor model the children
    child1_tm=createEmptytModel(n, x0,x);
    child2_tm=createEmptytModel(n, x0,x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1,n,x0,x,mode);
    taylor_model(child2_tm, f->child2,n,x0,x,mode);
    
    //do the necessary chages from children to parent
    mpfi_init2(minusOne,getToolPrecision());
    mpfi_set_si(minusOne,-1);
    ctMultiplication_TM(child2_tm,child2_tm, minusOne,mode);
    addition_TM(tt,child1_tm, child2_tm,mode);
      
    copytModel(t,tt);
    
    //clear old taylor model
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    cleartModel(tt);
    mpfi_clear(minusOne);
    break;

  case MUL:
     tt=createEmptytModel(n,x0,x); 
   //create a new empty taylor model the children
    child1_tm=createEmptytModel(n,x0,x);
    child2_tm=createEmptytModel(n, x0,x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1,n,x0,x,mode);
    taylor_model(child2_tm, f->child2,n,x0,x,mode);
    
    //do the necessary chages from children to parent
    multiplication_TM(tt,child1_tm, child2_tm,mode);
    copytModel(t,tt);
    //clear old taylor model
    cleartModel(child1_tm);
    cleartModel(child2_tm);     
    cleartModel(tt);
    break;

  case DIV:
  
  //child1 * inverse(child2)
  tt=createEmptytModel(n,x0,x); 
    
  //check whether g(x0)is zero
  mpfi_init2(gx0, getToolPrecision());
  evaluateInterval(gx0,f->child2, NULL, x0)  ;
  
  ttt=createEmptytModel(n,x0,x); 
   

    if ((mpfi_is_zero(gx0))&& (mode==RELATIVE)){
  
      orderUpperBound=10;
      //create a new empty taylor model the child
      child1Extended_tm=createEmptytModel(n+orderUpperBound,x0,x);
      child2Extended_tm=createEmptytModel(n+orderUpperBound,x0,x);
      
      //call taylor_model for the children
      taylor_model(child1Extended_tm, f->child1,n+orderUpperBound,x0,x,mode);
      taylor_model(child2Extended_tm, f->child2,n+orderUpperBound,x0,x,mode);
      
      //reduce order taylor model
      int l;
      l=0;
      while((mpfi_is_zero(child1Extended_tm->poly_array[l])) && (mpfi_is_zero(child2Extended_tm->poly_array[l]))){
      l++;}
    
      //printf("The order of the zero is: %d",l);
      //remove coeffs that are 0
      child1RemoveCoeffs_tm=createEmptytModel(n+orderUpperBound-l,x0,x);
      child2RemoveCoeffs_tm=createEmptytModel(n+orderUpperBound-l,x0,x);
       
      removeCoeffs_TM(child1RemoveCoeffs_tm, child1Extended_tm, l-1);
      removeCoeffs_TM(child2RemoveCoeffs_tm, child2Extended_tm, l-1);
       
      child1_tm=createEmptytModel(n,x0,x);
      child2_tm=createEmptytModel(n,x0,x);
      reduceOrder_TM(child1_tm,child1RemoveCoeffs_tm,n);
      reduceOrder_TM(child2_tm,child2RemoveCoeffs_tm,n);
      /*printf("\nThe reduced tm are:\n");
      printtModel(child1_tm);
      printtModel(child2_tm);
      */
    
      cleartModel(child1RemoveCoeffs_tm);
      cleartModel(child2RemoveCoeffs_tm);
    
      cleartModel(child1Extended_tm);
      cleartModel(child2Extended_tm);
        
    }//we have reduced the poles, we have taylor models of order n, we apply the basic division
    else{//just create tms or order n directly
      //create a new empty taylor model the child
      child1_tm=createEmptytModel(n,x0,x);
      child2_tm=createEmptytModel(n,x0,x);
      //call taylor_model for the children
      taylor_model(child1_tm, f->child1,n,x0,x,mode);
      taylor_model(child2_tm, f->child2,n,x0,x,mode);
    }
    mpfi_set(gx0,child2_tm->poly_array[0]);
    mpfi_init2(rangeg, getToolPrecision());
    
    
    mpfi_init2(powx, getToolPrecision());
    mpfi_set_ui(powx,n);
    
    if (mode==RELATIVE){
      mpfi_sub(rangeg, child2_tm->x,child2_tm->x0);
      mpfi_pow(rangeg,rangeg,powx);
      mpfi_mul(rangeg,rangeg,child2_tm->rem_bound);
      mpfi_add(rangeg,rangeg, child2_tm->poly_bound);
    }
    else {
    mpfi_add(rangeg,child2_tm->rem_bound,child2_tm->poly_bound);
    }  
      inv_tm=createEmptytModel(n,gx0,rangeg);
    
      base_TMAux(inv_tm, MONOTONE_REMAINDER_INV, 0, NULL, NULL, n, gx0, rangeg,mode,&silent);
    composition_TM(ttt,inv_tm,child2_tm,mode);
    
    multiplication_TM(tt, ttt, child1_tm,mode);
    //clear old children
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    cleartModel(inv_tm);
    cleartModel(ttt);
    copytModel(t,tt);
    cleartModel(tt);
    mpfi_clear(rangeg);
    mpfi_clear(powx);
    
    mpfi_clear(gx0);
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
  case DOUBLEDOUBLE:
  case TRIPLEDOUBLE:
  case ERF: 
  case ERFC:
  case LOG_1P:
  case EXP_M1:  
  case DOUBLEEXTENDED:
  case CEIL:
  case FLOOR: 
  case NEARESTINT: 
  case LIBRARYFUNCTION:
  case PROCEDUREFUNCTION:
    tt=createEmptytModel(n,x0,x); 
   //create a new empty taylor model the child
    child1_tm=createEmptytModel(n,x0,x);

    //call taylor_model on the child
    taylor_model(child1_tm, f->child1,n,x0,x,mode);
    //compute tm for the basic case
    
        
    mpfi_init2(fx0,getToolPrecision());
    mpfi_init2(rangef, getToolPrecision());
    
    mpfi_init2(pow, getToolPrecision());
    mpfi_set_ui(pow,n);
    
    evaluateInterval(fx0, f->child1, NULL, x0);
    if (mode==RELATIVE){
      mpfi_sub(rangef, x,x0);
      mpfi_pow(rangef,rangef,pow);
      mpfi_mul(rangef,rangef,child1_tm->rem_bound);
      mpfi_add(rangef,rangef, child1_tm->poly_bound);
    }
    else{
      mpfi_add(rangef,child1_tm->rem_bound, child1_tm->poly_bound);
    }

    child2_tm=createEmptytModel(n,fx0,rangef);

    if (f->nodeType == LIBRARYFUNCTION)
      base_TMAux(child2_tm, MONOTONE_REMAINDER_LIBRARY_FUNCTION, 0, f, NULL, n, fx0, rangef,mode,&silent);
    else if (f->nodeType == PROCEDUREFUNCTION)
      base_TMAux(child2_tm, MONOTONE_REMAINDER_PROCEDURE_FUNCTION, 0, f, NULL, n, fx0, rangef,mode,&silent);
    else
      base_TMAux(child2_tm, MONOTONE_REMAINDER_BASE_FUNCTION, f->nodeType, NULL, NULL, n, fx0, rangef,mode,&silent);
    composition_TM(tt,child2_tm, child1_tm,mode);
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    copytModel(t,tt);
    cleartModel(tt);
    mpfi_clear(fx0);    
    mpfi_clear(rangef);    
    mpfi_clear(pow);
        
  break;
  case POW:
  
  //create the result taylorModel
  tt=createEmptytModel(n,x0,x); 
  
      simplifiedChild2=simplifyTreeErrorfree(f->child2);
      simplifiedChild1=simplifyTreeErrorfree(f->child1);
      
      if ((simplifiedChild2->nodeType==CONSTANT) &&(simplifiedChild1->nodeType==CONSTANT)) { //we have the ct1^ct2 case
         // printf("We are in the  ct1^ct2 case");       
         mpfi_init2(temp1, getToolPrecision());
         mpfi_set_fr(temp1, *(simplifiedChild1->value));
         mpfi_init2(temp2, getToolPrecision());
         mpfi_set_fr(temp2, *(simplifiedChild2->value));
         mpfi_pow(temp1,temp1,temp2);
         consttModel(tt,temp1);
         copytModel(t,tt);
         cleartModel(tt);
         mpfi_clear(temp1);
         mpfi_clear(temp2);
      }
      else if (simplifiedChild2->nodeType==CONSTANT) { //we have the f^p case
        //printf("We are in the  f^p case");        
        //mpfi_t powx,fx0,rangef;        
        //create a new empty taylor model the child
        child1_tm=createEmptytModel(n,x0,x);
        //call taylor_model for the child
        taylor_model(child1_tm, f->child1,n,x0,x,mode);
        //printf("\n\n-----------taylormodel child1: \n");
        //printtModel(child1_tm);
        //printf("-----------------------------\n");
        mpfi_init2(fx0,getToolPrecision());
        evaluateInterval(fx0, f->child1, NULL, x0);
        
        mpfi_init2(rangef, getToolPrecision());
        mpfi_init2(powx, getToolPrecision());
        mpfi_set_ui(powx,n);
        if (mode==RELATIVE){
          mpfi_sub(rangef, child1_tm->x,child1_tm->x0);
          mpfi_pow(rangef,rangef,powx);
          mpfi_mul(rangef,rangef,child1_tm->rem_bound);
          mpfi_add(rangef,rangef, child1_tm->poly_bound);
        }
        else{
          mpfi_add(rangef,child1_tm->rem_bound, child1_tm->poly_bound);
        }
        //create tm for x^p over ragef in fx0
        ctPowVar_tm=createEmptytModel(n,fx0,rangef);
        
        base_TMAux(ctPowVar_tm, MONOTONE_REMAINDER_CONSTPOWERVAR, 0, NULL, *(simplifiedChild2->value), n, fx0,rangef,mode,&silent);
        
        //printf("\n\n-----------taylormodel child1: \n");
        //printtModel(ctPowVar_tm);
        //printf("-----------------------------\n");
        
        
        composition_TM(tt,ctPowVar_tm,child1_tm,mode);
    
        //clear old child
        cleartModel(child1_tm);
        cleartModel(ctPowVar_tm);
        copytModel(t,tt);
        cleartModel(tt);
        mpfi_clear(rangef);
        mpfi_clear(powx);
        mpfi_clear(fx0);
      } 
       else if (simplifiedChild1->nodeType==CONSTANT) { //we have the p^f case
        
        //mpfi_t powx,fx0,rangef;        
        //create a new empty taylor model the child
        child2_tm=createEmptytModel(n,x0,x);
        //call taylor_model for the child
        taylor_model(child2_tm, f->child2,n,x0,x,mode);
        
        mpfi_init2(fx0,getToolPrecision());
        evaluateInterval(fx0, f->child2, NULL, x0);
        
        mpfi_init2(rangef, getToolPrecision());
        mpfi_init2(powx, getToolPrecision());
        mpfi_set_ui(powx,n);
        
        if (mode==RELATIVE){
          mpfi_sub(rangef, child2_tm->x,child2_tm->x0);
          mpfi_pow(rangef,rangef,powx);
          mpfi_mul(rangef,rangef,child2_tm->rem_bound);
          mpfi_add(rangef,rangef, child2_tm->poly_bound);
        }
        else{
          mpfi_add(rangef,child2_tm->rem_bound, child2_tm->poly_bound);
        }
        //create tm for p^x over ragef in fx0
        varCtPower_tm=createEmptytModel(n,fx0,rangef);
        
        base_TMAux(varCtPower_tm, MONOTONE_REMAINDER_VARCONSTPOWER, 0, NULL, *(simplifiedChild1->value), n, fx0,rangef,mode,&silent );
        composition_TM(tt,varCtPower_tm,child2_tm,mode);
    
        //clear old child
        cleartModel(child2_tm);
        cleartModel(varCtPower_tm);
        copytModel(t,tt);
        cleartModel(tt);
        mpfi_clear(rangef);
        mpfi_clear(powx);
        mpfi_clear(fx0);
        }
      else {
      //printf("We are in the  f^g case");  
      //exp(g log(f))
      //  mpfi_t powx,fx0,rangef;        
        //create a new empty taylor model the children
        child1_tm=createEmptytModel(n,x0,x);
        child2_tm=createEmptytModel(n,x0,x);
        //call taylor_model for child 2 = g
        taylor_model(child2_tm, f->child2,n,x0,x,mode);
        
        //call taylor_model for child 1 = f
        taylor_model(child1_tm, f->child1,n,x0,x,mode);
        
        //create  taylor_model for log (child 1) = log(f)
                
        mpfi_init2(fx0,getToolPrecision());
        evaluateInterval(fx0, f->child1, NULL, x0);
        
        mpfi_init2(rangef, getToolPrecision());
        mpfi_init2(powx, getToolPrecision());
        mpfi_set_ui(powx,n);
        
        if (mode==RELATIVE){
          mpfi_sub(rangef, child1_tm->x,child1_tm->x0);
          mpfi_pow(rangef,rangef,powx);
          mpfi_mul(rangef,rangef,child1_tm->rem_bound);
          mpfi_add(rangef,rangef, child1_tm->poly_bound);
        }
        else{
          mpfi_add(rangef,child1_tm->rem_bound, child1_tm->poly_bound);
        }
        
        logx_tm=createEmptytModel(n,fx0,rangef);
        base_TMAux(logx_tm, MONOTONE_REMAINDER_BASE_FUNCTION, LOG, NULL, NULL, n, fx0, rangef,mode, &silent);
        logf_tm=createEmptytModel(n,x0,x);
        composition_TM(logf_tm,logx_tm,child1_tm,mode);
        //-------------------------------------------
        
        
        //multiply g by log f
        ttt=createEmptytModel(n,x0,x);
        multiplication_TM(ttt,logf_tm,child2_tm,mode);
        
        //------------------------------------------
        mpfi_init2(gx0,getToolPrecision());
        evaluateInterval(gx0, f->child2, NULL, x0);
        mpfi_log(fx0,fx0);
        mpfi_mul(gx0,gx0,fx0);
        
        mpfi_set_ui(powx,n);
        if (mode==RELATIVE){
          mpfi_sub(rangef, ttt->x,ttt->x0);
          mpfi_pow(rangef,rangef,powx);
          mpfi_mul(rangef,rangef,ttt->rem_bound);
          mpfi_add(rangef,rangef, ttt->poly_bound);
        }
        else{
          mpfi_add(rangef,ttt->rem_bound, ttt->poly_bound);
        }    
        expx_tm=createEmptytModel(n,gx0,rangef);
        base_TMAux(expx_tm, MONOTONE_REMAINDER_BASE_FUNCTION, EXP, NULL, NULL, n, gx0, rangef, mode, &silent);
        composition_TM(tt,expx_tm,ttt,mode);
               
    
        //clear old child
        cleartModel(child2_tm);
        cleartModel(child1_tm);
        cleartModel(ttt);
        cleartModel(expx_tm);
        cleartModel(logx_tm);
        cleartModel(logf_tm);
        
        copytModel(t,tt);
        cleartModel(tt);
        mpfi_clear(rangef);
        mpfi_clear(powx);
        mpfi_clear(fx0);   
        mpfi_clear(gx0); 
        
    }
    free_memory(simplifiedChild2);
    free_memory(simplifiedChild1);
    break;
    
  default:
   sollyaFprintf(stderr,"Error: TM: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
//  }
}
  return;
}
chain *constructChain(mpfi_t *err, int n){
  chain *l;
  mpfi_t *elem;
  int i;
  
  l = NULL;
  for(i=n;i>=0;i--){
    elem= (mpfi_t*)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*elem,getToolPrecision());
    mpfi_set(*elem,err[i]);
    l=addElement(l, elem);
  }
  return l;
}
void printMpfiChain(chain *c) {
  chain *curr=c;
  sollyaPrintf("[");
  while(curr!=NULL) {
    printInterval( *(mpfi_t *)(curr->value));
    curr=curr->next;
  }
  sollyaPrintf("]\n");
  return;
}


void taylorform(node **T, chain **errors, mpfi_t **delta,
		node *f, int n,	mpfi_t *x0, mpfi_t *d, int mode) {
  tModel *t;
  mpfi_t x0Int;
  mpfr_t *coeffsMpfr;
  mpfi_t *coeffsErrors;
  int i;
  node *z;
  chain *err;
  mpfi_t *rest;
  mpfi_t temp;
  mpfi_t pow;
  mpfi_t myD;

  /* Adjust n to the notion of degree in the taylor command */
  n++;

  /* Check if degree is at least 1, once it has been adjusted */
  if (n < 1) {
    printMessage(1,"Warning: the degree of a Taylor Model must be at least 0.\n");
    *T = NULL;
    return;
  } 

  if (d != NULL) {
    mpfi_init2(myD,mpfi_get_prec(*d));
    mpfi_set(myD,*d);
  } else {
    mpfi_init2(myD,mpfi_get_prec(*x0));
    mpfi_set(myD,*x0);
  }

  mpfi_init2(x0Int,getToolPrecision());
  mpfi_set(x0Int,*x0);
  t=createEmptytModel(n,x0Int,myD);
  //printf("we have created an emptytm");  

  taylor_model(t,f,n,x0Int,myD, mode);


  //printtModel(t);

  coeffsMpfr= (mpfr_t *)safeCalloc((n),sizeof(mpfr_t));
  coeffsErrors = (mpfi_t *)safeCalloc((n),sizeof(mpfi_t));

  rest= (mpfi_t*)safeMalloc(sizeof(mpfi_t));
  mpfi_init2(*rest,getToolPrecision());

  for(i=0;i<n;i++){
    mpfi_init2(coeffsErrors[i],getToolPrecision());
    mpfr_init2(coeffsMpfr[i],getToolPrecision());
  }

  mpfr_get_poly(coeffsMpfr, coeffsErrors, *rest, t->n -1,t->poly_array, t->x0,t->x);
 
  //create T; 
  *T=makePolynomial(coeffsMpfr, (t->n)-1);

  //create errors;
  err=constructChain(coeffsErrors,t->n-1);

  //printMpfiChain(err);
  *errors = err;
  /*
    if (mode == ABSOLUTE) {
    mpfi_init2(pow, getToolPrecision());
    mpfi_set_si(pow, t->n);
    mpfi_init2(temp,getToolPrecision());
    mpfi_sub(temp, t->x, t->x0);
    mpfi_pow(temp, temp,pow);
    mpfi_mul(*rest,temp, t->rem_bound);
    mpfi_clear(pow);
    mpfi_clear(temp);
    } else {
  
    mpfi_set(*rest,t->rem_bound);
    
    }
  */

  if (d != NULL) {
    mpfi_set(*rest,t->rem_bound);  
    *delta=rest;
  } else {
    mpfi_clear(*rest);
    free(rest);
  }
    
  for(i=0;i<n;i++){
    mpfr_clear(coeffsMpfr[i]);
    mpfi_clear(coeffsErrors[i]);
  }
  free(coeffsMpfr);
  free(coeffsErrors);
  mpfi_clear(x0Int);
  cleartModel(t);

  mpfi_clear(myD);
}
