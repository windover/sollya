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
extern void fprintInterval(FILE *fd, mpfi_t interval);


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


/* Computes the successive derivatives of y -> y^p at point x */ 
/* [x^p    p*x^(p-1)   ...   p*(p-1)*...*(p-n+1)*x^(p-n) ]    */
void constantPower_diff(mpfi_t *res, mpfr_t p, mpfi_t x, int n) {
  mpfi_t expo, acc;
  int i;
  
  /* The precision of expo is set in such a way that expo will
     be a point interval during the algorithm */
  mpfi_init2(expo, mpfr_get_prec(p)+8*sizeof(int));
  mpfi_init2(acc, getToolPrecision());
  
  mpfi_set_fr(expo, p);
  mpfi_set_ui(acc, 1);
  
  for(i=0; i<=n; i++) {
    if (mpfi_is_zero(acc)) mpfi_set_ui(res[i],0);
    else {
      mpfi_pow(res[i], x, expo);
      mpfi_mul(res[i], res[i], acc);
      
      mpfi_mul(acc, acc, expo);
      mpfi_sub_ui(expo, expo, 1);
    }
  }

  mpfi_clear(expo);
  mpfi_clear(acc);

  return;
}


void exp_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t temp;

  mpfi_init2(temp, getToolPrecision());

  mpfi_exp(temp, x);
  for(i=0;i<=n;i++) mpfi_set(res[i], temp);

  mpfi_clear(temp);
  return;
}

void log_diff(mpfi_t *res, mpfi_t x, int n) {
  mpfr_t minusOne;
  
  mpfi_log(res[0], x);

  if(n>=1) {
    mpfr_init2(minusOne, getToolPrecision());
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(res+1, minusOne, x, n-1);
    mpfr_clear(minusOne);
  }
  return;
}

void log2_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t log2;
  mpfi_init2(log2, getToolPrecision());

  mpfi_set_ui(log2, 2); mpfi_log(log2, log2);
  log_diff(res,x,n);
  for(i=0;i<=n;i++) mpfi_div(res[i], res[i], log2);

  mpfi_clear(log2);
  return;
}

void log10_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t log10;
  mpfi_init2(log10, getToolPrecision());

  mpfi_set_ui(log10, 10); mpfi_log(log10, log10);
  log_diff(res,x,n);
  for(i=0;i<=n;i++) mpfi_div(res[i], res[i], log10);

  mpfi_clear(log10);
  return;
}

void sin_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t vals[4];
  
  if(n==0) mpfi_sin(res[0], x);
  else {
    
    for(index=0;index<4;index++) mpfi_init2(vals[index], getToolPrecision());
    
    mpfi_sin(vals[0], x);  mpfi_cos(vals[1], x);
    mpfi_neg(vals[2],vals[0]);
    mpfi_neg(vals[3],vals[1]);

    for(i=0;i<=n;i++) mpfi_set(res[i], vals[i % 4]);

    for(index=0;index<4;index++) mpfi_clear(vals[index]);
  }

  return;
}

void cos_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t vals[4];
  
  if(n==0) mpfi_cos(res[0], x);
  else {
    
    for(index=0;index<4;index++) mpfi_init2(vals[index], getToolPrecision());
    
    mpfi_cos(vals[0], x);  mpfi_sin(vals[3], x);
    mpfi_neg(vals[2],vals[0]);
    mpfi_neg(vals[1],vals[3]);

    for(i=0;i<=n;i++) mpfi_set(res[i], vals[i % 4]);

    for(index=0;index<4;index++) mpfi_clear(vals[index]);
  }

  return;
}

void sinh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t vals[2];
  
  if(n==0) mpfi_sinh(res[0], x);
  else {
    
    for(index=0;index<2;index++) mpfi_init2(vals[index], getToolPrecision());
    
    mpfi_sinh(vals[0], x);  mpfi_cosh(vals[1], x);

    for(i=0;i<=n;i++) mpfi_set(res[i], vals[i % 2]);

    for(index=0;index<2;index++) mpfi_clear(vals[index]);
  }

  return;
}

void cosh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t vals[2];
  
  if(n==0) mpfi_cosh(res[0], x);
  else {
    
    for(index=0;index<2;index++) mpfi_init2(vals[index], getToolPrecision());
    
    mpfi_cosh(vals[0], x);  mpfi_sinh(vals[1], x);

    for(i=0;i<=n;i++) mpfi_set(res[i], vals[i % 2]);

    for(index=0;index<2;index++) mpfi_clear(vals[index]);
  }

  return;
}

void baseFunction_diff(mpfi_t *res, int nodeType, mpfi_t x, int n) {
  mpfr_t oneHalf;

  switch(nodeType) {
  case SQRT:
    mpfr_init2(oneHalf, getToolPrecision());
    mpfr_set_d(oneHalf, 0.5, GMP_RNDN);
    constantPower_diff(res, oneHalf, x, n);
    mpfr_clear(oneHalf);
    break;
  case EXP:
    exp_diff(res, x, n);
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
    break;
  case ASIN:
    break;
  case ACOS:
    break;
  case ATAN:
    break;
  case SINH:
    sinh_diff(res,x,n);
    break;
  case COSH:
    cosh_diff(res,x,n);
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



void computeBinomials(mpfi_t **res, int n) {
  int m,k;
  
  mpfi_set_ui(res[0][0], 1);
  for(m=1; m<=n; m++) {
    mpfi_set_ui(res[m][0], 1);
    for(k=1; k<=m-1; k++) {
      mpfi_add(res[m][k], res[m-1][k-1], res[m-1][k]);
    }
    mpfi_set_ui(res[m][m], 1);
  }

  return;
}


void multiplication_AD(mpfi_t *res, mpfi_t *f, mpfi_t *g, int n) {
  int i,j,p;
  mpfi_t temp;
  mpfi_t **binomial_array;

  binomial_array = (mpfi_t **)safeMalloc( (n+1)*sizeof(mpfi_t *));
  for(i=0;i<=n;i++) {
    binomial_array[i] = (mpfi_t *)safeMalloc( (n+1)*sizeof(mpfi_t) );
    for(j=0;j<=n;j++) {
      mpfi_init2(binomial_array[i][j], getToolPrecision());
    }
  }
  computeBinomials(binomial_array, n);

  mpfi_init2(temp, getToolPrecision());

  for(p=0;p<=n;p++) {
    i=0; j=p; mpfi_set_ui(res[p], 0);
    while(i<=p) {
      mpfi_mul(temp, f[i], g[j]);
      mpfi_mul(temp, temp, binomial_array[p][i]);
      mpfi_add(res[p], res[p], temp);

      i++;
      j--;
    }
  }

  mpfi_clear(temp);

  for(i=0;i<=n;i++) {
    for(j=0;j<=n;j++) {
      mpfi_clear(binomial_array[i][j]);
    }
    free(binomial_array[i]);
  }
  free(binomial_array);
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
  mpfr_t minusOne;
  
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

    mpfr_init2(minusOne, getToolPrecision());
    
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(res2, minusOne, res1[0], n);
    composition_AD(res3, res2, res1, n);

    auto_diff(res4, f->child1, x, n);
    multiplication_AD(res, res3, res4, n);

    mpfr_clear(minusOne);
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
