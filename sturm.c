/*
  For compiling this file:
    gcc -fPIC -Wall -c sturm.c
    gcc -fPIC -shared -o sturm sturm.o


  Within Sollya:
    > externalproc(getNrRoots, "./sturm", (function, range) -> integer);
    getNrRoots(function, range, integer) -> list of range

  And then, for instance:
    > getNrRoots(x+1, [2.5; 2.6]);

*/


#include "sollya.h"
//these are the functions that work on mpq_t
int sturm_mpq(int *n, mpq_t *p, int p_degree, mpfi_t x);
int polynomialDivide_mpq(mpq_t *quotient, int *quotient_degree, mpq_t *rest, int *rest_degree, mpq_t *p, int p_degree, mpq_t *q, int q_degree) ;
int polynomialDeriv_mpq(mpq_t **derivCoeff, int *deriv_degree, mpq_t *p, int p_degree);
int polynomialEval_mpq( mpq_t *res, mpq_t x, mpq_t *p, int p_degree);


int mpfr_to_mpq( mpq_t y, mpfr_t x);



int getNrRoots(int *res, void **args) {
  node *f;
  mpfi_t x;
  int degree,prec,i,nr;
  node **coefficients;
  mpfr_t *fpCoefficients;
  mpq_t  *qCoefficients;
  int r;
  int *fpCoeffRoundAutomatically;
  mpfr_t tempValue;
  node *tempTree;
  
  prec=getToolPrecision();

  f = (node *)args[0];
  
  mpfi_init2(x, prec);
  mpfi_set(x, *( (mpfi_t *)args[1] ));

  getCoefficients(&degree,&coefficients,f);

  if (degree < 0) {
    fprintf(stderr,"Error: implementpoly: an error occurred. Could not extract the coefficients of the given polynomial.\n");
    exit(1);
  }

  fpCoefficients = (mpfr_t *) safeCalloc(degree+1,sizeof(mpfr_t));
  fpCoeffRoundAutomatically = (int *) safeCalloc(degree+1,sizeof(int));
  
  qCoefficients = (mpq_t *) safeCalloc(degree+1,sizeof(mpq_t));
  
  mpfr_init2(tempValue,prec);
  mpfr_set_d(tempValue,1.0,GMP_RNDN);

  for (i=0;i<=degree;i++) {
    mpfr_init2(fpCoefficients[i],prec);
    fpCoeffRoundAutomatically[i] = 0;

    if (coefficients[i] != NULL) {
      tempTree = simplifyTreeErrorfree(coefficients[i]);
      free_memory(coefficients[i]);
      if (!isConstant(tempTree)) {
    fprintf(stderr,"Error: implementpoly: an error occurred. A polynomial coefficient is not constant.\n");
    exit(1);
      }
      if (tempTree->nodeType != CONSTANT) {
    printMessage(1,"Warning: the %dth coefficient of the polynomial to implement is neither a floating point\n",i);
    printMessage(1,"constant nor is able to be evaluated without rounding to a floating point constant.\n");
    printMessage(1,"Will evaluate it faithfully with the current precision (%d bits) \n",prec);
    r=evaluateFaithful(fpCoefficients[i], tempTree, tempValue, prec);
    if (!r){
      mpfr_set_ui(fpCoefficients[i],0,GMP_RNDN);
      printMessage(1,"Warning: Forced the coefficient %d to 0 \n",i);
      }
    fpCoeffRoundAutomatically[i] = 1;
      } 
      else {
        if (mpfr_set(fpCoefficients[i],*(tempTree->value),GMP_RNDN) != 0) {
          //if (!noRoundingWarnings) {
          printMessage(1,"Warning: rounding occurred on internal handling of a coefficient of the given polynomial.\n");
         // }
        fpCoeffRoundAutomatically[i] = 1;
      }
     }
     free_memory(tempTree);
    } else {
      mpfr_set_d(fpCoefficients[i],0.0,GMP_RNDN);
    }
  }
  free(coefficients);
  mpfr_clear(tempValue); 
  
  for (i=0;i<=degree;i++) {
    //printValue(fpCoefficients[i],prec);
    mpq_init(qCoefficients[i]);
    mpfr_to_mpq( qCoefficients[i], fpCoefficients[i]);
  }  
  //printf("\nSturm....\n");
  sturm_mpq(&nr, qCoefficients, degree,x);
  *res = nr;
  mpfi_clear(x);
  for (i=0;i<=degree;i++) {
  mpq_clear(qCoefficients[i]);
  mpfr_clear(fpCoefficients[i]);  
  }
  return 1;
}

int mpfr_to_mpq( mpq_t y, mpfr_t x){
  mpz_t mant;
  mp_exp_t expo;
  mpq_t aux;
  if (mpfr_number_p(x)) {
    mpz_init(mant);
    expo = mpfr_get_z_exp(mant,x);
    mpq_init(aux);    
    mpq_set_z(aux,mant);
    
    if (expo>=0)
    mpq_mul_2exp(aux,aux,(unsigned int)expo);
    else
    mpq_div_2exp(aux,aux,(unsigned int)(-expo));
    mpq_set(y,aux);
    mpq_clear(aux);
    return 1;
  }
  else return 0;
}



int polynomialDeriv_mpq(mpq_t **derivCoeff, int *deriv_degree, mpq_t *p, int p_degree){
  int i;
  int prec;
  mpq_t aux;
  prec=getToolPrecision();
  if ((mpq_cmp_ui(p[p_degree],0,1))==0) 
    return 0;
  if (p_degree>=1)
    *deriv_degree=p_degree-1;
  else if (p_degree==0) *deriv_degree=0;
  else return 0; 
 
  *derivCoeff= (mpq_t *)safeMalloc((*deriv_degree+1)*sizeof(mpq_t));  
  mpq_init((*derivCoeff)[0]);//is set to 0
  mpq_init(aux);
  
  for (i=1; i<=p_degree;i++){
    mpq_init((*derivCoeff)[i-1]);
    mpq_set_ui(aux,i,1);
    mpq_mul((*derivCoeff)[i-1],p[i],aux);
  }
  mpq_clear(aux);
  return 1;
}  


int polynomialEval_mpq( mpq_t *res, mpq_t x, mpq_t *p, int p_degree){
  int i;
  mpq_t pow, aux;
  mpq_init(pow);
  mpq_set_ui(pow,1,1);
  mpq_init(aux);
  mpq_set_ui(aux,1,1); 
  mpq_init(*res);//is set to 0/1
  for (i=0; i<=p_degree; i++) {
    mpq_mul(aux,p[i],pow);
    mpq_add(*res, aux, *res);
    mpq_mul(pow, pow, x); 
  }

  
  mpq_clear(aux);
  mpq_clear(pow);
  
  return 1;
}

int polynomialDivide_mpq(mpq_t *quotient, int *quotient_degree, mpq_t *rest, int *rest_degree, mpq_t *p, int p_degree, mpq_t *q, int q_degree) {
  
  int i,step,k;
  mpq_t aux;
 
  *quotient_degree=p_degree-q_degree;
  
  if (((mpq_cmp_ui(q[q_degree],0,1))==0) || ((mpq_cmp_ui(p[p_degree],0,1))==0))
    return 0;
 
   mpq_init(aux);
  
  step=0;
  for (k=*quotient_degree; k>=0;k--)
  {

    mpq_set(quotient[k],p[p_degree-step]);
    mpq_div(quotient[k],quotient[k],q[q_degree]);
    for (i=q_degree; i>=0;i--){    
        mpq_mul(aux,quotient[k],q[i]);
        mpq_sub(p[p_degree-step-(q_degree-i)],p[p_degree-step-(q_degree-i)],aux);  
    }
    step++; 
  }
  *rest_degree=0;
  for (i=q_degree-1; i>=0; i--)  
  {
    if ((mpq_cmp_ui(p[i],0,1))!=0){
      *rest_degree=i;
      break;
    }
  }
  for (i=*rest_degree; i>=0; i--){ 
    mpq_set(rest[i],p[i]);
  }
  mpq_clear(aux);
  return 1;
}  

int sturm_mpq(int *n, mpq_t *p, int p_degree, mpfi_t x){
  mpq_t *quotient, *rest, *dp;
  int quotient_degree, rest_degree, dp_degree;
  mpq_t *evalResA;
  mpq_t *evalResB;
  mpq_t *s0, *s1;
  mpq_t evalRes;
  int s0_degree, s1_degree;
  mpfr_t a,b;
  mpq_t aq,bq;
  int i,na,nb,prec,nrRoots;
  int varSignB,varSignA;

  prec=getToolPrecision();
  na=0; nb=0;  
  nrRoots=0;
  mpfr_init2(a,prec);
  mpfr_init2(b,prec);
  mpfi_get_left(a,x);
  mpfi_get_right(b,x);
 
  mpq_init(aq);
  mpq_init(bq);
    
  mpfr_to_mpq(aq,a);
  mpfr_to_mpq(bq,b);
  
  evalResA = (mpq_t *)safeMalloc((p_degree+1)*sizeof(mpq_t));  
  evalResB = (mpq_t *)safeMalloc((p_degree+1)*sizeof(mpq_t));    
  s0=(mpq_t *)safeMalloc((p_degree+1)*sizeof(mpq_t));
  quotient=(mpq_t *)safeMalloc((p_degree+1)*sizeof(mpq_t));
  rest=(mpq_t *)safeMalloc((p_degree+1)*sizeof(mpq_t));
  for (i=0; i<=p_degree; i++){ 
    mpq_init(quotient[i]);
    mpq_init(rest[i]);
  }

  s0_degree=p_degree;

  for (i=0; i<=p_degree; i++){ 
    mpq_init(s0[i]); 
    mpq_set(s0[i],p[i]);
  }
        
  polynomialDeriv_mpq(&dp, &dp_degree, p, p_degree);
  mpq_init(evalRes);
    
  polynomialEval_mpq( &evalRes, aq, s0, s0_degree);
  if (mpq_cmp_ui(evalRes,0,1)!=0){
    mpq_init(evalResA[na]);
    mpq_set(evalResA[na],evalRes);
    na++;
  }
  else nrRoots++; /*if the left extremity is a root we count it here
                    since the number of sign changes gives the nr of distinct 
                    roots between a and b, a<b*/  
  polynomialEval_mpq( &evalRes, bq, s0, s0_degree);
  if (mpq_cmp_ui(evalRes,0,1)!=0){
    mpq_init(evalResB[nb]);
    mpq_set(evalResB[nb],evalRes);
    nb++;
  }
  s1=dp;
  s1_degree=dp_degree;
  if (s0_degree>0){

    polynomialEval_mpq( &evalRes, aq, dp, dp_degree);
    if (mpq_cmp_ui(evalRes,0,1)!=0){
      mpq_init(evalResA[na]);
      mpq_set(evalResA[na],evalRes);
      na++;
    }
  
    polynomialEval_mpq( &evalRes, bq, dp, dp_degree);
    if (mpq_cmp_ui(evalRes,0,1)!=0){
      mpq_init(evalResB[nb]);
      mpq_set(evalResB[nb],evalRes);
      nb++;
    }

    /*mpq_init(evalResA[evalNr]);
    mpq_init(evalResB[evalNr]);
    polynomialEval_mpq(&evalResA[evalNr], aq, dp, dp_degree);
    polynomialEval_mpq( &evalResB[evalNr], bq, dp, dp_degree);
    evalNr++;*/  
  }
  
  while (s1_degree!=0){
   // mpq_init(evalResA[evalNr]);
    //mpq_init(evalResB[evalNr]);
          
    polynomialDivide_mpq(quotient, &quotient_degree, rest, &rest_degree, s0, s0_degree, s1, s1_degree) ;
    
    s0_degree=s1_degree; 
    for(i=0;i<=s0_degree;i++)
      mpq_set(s0[i],s1[i]);
    
    s1_degree=rest_degree; 
    
    for(i=0;i<=s1_degree;i++){
      mpq_set(s1[i],rest[i]);
    }
    
    for (i=0; i<=s1_degree; i++)
      mpq_neg(s1[i],s1[i]);
    
   // polynomialEval_mpq( &evalResA[evalNr], aq, s1, s1_degree);
   // polynomialEval_mpq(  &evalResB[evalNr], bq, s1, s1_degree);
   // evalNr++;
    polynomialEval_mpq( &evalRes, aq, s1, s1_degree);
    if (mpq_cmp_ui(evalRes,0,1)!=0){
      mpq_init(evalResA[na]);
      mpq_set(evalResA[na],evalRes);
      na++;
    }
  
    polynomialEval_mpq( &evalRes, bq, s1, s1_degree);
    if (mpq_cmp_ui(evalRes,0,1)!=0){
      mpq_init(evalResB[nb]);
      mpq_set(evalResB[nb],evalRes);
      nb++;
    }
  }
  
  varSignA=0;
  for (i=1; i<na; i++){
    if ((mpq_cmp_ui(evalResA[i-1],0,1) * mpq_cmp_ui(evalResA[i],0,1))<0) 
      varSignA++;
    
  } 
  varSignB=0;
  for (i=1; i<nb; i++){
    if ((mpq_cmp_si(evalResB[i-1],0,1) * mpq_cmp_si(evalResB[i],0,1))<0) 
      varSignB++;
  }
 // printf("\nA variations: = %d\n", varSignA);
 // printf("\nB variations: = %d\n", varSignB);
  *n=(((varSignA-varSignB)>0)?(varSignA-varSignB+nrRoots):(varSignB-varSignA+nrRoots) );

  
  

return 1;
}



