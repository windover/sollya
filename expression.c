#include <mpfr.h>
#include "expression.h"
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>
#include "main.h"




void free_memory(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    free(tree);
    break;
  case CONSTANT:
    mpfr_clear(*(tree->value));
    free(tree->value);
    free(tree);
    break;
  case ADD:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case SUB:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case MUL:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case DIV:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case SQRT:
    free_memory(tree->child1);
    free(tree);
    break;
  case EXP:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG2:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG10:
    free_memory(tree->child1);
    free(tree);
    break;
  case SIN:
    free_memory(tree->child1);
    free(tree);
    break;
  case COS:
    free_memory(tree->child1);
    free(tree);
    break;
  case TAN:
    free_memory(tree->child1);
    free(tree);
    break;
  case ASIN:
    free_memory(tree->child1);
    free(tree);
    break;
  case ACOS:
    free_memory(tree->child1);
    free(tree);
    break;
  case ATAN:
    free_memory(tree->child1);
    free(tree);
    break;
  case SINH:
    free_memory(tree->child1);
    free(tree);
    break;
  case COSH:
    free_memory(tree->child1);
    free(tree);
    break;
  case TANH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ASINH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ACOSH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ATANH:
    free_memory(tree->child1);
    free(tree);
    break;
  case POW:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case NEG:
    free_memory(tree->child1);
    free(tree);
    break;
  case ABS:
    free_memory(tree->child1);
    free(tree);
    break;
  default:
   fprintf(stderr,"free_memory: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}


int isInfix(node *tree) {
  switch(tree->nodeType) {
  case ADD:
  case SUB:
  case MUL:
  case DIV:
  case POW:
    return 1;
    break;
  default: return 0;
  }
}


void printValue(mpfr_t *value, mp_prec_t prec) {
  mpfr_t y;
  char *str;
  mp_exp_t e;
  double v;
  int t;

  mpfr_init2(y,prec);
  v = mpfr_get_d(*value,GMP_RNDN);
  t = (int) v;
  v = (double) t;
  mpfr_set_d(y,v,GMP_RNDN);
  if (mpfr_cmp(y,*value) == 0) {
    printf("%d",t);
  } else { 
    mpfr_set(y,*value,GMP_RNDN);
    if (mpfr_sgn(y) < 0) {
      printf("-"); mpfr_neg(y,y,GMP_RNDN);
    }
    str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
    printf("0.%sE%d",str,(int)e);
    mpfr_free_str(str);      
  }
  mpfr_clear(y);
}


void printTree(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    printf("%s",variablename);
    break;
  case CONSTANT:
    printValue(tree->value,precision);
    break;
  case ADD:
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    printf(" + ");
    if (isInfix(tree->child2)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2)) 
      printf(")");
    break;
  case SUB:
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    printf(" - ");
    if (isInfix(tree->child2)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2)) 
      printf(")");
    break;
  case MUL:
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    printf(" * ");
    if (isInfix(tree->child2)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2)) 
      printf(")");
    break;
  case DIV:
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    printf(" / ");
    if (isInfix(tree->child2)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2)) 
      printf(")");
    break;
  case SQRT:
    printf("sqrt(");
    printTree(tree->child1);
    printf(")");
    break;
  case EXP:
    printf("exp(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG:
    printf("log(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG2:
    printf("log2(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG10:
    printf("log10(");
    printTree(tree->child1);
    printf(")");
    break;
  case SIN:
    printf("sin(");
    printTree(tree->child1);
    printf(")");
    break;
  case COS:
    printf("cos(");
    printTree(tree->child1);
    printf(")");
    break;
  case TAN:
    printf("tan(");
    printTree(tree->child1);
    printf(")");
    break;
  case ASIN:
    printf("asin(");
    printTree(tree->child1);
    printf(")");
    break;
  case ACOS:
    printf("acos(");
    printTree(tree->child1);
    printf(")");
    break;
  case ATAN:
    printf("atan(");
    printTree(tree->child1);
    printf(")");
    break;
  case SINH:
    printf("sinh(");
    printTree(tree->child1);
    printf(")");
    break;
  case COSH:
    printf("cosh(");
    printTree(tree->child1);
    printf(")");
    break;
  case TANH:
    printf("tanh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ASINH:
    printf("asinh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ACOSH:
    printf("acosh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ATANH:
    printf("atanh(");
    printTree(tree->child1);
    printf(")");
    break;
  case POW:
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    printf("^(");
    printTree(tree->child2);
    printf(")");
    break;
  case NEG:
    printf("-");
    printTree(tree->child1);
    break;
  case ABS:
    printf("abs(");
    printTree(tree->child1);
    printf(")");
    break;
  default:
   fprintf(stderr,"printTree: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}


node* copyTree(node *tree) {
  node *copy;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SUB:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case MUL:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case DIV:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SQRT:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = copyTree(tree->child1);
    break;
  case EXP:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG2:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG2;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG10:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = LOG10;
    copy->child1 = copyTree(tree->child1);
    break;
  case SIN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case COS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = copyTree(tree->child1);
    break;
  case TAN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASIN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATAN:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case SINH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case COSH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case TANH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASINH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOSH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATANH:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case POW:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case NEG:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = copyTree(tree->child1);
    break;
  case ABS:
    copy = (node*) malloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = copyTree(tree->child1);
    break;
  default:
   fprintf(stderr,"copyTree: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


node* differentiate(node *tree) {
  node *derivative;
  mpfr_t *mpfr_temp;
  node *temp_node, *temp_node2, *temp_node3, *f_diff, *g_diff, *f_copy, *g_copy, *g_copy2, *h_copy, *h_copy2;
  node *temp_node4, *f_copy2;

  switch (tree->nodeType) {
  case VARIABLE:
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = CONSTANT;
    temp_node->value = mpfr_temp;
    derivative = temp_node;
    break;
  case CONSTANT:
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = CONSTANT;
    temp_node->value = mpfr_temp;
    derivative = temp_node;    
    break;
  case ADD:
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = ADD;
    temp_node->child1 = differentiate(tree->child1);
    temp_node->child2 = differentiate(tree->child2);
    derivative = temp_node;
    break;
  case SUB:
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = SUB;
    temp_node->child1 = differentiate(tree->child1);
    temp_node->child2 = differentiate(tree->child2);
    derivative = temp_node;
    break;
  case MUL:
    if (tree->child1->nodeType == CONSTANT) {
      f_diff = differentiate(tree->child2);
      g_copy = copyTree(tree->child1);
      temp_node = (node*) malloc(sizeof(node));
      temp_node->nodeType = MUL;
      temp_node->child1 = g_copy;
      temp_node->child2 = f_diff;
      derivative = temp_node;
    } else {
      if (tree->child2->nodeType == CONSTANT) {
	f_diff = differentiate(tree->child1);
	g_copy = copyTree(tree->child2);
	temp_node = (node*) malloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_copy;
	temp_node->child1 = f_diff;
	derivative = temp_node;
      } else {
	f_copy = copyTree(tree->child1);
	g_copy = copyTree(tree->child2);
	f_diff = differentiate(tree->child1);
	g_diff = differentiate(tree->child2);
	temp_node = (node*) malloc(sizeof(node));
	temp_node->nodeType = ADD;
	temp_node2 = (node*) malloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node3 = (node*) malloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node->child1 = temp_node2;
	temp_node->child2 = temp_node3;
	temp_node2->child1 = f_copy;
	temp_node2->child2 = g_diff;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = f_diff;
	derivative = temp_node;
      }
    }
    break;
  case DIV:
    f_copy = copyTree(tree->child1);
    g_copy = copyTree(tree->child2);
    f_diff = differentiate(tree->child1);
    g_diff = differentiate(tree->child2);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = SUB;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = MUL;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node->child1 = temp_node2;
    temp_node->child2 = temp_node3;
    temp_node2->child1 = g_copy;
    temp_node2->child2 = f_diff;
    temp_node3->child1 = f_copy;
    temp_node3->child2 = g_diff;
    g_copy = copyTree(tree->child2);
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = POW;
    temp_node2->child1 = g_copy;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
    temp_node4->value = mpfr_temp;
    temp_node2->child2 = temp_node4;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = DIV;
    temp_node3->child1 = temp_node;
    temp_node3->child2 = temp_node2;
    derivative = temp_node3;
    break;
  case SQRT:
    h_copy = copyTree(tree);
    g_diff = differentiate(tree->child1);
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = MUL;
    temp_node2->child1 = temp_node3;
    temp_node2->child2 = h_copy;
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = DIV;
    temp_node->child1 = g_diff;
    temp_node->child2 = temp_node2;
    derivative = temp_node;
    break;
  case EXP:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = EXP;
    temp_node->child1 = temp_node2;
    temp_node2->child1 = g_copy;    
    derivative = temp_node;
    break;
  case LOG:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node->child1 = temp_node2;
    temp_node2->child2 = g_copy;    
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    derivative = temp_node;
    break;
  case LOG2:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node->child1 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node2->child2 = temp_node3;
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = LOG;
    temp_node3->child2 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    derivative = temp_node;
    break;
  case LOG10:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node->child1 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node2->child2 = temp_node3;
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = LOG;
    temp_node3->child2 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,10.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    derivative = temp_node;
    break;
  case SIN:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = COS;
    temp_node->child1 = temp_node2;
    temp_node2->child1 = g_copy;
    derivative = temp_node;
    break;
  case COS:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = SIN;
    temp_node2->child1 = g_copy;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = NEG;
    temp_node3->child1 = temp_node2;
    temp_node->child1 = temp_node3;
    derivative = temp_node;
    break;
  case TAN:
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = ADD;
    temp_node->child1 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    h_copy = copyTree(tree);
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
    temp_node4->value = mpfr_temp;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = POW;
    temp_node2->child2 = temp_node3;
    temp_node3->child1 = h_copy;
    temp_node3->child2 = temp_node4;
    derivative = temp_node;
    break;
  case ASIN:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = DIV;
    temp_node->child1 = temp_node4;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node3->child2 = g_copy2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = SUB;
    temp_node2->child2 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = SQRT;
    temp_node3->child1 = temp_node2;
    temp_node4->child2 = temp_node3;
    derivative = temp_node;
    break;
  case ACOS:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = DIV;
    temp_node->child1 = temp_node4;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node3->child2 = g_copy2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = SUB;
    temp_node2->child2 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = SQRT;
    temp_node3->child1 = temp_node2;
    temp_node4->child2 = temp_node3;
    derivative = temp_node;
    break;
  case ATAN:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = MUL;
    temp_node2->child1 = g_copy;
    temp_node2->child2 = g_copy2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = ADD;
    temp_node4->child1 = temp_node3;
    temp_node4->child2 = temp_node2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node2->child2 = temp_node4;
    temp_node->child1 = temp_node2;
    derivative = temp_node;
    break;
  case SINH:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = COSH;
    temp_node2->child1 = g_copy;
    temp_node->child1 = temp_node2;
    derivative = temp_node;
    break;
  case COSH:
    g_copy = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = SINH;
    temp_node2->child1 = g_copy;
    temp_node->child1 = temp_node2;
    derivative = temp_node;
    break;
  case TANH:
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = ADD;
    temp_node->child1 = temp_node2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    h_copy = copyTree(tree);
    h_copy2 = copyTree(tree);
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node2->child2 = temp_node3;
    temp_node3->child1 = h_copy;
    temp_node3->child2 = h_copy2;
    derivative = temp_node;
    break;
  case ASINH:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = DIV;
    temp_node->child1 = temp_node4;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node3->child2 = g_copy2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = ADD;
    temp_node2->child2 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = SQRT;
    temp_node3->child1 = temp_node2;
    temp_node4->child2 = temp_node3;
    derivative = temp_node;
    break;
  case ACOSH:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = DIV;
    temp_node->child1 = temp_node4;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = MUL;
    temp_node3->child1 = g_copy;
    temp_node3->child2 = g_copy2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = ADD;
    temp_node2->child2 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = SQRT;
    temp_node3->child1 = temp_node2;
    temp_node4->child2 = temp_node3;
    derivative = temp_node;
    break;
  case ATANH:
    g_copy = copyTree(tree->child1);
    g_copy2 = copyTree(tree->child1);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = MUL;
    temp_node2->child1 = g_copy;
    temp_node2->child2 = g_copy2;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node4 = (node*) malloc(sizeof(node));
    temp_node4->nodeType = SUB;
    temp_node4->child1 = temp_node3;
    temp_node4->child2 = temp_node2;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node3 = (node*) malloc(sizeof(node));
    temp_node3->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,precision);
    mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
    temp_node3->value = mpfr_temp;
    temp_node2->child1 = temp_node3;
    temp_node2->child2 = temp_node4;
    temp_node->child1 = temp_node2;
    derivative = temp_node;
    break;
  case POW:
    if (tree->child2->nodeType == CONSTANT) {
      g_copy = copyTree(tree->child2);
      g_copy2 = copyTree(tree->child2);
      f_diff = differentiate(tree->child1);      
      f_copy = copyTree(tree->child1);
      temp_node2 = (node*) malloc(sizeof(node));
      temp_node2->nodeType = MUL;
      temp_node2->child1 = g_copy;
      temp_node2->child2 = f_diff;
      temp_node3 = (node*) malloc(sizeof(node));
      temp_node3->nodeType = SUB;
      temp_node4 = (node*) malloc(sizeof(node));
      temp_node4->nodeType = CONSTANT;
      mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*mpfr_temp,precision);
      mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
      temp_node4->value = mpfr_temp;
      temp_node3->child2 = temp_node4;
      temp_node3->child1 = g_copy2;
      temp_node4 = (node*) malloc(sizeof(node));
      temp_node4->nodeType = POW;
      temp_node4->child1 = f_copy;
      temp_node4->child2 = temp_node3;
      temp_node = (node*) malloc(sizeof(node));
      temp_node->nodeType = MUL;
      temp_node->child1 = temp_node4;
      temp_node->child2 = temp_node2;
      derivative = temp_node;
    } else {
      h_copy = copyTree(tree);
      f_diff = differentiate(tree->child1);
      f_copy = copyTree(tree->child1);
      f_copy2 = copyTree(tree->child1);
      g_copy = copyTree(tree->child2);
      g_diff = differentiate(tree->child2);
      temp_node4 = (node*) malloc(sizeof(node));
      temp_node4->nodeType = LOG;
      temp_node4->child1 = f_copy;
      temp_node3 = (node*) malloc(sizeof(node));
      temp_node3->nodeType = MUL;
      temp_node3->child1 = g_diff;
      temp_node3->child2 = temp_node4;
      temp_node2 = (node*) malloc(sizeof(node));
      temp_node2->nodeType = MUL;
      temp_node2->child1 = f_diff;
      temp_node2->child2 = g_copy;
      temp_node = (node*) malloc(sizeof(node));
      temp_node->nodeType = DIV;
      temp_node->child1 = temp_node2;
      temp_node->child2 = f_copy2;
      temp_node4 = (node*) malloc(sizeof(node));
      temp_node4->nodeType = ADD;
      temp_node4->child1 = temp_node;
      temp_node4->child2 = temp_node3;
      temp_node = (node*) malloc(sizeof(node));
      temp_node->nodeType = MUL;
      temp_node->child1 = h_copy;
      temp_node->child2 = temp_node4;
      derivative = temp_node;
    }
    break;
  case NEG:
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = NEG;
    temp_node->child1 = g_diff;
    derivative = temp_node;
    break;
  case ABS:
    g_copy = copyTree(tree->child1);
    h_copy = copyTree(tree);
    g_diff = differentiate(tree->child1);
    temp_node = (node*) malloc(sizeof(node));
    temp_node->nodeType = MUL;
    temp_node->child2 = g_diff;
    temp_node2 = (node*) malloc(sizeof(node));
    temp_node2->nodeType = DIV;
    temp_node->child1 = temp_node2;
    temp_node2->child1 = g_copy;
    temp_node2->child2 = h_copy;
    derivative = temp_node;
    break;
  default:
   fprintf(stderr,"differentiate: unknown identifier in the tree\n");
   exit(1);
  }
  return derivative;
}


int evaluateConstantExpression(mpfr_t result, node *tree, mp_prec_t prec) {
  mpfr_t stack1, stack2;
  int isConstant;

  mpfr_init2(stack1, prec);
  mpfr_init2(stack2, prec);

  switch (tree->nodeType) {
  case VARIABLE:
    isConstant = 0;
    break;
  case CONSTANT:
    mpfr_set(result, *(tree->value), GMP_RNDN);
    isConstant = 1;
    break;
  case ADD:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_add(result, stack1, stack2, GMP_RNDN);
    break;
  case SUB:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_sub(result, stack1, stack2, GMP_RNDN);
    break;
  case MUL:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_mul(result, stack1, stack2, GMP_RNDN);
    break;
  case DIV:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_div(result, stack1, stack2, GMP_RNDN);
    break;
  case SQRT:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sqrt(result, stack1, GMP_RNDN);
    break;
  case EXP:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_exp(result, stack1, GMP_RNDN);
    break;
  case LOG:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log(result, stack1, GMP_RNDN);
    break;
  case LOG2:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG10:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log10(result, stack1, GMP_RNDN);
    break;
  case SIN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sin(result, stack1, GMP_RNDN);
    break;
  case COS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_cos(result, stack1, GMP_RNDN);
    break;
  case TAN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_tan(result, stack1, GMP_RNDN);
    break;
  case ASIN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_asin(result, stack1, GMP_RNDN);
    break;
  case ACOS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_acos(result, stack1, GMP_RNDN);
    break;
  case ATAN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_atan(result, stack1, GMP_RNDN);
    break;
  case SINH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sinh(result, stack1, GMP_RNDN);
    break;
  case COSH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_cosh(result, stack1, GMP_RNDN);
    break;
  case TANH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_tanh(result, stack1, GMP_RNDN);
    break;
  case ASINH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_asinh(result, stack1, GMP_RNDN);
    break;
  case ACOSH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_acosh(result, stack1, GMP_RNDN);
    break;
  case ATANH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_atanh(result, stack1, GMP_RNDN);
    break;
  case POW:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_pow(result, stack1, stack2, GMP_RNDN);
    break;
  case NEG:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_neg(result, stack1, GMP_RNDN);
    break;
  case ABS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_abs(result, stack1, GMP_RNDN);
  default:
    fprintf(stderr,"evaluateConstantExpression: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return isConstant;
} 


node* simplify(node *tree) {
  node *simplChild1, *simplChild2, *simplified;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    simplified = (node*) malloc(sizeof(node));
    simplified->nodeType = VARIABLE;
    break;
  case CONSTANT:
    simplified = (node*) malloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) malloc(sizeof(mpfr_t));
    mpfr_init2(*value,precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    simplified->value = value;
    break;
  case ADD:
    simplChild1 = simplify(tree->child1);
    simplChild2 = simplify(tree->child2);
    simplified = (node*) malloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_add(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free(simplified);
	simplified = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = ADD;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case SUB:
    simplChild1 = simplify(tree->child1);
    simplChild2 = simplify(tree->child2);
    simplified = (node*) malloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_sub(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	simplified->nodeType = NEG;
	simplified->child1 = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = SUB;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case MUL:
    simplChild1 = simplify(tree->child1);
    simplChild2 = simplify(tree->child2);
    simplified = (node*) malloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_mul(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if (((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) ||
	  ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value))))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) malloc(sizeof(mpfr_t));
	mpfr_init2(*value,precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild1->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild1->value),1.0) == 0)) {
	  free_memory(simplChild1);
	  free(simplified);
	  simplified = simplChild2;
	} else {
	  if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	    free_memory(simplChild2);
	    free(simplified);
	    simplified = simplChild1;
	  } else {
	    simplified->nodeType = MUL;
	    simplified->child1 = simplChild1;
	    simplified->child2 = simplChild2;
	  }
	}
      }
    }
    break;
  case DIV:
    simplChild1 = simplify(tree->child1);
    simplChild2 = simplify(tree->child2);
    simplified = (node*) malloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_div(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) malloc(sizeof(mpfr_t));
	mpfr_init2(*value,precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = DIV;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case SQRT:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_sqrt(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SQRT;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_exp(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = EXP;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_log(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG2:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_log2(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG2;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG10:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_log10(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG10;
      simplified->child1 = simplChild1;
    }
    break;
  case SIN:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_sin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SIN;
      simplified->child1 = simplChild1;
    }
    break;
  case COS:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_cos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COS;
      simplified->child1 = simplChild1;
    }
    break;
  case TAN:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_tan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TAN;
      simplified->child1 = simplChild1;
    }
    break;
  case ASIN:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_asin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASIN;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOS:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_acos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOS;
      simplified->child1 = simplChild1;
    }
    break;
  case ATAN:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_atan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATAN;
      simplified->child1 = simplChild1;
    }
    break;
  case SINH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_sinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SINH;
      simplified->child1 = simplChild1;
    }
    break;
  case COSH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_cosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COSH;
      simplified->child1 = simplChild1;
    }
    break;
  case TANH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_tanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TANH;
      simplified->child1 = simplChild1;
    }
    break;
  case ASINH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_asinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASINH;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOSH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_acosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOSH;
      simplified->child1 = simplChild1;
    }
    break;
  case ATANH:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_atanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATANH;
      simplified->child1 = simplChild1;
    }
    break;
  case POW:
    simplChild1 = simplify(tree->child1);
    simplChild2 = simplify(tree->child2);
    simplified = (node*) malloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_pow(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	free(simplified);
	free_memory(simplChild2);
	simplified = simplChild1;
      } else {
	simplified->nodeType = POW;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
      }
    }
    break;
  case NEG:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_neg(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = NEG;
      simplified->child1 = simplChild1;
    }
    break;
  case ABS:
    simplChild1 = simplify(tree->child1);
    simplified = (node*) malloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*value,precision);
      simplified->value = value;
      mpfr_abs(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ABS;
      simplified->child1 = simplChild1;
    }
  default:
    fprintf(stderr,"simplify: unknown identifier in the tree\n");
    exit(1);
  }

  return simplified;
}


void evaluate(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec) {
  mpfr_t stack1, stack2;

  mpfr_init2(stack1, prec);
  mpfr_init2(stack2, prec);

  switch (tree->nodeType) {
  case VARIABLE:
    mpfr_set(result, x, GMP_RNDN);
    break;
  case CONSTANT:
    mpfr_set(result, *(tree->value), GMP_RNDN);
    break;
  case ADD:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_add(result, stack1, stack2, GMP_RNDN);
    break;
  case SUB:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_sub(result, stack1, stack2, GMP_RNDN);
    break;
  case MUL:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_mul(result, stack1, stack2, GMP_RNDN);
    break;
  case DIV:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_div(result, stack1, stack2, GMP_RNDN);
    break;
  case SQRT:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sqrt(result, stack1, GMP_RNDN);
    break;
  case EXP:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_exp(result, stack1, GMP_RNDN);
    break;
  case LOG:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log(result, stack1, GMP_RNDN);
    break;
  case LOG2:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG10:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log10(result, stack1, GMP_RNDN);
    break;
  case SIN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sin(result, stack1, GMP_RNDN);
    break;
  case COS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_cos(result, stack1, GMP_RNDN);
    break;
  case TAN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_tan(result, stack1, GMP_RNDN);
    break;
  case ASIN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_asin(result, stack1, GMP_RNDN);
    break;
  case ACOS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_acos(result, stack1, GMP_RNDN);
    break;
  case ATAN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_atan(result, stack1, GMP_RNDN);
    break;
  case SINH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sinh(result, stack1, GMP_RNDN);
    break;
  case COSH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_cosh(result, stack1, GMP_RNDN);
    break;
  case TANH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_tanh(result, stack1, GMP_RNDN);
    break;
  case ASINH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_asinh(result, stack1, GMP_RNDN);
    break;
  case ACOSH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_acosh(result, stack1, GMP_RNDN);
    break;
  case ATANH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_atanh(result, stack1, GMP_RNDN);
    break;
  case POW:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_pow(result, stack1, stack2, GMP_RNDN);
    break;
  case NEG:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_neg(result, stack1, GMP_RNDN);
    break;
  case ABS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_abs(result, stack1, GMP_RNDN);
  default:
    fprintf(stderr,"evaluate: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return;
}
