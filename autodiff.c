/*
  For compiling this file:
    gcc -fPIC -Wall -c autodiff.c
    gcc -fPIC -shared -o autodiff autodiff.o


  Within Sollya:
    > externalproc(AD, "./autodiff", (function, range, integer) -> list of range);
    AD(function, range, integer) -> list of range

  And then, for instance:
    > AD(exp(x)*cos(x), [2.5; 2.6], 10);

*/


#include "sollya.h"
extern int mpfi_pow(mpfi_t res, mpfi_t x, mpfi_t y);

/* This function performs the differentiation.
   See the commentaries below.
*/
void auto_diff(mpfi_t* res, node *f, mpfi_t x, int n);


int AD(chain **res, void **args) {
  node *f;
  mpfi_t x;
  int i,n;
  mpfi_t *res_array;
  mpfi_t *temp;

  f = (node *)args[0];
  n = *( (int *)args[2] );

  res_array = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  for(i=0;i<=n;i++) mpfi_init2(res_array[i], getToolPrecision());

  
  mpfi_init2(x, getToolPrecision());
  mpfi_set(x, *( (mpfi_t *)args[1] ));

  auto_diff(res_array, f, x, n);

  *res = NULL;
  for(i=n;i>=0;i--) {
    temp = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp, getToolPrecision());
    mpfi_set(*temp, res_array[i]);
    *res = addElement(*res, temp);
  }
  
  free(res_array);
  mpfi_clear(x);
	   
  return 1;
}




void baseFunction_diff(mpfi_t *res2, int nodeType, mpfi_t x, int n) {
  switch(nodeType) {
  case SQRT:
    break;
  case EXP:
    break;
  case LOG:
    break;
  case LOG_2:
    break;
  case LOG_10:
    break;
  case SIN:
    break;
  case COS:
    break;
  case TAN:
    break;
  case ASIN:
    break;
  case ACOS:
    break;
  case ATAN:
    break;
  case SINH:
    break;
  case COSH:
    break;
  case TANH:
    break;
  case ASINH:
    break;
  case ACOSH:
    break;
  case ATANH:
    break;
  case ABS:
    break;
  case DOUBLE:
    break;
  case DOUBLEDOUBLE:
    break;
  case TRIPLEDOUBLE:
    break;
  case ERF:
    break; 
  case ERFC:
    break;
  case LOG_1P:
    break;
  case EXP_M1:
    break;
  case DOUBLEEXTENDED:
    break;
  case CEIL:
    break;
  case FLOOR:
    break;
  default:
    fprintf(stderr,"Error: AD: unknown unary function (%d) in the tree\n",nodeType);
    exit(1);
  }

  return;
}

/* Computes the successive derivatives of y -> y^q at point x */ 
void integerPower_diff(mpfi_t *res, int p, mpfi_t x, int n) {
  int i,k;
  mpfi_t pminusk, y, acc;

  mpfi_init2(pminusk, getToolPrecision());
  mpfi_init2(y, getToolPrecision());
  mpfi_init2(acc, getToolPrecision());

  if(p==0) {
    mpfi_set_ui(res[0], 1);
    for(i=1; i<=n; i++) mpfi_set_ui(res[i], 0);
  }
  else {
    if( (p>0) && (p <= n)) k=p;
    else k=n;

    for(i=n;i>=k+1;i--)  mpfi_set_ui(res[i], 0);

    mpfi_set_si(pminusk, p-k); 
    mpfi_pow(y, x, pminusk);
    for(i=k;i>=0;i--) {
      mpfi_set(res[i], y);
      mpfi_mul(y, y, x);
    }
    
    mpfi_set_si(acc, p);
    for(i=1;i<=k;i++) {
      mpfi_mul(res[i], res[i], acc);
      mpfi_mul_si(acc, acc, p-i);
    }
  }

  mpfi_clear(pminusk);
  mpfi_clear(y);
  mpfi_clear(acc);

  return;
}

void multiplication_AD(mpfi_t *res, mpfi_t *f, mpfi_t *g, int n) {
  return;
}

void composition_AD(mpfi_t *res, mpfi_t *g, mpfi_t *f, int n) {
  mpfi_t *temp_array;
  int i;

  if(n==0) mpfi_set(res[0], g[0]);
  else {
    temp_array = (mpfi_t *)safeMalloc(n*sizeof(mpfi_t));
    for(i=0;i<=n-1;i++) {
      mpfi_init2(temp_array[i], getToolPrecision());
    }

    composition_AD(temp_array, g+1, f, n-1);
    multiplication_AD(res+1, temp_array, f+1, n-1);
    mpfi_set(res[0], g[0]);

    for(i=0;i<=n-1;i++) mpfi_clear(temp_array[i]);
    free(temp_array);
  }

  return ;
}


/* res is a reserved space for n+1 mpfi_t such that:
   res = [ f(x), f'(x), f''(x), ..., f^(n)(x) ]
*/
void auto_diff(mpfi_t* res, node *f, mpfi_t x, int n) {
  int i;
  mpfi_t *res1, *res2, *res3, *res4;
  
  switch (f->nodeType) {

  case VARIABLE:
    mpfi_set(res[0], x);
    if(n>=1) {
      mpfi_set_ui(res[1], 1);
      for(i=2;i<=n;i++) mpfi_set_ui(res[i], 0);
    }
    break;

  case PI_CONST:
    mpfi_const_pi(res[0]);
    for(i=1;i<=n;i++) mpfi_set_ui(res[i], 0);
    break;

  case CONSTANT:
    mpfi_set_fr(res[0], *(f->value));
    for(i=1;i<=n;i++) mpfi_set_ui(res[i], 0);
    break;

  case NEG:
    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
    }
    auto_diff(res1, f->child1, x, n);
    for(i=0;i<=n;i++)  mpfi_neg(res[i], res1[i]);

    for(i=0;i<=n;i++) mpfi_clear(res1[i]);
    free(res1);

    break;

  case ADD:
    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
      mpfi_init2(res2[i], getToolPrecision());
    }
    auto_diff(res1, f->child1, x, n);
    auto_diff(res2, f->child2, x, n);
    for(i=0;i<=n;i++)  mpfi_add(res[i], res1[i], res2[i]);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
    }
    free(res1);
    free(res2);

    break;

  case SUB:
    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
      mpfi_init2(res2[i], getToolPrecision());
    }
    auto_diff(res1, f->child1, x, n);
    auto_diff(res2, f->child2, x, n);
    for(i=0;i<=n;i++)  mpfi_sub(res[i], res1[i], res2[i]);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
    }
    free(res1);
    free(res2);

    break;

  case MUL:
    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
      mpfi_init2(res2[i], getToolPrecision());
    }
    auto_diff(res1, f->child1, x, n);
    auto_diff(res2, f->child2, x, n);

    multiplication_AD(res, res1, res2, n);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
    }
    free(res1);
    free(res2);
    break;

  case DIV:
    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res3 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res4 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
      mpfi_init2(res2[i], getToolPrecision());
      mpfi_init2(res3[i], getToolPrecision());
      mpfi_init2(res4[i], getToolPrecision());
    }

    auto_diff(res1, f->child2, x, n);

    integerPower_diff(res2, -1, res1[0], n);
    composition_AD(res3, res2, res1, n);

    auto_diff(res4, f->child1, x, n);
    multiplication_AD(res, res3, res4, n);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
      mpfi_clear(res3[i]);
      mpfi_clear(res4[i]);
    }
    free(res1);
    free(res2);
    free(res3);
    free(res4);

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

    res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
    for(i=0;i<=n;i++) {
      mpfi_init2(res1[i], getToolPrecision());
      mpfi_init2(res2[i], getToolPrecision());
    }

    auto_diff(res1, f->child1, x, n);
    baseFunction_diff(res2, f->nodeType, res1[0], n);
    composition_AD(res, res2, res1, n);

    for(i=0;i<=n;i++) {
      mpfi_clear(res1[i]);
      mpfi_clear(res2[i]);
    }
    free(res1);
    free(res2);
    

  case POW:
    break;

  case LIBRARYFUNCTION:
    break;

  default:
   fprintf(stderr,"Error: AD: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }

  return;
}
