/*
  For compiling this file:
    gcc -fPIC -Wall -c taylorModel.c
    gcc -fPIC -shared -o taylorModel taylorModel.o


  Within Sollya:
    > externalproc(TM, "./taylorModel", (function, range, integer) -> list of range);

  And then, for instance:
    > TM(exp(x)*cos(x), [2.5; 2.6], 10);

*/


#include "sollya.h"

extern int mpfi_pow(mpfi_t res, mpfi_t x, mpfi_t y);
extern void fprintInterval(FILE *fd, mpfi_t interval);
extern chain *uncertifiedFindZeros(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);
extern void freeMpfrPtr(void *ptr);
//extern node *makePolynomial(mpfr_t *coefficients, int degree);
//extern int isPolynomial(node *tree)
//extern void getCoefficients(int *degree, node ***coefficients, node *poly)
//extern void dirtyfindzeros()

/*this is the taylor model structure:
n- order
rem_bound - bound for the remainder
poly_array - array of coeffs for the polynomial (mpfi's)
poly_bound - bound for the polynomial (helpful for computations)
x- interval on which the tm is computed
x0 - expansion point
*/
typedef struct tmdl {
int n; 
mpfi_t rem_bound;
mpfi_t *poly_array;
mpfi_t poly_bound;
mpfi_t x;
mpfr_t x0;
} tModel;




/* This function performs the taylor model.
   See the commentaries below.
*/
void taylor_model(tModel *t, node *f);

/*This function creates an empty taylor model
Allocates memory for array, initializes mpfi-s
*/
tModel* createEmptytModel(int n,  mpfi_t x){ //mpfr_t x0,
  tModel* t;
  int i;
 // printf("\nin createEmptyTM\n ");
  t= (tModel *)safeMalloc(sizeof(tModel));
  mpfi_init2(t->rem_bound, getToolPrecision());
  mpfi_init2(t->poly_bound,getToolPrecision());
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  //mpfr_init2(t->x0,getToolPrecision());
  //mpfr_set(t->x0,x0,GMP_RNDN);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  for(i=0;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  return t;
}


tModel* createConsttModel(int n,  mpfi_t x, mpfi_t ct){ //mpfr_t x0,
  tModel* t;
  int i;
 // printf("\nin createEmptyTM\n ");
  t= (tModel *)safeMalloc(sizeof(tModel));
  mpfi_init2(t->rem_bound, getToolPrecision());
  mpfi_init2(t->poly_bound,getToolPrecision());
  mpfi_init2(t->x,getToolPrecision());
  mpfi_set(t->x,x);
  //mpfr_init2(t->x0,getToolPrecision());
  //mpfr_set(t->x0,x0,GMP_RNDN);
  t->n=n;
  t->poly_array= (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  for(i=0;i<=n;i++){
    mpfi_init2(t->poly_array[i], getToolPrecision());
    mpfi_set_ui(t->poly_array[i],0);
  }
  
  mpfi_set(t->poly_array[0],ct);
  mpfi_set(t->poly_bound,ct);
  mpfi_set(t->rem_bound,0); 
  return t;
}



/*This function dealocates a taylor model
*/
void cleartModel(tModel *t){
  int i;
  for(i=0;i<=t->n;i++) mpfi_clear(t->poly_array[i]);
  safeFree(t->poly_array);
  mpfi_clear(t->rem_bound);
  mpfi_clear(t->poly_bound);  
  mpfi_clear(t->x);
  safeFree(t);
}

/*This function pretty prints a taylor model
*/
void printtModel(tModel *t){
  int i;
  printf("\nTaylor model of order, %d:", t->n);
  for(i=0;i<=t->n;i++) {
    printInterval(t->poly_array[i]);
    printf(",");
  }  
  printf("r=");
  printInterval(t->rem_bound);
  printf(",b=");
  printInterval(t->poly_bound);  
  printf("\n");  
  }


/*This function sets a taylor model t 
with the values given by anoter tm tt
they implicitely have the same order and interval
(are from the same family)
*/
void settModel(tModel *t, tModel *tt){
  int i;
  for(i=0;i<=tt->n;i++) {
    mpfi_set(t->poly_array[i],tt->poly_array[i]);
  }  
  mpfi_set(t->rem_bound,tt->rem_bound);
  mpfi_set(t->poly_bound,tt->poly_bound);  
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
  safeFree(res);
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
  safeFree(rootsIntervals);
  
  for(i=0;i<=n;i++){
    mpfr_clear(polyCoeffs[i]);
  }
  safeFree(polyCoeffs);
  
  mpfr_clear(a);
  mpfr_clear(b);  
  mpfr_clear(inf);
  mpfr_clear(sup);
  mpfr_clear(pinf);
  mpfr_clear(psup);  
  free_memory(poly);
  free_memory(diff_poly);  
  
}


int TM(chain **res, void **args) {
  node *f;
  mpfi_t x;
  int i,n;
  mpfi_t* rem_bound;
  mpfi_t *res_array;
  mpfi_t *temp, *temp2;
  tModel* t;
  f = (node *)args[0];
  n = *( (int *)args[2] );

  rem_bound = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
  mpfi_init2(*rem_bound, getToolPrecision());

  res_array = (mpfi_t *)safeMalloc((n+1)*sizeof(mpfi_t));
  for(i=0;i<=n;i++) mpfi_init2(res_array[i], getToolPrecision());

  mpfi_init2(x, getToolPrecision());
  mpfi_set(x, *( (mpfi_t *)args[1] ));
  //printf("we will create a taylor model");
  t= createEmptytModel(n,x);
  //printf("we created the empty tm\n");
  taylor_model(t, f);

  *res = NULL;
  temp = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp, getToolPrecision());
    mpfi_set(*temp, t->poly_bound);
    *res = addElement(*res, temp);
    
    temp2 = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp2, getToolPrecision());
    mpfi_set(*temp2, t->rem_bound);
    *res = addElement(*res, temp2);
  
  for(i=n;i>=0;i--) {
    temp = (mpfi_t *)safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp, getToolPrecision());
    mpfi_set(*temp, t->poly_array[i]);
    *res = addElement(*res, temp);
  }
    
  
  safeFree(t->poly_array);
  safeFree(t);
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
    safeFree(cc);
  }
  else mpfi_set_ui(rr,0);
  mpfi_set(*r,rr);
  mpfi_clear(rr);
  return 0;
}

/*This function computes the tm for multiplication of two 
given tm's 
*/
void  multiplication_TM(tModel *t,tModel *c1, tModel *c2){
  //we will multiply two taylor models of order n; and obtain a new taylor model of order n;
  int n,i,j;
  mpfi_t *r;
  tModel *tt;
  //printf("in multiplication TM");
  n=t->n;
  //aux tm for doing the multiplications
  
  tt=createEmptytModel(n,t->x);
  
  r= (mpfi_t *)safeMalloc((n)*sizeof(mpfi_t));
  
  for(i=0;i<=n-1;i++){
    mpfi_init2(r[i], getToolPrecision());
    mpfi_set_ui(r[i],0);
  }
  mpfi_t temp1, temp2;
  mpfi_init2(temp1, getToolPrecision());
  mpfi_init2(temp2, getToolPrecision());
  
 
  //i1*p2+i2*p1+i1*i2
  mpfi_mul(temp1, c1->rem_bound, c2->rem_bound);
  mpfi_mul(temp2, c1->poly_bound, c2->rem_bound);
  mpfi_add(tt->rem_bound,temp1,temp2);
  mpfi_mul(temp1, c1->rem_bound, c2->poly_bound);
  mpfi_add(tt->rem_bound, tt->rem_bound, temp1);
  //new polynomial;
  for(i=0; i<=n;i++)
    for (j=0;j<=n;j++){
      mpfi_mul(temp1,c1->poly_array[i], c2->poly_array[j]);
      if ((i+j)<=n )
        mpfi_add(tt->poly_array[i+j],tt->poly_array[i+j],temp1);
      else
        mpfi_add(r[i+j-n-1],r[i+j-n-1],temp1);
    }
   //compute the bound for poly from x^(n+1)...x^(2*n)
   //----------------------------------------
   //polynomialBound(&temp1, n-1,r,t->x);
   //--------------------------------------
   
   polynomialBoundSharp(&temp1, n-1,r,t->x);
   
   //printInterval(temp1);
   //we have to multiply by x^(n+1);
   mpfi_set_ui(temp2,n+1);
   mpfi_pow(temp2,t->x,temp2);
   //printInterval(temp2);
   mpfi_mul(temp1,temp1,temp2);
   //we set the bound for the remainder;
   mpfi_add(tt->rem_bound,tt->rem_bound,temp1);
   
  //we compute the new polynomial bound for the new model
  //----------------------------------------
  //polynomialBound(&temp1, n,tt->poly_array,t->x);   
  //
  polynomialBoundSharp(&temp1, n,tt->poly_array,t->x);   
  mpfi_set(tt->poly_bound,temp1);
  
  mpfi_clear(temp1);
  mpfi_clear(temp2);
  for(i=0;i<=n-1;i++)
    mpfi_clear(r[i]);
  safeFree(r); 
  
  //set the result
  settModel(t,tt);
  //clear the aux tm;
  cleartModel(tt);
 }

//-----------------------------------------------------------





//-----------------------------------------------------------

/*This function computes the tm for addition of two 
given tm's 
*/
void addition_TM(tModel *t,tModel *child1_tm, tModel *child2_tm){
  int i;
  int n;
  tModel *tt;
  n=t->n;
  tt=createEmptytModel(n,t->x);
  for(i=0;i<=n;i++)  mpfi_add(tt->poly_array[i], child1_tm->poly_array[i],child2_tm->poly_array[i]);
  mpfi_add(tt->rem_bound,child1_tm->rem_bound,child2_tm->rem_bound);
 // mpfi_add(tt->poly_bound,child1_tm->poly_bound,child2_tm->poly_bound);
  polynomialBoundSharp(&tt->poly_bound, n,tt->poly_array,t->x);   
  settModel(t,tt);
  cleartModel(tt);
}

/*This function computes the tm for division
with a ct term of a given tm
*/
void ctDivision_TM(tModel*t, mpfi_t c){
  int i;
  int n;
  n=t->n;
  
  for(i=0;i<=n;i++)  mpfi_div(t->poly_array[i],t->poly_array[i],c);
  mpfi_div(t->rem_bound,t->rem_bound,c);
  mpfi_div(t->poly_bound,t->poly_bound,c);


}

/*This function computes the tm for multiplication
with a ct term of a given tm
*/
void ctMultiplication_TM(tModel*t, mpfi_t c){
  int i;
  int n;
  n=t->n;
  
  for(i=0;i<=n;i++)  mpfi_mul(t->poly_array[i],t->poly_array[i],c);
  mpfi_mul(t->rem_bound,t->rem_bound,c);
  mpfi_mul(t->poly_bound,t->poly_bound,c);


}

/*This function computes the tm for exp(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 385
*/
void exp_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,fact,temp,powx,int01;
  tModel *tt,*tc, *partialResult_tm, *partialResult2_tm;
 // printf("in exp_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute exp(cf)
  mpfi_exp(cf,cf);
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set_ui(tt->poly_bound,1);
  mpfi_set_ui(tt->poly_array[0],1);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute i!
    mpfi_mul_ui(fact, fact, i);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
    //div by i!
    settModel( partialResult2_tm,  partialResult_tm);
    ctDivision_TM(partialResult2_tm, fact);
    
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model before multiplying:");
  //printtModel(tt);
  //multiply everything by exp(cf)
  ctMultiplication_TM(tt,cf);
  
  //we have the polynomial of taylor model for exp(...)
    
  //we work on the bound;
  //exp(c) f^(n+1)/(n+1)! * exp([0,1]*f)
  mpfi_mul_ui(fact, fact, n+1);
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);
    
  mpfi_init2(powx,getToolPrecision());
  mpfi_set_ui(powx,n+1);
  mpfi_pow(powx,temp, powx);
  mpfi_div(powx,powx,fact); 
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
    
  mpfi_exp(temp,temp);
  mpfi_mul(temp,powx,temp);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(fact);
  mpfi_clear(int01);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}

/*This function computes the tm for log(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 386
*/
void log_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,logcf, powcf, inti,temp,powx,pown,int01, temp1, temp2;
  tModel *tt,*tc, *partialResult_tm, *partialResult2_tm;
  
  mpfr_t inftemp2,suptemp2;
  printf("in log_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute log(cf)
  mpfi_init2(logcf,getToolPrecision());
  mpfi_log(logcf,cf);
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(powcf, getToolPrecision());
  mpfi_set_ui(powcf, 1);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set(tt->poly_bound,logcf);
  mpfi_set(tt->poly_array[0],logcf);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute cf^i
    mpfi_mul(powcf,powcf, cf);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
    //div by cf^i
    settModel( partialResult2_tm,  partialResult_tm);
    ctDivision_TM(partialResult2_tm, powcf);
    //div by i*(-1)^(i+1)
    if ((i%2)==0) 
      mpfi_set_si(inti,(-1)*i);
    else 
      mpfi_set_ui(inti,i);
    ctDivision_TM(partialResult2_tm,inti);
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model obtained:");
  //printtModel(tt);
  
  //we have the polynomial of taylor model for log(...)
    
  //we work on the bound;
  //1/(k+1)  (-1)^(n+2) f^(n+1)/cf^(n+1) * 1/(1+[0,1]*f/cf)^(n+1)
  if (n%2==0)
    mpfi_set_ui(inti,n+1);
  else
    mpfi_set_si(inti,(-1)*(n+1));
  mpfi_mul(powcf,powcf,cf);
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
  
  mpfi_init2(temp1, getToolPrecision());
  mpfi_set(temp1, temp);
  
  mpfi_init2(temp2, getToolPrecision());
  mpfi_set(temp2, temp);
  
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp1, pown);
  mpfi_div(powx,powx,powcf); 
  mpfi_div(powx,powx,inti);
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp1,temp1,int01);
  mpfi_div(temp1,temp1,cf);
  mpfi_add_ui(temp1,temp1,1);  
  mpfi_pow(temp1,temp1,pown);
  mpfi_div(temp1,powx,temp1);
  
  
  
  
  
  
  printf("bound1=");
  printInterval(temp1);
  
  
  
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  /*
  mpfi_init2(powx,getToolPrecision());
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_div(temp2,cf,temp2);
  mpfi_add(temp2,temp2,int01);
  mpfi_ui_div(temp2,1,temp2);
  mpfi_pow(temp2,temp2,pown);
  
  
  */
  printf("initially z=");
  printInterval(temp2);
  mpfr_init2(inftemp2, getToolPrecision());
  mpfr_init2(suptemp2, getToolPrecision());
  
  mpfi_get_left(inftemp2,temp2);
  mpfi_get_right(suptemp2,temp2);
  
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_mul_fr(powx,int01,inftemp2);
  mpfi_add(powx,cf,powx);
  mpfi_fr_div(powx,inftemp2,powx);
  mpfi_pow(powx, powx, pown);
  mpfi_get_left(inftemp2,powx);
  
  mpfi_mul_fr(powx,int01,suptemp2);
  mpfi_add(powx,cf,powx);
  mpfi_fr_div(powx,suptemp2,powx);
  mpfi_pow(powx, powx, pown);
  mpfi_get_right(suptemp2,powx);
  
  mpfi_interv_fr(temp2,inftemp2,suptemp2);
  
  mpfi_div(temp2,temp2,inti);
  
  
  
  
   printf("bound2=");
  printInterval(temp2);
  
  mpfi_intersect(temp1,temp1,temp2);
  
  mpfi_add(tt->rem_bound,tt->rem_bound,temp1);
    
    
  mpfi_clear(temp);
  mpfi_clear(temp1);
  mpfi_clear(temp2);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(powcf);
  mpfi_clear(logcf);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(tc);
  cleartModel(tt);
}

/*This function computes the tm for sin(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 387
*/
void sin_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,sincf, coscf, fact,temp,powx,pown,int01,inti;
  tModel *tt,*tc, *partialResult_tm,*partialResult2_tm;
  //printf("in sin_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute sin(cf)
  mpfi_init2(sincf,getToolPrecision());
  mpfi_sin(sincf,cf);
  //compute cos(cf)
  mpfi_init2(coscf,getToolPrecision());
  mpfi_cos(coscf,cf);
  
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set(tt->poly_bound,sincf);
  mpfi_set(tt->poly_array[0],sincf);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute i!
    mpfi_mul_ui(fact,fact, i);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
    //mul by sin,cos,-sin,-cos
    settModel(partialResult2_tm,partialResult_tm);
    //div by i!
    ctDivision_TM(partialResult2_tm, fact);
    if ((i%4)==0) 
      mpfi_set(inti,sincf);
    else if ((i%4)==1) 
      mpfi_set(inti,coscf);
    else if ((i%4)==2){ 
      mpfi_set(inti,sincf);
      mpfi_mul_si(inti,inti,-1);
      }
    else{
      mpfi_set(inti,coscf);
      mpfi_mul_si(inti,inti,-1);
      }
    ctMultiplication_TM(partialResult2_tm,inti);
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for log(...)
    
  //we work on the bound;
  //1/(k+1)!  f^(n+1) * J -> cos, -sin,-cos,sin
  mpfi_mul_ui(fact,fact,n+1);
      
    
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,fact); 
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  
  if ((n%4)==0) {
      mpfi_cos(temp,temp);
      }
    else if ((n%4)==1){ 
      mpfi_sin(temp,temp);
      mpfi_mul_si(temp,temp,-1);
      }
    else if ((n%4)==2) {
      mpfi_cos(temp,temp);
      mpfi_mul_si(temp,temp,-1);
      }
    else{
      mpfi_sin(temp,temp);
      }
  mpfi_mul(temp,temp,powx);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(coscf);
  mpfi_clear(sincf);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}


/*This function computes the tm for cos(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 387
*/
void cos_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,sincf, coscf, fact,temp,powx,pown,int01,inti;
  tModel *tt,*tc, *partialResult_tm,*partialResult2_tm;
  printf("in cos_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute sin(cf)
  mpfi_init2(sincf,getToolPrecision());
  mpfi_sin(sincf,cf);
  //compute cos(cf)
  mpfi_init2(coscf,getToolPrecision());
  mpfi_cos(coscf,cf);
  
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set(tt->poly_bound,coscf);
  mpfi_set(tt->poly_array[0],coscf);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute i!
    mpfi_mul_ui(fact,fact, i);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
    //mul by cos,-sin,-cos,sin
    settModel(partialResult2_tm,partialResult_tm);
    //div by i!
    ctDivision_TM(partialResult2_tm, fact);
    if ((i%4)==0) 
      mpfi_set(inti,coscf);
    else if ((i%4)==1) {
      mpfi_set(inti,sincf);
      mpfi_mul_si(inti,inti,-1);
      }
    else if ((i%4)==2){ 
      mpfi_set(inti,coscf);
      mpfi_mul_si(inti,inti,-1);
      }
    else{
      mpfi_set(inti,sincf);
      }
    ctMultiplication_TM(partialResult2_tm,inti);
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for log(...)
    
  //we work on the bound;
  //1/(k+1)!  f^(n+1) * J -> cos, -sin,-cos,sin
  mpfi_mul_ui(fact,fact,n+1);
      
    
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,fact); 
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  
  if ((n%4)==0) {
      mpfi_sin(temp,temp);
      mpfi_mul_si(temp,temp,-1);
      }
    else if ((n%4)==1){ 
      mpfi_cos(temp,temp);
      mpfi_mul_si(temp,temp,-1);
      }
    else if ((n%4)==2) {
      mpfi_sin(temp,temp);
      }
    else{
      mpfi_cos(temp,temp);
      }
  mpfi_mul(temp,temp,powx);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(coscf);
  mpfi_clear(sincf);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}



void sinh_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,sinhcf, coshcf, fact,temp,powx,pown,int01,inti;
  tModel *tt,*tc, *partialResult_tm,*partialResult2_tm;
  //printf("in sinh_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute sinh(cf)
  mpfi_init2(sinhcf,getToolPrecision());
  mpfi_sinh(sinhcf,cf);
  //compute cos(cf)
  mpfi_init2(coshcf,getToolPrecision());
  mpfi_cosh(coshcf,cf);
  
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set(tt->poly_bound,sinhcf);
  mpfi_set(tt->poly_array[0],sinhcf);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute i!
    mpfi_mul_ui(fact,fact, i);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
    
    //mul by sinh,cosh
    settModel(partialResult2_tm,partialResult_tm);
    //div by i!
    ctDivision_TM(partialResult2_tm, fact);
    if ((i%2)==0) 
      mpfi_set(inti,sinhcf);
    else 
      mpfi_set(inti,coshcf);
    
    ctMultiplication_TM(partialResult2_tm,inti);
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for log(...)
    
  //we work on the bound;
  //1/(k+1)!  f^(n+1) * J -> cos, -sin,-cos,sin
  mpfi_mul_ui(fact,fact,n+1);
      
    
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,fact); 
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  
  if ((n%2)==0) 
      mpfi_cosh(temp,temp);
  else 
      mpfi_sinh(temp,temp);
      
  mpfi_mul(temp,temp,powx);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(coshcf);
  mpfi_clear(sinhcf);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}


/*This function computes the tm for cosh(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 388
*/
void cosh_TM(tModel *t, tModel *child1_tm){
  int i,n;
  
  mpfi_t cf,sinhcf, coshcf, fact,temp,powx,pown,int01,inti;
  tModel *tt,*tc, *partialResult_tm,*partialResult2_tm;
  //printf("in cosh_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,child1_tm);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  //compute sinh(cf)
  mpfi_init2(sinhcf,getToolPrecision());
  mpfi_sinh(sinhcf,cf);
  //compute cosh(cf)
  mpfi_init2(coshcf,getToolPrecision());
  mpfi_cosh(coshcf,cf);
  
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set(tt->poly_bound,coshcf);
  mpfi_set(tt->poly_array[0],coshcf);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute i!
    mpfi_mul_ui(fact,fact, i);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    //printtModel(partialResult_tm);
   
    //mul by cos,-sin,-cos,sin
    settModel(partialResult2_tm,partialResult_tm);
     //div by i!
    ctDivision_TM(partialResult2_tm, fact);
    if ((i%2)==0) 
      mpfi_set(inti,coshcf);
    else 
      mpfi_set(inti,sinhcf);
      
     
    ctMultiplication_TM(partialResult2_tm,inti);
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
    }
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for log(...)
    
  //we work on the bound;
  //1/(k+1)!  f^(n+1) * J -> cos, -sin,-cos,sin
  mpfi_mul_ui(fact,fact,n+1);
      
    
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,fact); 
    
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  
  if ((n%2)==0) 
      mpfi_sinh(temp,temp);
  else 
      mpfi_cosh(temp,temp);
  mpfi_mul(temp,temp,powx);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(coshcf);
  mpfi_clear(sinhcf);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}

/*This function computes the tm for 1/(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 386
*/
void inv_TM(tModel *t, tModel *c1){
  int i,n;
  
  mpfi_t cf, powcf, inti,temp,powx,pown,int01;
  tModel *tt,*tc, *partialResult_tm, *partialResult2_tm;
  //printf("in inv_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,c1);
  //printf("Before inverting");
  //printtModel(tc);  
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(powcf, getToolPrecision());
  mpfi_set_ui(powcf, 1);//start with 1/cf
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set_ui(tt->poly_bound,1);
  mpfi_set_ui(tt->poly_array[0],1);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute cf^i
    mpfi_mul(powcf,powcf, cf);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    
    //div by (-1)^i cf^i
    if ((i%2)==1) 
      mpfi_mul_si(inti,powcf,-1);
    else 
      mpfi_set(inti,powcf);
    settModel(partialResult2_tm,partialResult_tm);
    ctDivision_TM(partialResult2_tm, inti);
    //printtModel(partialResult2_tm);
    
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
  }
  //divide again by cf
  ctDivision_TM(tt, cf);
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for 1/(...)
    
  //we work on the bound;
  //(-1)^(n+1) f^(n+1)/cf^(n+2) * 1/(1+[0,1]*f/cf)^(n+2)
  mpfi_mul(powcf,powcf,cf);
  mpfi_mul(powcf,powcf,cf);
  
  if (n%2==0)
    mpfi_mul_si(powcf,powcf,-1);
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,powcf); 
      
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  mpfi_div(temp,temp,cf);
  mpfi_add_ui(temp,temp,1);
  mpfi_set_ui(pown,n+2);  
  mpfi_pow(temp,temp,pown);
  mpfi_div(temp,powx,temp);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(powcf);
  
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}


/*This function computes the tm for 1/(given_tm)
It uses the taylor series expansion given in :
Chaves Daumas : A Libary of Taylor Models for PVS automatic proof
checker 2006

Actually it is not sharper than the Makino-Berz version
and currently we are not sure if it is totally correct

Implemented just for testing
*/
void invSharp_TM(tModel *t, tModel *c1){
  int i,n;
  
  mpfi_t cf, powcf, inti,temp,pown; //powx,int01
  tModel *tt,*tc, *partialResult_tm, *partialResult2_tm;
  mpfr_t inf,sup;
  mpfi_t infInt, supInt,s1,s2,s1div;
  printf("in invSharp_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,c1);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(powcf, getToolPrecision());
  mpfi_set_ui(powcf, 1);//start with 1/cf
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  partialResult_tm=createEmptytModel(n,t->x);
  
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set_ui(tt->poly_bound,1);
  mpfi_set_ui(tt->poly_array[0],1);
  mpfi_set_ui(tt->rem_bound,0);
  printf("partial result");  
  printtModel(partialResult_tm);
  printf("child:");
  printtModel(tc);    
  
  //we compute s1=(-tc->poly_bound/cf)^(n+1)/(1+tc->poly_bound/cf)
  mpfi_init2(s1,getToolPrecision());
  mpfi_set(s1, tc->poly_bound);
  
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(s1div,getToolPrecision());
  
  mpfi_div(s1div,s1,cf);
  mpfi_mul_si(s1,s1,-1);
  
   
  mpfi_pow(s1,s1,pown);
  
  mpfi_add_ui(s1div,s1div,1);
  
  mpfi_div(s1,s1,s1div);
  
    
  for(i=1;i<=n;i++){
    //compute cf^i
    mpfi_mul(powcf,powcf, cf);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    printf("i= %d  ",i);
    
    //div by (-1)^i cf^i
    if ((i%2)==1) 
      mpfi_mul_si(inti,powcf,-1);
    else 
      mpfi_set(inti,powcf);
    settModel(partialResult2_tm,partialResult_tm);
    ctDivision_TM(partialResult2_tm, inti);
    printtModel(partialResult2_tm);
    
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
  }
  //divide again by cf
  ctDivision_TM(tt, cf);
  printf("Taylor model obtained:");
  printtModel(tt);
  //we have the polynomial of taylor model for 1/(...)
    
  //we work on the bound;
  //(-1)^(n+1) f^(n+1)/cf^(n+2) * 1/(1+[0,1]*f/cf)^(n+2)
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tt->poly_bound,tt->rem_bound);//bound on the tt
    
  mpfi_init2(s2,getToolPrecision());
  mpfi_div(s2,c1->x,c1->poly_bound);
  mpfr_init2(inf,getToolPrecision());
  mpfr_init2(sup,getToolPrecision());  
  
  mpfi_get_left(inf,s2);
  mpfi_get_right(sup,s2);
  
  mpfi_init2(infInt, getToolPrecision());
  mpfi_interv_fr(infInt, inf,inf);
 
  mpfi_ui_div(infInt,1,infInt);
  mpfi_add_ui(infInt,infInt,1);
  mpfi_ui_div(infInt,1,infInt);
  
  mpfi_get_left(inf, infInt);
  
  
  mpfi_init2(supInt, getToolPrecision());
  mpfi_interv_fr(supInt, sup,sup);
  
  mpfi_ui_div(supInt,1,supInt);
  mpfi_add_ui(supInt,supInt,1);
  mpfi_ui_div(supInt,1,supInt);
  mpfi_get_right(sup, supInt);
  
  mpfi_interv_fr(s2, inf, sup);
  mpfi_mul(temp,s2,temp);
  
  mpfi_mul(s2, s1,s2);
  mpfi_add(s2,s2,s1);
  mpfi_div(s2,s2,cf);
  
  mpfi_add(temp,temp,s2);
  printf("bound=");
  printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(pown);
  mpfi_clear(powcf);
  mpfi_clear(s1);
  mpfi_clear(s2);
  mpfr_clear(inf);
  mpfr_clear(sup);
  mpfi_clear( infInt);
  mpfi_clear(supInt);
  mpfi_clear(s1div);
 // mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}

/*This function computes the tm for division of two taylor models
using inv(given_tm)
*/
void division_TM(tModel *t, tModel *c1, tModel *c2){
 
  int n;
  tModel *tt, *inv_c2;
  n=t->n;
  tt=createEmptytModel(n,t->x);
  //compute inverse for the taylor model for child2 obtained
  //create a new empty taylor model the invchild2
  inv_c2=createEmptytModel(n, t->x);
  //call taylor_model for the inverse
  inv_TM(inv_c2,c2);
  //multiply c1 and inv_c2
  multiplication_TM(tt,c1,inv_c2);
  settModel(t,tt);
  cleartModel(tt);
  cleartModel(inv_c2);
}

/*This function computes the tm for sqrt(given_tm)
It uses the taylor series expansion given in :
Makino-Berz : Taylor Models and Other Validated Functional Inclusion Methods
2003,International jurnal of pure and applied mathematics, 379-456
pag. 386
*/
void sqrt_TM(tModel *t, tModel *c1){
  int i,n;
  
  mpfi_t cf, sqrtcf, powcf,fact, inti,temp,powx,pown,int01;
  tModel *tt,*tc, *partialResult_tm, *partialResult2_tm;
  //printf("in sqrt_TM");
  n=t->n;
  
  //additional tms for computations
  tt=createEmptytModel(n,t->x);
  settModel(tt,t);
  tc=createEmptytModel(n,t->x);
  settModel(tc,c1);
    
  //take the constant coefficient
  mpfi_init2(cf,getToolPrecision());
  mpfi_set(cf,tc->poly_array[0]);
  mpfi_sub(tc->poly_bound,tc->poly_bound,cf);
  mpfi_set_ui(tc->poly_array[0],0);
  
  //we have the taylor model tc; we use tm_addition and tm_multiplication to obtain the new tm;
  mpfi_init2(powcf, getToolPrecision());
  mpfi_set_ui(powcf, 1);//start with 1
  
  mpfi_init2(sqrtcf, getToolPrecision());
  mpfi_sqrt(sqrtcf, cf);
  
  mpfi_init2(inti, getToolPrecision());
  mpfi_set_ui(inti, 1);
  
  
  mpfi_init2(fact, getToolPrecision());
  mpfi_set_ui(fact, 1);
  
  
  partialResult_tm=createEmptytModel(n,t->x);
  
  partialResult2_tm=createEmptytModel(n,t->x);
  //make this tm a constant
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
    
  mpfi_set_ui(tt->poly_bound,1);
  mpfi_set_ui(tt->poly_array[0],1);
  mpfi_set_ui(tt->rem_bound,0);
  //printf("partial result");  
  //printtModel(partialResult_tm);
  //printf("child:");
  //printtModel(tc);    
  for(i=1;i<=n;i++){
    //compute cf^i
    mpfi_mul(powcf,powcf, cf);
    //compute (child1_tm)^i
    multiplication_TM(partialResult_tm, partialResult_tm, tc);
    //printf("i= %d  ",i);
    
    //div by (-1)^(i+1) cf^i 
    //mul by (2i-3)!!
    //div by (2i)!! 
    if ((i%2)==0) 
      mpfi_mul_si(inti,powcf,-1);
    else 
      mpfi_set(inti,powcf);
  
    mpfi_mul_ui(fact,fact,2*i);
    if (i>1) mpfi_div_ui(fact,fact,2*i-3);

    mpfi_mul(inti,inti,fact);


    settModel(partialResult2_tm,partialResult_tm);
    ctDivision_TM(partialResult2_tm, inti);
    //printtModel(partialResult2_tm);
    
    //add with previous result
    addition_TM(tt,tt,partialResult2_tm);
  }
  //multiply  by sqrtcf
  ctMultiplication_TM(tt, sqrtcf);
  //printf("Taylor model obtained:");
  //printtModel(tt);
  //we have the polynomial of taylor model for 1/(...)
    
  //we work on the bound;
  //(-1)^(n) sqrtcf fact f^(n+1)/cf^(n+1) * 1/(1+[0,1]*f/cf)^(n+1/2)
  mpfi_mul(powcf,powcf,cf);
  if (n%2==1)
    mpfi_mul_si(powcf,powcf,-1);
    
  mpfi_mul_ui(fact,fact,2*n+2);
  mpfi_div_ui(fact,fact,2*n-1);
  mpfi_div(fact,fact,sqrtcf);
  
  mpfi_init2(temp, getToolPrecision());
  mpfi_add(temp, tc->poly_bound,tc->rem_bound);//bound on the tc
    
  mpfi_init2(pown,getToolPrecision());
  mpfi_set_ui(pown,n+1);
  
  mpfi_init2(powx,getToolPrecision());
  mpfi_pow(powx,temp, pown);
  mpfi_div(powx,powx,powcf); 
      
  mpfi_init2(int01,getToolPrecision());
  mpfi_interv_ui(int01,0,1);
  mpfi_mul(temp,temp,int01);
  mpfi_div(temp,temp,cf);
  mpfi_add_ui(temp,temp,1);
  mpfi_set_ui(pown,2*n+1);
  mpfi_div_ui(pown,pown, 2);  
  mpfi_pow(temp,temp,pown);
  mpfi_div(temp,powx,temp);
  
  mpfi_div(temp,temp,fact);
  //printf("bound=");
  //printInterval(temp);
  mpfi_add(tt->rem_bound,tt->rem_bound,temp);
    
    
  mpfi_clear(temp);
  mpfi_clear(powx);
  mpfi_clear(pown);
  mpfi_clear(powcf);
  mpfi_clear(sqrtcf);
  mpfi_clear(fact);
  mpfi_clear(int01);
  mpfi_clear(inti);
  settModel(t,tt);
  //clear old taylor models
  cleartModel(partialResult_tm);
  cleartModel(partialResult2_tm);
  cleartModel(tc);
  cleartModel(tt);
}
/*This function computes the tm for the integer power function
of two taylor models
K must be an integer
*/

void  natPower_TM(tModel *t,tModel *tc, int k){
  //we will raise at power k a taylor model of order n; and obtain a new taylor model of order n;
  int n,i;
  
  tModel *partialResult_tm, *powChild;
  printf("in natPower TM");
  n=t->n;
  //aux tm for doing the multiplications
  
 
  partialResult_tm=createEmptytModel(n,t->x);
  
  mpfi_set_ui(partialResult_tm->poly_bound,1);
  mpfi_set_ui(partialResult_tm->rem_bound,0);
  mpfi_set_ui(partialResult_tm->poly_array[0],1);
  powChild=createEmptytModel(n,t->x);
  if (k<0){
    inv_TM(powChild, tc);
    k=-k;
  }
  else
  settModel(powChild, tc);
  printf("\nbefore raising at power");
  
  printtModel(powChild); 
  for(i=1;i<=k;i++){
    
    //compute (powChild)^i
    multiplication_TM(partialResult_tm, partialResult_tm, powChild);
    
    printtModel(partialResult_tm);
   // settModel(partialResult_tm, partialResult_tm2);
   }
  //set the result
  settModel(t,partialResult_tm);
  //clear the aux tm;
  cleartModel(partialResult_tm);
  cleartModel(powChild);
 }






/*This function computes the tm for the power function
of two taylor models
It uses the definition f^g=exp(g*log(f))
Currently we didn't find any other existing method for this operation
*/
void pow_TM(tModel *t, tModel *c1, tModel *c2){
 
  int n;
  tModel *tt, *log_c1, *prod;
  n=t->n;
  //printf("in power_TM\n");
  tt=createEmptytModel(n,t->x);
  //compute log for the taylor model for child1 obtained
  //create a new empty taylor model the logchild1
  log_c1=createEmptytModel(n, t->x);
  log_TM(log_c1, c1);
  //printf("\nbase model:");
  //printtModel(c1);
  //printf("\nlog model of base: ");
  //printtModel(log_c1);
  
  //use multiplication_TM for ch2*log ch1
  prod=createEmptytModel(n,t->x);
  multiplication_TM(prod,c2,log_c1);
  //printf("\nmultiplic model of exponent*log base: ");
  //printtModel(prod);
  
  //exponential of the result
  exp_TM(tt,prod);
 
  //printf("\npower model: ");
  //printtModel(tt);
  
  settModel(t,tt);
  cleartModel(tt);
  cleartModel(log_c1);
  cleartModel(prod);
}

void taylor_model(tModel *t, node *f) {
  int i;
 // mpfi_t *res1, *res2, *res3, *res4, *res5, *res6;
  //mpfi_t *rem_bound1, *rem_bound2;
 // mpfr_t minusOne;
  
  node *simplifiedChild1, *simplifiedChild2;
  mpfi_t temp1,temp2;
  node **coefficients;
  mpfi_t *rpoly, *boundRpoly;
  tModel *child1_tm, *child2_tm;
  int d,n;
  mpfi_t powx,powy;
  mpfi_t ct;
  n=t->n;
  //printf("We entered taylor model order: %d\n",n);
  if (isPolynomial(f) ){
  //printf("We found a polynomial!!!\n");
    getCoefficients(&d, &coefficients, f);
    //for(i=0;i<=d;i++) if (coefficients[i]!=NULL) printTree(coefficients[i]);
    if (d<=n){
     // printf("The degree of polynomial smaller : %d than the taylor model degree\n",d);
      for(i=0;i<=d;i++) {
        //printf("%d\n",i);
        //printInterval(t->poly_array[i]);
        mpfi_set_node(&(t->poly_array[i]),coefficients[i]);
      }
      // printf("we set the coefficients\n");
      //compute the bound for the polynomial, put the bound for tm= 0;
      boundRpoly=(mpfi_t *)safeMalloc(sizeof(mpfi_t));
      mpfi_init2(*boundRpoly,getToolPrecision());
      polynomialBoundSharp(boundRpoly,d,t->poly_array,t->x);
      mpfi_set(t->poly_bound,*boundRpoly);
      mpfi_clear(*boundRpoly); 
      mpfi_set_ui(t->rem_bound,0);
    }
    else {
      //printf("The degree of polynomial bigger : %d then the taylor model degree\n",d);
      for(i=0;i<=n;i++) mpfi_set_node(&(t->poly_array[i]),coefficients[i]);
      //we keep the bound on the n degree polynomial
        boundRpoly=(mpfi_t *)safeMalloc(sizeof(mpfi_t));
        mpfi_init2(*boundRpoly,getToolPrecision());
        polynomialBoundSharp(boundRpoly,n,t->poly_array,t->x);
        //printInterval(*boundRpoly);
        mpfi_set(t->poly_bound,*boundRpoly);
        
      //for n+1 pana la d, creaza polynomul, evalueaza-l pe interval si pe urma returneaza in rem_bound;
      rpoly=(mpfi_t *)safeMalloc((d-1)*sizeof(mpfi_t));
     
      for (i=n+1;i<=d;i++){
        //the polynomial has the form x^(n+1)*(coeff[n+1] + coeff[n+2]*x+...+ coeff[d]*x^(d-n-1) )
        //we create the polynomial of degree d-n-1; and evaluate it on the interval
     
        mpfi_init2(rpoly[i-n-1], getToolPrecision());
        mpfi_set_node( &rpoly[i-n-1], coefficients[i]);
      }
        polynomialBoundSharp(boundRpoly,d-n-1,rpoly,t->x);
        //printInterval(*boundRpoly);
        //we have to multiply by x^(n+1);
        mpfi_init2(powx,getToolPrecision());
        mpfi_init2(powy,getToolPrecision());
        mpfi_set_ui(powy,n+1);
        mpfi_pow(powx,t->x,powy);
        //printInterval(powx);
        mpfi_mul(*boundRpoly,*boundRpoly,powx);
        //we set the bound for the remainder;
        mpfi_set(t->rem_bound,*boundRpoly);
               
        mpfi_clear(*boundRpoly); 
        mpfi_clear(powx);      
        mpfi_clear(powy);  
      
    }
    
  }
  else {
  
  switch (f->nodeType) {
/*
  case VARIABLE:
  case PI_CONST:
  case CONSTANT:
  //cases not likely to appear because they are treated in polynomial case
*/  
  case NEG:
    //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //do the necessary chages from child to parent
    for(i=0;i<=n;i++)  mpfi_neg(t->poly_array[i], child1_tm->poly_array[i]);
    mpfi_neg(t->rem_bound,child1_tm->rem_bound);
    mpfi_neg(t->poly_bound,child1_tm->poly_bound);
    
    //clear old taylor model
    cleartModel(child1_tm);
    break;

  case ADD:
  
  //create a new empty taylor model the children
    child1_tm=createEmptytModel(n, t->x);
    child2_tm=createEmptytModel(n, t->x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1);
    taylor_model(child2_tm, f->child2);
    //do the necessary chages from children to parent
    /*for(i=0;i<=n;i++)  mpfi_add(t->poly_array[i], child1_tm->poly_array[i],child2_tm->poly_array[i]);
    mpfi_add(t->rem_bound,child1_tm->rem_bound,child2_tm->rem_bound);
    mpfi_add(t->poly_bound,child1_tm->poly_bound,child2_tm->poly_bound);
    */
    addition_TM(t,child1_tm, child2_tm);
    //clear old taylor model
    cleartModel(child1_tm);
     cleartModel(child2_tm);
    break;

  case SUB:
    printf("in SUB");
    //create a new empty taylor model the children
    child1_tm=createEmptytModel(n, t->x);
    child2_tm=createEmptytModel(n, t->x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1);
    taylor_model(child2_tm, f->child2);
    //do the necessary chages from children to parent
    for(i=0;i<=n;i++)  mpfi_sub(t->poly_array[i], child1_tm->poly_array[i],child2_tm->poly_array[i]);
    mpfi_sub(t->rem_bound,child1_tm->rem_bound,child2_tm->rem_bound);
    mpfi_sub(t->poly_bound,child1_tm->poly_bound,child2_tm->poly_bound);
    
    //clear old taylor model
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    break;

  case MUL:
   //create a new empty taylor model the children
    child1_tm=createEmptytModel(n, t->x);
    child2_tm=createEmptytModel(n, t->x);
    //call taylor_model on the children
    taylor_model(child1_tm, f->child1);
    taylor_model(child2_tm, f->child2);
    //do the necessary chages from children to parent
    multiplication_TM(t,child1_tm, child2_tm);
    
    //clear old taylor model
    cleartModel(child1_tm);
    cleartModel(child2_tm);
    break;

  case DIV:
  //multiplicative inverse * child1
  printf("division");
  //create a new empty taylor model the child1
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
  
  //create a new empty taylor model the child2
    child2_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child2_tm, f->child2);
    
  //call the division_TM
  division_TM(t, child1_tm, child2_tm);
  //clear old child
  cleartModel(child1_tm);
  
    break;

  case SQRT:
  
   //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute exp for the taylor model obtained
    sqrt_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
  
  break;
  case EXP:
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute exp for the taylor model obtained
    exp_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
    
  break;
  
  case LOG:
  printf("loogggg");
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute log for the taylor model obtained
    log_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
  break;
  
  case LOG_2:
   
  break;
  
  case LOG_10:
   
  break;
  
  case SIN:
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute log for the taylor model obtained
    sin_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
  break;
  
  case COS:
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute log for the taylor model obtained
    cos_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
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
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute sinh for the taylor model obtained
    sinh_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
  break;
  case COSH:
  //create a new empty taylor model the child
    child1_tm=createEmptytModel(n, t->x);
    //call taylor_model on the child
    taylor_model(child1_tm, f->child1);
    //compute cosh for the taylor model obtained
    cosh_TM(t,child1_tm);
    //clear old child
    cleartModel(child1_tm);
  break;
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
  //power f^g = exp(g * log f)
  printf(" power \n ");
  
  //we will try to create more cases just in case it will be better
 
 //var^constant -> polynomial, not likely to appear
  
 /*if (((f->child2)->nodeType==CONSTANT) && ((f->child1)->nodeType==VARIABLE)){
        
        //create a new empty taylor model for the child
        child1_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child1_tm, f->child1);
        
        //compute ctpower for the taylor model obtained
        mpfi_init2(ct, getToolPrecision());
        if (mpfr_integer_p(*((f->child2)->value))!=0) {  //it is an integer
         //use natPower_TM();
         natPower_TM(t,child1_tm,mpfr_get_si(*((f->child2)->value),GMP_RNDN));        
        }
        else{
        mpfi_set_fr(ct, *((f->child2)->value));
       // ctPower_TM(t,child1_tm,ct);
        //clear old child
        cleartModel(child1_tm);
        mpfi_clear(ct);
        }
    }
    else{*/
      simplifiedChild2=simplifyTreeErrorfree(f->child2);
      simplifiedChild1=simplifyTreeErrorfree(f->child1);
      
      if ((simplifiedChild2->nodeType==CONSTANT) &&(simplifiedChild1->nodeType==CONSTANT)) { //we have the ct1^ct2 case
         // printf("We are in the  ct1^ct2 case");       
         mpfi_init2(temp1, getToolPrecision());
         mpfi_set_fr(temp1, *(simplifiedChild1->value));
         mpfi_init2(temp2, getToolPrecision());
         mpfi_set_fr(temp2, *(simplifiedChild2->value));
         mpfi_pow(temp1,temp1,temp2);
         child1_tm=createConsttModel(n, t->x,temp1 );
         settModel(t, child1_tm);
         cleartModel(child1_tm);
         mpfi_clear(temp1);
         mpfi_clear(temp2);
      }
      else if (simplifiedChild2->nodeType==CONSTANT) { //we have the f^p case
        //printf("We are in the  f^p case");        
          //create a new empty taylor model for the child
        child1_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child1_tm, f->child1);
        //compute ctpower for the taylor model obtained
        mpfi_init2(ct, getToolPrecision());
        if (mpfr_integer_p(*((f->child2)->value))!=0) {  //it is an integer
         //use natPower_TM();
         natPower_TM(t,child1_tm,mpfr_get_si(*((f->child2)->value),GMP_RNDN));        
        }
        else{
          //compute ctpower for the taylor series obtained
          mpfi_init2(ct, getToolPrecision());
          mpfi_set_fr(ct, *(simplifiedChild2->value));
          // ctPower_TM(t,child1_tm,ct);
          //clear old child
          cleartModel(child1_tm);
          mpfi_clear(ct);  
        }
      }   
       else if (simplifiedChild1->nodeType==CONSTANT) { //we have the p^f case
        //printf("We are in the  p^f case");   
        //create a new empty taylor model the child1
        child1_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child1_tm, f->child1);
  
        //create a new empty taylor model the child2
        child2_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child2_tm, f->child2);
    
        pow_TM(t, child1_tm, child2_tm);
  
  
        //clear old child
        cleartModel(child1_tm);
        cleartModel(child2_tm);  
        
      } 
      else {
        //printf("We are in the  f^g case");  
        //create a new empty taylor model the child1
        child1_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child1_tm, f->child1);
  
        //create a new empty taylor model the child2
        child2_tm=createEmptytModel(n, t->x);
        //call taylor_model on the child
        taylor_model(child2_tm, f->child2);
    
        pow_TM(t, child1_tm, child2_tm);
  
  
        //clear old child
        cleartModel(child1_tm);
        cleartModel(child2_tm);   
      
    }
    free_memory(simplifiedChild2);
    free_memory(simplifiedChild1);
 
  
 
  
   
   break;
  case VARIABLE:
  case PI_CONST:
  case CONSTANT:
  case LIBRARYFUNCTION:
    break;

  default:
   fprintf(stderr,"Error: TM: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }
}
  return;
}

