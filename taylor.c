#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taylor.h"
#include "expression.h"
#include "main.h"




node *taylor(node* tree, int degree, node* point, mp_prec_t prec) {
  node *copy, *temp, *temp2, *fderiv, *fderivsubst, *denominator, *numerator, *expon, *variable, *term;
  mpfr_t *value;
  mpz_t denominatorGMP;
  int i;


  value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*value,prec);
  mpfr_set_d(*value,0.0,GMP_RNDN);
  copy = (node *) safeMalloc(sizeof(node));
  copy->nodeType = CONSTANT;
  copy->value = value;

  mpz_init(denominatorGMP);
  fderiv = copyTree(tree);
  for (i=0;i<=degree;i++) {
    temp = substitute(fderiv,point);
    fderivsubst = simplifyTreeErrorfree(temp);
    free_memory(temp);
    mpz_fac_ui(denominatorGMP,(unsigned int) i);
    value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    if(mpfr_set_z(*value,denominatorGMP,GMP_RNDN) != 0) {
      printMessage(1,"Warning: rounding occured on computing a taylor constant factor.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    denominator = (node *) safeMalloc(sizeof(node));
    denominator->nodeType = CONSTANT;
    denominator->value = value;
    value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    mpfr_set_d(*value,1.0,GMP_RNDN);
    numerator = (node *) safeMalloc(sizeof(node));
    numerator->nodeType = CONSTANT;
    numerator->value = value;
    temp = (node *) safeMalloc(sizeof(node));
    temp->nodeType = DIV;
    temp->child1 = numerator;
    temp->child2 = denominator;
    temp2 = (node *) safeMalloc(sizeof(node));
    temp2->nodeType = MUL;
    temp2->child1 = temp;
    temp2->child2 = fderivsubst;
    variable = (node *) safeMalloc(sizeof(node));
    variable->nodeType = VARIABLE;
    value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    if(mpfr_set_si(*value,i,GMP_RNDN) != 0) {
      printMessage(1,"Warning: rounding occured on computing a taylor exponent.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    expon = (node *) safeMalloc(sizeof(node));
    expon->nodeType = CONSTANT;
    expon->value = value;
    temp = (node *) safeMalloc(sizeof(node));
    temp->nodeType = POW;
    temp->child1 = variable;
    temp->child2 = expon;
    term = (node *) safeMalloc(sizeof(node));
    term->nodeType = MUL;
    term->child1 = temp2;
    term->child2 = temp;
    temp = (node *) safeMalloc(sizeof(node));
    temp->nodeType = ADD;
    temp->child1 = copy;
    temp->child2 = term;
    copy = temp;
    temp = differentiate(fderiv);
    free_memory(fderiv);
    fderiv = temp;
  }
  mpz_clear(denominatorGMP);
  
  free_memory(fderiv);

  temp = horner(copy);
  free_memory(copy);
  return temp;
}
