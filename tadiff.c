/*
  For compiling this file:
    gcc -fPIC -Wall -c tadiff.c
    gcc -fPIC -shared -o tadiff tadiff.o


  Within Sollya:
    > externalproc(TM, "./tadiff", (function, range, integer) -> list of range);

  And then, for instance:
    > TM(exp(x)*cos(x), [2.5; 2.6], 10);

*/


#include "sollya.h"

extern int mpfi_pow(mpfi_t res, mpfi_t x, mpfi_t y);
extern void fprintInterval(FILE *fd, mpfi_t interval);
extern chain *uncertifiedFindZeros(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);
extern void freeMpfrPtr(void *ptr);

typedef struct taylorCoeffs {
int n; 
mpfi_t *poly_array;
mpfi_t x;
} tSeries;




/* This function performs the taylor truncated series.
   See the commentaries below.
*/
void taylor_series(tSeries *t, node *f);

/*This function creates an empty taylor series
Allocates memory for array, initializes mpfi-s
*/
tSeries* createEmptytSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
 // printf("\nin createEmptyTS\n ");
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],x);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  return t;
}

/*This function dealocates a taylor series
*/
void cleartSeries(tSeries *t){
  int i;
  for(i=0;i<=t->n;i++) mpfi_clear(t->poly_array[i]);
  free(t->poly_array);
  mpfi_clear(t->x);
  free(t);
}

/*This function pretty prints a taylor series
*/
void printtSeries(tSeries *t){
  int i;
  printf("\nTaylor series of order, %d:", t->n);
  for(i=0;i<=t->n;i++) {
    printInterval(t->poly_array[i]);
    printf(",");
  }  
  printf("\n");  
  }


/*This function sets a taylor series t 
with the values given by anoter ts tt
they implicitely have the same order and interval
(are from the same family)
*/
void settSeries(tSeries *t, tSeries *tt){
  int i;
  for(i=0;i<=tt->n;i++) {
    mpfi_set(t->poly_array[i],tt->poly_array[i]);
  }  
}

/*This function computes an interval bound
for a polynomial given by coeffs and order n, 
on int x, using basic IA and Horner form
*/
void polynomialBound(mpfi_t *bound,int n,mpfi_t *coeffs,mpfi_t x){
  int i;
  mpfi_t r;
  mpfi_init2(r,getToolPrecision());
  mpfi_set(r,coeffs[n]);
  for (i=n-1;i>=0;i--){
  mpfi_mul(r,r,x);
  mpfi_add(r,r,coeffs[i]);
  }
  mpfi_set(*bound,r);
  mpfi_clear(r);
}
/*This function transforms an polynomial with interval coeffs
into a poly with mpfr coeffs and a small remainder
*/
void mpfr_get_poly(mpfr_t *rc, mpfi_t rest, int n, mpfi_t *gc, mpfi_t x){
  int i;
  mpfi_t *res;
  mpfi_t r;
  res= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  mpfi_init2(r,getToolPrecision());
  for (i=0; i<=n; i++){
    mpfi_mid(rc[i],gc[i]);
    mpfi_init2(res[i], getToolPrecision());
    mpfi_sub_fr(res[i],gc[i], rc[i]);
  }
  polynomialBound(&r,n,res,x);
  
  mpfi_set(rest,r);
  
  for (i=0; i<=n; i++){
    mpfi_clear(res[i]);  
  }
  free(res);
  mpfi_clear(r);
  return;

}

/*This function computes a sharp interval bound
for a polynomial given by coeffs and order n, 
on int x, using dirtyfindzeros - for the moment
this function is not certified:
**Sturm's nr of roots test is not integrated**
**The mpfr's obtained for the roots are not expanded
into small intervals arround the true root**
*/
void polynomialBoundSharp(mpfi_t *bound,int n,mpfi_t *coeffs,mpfi_t x){
  int i;
  mpfi_t r,partialBound;
 
  mpfr_t *polyCoeffs;
  node *poly, *diff_poly;
  mpfr_t a, b;
  chain *zeros;
  mpfi_t *rootsIntervals;
  mpfr_t inf, sup, pinf, psup;
  mpfi_t extr1;
  int points, nrRoots;
  points =100;
  
  mpfi_init2(r,getToolPrecision());
  mpfi_init2(partialBound, getToolPrecision());
  
  polyCoeffs= (mpfr_t *)safeMalloc((n+1)*sizeof(mpfr_t));
  for (i=0; i<=n; i++){
  mpfr_init2(polyCoeffs[i], getToolPrecision());  
  }
  mpfr_init2(a, getToolPrecision());
  mpfr_init2(b, getToolPrecision());    
  
  mpfi_get_left(a,x);
  mpfi_get_right(b,x);
  //transform the interval coeffs into mpfr + I;
  //printf("\nWe transform into mpfrs the coeffs of poly\n");
  
  mpfr_get_poly(polyCoeffs, r, n,coeffs, x);
  
 //transform the polynomial with mpfr_coeffs into a node * p
 poly=makePolynomial(polyCoeffs, n);
 
 //derivate the polynomial
 diff_poly = differentiate(poly);
 //find the zeros
 zeros =uncertifiedFindZeros(diff_poly, a, b, points, getToolPrecision());
 nrRoots=lengthChain(zeros);
 rootsIntervals= (mpfi_t *)safeMalloc((nrRoots)*sizeof(mpfi_t));
 for(i=0;i<nrRoots;i++){
  mpfi_init2(rootsIntervals[i],getToolPrecision());
  mpfi_set_fr(rootsIntervals[i],*((mpfr_t*)zeros->value));
 }
 
 //compute an enclosure for each root zeros-----> rootsIntervals, nrRoots
 /*
 for i from nRight-1 to 0 by -1 do {
  if(procVerbosity>=3) then print("Finding an enclosure for the root number ",i);
  test = false;
  precisionForRounding = oldprec;
  while (!test) do {
    a = round(listRight[i], precisionForRounding, RD);
    b = round(listRight[i], precisionForRounding, RU);
    ya = evaluate(q-sup(errorRange), [a;a]);
    yb = evaluate(q-sup(errorRange), [b;b]);

    if (sup(ya)<0 && inf(yb)>0)
    then { listRightIntervals = [a;b].:listRightIntervals ;
           listRightSigns = -1.:listRightSigns;
           test = true;
         }
    else {
    if (inf(ya)>0 && sup(yb)<0)
    then { listRightIntervals = [a;b].:listRightIntervals ;
           listRightSigns = 1.:listRightSigns;
           test = true;
         }
    else { precisionForRounding = precisionForRounding-10;
           if(procVerbosity>=3) then print("Looping... (precision = ",precisionForRounding,")");
         };
    };
  };*/
  
  //compute the the bound for each small interval for the initial polynomial
  mpfr_init2(inf,getToolPrecision());
  mpfr_init2(sup,getToolPrecision());
  mpfr_init2(pinf,getToolPrecision());
  mpfr_init2(psup,getToolPrecision());
  //take the values in the extremas of the interval
  mpfi_init2(extr1,getToolPrecision());
  mpfi_set_fr(extr1,a);
  polynomialBound(&partialBound,n, coeffs,extr1);
  mpfi_get_left(inf, partialBound);
  mpfi_get_right(sup,partialBound);
  
    for (i=0;i<nrRoots;i++){
      polynomialBound(&partialBound,n, coeffs,rootsIntervals[i]);
      mpfi_get_left(pinf, partialBound);
      mpfi_get_right(psup,partialBound);
      if (mpfr_less_p(pinf,inf)!=0) mpfr_set(inf, pinf,GMP_RNDN);
      if (mpfr_greater_p(psup,sup)!=0) mpfr_set(sup,psup,GMP_RNDU);
    }
    
  mpfi_init2(extr1,getToolPrecision());
  mpfi_set_fr(extr1,b);
  polynomialBound(&partialBound,n, coeffs,extr1);  
  mpfi_get_left(pinf, partialBound);
  mpfi_get_right(psup,partialBound);
  if (mpfr_less_p(pinf,inf)!=0) mpfr_set(inf, pinf,GMP_RNDN);
  if (mpfr_greater_p(psup,sup)!=0) mpfr_set(sup,psup,GMP_RNDU);
  
  mpfi_interv_fr(partialBound, inf,sup);
  mpfi_add(r,r,partialBound);
  mpfi_set(*bound,r);
  
  
  
  mpfi_clear(r);
  mpfi_clear(partialBound);
  mpfi_clear(extr1);
  freeChain(zeros,freeMpfrPtr);
  for(i=0;i<nrRoots;i++){
  mpfi_clear(rootsIntervals[i]);
  }
  free(rootsIntervals);
  
  for(i=0;i<=n;i++){
    mpfr_clear(polyCoeffs[i]);
  }
  free(polyCoeffs);
  
  mpfr_clear(a);
  mpfr_clear(b);  
  mpfr_clear(inf);
  mpfr_clear(sup);
  mpfr_clear(pinf);
  mpfr_clear(psup);  
  free_memory(poly);
  free_memory(diff_poly);  
  
}


int TAD(chain **res, void **args) {
  node *f;
  mpfi_t x;
  int i,n;
  
  mpfi_t *temp;
  tSeries* t;
  f = (node *)args[0];
  n = *( (int *)args[2] );

  
  
  mpfi_init2(x, getToolPrecision());
  mpfi_set(x, *( (mpfi_t *)args[1] ));
  //printf("we will create a taylor series");
  t= createEmptytSeries(n,x);
  //printf("we created the empty ts\n");
  taylor_series(t, f);

  *res = NULL;
   
  for(i=n;i>=0;i--) {
    temp = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp, getToolPrecision());
    mpfi_set(*temp, t->poly_array[i]);
    *res = addElement(*res, temp);
  }
    
  
  free(t->poly_array);
  free(t);
  mpfi_clear(x);
	   
  return 1;
}
/*This function gets an mpfi from a node c:
if c constant after simplification-> ok
if not 0
*/
int mpfi_set_node( mpfi_t *r, node * c) {
  mpfi_t rr;
  node *cc;
  mpfi_init2(rr,getToolPrecision());
  if (c!=NULL){
    cc=simplifyTreeErrorfree(c);
    switch (cc->nodeType){
      case PI_CONST: mpfi_const_pi(rr);
      break;
      case CONSTANT:mpfi_set_fr(rr,*(cc->value));
      break;
      default: mpfi_set_ui(rr,0);
      break;
      }
    free(cc);
  }
  else mpfi_set_ui(rr,0);
  mpfi_set(*r,rr);
  mpfi_clear(rr);
  return 0;
}

/*This function computes the ts for multiplication of two 
given ts's 
*/
void  multiplication_TS(tSeries *t,tSeries *c1, tSeries *c2){
  //we will multiply two taylor series of order n; and obtain a new taylor series of order n;
  int n,i,k;
 // mpfi_t *r;
  tSeries *tt;
  //printf("in multiplication TS");
  n=t->n;
  //aux ts for doing the multiplications
  
  tt=createEmptytSeries(n,t->x);
  mpfi_set_ui(tt->poly_array[0],0);
  
  mpfi_t temp1;
  mpfi_init2(temp1, getToolPrecision());
  
  
  //new series;
  for(k=0; k<=n;k++)
    for (i=0;i<=k;i++){
      mpfi_mul(temp1,c1->poly_array[i], c2->poly_array[k-i]);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
    }
   
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tt);
  //clear the aux ts;
  cleartSeries(tt);
 }


/*This function computes the ts for addition of two 
given ts's 
*/
void addition_TS(tSeries *t,tSeries *child1_ts, tSeries *child2_ts){
  int i;
  int n;
  tSeries *tt;
  n=t->n;
  tt=createEmptytSeries(n,t->x);
  for(i=0;i<=n;i++)  mpfi_add(tt->poly_array[i], child1_ts->poly_array[i],child2_ts->poly_array[i]);
  settSeries(t,tt);
  cleartSeries(tt);
}

/*This function computes the ts for division
with a ct term of a given ts
*/
void ctDivision_TM(tSeries*t, mpfi_t c){
  int i;
  int n;
  n=t->n;
  
  for(i=0;i<=n;i++)  mpfi_div(t->poly_array[i],t->poly_array[i],c);
  
}

/*This function computes the ts for multiplication
with a ct term of a given ts
*/
void ctMultiplication_TM(tSeries*t, mpfi_t c){
  int i;
  int n;
  n=t->n;
  
  for(i=0;i<=n;i++)  mpfi_mul(t->poly_array[i],t->poly_array[i],c);
}



tSeries* createExptSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
  mpfi_t temp, fact;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_exp(temp,x);
  
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact,1);
  
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_mul_ui(fact, fact, i);
    mpfi_div(t->poly_array[i],temp,fact);
  }
  mpfi_clear(temp);
  mpfi_clear(fact);
  return t;
}


tSeries* createConsttSeries(int n,  mpfi_t x, mpfi_t ct){ 
  tSeries* t;
  int i;
  mpfi_t temp;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_set(temp,ct);
  
   
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  mpfi_clear(temp);
  
  return t;
}

tSeries* createPiConsttSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
  mpfi_t temp;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_const_pi(temp);
  
   
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  mpfi_clear(temp);
  
  return t;
}

tSeries* createVartSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
  mpfi_t temp;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_set(temp, x);
  
   
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp);
  
  if (n>=1){
    mpfi_init2(t->poly_array[1], getToolPrecision());
    mpfi_set_ui(t->poly_array[1],1);
  }
  
  for(i=2;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  mpfi_clear(temp);
  
  return t;
}






tSeries* createSintSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
  mpfi_t temp1, temp2, temp3, temp4;
  mpfi_t fact;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact,1);
  
  mpfi_init2(temp1, getToolPrecision());
  mpfi_sin(temp1,x);
  mpfi_init2(temp3, getToolPrecision());
  mpfi_mul_si(temp3,temp1,-1);
   
  mpfi_init2(temp2, getToolPrecision());
  mpfi_cos(temp2,x);
  mpfi_init2(temp4, getToolPrecision());
  mpfi_mul_si(temp4,temp1,-1);
  
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp1);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    if (i%4==0) mpfi_set(t->poly_array[i],temp1);
    else if (i%4==1) mpfi_set(t->poly_array[i],temp2);
    else if (i%4==2) mpfi_set(t->poly_array[i],temp3);
    else mpfi_set(t->poly_array[i],temp4);
    mpfi_mul_ui(fact, fact, i);
    mpfi_div(t->poly_array[i],t->poly_array[i],fact);
  }
  mpfi_clear(temp1);
  mpfi_clear(temp2);
  mpfi_clear(temp3);
  mpfi_clear(temp4);
  mpfi_clear(fact);
  
  return t;
}

tSeries* createCostSeries(int n,  mpfi_t x){ 
  tSeries* t;
  int i;
  mpfi_t temp1, temp2, temp3, temp4;
  mpfi_t fact;
  
  t= (tSeries *)safeMalloc(sizeof(tSeries));
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact,1);
  
  mpfi_init2(temp1, getToolPrecision());
  mpfi_cos(temp1,x);
  
  mpfi_init2(temp3, getToolPrecision());
  mpfi_mul_si(temp3,temp1,-1);
   
  mpfi_init2(temp4, getToolPrecision());
  mpfi_sin(temp4,x);
  
  mpfi_init2(temp2, getToolPrecision());
  mpfi_mul_si(temp2,temp4,-1);
  
  mpfi_init2(t->poly_array[0], getToolPrecision());
  mpfi_set(t->poly_array[0],temp1);
  
  for(i=1;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    if (i%4==0) mpfi_set(t->poly_array[i],temp1);
    else if (i%4==1) mpfi_set(t->poly_array[i],temp2);
    else if (i%4==2) mpfi_set(t->poly_array[i],temp3);
    else mpfi_set(t->poly_array[i],temp4);
    mpfi_mul_ui(fact, fact, i);
    mpfi_div(t->poly_array[i],t->poly_array[i],fact);
  }
  mpfi_clear(temp1);
  mpfi_clear(temp2);
  mpfi_clear(temp3);
  mpfi_clear(temp4);
  mpfi_clear(fact);
  
  return t;
}

/*This function computes the ts for exp(given_ts)
It uses the formulas given in :
Bendtsen, Stauning - TADIFF, a flexible c++ package for automatic differentiation
using taylor series expansion, 1997
pag 5 - (13)
*/
void exp_TS(tSeries *t, tSeries *child1_ts){
  int i,n,k;
  
  mpfi_t temp1;
  tSeries *tt,*tc, *ttt;
  
 // printf("in exp_TS");
  n=t->n;
  //additional tms for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  printtSeries(tc);
  
  tt=createExptSeries(n,tc->poly_array[0]);
  printtSeries(tt);   
  
  ttt=createEmptytSeries(n,tt->x);
  
  mpfi_set(ttt->poly_array[0],tt->poly_array[0]);
  
  mpfi_init2(temp1, getToolPrecision());
   
  //new series;
  for(k=1; k<=n;k++){
    for (i=0;i<=k-1;i++){
      mpfi_mul(temp1,tt->poly_array[i], tc->poly_array[k-i]);
      mpfi_mul_ui(temp1,temp1, k-i);
      mpfi_add(ttt->poly_array[k],ttt->poly_array[k],temp1);
    }
    mpfi_div_ui(ttt->poly_array[k],ttt->poly_array[k],k);
  }
   
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,ttt);
  
  
  cleartSeries(tc);
  cleartSeries(tt);
  cleartSeries(ttt);
}


/*This function computes the ts for sin(given_ts)
It uses the formulas given in :
Bendtsen, Stauning - TADIFF, a flexible c++ package for automatic differentiation
using taylor series expansion, 1997
pag 5 - (15)
*/
void sin_TS(tSeries *t, tSeries *child1_ts){
  int j,n,k,i;
  
  mpfi_t temp1;
  tSeries *tsin,*tcos,*tc;
 // printf("in sin_TS");
  n=t->n;
  //additional tms for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  
  tsin=createEmptytSeries(n,t->x);
  mpfi_sin(tsin->poly_array[0],tc->poly_array[0]);
  
  tcos=createEmptytSeries(n,t->x);
  mpfi_cos(tcos->poly_array[0],tc->poly_array[0]);
  
   
  mpfi_init2(temp1, getToolPrecision());
   
   
  //new series;
  for(k=1; k<=n;k++){
    for (j=0;j<=k-1;j++){
      if (j>0){
        for(i=0;i<=j-1;i++){
          mpfi_mul(temp1,tsin->poly_array[i], tc->poly_array[j-i]);
          mpfi_mul_ui(temp1,temp1, j-i);
          mpfi_add(tcos->poly_array[j],tcos->poly_array[j],temp1);
        }
        mpfi_div_si(tcos->poly_array[j],tcos->poly_array[j],-j);
      }
      mpfi_mul(temp1,tcos->poly_array[j], tc->poly_array[k-j]);
      mpfi_mul_ui(temp1,temp1, k-j);
      mpfi_add(tsin->poly_array[k],tsin->poly_array[k],temp1);
    }
    mpfi_div_ui(tsin->poly_array[k],tsin->poly_array[k],k);
  }
   
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tsin);
  
  
  cleartSeries(tc);
  cleartSeries(tsin);
  cleartSeries(tcos);
}




/*This function computes the ts for sin(given_ts)
It uses the formulas given in :
Bendtsen, Stauning - TADIFF, a flexible c++ package for automatic differentiation
using taylor series expansion, 1997
pag 5 - (14)
*/
void cos_TS(tSeries *t, tSeries *child1_ts){
  int j,n,k,i;
  
  mpfi_t temp1;
  tSeries *tsin,*tcos,*tc;
 // printf("in sin_TS");
  n=t->n;
  //additional tms for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  
  tsin=createEmptytSeries(n,t->x);
  mpfi_sin(tsin->poly_array[0],tc->poly_array[0]);
  
  tcos=createEmptytSeries(n,t->x);
  mpfi_cos(tcos->poly_array[0],tc->poly_array[0]);
  
   
  mpfi_init2(temp1, getToolPrecision());
   
   
  //new series;
  for(k=1; k<=n;k++){
    for (j=0;j<=k-1;j++){
      if (j>0){
        for(i=0;i<=j-1;i++){
          mpfi_mul(temp1,tcos->poly_array[i], tc->poly_array[j-i]);
          mpfi_mul_ui(temp1,temp1, j-i);
          mpfi_add(tsin->poly_array[j],tsin->poly_array[j],temp1);
        }
        mpfi_div_ui(tsin->poly_array[j],tsin->poly_array[j],j);
      }
      mpfi_mul(temp1,tsin->poly_array[j], tc->poly_array[k-j]);
      mpfi_mul_ui(temp1,temp1, k-j);
      mpfi_add(tcos->poly_array[k],tcos->poly_array[k],temp1);
    }
    mpfi_div_si(tcos->poly_array[k],tcos->poly_array[k],-k);
  }
   
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tcos);
  
  
  cleartSeries(tc);
  cleartSeries(tsin);
  cleartSeries(tcos);
}


void division_TS(tSeries *t, tSeries *child1_ts, tSeries *child2_ts){
  int i,n,k;
  
  mpfi_t temp1;
  tSeries *tt,*tc1, *tc2;
 // printf("in division_TS");
  n=t->n;
  //additional tms for computations
  tc1=createEmptytSeries(n,child1_ts->x);
  settSeries(tc1,child1_ts);
  
  tc2=createEmptytSeries(n,child2_ts->x);
  settSeries(tc2,child2_ts);
  
  tt=createEmptytSeries(n,t->x);
     
  mpfi_init2(temp1, getToolPrecision());
  mpfi_div(temp1, tc1->poly_array[0], tc2->poly_array[0]);
  mpfi_set ( tt->poly_array[0], temp1);
  
  //new series;
  for(k=1; k<=n;k++){
    for (i=1;i<=k;i++){
      mpfi_mul(temp1,tc2->poly_array[i], tt->poly_array[k-i]);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
    }
    mpfi_sub(tt->poly_array[k],tc1->poly_array[k],tt->poly_array[k]);
    mpfi_div(tt->poly_array[k],tt->poly_array[k],tc2->poly_array[0]);
  }
   
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tt);
  
  
  cleartSeries(tc1);
  cleartSeries(tc2);
  cleartSeries(tt);
}




/*This function computes the ts for sqrt(given_ts)
It uses the formulas given in :
Bendtsen, Stauning - TADIFF, a flexible c++ package for automatic differentiation
using taylor series expansion, 1997
pag 4 - (11)
*/

void sqrt_TS(tSeries *t, tSeries *child1_ts){
  int i,k,p,n;
  
  mpfi_t temp1, temp2;
  tSeries *tt,*tc;
 // printf("in sqrt_TS");
  n=t->n;
  //additional ts for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  tt=createEmptytSeries(n,tc->poly_array[0]);
  mpfi_sqrt(tt->poly_array[0],tc->poly_array[0]);
  
  mpfi_init2(temp1, getToolPrecision());
   
  mpfi_init2(temp2, getToolPrecision());
  
  //new series;
  for(k=1; k<=n;k++){
    mpfi_div(temp2, tc->poly_array[k], tt->poly_array[0]);
    mpfi_div_ui(temp2, temp2, 2);
    if (k%2!=0){
      p=(k-1)/2;
      for (i=1;i<=p;i++){
      mpfi_mul(temp1,tt->poly_array[i], tt->poly_array[k-i]);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
    }
    mpfi_mul_ui(tt->poly_array[k],tt->poly_array[k],2);
    mpfi_sub(tt->poly_array[k], temp2, tt->poly_array[k]);   
    }
    else {
    p=(k-2)/2;
      for (i=1;i<=p;i++){
      mpfi_mul(temp1,tt->poly_array[i], tt->poly_array[k-i]);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
    }
    mpfi_mul_ui(tt->poly_array[k],tt->poly_array[k],2);
    mpfi_sub(tt->poly_array[k], temp2, tt->poly_array[k]);  
    
    mpfi_mul(temp2, tt->poly_array[k/2], tt->poly_array[k/2]);
    
    mpfi_add(tt->poly_array[k], tt->poly_array[k], temp2);
    
    }
    
  }
   
  mpfi_clear(temp1);
  mpfi_clear(temp2);
 
  //set the result
  settSeries(t,tt);
  
  
  cleartSeries(tc);
  cleartSeries(tt);
}


/*This function computes the ts for log(given_ts)
It uses the formulas given in :
Bendtsen, Stauning - TADIFF, a flexible c++ package for automatic differentiation
using taylor series expansion, 1997
pag 4 - (17)
*/

void log_TS(tSeries *t, tSeries *child1_ts){
  int k,j,n;
  
  mpfi_t temp1;
  tSeries *tt,*tc;
 // printf("in log_TS");
  n=t->n;
  //additional ts for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  tt=createEmptytSeries(n,tc->poly_array[0]);
  mpfi_log(tt->poly_array[0],tc->poly_array[0]);
  
  mpfi_init2(temp1, getToolPrecision());
   
  //new 
  for(k=1; k<=n;k++){
      for (j=1;j<=k-1;j++){
      mpfi_mul(temp1,tt->poly_array[j], tc->poly_array[k-j]);
      mpfi_mul_ui(temp1, temp1,j);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
      }
    mpfi_div_ui(tt->poly_array[k],tt->poly_array[k],k);
    mpfi_sub(tt->poly_array[k], tc->poly_array[k],tt->poly_array[k]);   
    mpfi_div(tt->poly_array[k],tt->poly_array[k],tc->poly_array[0]);
    }
    
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tt);
  
  
  cleartSeries(tc);
  cleartSeries(tt);
}



void tan_TS(tSeries *t, tSeries *child1_ts){
  int k,j,n;
  
  mpfi_t temp1;
  tSeries *tt,*tc;
 // printf("in log_TS");
  n=t->n;
  //additional ts for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  tt=createEmptytSeries(n,tc->poly_array[0]);
  mpfi_tan(tt->poly_array[0],tc->poly_array[0]);
  
  mpfi_init2(temp1, getToolPrecision());
   
  //new 
  for(k=1; k<=n;k++){
      for (j=1;j<=k-1;j++){
      mpfi_mul(temp1,tt->poly_array[j], tc->poly_array[k-j]);
      mpfi_mul_ui(temp1, temp1,j);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp1);
      }
    mpfi_div_ui(tt->poly_array[k],tt->poly_array[k],k);
    mpfi_sub(tt->poly_array[k], tc->poly_array[k],tt->poly_array[k]);   
    mpfi_div(tt->poly_array[k],tt->poly_array[k],tc->poly_array[0]);
    }
    
  mpfi_clear(temp1);
 
  //set the result
  settSeries(t,tt);
  
  
  cleartSeries(tc);
  cleartSeries(tt);
}
/*the power formula from tadiff is worse than our composition formula.
Reason: when using interval arithmetic: u^a/u \neq u^(a-1)
This formula has another drawback when u contains 0
*/
void ctPower_TS(tSeries *t, tSeries *child1_ts, mpfi_t a){
  int k,j,n;
  
  mpfi_t temp1, temp2;
  tSeries *tt,*tc;
  
  n=t->n;
  //additional tms for computations
  tc=createEmptytSeries(n,t->x);
  settSeries(tc,child1_ts);
  
  
  tt=createEmptytSeries(n,tc->poly_array[0]);
  mpfi_pow(tt->poly_array[0],tc->poly_array[0],a);
  
  mpfi_init2(temp1, getToolPrecision());
   
  mpfi_init2(temp2, getToolPrecision());
  
  //new series;
  for(k=1; k<=n;k++){
    
    for (j=0;j<=k-1;j++){
      mpfi_mul(temp1,tt->poly_array[j], tc->poly_array[k-j]);
      mpfi_mul_ui(temp2,a,k-j);
      mpfi_sub_si(temp2,temp2,j);
      mpfi_mul(temp2,temp1,temp2);
      mpfi_add(tt->poly_array[k],tt->poly_array[k],temp2);
    }
    
    mpfi_div_ui(tt->poly_array[k],tt->poly_array[k],k);
    mpfi_div(tt->poly_array[k], tt->poly_array[k],tc->poly_array[0]);   
    
  }    
  
  
     
  mpfi_clear(temp1);
  mpfi_clear(temp2);
 
  //set the result
  settSeries(t,tt);
  
  
  cleartSeries(tc);
  cleartSeries(tt);
}


void taylor_series(tSeries *t, node *f) {
  int i;
 // mpfi_t *res1, *res2, *res3, *res4, *res5, *res6;
  //mpfi_t *rem_bound1, *rem_bound2;
 // mpfr_t minusOne;
  node *simplifiedChild1, *simplifiedChild2;
  mpfi_t temp1,temp2;
  //node **coefficients;
  //mpfi_t *rpoly, *boundRpoly;
  tSeries *child1_ts, *child2_ts;
  mpfi_t ct;
  int n;
  //mpfi_t powx,powy;
  
  n=t->n;
  switch (f->nodeType) {

  case VARIABLE:
    child1_ts=createVartSeries(n, t->x);
    settSeries(t, child1_ts);
    cleartSeries(child1_ts);
    break;
  case PI_CONST:
    child1_ts=createPiConsttSeries(n, t->x);
    settSeries(t, child1_ts);
    cleartSeries(child1_ts);
    break;
  
  case CONSTANT:
    mpfi_init2(ct, getToolPrecision());
    mpfi_set_fr(ct, *(f->value));
    child1_ts=createConsttSeries(n, t->x,ct );
    settSeries(t, child1_ts);
    cleartSeries(child1_ts);
    mpfi_clear(ct);
    break;

  case NEG:
    //create a new empty taylor series for the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the child
    taylor_series(child1_ts, f->child1);
    //do the necessary chages from child to parent
    for(i=0;i<=n;i++)  mpfi_neg(t->poly_array[i], child1_ts->poly_array[i]);
        
    //clear old taylor series
    cleartSeries(child1_ts);
    break;

  case ADD:
  
  //create a new empty taylor series for the children
    child1_ts=createEmptytSeries(n, t->x);
    child2_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the children
    taylor_series(child1_ts, f->child1);
    taylor_series(child2_ts, f->child2);
    //do the necessary chages from children to parent
    
    addition_TS(t,child1_ts, child2_ts);
    //clear old taylor model
    cleartSeries(child1_ts);
    cleartSeries(child2_ts);
    break;

  case SUB:
    printf("in SUB");
    //create a new empty taylor series the children
    child1_ts=createEmptytSeries(n, t->x);
    child2_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the children
    taylor_series(child1_ts, f->child1);
    taylor_series(child2_ts, f->child2);
    //do the necessary chages from children to parent
    for(i=0;i<=n;i++)  mpfi_sub(t->poly_array[i], child1_ts->poly_array[i],child2_ts->poly_array[i]);
    
    //clear old taylor series
    cleartSeries(child1_ts);
    cleartSeries(child2_ts);
    break;

  case MUL:
   //create a new empty taylor series the children
    child1_ts=createEmptytSeries(n, t->x);
    child2_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the children
    taylor_series(child1_ts, f->child1);
    taylor_series(child2_ts, f->child2);
    //do the necessary chages from children to parent
    multiplication_TS(t,child1_ts, child2_ts);
    
    //clear old taylor series
    cleartSeries(child1_ts);
    cleartSeries(child2_ts);
    break;

  case DIV:
  
  ///create a new empty taylor series the children
    child1_ts=createEmptytSeries(n, t->x);
    child2_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the children
    taylor_series(child1_ts, f->child1);
    taylor_series(child2_ts, f->child2);
    //do the necessary chages from children to parent
    division_TS(t,child1_ts, child2_ts);
  
    break;

  case SQRT:
  
   //create a new empty taylor series for the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_model on the child
    taylor_series(child1_ts, f->child1);
    //compute sqrt for the taylor model obtained
    sqrt_TS(t,child1_ts);
    //clear old child
    cleartSeries(child1_ts);
  
  break;
  case EXP:
  //create a new empty taylor series for the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the child
    taylor_series(child1_ts, f->child1);
    //compute exp for the taylor series obtained
    exp_TS(t,child1_ts);
    //clear old child
    cleartSeries(child1_ts);
    
  break;
  
  case LOG:
    //create a new empty taylor series for the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the child
    taylor_series(child1_ts, f->child1);
    //compute exp for the taylor series obtained
    log_TS(t,child1_ts);
    //clear old child
    cleartSeries(child1_ts);
     
  break;
  
  case LOG_2:
   
  break;
  
  case LOG_10:
   
  break;
  
  case SIN:
  //create a new empty taylor series the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the child
    taylor_series(child1_ts, f->child1);
    //compute sin for the taylor series obtained
    sin_TS(t,child1_ts);
    //clear old child
    cleartSeries(child1_ts);
  break;
  
  case COS:
  //create a new empty taylor series the child
    child1_ts=createEmptytSeries(n, t->x);
    //call taylor_series on the child
    taylor_series(child1_ts, f->child1);
    //compute cos for the taylor series obtained
    cos_TS(t,child1_ts);
    //clear old child
    cleartSeries(child1_ts);
  break;
  
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

    break;
  case POW:
   if (((f->child2)->nodeType==CONSTANT) && ((f->child1)->nodeType==VARIABLE)){
        
        //create a new empty taylor series the child
        child1_ts=createEmptytSeries(n, t->x);
        //call taylor_series on the child
        taylor_series(child1_ts, f->child1);
        
        //compute ctpower for the taylor series obtained
        mpfi_init2(ct, getToolPrecision());
        mpfi_set_fr(ct, *((f->child2)->value));
        ctPower_TS(t,child1_ts,ct);
        //clear old child
        cleartSeries(child1_ts);
        mpfi_clear(ct);
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
         mpfi_pow(temp1,temp1,temp2);
         child1_ts=createConsttSeries(n, t->x,temp1 );
         settSeries(t, child1_ts);
         cleartSeries(child1_ts);
         mpfi_clear(temp1);
         mpfi_clear(temp2);
      }
      else if (simplifiedChild2->nodeType==CONSTANT) { //we have the f^p case
        //printf("We are in the  f^p case");        
          //create a new empty taylor series the child
        child1_ts=createEmptytSeries(n, t->x);
        //call taylor_series on the child
        taylor_series(child1_ts, f->child1);
        
        //compute ctpower for the taylor series obtained
        mpfi_init2(ct, getToolPrecision());
        mpfi_set_fr(ct, *(simplifiedChild2->value));
        ctPower_TS(t,child1_ts,ct);
        //clear old child
        cleartSeries(child1_ts);
        mpfi_clear(ct);  
      } 
       else if (simplifiedChild1->nodeType==CONSTANT) { //we have the p^f case
        //printf("We are in the  p^f case");     
        
      } 
      else {
      //printf("We are in the  f^g case");     
      
      }
    free_memory(simplifiedChild2);
    free_memory(simplifiedChild1);
  }
  
   break;
  
  case LIBRARYFUNCTION:
    break;

  default:
   fprintf(stderr,"Error: TM: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }

  return;
}

