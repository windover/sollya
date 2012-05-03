/*For compiling this file:
    gcc -fPIC -Wall -c chebModels.c
    gcc -fPIC -shared -o chebModels chebModels.o
    
    From sollya:
    externalproc(CM, "./chebModels", (function, range, integer,integer, integer) ->list of function);
    externalproc(CertifiedIntegral, "./chebModels", (function, range, integer,integer, integer) ->list of function);
    externalproc(TB, "./chebModels", (function, range, constant) ->list of function);
*/


#include "chebModels.h"
#include "chebModelsAux.c"
/***************************************************************/
/***************************************************************/
/**********Functions related to Chebyshev Models****************/
/***************************************************************/
/***************************************************************/

  
/* This function creates an empty cheb model */
chebModel* createEmptycModel(int n,sollya_mpfi_t x){
  chebModel* t;
  int i;
 
  t= (chebModel *)safeMalloc(sizeof(chebModel));
  sollya_mpfi_init2(t->rem_bound, getToolPrecision());
  sollya_mpfi_init2(t->poly_bound,getToolPrecision());
    
  sollya_mpfi_init2(t->x,getToolPrecision());
  sollya_mpfi_set(t->x,x);
  
  t->n=n;
  t->poly_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->poly_array[i], getToolPrecision());
  }
  
  t->cheb_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->cheb_array[i], getToolPrecision());
  }
  t->cheb_matrix= (sollya_mpfi_t **)safeMalloc(sizeof(sollya_mpfi_t *));
  return t;
}

/*This function creates an empty chebyshev model 
and  computes the chebyshev points of order n over x
and the chebMatrix in function of the two flags points, matrix(1= compute, 0=do not compute)
*/
chebModel* createEmptycModelCompute(int n,sollya_mpfi_t x, int flag_points, int flag_matrix){
  chebModel* t;
  int i;
  //printf("In create cheb model compute");
  t= (chebModel *)safeMalloc(sizeof(chebModel));
  sollya_mpfi_init2(t->rem_bound, getToolPrecision());
  sollya_mpfi_init2(t->poly_bound,getToolPrecision());
  
  
  sollya_mpfi_init2(t->x,getToolPrecision());
  sollya_mpfi_set(t->x,x);
  
  t->n=n;
  t->poly_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->poly_array[i], getToolPrecision());
  }
  
  t->cheb_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->cheb_array[i], getToolPrecision());
  }
  t->cheb_matrix= (sollya_mpfi_t **)safeMalloc(sizeof(sollya_mpfi_t *));

  if (flag_points!=0) getChebyshevPoints(t->cheb_array,n,x);

  if (flag_matrix!=0) getChebMatrix(t->cheb_matrix,n);
  //printf("Out of create cheb model compute");
  return t;
}

/*This function creates an empty chebyshev model
and copies the values from chebpoints into the new cmodel
(this function assumes that we have already computed the chebpoints and the chebMatrix (if the respective pointers are not NULL)
*/
chebModel* createEmptycModelPrecomp(int n,sollya_mpfi_t x, sollya_mpfi_t *chebPoints, sollya_mpfi_t **chebM){
  chebModel* t;
  int i;
 
  t= (chebModel *)safeMalloc(sizeof(chebModel));
  sollya_mpfi_init2(t->rem_bound, getToolPrecision());
  sollya_mpfi_init2(t->poly_bound,getToolPrecision());
   
  sollya_mpfi_init2(t->x,getToolPrecision());
  sollya_mpfi_set(t->x,x);
  
  t->n=n;
  t->poly_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->poly_array[i], getToolPrecision());
  }
  
  t->cheb_array= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
  for(i=0;i<n;i++){
    sollya_mpfi_init2(t->cheb_array[i], getToolPrecision());
  }
   t->cheb_matrix= (sollya_mpfi_t **)safeMalloc(sizeof(sollya_mpfi_t *)); 

if (chebPoints!=NULL)
  for(i=0;i<n;i++)  sollya_mpfi_set(t->cheb_array[i], chebPoints[i]);
  
if (chebM!=NULL)
  t->cheb_matrix=chebM;

return t;
}

/*This function dealocates a cheb model
*/
void clearcModel(chebModel *t){
  int i;
  for(i=0;i<t->n;i++) sollya_mpfi_clear(t->poly_array[i]);
  free(t->poly_array);
  
  for(i=0;i<t->n;i++) sollya_mpfi_clear(t->cheb_array[i]);
  free(t->cheb_array);
  
  sollya_mpfi_clear(t->rem_bound);
  sollya_mpfi_clear(t->poly_bound);  
   
  sollya_mpfi_clear(t->x);
  //free(t->cheb_matrix);
  free(t);
}

/*This function pretty prints a cheb model
*/
void printcModel(chebModel *t){
  int i;
  printf("\nChebModel of order, %d in Chebyshev base", t->n);
  printf("over ");
  printInterval(t->x);
  printf("\nCoeffs:");
  for(i=0;i<t->n;i++) {
    printInterval(t->poly_array[i]);
    printf(",");
  }  
  printf("r=");
  printInterval(t->rem_bound);
  printf(",b=");
  printInterval(t->poly_bound);  
  printf("\n");  
  }

/* The convention for all the following functions is:
the cmodel given as parameter has to be created previously 
*/


/*This function sets the chebModel t 
with constant ct;
*/

void constcModel(chebModel*t, sollya_mpfi_t ct){ 
  int i,n;
  n=t->n;
  
  for(i=1;i<n;i++){
     sollya_mpfi_set_ui(t->poly_array[i],0);
  }
  
  sollya_mpfi_set(t->poly_array[0],ct);
  sollya_mpfi_set(t->poly_bound,ct);
  sollya_mpfi_set_ui(t->rem_bound,0); 
}


/* Check that models are compatible one with another: i.e. they can be added, mulitplied, copied, etc. */
int cModelsAreCompatible(chebModel *t1, chebModel *t2) {
    return ((t1 != NULL) && (t2 != NULL) && 
            (sollya_mpfi_equal_p(t1->x, t2->x) || (sollya_mpfi_nan_p(t1->x) && sollya_mpfi_nan_p(t2->x))) &&
            (t1->n == t2->n));
}

/*This function sets a cheby model t with the values given by anoter cm tt
they should have the same basis and interval, if an incompatibility is detected,
no modification is made.
*/
void copycModel(chebModel *t, chebModel *tt){
  int i;
  
  if (!cModelsAreCompatible(t, tt)) {
    printf( "Error in chebModels: trying to copy incompatible models.\n");
    printf( "No modification is made.\n");
    return;
  }
  
  for(i=0;i<tt->n;i++) {
    sollya_mpfi_set(t->poly_array[i],tt->poly_array[i]);
  }  
  
  sollya_mpfi_set(t->rem_bound,tt->rem_bound);
  sollya_mpfi_set(t->poly_bound,tt->poly_bound);
  
  
  for(i=0;i<tt->n;i++) {
    sollya_mpfi_set(t->cheb_array[i],tt->cheb_array[i]);
  }    

  t->cheb_matrix=tt->cheb_matrix;
}



/***************************************************/
/******************Operations on ChebModels*********/
/***************************************************/
/***************************************************/

/*This function computes the cm for addition of two  given cm's 
The addition of two cheb/taylor models is the same
*/
void addition_CM(chebModel *t,chebModel *child1_tm, chebModel *child2_tm){
  int i;
  int n;
  chebModel *tt;
  if ( (!cModelsAreCompatible(child1_tm, child2_tm)) || (!cModelsAreCompatible(t, child1_tm)) ) {
    printf( "Error in chebModels: trying to add incompatible models.\n");
    printf( "No modification is made.\n");
    return;
  }
  n=t->n;
  tt=createEmptycModelPrecomp(n,t->x, child1_tm->cheb_array,child1_tm->cheb_matrix);
  for(i=0;i<n;i++)  
  sollya_mpfi_add(tt->poly_array[i], child1_tm->poly_array[i],child2_tm->poly_array[i]);
  
 
  sollya_mpfi_add(tt->rem_bound, child1_tm->rem_bound, child2_tm->rem_bound);
  //chebPolynomialBoundDefault(&(tt->poly_bound), n, tt->poly_array);
  copycModel(t,tt);
  clearcModel(tt);
}
/* This function computes the cm for multiplication by a constant */
void ctMultiplication_CM(chebModel*d, chebModel*s, sollya_mpfi_t c){
  int i;
  int n;
  chebModel *tt;

  n=s->n;
  tt=createEmptycModelPrecomp(n,s->x, s->cheb_array,s->cheb_matrix);
  
  for(i=0; i<n; i++)  sollya_mpfi_mul(tt->poly_array[i], s->poly_array[i], c);
  sollya_mpfi_mul(tt->rem_bound, s->rem_bound, c);
  sollya_mpfi_mul(tt->poly_bound, s->poly_bound, c);

  copycModel(d,tt);
  clearcModel(tt);
}

/*This function computes the cm for multiplication of two 
given cm's;

-- the parameter tightBounds>1 we use tightbounding, otherwise it means
that we are interested in speed, and we will use a simple algo for bounding

-- the parameter forComposition=1 means that we are using the multiplication inside a composition,
so we suppose that the bounds for the models are already computed inside the models.

*/


void  multiplication_CM(chebModel *t,chebModel *c1, chebModel *c2, int tightBounds, int forComposition){
  //we will multiply two cheby models of order n; and obtain a new cheby model of order n;
  int n,i,j;
  mp_prec_t prec;
  prec = getToolPrecision();
  chebModel *tt;
  sollya_mpfi_t temp1, temp2;
  sollya_mpfi_t *r;
  if ( (!cModelsAreCompatible(c2, c1)) || (!cModelsAreCompatible(t, c1)) ) {
    printf( "Error in chebModels: trying to add incompatible models.\n");
    printf( "No modification is made.\n");
    return;
  }
  n=t->n;
  
  //printf("Entering multiplication CM");
  //printf("\n\nc1=");
  //printcModel(c1);
  //printf("\n\nc2=");
  //printcModel(c2);
  //printf("**************************************\n");
  
  
  /*aux cm for doing the multiplications*/
  tt=createEmptycModelPrecomp(n, t->x, t->cheb_array, t->cheb_matrix);
  for(i=0;i<n;i++){
   sollya_mpfi_set_ui(tt->poly_array[i],0);
  }
  
  sollya_mpfi_init2(temp1, getToolPrecision());
  sollya_mpfi_init2(temp2, getToolPrecision());
  
  
  
  /*absolute error only*/
  /*We are multiplying chebmodels, considering the absolute error
    We are given:  (C1, r1)
                   (C2, r2)*/
    
   /*compute in temp1 r1*r2*/ 
   sollya_mpfi_mul(temp1, c1->rem_bound, c2->rem_bound);
   //printf("r1:=");
   //printInterval(temp1);
   //printf("\n");
   
   if (forComposition==0){
   
   /*if we need tight bounds (level is greater than 1), we will try to refine them,
   else, we will compute the basic ones*/
   if (tightBounds>1) {
   //printf("tightBounds in multiplication");
    chebPolynomialBoundRefined(c1->poly_bound, n, c1->poly_array);
    chebPolynomialBoundRefined(c2->poly_bound, n, c2->poly_array);
   }
   else{
    chebPolynomialBoundDefault(c1->poly_bound, n, c1->poly_array); 
    chebPolynomialBoundDefault(c2->poly_bound, n, c2->poly_array); 
   }
   }//if we wanted to make a composition, we suppose the the bound are already computed
   /*compute in temp2 delta1*B(C2)*/
   
   sollya_mpfi_mul(temp2, c1->rem_bound, c2->poly_bound);
   //printf("r2:=");
   //printInterval(temp2);
   //printf("\n");
   
   sollya_mpfi_add(tt->rem_bound, temp2, temp1);
   //printf("r3:=");
   //printInterval(tt->rem_bound);
   //printf("\n");
  
  /*compute in temp2 delta2*B(C1)*/
   sollya_mpfi_mul(temp2, c2->rem_bound, c1->poly_bound);
   sollya_mpfi_add(tt->rem_bound, tt->rem_bound,temp2);
   //printf("r3:=");
   //printInterval(tt->rem_bound);
   //printf("\n");
  
   /*compute the product of the two polynomials*/
   /*the product has degree 2n-2=> we have to store 2n-1 coeffs*/
   /*in r we store only the upper part of the polynomial*/
   /*r = [0, 0 ...., 0, r0, ..., r(n-2)]                          */
  /* it represents the polynomial T1*T2|[n....2n-2]*/
   r = (sollya_mpfi_t *)safeMalloc((2*n-1)*sizeof(sollya_mpfi_t));
  
   for(i=0; i < 2*n-1; i++){
     sollya_mpfi_init2(r[i], getToolPrecision());
     sollya_mpfi_set_ui(r[i],0);
   }
   
  for(i=0; i<n; i++) {
    for (j=0; j<n; j++){
      sollya_mpfi_mul(temp1, c1->poly_array[i], c2->poly_array[j]);
      if ( (i+j) < n )
	      sollya_mpfi_add(tt->poly_array[i+j], tt->poly_array[i+j], temp1);
      else
	      sollya_mpfi_add(r[i+j], r[i+j], temp1);
	      
	    if ( abs(i-j) < n )
	      sollya_mpfi_add(tt->poly_array[abs(i-j)], tt->poly_array[abs(i-j)], temp1);
      else
	      sollya_mpfi_add(r[abs(i-j)], r[abs(i-j)], temp1);  
    }
  }
  
  for(i=0; i<n; i++) {
    sollya_mpfi_div_ui(tt->poly_array[i], tt->poly_array[i], 2);
  }
  for(i=n; i<2*n-1; i++) {
    sollya_mpfi_div_ui(r[i], r[i], 2);
  }
  
  if (tightBounds>1) {
    //printf("tightBounds in multiplication");
    chebPolynomialBoundRefined(temp1, 2*n-1, r);
  }
  else {
    chebPolynomialBoundDefault(temp1, 2*n-1, r);
  }
  sollya_mpfi_add(tt->rem_bound, tt->rem_bound,temp1);
  //printf("r5:=");
  //printInterval(tt->rem_bound);
  //printf("\n");
  
  /*chebPolynomialBoundSimple(temp1,n, tt->poly_array);
  sollya_mpfi_set(tt->poly_bound,temp1);
  */
  
  for(i=0;i<2*n-1;i++) { sollya_mpfi_clear(r[i]);}
  free(r); 
  
  sollya_mpfi_clear(temp1);
  sollya_mpfi_clear(temp2);
  /*set the result*/
  copycModel(t,tt);
  /*clear the aux tm*/
  clearcModel(tt);
  //printf("Out of multiplication");
}

/* composition: g o f
   VERY IMPORTANT ASSUMPTIONS:
   We are given a cheb model for the function f over x, order n
   and a cheb model for basic function g over y, order n with:
       range(f->poly)+ f->rem_bound \subseteq y

   Note that these assumptions ARE NOT CHECKED inside the function.
   If these assumptions are true, it returns a valid taylor model for g(f(x)) over x. */

void composition_CM(chebModel *t,chebModel *g, chebModel *f, int tightBounding, mpfr_t targetRem){

/*TODO: deal with tight bounding, and with target remainder*/
/*It is ideal to bound f tightly before, such that the image over which g is computed is small*/
/*!!!!!!!!We will suppose here that the image for f is already computed tightly. Please make sure that this is the case!!!!!*/
  int i;
  int n,m;
  chebModel *tt,*tinterm,*tadd, *tcheb0,*tcheb1 ;
  sollya_mpfi_t z, zz, z1,doi,minusOne, one;
  mpfr_t a, b;
  //printf("in composition_CM\n");
  sollya_mpfi_init2(z,getToolPrecision()); 
  sollya_mpfi_init2(zz,getToolPrecision()); 
  sollya_mpfi_init2(z1,getToolPrecision()); 
  sollya_mpfi_init2(doi,getToolPrecision()); 
  sollya_mpfi_init2(minusOne,getToolPrecision()); 
  sollya_mpfi_init2(one,getToolPrecision()); 
  mpfr_init2(a,getToolPrecision());
  mpfr_init2(b,getToolPrecision());
  sollya_mpfi_set_ui(doi,2); 
  sollya_mpfi_set_ui(one,1); 
  sollya_mpfi_set_si(minusOne,-1); 
  n=g->n;
  m=f->n;
  
  /*create an itermediary cheb model for 2/(b-a) *f(x)-(b+a)/(b-a) that will be used just as a clone in multiplications:
  a:=op(1,X);
  b:=op(2,X);
  z:=2&/(b&-a);
  temp:=ctMulChebModels(C2,z);
  zz:=(b&+a)&/(b&-a);
  (temp[1])[1]:=(temp[1])[1]&-zz;
  t1:=temp;
  # in t1 we have the model that will enter as a variable in T_n(x)
  */
  tinterm=createEmptycModelPrecomp(m,f->x, f->cheb_array, f->cheb_matrix);
  copycModel(tinterm,f);
  sollya_mpfi_get_right(b,g->x);
  sollya_mpfi_get_left(a,g->x);
  sollya_mpfi_set_fr(z1,b);
  sollya_mpfi_sub_fr(z1,z1,a);
  sollya_mpfi_inv(z1,z1);
  sollya_mpfi_mul_ui(z,z1,2);
  ctMultiplication_CM(tinterm, tinterm, z);
  
  sollya_mpfi_set_fr(zz,b);
  //sollya_mpfi_add_fr(zz,zz,a);
  mpfi_add_fr(zz,zz,a);
  sollya_mpfi_mul(zz,zz,z1);
  
  sollya_mpfi_sub(tinterm->poly_array[0],tinterm->poly_array[0],zz);
  sollya_mpfi_sub(tinterm->poly_bound,tinterm->poly_bound,zz);
  
  //printf("\nThe constants to be used are: \n");
  //printInterval(z);
  //printInterval(zz);
  
  
  tt=createEmptycModelPrecomp(m,f->x,f->cheb_array, f->cheb_matrix);
  constcModel(tt,g->poly_array[0]);
  //printf("in Composition CM");  
  
  if(n>0) {
    tadd=createEmptycModelPrecomp(m,f->x,f->cheb_array, f->cheb_matrix);
    ctMultiplication_CM(tadd, tinterm, g->poly_array[1]);
    addition_CM(tt,tt,tadd);
    
    tcheb0=createEmptycModelPrecomp(m,f->x,f->cheb_array,f->cheb_matrix);
    constcModel( tcheb0, one);
    
    tcheb1=createEmptycModelPrecomp(m,f->x,f->cheb_array,f->cheb_matrix);
    copycModel(tcheb1,tinterm);
    
    /*tinterm becomes 2*x*/
    ctMultiplication_CM(tinterm, tinterm, doi);
    /*tinterm is already bounded*/
    
    for (i=2;i<n;i++){
      /*2xT_i(x)*/
      //printf("*%d*",i);
      //printf("\nstep %d in composition computation : ",i);
      if (tightBounding>1){//only if level is 2 we bound this also tightly
        chebPolynomialBoundRefined(tcheb1->poly_bound, m, tcheb1->poly_array);
      }
      else{
        chebPolynomialBoundDefault(tcheb1->poly_bound, m, tcheb1->poly_array);
      }
      multiplication_CM(tadd,tinterm,tcheb1,tightBounding,1);//2x*t_i(x)
      //printcModel(tadd);
      ctMultiplication_CM(tcheb0, tcheb0,minusOne);
      addition_CM(tadd,tadd,tcheb0);//t_{i+1}=2x*t_i(x)-t_{i-1}(x)
      //printf("\n tcheb2 = \n");
      //printcModel(tadd);
      //printf("\n^^^^^^^  ^^  ^^^^^^\n");
      copycModel(tcheb0,tcheb1); //t_{i-1}:=t_i
      copycModel(tcheb1,tadd); //t_i = t_{i+1}
      ctMultiplication_CM(tadd,tadd,g->poly_array[i]);
      addition_CM(tt,tt,tadd);
    }
  }
  sollya_mpfi_add(tt->rem_bound,tt->rem_bound,g->rem_bound);
  //the polybound is not updated
  
  
  
  copycModel(t,tt);
  clearcModel(tt);
  clearcModel(tinterm);
  if(n>0){
    clearcModel(tadd);
    clearcModel(tcheb0);
    clearcModel(tcheb1);
  }
 
  sollya_mpfi_clear(z); 
  sollya_mpfi_clear(zz); 
  sollya_mpfi_clear(z1); 
  sollya_mpfi_clear(doi); 
  sollya_mpfi_clear(minusOne); 
  sollya_mpfi_clear(one); 
  mpfr_clear(a);
  mpfr_clear(b);
  //printf("\nOut of composition\n");
  //printf("**********************\n");
  
}

/*******************************************************************************/


/*This function computes a chebyshev model for a basic function*/
/*getBasicChebModel:=proc(f,X::interval,n)
local chebCoeffs, remainder,p,i, pa, pb,a,b,aa::interval,bb::interval ;
#print("the function in basic chebmodel",f);
chebCoeffs:=getChebCoeffs(f,X,n):
#p:=unapply(getPolyFromIntervalCoeffs(chebCoeffs,X),x);
a:=op(1,X);
b:=op(2,X);
#with(intpakX):
aa:= construct(a,a);
bb:= construct(b,b);
pa:=evalIntervalChebPolyClenshaw(chebCoeffs,X,aa);
pb:=evalIntervalChebPolyClenshaw(chebCoeffs,X,bb);
remainder:=getRemainder(f,pa,pb,X,n):
return [chebCoeffs, remainder,X]
end proc:
*/


#define MONOTONE_REMAINDER_BASE_FUNCTION 0
#define MONOTONE_REMAINDER_LIBRARY_FUNCTION 1
#define MONOTONE_REMAINDER_INV 2
#define MONOTONE_REMAINDER_CONSTPOWERVAR 3
#define MONOTONE_REMAINDER_VARCONSTPOWER 4
#define MONOTONE_REMAINDER_PROCEDURE_FUNCTION 5

/* This function computes a cheb remainder for a function on an interval, assuming
   the n-th derivative is monotone.
   typeOfFunction is used to separate the cases:
   * MONOTONE_REMAINDER_BASE_FUNCTION --> we consider a base function, represented by its nodeType (p and f are useless)
   * MONOTONE_REMAINDER_LIBRARY_FUNCTION --> we consider a base function, represented by its nodeType (p and nodeType are useless)
   * MONOTONE_REMAINDER_PROCEDURE_FUNCTION --> we consider a base function, represented by its nodeType (p and nodeType are useless)
   * MONOTONE_REMAINDER_INV  --> we consider (x -> 1/x) (nodeType, f, and p are useless)
   * MONOTONE_REMAINDER_CONSTPOWERVAR --> we consider (x -> p^x) (nodeType and f are useless)
   * MONOTONE_REMAINDER_VARCONSTPOWER --> we consider (x -> x^p) (nodeType and f are useless)

   The coeffs of the interpolation polynomial
   are given as an array of mpfi's, developed over x.
   For more details, see the issac article.
*/



void computeMonotoneRemainderCheb(sollya_mpfi_t *bound, int typeOfFunction, int nodeType, node *f, mpfr_t p,
                              int n, sollya_mpfi_t *poly_array, sollya_mpfi_t x){
  sollya_mpfi_t xinf, xsup;
  mpfr_t xinfFr, xsupFr;
  sollya_mpfi_t bound1, bound2, boundx0, boundf1, boundf2, boundfx0;
  sollya_mpfi_t p_interv;
  mp_prec_t prec;
  int silent;
  silent=1;
  prec = getToolPrecision();
  
  sollya_mpfi_init2(xinf, prec);  sollya_mpfi_init2(xsup, prec);
  mpfr_init2(xinfFr, prec);   mpfr_init2(xsupFr, prec);
  sollya_mpfi_init2(bound1, prec);  sollya_mpfi_init2(bound2, prec);  sollya_mpfi_init2(boundx0, prec);  
  sollya_mpfi_init2(boundf1, prec);  sollya_mpfi_init2(boundf2, prec); sollya_mpfi_init2(boundfx0, prec); 
  sollya_mpfi_init2(p_interv, prec);

  sollya_mpfi_get_left(xinfFr,x);  sollya_mpfi_get_right(xsupFr,x); 
  sollya_mpfi_set_fr(xinf, xinfFr);  sollya_mpfi_set_fr(xsup, xsupFr);  
  
  evaluateChebPolynomialClenshaw(bound1, n, poly_array, x,xinf); /* enclosure of p(xinf) */
  //printf("\nthe value in xinf is:"); printInterval(bound1);
  
  evaluateChebPolynomialClenshaw(bound2, n, poly_array, x,xsup); /* enclosure of p(xsup) */
  //printf("\nthe value in xsup is:"); printInterval(bound2); 
  /* enclosure of f(xinf) and f(xsup) */
  switch(typeOfFunction) {
  case MONOTONE_REMAINDER_BASE_FUNCTION:
    baseFunction_diff(&boundf1,nodeType,xinf,0, &silent);
    baseFunction_diff(&boundf2,nodeType,xsup,0, &silent);
    break;
  case MONOTONE_REMAINDER_LIBRARY_FUNCTION:
    libraryFunction_diff(&boundf1, f, xinf, 0, &silent);
    libraryFunction_diff(&boundf2, f, xsup, 0, &silent);
    break;
  case MONOTONE_REMAINDER_PROCEDURE_FUNCTION:
    procedureFunction_diff(&boundf1, f, xinf, 0, &silent);
    procedureFunction_diff(&boundf2, f, xsup, 0, &silent);
    break;
  case MONOTONE_REMAINDER_INV:
    sollya_mpfi_inv(boundf1, xinf);
    sollya_mpfi_inv(boundf2, xsup);
    break;
  case MONOTONE_REMAINDER_CONSTPOWERVAR:
    sollya_mpfi_set_fr(p_interv, p);
    sollya_mpfi_pow(boundf1, xinf, p_interv);
    sollya_mpfi_pow(boundf2, xsup, p_interv);
    break;
  case MONOTONE_REMAINDER_VARCONSTPOWER:
    sollya_mpfi_set_fr(p_interv,p);
    sollya_mpfi_pow(boundf1, p_interv, xinf);
    sollya_mpfi_pow(boundf2, p_interv, xsup);
    break;
  default:
    printf("Error in chebModels: unkown type of function used with Zumkeller's technique\n");
    return;
  }
  
  
  sollya_mpfi_sub(bound1,boundf1,bound1);                          /* enclosure of f(xinf)-p(xinf-x0) */
  sollya_mpfi_sub(bound2,boundf2,bound2);                          /* enclosure of f(xsup)-p(xsup-x0) */

  sollya_mpfi_abs(bound1, bound1);
  sollya_mpfi_abs(bound2, bound2);
  //printf("\nabs1:=");
  //printInterval(bound1);
  //printf("\nabs2:=");
  //printInterval(bound2);
  sollya_mpfi_union(bound1, bound1, bound2);
  sollya_mpfi_neg(bound2, bound1);
  /* the remainder is bounded by the values it takes on the two extremas of the interval */
  sollya_mpfi_union(*bound, bound1, bound2);
  
  
  mpfr_clear(xinfFr); mpfr_clear(xsupFr);
  sollya_mpfi_clear(xinf); sollya_mpfi_clear(xsup);
  sollya_mpfi_clear(bound1); sollya_mpfi_clear(bound2); 
  sollya_mpfi_clear(boundf1);  sollya_mpfi_clear(boundf2); 
  sollya_mpfi_clear(p_interv);
  return;
}


/* This function computes a cheb model for a basic function, with the same convention
   as with computeMonotoneRemainderCheb */
void base_CMAux(chebModel *t, int typeOfFunction, int nodeType, node *f, mpfr_t p, int n, sollya_mpfi_t x,int verbosity){
  int i;
  chebModel *tt;
  sollya_mpfi_t *nDeriv;
  sollya_mpfi_t temp, pow;
  mpfr_t minusOne, a,b;
  mp_prec_t prec;
  sollya_mpfi_t *fValues;
 
  //printf("\n In baseCMAUx\n"); 
  int silent;
  silent=1; 
  prec = getToolPrecision();
   
 
   
  tt=createEmptycModelPrecomp(n,x, t->cheb_array,t->cheb_matrix);
  
  fValues= (sollya_mpfi_t *)safeMalloc((n)*sizeof(sollya_mpfi_t));
    for(i=0;i<n;i++){
      sollya_mpfi_init2(fValues[i], getToolPrecision());
    }
  /* We use AD for computing bound on the derivatives up to (n+1)th derivative */
  nDeriv= (sollya_mpfi_t *)safeCalloc((n+2),sizeof(sollya_mpfi_t));
  for(i=0;i<=n+1;i++) sollya_mpfi_init2(nDeriv[i], prec);

  switch(typeOfFunction) {
  case MONOTONE_REMAINDER_BASE_FUNCTION:
    baseFunction_diff(nDeriv, nodeType, x, n+1,&silent);
    for(i=0;i<n;i++){
      baseFunction_diff(&fValues[i],nodeType,tt->cheb_array[i],0,&silent);
    }
    break;
  case MONOTONE_REMAINDER_LIBRARY_FUNCTION:
    libraryFunction_diff(nDeriv, f, x, n+1,&silent);
    for(i=0;i<n;i++){
      libraryFunction_diff(&fValues[i],f,tt->cheb_array[i],0,&silent);
    }
    break;
  case MONOTONE_REMAINDER_PROCEDURE_FUNCTION:
    procedureFunction_diff(nDeriv, f, x, n+1,&silent);
    for(i=0;i<n;i++){
      procedureFunction_diff(&fValues[i],f,tt->cheb_array[i],0,&silent);
    }
    break;
  case MONOTONE_REMAINDER_INV: 
    mpfr_init2(minusOne, prec);
    mpfr_set_si(minusOne, -1, GMP_RNDN);
    constantPower_diff(nDeriv, x, minusOne, n+1,&silent);
    for(i=0;i<n;i++){
      constantPower_diff(&fValues[i],tt->cheb_array[i],minusOne,0,&silent);
    }
    mpfr_clear(minusOne);
    break;
  case MONOTONE_REMAINDER_CONSTPOWERVAR:
    constantPower_diff(nDeriv, x, p, n+1,&silent);
    for(i=0;i<n;i++){
      constantPower_diff(&fValues[i],tt->cheb_array[i],p,0,&silent);
    }
    break;
  case MONOTONE_REMAINDER_VARCONSTPOWER:
    powerFunction_diff(nDeriv, p, x, n+1,&silent);
    for(i=0;i<n;i++){
      powerFunction_diff(&fValues[i],p,tt->cheb_array[i],0,&silent);
    }
    break;
  default: 
    printf( "Error in ChebModels: unkown type of function used with Zumkeller's technique\n");
    return;
  }
  /*compute the values of the coefficients DONE: what to do with the chebMatrix*/
  getChebCoeffs(tt->poly_array, *(tt->cheb_matrix), fValues,n);
  
  /* Use Zumkeller technique to improve the bound in the absolute case,
     when the (n+1)th derivative has constant sign */
  if((sollya_mpfi_is_nonpos(nDeriv[n+1]) > 0)||(sollya_mpfi_is_nonneg(nDeriv[n+1]) > 0)){ 
    if (verbosity>10) {
      printf("\nthe remainder is monotone\n");
    }
    computeMonotoneRemainderCheb(&tt->rem_bound, typeOfFunction, nodeType, f, p, n, tt->poly_array, x);
  }
  else{
    /* just keep the bound obtained using AD */
    /*df:=unapply(simplify(diff(f(x),[x$n])),x);*/
    /*diffValue:=compute_naive_interval_range(df,X)&/(n!);
      diffValue:=(2&*diffValue&*((op(2,X)-op(1,X))^(n)))&/(4^n );*/
    
    //mpfr_init2(fac,prec);
    //mpfr_fac_ui(fac,n,GMP_RNDN);
    //sollya_mpfi_div_fr(tt->rem_bound, nDeriv[n], fac);
    //mpfi_div_fr(tt->rem_bound, nDeriv[n], fac);
    /*nderiv is already divided by the factorial*/
    //printInterval( nDeriv[n]);
    //mpfr_clear(fac);
    mpfi_set(tt->rem_bound, nDeriv[n]);
    mpfr_init2(a, prec);
    mpfr_init2(b, prec);
    sollya_mpfi_get_left(a,x);
    sollya_mpfi_get_right(b,x);
    sollya_mpfi_init2(temp, prec);
    sollya_mpfi_set_fr(temp, b);
    sollya_mpfi_sub_fr(temp, temp,a);
    sollya_mpfi_init2(pow, prec);
    sollya_mpfi_set_ui(pow, n);
    sollya_mpfi_pow(temp, temp, pow);
    sollya_mpfi_mul(tt->rem_bound,tt->rem_bound,temp);
    sollya_mpfi_mul_ui(tt->rem_bound,tt->rem_bound,2);  
    sollya_mpfi_set_ui(temp, 4);
    sollya_mpfi_pow(temp, temp, pow);
    
    sollya_mpfi_div(tt->rem_bound,tt->rem_bound,temp);
    sollya_mpfi_neg(temp,tt->rem_bound);
    sollya_mpfi_union(tt->rem_bound,tt->rem_bound,temp);
    sollya_mpfi_clear(temp);
    sollya_mpfi_clear(pow);
    mpfr_clear(a);
    mpfr_clear(b);
     
  }
   
  
  /* TODO bound the polynomial obtained - for the moment I consider that I will not bound the polynomials, only when needed*/
 
  
  copycModel(t,tt);
  clearcModel(tt);
  
  for(i=0;i<=n+1;i++)  sollya_mpfi_clear(nDeriv[i]);
  free(nDeriv);  
  
  for(i=0;i<n;i++){
    sollya_mpfi_clear(fValues[i]);
  }
  free(fValues);
}


void cheb_model(chebModel *t, node *f, int n, sollya_mpfi_t x, int tightBounding, int verbosity) {
  int i;
  
  node *simplifiedChild1, *simplifiedChild2;
  sollya_mpfi_t temp1,temp2;
  
  
  chebModel *tt, *child1_tm, *child2_tm, *ctPowVar_tm, *logx_tm, *expx_tm, *logf_tm;
  
  /*used by division*/
  sollya_mpfi_t rangeg;
  chebModel *ttt, *inv_tm;


  //sollya_mpfi_t powx,powy;
  sollya_mpfi_t minusOne;
  //mpfr_t zero;
  /*used by base functions*/
  //sollya_mpfi_t fx0,rangef,pow;
  sollya_mpfi_t rangef;
  if (isPolynomial(f) ){
    
    /*****Do the basis conversion***************/
    tt=createEmptycModelPrecomp(n,t->x, t->cheb_array, t->cheb_matrix);
    getNChebCoeffsFromPolynomial(tt->poly_array, tt->poly_bound, f, x,n);
    sollya_mpfi_set_ui(tt->rem_bound, 0);
    copycModel(t,tt);
    if (verbosity>10) {
      printf("\nPolynomial model\n");
      printcModel(t);
      printf("\n****************\n");
    }
    //clear old cheby models
    clearcModel(tt);
  }
  else {
    switch (f->nodeType) {
  
    case NEG:
      //create a new empty cheb model the child
      child1_tm=createEmptycModelPrecomp(n,t->x, t->cheb_array,t->cheb_matrix);
      //call cheby_model on the child
      cheb_model(child1_tm, f->child1,n,x, tightBounding, verbosity);
      tt=createEmptycModelPrecomp(n,t->x, t->cheb_array,t->cheb_matrix);
      //do the necessary chages from child to parent
      for(i=0;i<n;i++) 
      sollya_mpfi_neg(tt->poly_array[i], child1_tm->poly_array[i]);
    
      sollya_mpfi_neg(tt->rem_bound,child1_tm->rem_bound);
      //sollya_mpfi_neg(tt->poly_bound,child1_tm->poly_bound);
      copycModel(t,tt);
      if (verbosity>10) {
        printf("\nNegation model\n");
        printcModel(t);
        printf("\n****************\n");
      }
    
      //clear old cheby models
      clearcModel(child1_tm);
      clearcModel(tt);
      break;
   

    case ADD:
      
      //create a new empty chebmodel the children
      
      child1_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array,t->cheb_matrix);
      child2_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array,t->cheb_matrix);
      //call cheby_model on the children
      cheb_model(child1_tm, f->child1,n,x,tightBounding, verbosity);
      cheb_model(child2_tm, f->child2,n,x,tightBounding, verbosity);
      tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array,child1_tm->cheb_matrix);
      addition_CM(tt,child1_tm, child2_tm);
      copycModel(t,tt);
      if (verbosity>10) {
        printf("\nADD model\n");
        printcModel(t);
        printf("\n****************\n");
      }
      //clear old cheby model
      clearcModel(child1_tm);
      clearcModel(child2_tm);
      clearcModel(tt);
      break;
  
    case SUB:
           
      //create a new empty cheby model the children
      child1_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array,t->cheb_matrix);
      child2_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array,t->cheb_matrix);
      //call cheby_model on the children
      cheb_model(child1_tm, f->child1,n,x,tightBounding, verbosity);
      cheb_model(child2_tm, f->child2,n,x,tightBounding, verbosity);
      
      //do the necessary chages from children to parent
      sollya_mpfi_init2(minusOne,getToolPrecision());
      sollya_mpfi_set_si(minusOne,-1);
      ctMultiplication_CM(child2_tm,child2_tm, minusOne);
      tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array, child1_tm->cheb_matrix);
      addition_CM(tt,child1_tm, child2_tm);
      if (verbosity>10) {
        printf("\nSUB model\n");
        printcModel(t);
        printf("\n****************\n");
      }
      
      copycModel(t,tt);
    
      //clear old cheby model
      clearcModel(child1_tm);
      clearcModel(child2_tm);
      clearcModel(tt);
      sollya_mpfi_clear(minusOne);
      break;

    case MUL:
     //create a new empty taylor model the children
     child1_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);
     child2_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);
     //call cheby_model on the children
     cheb_model(child1_tm, f->child1,n,x,tightBounding, verbosity);
     cheb_model(child2_tm, f->child2,n,x,tightBounding, verbosity);
    
     //do the necessary chages from children to parent
     tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array,  child1_tm->cheb_matrix);
     //pushTimeCounter();
     multiplication_CM(tt,child1_tm, child2_tm,tightBounding,0);
     //popTimeCounter("Multipling 2 CMs");
     copycModel(t,tt);
     if (verbosity>10) {
        printf("\nMultiplication model\n");
        printcModel(t);
        printf("\n****************\n");
      }
     //clear old cheby model
     clearcModel(child1_tm);
     clearcModel(child2_tm);     
     clearcModel(tt);
     break;

    case DIV:
  
          
      //create a new empty cheby model the child
      child1_tm=createEmptycModelPrecomp(n,t->x, t->cheb_array, t->cheb_matrix);
      //call cheb_model on the child
      cheb_model(child1_tm, f->child1,n,x,tightBounding, verbosity);
      //create a new empty cheby model the child
      child2_tm=createEmptycModelPrecomp(n,t->x, t->cheb_array,t->cheb_matrix);
      //call cheb_model on the child
      cheb_model(child2_tm, f->child2,n,x,tightBounding, verbosity);
      //compute cm for the basic case
      sollya_mpfi_init2(rangeg, getToolPrecision());
      if (tightBounding>0){ //tightBounding level can be 0 ->everything default, 1 - composition image refined, 2- everything refined
        chebPolynomialBoundRefined(child2_tm->poly_bound, n, child2_tm->poly_array);
      }
      else{
        chebPolynomialBoundDefault(child2_tm->poly_bound, n, child2_tm->poly_array); 
      }
      sollya_mpfi_add(rangeg,child2_tm->rem_bound, child2_tm->poly_bound);
      //printInterval(rangeg);
      inv_tm=createEmptycModelCompute(n,rangeg,1,1);
      base_CMAux(inv_tm, MONOTONE_REMAINDER_INV, 0, NULL, NULL, n, rangeg,verbosity);
      //printf("We compose");
      ttt=createEmptycModelPrecomp(n,child2_tm->x, child2_tm->cheb_array,child2_tm->cheb_matrix);
      composition_CM(ttt,inv_tm, child2_tm, tightBounding, NULL);
      
      if (verbosity>10) {
        printf("\nIn inverse Composition model\n");
        printcModel(ttt);
        printf("\n****************\n");
      }
      //child1 * inverse(child2)
      tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array,  child1_tm->cheb_matrix);
      multiplication_CM(tt, ttt, child1_tm, tightBounding,0);
      
      //clear old children
      clearcModel(child1_tm);
      clearcModel(child2_tm);
      clearcModel(inv_tm);
      clearcModel(ttt);
      copycModel(t,tt);
      if (verbosity>10) {
        printf("\nInverse model\n");
        printcModel(t);
        printf("\n****************\n");
      }
      clearcModel(tt);
      sollya_mpfi_clear(rangeg);
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
    case SINGLE:
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
    case LIBRARYFUNCTION:
      
      if (((f->child1)->nodeType)==VARIABLE) {
         child1_tm=createEmptycModelPrecomp(n,t->x, t->cheb_array,t->cheb_matrix);
         //printf("\n************* cheby model for elementary function************\n");
         if (f->nodeType == LIBRARYFUNCTION)
          base_CMAux(child1_tm, MONOTONE_REMAINDER_LIBRARY_FUNCTION, 0, f, NULL, n, x, verbosity);
         else
          base_CMAux(child1_tm, MONOTONE_REMAINDER_BASE_FUNCTION, f->nodeType, NULL, NULL, n,x, verbosity);

         if (verbosity>10) {
          printf("\nIn Base function, has variable child\n");
          printcModel(child1_tm);
          printf("****************\n");
         }
      copycModel(t,child1_tm);
      clearcModel(child1_tm);   
      }
      else{   
      
      //create a new empty cheby model the child
      child1_tm=createEmptycModelPrecomp(n,t->x, t->cheb_array,t->cheb_matrix);
    
      //call cheb_model on the child
      cheb_model(child1_tm, f->child1,n,x,tightBounding, verbosity);
      if (verbosity>10) {
        printf("\nIn Base function, child model\n");
        printcModel(child1_tm);
        printf("\n****************\n");
      }
      sollya_mpfi_init2(rangeg, getToolPrecision());
      
      if (tightBounding>0){
        chebPolynomialBoundRefined(child1_tm->poly_bound, n, child1_tm->poly_array);
      }
      else{
        chebPolynomialBoundDefault(child1_tm->poly_bound, n, child1_tm->poly_array); 
      }
      sollya_mpfi_add(rangeg,child1_tm->rem_bound, child1_tm->poly_bound);
       if (verbosity>12) {
        printf("\n We compute the cheb model over:");
        printInterval(rangeg);
        printf("\n");
       }
      child2_tm=createEmptycModelCompute(n,rangeg,1,1);
      
      //printf("\n************* cheby model for elementary function************\n");
      if (f->nodeType == LIBRARYFUNCTION)
        base_CMAux(child2_tm, MONOTONE_REMAINDER_LIBRARY_FUNCTION, 0, f, NULL, n, rangeg, verbosity);
      else
        //printf("Before Base function");
        base_CMAux(child2_tm, MONOTONE_REMAINDER_BASE_FUNCTION, f->nodeType, NULL, NULL, n,rangeg, verbosity);

       if (verbosity>10) {
        printf("\nIn Base function, parent model\n");
        printcModel(child2_tm);
        printf("****************\n");
      }
     
      
      tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array, child1_tm->cheb_matrix);
      composition_CM(tt,child2_tm, child1_tm, tightBounding,NULL);
      //printf("\n\n*************after the composition************\n");   
      //printcModel(tt);
      
      //clear old child
      clearcModel(child1_tm);
      clearcModel(child2_tm);
      copycModel(t,tt);
      clearcModel(tt);
      sollya_mpfi_clear(rangeg);  
    }    
    break;
   
    case POW:
  
     
  
      simplifiedChild2=simplifyTreeErrorfree(f->child2);
      simplifiedChild1=simplifyTreeErrorfree(f->child1);
      
      if ((simplifiedChild2->nodeType==CONSTANT) &&(simplifiedChild1->nodeType==CONSTANT)) { //we have the ct1^ct2 case
         // printf("We are in the  ct1^ct2 case");       
         sollya_mpfi_init2(temp1, getToolPrecision());
         sollya_mpfi_set_fr(temp1, *(simplifiedChild1->value));
         sollya_mpfi_init2(temp2, getToolPrecision());
         sollya_mpfi_set_fr(temp2, *(simplifiedChild2->value));
         sollya_mpfi_pow(temp1,temp1,temp2);
         tt=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix); 
         constcModel(tt,temp1);
         copycModel(t,tt);
         clearcModel(tt);
         sollya_mpfi_clear(temp1);
         sollya_mpfi_clear(temp2);
      }
      else if (simplifiedChild2->nodeType==CONSTANT) { //we have the f^p case
        //printf("We are in the  f^p case");        
        tt=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);           
        child1_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);
        //call taylor_model for the child
        cheb_model(child1_tm, f->child1,n,x, tightBounding, verbosity);
                      
        sollya_mpfi_init2(rangeg, getToolPrecision());
         
        if (tightBounding>0){
          chebPolynomialBoundRefined(child1_tm->poly_bound, n, child1_tm->poly_array);
        }
        else{
          chebPolynomialBoundDefault(child1_tm->poly_bound, n, child1_tm->poly_array); 
        }
        sollya_mpfi_add(rangeg,child1_tm->rem_bound, child1_tm->poly_bound);
        //create cm for x^p over rangeg
        
        ctPowVar_tm=createEmptycModelCompute(n,rangeg,1,1);
        
        base_CMAux(ctPowVar_tm, MONOTONE_REMAINDER_CONSTPOWERVAR, 0, NULL, *(simplifiedChild2->value), n,rangeg, verbosity);
        
        //printf("\n\n-----------chebrmodel child1: \n");
        //printtModel(ctPowVar_tm);
        //printf("-----------------------------\n");
        
        tt=createEmptycModelPrecomp(n,child1_tm->x, child1_tm->cheb_array, child1_tm->cheb_matrix);
        composition_CM(tt,ctPowVar_tm,child1_tm, tightBounding, NULL);
    
        //clear old child
        clearcModel(child1_tm);
        clearcModel(ctPowVar_tm);
        copycModel(t,tt);
        clearcModel(tt);
        sollya_mpfi_clear(rangeg);
       
      } 
      else if (simplifiedChild1->nodeType==CONSTANT) { //we have the p^f case
             
                  
         //create a new empty cheby model for the child
        child2_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);
        //call taylor_model for the child
        cheb_model(child2_tm, f->child2,n,x, tightBounding, verbosity);
                      
        sollya_mpfi_init2(rangeg, getToolPrecision());
        if (tightBounding>0){
          chebPolynomialBoundRefined(child2_tm->poly_bound, n, child2_tm->poly_array);
        }
        else{
          chebPolynomialBoundDefault(child2_tm->poly_bound, n, child2_tm->poly_array); 
        }
        sollya_mpfi_add(rangeg,child2_tm->rem_bound, child2_tm->poly_bound);
        
         
        ctPowVar_tm=createEmptycModelCompute(n,rangeg,1,1);
        
        
        base_CMAux(ctPowVar_tm, MONOTONE_REMAINDER_VARCONSTPOWER, 0, NULL, *(simplifiedChild1->value), n,rangeg, verbosity);
        
         tt=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);  
        composition_CM(tt,ctPowVar_tm,child2_tm, tightBounding, NULL);
    
        //clear old child
        clearcModel(child2_tm);
        clearcModel(ctPowVar_tm);
        copycModel(t,tt);
        clearcModel(tt);
        sollya_mpfi_clear(rangeg);
        
        }
      else {
      //printf("We are in the  f^g case");  
      //exp(g log(f))
       
        //create a new empty taylor model the children
        /*g*/
       child2_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);    
       cheb_model(child2_tm, f->child2,n,x, tightBounding, verbosity); 
       
       
       /*f*/
       child1_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);    
       cheb_model(child1_tm, f->child1,n,x, tightBounding, verbosity); 
        
        //create  cheb_model for log (child 1) = log(f)
                
        /*log f*/
       sollya_mpfi_init2(rangef, getToolPrecision());
       if (tightBounding>0){
          chebPolynomialBoundRefined(child1_tm->poly_bound, n, child1_tm->poly_array);
        }
        else{
          chebPolynomialBoundDefault(child1_tm->poly_bound, n, child1_tm->poly_array); 
        }
       
       sollya_mpfi_add(rangef,child1_tm->rem_bound, child1_tm->poly_bound);
       logx_tm=createEmptycModelCompute(n,rangef,1,1);
       base_CMAux(logx_tm, MONOTONE_REMAINDER_BASE_FUNCTION, LOG, NULL, NULL, n, rangef, verbosity);
       logf_tm=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix); 
       composition_CM(logf_tm, logx_tm,child1_tm, tightBounding, NULL);
       //-------------------------------------------
        
        /*glog f*/
       ttt=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);       
       multiplication_CM(ttt,logf_tm,child2_tm, tightBounding,0);
       
       
       /*exp(g log f)*/
       
       if (tightBounding>0){
          chebPolynomialBoundRefined(ttt->poly_bound, n,ttt->poly_array);
        }
        else{
          chebPolynomialBoundDefault(ttt->poly_bound, n, ttt->poly_array); 
        }
       sollya_mpfi_add(rangef,ttt->rem_bound, ttt->poly_bound);
       expx_tm=createEmptycModelCompute(n,rangef,1,1);
       base_CMAux(expx_tm, MONOTONE_REMAINDER_BASE_FUNCTION, EXP, NULL, NULL, n,rangef, verbosity);
       
       tt=createEmptycModelPrecomp(n,t->x,t->cheb_array, t->cheb_matrix);    
       composition_CM(tt,expx_tm,ttt, tightBounding, NULL);
       
               
    
        //clear old child
        clearcModel(child2_tm);
        clearcModel(child1_tm);
        clearcModel(ttt);
        clearcModel(expx_tm);
        clearcModel(logx_tm);
        clearcModel(logf_tm);
        
        copycModel(t,tt);
        clearcModel(tt);
        sollya_mpfi_clear(rangef);
        
    }
    free_memory(simplifiedChild2);
    free_memory(simplifiedChild1);
    break;
    
  default:
   printf("Error: TM: unknown identifier (%d) in the tree\n",f->nodeType);
   exit(1);
  }
}
  return;
}


int CM(chain**resP, void **args) {
  node *f;
  sollya_mpfi_t x, zero;
  sollya_mpfi_t **coeffs;
  int n,i,tightBounding, verbosity;
  chebModel *t;
  chain *ch;
  chain *err;
  sollya_mpfi_t *coeffsErrors, *rest;
  node **T, **T1, **T2;
  
  mpfr_t *coeffsMpfr;
  mpfr_t u,v;

  sollya_mpfi_init2(zero, getToolPrecision());
  sollya_mpfi_set_ui(zero,0);
  
  
  
  f = (node *)args[0];
  n = *( (int *)args[2] );
  tightBounding=*( (int *)args[3] );
   verbosity=*( (int *)args[4] );
  sollya_mpfi_init2(x, getToolPrecision());
  sollya_mpfi_set(x, *( (sollya_mpfi_t *)args[1] ));
  
  /* Check if degree is at least 1, once it has been adjusted */
  if (n < 1) {
    printMessage(1,"Warning: the degree of a Cheb Model must be at least 0.\n");
	ch=NULL;
	 *resP=ch;
    return 0;
  } 

  ch=NULL;

  
  t=createEmptycModelCompute(n,x,1,1);
 
  cheb_model(t, f, n, x, tightBounding, verbosity);
  if (verbosity>0){
  printcModel(t);
  printf("\nThe model is computed with bounding level %d \n", tightBounding);
  }
  
   
   /*zz = (sollya_mpfi_t*)safeMalloc(sizeof(sollya_mpfi_t));
  sollya_mpfi_init2(*zz, getToolPrecision());
  sollya_mpfi_set(*zz, t->rem_bound);
  ch=addElement(ch,zz);
 
  zz = (sollya_mpfi_t*)safeMalloc(sizeof(sollya_mpfi_t));
  sollya_mpfi_init2(*zz, getToolPrecision());
  sollya_mpfi_set(*zz, t->poly_bound);
  ch=addElement(ch,zz);
  
  for (i=n-1; i>=0;i--){
  zz = (sollya_mpfi_t*)safeMalloc(sizeof(sollya_mpfi_t));
  sollya_mpfi_init2(*zz, getToolPrecision());
  sollya_mpfi_set(*zz, t->poly_array[i]);
  ch=addElement(ch,zz);
  }
  */
  
  coeffs = (sollya_mpfi_t**)safeMalloc(sizeof(sollya_mpfi_t*));
  //printf("\nBefore getCoeffsFromChebPolynomial1\n");
  getCoeffsFromChebPolynomial(coeffs, t->poly_array, n, x);
  //printf("\nTgetCoeffsFromChebPolynomial works1\n");
  coeffsMpfr= (mpfr_t *)safeCalloc((n),sizeof(mpfr_t));
  coeffsErrors = (sollya_mpfi_t *)safeCalloc((n),sizeof(sollya_mpfi_t));

  rest= (sollya_mpfi_t*)safeMalloc(sizeof(sollya_mpfi_t));
  sollya_mpfi_init2(*rest,getToolPrecision());

  for(i=0;i<n;i++){
    sollya_mpfi_init2(coeffsErrors[i],getToolPrecision());
    mpfr_init2(coeffsMpfr[i],getToolPrecision());
  }
  //printf("\n Before mpfr get poly1\n");
  mpfr_get_poly(coeffsMpfr, coeffsErrors, *rest, n-1,*coeffs, zero,x);
  //printf("\n After mpfr get poly1\n");
  //create T; 
  T=(node**)safeMalloc(sizeof(node*));
  *T=makePolynomial(coeffsMpfr, (t->n)-1);
 //printf("\n After make poly1\n");
  //create errors;
  err=constructChain(coeffsErrors,t->n-1);
  
  ch=addElement(ch,*T);
  
  mpfi_add(t->rem_bound, t->rem_bound,*rest);
  mpfr_init2(u, getToolPrecision());
  mpfr_init2(v, getToolPrecision());
  sollya_mpfi_get_left(u,t->rem_bound);
  
  sollya_mpfi_get_right(v,t->rem_bound);
  
  T1=(node**)safeMalloc(sizeof(node*));
  *T1=makeConstant(u);
  
  ch=addElement(ch,*T1);
  
  T2=(node**)safeMalloc(sizeof(node*));
  *T2=makeConstant(v);
  
  ch=addElement(ch,*T2);
  *resP=ch;
  clearcModel(t);
     
  return 1;
}

int CertifiedIntegral(chain**resP, void **args) {
  node *f;
  sollya_mpfi_t x, zero,ui,vi,temp;
  sollya_mpfi_t *c;
  int n,i,tightBounding, verbosity;
  chebModel *t;
  chain *ch;
  
  
  node  **T1, **T2;
  
  
  mpfr_t u,v;

  sollya_mpfi_init2(zero, getToolPrecision());
  sollya_mpfi_set_ui(zero,0);
  
 
  
  f = (node *)args[0];
  n = *( (int *)args[2] );
  tightBounding=*( (int *)args[3] );
   verbosity=*( (int *)args[4] );
  sollya_mpfi_init2(x, getToolPrecision());
  sollya_mpfi_set(x, *( (sollya_mpfi_t *)args[1] ));
  
  /* Check if degree is at least 1, once it has been adjusted */
  if (n < 1) {
    printMessage(1,"Warning: the degree of a Cheb Model must be at least 0.\n");
     ch=NULL;
    return 0;
  } 

  ch=NULL;
 if (verbosity>0) {
  printf("In certified integral");
  }
  
  t=createEmptycModelCompute(n,x,1,1);
 
  cheb_model(t, f, n, x, tightBounding, verbosity);
  if (verbosity>0){
  printcModel(t);
  printf("\nThe model is computed with bounding level %d \n", tightBounding);
  }
  
   c=(sollya_mpfi_t *)safeMalloc((n+1)*sizeof(sollya_mpfi_t));
  for (i=0;i<n+1;i++){
      sollya_mpfi_init2(c[i],getToolPrecision());
  }
  getChebCoeffsIntegrationPolynomial(c, t->poly_array, n, x);
  
  /*Compute a bound for the integration of the remainder |R|*(x_right-x_left)*/
  mpfr_init2(u, getToolPrecision());
  mpfr_init2(v, getToolPrecision());
  sollya_mpfi_get_left(u,x);
  sollya_mpfi_get_right(v,x);
  
  sollya_mpfi_init2(ui, getToolPrecision());
  sollya_mpfi_init2(vi, getToolPrecision());
  sollya_mpfi_set_fr(ui,u);
  sollya_mpfi_set_fr(vi,v);
 
  
  sollya_mpfi_init2(temp, getToolPrecision());
  
  sollya_mpfi_sub(temp, vi, ui);
  sollya_mpfi_abs(t->rem_bound, t->rem_bound);
  sollya_mpfi_mul(temp, temp, t->rem_bound);
  if (verbosity>0){
    printf("\nConstant part of the integral:");
    printInterval(temp);
  } 
  
  /*Compute P_integrated(x_right) - P_integrated(x_left)*/
  evaluateChebPolynomialClenshaw(ui, n+1, c, x,ui );
  if (verbosity>0){
    printf("\nevaluation to the left:");
    printInterval(ui);
  }
   
  evaluateChebPolynomialClenshaw(vi, n+1, c, x,vi );
  if (verbosity>0){
    printf("\nevaluation to the right:");
    printInterval(vi);
  }
  sollya_mpfi_sub(ui, vi, ui);
  sollya_mpfi_add(temp, temp, ui);
  
  if (verbosity>0){
    printf("\nfinal bound:");
    printInterval(temp);  
  }
 
 
 
  mpfr_init2(u, getToolPrecision());
  mpfr_init2(v, getToolPrecision());
  sollya_mpfi_get_left(u,temp);
  sollya_mpfi_get_right(v,temp);
  
  T2=(node**)safeMalloc(sizeof(node*));
  *T2=makeConstant(v);
  
  ch=addElement(ch,*T2);
  
  T1=(node**)safeMalloc(sizeof(node*));
  *T1=makeConstant(u);
  
  ch=addElement(ch,*T1);
  
 
  
   *resP=ch;
  clearcModel(t);
  sollya_mpfi_clear(temp); 
  mpfr_clear(u); 
  mpfr_clear(v); 
  sollya_mpfi_clear(ui);  
  sollya_mpfi_clear(vi); 
  for (i=0;i<n+1;i++){
      sollya_mpfi_clear(c[i]);
  } 
 free(c);
 sollya_mpfi_clear(x);
 //free_memory(f);
 return 1;
}

int TB(chain**resP, void **args){
  node *f;
  sollya_mpfi_t x, bound;
  mpfr_t gamma;
  chain *ch;
  f = (node *)args[0];
  sollya_mpfi_init2(x, getToolPrecision());
  sollya_mpfi_set(x, *( (sollya_mpfi_t *)args[1] ));
  mpfr_init2(gamma, getToolPrecision());
  mpfr_set(gamma, *( (mpfr_t *)args[2]),GMP_RNDN);
  sollya_mpfi_init2(bound, getToolPrecision());
  polynomialBoundRefined(bound,f,x,gamma, getToolPrecision());
  printInterval(bound);
   ch=NULL;
    ch=addElement(ch,f);
   *resP=ch;
   
  return 1; 
}





