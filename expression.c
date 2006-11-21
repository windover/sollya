#include <mpfr.h>
#include <gmp.h>
#include "expression.h"
#include <stdio.h> /* fprinft, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <string.h>
#include <errno.h>
#include "main.h"
#include "double.h"



void free_memory(node *tree) {
  if (tree == NULL) return;
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
  case LOG_2:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG_10:
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
  case DOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case DOUBLEDOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case TRIPLEDOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case ERF: 
    free_memory(tree->child1);
    free(tree);
    break;
  case ERFC:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG_1P:
    free_memory(tree->child1);
    free(tree);
    break;
  case EXP_M1:
    free_memory(tree->child1);
    free(tree);
    break;
  case DOUBLEEXTENDED:
    free_memory(tree->child1);
    free(tree);
    break;
  default:
   fprintf(stderr,"Error: free_memory: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}




void fprintHeadFunction(FILE *fd,node *tree, char *x, char *y) {
  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (x != NULL) fprintf(fd,"%s",x); else fprintf(fd,"x");
    break;
  case CONSTANT:
    fprintValue(fd,*(tree->value));
    break;
  case ADD:
    fprintf(fd,"%s + %s",x,y);
    break;
  case SUB:
    fprintf(fd,"%s - %s",x,y);
    break;
  case MUL:
    fprintf(fd,"%s * %s",x,y);
    break;
  case DIV:
    fprintf(fd,"%s / %s",x,y);
    break;
  case SQRT:
    fprintf(fd,"sqrt(%s)",x);
    break;
  case EXP:
    fprintf(fd,"exp(%s)",x);
    break;
  case LOG:
    fprintf(fd,"log(%s)",x);
    break;
  case LOG_2:
    fprintf(fd,"log2(%s)",x);
    break;
  case LOG_10:
    fprintf(fd,"log10(%s)",x);
    break;
  case SIN:
    fprintf(fd,"sin(%s)",x);
    break;
  case COS:
    fprintf(fd,"cos(%s)",x);
    break;
  case TAN:
    fprintf(fd,"tan(%s)",x);
    break;
  case ASIN:
    fprintf(fd,"asin(%s)",x);
    break;
  case ACOS:
    fprintf(fd,"acos(%s)",x);
    break;
  case ATAN:
    fprintf(fd,"atan(%s)",x);
    break;
  case SINH:
    fprintf(fd,"sinh(%s)",x);
    break;
  case COSH:
    fprintf(fd,"cosh(%s)",x);
    break;
  case TANH:
    fprintf(fd,"tanh(%s)",x);
    break;
  case ASINH:
    fprintf(fd,"asinh(%s)",x);
    break;
  case ACOSH:
    fprintf(fd,"acosh(%s)",x);
    break;
  case ATANH:
    fprintf(fd,"atanh(%s)",x);
    break;
  case POW:
    fprintf(fd,"%s^%s",x,y);
    break;
  case NEG:
    fprintf(fd,"-%s",x);
    break;
  case ABS:
    fprintf(fd,"abs(%s)",x);
    break;
  case DOUBLE:
    fprintf(fd,"double(%s)",x);
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(%s)",x);
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(%s)",x);
    break;
  case ERF: 
    fprintf(fd,"erf(%s)",x);
    break;
  case ERFC:
    fprintf(fd,"erfc(%s)",x);
    break;
  case LOG_1P:
    fprintf(fd,"log1p(%s)",x);
    break;
  case EXP_M1:
    fprintf(fd,"expm1(%s)",x);
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(%s)",x);
    break;
  default:
   fprintf(stderr,"fprintHeadFunction: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}

int precedence(node *tree) {
  switch (tree->nodeType) {
  case CONSTANT:
  case VARIABLE:
    return 1;
    break;
  case ADD:
  case SUB:
    return 2;
    break;
  case MUL:
    return 3;
    break;
  case DIV:
    return 4;
    break;
  case POW:
    return 5;
    break;
  default:
    return 6; 
  }
  return 0;
}


int isInfix(node *tree) {
  switch(tree->nodeType) {
  case CONSTANT: 
    if (mpfr_sgn(*(tree->value)) < 0) return 1;
    break;
  case ADD:
  case SUB:
  case MUL:
  case DIV:
  case POW:
  case NEG:
    return 1;
    break;
  default: return 0;
  }
  return 0;
}


void printValue(mpfr_t *value, mp_prec_t prec) {
  mpfr_t y;
  char *str, *str2;
  mp_exp_t e, expo;
  double v;
  int t;


  prec = mpfr_get_prec(*value);
  mpfr_init2(y,prec);
  v = mpfr_get_d(*value,GMP_RNDN);
  t = (int) v;
  v = (double) t;
  mpfr_set_d(y,v,GMP_RNDN);
  if ((mpfr_cmp(y,*value) == 0) && (mpfr_number_p(*value))) {
    printf("%d",t);
  } else { 
    mpfr_set(y,*value,GMP_RNDN);
    if (mpfr_sgn(y) < 0) {
      printf("-"); mpfr_neg(y,y,GMP_RNDN);
    }
    if ((dyadic == 1) || (dyadic == 2)) {
      if (!mpfr_number_p(*value)) {
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	printf("%s",str);
      } else {
	expo = mpfr_get_exp(y);
	if (mpfr_set_exp(y,prec)) {
	  printMessage(1,"\nWarning: %d is not in the current exponent range of a variable. Values displayed may be wrong.\n",(int)(prec));
	}
	expo -= prec;
	while (mpfr_integer_p(y)) {
	  mpfr_div_2ui(y,y,1,GMP_RNDN);
	  expo += 1;
	}
	expo--;
	if (mpfr_mul_2ui(y,y,1,GMP_RNDN) != 0) {
	  printMessage(1,"\nWarning: rounding occured during displaying a value. Values displayed may be wrong.\n");
	}
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	str2 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	strncpy(str2,str,e);
	if (dyadic == 1) 
	  printf("%sb%d",str2,(int)expo);
	else
	  printf("%s * 2^(%d)",str2,(int)expo);
	free(str2);
      }
      mpfr_free_str(str);      
    } else {
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      if (mpfr_number_p(*value)) 
	printf("0.%se%d",str,(int)e); 
      else 
	printf("%s",str);
      mpfr_free_str(str);      
    }
  }
  mpfr_clear(y);
}


void printMpfr(mpfr_t x) {
  mpfr_t tmp;
  mp_prec_t prec;

  prec = mpfr_get_prec(x);
  mpfr_init2(tmp,prec);
  mpfr_set(tmp,x,GMP_RNDN);

  printValue(&tmp,prec);
  printf("\n");

  mpfr_clear(tmp);
}



void fprintValue(FILE *fd, mpfr_t value) {
  mpfr_t y;
  char *str, *str2;
  mp_exp_t e, expo;
  mp_prec_t prec;

  if (mpfr_zero_p(value)) {
    fprintf(fd,"0");
  } else {
    prec = mpfr_get_prec(value);
    mpfr_init2(y,prec+10);
    mpfr_set(y,value,GMP_RNDN);
    if (mpfr_sgn(y) < 0) {
      fprintf(fd,"-"); mpfr_neg(y,y,GMP_RNDN);
    }
    if (!mpfr_number_p(value)) {
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      fprintf(fd,"%s",str);
    } else {
      expo = mpfr_get_exp(y);
      if (mpfr_set_exp(y,prec+10)) {
	printMessage(1,"\nWarning: upon printing to a file: %d is not in the current exponent range of a variable. Values printed may be wrong.\n",(int)(prec+10));
      }
      expo -= prec+10;
      while (mpfr_integer_p(y)) {
	mpfr_div_2ui(y,y,1,GMP_RNDN);
	expo += 1;
      }
      expo--;
      if (mpfr_mul_2ui(y,y,1,GMP_RNDN) != 0) {
	printMessage(1,"\nWarning: upon printing to a file: rounding occured. Values printed may be wrong.\n");
      }
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      str2 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
      strncpy(str2,str,e);
      fprintf(fd,"%sb%d",str2,(int)expo);
      free(str2);
    }
    mpfr_clear(y);
  }
}



void printTree(node *tree) {
  int pred;

  pred = precedence(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    printf("%s",variablename);
    break;
  case CONSTANT:
    printValue(tree->value,mpfr_get_prec(*(tree->value)));
    break;
  case ADD:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf(")");
    printf(" + ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf(")");
    break;
  case SUB:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf(")");
    printf(" - ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf(")");
    break;
  case MUL:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf(")");
    printf(" * ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf(")");
    break;
  case DIV:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred)) 
      printf(")");
    printf(" / ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
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
  case LOG_2:
    printf("log2(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG_10:
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
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf(")");
    printf("^");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) {
      printf("(");
    }
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) {
      printf(")");
    }
    break;
  case NEG:
    printf("-");
    if (isInfix(tree->child1)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1)) 
      printf(")");
    break;
  case ABS:
    printf("abs(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLE:
    printf("double(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLEDOUBLE:
    printf("doubledouble(");
    printTree(tree->child1);
    printf(")");
    break;
  case TRIPLEDOUBLE:
    printf("tripledouble(");
    printTree(tree->child1);
    printf(")");
    break;
  case ERF: 
    printf("erf(");
    printTree(tree->child1);
    printf(")");
    break;
  case ERFC:
    printf("erfc(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG_1P:
    printf("log1p(");
    printTree(tree->child1);
    printf(")");
    break;
  case EXP_M1:
    printf("expm1(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLEEXTENDED:
    printf("doubleextended(");
    printTree(tree->child1);
    printf(")");
    break;
  default:
   fprintf(stderr,"Error: printTree: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}

void fprintTree(FILE *fd, node *tree) {
  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename != NULL) fprintf(fd,"%s",variablename); else fprintf(fd,"x");
    break;
  case CONSTANT:
    fprintValue(fd,*(tree->value));
    break;
  case ADD:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," + ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case SUB:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," - ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case MUL:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," * ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case DIV:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," / ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case SQRT:
    fprintf(fd,"sqrt(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP:
    fprintf(fd,"exp(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG:
    fprintf(fd,"log(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_2:
    fprintf(fd,"log2(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_10:
    fprintf(fd,"log10(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SIN:
    fprintf(fd,"sin(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COS:
    fprintf(fd,"cos(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TAN:
    fprintf(fd,"tan(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASIN:
    fprintf(fd,"asin(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOS:
    fprintf(fd,"acos(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATAN:
    fprintf(fd,"atan(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SINH:
    fprintf(fd,"sinh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COSH:
    fprintf(fd,"cosh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TANH:
    fprintf(fd,"tanh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASINH:
    fprintf(fd,"asinh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOSH:
    fprintf(fd,"acosh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATANH:
    fprintf(fd,"atanh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case POW:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd,"^(");
    fprintTree(fd,tree->child2);
    fprintf(fd,")");
    break;
  case NEG:
    fprintf(fd,"-");
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    break;
  case ABS:
    fprintf(fd,"abs(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLE:
    fprintf(fd,"double(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERF: 
    fprintf(fd,"erf(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERFC:
    fprintf(fd,"erfc(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_1P:
    fprintf(fd,"log1p(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP_M1:
    fprintf(fd,"expm1(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  default:
   fprintf(stderr,"Error: fprintTree: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}



node* copyTree(node *tree) {
  node *copy;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = copyTree(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = copyTree(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = copyTree(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = copyTree(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case ERF: 
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = copyTree(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = copyTree(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = copyTree(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: copyTree: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


node* simplifyTreeErrorfree(node *tree) {
  node *simplChild1, *simplChild2, *simplified;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = VARIABLE;
    break;
  case CONSTANT:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,mpfr_get_prec(*(tree->value)) + 10);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    simplified->value = value;
    break;
  case ADD:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplChild2 = simplifyTreeErrorfree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_add(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ADD;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
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
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplChild2 = simplifyTreeErrorfree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sub(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SUB;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
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
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplChild2 = simplifyTreeErrorfree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_mul(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = MUL;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if (((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) ||
	  ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value))))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplChild2 = simplifyTreeErrorfree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_div(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = DIV;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sqrt(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SQRT;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = SQRT;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_exp(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = EXP;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = EXP;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_2:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log2(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_2;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_2;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_10:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log10(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_10;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_10;
      simplified->child1 = simplChild1;
    }
    break;
  case SIN:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sin(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SIN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = SIN;
      simplified->child1 = simplChild1;
    }
    break;
  case COS:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_cos(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = COS;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = COS;
      simplified->child1 = simplChild1;
    }
    break;
  case TAN:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_tan(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = TAN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TAN;
      simplified->child1 = simplChild1;
    }
    break;
  case ASIN:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_asin(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ASIN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ASIN;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOS:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_acos(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ACOS;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ACOS;
      simplified->child1 = simplChild1;
    }
    break;
  case ATAN:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_atan(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ATAN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ATAN;
      simplified->child1 = simplChild1;
    }
    break;
  case SINH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sinh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SINH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = SINH;
      simplified->child1 = simplChild1;
    }
    break;
  case COSH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_cosh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = COSH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = COSH;
      simplified->child1 = simplChild1;
    }
    break;
  case TANH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_tanh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = TANH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TANH;
      simplified->child1 = simplChild1;
    }
    break;
  case ASINH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_asinh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ASINH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ASINH;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOSH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_acosh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ACOSH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ACOSH;
      simplified->child1 = simplChild1;
    }
    break;
  case ATANH:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_atanh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ATANH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ATANH;
      simplified->child1 = simplChild1;
    }
    break;
  case POW:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplChild2 = simplifyTreeErrorfree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_pow(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = POW;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
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
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_neg(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = NEG;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = NEG;
      simplified->child1 = simplChild1;
    }
    break;
  case ABS:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_abs(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ABS;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ABS;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLE:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_round_to_double(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = DOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEDOUBLE:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubledouble(*value, *(simplChild1->value));
      free_memory(simplChild1);
      if ((mpfr_round_to_doubledouble(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = DOUBLEDOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case TRIPLEDOUBLE:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_round_to_tripledouble(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = TRIPLEDOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TRIPLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case ERF: 
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_erf(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ERF;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ERF;
      simplified->child1 = simplChild1;
    }
    break;
  case ERFC:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_erfc(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ERFC;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ERFC;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_1P:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log1p(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_1P;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_1P;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP_M1:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_expm1(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = EXP_M1;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = EXP_M1;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEEXTENDED:
    simplChild1 = simplifyTreeErrorfree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_round_to_doubleextended(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = DOUBLEEXTENDED;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLEEXTENDED;
      simplified->child1 = simplChild1;
    }
    break;
  default:
    fprintf(stderr,"Error: simplifyTreeErrorfree: unknown identifier in the tree\n");
    exit(1);
  }

  return simplified;
}


int isPolynomial(node *tree);
node *differentiatePolynomialUnsafe(node *tree);

node* differentiateUnsimplified(node *tree) {
  node *derivative;
  mpfr_t *mpfr_temp;
  node *temp_node, *temp_node2, *temp_node3, *f_diff, *g_diff, *f_copy, *g_copy, *g_copy2, *h_copy, *h_copy2;
  node *temp_node4, *f_copy2, *temp_node5;

  if (isConstant(tree)) {
    mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
    temp_node = (node*) safeMalloc(sizeof(node));
    temp_node->nodeType = CONSTANT;
    temp_node->value = mpfr_temp;
    derivative = temp_node;    
  } else {
    if (isPolynomial(tree)) {
      derivative = differentiatePolynomialUnsafe(tree);
    } else {
      
      switch (tree->nodeType) {
      case VARIABLE:
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case CONSTANT:
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;    
	break;
      case ADD:
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = ADD;
	temp_node->child1 = differentiateUnsimplified(tree->child1);
	temp_node->child2 = differentiateUnsimplified(tree->child2);
	derivative = temp_node;
	break;
      case SUB:
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = SUB;
	temp_node->child1 = differentiateUnsimplified(tree->child1);
	temp_node->child2 = differentiateUnsimplified(tree->child2);
	derivative = temp_node;
	break;
      case MUL:
	if (tree->child1->nodeType == CONSTANT) {
	  f_diff = differentiateUnsimplified(tree->child2);
	  g_copy = copyTree(tree->child1);
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = g_copy;
	  temp_node->child2 = f_diff;
	  derivative = temp_node;
	} else {
	  if (tree->child2->nodeType == CONSTANT) {
	    f_diff = differentiateUnsimplified(tree->child1);
	    g_copy = copyTree(tree->child2);
	    temp_node = (node*) safeMalloc(sizeof(node));
	    temp_node->nodeType = MUL;
	    temp_node->child2 = g_copy;
	    temp_node->child1 = f_diff;
	    derivative = temp_node;
	  } else {
	    f_copy = copyTree(tree->child1);
	    g_copy = copyTree(tree->child2);
	    f_diff = differentiateUnsimplified(tree->child1);
	    g_diff = differentiateUnsimplified(tree->child2);
	    temp_node = (node*) safeMalloc(sizeof(node));
	    temp_node->nodeType = ADD;
	    temp_node2 = (node*) safeMalloc(sizeof(node));
	    temp_node2->nodeType = MUL;
	    temp_node3 = (node*) safeMalloc(sizeof(node));
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
	f_diff = differentiateUnsimplified(tree->child1);
	g_diff = differentiateUnsimplified(tree->child2);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = SUB;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node->child1 = temp_node2;
	temp_node->child2 = temp_node3;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = f_diff;
	temp_node3->child1 = f_copy;
	temp_node3->child2 = g_diff;
	g_copy = copyTree(tree->child2);
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = POW;
	temp_node2->child1 = g_copy;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node4->value = mpfr_temp;
	temp_node2->child2 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = DIV;
	temp_node3->child1 = temp_node;
	temp_node3->child2 = temp_node2;
	derivative = temp_node3;
	break;
      case SQRT:
	h_copy = copyTree(tree);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = temp_node3;
	temp_node2->child2 = h_copy;
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = DIV;
	temp_node->child1 = g_diff;
	temp_node->child2 = temp_node2;
	derivative = temp_node;
	break;
      case EXP:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = EXP;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;    
	derivative = temp_node;
	break;
      case LOG:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node2->child2 = g_copy;    
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case LOG_2:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node2->child2 = temp_node3;
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = LOG;
	temp_node3->child2 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case LOG_10:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node2->child2 = temp_node3;
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = LOG;
	temp_node3->child2 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,10.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case SIN:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = COS;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;
	derivative = temp_node;
	break;
      case COS:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SIN;
	temp_node2->child1 = g_copy;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node2;
	temp_node->child1 = temp_node3;
	derivative = temp_node;
	break;
      case TAN:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	h_copy = copyTree(tree);
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node4->value = mpfr_temp;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = POW;
	temp_node2->child2 = temp_node3;
	temp_node3->child1 = h_copy;
	temp_node3->child2 = temp_node4;
	derivative = temp_node;
	break;
      case ASIN:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = POW;
	temp_node3->child1 = g_copy;
	temp_node5 = (node*) safeMalloc(sizeof(node));
	temp_node5->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node5->value = mpfr_temp;
	temp_node3->child2 = temp_node5;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ACOS:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ATAN:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = g_copy2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = ADD;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = temp_node2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node2->child2 = temp_node4;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case SINH:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = COSH;
	temp_node2->child1 = g_copy;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case COSH:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SINH;
	temp_node2->child1 = g_copy;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case TANH:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	h_copy = copyTree(tree);
	h_copy2 = copyTree(tree);
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node2->child2 = temp_node3;
	temp_node3->child1 = h_copy;
	temp_node3->child2 = h_copy2;
	derivative = temp_node;
	break;
      case ASINH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ACOSH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ATANH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = g_copy2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = SUB;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = temp_node2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
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
	  f_diff = differentiateUnsimplified(tree->child1);      
	  f_copy = copyTree(tree->child1);
	  temp_node2 = (node*) safeMalloc(sizeof(node));
	  temp_node2->nodeType = MUL;
	  temp_node2->child1 = g_copy;
	  temp_node2->child2 = f_diff;
	  temp_node3 = (node*) safeMalloc(sizeof(node));
	  temp_node3->nodeType = SUB;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = CONSTANT;
	  mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*mpfr_temp,tools_precision);
	  mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	  temp_node4->value = mpfr_temp;
	  temp_node3->child2 = temp_node4;
	  temp_node3->child1 = g_copy2;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = POW;
	  temp_node4->child1 = f_copy;
	  temp_node4->child2 = temp_node3;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = temp_node4;
	  temp_node->child2 = temp_node2;
	  derivative = temp_node;
	} else {
	  h_copy = copyTree(tree);
	  f_diff = differentiateUnsimplified(tree->child1);
	  f_copy = copyTree(tree->child1);
	  f_copy2 = copyTree(tree->child1);
	  g_copy = copyTree(tree->child2);
	  g_diff = differentiateUnsimplified(tree->child2);
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = LOG;
	  temp_node4->child1 = f_copy;
	  temp_node3 = (node*) safeMalloc(sizeof(node));
	  temp_node3->nodeType = MUL;
	  temp_node3->child1 = g_diff;
	  temp_node3->child2 = temp_node4;
	  temp_node2 = (node*) safeMalloc(sizeof(node));
	  temp_node2->nodeType = MUL;
	  temp_node2->child1 = f_diff;
	  temp_node2->child2 = g_copy;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = DIV;
	  temp_node->child1 = temp_node2;
	  temp_node->child2 = f_copy2;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = ADD;
	  temp_node4->child1 = temp_node;
	  temp_node4->child2 = temp_node3;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = h_copy;
	  temp_node->child2 = temp_node4;
	  derivative = temp_node;
	}
	break;
      case NEG:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = NEG;
	temp_node->child1 = g_diff;
	derivative = temp_node;
	break;
      case ABS:
	g_copy = copyTree(tree->child1);
	h_copy = copyTree(tree);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = h_copy;
	derivative = temp_node;
	break;
      case DOUBLE:
	printMessage(1,
		     "Warning: the double rounding operator is not differentiable.\nRemplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case DOUBLEDOUBLE:
	printMessage(1,
		     "Warning: the double-double rounding operator is not differentiable.\nRemplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case TRIPLEDOUBLE:
	printMessage(1,
		     "Warning: the triple-double rounding operator is not differentiable.\nRemplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case ERF: 
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = ATAN;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node4;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = POW;
	temp_node4->child1 = g_copy;
	temp_node4->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = EXP;
	temp_node4->child1 = temp_node3;
	temp_node2->child1 = temp_node4;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case ERFC:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = ATAN;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node4;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = POW;
	temp_node4->child1 = g_copy;
	temp_node4->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = EXP;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node2->child1 = temp_node3;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case LOG_1P:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = ADD;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = g_copy;
	temp_node2->child2 = temp_node4;    
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case EXP_M1:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = EXP;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;    
	derivative = temp_node;
	break;
      case DOUBLEEXTENDED:
	printMessage(1,
		     "Warning: the double-extended rounding operator is not differentiable.\nRemplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      default:
	fprintf(stderr,"Error: differentiateUnsimplified: unknown identifier in the tree\n");
	exit(1);
      }
    }
  }
  return derivative;
}


node* differentiate(node *tree) {
  node *temp, *temp2, *temp3;

  printMessage(12,"Information: formally differentiating a function.\n");

  temp3 = simplifyTreeErrorfree(tree);
  temp = differentiateUnsimplified(temp3);
  temp2 = simplifyTreeErrorfree(temp);
  free_memory(temp);
  free_memory(temp3);
  return temp2;
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
  case LOG_2:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG_10:
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
    break;
  case DOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_double(result, stack1);
    break;
  case DOUBLEDOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_doubledouble(result, stack1);
  case TRIPLEDOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_tripledouble(result, stack1);
    break;
  case ERF:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_erf(result, stack1, GMP_RNDN);
    break;
  case ERFC:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_erfc(result, stack1, GMP_RNDN);
    break;
  case LOG_1P:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log1p(result, stack1, GMP_RNDN);
    break;
  case EXP_M1:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_expm1(result, stack1, GMP_RNDN);
    break;
  case DOUBLEEXTENDED:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_doubleextended(result, stack1);
    break;
  default:
    fprintf(stderr,"Error: evaluateConstantExpression: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return isConstant;
} 


node* simplifyTree(node *tree) {
  node *simplChild1, *simplChild2, *simplified;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = VARIABLE;
    break;
  case CONSTANT:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    simplified->value = value;
    break;
  case ADD:
    simplChild1 = simplifyTree(tree->child1);
    simplChild2 = simplifyTree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTree(tree->child1);
    simplChild2 = simplifyTree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTree(tree->child1);
    simplChild2 = simplifyTree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
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
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTree(tree->child1);
    simplChild2 = simplifyTree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_div(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sqrt(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SQRT;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_exp(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = EXP;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_2:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log2(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_2;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_10:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log10(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_10;
      simplified->child1 = simplChild1;
    }
    break;
  case SIN:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SIN;
      simplified->child1 = simplChild1;
    }
    break;
  case COS:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_cos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COS;
      simplified->child1 = simplChild1;
    }
    break;
  case TAN:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_tan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TAN;
      simplified->child1 = simplChild1;
    }
    break;
  case ASIN:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_asin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASIN;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOS:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_acos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOS;
      simplified->child1 = simplChild1;
    }
    break;
  case ATAN:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_atan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATAN;
      simplified->child1 = simplChild1;
    }
    break;
  case SINH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SINH;
      simplified->child1 = simplChild1;
    }
    break;
  case COSH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_cosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COSH;
      simplified->child1 = simplChild1;
    }
    break;
  case TANH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_tanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TANH;
      simplified->child1 = simplChild1;
    }
    break;
  case ASINH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_asinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASINH;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOSH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_acosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOSH;
      simplified->child1 = simplChild1;
    }
    break;
  case ATANH:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_atanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATANH;
      simplified->child1 = simplChild1;
    }
    break;
  case POW:
    simplChild1 = simplifyTree(tree->child1);
    simplChild2 = simplifyTree(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
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
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_neg(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = NEG;
      simplified->child1 = simplChild1;
    }
    break;
  case ABS:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_abs(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ABS;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLE:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_double(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEDOUBLE:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubledouble(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case TRIPLEDOUBLE:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_tripledouble(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TRIPLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case ERF:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_erf(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ERF;
      simplified->child1 = simplChild1;
    }
    break;
  case ERFC:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_erfc(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ERFC;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_1P:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log1p(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_1P;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP_M1:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_expm1(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = EXP_M1;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEEXTENDED:
    simplChild1 = simplifyTree(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubleextended(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLEEXTENDED;
      simplified->child1 = simplChild1;
    }
    break;
  default:
    fprintf(stderr,"Error: simplifyTree: unknown identifier in the tree\n");
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
  case LOG_2:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG_10:
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
    break;
  case DOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_double(result, stack1);
    break;
  case DOUBLEDOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_doubledouble(result, stack1);
    break;
  case TRIPLEDOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_tripledouble(result, stack1);
    break;
  case ERF:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_erf(result, stack1, GMP_RNDN);
    break;
  case ERFC:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_erfc(result, stack1, GMP_RNDN);
    break;
  case LOG_1P:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log1p(result, stack1, GMP_RNDN);
    break;
  case EXP_M1:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_expm1(result, stack1, GMP_RNDN);
    break;
  case DOUBLEEXTENDED:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_doubleextended(result, stack1);
    break;
  default:
    fprintf(stderr,"Error: evaluate: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return;
}


int arity(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
    return 0;
    break;
  case ADD:
    return 2;
    break;
  case SUB:
    return 2;
    break;
  case MUL:
    return 2;
    break;
  case DIV:
    return 2;
    break;
  case SQRT:
    return 1;
    break;
  case EXP:
    return 1;
    break;
  case LOG:
    return 1;
    break;
  case LOG_2:
    return 1;
    break;
  case LOG_10:
    return 1;
    break;
  case SIN:
    return 1;
    break;
  case COS:
    return 1;
    break;
  case TAN:
    return 1;
    break;
  case ASIN:
    return 1;
    break;
  case ACOS:
    return 1;
    break;
  case ATAN:
    return 1;
    break;
  case SINH:
    return 1;
    break;
  case COSH:
    return 1;
    break;
  case TANH:
    return 1;
    break;
  case ASINH:
    return 1;
    break;
  case ACOSH:
    return 1;
    break;
  case ATANH:
    return 1;
    break;
  case POW:
    return 2;
    break;
  case NEG:
    return 1;
    break;
  case ABS:
    return 1;
    break;
  case DOUBLE:
    return 1;
    break;
  case DOUBLEDOUBLE:
    return 1;
    break;
  case TRIPLEDOUBLE:
    return 1;
    break;
  case ERF:
    return 1;
    break;
  case ERFC:
    return 1;
    break;
  case LOG_1P:
    return 1;
    break;
  case EXP_M1:
    return 1;
    break;
  case DOUBLEEXTENDED:
    return 1;
    break;
  default:
    fprintf(stderr,"Error: arity: unknown identifier in the tree\n");
    exit(1);
  }
}


int isSyntacticallyEqual(node *tree1, node *tree2) {

  if (tree1->nodeType != tree2->nodeType) return 0;
  if (tree1->nodeType == CONSTANT) {
    if (mpfr_equal_p(*(tree1->value),*(tree2->value))) 
      return 1;
    else 
      return 0;
  }
  if (tree1->nodeType == VARIABLE) return 1;

  if (arity(tree1) == 1) {
    if (!isSyntacticallyEqual(tree1->child1,tree2->child1)) return 0;
  } else {
    if (!isSyntacticallyEqual(tree1->child1,tree2->child1)) return 0;
    if (!isSyntacticallyEqual(tree1->child2,tree2->child2)) return 0;
  }

  return 1;
}



int isConstant(node *tree);

int isPolynomial(node *tree) {
  int res;
  node *temp;
  
  if (isConstant(tree)) return 1;

  switch (tree->nodeType) {
  case VARIABLE:
    res = 1;
    break;
  case CONSTANT:
    res = 1;
    break;
  case ADD:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case SUB:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case MUL:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case DIV:
    res = isPolynomial(tree->child1) && isConstant(tree->child2);
    break;
  case SQRT:
    res = 0;
    break;
  case EXP:
    res = 0;
    break;
  case LOG:
    res = 0;
    break;
  case LOG_2:
    res = 0;
    break;
  case LOG_10:
    res = 0;
    break;
  case SIN:
    res = 0;
    break;
  case COS:
    res = 0;
    break;
  case TAN:
    res = 0;
    break;
  case ASIN:
    res = 0;
    break;
  case ACOS:
    res = 0;
    break;
  case ATAN:
    res = 0;
    break;
  case SINH:
    res = 0;
    break;
  case COSH:
    res = 0;
    break;
  case TANH:
    res = 0;
    break;
  case ASINH:
    res = 0;
    break;
  case ACOSH:
    res = 0;
    break;
  case ATANH:
    res = 0;
    break;
  case POW:
    {
      res = 0;
      if (isConstant(tree)) {
	res = 1;
      } else {
	if (isPolynomial(tree->child1)) {
	  if (tree->child2->nodeType == CONSTANT) 
	    temp = tree->child2; 
	  else 
	    temp = simplifyTreeErrorfree(tree->child2);
	  if (temp->nodeType == CONSTANT) {
	    if (mpfr_integer_p(*(temp->value))) {
	      if (mpfr_sgn(*(temp->value)) >= 0) {
		res = 1;
	      }
	    }
	  }
	  if (tree->child2->nodeType != CONSTANT) free_memory(temp);
	}
      }
    }
    break;
  case NEG:
    res = isPolynomial(tree->child1);
    break;
  case ABS:
    res = 0;
    break;
  case DOUBLE:
    res = 0;
    break;
  case DOUBLEDOUBLE:
    res = 0;
    break;
  case TRIPLEDOUBLE:
    res = 0;
    break;
  case ERF:
    res = 0;
    break;
  case ERFC:
    res = 0;
    break;
  case LOG_1P:
    res = 0;
    break;
  case EXP_M1:
    res = 0;
    break;
  case DOUBLEEXTENDED:
    res = 0;
    break;
  default:
    fprintf(stderr,"Error: isPolynomial: unknown identifier in the tree\n");
    exit(1);
  }
 return res;
}

#define MAX(a,b) (a) > (b) ? (a) : (b)


int getDegreeUnsafe(node *tree) {
  int l, r;
  mpfr_t temp;

  if (isConstant(tree)) return 0;

  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
    return 0;
    break;
  case ADD:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return MAX(l,r);
    break;
  case SUB:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return MAX(l,r);
    break;
  case MUL:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return l + r;
    break;
  case DIV:
    return getDegreeUnsafe(tree->child1);
    break;
  case POW:
    {
      l = getDegreeUnsafe(tree->child1);
      if (tree->child2->nodeType != CONSTANT) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occured. The exponent in a power operator is not constant.\n");
	exit(1);
      }
      if (!mpfr_integer_p(*(tree->child2->value))) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occured. The exponent in a power operator is not integer.\n");
	exit(1);
      }
      if (mpfr_sgn(*(tree->child2->value)) < 0) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occured. The exponent in a power operator is negative.\n");
	exit(1);
      }

      r = (int) mpfr_get_d(*(tree->child2->value),GMP_RNDN);
      mpfr_init2(temp,mpfr_get_prec(*(tree->child2->value)) + 10);
      mpfr_set_si(temp,r,GMP_RNDN);
      if (mpfr_cmp(*(tree->child2->value),temp) != 0) {
	printMessage(1,
"Warning: tried to compute polynomial degree of an expression using a power operator with an exponent\n");
	printf("which cannot be represented on a integer variable.\n");
	mpfr_clear(temp);
	return -1;
      }
      mpfr_clear(temp);
      return l * r;
    }
    break;
  case NEG:
    return getDegreeUnsafe(tree->child1);
    break;
  default:
    fprintf(stderr,"Error: getDegreeUnsafe: an error occured on handling the expression tree\n");
    exit(1);
  }
}

int getDegree(node *tree) {
  if (!isPolynomial(tree)) return -1;
  return getDegreeUnsafe(tree);
}





node* makeBinomial(node *a, node *b, int n, int s) {
  node *tree, *coeff, *aPow, *bPow, *tempNode, *tempNode2;
  mpfr_t *coeffVal, *mpfr_temp;
  unsigned int i;
  mpz_t coeffGMP;
  
  tree = (node*) safeMalloc(sizeof(node));
  tree->nodeType = CONSTANT;
  mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*mpfr_temp,tools_precision);
  mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
  tree->value = mpfr_temp;
  mpz_init(coeffGMP);
  for (i=0;i<=((unsigned int) n);i++) {
    mpz_bin_uiui(coeffGMP,(unsigned int) n,i);
    coeffVal = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*coeffVal,tools_precision);
    if(mpfr_set_z(*coeffVal,coeffGMP,GMP_RNDN) != 0) {
      printMessage(1,"Warning: on expanding a power operator a rounding occured when calculating a binomial coefficient.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    if ((s < 0) && ((i & 1) != 0)) {
      mpfr_neg(*coeffVal,*coeffVal,GMP_RNDN);
    }
    coeff = (node*) safeMalloc(sizeof(node));
    coeff->nodeType = CONSTANT;
    coeff->value = coeffVal;
    aPow = (node*) safeMalloc(sizeof(node));
    aPow->nodeType = POW;
    aPow->child1 = copyTree(a);
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    if(mpfr_set_ui(*mpfr_temp,i,GMP_RNDN) != 0) {
      printMessage(1,"Warning: on expanding a power operator a rounding occured when calculating an exponent constant.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    tempNode->value = mpfr_temp;
    aPow->child2 = tempNode;
    bPow = (node*) safeMalloc(sizeof(node));
    bPow->nodeType = POW;
    bPow->child1 = copyTree(b);
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    if(mpfr_set_ui(*mpfr_temp,((unsigned int) n) - i,GMP_RNDN) != 0) {
      printMessage(1,"Warning: on expanding a power operator a rounding occured when calculating an exponent constant.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    tempNode->value = mpfr_temp;
    bPow->child2 = tempNode;
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = MUL;
    tempNode->child1 = coeff;
    tempNode->child2 = aPow;
    tempNode2 = (node*) safeMalloc(sizeof(node));
    tempNode2->nodeType = MUL;
    tempNode2->child1 = tempNode;
    tempNode2->child2 = bPow;
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = ADD;
    tempNode->child1 = tree;
    tempNode->child2 = tempNode2;
    tree = tempNode;
  }
  mpz_clear(coeffGMP);

  return tree;
}


node* expandPowerInPolynomialUnsafe(node *tree) {
  node *copy, *left, *tempTree, *tempTree2, *tempTree3;
  int r, i;
  mpfr_t temp;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    return copyTree(tree);
    break;
  case CONSTANT:
    return copyTree(tree);
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;    
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case POW:
    {
      left = expandPowerInPolynomialUnsafe(tree->child1);
      if (tree->child2->nodeType != CONSTANT) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured. The exponent in a power operator is not constant.\n");
	exit(1);
      }
      if (!mpfr_integer_p(*(tree->child2->value))) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured. The exponent in a power operator is not integer.\n");
	exit(1);
      }
      if (mpfr_sgn(*(tree->child2->value)) < 0) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured. The exponent in a power operator is negative.\n");
	exit(1);
      }

      r = (int) mpfr_get_d(*(tree->child2->value),GMP_RNDN);
      mpfr_init2(temp,mpfr_get_prec(*(tree->child2->value)) + 10);
      mpfr_set_si(temp,r,GMP_RNDN);
      if (mpfr_cmp(*(tree->child2->value),temp) != 0) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured. Tried to expand an expression using a power operator with an exponent\n");
	fprintf(stderr,"which cannot be represented on a integer variable.\n");
	mpfr_clear(temp);
	exit(1);
      }
      mpfr_clear(temp);
      if (r > 1) {
	switch (left->nodeType) {
	case VARIABLE:
	case CONSTANT:
	  tempTree = copyTree(left);
	  for (i=1;i<r;i++) {
	    tempTree2 = (node *) safeMalloc(sizeof(node));
	    tempTree2->nodeType = MUL;
	    tempTree2->child1 = tempTree;
	    tempTree2->child2 = copyTree(left);
	    tempTree = tempTree2;
	  }
	  break;
	case ADD:
	  tempTree = makeBinomial(left->child1,left->child2,r,1);
	  break;
	case SUB:
	  tempTree = makeBinomial(left->child1,left->child2,r,-1);
	  break;
	case MUL:
	  tempTree = (node *) safeMalloc(sizeof(node));
	  tempTree->nodeType = MUL;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child1);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child1 = tempTree2;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child2);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child2 = tempTree2;
	  break;
	case DIV:
	  tempTree = (node *) safeMalloc(sizeof(node));
	  tempTree->nodeType = DIV;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child1);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child1 = tempTree2;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child2);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child2 = tempTree2;
	  break;
	case NEG:
	  if (r & 1) {
	    /* r is odd */
	    tempTree = (node *) safeMalloc(sizeof(node));
	    tempTree->nodeType = NEG;
	    tempTree2 = (node *) safeMalloc(sizeof(node));
	    tempTree2->nodeType = POW;
	    tempTree2->child1 = copyTree(left->child1);
	    tempTree3 = (node*) safeMalloc(sizeof(node));
	    tempTree3->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    mpfr_set_si(*value,r,GMP_RNDN);
	    tempTree3->value = value;
	    tempTree2->child2 = tempTree3;
	    tempTree->child1 = tempTree2;
	  } else {
	    tempTree = (node *) safeMalloc(sizeof(node));
	    tempTree->nodeType = POW;
	    tempTree->child1 = copyTree(left->child1);
	    tempTree3 = (node*) safeMalloc(sizeof(node));
	    tempTree3->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    mpfr_set_si(*value,r,GMP_RNDN);
	    tempTree3->value = value;
	    tempTree->child2 = tempTree3;
	  }
	  break;
	default:
	  if (isConstant(left)) return copyTree(tree);

	  fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured on handling the expanded expression subtree\n");
	  exit(1);
	}
	copy = expandPowerInPolynomialUnsafe(tempTree);
	free_memory(tempTree);
      } else {
	if (r == 1) {
	  copy = copyTree(left);
	} else {
	  copy = (node*) safeMalloc(sizeof(node));
	  copy->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_d(*value,1.0,GMP_RNDN);
	  copy->value = value;
	}
      }
      free_memory(left);
      return copy;
    }
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    return copy;
    break;
  default:

    if (isConstant(tree)) return copyTree(tree);

    fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occured on handling the expression tree\n");
    exit(1);
  }
}

node* expandPowerInPolynomial(node *tree) {
  if (getDegree(tree) < 0) return copyTree(tree);
  return expandPowerInPolynomialUnsafe(tree);
}



node* expandDivision(node *tree) {
  node *copy, *left, *right, *tempNode;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case DIV:
    left = expandDivision(tree->child1);
    right = expandDivision(tree->child2);
    if (right->nodeType == DIV) {
      tempNode = right->child1;
      right->child1 = right->child2;
      right->child2 = tempNode;
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = MUL;
      copy->child1 = left;
      copy->child2 = right;
    } else {
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = DIV;
      copy->child1 = left;
      copy->child2 = right;
    }
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = expandDivision(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = expandDivision(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = expandDivision(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = expandDivision(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: expandDivision: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}



node* expandPolynomialUnsafe(node *tree) {
  node *left, *right, *copy, *tempNode, *tempNode2, *tempNode3, *tempNode4; 
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    return copyTree(tree);
    break;
  case CONSTANT:
    return copyTree(tree);
    break;
  case ADD:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = left;
    copy->child2 = right;
    return copy;    
    break;
  case SUB:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = left;
    copy->child2 = right;
    return copy;
    break;
  case MUL:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    switch (left->nodeType) {
    case VARIABLE:
    case CONSTANT:
      switch (right->nodeType) {
      case VARIABLE:
      case CONSTANT:
	copy = (node*) safeMalloc(sizeof(node));
	copy->nodeType = MUL;
	copy->child1 = left;
	copy->child2 = right;
	break;  
      default:
	tempNode = (node*) safeMalloc(sizeof(node));
	tempNode->nodeType = MUL;
	tempNode->child1 = right;
	tempNode->child2 = left;
	copy = expandPolynomialUnsafe(tempNode);
	free_memory(tempNode);
      }
      break;
    case MUL:
      switch (right->nodeType) {
      case ADD:
      case SUB:
      case NEG:
      case DIV:      
	tempNode = (node*) safeMalloc(sizeof(node));
	tempNode->nodeType = MUL;
	tempNode->child1 = right;
	tempNode->child2 = left;
	copy = expandPolynomialUnsafe(tempNode);
	free_memory(tempNode);
	break;
      default:
	copy = (node*) safeMalloc(sizeof(node));
	copy->nodeType = MUL;
	copy->child1 = left;
	copy->child2 = right;
	break;  
      }
      break;  
    case ADD:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = ADD;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);
      break;
    case SUB:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = SUB;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case NEG:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = NEG;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case DIV:
      if (isConstant(left)) {
	copy = (node*) safeMalloc(sizeof(node));
	copy->nodeType = MUL;
	copy->child1 = left;
	copy->child2 = right;
      } else {
	tempNode = (node*) safeMalloc(sizeof(node));
	tempNode->nodeType = MUL;
	tempNode2 = (node*) safeMalloc(sizeof(node));
	tempNode2->nodeType = MUL;
	tempNode3 = (node*) safeMalloc(sizeof(node));
	tempNode3->nodeType = DIV;
	tempNode4 = (node*) safeMalloc(sizeof(node));
	tempNode4->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	mpfr_set_d(*value,1.0,GMP_RNDN);
	tempNode4->value = value;
	tempNode3->child1 = tempNode4;
	tempNode3->child2 = copyTree(left->child2);
	tempNode2->child1 = copyTree(left->child1);
	tempNode2->child2 = right;
	tempNode->child1 = tempNode3;
	tempNode->child2 = tempNode2;
	free_memory(left);
	copy = expandPolynomialUnsafe(tempNode);
	free_memory(tempNode);
      }      
      break;
    default:
      if (isConstant(left)) {
	return copyTree(tree);
      } else {
	fprintf(stderr,"Error: expandPolynomialUnsafe: an error occured on handling the MUL left rewritten expression subtree\n");
	exit(1);
      }
    }
    return copy;
    break;
  case DIV:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    switch (left->nodeType) {
    case CONSTANT:
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = DIV;
      copy->child1 = left;
      copy->child2 = right;
      break;  
    case VARIABLE:
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = MUL;
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = DIV;
      tempNode->child2 = right;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      tempNode2->value = value;
      tempNode->child1 = tempNode2;
      copy->child2 = left;
      copy->child1 = tempNode;
      break;
    case ADD:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = ADD;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);
      break;
    case SUB:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = SUB;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case MUL:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = MUL;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      tempNode3->value = value;
      tempNode4 = (node*) safeMalloc(sizeof(node));
      tempNode4->nodeType = MUL;
      tempNode2->child1 = tempNode3;
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode4;
      tempNode4->child1 = copyTree(left->child1);
      tempNode4->child2 = copyTree(left->child2);
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case DIV:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = DIV;
      tempNode->child1 = copyTree(left->child1);
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child2);
      tempNode2->child2 = right;
      tempNode->child2 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case NEG:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = NEG;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    default: 
      if (isConstant(left)) {
	return copyTree(tree);
      } else {
	fprintf(stderr,"Error: expandPolynomialUnsafe: an error occured on handling the DIV left rewritten expression subtree\n");
	exit(1);
      }
    }
    return copy;
    break;
  case NEG:
    left = expandPolynomialUnsafe(tree->child1);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = left;
    return copy;
    break;
  default:
    if (isConstant(tree)) {
      return copyTree(tree);
    } else {
      fprintf(stderr,"Error: expandPolynomialUnsafe: an error occured on handling the expression tree\n");
      exit(1);
    }
  }
}



node* expandPolynomial(node *tree) {
  node *temp, *temp2;
  if (getDegree(tree) < 0) return copyTree(tree);
  temp = expandPowerInPolynomialUnsafe(tree);
  temp2 = expandPolynomialUnsafe(temp);
  free_memory(temp);
  return temp2;
}

node* expandUnsimplified(node *tree) {
  node *copy;
  mpfr_t *value;

  if (!isConstant(tree) && isPolynomial(tree)) return expandPolynomial(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = expand(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = expand(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = expand(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = expand(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = expand(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = expand(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = expand(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = expand(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = expand(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = expand(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = expand(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = expand(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = expand(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = expand(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = expand(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expand(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = expand(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = expand(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = expand(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: expand: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}

node* expand(node *tree) {
  node *temp, *temp2, *temp3;

  temp3 = expandDivision(tree);
  temp = expandUnsimplified(temp3);
  temp2 = simplifyTreeErrorfree(temp);
  free_memory(temp);
  free_memory(temp3);
  return temp2;
}



int isConstant(node *tree) {
 switch (tree->nodeType) {
  case VARIABLE:
    return 0;
    break;
  case CONSTANT:
    return 1;
    break;
  case ADD:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
 case SUB:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case MUL:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case DIV:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case SQRT:
    return isConstant(tree->child1);
    break;
  case EXP:
    return isConstant(tree->child1);
    break;
  case LOG:
    return isConstant(tree->child1);
    break;
  case LOG_2:
    return isConstant(tree->child1);
    break;
  case LOG_10:
    return isConstant(tree->child1);
    break;
  case SIN:
    return isConstant(tree->child1);
    break;
  case COS:
    return isConstant(tree->child1);
    break;
  case TAN:
    return isConstant(tree->child1);
    break;
  case ASIN:
    return isConstant(tree->child1);
    break;
  case ACOS:
    return isConstant(tree->child1);
    break;
  case ATAN:
    return isConstant(tree->child1);
    break;
  case SINH:
    return isConstant(tree->child1);
    break;
  case COSH:
    return isConstant(tree->child1);
    break;
  case TANH:
    return isConstant(tree->child1);
    break;
  case ASINH:
    return isConstant(tree->child1);
    break;
  case ACOSH:
    return isConstant(tree->child1);
    break;
  case ATANH:
    return isConstant(tree->child1);
    break;
  case POW:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case NEG:
    return isConstant(tree->child1);
    break;
  case ABS:
    return isConstant(tree->child1);
    break;
  case DOUBLE:
    return isConstant(tree->child1);
    break;
  case DOUBLEDOUBLE:
    return isConstant(tree->child1);
    break;
  case TRIPLEDOUBLE:
    return isConstant(tree->child1);
    break;
  case ERF:
    return isConstant(tree->child1);
    break;
  case ERFC:
    return isConstant(tree->child1);
    break;
  case LOG_1P:
    return isConstant(tree->child1);
    break;
  case EXP_M1:
    return isConstant(tree->child1);
    break;
  case DOUBLEEXTENDED:
    return isConstant(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: isConstant: unknown identifier in the tree\n");
   exit(1);
  }
}



int isMonomial(node *tree) {

  switch (tree->nodeType) {
  case MUL:
    return (isMonomial(tree->child1) & isMonomial(tree->child2));
    break;
  case NEG:
    return isMonomial(tree->child1);
    break;
  case VARIABLE:
    return 1;
    break;
  default: 
    return isConstant(tree);
  }
  return 0;
}



node* getCoefficientsInMonomialUnsafe(node *polynom) {
  node *leftSub, *rightSub, *coeffs;
  mpfr_t *value;

  if (isConstant(polynom)) return copyTree(polynom);

  if (polynom->nodeType == VARIABLE) return NULL;
 
  if (polynom->nodeType == MUL) {
    leftSub = getCoefficientsInMonomialUnsafe(polynom->child1);
    rightSub = getCoefficientsInMonomialUnsafe(polynom->child2);
    if ((leftSub == NULL) && (rightSub == NULL)) return NULL;
    if (leftSub == NULL) return rightSub;
    if (rightSub == NULL) return leftSub;
    coeffs = (node*) safeMalloc(sizeof(node));
    coeffs->nodeType = MUL;
    coeffs->child1 = leftSub;
    coeffs->child2 = rightSub;
    return coeffs;
  }

  if (polynom->nodeType == NEG) {
    leftSub = getCoefficientsInMonomialUnsafe(polynom->child1);
    rightSub = (node *) safeMalloc(sizeof(node));
    rightSub->nodeType = CONSTANT;
    value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set_d(*value,-1.0,GMP_RNDN);
    rightSub->value = value;
    if (leftSub == NULL) return rightSub;
    coeffs = (node*) safeMalloc(sizeof(node));
    coeffs->nodeType = MUL;
    coeffs->child1 = leftSub;
    coeffs->child2 = rightSub;
    return coeffs;
  }

  fprintf(stderr,"Error: getCoefficientsInMonomialUnsafe: an error occured. The expression does not have the correct monomial form.\n");
  exit(1);
  return NULL;
}


void getCoefficientsUnsafe(node **monomials, node *polynom, int sign) {
  int degree;
  node *temp, *coeff, *temp2;
  mpfr_t *value;
 
  if (isMonomial(polynom)) {
    degree = getDegree(polynom);
    coeff = getCoefficientsInMonomialUnsafe(polynom);
    if (coeff == NULL) {
      coeff = (node *) safeMalloc(sizeof(node));
      coeff->nodeType = CONSTANT;
      value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      coeff->value = value;
    }
    temp = monomials[degree];
    if (temp == NULL) {
      if (sign < 0) {
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = NEG;
	temp2->child1 = coeff;
	coeff = temp2;
      }
      temp = coeff;
    } else {
      temp2 = (node*) safeMalloc(sizeof(node));
      if (sign > 0) temp2->nodeType = ADD; else temp2->nodeType = SUB;
      temp2->child1 = temp;
      temp2->child2 = coeff;
      temp = temp2;
    }
    monomials[degree] = temp;
    return;
  }

  if (polynom->nodeType == ADD) {
    getCoefficientsUnsafe(monomials,polynom->child1,sign);
    getCoefficientsUnsafe(monomials,polynom->child2,sign);
    return;
  }

  if (polynom->nodeType == SUB) {
    getCoefficientsUnsafe(monomials,polynom->child1,sign);
    getCoefficientsUnsafe(monomials,polynom->child2,-sign);
    return;
  }

  if (polynom->nodeType == NEG) {
    getCoefficientsUnsafe(monomials,polynom->child1,-sign);
    return;
  }

  fprintf(stderr,"Error: getCoefficientsUnsafe: an error occured. The given polynomial is neither a monomial nor a sum of monomials\n");
  exit(1);
}


void getCoefficients(int *degree, node ***coefficients, node *poly) {
  node *temp, *temp2, *temp3, *temp4;
  int i;

  *degree = getDegree(poly);
  if (*degree < 0) {
    printMessage(1,"Warning: Tried to get coefficients of an expression that is not a polynomial.\n");
    return;
  }

  temp = simplifyTreeErrorfree(poly);
  temp2 = expandPowerInPolynomialUnsafe(temp);
  temp3 = expandPolynomialUnsafe(temp2);
  temp4 = simplifyTreeErrorfree(temp3);

  *coefficients = (node**) safeCalloc((*degree + 1),sizeof(node*));
  for (i=0;i<=*degree;i++) (*coefficients)[i] = NULL;

  getCoefficientsUnsafe(*coefficients,temp4,1);

  free_memory(temp);
  free_memory(temp2);
  free_memory(temp3);
  free_memory(temp4);
}



node* hornerPolynomialUnsafe(node *tree) {
  node *copy, *temp, *temp2, *temp3, *temp4, *simplified;
  node **monomials;
  int degree, i, k, e;
  mpfr_t *value;
  
  simplified = simplifyTreeErrorfree(tree);

  degree = getDegree(simplified);
  monomials = (node**) safeCalloc((degree + 1),sizeof(node*));
  for (i=0;i<=degree;i++) monomials[i] = NULL;
  
  getCoefficientsUnsafe(monomials,simplified,1);

  if (monomials[degree] == NULL) {
    fprintf(stderr,
"Error: hornerPolynomialUnsafe: an error occured. The coefficient of a monomial with the polynomial's degree exponent is zero.\n");
    exit(1);
    return NULL;
  }

  copy = copyTree(monomials[degree]);

  for (i=degree-1;i>=0;i--) {
    if (monomials[i] == NULL) {
      if ((i == 0)) {
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp->child1 = temp2;
	temp->child2 = copy;
	copy = temp;
      } else {
	for (k=i-1;((monomials[k]==NULL) && (k > 0));k--);
	e = (i - k) + 1;
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp3 = (node *) safeMalloc(sizeof(node));
	temp3->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,e,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: rounding occured on representing a monomial power exponent with %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp3->value = value;
	temp4 = (node *) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp2;
	temp4->child2 = temp3;
	temp->child1 = temp4;
	temp->child2 = copy;
	copy = temp;
	if (monomials[k] != NULL) {
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = ADD;
	  temp->child1 = copyTree(monomials[k]);
	  temp->child2 = copy;
	  copy = temp;
	}
	i = k;
      }
    } else {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = MUL;
      temp2 = (node *) safeMalloc(sizeof(node));
      temp2->nodeType = VARIABLE;
      temp->child1 = temp2;
      temp->child2 = copy;
      copy = temp;
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = ADD;
      temp->child1 = copyTree(monomials[i]);
      temp->child2 = copy;
      copy = temp;
    }
  }
  

  for (i=0;i<=degree;i++) {
    if (monomials[i] != NULL) free_memory(monomials[i]);
  }
  free(monomials);

  free_memory(simplified);
  return copy;
}

node* hornerPolynomial(node *tree) {
  node *temp, *temp2, *temp3, *temp4;
  if (isConstant(tree)) return copyTree(tree);
  if (getDegree(tree) < 0) return copyTree(tree);
  temp4 = simplifyTreeErrorfree(tree);
  temp = expandPowerInPolynomialUnsafe(temp4);
  temp2 = expandPolynomialUnsafe(temp);
  temp3 = hornerPolynomialUnsafe(temp2);
  free_memory(temp);
  free_memory(temp2);
  free_memory(temp4);
  return temp3;
}


node* hornerUnsimplified(node *tree) {
  node *copy;
  mpfr_t *value;

  if (isPolynomial(tree)) return hornerPolynomial(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = horner(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = horner(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = horner(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = horner(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = horner(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = horner(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = horner(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = horner(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = horner(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = horner(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = horner(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = horner(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = horner(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = horner(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = horner(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = horner(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = horner(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = horner(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = horner(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: horner: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


node* horner(node *tree) {
  node *temp, *temp2, *temp3;

  temp3 = simplifyTreeErrorfree(tree);
  temp = hornerUnsimplified(temp3);
  temp2 = simplifyTreeErrorfree(temp);
  free_memory(temp);
  free_memory(temp3);
  return temp2;
}




node *differentiatePolynomialUnsafe(node *tree) {
  node *simplifiedTemp, *simplified, *copy, *temp, *temp2, *temp3, *temp4, *temp5;
  int degree, i;
  node **monomials;
  mpfr_t *value;

  simplifiedTemp = expandPowerInPolynomialUnsafe(tree);
  simplified = expandPolynomialUnsafe(simplifiedTemp);

  degree = getDegree(simplified);

  if (degree == 0) {
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set_d(*value,0.0,GMP_RNDN);
    copy->value = value;
  } else {

    monomials = (node**) safeCalloc((degree + 1),sizeof(node*));
    for (i=0;i<=degree;i++) monomials[i] = NULL;
    
   
    getCoefficientsUnsafe(monomials,simplified,1);
 
  
    if (monomials[degree] == NULL) {
      fprintf(stderr,
	     "Error: differentiatePolynomialUnsafe: an error occured. The coefficient of a monomial with the polynomial's degree exponent is zero.\n"
	     );
      exit(1);
      return NULL;
    }
    
    
    if (degree >= 2) {
      if (degree > 2) {
	temp = copyTree(monomials[degree]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: rounding occured on differentiating a polynomial. A constant could not be written on %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp2->value = value;
	temp3 = (node*) safeMalloc(sizeof(node));
	temp3->nodeType = MUL;
	temp3->child1 = temp2;
	temp3->child2 = temp;
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree-1,GMP_RNDN) != 0) {
	  printMessage(1,
		 "Warning: rounding occured on differentiating a polynomial. An exponent constant could not be written on %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp2->value = value;
	temp = (node*) safeMalloc(sizeof(node));
	temp->nodeType = VARIABLE;
	temp4 = (node*) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp;
	temp4->child2 = temp2;
	temp5 = (node*) safeMalloc(sizeof(node));
	temp5->nodeType = MUL;
	temp5->child1 = temp3;
	temp5->child2 = temp4;
	copy = temp5;
      } else {
	temp = copyTree(monomials[degree]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: rounding occured on differentiating a polynomial. A constant could not be written on %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp2->value = value;
	temp3 = (node*) safeMalloc(sizeof(node));
	temp3->nodeType = MUL;
	temp3->child1 = temp2;
	temp3->child2 = temp;
	temp = (node*) safeMalloc(sizeof(node));
	temp->nodeType = VARIABLE;
	temp4 = (node*) safeMalloc(sizeof(node));
	temp4->nodeType = MUL;
	temp4->child1 = temp3;
	temp4->child2 = temp;
	copy = temp4;
      }
          
      for (i=degree-1;i>1;i--) {
	if (monomials[i] != NULL) {
	  temp = copyTree(monomials[i]);
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  if (mpfr_set_si(*value,i,GMP_RNDN) != 0) {
	    printMessage(1,"Warning: rounding occured on differentiating a polynomial. A constant could not be written on %d bits.\n",
		   (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	  temp2->value = value;
	  temp3 = (node*) safeMalloc(sizeof(node));
	  temp3->nodeType = MUL;
	  temp3->child1 = temp2;
	  temp3->child2 = temp;
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  if (mpfr_set_si(*value,i-1,GMP_RNDN) != 0) {
	    printMessage(1,
		   "Warning: rounding occured on differentiating a polynomial. An exponent constant could not be written on %d bits.\n",
		   (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	  temp2->value = value;
	  temp = (node*) safeMalloc(sizeof(node));
	  temp->nodeType = VARIABLE;
	  temp4 = (node*) safeMalloc(sizeof(node));
	  temp4->nodeType = POW;
	  temp4->child1 = temp;
	  temp4->child2 = temp2;
	  temp5 = (node*) safeMalloc(sizeof(node));
	  temp5->nodeType = MUL;
	  temp5->child1 = temp3;
	  temp5->child2 = temp4;
	  temp = copy;
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = ADD;
	  temp2->child1 = temp5;
	  temp2->child2 = temp;
	  copy = temp2;      
	} 
      }
      
      if (monomials[1] != NULL) {
	temp = copyTree(monomials[1]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = ADD;
	temp2->child1 = temp;
	temp2->child2 = copy;
	copy = temp2;      
      } 
    } else {
      copy = copyTree(monomials[1]);
    }
  
    for (i=0;i<=degree;i++) {
      if (monomials[i] != NULL) free_memory(monomials[i]);
    }
    free(monomials);
  } 
  free_memory(simplifiedTemp);
  free_memory(simplified);

  return copy;
}


int getNumeratorDenominator(node **numerator, node **denominator, node *tree) {
  if (tree->nodeType == DIV) {
    *numerator = copyTree(tree->child1);
    *denominator = copyTree(tree->child2);
    return 1;
  }
  else {
    *numerator = copyTree(tree);
    *denominator = NULL;
    return 0;
  }
}


node *substitute(node* tree, node *t) {
  node *copy;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = copyTree(t);
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,mpfr_get_prec(*(tree->value)));
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = substitute(tree->child1,t);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = substitute(tree->child1,t);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = substitute(tree->child1,t);
    break;
  default:
   fprintf(stderr,"Error: substitute: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


int readDyadic(mpfr_t res, char *c) {
  char *mantissa, *exponent, *curr, *curr2;  
  mpfr_t mant, expo, temp1, temp2;
  mp_prec_t prec;
  int rounding;

  mantissa = (char *) safeCalloc(strlen(c)+1,sizeof(char));
  exponent = (char *) safeCalloc(strlen(c)+1,sizeof(char));
  curr = c; curr2 = mantissa;
  while ((*curr != '\0') && (*curr != 'b') && (*curr != 'B')) {
    *curr2 = *curr;
    curr2++;
    curr++;
  }
  if (*curr != '\0') curr++;
  curr2 = exponent;
  while (*curr != '\0') {
    *curr2 = *curr;
    curr2++;
    curr++;
  }

  rounding = 1;

  prec = mpfr_get_prec(res);
  mpfr_init2(mant,prec);
  mpfr_init2(expo,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec); 

  mpfr_set_str(temp1,mantissa,10,GMP_RNDU);
  mpfr_set_str(temp2,mantissa,10,GMP_RNDD);
  if (mpfr_cmp(temp1,temp2) != 0) {
    rounding = 0;
    mpfr_set_str(temp1,mantissa,10,GMP_RNDN);
  }
  if (mpfr_set(mant,temp1,GMP_RNDN) != 0) {
    rounding = 0;
  }
  mpfr_set_str(temp1,exponent,10,GMP_RNDU);
  mpfr_set_str(temp2,exponent,10,GMP_RNDD);
  if (mpfr_cmp(temp1,temp2) != 0) {
    rounding = 0;
    mpfr_set_str(temp1,exponent,10,GMP_RNDN);
  }
  if (mpfr_exp2(expo,temp1,GMP_RNDN) != 0) {
    rounding = 0;
  }
  if (mpfr_mul(res,mant,expo,GMP_RNDN) != 0) {
    rounding = 0;
  }
 
  if (!mpfr_number_p(res)) rounding = 1;

  mpfr_clear(mant);
  mpfr_clear(expo);
  mpfr_clear(temp1);
  mpfr_clear(temp2);
  free(mantissa);
  free(exponent);
  return rounding;
}

void *copyTreeOnVoid(void *tree) {
  return copyTree((node *) tree);
}

void freeMemoryOnVoid(void *tree) {
  free_memory((node *) tree);
}

void freeRangetypePtr(void *ptr) {
  mpfr_clear(*(((rangetype *) ptr)->a));
  mpfr_clear(*(((rangetype *) ptr)->b));
  free(((rangetype *) ptr)->a);
  free(((rangetype *) ptr)->b);
  free(ptr);
}

void *copyRangetypePtr(void *ptr) {
  rangetype *newPtr;

  newPtr = (rangetype *) safeMalloc(sizeof(rangetype));
  newPtr->a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  newPtr->b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));

  mpfr_init2(*(newPtr->a),mpfr_get_prec(*(((rangetype *) ptr)->a)));
  mpfr_init2(*(newPtr->b),mpfr_get_prec(*(((rangetype *) ptr)->b)));

  mpfr_set(*(newPtr->a),*(((rangetype *) ptr)->a),GMP_RNDN);
  mpfr_set(*(newPtr->b),*(((rangetype *) ptr)->b),GMP_RNDN);

  return newPtr;
}

node *makePolynomial(mpfr_t *coefficients, int degree) {
  node *tempTree, *tempTree2, *tempTree3;
  int i;
  
  tempTree = (node *) safeMalloc(sizeof(node));
  tempTree->nodeType = CONSTANT;
  tempTree->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempTree->value),mpfr_get_prec(coefficients[degree]));
  mpfr_set(*(tempTree->value),coefficients[degree],GMP_RNDN);
  for (i=degree-1;i>=0;i--) {
    tempTree2 = (node *) safeMalloc(sizeof(node));
    tempTree2->nodeType = MUL;
    tempTree3 = (node *) safeMalloc(sizeof(node));
    tempTree3->nodeType = VARIABLE;
    tempTree2->child1 = tempTree3;
    tempTree2->child2 = tempTree;
    tempTree = (node *) safeMalloc(sizeof(node));
    tempTree->nodeType = ADD;
    tempTree->child2 = tempTree2;
    tempTree3 = (node *) safeMalloc(sizeof(node));
    tempTree3->nodeType = CONSTANT;
    tempTree3->value = (mpfr_t *) safeMalloc(sizeof(node));
    mpfr_init2(*(tempTree3->value),mpfr_get_prec(coefficients[i]));
    mpfr_set(*(tempTree3->value),coefficients[i],GMP_RNDN);
    tempTree->child1 = tempTree3;
  }
  tempTree2 = horner(tempTree);
  free_memory(tempTree);
  return tempTree2;
}


int treeSize(node *tree) {
  if (tree == NULL) return 0;
  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
    return 1;
    break;
  case ADD:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case SUB:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case MUL:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case DIV:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case SQRT:
    return treeSize(tree->child1) + 1;
    break;
  case EXP:
    return treeSize(tree->child1) + 1;
    break;
  case LOG:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_2:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_10:
    return treeSize(tree->child1) + 1;
    break;
  case SIN:
    return treeSize(tree->child1) + 1;
    break;
  case COS:
    return treeSize(tree->child1) + 1;
    break;
  case TAN:
    return treeSize(tree->child1) + 1;
    break;
  case ASIN:
    return treeSize(tree->child1) + 1;
    break;
  case ACOS:
    return treeSize(tree->child1) + 1;
    break;
  case ATAN:
    return treeSize(tree->child1) + 1;
    break;
  case SINH:
    return treeSize(tree->child1) + 1;
    break;
  case COSH:
    return treeSize(tree->child1) + 1;
    break;
  case TANH:
    return treeSize(tree->child1) + 1;
    break;
  case ASINH:
    return treeSize(tree->child1) + 1;
    break;
  case ACOSH:
    return treeSize(tree->child1) + 1;
    break;
  case ATANH:
    return treeSize(tree->child1) + 1;
    break;
  case POW:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case NEG:
    return treeSize(tree->child1) + 1;
    break;
  case ABS:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLEDOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case TRIPLEDOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case ERF:
    return treeSize(tree->child1) + 1;
    break;
  case ERFC:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_1P:
    return treeSize(tree->child1) + 1;
    break;
  case EXP_M1:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLEEXTENDED:
    return treeSize(tree->child1) + 1;
    break;
  default:
   fprintf(stderr,"Error: treeSize: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return -1;
}



int highestDegreeOfPolynomialSubexpression(node *tree) {
  int l, r;

  if (isPolynomial(tree)) return getDegree(tree);

  switch (arity(tree)) {
  case 2:
    l = highestDegreeOfPolynomialSubexpression(tree->child1);
    r = highestDegreeOfPolynomialSubexpression(tree->child2);
    return l > r ? l : r;
    break;
  case 1:
    return highestDegreeOfPolynomialSubexpression(tree->child1);
    break;
  case 0:
    return getDegree(tree);
    break;
  default: 
    fprintf(stderr,"Error: unknown arity of an operator.\n");
    exit(1);
  }

  return -1;
}



node *getIthCoefficient(node *poly, int i) {
  node *tempNode;
  node **coefficients;
  int degree, k;

  if ((!isPolynomial(poly)) || (i < 0)) {
    tempNode = (node *) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(tempNode->value),10);
    mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
    return tempNode;
  } 

  getCoefficients(&degree, &coefficients, poly);

  if ((i > degree) || (coefficients[i] == NULL)) {
    tempNode = (node *) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(tempNode->value),10);
    mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
  } else {
    tempNode = copyTree(coefficients[i]);
  }
  
  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) free_memory(coefficients[k]);
  }

  free(coefficients);

  return tempNode;
}


node *getSubpolynomial(node *poly, chain *monomials, int fillDegrees, mp_prec_t prec) {
  node *tempNode, *tempNode2, *tempNode3;
  node **coefficients;
  int degree, k, currDeg, maxDegree;
  chain *curr;

  tempNode = (node *) safeMalloc(sizeof(node));
  tempNode->nodeType = CONSTANT;
  tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempNode->value),prec);
  mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);

  if (!isPolynomial(poly)) {
    return tempNode;
  } 

  getCoefficients(&degree, &coefficients, poly);

  curr = monomials;

  tempNode = (node *) safeMalloc(sizeof(node));
  tempNode->nodeType = CONSTANT;
  tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempNode->value),prec);
  mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);  

  maxDegree = -1;

  while (curr != NULL) {
    currDeg = *((int *) (curr->value));
    if (currDeg > maxDegree) maxDegree = currDeg;
    if ((currDeg >= 0) && (currDeg <= degree) && (coefficients[currDeg] != NULL)) {
      tempNode2 = (node *) safeMalloc(sizeof(node));
      tempNode2->nodeType = POW;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = CONSTANT;
      tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(tempNode3->value),prec);
      if (mpfr_set_si(*(tempNode3->value),currDeg,GMP_RNDN) != 0) {
	printMessage(1,"Warning: during subpolynomial extraction, the exponent of a power could not be represented exactly on with the given precision.\n");
      }
      tempNode2->child2 = tempNode3;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = VARIABLE;
      tempNode2->child1 = tempNode3;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode3->child2 = tempNode2;
      tempNode3->child1 = copyTree(coefficients[currDeg]);
      tempNode2 = (node *) safeMalloc(sizeof(node));
      tempNode2->nodeType = ADD;
      tempNode2->child2 = tempNode3;
      tempNode2->child1 = tempNode;
      tempNode = tempNode2;
    }
    curr = curr->next;
  }

  if (fillDegrees) {
    for (k=maxDegree+1;k<=degree;k++) {
      if (coefficients[k] != NULL) {
	tempNode2 = (node *) safeMalloc(sizeof(node));
	tempNode2->nodeType = POW;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = CONSTANT;
	tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(tempNode3->value),prec);
	if (mpfr_set_si(*(tempNode3->value),k,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: during subpolynomial extraction, the exponent of a power could not be represented exactly on with the given precision.\n");
	}
	tempNode2->child2 = tempNode3;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = VARIABLE;
	tempNode2->child1 = tempNode3;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = MUL;
	tempNode3->child2 = tempNode2;
	tempNode3->child1 = copyTree(coefficients[k]);
	tempNode2 = (node *) safeMalloc(sizeof(node));
	tempNode2->nodeType = ADD;
	tempNode2->child2 = tempNode3;
	tempNode2->child1 = tempNode;
	tempNode = tempNode2;
      }
    }
  }


  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) free_memory(coefficients[k]);
  }

  free(coefficients);

  tempNode2 = horner(tempNode);

  free_memory(tempNode);
  
  return tempNode2;
}

node *makeCanonicalPolyUnsafe(node *poly, mp_prec_t prec) {
  node **coefficients;
  int degree, k;
  node *tempNode, *tempNode2, *tempNode3;

  getCoefficients(&degree, &coefficients, poly);

  tempNode = (node *) safeMalloc(sizeof(node));
  tempNode->nodeType = CONSTANT;
  tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempNode->value),prec);
  mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) {
      if (k == 0) {
	tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = ADD;
	  tempNode2->child2 = coefficients[k];
	  tempNode2->child1 = tempNode;
	  tempNode = tempNode2;
      } else {
	if (k == 1) {
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = VARIABLE;
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = MUL;
	  tempNode2->child2 = tempNode3;
	  tempNode2->child1 = coefficients[k];
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = ADD;
	  tempNode3->child2 = tempNode2;
	  tempNode3->child1 = tempNode;
	  tempNode = tempNode3;
	} else {
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = POW;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = CONSTANT;
	  tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(tempNode3->value),prec);
	  if (mpfr_set_si(*(tempNode3->value),k,GMP_RNDN) != 0) {
	    printMessage(1,"Warning: during transformation to canonical form, the exponent of a power could not be represented exactly on with the given precision.\n");
	  }
	  tempNode2->child2 = tempNode3;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = VARIABLE;
	  tempNode2->child1 = tempNode3;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = MUL;
	  tempNode3->child2 = tempNode2;
	  tempNode3->child1 = coefficients[k];
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = ADD;
	  tempNode2->child2 = tempNode3;
	  tempNode2->child1 = tempNode;
	  tempNode = tempNode2;
	}
      }
    }
  }

  tempNode2 = simplifyTreeErrorfree(tempNode);

  return tempNode2;
}

node *makeCanonical(node *tree, mp_prec_t prec) {
  node *copy;
  mpfr_t *value;

  if (isPolynomial(tree)) return makeCanonicalPolyUnsafe(tree,prec);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set(*value,*(tree->value),GMP_RNDN);
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ERF: 
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  default:
   fprintf(stderr,"Error: makeCanonical: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}

