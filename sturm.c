/*
  For compiling this file:
    gcc -fPIC -Wall -c sturm.c
    gcc -fPIC -shared -o sturm sturm.o


  Within Sollya:
    > externalproc(getNrRoots, "./sturm", (function, range) -> integer);

  And then, for instance:
    > getNrRoots(x+1, [2.5; 2.6]);

*/


#include "sollya.h"
#include <gmp.h>
#include <limits.h>

extern int noRoundingWarnings;
extern int verbosity;

//these are the functions that work on mpq_t


int sturm_mpq(int *n, mpq_t *p, int p_degree, mpfi_t x);
int polynomialDivide_mpq(mpq_t *quotient, int *quotient_degree, mpq_t *rest, int *rest_degree, mpq_t *p, int p_degree, mpq_t *q, int q_degree) ;
int polynomialDeriv_mpq(mpq_t **derivCoeff, int *deriv_degree, mpq_t *p, int p_degree);
int polynomialEval_mpq( mpq_t *res, mpq_t x, mpq_t *p, int p_degree);
int sturm_mpfi(int *n, mpq_t *p, int p_degree, mpfi_t x);
int polynomialDivide_mpfi(mpfi_t *quotient, int *quotient_degree, mpfi_t *rest, int *rest_degree, mpfi_t *p, int p_degree, mpfi_t *q, int q_degree, mp_prec_t prec) ;
int polynomialDeriv_mpfi(mpfi_t **derivCoeff, int *deriv_degree, mpfi_t *p, int p_degree, mp_prec_t prec);
int polynomialEval_mpfi( mpfi_t *res, mpfi_t x, mpfi_t *p, int p_degree);


int mpfr_to_mpq( mpq_t y, mpfr_t x);


void printMpq(mpq_t x) {
  mpz_t num;
  mpz_t denom;
  mpfr_t numMpfr;
  mpfr_t denomMpfr;
  mp_prec_t prec;
  int p;
  unsigned int dyadicValue;

  mpz_init(num);
  mpz_init(denom);

  mpq_get_num(num,x);
  mpq_get_den(denom,x);
  
  prec = mpz_sizeinbase(num, 2);
  dyadicValue = mpz_scan1(num, 0);
  p = prec - dyadicValue;
  if (p < 12) prec = 12; else prec = p; 
  mpfr_init2(numMpfr,prec);
  mpfr_set_z(numMpfr,num,GMP_RNDN);

  prec = mpz_sizeinbase(denom, 2);
  dyadicValue = mpz_scan1(denom, 0);
  p = prec - dyadicValue;
  if (p < 12) prec = 12; else prec = p; 
  mpfr_init2(denomMpfr,prec);
  mpfr_set_z(denomMpfr,denom,GMP_RNDN);

  printValue(&numMpfr); printf(" / "); printValue(&denomMpfr);

  mpfr_clear(numMpfr);
  mpfr_clear(denomMpfr);

  mpz_clear(num);
  mpz_clear(denom);

}


int tryEvaluateConstantTermToMpq(mpq_t res, node *tree) {
  mpq_t resA, resB, resC;
  int result;
  mpz_t num, denom;
  mpz_t num2, denom2;
  signed long int expo;

  if (tree == NULL) return 0;

  mpq_init(resA);
  mpq_init(resB);
  mpq_init(resC);

  result = 1;
  switch (tree->nodeType) {
  case CONSTANT:
    mpfr_to_mpq(resC,*(tree->value));
    break;
  case ADD:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1) && 
	tryEvaluateConstantTermToMpq(resB, tree->child2)) {
      mpq_add(resC,resA,resB);
    } else result = 0;
    break;
  case SUB:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1) && 
	tryEvaluateConstantTermToMpq(resB, tree->child2)) {
      mpq_sub(resC,resA,resB);
    } else result = 0;
    break;
  case MUL:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1) && 
	tryEvaluateConstantTermToMpq(resB, tree->child2)) {
      mpq_mul(resC,resA,resB);
    } else result = 0;
    break;
  case DIV:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1) && 
	tryEvaluateConstantTermToMpq(resB, tree->child2)) {
      mpq_div(resC,resA,resB);
    } else result = 0;
    break;
  case SQRT:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1)) {
      mpz_init(num);
      mpz_init(denom);
      mpq_get_num(num,resA);
      mpq_get_den(denom,resA);
      if (mpz_root(num,num,2) && mpz_root(denom,denom,2)) {
	mpq_set_num(resC,num);
	mpq_set_den(resC,denom);
	mpq_canonicalize(resC);
      } else {
	result = 0;
      }
      mpz_clear(num);
      mpz_clear(denom);
    } else result = 0;
    break;
  case POW:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1) && 
	tryEvaluateConstantTermToMpq(resB, tree->child2)) {
      mpz_init(num);
      mpz_init(denom);
      mpq_get_num(num,resB);
      mpq_get_den(denom,resB);
      if (mpz_cmp_ui(denom,1) == 0) {
	/* Must set resC to resA^num */
	mpz_init(num2);
	mpz_init(denom2);
	if (mpz_sgn(num) < 0) {
	  mpq_get_num(denom2,resA);
	  mpq_get_den(num2,resA);
	  mpz_neg(num,num);
	} else {
	  mpq_get_num(num2,resA);
	  mpq_get_den(denom2,resA);
	}
	/* Must set resC to (num2^num)/(denom2^num), num is positive */
	if (mpz_fits_slong_p(num)) {
	  expo = mpz_get_si(num);
	  /* Must set resC to (num2^expo)/(denom2^expo), expo is positive */
	  mpz_pow_ui(num2, num2, (unsigned long int) expo);
	  mpz_pow_ui(denom2, denom2, (unsigned long int) expo);
	  mpq_set_num(resC,num2);
	  mpq_set_den(resC,denom2);
	  mpq_canonicalize(resC);
	} else result = 0;
	mpz_clear(num2);
	mpz_clear(denom2);
      } else result = 0;
      mpz_clear(num);
      mpz_clear(denom);
    } else result = 0;
    break;
  case NEG:
    if (tryEvaluateConstantTermToMpq(resA, tree->child1)) {
      mpq_neg(resC,resA);
    } else result = 0;
    break;
  default:
    result = 0;
  }

  if (result) mpq_set(res,resC);

  mpq_clear(resA);
  mpq_clear(resB);
  mpq_clear(resC);

  return result;
}





int getNrRoots(int *res, void **args) {
  node *f;
  mpfi_t x;
  int degree,i,nr;
  node **coefficients;
  mpq_t  *qCoefficients;
  int r;
  mpfr_t tempValue, tempValue2;
  node *tempTree;
  int deg;
  int resMpfi;
  mp_prec_t prec;
  
  prec=getToolPrecision();

  f = (node *)args[0];
  
  mpfi_init2(x, mpfi_get_prec(*( (mpfi_t *)args[1] )));
  mpfi_set(x, *( (mpfi_t *)args[1] ));

  getCoefficients(&degree,&coefficients,f);

  if (degree < 0) {
    fprintf(stderr,"Error: getNrRoots: an error occurred. Could not extract the coefficients of the given polynomial.\n");
    exit(1);
  }
  
  qCoefficients = (mpq_t *) safeCalloc(degree+1,sizeof(mpq_t));
  for (i=0;i<=degree;i++) {
    mpq_init(qCoefficients[i]);
  }  

  mpfr_init2(tempValue,prec);
  mpfr_set_d(tempValue,1.0,GMP_RNDN);
  mpfr_init2(tempValue2,prec);
  for (i=0;i<=degree;i++) {
    if (coefficients[i] != NULL) {
      tempTree = simplifyTreeErrorfree(coefficients[i]);
      free_memory(coefficients[i]);
      if (!isConstant(tempTree)) {
	fprintf(stderr,"Error: getNrRoots: an error occurred. A polynomial coefficient is not constant.\n");
	exit(1);
      }
      if (tempTree->nodeType != CONSTANT) {
	if (tryEvaluateConstantTermToMpq(qCoefficients[i], tempTree)) {
	  if (verbosity >= 3) {
	    changeToWarningMode();
	    printf("Information: in getNrRoots: evaluated the %dth coefficient to ",i);
	    printMpq(qCoefficients[i]);
	    printf("\n");
	    restoreMode();
	  }
	} else {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: the %dth coefficient of the polynomial is neither a floating point\n",i);
	    printMessage(1,"constant nor can be evaluated without rounding to a floating point constant.\n");
	    printMessage(1,"Will faithfully evaluate it with the current precision (%d bits) \n",prec);
	  }
	  r=evaluateFaithful(tempValue2, tempTree, tempValue, prec);
	  if (!r){
	    mpfr_set_ui(tempValue2,0,GMP_RNDN);
	    if (!noRoundingWarnings) {
	      printMessage(1,"Warning: Rounded the coefficient %d to 0.\n",i);
	    }
	  }
	  mpfr_to_mpq(qCoefficients[i], tempValue2);
	  if (verbosity >= 3) {
	    changeToWarningMode();
	    printf("Information: evaluated the %dth coefficient to ",i);
	    printMpq(qCoefficients[i]);
	    printf("\n");
	    restoreMode();
	  }
	}
      } 
      else {
	mpfr_to_mpq(qCoefficients[i], *(tempTree->value));
      }
      free_memory(tempTree);
    } else {
      mpq_set_ui(qCoefficients[i],0,1);
    }
  }
  free(coefficients);
  mpfr_clear(tempValue); 
  mpfr_clear(tempValue2);

  for(deg = degree; deg >= 0 && (mpq_sgn(qCoefficients[deg]) == 0); deg--); 

  if (deg >= 0) {
    resMpfi = sturm_mpfi(&nr, qCoefficients, deg,x);
    if (!resMpfi) {
      printMessage(1,"Warning: using slower GMP MPQ version\n");
      sturm_mpq(&nr, qCoefficients, deg,x);
    }
    *res = nr;
  } else {
    printMessage(1,"Warning: the given polynomial is the zero polynomial. Its number of zeros is infinite.\n");
    *res = INT_MAX;
  }

  mpfi_clear(x);
  for (i=0;i<=degree;i++) {
    mpq_clear(qCoefficients[i]);
  }
  free(qCoefficients);
  
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
  mpq_t aux;

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


  prec=mpfi_get_prec(x);
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

  }
  
  while (s1_degree!=0){
          
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

  *n=(((varSignA-varSignB)>0)?(varSignA-varSignB+nrRoots):(varSignB-varSignA+nrRoots) );

  free(evalResA);
  free(evalResB);
  free(s0); 
  free(quotient); 
  free(rest); 
  
  return 1;
}

int polynomialDeriv_mpfi(mpfi_t **derivCoeff, int *deriv_degree, mpfi_t *p, int p_degree, mp_prec_t prec){
  int i;
  mpfi_t aux;

  if (mpfi_is_zero(p[p_degree])) 
    return 0;
  if (p_degree>=1)
    *deriv_degree=p_degree-1;
  else if (p_degree==0) *deriv_degree=0;
  else return 0; 
 
  *derivCoeff= (mpfi_t *)safeMalloc((*deriv_degree+1)*sizeof(mpfi_t));  
  mpfi_init2((*derivCoeff)[0],prec);
  mpfi_set_ui((*derivCoeff)[0],0);
  mpfi_init2(aux,prec);
  
  for (i=1; i<=p_degree;i++){
    mpfi_init2((*derivCoeff)[i-1],prec);
    mpfi_set_ui(aux,i);
    mpfi_mul((*derivCoeff)[i-1],p[i],aux);
  }
  mpfi_clear(aux);
  return 1;
}  


int polynomialEval_mpfi( mpfi_t *res, mpfi_t x, mpfi_t *p, int p_degree){
  int i;

  mpfi_set_ui(*res,0);
  mpfi_set(*res,p[p_degree]);
  for (i=p_degree-1;i>=0;i--) {
    mpfi_mul(*res,*res,x);
    mpfi_add(*res,*res,p[i]);
  }

  return 1;
}

int polynomialDivide_mpfi(mpfi_t *quotient, int *quotient_degree, mpfi_t *rest, int *rest_degree, mpfi_t *p, int p_degree, mpfi_t *q, int q_degree, mp_prec_t prec) {
  
  int i,step,k;
  mpfi_t aux;
  int okay;

  okay = 1;
 
  *quotient_degree=p_degree-q_degree;
  
  if (mpfi_is_zero(q[q_degree]) || mpfi_is_zero(p[p_degree]))
    return 0;
 
  mpfi_init2(aux,prec);
  
  step=0;
  for (k=*quotient_degree; (k>=0) && okay;k--)
    {

      mpfi_set(quotient[k],p[p_degree-step]);
      if (!mpfi_has_zero(q[q_degree])) 
	mpfi_div(quotient[k],quotient[k],q[q_degree]);
      else {
	okay = 0;
      }
      if (okay) {
	for (i=q_degree; i>=0;i--){    
	  mpfi_mul(aux,quotient[k],q[i]);
	  mpfi_sub(p[p_degree-step-(q_degree-i)],p[p_degree-step-(q_degree-i)],aux);  
	}
	step++; 
      }
    }
  *rest_degree=0;
  for (i=q_degree-1; i>=0; i--)  
    {
      if (!mpfi_is_zero(p[i])){
	*rest_degree=i;
	break;
      }
    }
  for (i=*rest_degree; i>=0; i--){ 
    mpfi_set(rest[i],p[i]);
  }
  mpfi_clear(aux);
  return okay;
}  

mp_prec_t getMpzPrecision(mpz_t x) {
  mp_prec_t prec;
  int p, dyadicValue;

  prec = mpz_sizeinbase(x, 2);
  dyadicValue = mpz_scan1(x, 0);
  p = prec - dyadicValue;
  if (p < 12) prec = 12; else prec = p; 

  return prec;
}


int sturm_mpfi(int *n, mpq_t *pMpq, int p_degree, mpfi_t x){
  mpfi_t *quotient, *rest, *dp;
  int quotient_degree, rest_degree, dp_degree;
  mpfi_t *evalResA;
  mpfi_t *evalResB;
  mpfi_t *s0, *s1;
  mpfi_t evalRes;
  int s0_degree, s1_degree;
  mpfr_t a,b;
  mpfi_t aq,bq;
  int i,na,nb,nrRoots;
  int varSignB,varSignA;
  mpfi_t *p;
  int resultat;
  int resDiv;
  mp_prec_t prec, tempprec, prec2;


  resultat = 1;

  prec = getToolPrecision();
  for (i=0;i<=p_degree;i++) {
    tempprec = getMpzPrecision(mpq_numref(pMpq[i])) + 10;
    if (tempprec > prec) prec = tempprec;
    tempprec = getMpzPrecision(mpq_denref(pMpq[i])) + 10;
    if (tempprec > prec) prec = tempprec;
  }
  prec = 2 * prec;

  printMessage(2,"Information: in sturm_mpfi: chosen working precision is %d\n",(int) prec);

  p = (mpfi_t *) safeCalloc(p_degree+1,sizeof(mpfi_t));
  for (i=0;i<=p_degree;i++) {
    mpfi_init2(p[i],prec);
    mpfi_set_q(p[i],pMpq[i]);
  }

  prec2=mpfi_get_prec(x);
  if (prec > prec2) prec2 = prec;
  na=0; nb=0;  
  nrRoots=0;
  mpfr_init2(a,prec2);
  mpfr_init2(b,prec2);
  mpfi_get_left(a,x);
  mpfi_get_right(b,x);
 
  mpfi_init2(aq,prec2);
  mpfi_init2(bq,prec2);
    
  mpfi_set_fr(aq,a);
  mpfi_set_fr(bq,b);
  
  mpfi_init2(evalRes,prec);

  evalResA = (mpfi_t *)safeMalloc((p_degree+1)*sizeof(mpfi_t));  
  evalResB = (mpfi_t *)safeMalloc((p_degree+1)*sizeof(mpfi_t));    
  s0=(mpfi_t *)safeMalloc((p_degree+1)*sizeof(mpfi_t));
  quotient=(mpfi_t *)safeMalloc((p_degree+1)*sizeof(mpfi_t));
  rest=(mpfi_t *)safeMalloc((p_degree+1)*sizeof(mpfi_t));
  for (i=0; i<=p_degree; i++){ 
    mpfi_init2(quotient[i],prec);
    mpfi_init2(rest[i],prec);
  }

  s0_degree=p_degree;

  for (i=0; i<=p_degree; i++){ 
    mpfi_init2(s0[i],prec); 
    mpfi_set(s0[i],p[i]);
  }
        
  polynomialDeriv_mpfi(&dp, &dp_degree, p, p_degree, prec);
  mpfi_init2(evalRes,prec);
    
  polynomialEval_mpfi( &evalRes, aq, s0, s0_degree);
  if (!mpfi_has_zero(evalRes)){
    mpfi_init2(evalResA[na],prec);
    mpfi_set(evalResA[na],evalRes);
    na++;
  }
  else {
    if (mpfi_is_zero(evalRes)) 
    nrRoots++; /*if the left extremity is a root we count it here
                    since the number of sign changes gives the nr of distinct 
                    roots between a and b, a<b*/  
    else resultat = 0;
  }

  polynomialEval_mpfi( &evalRes, bq, s0, s0_degree);
  if (!mpfi_has_zero(evalRes)){
    mpfi_init2(evalResB[nb],prec);
    mpfi_set(evalResB[nb],evalRes);
    nb++;
  } else {
    if (!mpfi_is_zero(evalRes)) resultat = 0;
  }

  s1=dp;
  s1_degree=dp_degree;
  if (s0_degree>0){

    polynomialEval_mpfi( &evalRes, aq, dp, dp_degree);
    if (!mpfi_has_zero(evalRes)){
      mpfi_init2(evalResA[na],prec);
      mpfi_set(evalResA[na],evalRes);
      na++;
    } else {
      if (!mpfi_is_zero(evalRes)) resultat = 0;
    }
  
    polynomialEval_mpfi( &evalRes, bq, dp, dp_degree);
    if (!mpfi_has_zero(evalRes)){
      mpfi_init2(evalResB[nb],prec);
      mpfi_set(evalResB[nb],evalRes);
      nb++;
    } else {
      if (!mpfi_is_zero(evalRes)) resultat = 0;
    }

  }
  
  while ((s1_degree!=0) && resultat) {
          
    resDiv = polynomialDivide_mpfi(quotient, &quotient_degree, rest, &rest_degree, s0, s0_degree, s1, s1_degree, prec);

    if (!resDiv) 
      resultat = 0; 
    else {

      s0_degree=s1_degree; 
      for(i=0;i<=s0_degree;i++) {
	mpfi_set(s0[i],s1[i]);
      }

      s1_degree=rest_degree; 
      
      for(i=0;i<=s1_degree;i++){
	mpfi_set(s1[i],rest[i]);
      }
      
      for (i=0; i<=s1_degree; i++)
	mpfi_neg(s1[i],s1[i]);
      
      polynomialEval_mpfi( &evalRes, aq, s1, s1_degree);
      if (!mpfi_has_zero(evalRes)){
	mpfi_init2(evalResA[na],prec);
	mpfi_set(evalResA[na],evalRes);
	na++;
      } else {
	if (!mpfi_is_zero(evalRes)) resultat = 0;
      }
      
      polynomialEval_mpfi( &evalRes, bq, s1, s1_degree);
      if (!mpfi_has_zero(evalRes)){
	mpfi_init2(evalResB[nb],prec);
	mpfi_set(evalResB[nb],evalRes);
	nb++;
      } else {
	if (!mpfi_is_zero(evalRes)) resultat = 0;
      }
    }
  }
  
  varSignA=0;
  for (i=1; i<na; i++){
    if (mpfi_is_pos(evalResA[i-1]) ^ mpfi_is_pos(evalResA[i])) varSignA++;    
  } 
  varSignB=0;
  for (i=1; i<nb; i++){
    if (mpfi_is_pos(evalResB[i-1]) ^ mpfi_is_pos(evalResB[i])) varSignB++;    
  }

  *n=(((varSignA-varSignB)>0)?(varSignA-varSignB+nrRoots):(varSignB-varSignA+nrRoots) );

  free(evalResA);
  free(evalResB);
  free(s0); 
  free(quotient); 
  free(rest); 
  mpfi_clear(evalRes);

  for (i=0;i<=p_degree;i++) {
    mpfi_clear(p[i]);
  }
  free(p);
  
  return resultat;
}


