#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taylor.h"
#include "expression.h"



node *substitute(node* tree, node *t) {
  node *copy;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = copyTree(t);
    break;
  case CONSTANT:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,mpfr_get_prec(*(tree->value)));
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SUB:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case MUL:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case DIV:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SQRT:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = substitute(tree->child1,t);
    break;
  case EXP:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_2:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_10:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SIN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TAN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASIN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATAN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SINH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COSH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TANH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASINH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOSH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATANH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case POW:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case NEG:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ABS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLE:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  default:
   fprintf(stderr,"substitute: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


node *taylor(node* tree, int degree, node* point, mp_prec_t prec) {
  node *copy, *temp, *temp2, *fderiv, *fderivsubst, *denominator, *numerator, *expon, *variable, *term;
  mpfr_t *value;
  mpz_t denominatorGMP;
  int i;


  value = (mpfr_t *) malloc(sizeof(mpfr_t));
  mpfr_init2(*value,prec);
  mpfr_set_d(*value,0.0,GMP_RNDN);
  copy = (node *) malloc(sizeof(node));
  copy->nodeType = CONSTANT;
  copy->value = value;

  mpz_init(denominatorGMP);
  fderiv = copyTree(tree);
  for (i=0;i<=degree;i++) {
    temp = substitute(fderiv,point);
    fderivsubst = simplifyTreeErrorfree(temp);
    free_memory(temp);
    mpz_fac_ui(denominatorGMP,(unsigned int) i);
    value = (mpfr_t *) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    if(mpfr_set_z(*value,denominatorGMP,GMP_RNDN) != 0) {
      printf("Warning: rounding occured on computing a taylor constant factor.\n");
      printf("Try to increase the working tools_precision.\n");
    }
    denominator = (node *) malloc(sizeof(node));
    denominator->nodeType = CONSTANT;
    denominator->value = value;
    value = (mpfr_t *) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    mpfr_set_d(*value,1.0,GMP_RNDN);
    numerator = (node *) malloc(sizeof(node));
    numerator->nodeType = CONSTANT;
    numerator->value = value;
    temp = (node *) malloc(sizeof(node));
    temp->nodeType = DIV;
    temp->child1 = numerator;
    temp->child2 = denominator;
    temp2 = (node *) malloc(sizeof(node));
    temp2->nodeType = MUL;
    temp2->child1 = temp;
    temp2->child2 = fderivsubst;
    variable = (node *) malloc(sizeof(node));
    variable->nodeType = VARIABLE;
    value = (mpfr_t *) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,prec);
    if(mpfr_set_si(*value,i,GMP_RNDN) != 0) {
      printf("Warning: rounding occured on computing a taylor exponent.\n");
      printf("Try to increase the working tools_precision.\n");
    }
    expon = (node *) malloc(sizeof(node));
    expon->nodeType = CONSTANT;
    expon->value = value;
    temp = (node *) malloc(sizeof(node));
    temp->nodeType = POW;
    temp->child1 = variable;
    temp->child2 = expon;
    term = (node *) malloc(sizeof(node));
    term->nodeType = MUL;
    term->child1 = temp2;
    term->child2 = temp;
    temp = (node *) malloc(sizeof(node));
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
