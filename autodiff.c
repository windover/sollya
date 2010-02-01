/*
  For compiling this file:
    gcc -fPIC -Wall -c autodiff.c
    gcc -fPIC -shared -o autodiff autodiff.o


  Within Sollya:
    > externalproc(AD, "./autodiff", (function, range, integer) -> list of range);

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

void expm1_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
  mpfi_t temp;

  mpfi_init2(temp, getToolPrecision());

  mpfi_exp(temp, x);
  for(i=0;i<=n;i++) mpfi_set(res[i], temp);

  mpfi_sub_ui(res[0], res[0], 1);

  mpfi_clear(temp);
  return;
}

void powerFunction_diff(mpfi_t *res, mpfr_t p, mpfi_t x, int n) { //the power function is: p^x, where p is a positive ct
  int i;
  mpfi_t temp1,temp2;

  mpfi_init2(temp1, getToolPrecision());
  mpfi_init2(temp2, getToolPrecision());
  mpfi_set_fr(temp1,p);
  mpfi_log(temp1,temp1);
  mpfi_mul(temp2,temp1,x);
  mpfi_exp(temp2, temp2);
  for(i=0;i<=n;i++) {
    mpfi_set(res[i], temp2);
    mpfi_mul(temp2,temp2,temp1);
  }
  mpfi_clear(temp1);
  mpfi_clear(temp2);
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

/*tan_diff : recurrence formula: p_(n+1)(u)=p'_n(u) * (1+u^2) , u=tan(x)
tan^(n)=p_(n)(u)
p_0=u;
p_1=1+u^2
*/
void tan_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow;
  
    
  coeffs_array = (mpfi_t *)safeMalloc( (n+2)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n+2)*sizeof(mpfi_t));

  for (index=0; index<=n+1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_tan(u, x);
  
  for (index=0; index<=n; index++){
    if (index==0){
      mpfi_set_ui(coeffs_array[0],0);
      mpfi_set_ui(coeffs_array[1],1);
      mpfi_set_ui(powers_array[0],1);
      mpfi_set(powers_array[1],u);
      
    }
    else if (index==1){
      mpfi_set_ui(coeffs_array[0],1);
      mpfi_set_ui(coeffs_array[1],0);
      mpfi_set_ui(coeffs_array[2],1);
      mpfi_set_ui(pow,2);
      mpfi_pow(powers_array[2],u,pow);
    }
    else{
     //newcoeff(k)=(k-1) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
     //the new coefficent added at index+1
      mpfi_set(coeffs_array[index+1],coeffs_array[index]);
      mpfi_mul_ui(coeffs_array[index+1],coeffs_array[index+1],index);
      //keep the coeff at index      
      mpfi_set(oldCoeff,coeffs_array[index]);
      //modify at index with new value      
      mpfi_set(coeffs_array[index],coeffs_array[index-1]);
      mpfi_mul_ui(coeffs_array[index],coeffs_array[index],index-1);
      //inter-extremities case
      for (i=index-1; i>1;i--){
        mpfi_set(s1,oldCoeff);
        mpfi_mul_ui(s1,s1,i+1);
        mpfi_set(oldCoeff,coeffs_array[i]);
        mpfi_set(coeffs_array[i],coeffs_array[i-1]);
        mpfi_mul_ui(coeffs_array[i],coeffs_array[i],i-1);
        mpfi_add(coeffs_array[i],coeffs_array[i], s1);
      }
      //modify at coeff 0 with new value      
      mpfi_set(coeffs_array[0],coeffs_array[1]);
      //modify at 1 with new value      
      mpfi_set(coeffs_array[1],oldCoeff);
      mpfi_mul_ui(coeffs_array[1],coeffs_array[1],2);
      //add in powers array one more power
      mpfi_set_ui(pow,index+1);
      mpfi_pow(powers_array[index+1],u,pow);
    }
    //we have the coeffcients, we compute the result
    /*printf("index=%d",index);
    for (i=0;i<=index+1; i++){
      printInterval(coeffs_array[i]);
    }
    printf("\n");*/
    mpfi_set_ui(res[index],0);    
    for (i=0;i<=index+1; i++){
      mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
      mpfi_add(res[index],res[index],partialSum);
    }

  }
  for (index=0; index<=n+1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  
  return;
}

/*tanh_diff : recurrence formula: p_(n+1)(u)=p'_n(u) * (1-u^2) , u=tanh(x)
tan^(n)=p_(n)(u)
p_0=u;
p_1=1-u^2
*/
void tanh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow;
  
    
  coeffs_array = (mpfi_t *)safeMalloc( (n+2)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n+2)*sizeof(mpfi_t));

  for (index=0; index<=n+1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_tanh(u, x);
  
  for (index=0; index<=n; index++){
    if (index==0){
      mpfi_set_ui(coeffs_array[0],0);
      mpfi_set_ui(coeffs_array[1],1);
      mpfi_set_ui(powers_array[0],1);
      mpfi_set(powers_array[1],u);
      
    }
    else if (index==1){
      mpfi_set_ui(coeffs_array[0],1);
      mpfi_set_ui(coeffs_array[1],0);
      mpfi_set_si(coeffs_array[2],-1);
      mpfi_set_ui(pow,2);
      mpfi_pow(powers_array[2],u,pow);
    }
    else{
     //newcoeff(k)=-(k-1) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
     //the new coefficent added at index+1
      mpfi_set(coeffs_array[index+1],coeffs_array[index]);
      mpfi_mul_si(coeffs_array[index+1],coeffs_array[index+1],-index);
      //keep the coeff at index      
      mpfi_set(oldCoeff,coeffs_array[index]);
      //modify at index with new value      
      mpfi_set(coeffs_array[index],coeffs_array[index-1]);
      mpfi_mul_si(coeffs_array[index],coeffs_array[index],-(index-1));
      //inter-extremities case
      for (i=index-1; i>1;i--){
        mpfi_set(s1,oldCoeff);
        mpfi_mul_ui(s1,s1,i+1);
        mpfi_set(oldCoeff,coeffs_array[i]);
        mpfi_set(coeffs_array[i],coeffs_array[i-1]);
        mpfi_mul_si(coeffs_array[i],coeffs_array[i],-(i-1));
        mpfi_add(coeffs_array[i],coeffs_array[i], s1);
      }
      //modify at coeff 0 with new value      
      mpfi_set(coeffs_array[0],coeffs_array[1]);
      //modify at 1 with new value      
      mpfi_set(coeffs_array[1],oldCoeff);
      mpfi_mul_ui(coeffs_array[1],coeffs_array[1],2);
      //add in powers array one more power
      mpfi_set_ui(pow,index+1);
      mpfi_pow(powers_array[index+1],u,pow);
    }
    //we have the coeffcients, we compute the result
    /*printf("index=%d",index);
    for (i=0;i<=index+1; i++){
      printInterval(coeffs_array[i]);
    }
    printf("\n");*/
    mpfi_set_ui(res[index],0);    
    for (i=0;i<=index+1; i++){
      mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
      mpfi_add(res[index],res[index],partialSum);
    }

  }
  for (index=0; index<=n+1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  return;
}



/*atan_diff : reccurence formula: p_(n+1)=p'_n * (1+x^2) -2*n *x * p_n 
atan^(n)=p_(n)/((1+x^2)^n)
p_1=1;
*/
void atan_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow,a1,nominator;
  
    
  coeffs_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));

  for (index=0; index<=n-1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_init2(a1,getToolPrecision());
  mpfi_atan(u, x);
  mpfi_init2(nominator,getToolPrecision());
  mpfi_sqr(nominator,x);
  mpfi_add_si(nominator, nominator,1);
  mpfi_set(res[0],u);
  //if (n==0) 
  //else
  //{
    for (index=0; index<=n-1; index++){
      if (index==0){
        mpfi_set_ui(coeffs_array[0],1);
        mpfi_set_ui(powers_array[0],1);
      }
      else if (index==1){
        mpfi_set_ui(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],-2);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[1],x,pow);
      }
      else if (index==2){
        mpfi_set_si(coeffs_array[0],-2);
        mpfi_set_ui(coeffs_array[1],0);
        mpfi_set_ui(coeffs_array[2],6);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[2],x,pow);
      }
      else if (index==3){
        mpfi_set_si(coeffs_array[0],0);
        mpfi_set_ui(coeffs_array[1],24);
        mpfi_set_ui(coeffs_array[2],0);
        mpfi_set_si(coeffs_array[3],-24);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[3],x,pow);
      }
      else{
        //newcoeff(k)=(k-1 -2*n) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
        //the new coefficent added at index
        mpfi_set(coeffs_array[index],coeffs_array[index-1]);
        mpfi_mul_si(coeffs_array[index],coeffs_array[index],index-1-2*(index));
        //keep the coeff at index-1     
        mpfi_set(oldCoeff,coeffs_array[index-1]);
        //modify at index with new value      
        mpfi_set(coeffs_array[index-1],coeffs_array[index-2]);
        mpfi_mul_si(coeffs_array[index-1],coeffs_array[index-1],index-2-2*(index));
        //inter-extremities case
        for (i=index-2; i>1;i--){
          mpfi_set(s1,oldCoeff);
          mpfi_mul_si(s1,s1,i+1);
          mpfi_set(oldCoeff,coeffs_array[i]);
          mpfi_set(coeffs_array[i],coeffs_array[i-1]);
          mpfi_mul_si(coeffs_array[i],coeffs_array[i],i-1-2*(index));
          mpfi_add(coeffs_array[i],coeffs_array[i], s1);
        } 
        //for a1 and ao special case
        //newa1=2*a2-2n*a0   newa0=a1      
        //compute 2*a2      
        mpfi_mul_si(oldCoeff, oldCoeff,2);      
        mpfi_set(a1, coeffs_array[1]);      
        //compute -2n*a0 
        mpfi_mul_si(coeffs_array[1],coeffs_array[0],-2*(index));
        //add
        mpfi_add(coeffs_array[1], coeffs_array[1],oldCoeff);
        //modify at coeff 0 with new value      
        mpfi_set(coeffs_array[0],a1);
        //add in powers array one more power
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[index],x,pow);
      }
      //we have the coeffcients, we compute the result
     /* printf("index=%d",index);
      for (i=0;i<=index; i++){
        printInterval(coeffs_array[i]);
      }
      printf("\n");*/
      mpfi_set_ui(res[index+1],0);    
      for (i=0;i<=index; i++){
        mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
        mpfi_add(res[index+1],res[index+1],partialSum);
      } 
      mpfi_sqr(nominator,x);
      mpfi_add_si(nominator, nominator,1);
  
      mpfi_set_ui(pow,index+1);
      mpfi_pow(nominator,nominator,pow);
      mpfi_div(res[index+1],res[index+1],nominator);
    }
  //}
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  mpfi_clear(a1);
  mpfi_clear(nominator);
  return;
}


/*atanh_diff : reccurence formula: p_(n+1)=p'_n * (1-x^2) +2*n *x * p_n 
atan^(n)=p_(n)/((1-x^2)^n)
p_1=1;
*/
void atanh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow,a1,nominator;
  
    
  coeffs_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));

  for (index=0; index<=n-1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_init2(a1,getToolPrecision());
  mpfi_atanh(u, x);
  mpfi_init2(nominator,getToolPrecision());
  mpfi_sqr(nominator,x);
  mpfi_add_si(nominator, nominator,1);
  mpfi_set(res[0],u);
  //if (n==0) 
  //else
  //{
    for (index=0; index<=n-1; index++){
      if (index==0){
        mpfi_set_ui(coeffs_array[0],1);
        mpfi_set_ui(powers_array[0],1);
      }
      else if (index==1){
        mpfi_set_ui(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],2);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[1],x,pow);
      }
      else if (index==2){
        mpfi_set_si(coeffs_array[0],2);
        mpfi_set_ui(coeffs_array[1],0);
        mpfi_set_ui(coeffs_array[2],6);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[2],x,pow);
      }
      else if (index==3){
        mpfi_set_si(coeffs_array[0],0);
        mpfi_set_ui(coeffs_array[1],24);
        mpfi_set_ui(coeffs_array[2],0);
        mpfi_set_si(coeffs_array[3],24);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[3],x,pow);
      }
      else{
        //newcoeff(k)=(-(k-1) +2*n) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
        //the new coefficent added at index
        mpfi_set(coeffs_array[index],coeffs_array[index-1]);
        mpfi_mul_si(coeffs_array[index],coeffs_array[index],-(index-1)+2*(index));
        //keep the coeff at index-1     
        mpfi_set(oldCoeff,coeffs_array[index-1]);
        //modify at index with new value      
        mpfi_set(coeffs_array[index-1],coeffs_array[index-2]);
        mpfi_mul_si(coeffs_array[index-1],coeffs_array[index-1],-(index-2)+2*(index));
        //inter-extremities case
        for (i=index-2; i>1;i--){
          mpfi_set(s1,oldCoeff);
          mpfi_mul_si(s1,s1,i+1);
          mpfi_set(oldCoeff,coeffs_array[i]);
          mpfi_set(coeffs_array[i],coeffs_array[i-1]);
          mpfi_mul_si(coeffs_array[i],coeffs_array[i],-(i-1)+2*(index));
          mpfi_add(coeffs_array[i],coeffs_array[i], s1);
        } 
        //for a1 and ao special case
        //newa1=2*a2+2n*a0   newa0=a1      
        //compute 2*a2      
        mpfi_mul_si(oldCoeff, oldCoeff,2);      
        mpfi_set(a1, coeffs_array[1]);      
        //compute -2n*a0 
        mpfi_mul_si(coeffs_array[1],coeffs_array[0],2*(index));
        //add
        mpfi_add(coeffs_array[1], coeffs_array[1],oldCoeff);
        //modify at coeff 0 with new value      
        mpfi_set(coeffs_array[0],a1);
        //add in powers array one more power
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[index],x,pow);
      }
      //we have the coeffcients, we compute the result
     /* printf("index=%d",index);
      for (i=0;i<=index; i++){
        printInterval(coeffs_array[i]);
      }
      printf("\n");*/
      mpfi_set_ui(res[index+1],0);    
      for (i=0;i<=index; i++){
        mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
        mpfi_add(res[index+1],res[index+1],partialSum);
      } 
      mpfi_sqr(nominator,x);
      mpfi_si_sub(nominator, 1,nominator);
  
      mpfi_set_ui(pow,index+1);
      mpfi_pow(nominator,nominator,pow);
      mpfi_div(res[index+1],res[index+1],nominator);
    }
  //}
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  mpfi_clear(a1);
  mpfi_clear(nominator);
  return;
}






/*asin_diff : reccurence formula: p_(n+1)=p'_n * (1-x^2) +(2*n-1) *x * p_n 
asin^(n)=p_(n)/((1-x^2)^((2*n-1)/2))
p_1=1;
p_2=x;
p_3=2x^2+1
*/
void asin_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow,a1,nominator;
  
  //the polynomial for the nth derivative has degree n-1, need n coeffs  
  coeffs_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));

  for (index=0; index<=n-1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_init2(a1,getToolPrecision());
  mpfi_asin(u, x);
  //we need the nominator for dividing the polynominal by ((1-x^2)^((2*n-1)/2))
  mpfi_init2(nominator,getToolPrecision());
  mpfi_sqr(nominator,x);
  mpfi_si_sub(nominator, 1,nominator);
  //put the asin value in res[0]
  mpfi_set(res[0],u);
  //if (n==0) 
  //else
  //{
    for (index=0; index<=n-1; index++){
      if (index==0){
        mpfi_set_ui(coeffs_array[0],1);
        mpfi_set_ui(powers_array[0],1);
      }
      else if (index==1){
        mpfi_set_ui(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],1);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[1],x,pow);
      }
      else if (index==2){
        mpfi_set_si(coeffs_array[0],1);
        mpfi_set_ui(coeffs_array[1],0);
        mpfi_set_ui(coeffs_array[2],2);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[2],x,pow);
      }
      else if (index==3){
        mpfi_set_si(coeffs_array[0],0);
        mpfi_set_ui(coeffs_array[1],9);
        mpfi_set_ui(coeffs_array[2],0);
        mpfi_set_si(coeffs_array[3],6);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[3],x,pow);
      }
      else{
        //newcoeff(k)=(-(k-1) +(2*n-1)) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
        //the new coefficent added at index
        mpfi_set(coeffs_array[index],coeffs_array[index-1]);
        mpfi_mul_si(coeffs_array[index],coeffs_array[index],-(index-1)+(2*index-1));
        //keep the coeff at index-1     
        mpfi_set(oldCoeff,coeffs_array[index-1]);
        //modify at index with new value      
        mpfi_set(coeffs_array[index-1],coeffs_array[index-2]);
        mpfi_mul_si(coeffs_array[index-1],coeffs_array[index-1],-(index-2)+(2*index-1));
        //inter-extremities case
        for (i=index-2; i>1;i--){
          mpfi_set(s1,oldCoeff);
          mpfi_mul_si(s1,s1,i+1);
          mpfi_set(oldCoeff,coeffs_array[i]);
          mpfi_set(coeffs_array[i],coeffs_array[i-1]);
          mpfi_mul_si(coeffs_array[i],coeffs_array[i],-(i-1)+(2*index-1));
          mpfi_add(coeffs_array[i],coeffs_array[i], s1);
        } 
        //for a1 and ao special case
        //newa1=2*a2 +(2n-1)*a0   newa0=a1      
        //compute 2*a2      
        mpfi_mul_si(oldCoeff, oldCoeff,2);      
        mpfi_set(a1, coeffs_array[1]);      
        //compute (2n-1)*a0 
        mpfi_mul_si(coeffs_array[1],coeffs_array[0],2*index-1);
        //add
        mpfi_add(coeffs_array[1], coeffs_array[1],oldCoeff);
        //modify at coeff 0 with new value      
        mpfi_set(coeffs_array[0],a1);
        //add in powers array one more power
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[index],x,pow);
      }
      //we have the coeffcients, we compute the result
      /*printf("index=%d",index);
      for (i=0;i<=index; i++){
        printInterval(coeffs_array[i]);
      }
      printf("\n");*/
      mpfi_set_ui(res[index+1],0);    
      for (i=0;i<=index; i++){
        mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
        mpfi_add(res[index+1],res[index+1],partialSum);
      } 
      mpfi_sqr(nominator,x);
      mpfi_si_sub(nominator, 1,nominator);
  
      mpfi_set_si(pow,(2*index+1));
      mpfi_div_si(pow,pow,2);
      mpfi_pow(nominator,nominator,pow);
      mpfi_div(res[index+1],res[index+1],nominator);
    }
  //}
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  mpfi_clear(a1);
  mpfi_clear(nominator);
  return;
}

/*acos_diff : except for the res[0], all the terms are equal to -asin^(n)(x)
*/
void acos_diff(mpfi_t *res, mpfi_t x, int n) {
  int i;
 
  
  asin_diff(res,x,n);
  mpfi_acos(res[0],x);
  for (i=1; i<=n;i++)
    mpfi_mul_si(res[i],res[i],-1);
  return;
}

/*asinh_diff : reccurence formula: p_(n+1)=p'_n * (1+x^2) -(2*n-1) *x * p_n 
asin^(n)=p_(n)/((1+x^2)^((2*n-1)/2))
p_1=1;
p_2=-x;
p_3=2x^2-1
*/
void asinh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow,a1,nominator;
  
  //the polynomial for the nth derivative has degree n-1, need n coeffs  
  coeffs_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));

  for (index=0; index<=n-1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_init2(a1,getToolPrecision());
  mpfi_asinh(u, x);
  //we need the nominator for dividing the polynominal by ((1+x^2)^((2*n-1)/2))
  mpfi_init2(nominator,getToolPrecision());
  mpfi_sqr(nominator,x);
  mpfi_add_si(nominator, nominator,1);
  //put the asin value in res[0]
  mpfi_set(res[0],u);
  //if (n==0) 
  //else
  //{
    for (index=0; index<=n-1; index++){
      if (index==0){
        mpfi_set_ui(coeffs_array[0],1);
        mpfi_set_ui(powers_array[0],1);
      }
      else if (index==1){
        mpfi_set_ui(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],-1);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[1],x,pow);
      }
      else if (index==2){
        mpfi_set_si(coeffs_array[0],-1);
        mpfi_set_ui(coeffs_array[1],0);
        mpfi_set_ui(coeffs_array[2],2);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[2],x,pow);
      }
      else if (index==3){
        mpfi_set_si(coeffs_array[0],0);
        mpfi_set_ui(coeffs_array[1],9);
        mpfi_set_ui(coeffs_array[2],0);
        mpfi_set_si(coeffs_array[3],-6);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[3],x,pow);
      }
      else{
        //newcoeff(k)=(-(k-1) -(2*n-1)) coeff(k-1)+(k+1)coeff(k+1) except for the last two ones and first two ones
        //the new coefficent added at index
        mpfi_set(coeffs_array[index],coeffs_array[index-1]);
        mpfi_mul_si(coeffs_array[index],coeffs_array[index],(index-1)-(2*index-1));
        //keep the coeff at index-1     
        mpfi_set(oldCoeff,coeffs_array[index-1]);
        //modify at index with new value      
        mpfi_set(coeffs_array[index-1],coeffs_array[index-2]);
        mpfi_mul_si(coeffs_array[index-1],coeffs_array[index-1],(index-2)-(2*index-1));
        //inter-extremities case
        for (i=index-2; i>1;i--){
          mpfi_set(s1,oldCoeff);
          mpfi_mul_si(s1,s1,i+1);
          mpfi_set(oldCoeff,coeffs_array[i]);
          mpfi_set(coeffs_array[i],coeffs_array[i-1]);
          mpfi_mul_si(coeffs_array[i],coeffs_array[i],(i-1)-(2*index-1));
          mpfi_add(coeffs_array[i],coeffs_array[i], s1);
        } 
        //for a1 and ao special case
        //newa1=2*a2 -(2n-1)*a0   newa0=a1      
        //compute 2*a2      
        mpfi_mul_si(oldCoeff, oldCoeff,2);      
        mpfi_set(a1, coeffs_array[1]);      
        //compute -(2n-1)*a0 
        mpfi_mul_si(coeffs_array[1],coeffs_array[0],-(2*index-1));
        //add
        mpfi_add(coeffs_array[1], coeffs_array[1],oldCoeff);
        //modify at coeff 0 with new value      
        mpfi_set(coeffs_array[0],a1);
        //add in powers array one more power
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[index],x,pow);
      }
      //we have the coeffcients, we compute the result
      /*printf("index=%d",index);
      for (i=0;i<=index; i++){
        printInterval(coeffs_array[i]);
      }
      printf("\n");*/
      mpfi_set_ui(res[index+1],0);    
      for (i=0;i<=index; i++){
        mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
        mpfi_add(res[index+1],res[index+1],partialSum);
      } 
      mpfi_sqr(nominator,x);
      mpfi_add_si(nominator, nominator,1);
  
      mpfi_set_si(pow,(2*index+1));
      mpfi_div_si(pow,pow,2);
      mpfi_pow(nominator,nominator,pow);
      mpfi_div(res[index+1],res[index+1],nominator);
    }
  //}
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  mpfi_clear(a1);
  mpfi_clear(nominator);
  return;
}


/*acosh_diff : reccurence formula: p_(n+1)=p'_n * (x^2-1) -(2*n-1) *x * p_n 
asin^(n)=p_(n)/((x^2-1)^((2*n-1)/2))
p_1=1;
p_2=-x;
p_3=2x^2+1
*/
void acosh_diff(mpfi_t *res, mpfi_t x, int n) {
  int i,index;
  mpfi_t *coeffs_array, *powers_array, u, partialSum,s1,oldCoeff,pow,a1,nominator;
  
  //the polynomial for the nth derivative has degree n-1, need n coeffs  
  coeffs_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));
  powers_array = (mpfi_t *)safeMalloc( (n)*sizeof(mpfi_t));

  for (index=0; index<=n-1; index++){
    mpfi_init2(coeffs_array[index], getToolPrecision());
    mpfi_init2(powers_array[index], getToolPrecision());
  }
 

  mpfi_init2(partialSum,getToolPrecision());
  mpfi_init2(oldCoeff,getToolPrecision());
  mpfi_init2(s1,getToolPrecision());
  mpfi_init2(pow,getToolPrecision());
  mpfi_init2(u,getToolPrecision());
  mpfi_init2(a1,getToolPrecision());
  mpfi_acosh(u, x);
  //we need the nominator for dividing the polynominal by ((1+x^2)^((2*n-1)/2))
  mpfi_init2(nominator,getToolPrecision());
  mpfi_sqr(nominator,x);
  mpfi_add_si(nominator, nominator,1);
  //put the asin value in res[0]
  mpfi_set(res[0],u);
  //if (n==0) 
  //else
  //{
    for (index=0; index<=n-1; index++){
      if (index==0){
        mpfi_set_ui(coeffs_array[0],1);
        mpfi_set_ui(powers_array[0],1);
      }
      else if (index==1){
        mpfi_set_ui(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],-1);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[1],x,pow);
      }
      else if (index==2){
        mpfi_set_si(coeffs_array[0],1);
        mpfi_set_ui(coeffs_array[1],0);
        mpfi_set_ui(coeffs_array[2],2);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[2],x,pow);
      }
      else if (index==3){
        mpfi_set_si(coeffs_array[0],0);
        mpfi_set_si(coeffs_array[1],-9);
        mpfi_set_ui(coeffs_array[2],0);
        mpfi_set_si(coeffs_array[3],-6);
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[3],x,pow);
      }
      else{
        //newcoeff(k)=((k-1) -(2*n-1)) coeff(k-1)-(k+1)coeff(k+1) except for the last two ones and first two ones
        //the new coefficent added at index
        mpfi_set(coeffs_array[index],coeffs_array[index-1]);
        mpfi_mul_si(coeffs_array[index],coeffs_array[index],(index-1)-(2*index-1));
        //keep the coeff at index-1     
        mpfi_set(oldCoeff,coeffs_array[index-1]);
        //modify at index with new value      
        mpfi_set(coeffs_array[index-1],coeffs_array[index-2]);
        mpfi_mul_si(coeffs_array[index-1],coeffs_array[index-1],(index-2)-(2*index-1));
        //inter-extremities case
        for (i=index-2; i>1;i--){
          mpfi_set(s1,oldCoeff);
          mpfi_mul_si(s1,s1,-(i+1));
          mpfi_set(oldCoeff,coeffs_array[i]);
          mpfi_set(coeffs_array[i],coeffs_array[i-1]);
          mpfi_mul_si(coeffs_array[i],coeffs_array[i],(i-1)-(2*index-1));
          mpfi_add(coeffs_array[i],coeffs_array[i], s1);
        } 
        //for a1 and ao special case
        //newa1=-2*a2 -(2n-1)*a0   newa0=-a1      
        //compute -2*a2      
        mpfi_mul_si(oldCoeff, oldCoeff,-2);      
        mpfi_set(a1, coeffs_array[1]);      
        //compute -(2n-1)*a0 
        mpfi_mul_si(coeffs_array[1],coeffs_array[0],-(2*index-1));
        //add
        mpfi_add(coeffs_array[1], coeffs_array[1],oldCoeff);
        //modify at coeff 0 with new value      
        mpfi_mul_si(coeffs_array[0],a1,-1);
        //add in powers array one more power
        mpfi_set_ui(pow,index);
        mpfi_pow(powers_array[index],x,pow);
      }
      //we have the coeffcients, we compute the result
      /*printf("index=%d",index);
      for (i=0;i<=index; i++){
        printInterval(coeffs_array[i]);
      }
      printf("\n");*/
      mpfi_set_ui(res[index+1],0);    
      for (i=0;i<=index; i++){
        mpfi_mul(partialSum,coeffs_array[i],powers_array[i]);
        mpfi_add(res[index+1],res[index+1],partialSum);
      } 
      mpfi_sqr(nominator,x);
      mpfi_sub_si(nominator, nominator,1);
  
      mpfi_set_si(pow,(2*index+1));
      mpfi_div_si(pow,pow,2);
      mpfi_pow(nominator,nominator,pow);
      mpfi_div(res[index+1],res[index+1],nominator);
    }
  //}
  for (index=0; index<=n-1; index++){
    mpfi_clear(coeffs_array[index]);
    mpfi_clear(powers_array[index]);
  }
  mpfi_clear(oldCoeff);
  mpfi_clear(partialSum);
  mpfi_clear(s1);
  mpfi_clear(pow);
  mpfi_clear(a1);
  mpfi_clear(nominator);
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
    tan_diff(res,x,n);
    break;
  case ASIN:
    asin_diff(res,x,n);
    break;
  case ACOS:
    acos_diff(res,x,n);
    break;
  case ATAN:
     atan_diff(res,x,n);
    break;
  case SINH:
    sinh_diff(res,x,n);
    break;
  case COSH:
    cosh_diff(res,x,n);
    break;
  case TANH:
    tanh_diff(res,x,n);
    break;
  case ASINH:
    asinh_diff(res,x,n);
    break;
  case ACOSH:
    acosh_diff(res,x,n);
    break;
  case ATANH:
    atanh_diff(res,x,n);
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
    expm1_diff(res,x,n);
    break;
  case DOUBLEEXTENDED:
    break;
  case CEIL:
    break;
  case FLOOR:
    break;
  case NEARESTINT:
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
  mpfi_t *res1, *res2, *res3, *res4, *res5, *res6;
  mpfr_t minusOne;
  node *simplifiedChild1, *simplifiedChild2;
  mpfi_t temp1,temp2;
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
  case NEARESTINT:

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
    
    break;
  case POW:
    
    if (((f->child2)->nodeType==CONSTANT) && ((f->child1)->nodeType==VARIABLE)){
      constantPower_diff(res,*(f->child2->value) , x, n);
    }
    else{
      simplifiedChild2=simplifyTreeErrorfree(f->child2);
      simplifiedChild1=simplifyTreeErrorfree(f->child1);
      
      if ((simplifiedChild2->nodeType==CONSTANT) &&(simplifiedChild1->nodeType==CONSTANT)) { //we have the ct1^ct2 case
         // printf("We are in the  ct1^ct2 case");       
         mpfi_init2(temp1, getToolPrecision());
         mpfi_set_fr(temp1, *(simplifiedChild1->value));
         mpfi_init2(temp2, getToolPrecision());
         mpfi_set_fr(temp2, *(simplifiedChild2->value));
         mpfi_pow(res[0],temp1,temp2);
         for(i=1;i<=n;i++) mpfi_set_ui(res[i],0);

         mpfi_clear(temp1);
         mpfi_clear(temp2);
      }
      else if (simplifiedChild2->nodeType==CONSTANT) { //we have the f^p case
        //printf("We are in the  f^p case");        
        res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
        res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
        for(i=0;i<=n;i++) {
          mpfi_init2(res1[i], getToolPrecision());
          mpfi_init2(res2[i], getToolPrecision());
        }
        auto_diff(res1, f->child1, x, n);
        constantPower_diff(res2,*(simplifiedChild2->value) , res1[0], n);
        composition_AD(res, res2, res1, n); 
        for(i=0;i<=n;i++) {
          mpfi_clear(res1[i]);
          mpfi_clear(res2[i]); 
        }
        free(res1);
        free(res2);    
      } 
       else if (simplifiedChild1->nodeType==CONSTANT) { //we have the p^f case
        //printf("We are in the  p^f case");     
        res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
        res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
        for(i=0;i<=n;i++) {
          mpfi_init2(res1[i], getToolPrecision());
          mpfi_init2(res2[i], getToolPrecision());
        }
        auto_diff(res1, f->child2, x, n);
        powerFunction_diff(res2,*(simplifiedChild1->value) , res1[0], n);
        composition_AD(res, res2, res1, n); 
        for(i=0;i<=n;i++) {
          mpfi_clear(res1[i]);
          mpfi_clear(res2[i]); 
        }
        free(res1);
        free(res2);    
      } 
      else {
      //printf("We are in the  f^g case");     
      res1 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      res2 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      res3 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      res4 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      res5 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      res6 = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
      for(i=0;i<=n;i++) {
        mpfi_init2(res1[i], getToolPrecision());
        mpfi_init2(res2[i], getToolPrecision());
        mpfi_init2(res3[i], getToolPrecision());
        mpfi_init2(res4[i], getToolPrecision());
        mpfi_init2(res5[i], getToolPrecision());
        mpfi_init2(res6[i], getToolPrecision());
      }

      
      auto_diff(res1, f->child1, x, n);
      log_diff(res2,res1[0],n);
      composition_AD(res3, res2, res1, n);
      auto_diff(res4,f->child2,x,n);
      multiplication_AD(res5,res3,res4,n);
      exp_diff(res6,res5[0],n);
      composition_AD(res,res6,res5,n);
      
      for(i=0;i<=n;i++) {
        mpfi_clear(res1[i]);
        mpfi_clear(res2[i]);
        mpfi_clear(res3[i]);
        mpfi_clear(res4[i]);
        mpfi_clear(res5[i]);
        mpfi_clear(res6[i]);
      }
      free(res1);
      free(res2);
      free(res3);
      free(res4);
      free(res5);
      free(res6);

    }
    free_memory(simplifiedChild2);
    free_memory(simplifiedChild1);
  }
    break;

  case LIBRARYFUNCTION:
    break;

  default:
   fprintf(stderr,"Error: AD: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }

  return;
}
