/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.fr
sylvain.chevillard@ens-lyon.fr
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinite norm, an automatic polynomial
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

#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include <mpfi.h>
#include "general.h"
#include "expression.h"
#include "chain.h"
#include "remez.h"
#include "fpminimax.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>



void continuedFrac(mpq_t q, mpfi_t x) {
  mpfi_t xprime;
  mpfr_t a,b;
  mpfr_t m1,m2;
  mp_prec_t t;
  mpq_t res;
  mpz_t u;

  t = mpfi_get_prec(x);
  mpfi_init2(xprime,t);
  mpfr_init2(a,t);
  mpfr_init2(b,t);
  mpfr_init2(m1,t);
  mpfr_init2(m2,t);
  mpq_init(res);
  mpz_init(u);

  mpfi_get_left(a,x);
  mpfi_get_right(b,x);
  mpfr_floor(m1,a);
  mpfr_floor(m2,b);

  if (mpfr_equal_p(m1,m2) && !mpfr_equal_p(a,m1)) {
    mpfr_get_z(u,m1,GMP_RNDN); //exact
    mpfr_sub(a,a,m1,GMP_RNDD);
    mpfr_sub(b,b,m1,GMP_RNDU);
    mpfi_interv_fr(xprime,a,b);
    mpfi_inv(xprime,xprime);
    continuedFrac(res,xprime);
    mpq_inv(res,res);
    mpq_set_num(q,u);
    mpz_set_ui(u,1);
    mpq_set_den(q,u);
    mpq_add(q,q,res);
  }
  else {
    mpfr_add(m1,a,b,GMP_RNDN);
    mpfr_div_2ui(m1,m1,1,GMP_RNDN);
    mpfr_get_z(u,m1,GMP_RNDN);
    mpq_set_num(q,u);
    mpz_set_ui(u,1);
    mpq_set_den(q,u);
  }
  
  mpfi_clear(xprime);
  mpfr_clear(a);
  mpfr_clear(b);
  mpfr_clear(m1);
  mpfr_clear(m2);
  mpq_clear(res);
  mpz_clear(u);
  return;
}

node *rationalApprox(mpfr_t x, unsigned int n) {
  mpq_t q;
  mpz_t u;
  mpfi_t xprime;
  node *tree;
  node *num;
  node *denom;
  mpfr_t *numerator;
  mpfr_t *denominator;

  mpq_init(q);
  mpz_init(u);
  mpfi_init2(xprime,(mp_prec_t)n);

  mpfi_set_fr(xprime,x);
  continuedFrac(q,xprime);
 
  mpq_get_num(u,q);
  numerator = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*numerator,mp_bits_per_limb*mpz_size(u));
  mpfr_set_z(*numerator,u,GMP_RNDN);

  mpq_get_den(u,q);
  denominator = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*denominator,mp_bits_per_limb*mpz_size(u));
  mpfr_set_z(*denominator,u,GMP_RNDN);

  tree = safeMalloc(sizeof(node));
  tree->nodeType = DIV;
  num = safeMalloc(sizeof(node));
  denom = safeMalloc(sizeof(node));
  num->nodeType = CONSTANT;
  denom->nodeType = CONSTANT;
  num->value = numerator;
  denom->value = denominator;
  tree->child1 = num;
  tree->child2 = denom;

  mpfi_clear(xprime);
  mpq_clear(q);
  mpz_clear(u);
  return tree;
}


void freeFormatTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((formatType *) ptr)->formatType == TI_FORMAT) {
    mpfr_clear(*(((formatType *) ptr)->tiValue));
    free(((formatType *) ptr)->tiValue);
  }
  free((formatType *) ptr);
}

void freeErrorTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((errorType *) ptr)->errorType == WEIGHTFUNCTION_ERROR) {
    free_memory(((errorType *) ptr)->weightFunction);
  }
  free((errorType *) ptr);
}

void freeMpfrPtr(void *ptr) {
  if (ptr == NULL) return;

  mpfr_clear(*((mpfr_t *) ptr));
  free((mpfr_t *) ptr);
}

void freePointsTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((pointsType *) ptr)->pointsType == USER_POINTS) {
    freeChain(((pointsType *) ptr)->pointsList,freeMpfrPtr);
  }
  free((errorType *) ptr);
}




void affiche_format(formatType *f) {
  switch (f->formatType) {
  case DOUBLE_FORMAT:
    printf("D ");
    break;
  case DOUBLEDOUBLE_FORMAT:
    printf("DD ");
    break;
  case TRIPLEDOUBLE_FORMAT:
    printf("TD ");
    break;
  case PRECISION_FORMAT:
    printf("%d ",f->prec);
    break;
  case MI_FORMAT:
    printf("%d ",f->prec);
    break;
  case TI_FORMAT:
    printValue(f->tiValue);
    printf(" ");
    break;
  default:
    printf("Urrglh ");
  }
}

node *createPoly(chain *monomials, chain *coefficients) {
  node *result;
  node *temp;
  chain *list1=monomials;
  chain *list2=coefficients;
  mpfr_t *a;
  mpfr_t *n;

  /* Handling improbable special cases to make C. Lauter happy */
  if(list1==NULL) {
    fprintf(stderr,"Error : if somebody can read that, I was wrong!\n");
    recoverFromError();
  }
  if(list2==NULL) {
    fprintf(stderr,"Error : if somebody can read that, I was wrong!\n");
    recoverFromError();
  }
  if(list1->next==NULL && list2->next!=NULL) {
    fprintf(stderr,"Error : if somebody can read that, I was wrong!\n");
    recoverFromError();
  }
  if(list2->next==NULL && list1->next!=NULL) {
    fprintf(stderr,"Error : if somebody can read that, I was wrong!\n");
    recoverFromError();
  }

  
  /* Now the interesting part */
  if(list1->next==NULL && list2->next==NULL) {
    result = safeMalloc(sizeof(node));
    result->nodeType=MUL;

    result->child1=safeMalloc(sizeof(node));
    result->child1->nodeType=CONSTANT;

    a = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*a, mpfr_get_prec(*(mpfr_t *)(list2->value)));
    mpfr_set(*a, *(mpfr_t *)(list2->value), GMP_RNDN); //exact
    result->child1->value=a;

    result->child2=safeMalloc(sizeof(node));
    result->child2->nodeType=POW;
    result->child2->child1=safeMalloc(sizeof(node));
    result->child2->child1->nodeType=VARIABLE;
    result->child2->child2=safeMalloc(sizeof(node));
    result->child2->child2->nodeType=CONSTANT;

    n = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*n, 53);
    mpfr_set_si(*n, *(int *)(list1->value), GMP_RNDN); //exact
    result->child2->child2->value=n;
  }
  else {
    result = safeMalloc(sizeof(node));
    result->nodeType=ADD;
    result->child2 = createPoly(list1->next, list2->next);

    result->child1 = safeMalloc(sizeof(node));
    temp = result->child1;
    temp->nodeType=MUL;

    temp->child1=safeMalloc(sizeof(node));
    temp->child1->nodeType=CONSTANT;

    a = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*a, mpfr_get_prec(*(mpfr_t *)(list2->value)));
    mpfr_set(*a, *(mpfr_t *)(list2->value), GMP_RNDN); //exact
    temp->child1->value=a;

    temp->child2=safeMalloc(sizeof(node));
    temp->child2->nodeType=POW;
    temp->child2->child1=safeMalloc(sizeof(node));
    temp->child2->child1->nodeType=VARIABLE;
    temp->child2->child2=safeMalloc(sizeof(node));
    temp->child2->child2->nodeType=CONSTANT;

    n = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*n, 53);
    mpfr_set_si(*n, *(int *)(list1->value), GMP_RNDN); //exact
    temp->child2->child2->value=n;
  }

  return result;
}
