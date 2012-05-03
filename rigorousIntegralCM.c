#include "chebyshevform.c"
/*For compiling this file:
    gcc -fPIC -Wall -c rigorousIntegralCM.c
    gcc -fPIC -shared -o rigorousIntegralCM rigorousIntegralCM.o
    
    From sollya:
    externalproc(CertifiedIntegral, "./rigorousIntegralCM", (function, range, integer,integer, integer) ->list of function);
    z=CertifiedIntegral(4/(1+x^2),[0,1],20,0,0);
*/
int CertifiedIntegral(chain**resP, void **args) {
  node *f;
  sollya_mpfi_t dom,ui,vi,temp;
  sollya_mpfi_t *c;
  int n,i,tightBounding, verbosity;
  chebModel *t;
  chain *ch;
  
  mp_prec_t prec;
  node  **T1, **T2;
  
  
  mpfr_t u,v, domR, domL;

  prec=getToolPrecision();
  
  f = (node *)args[0];
  n = *( (int *)args[2] );
  tightBounding=*( (int *)args[3] );
   verbosity=*( (int *)args[4] );
  sollya_mpfi_init2(dom, prec);
  sollya_mpfi_set(dom, *( (sollya_mpfi_t *)args[1] ));
  
  
  /* Check if degree is at least 1, once it has been adjusted */
  if (n < 1) {
    printMessage(1,"Warning: the degree of a Chebyshev Model must be at least 0.\n");
    ch = NULL;
    return 0;
  }
  
  /*  Check that the interval dom is not a point interval*/
  mpfr_init2(domR, sollya_mpfi_get_prec(dom));
  sollya_mpfi_get_right(domR, dom);

  mpfr_init2(domL, sollya_mpfi_get_prec(dom));
  sollya_mpfi_get_left(domL, dom);
  
  
  if (mpfr_cmp(domR,domL)==0) {
    printMessage(1,"Warning: the domain of a Chebyshev Model can not be a point interval.\n");
    mpfr_clear(domL);
    mpfr_clear(domR);
    ch = NULL;
    return 0;
  }
  mpfr_clear(domL);
  mpfr_clear(domR);
  t=createEmptycModelCompute(n,dom,1,1, prec);
  if (verbosity>10){
    printf("we have created an emptyChebmodel \n");
  }
  cheb_model(t, f, n, dom, tightBounding, verbosity, prec);
  if (verbosity>5){
    printcModel(t);
  }
  c=(sollya_mpfi_t *)safeMalloc((n+1)*sizeof(sollya_mpfi_t));
  for (i=0;i<n+1;i++){
      sollya_mpfi_init2(c[i],prec);
  }
  getChebCoeffsIntegrationPolynomial(c, t->poly_array, n, dom);
  
  /*Compute a bound for the integration of the remainder |R|*(x_right-x_left)*/
  mpfr_init2(u, prec);
  mpfr_init2(v, prec);
  sollya_mpfi_get_left(u,dom);
  sollya_mpfi_get_right(v,dom);
  
  sollya_mpfi_init2(ui, prec);
  sollya_mpfi_init2(vi, prec);
  sollya_mpfi_set_fr(ui,u);
  sollya_mpfi_set_fr(vi,v);
 
  
  sollya_mpfi_init2(temp, prec);
  
  sollya_mpfi_sub(temp, vi, ui);
  sollya_mpfi_abs(t->rem_bound, t->rem_bound);
  sollya_mpfi_mul(temp, temp, t->rem_bound);
  if (verbosity>0){
    printf("\nConstant part of the integral = ");
    printInterval(temp);
    printf("\n");
  } 
  
  /*Compute P_integrated(x_right) - P_integrated(x_left)*/
  evaluateChebPolynomialClenshaw(ui, n+1, c, dom,ui );
  if (verbosity>0){
    printf("\nEvaluation to the left = ");
    printInterval(ui);
    printf("\n");
  }
   
  evaluateChebPolynomialClenshaw(vi, n+1, c, dom,vi );
  if (verbosity>0){
    printf("\nEvaluation to the right = ");
    printInterval(vi);
    printf("\n");
  }
  sollya_mpfi_sub(ui, vi, ui);
  sollya_mpfi_add(temp, temp, ui);
  
  if (verbosity>0){
    printf("\nFinal bound = ");
    printInterval(temp);  
    printf("\n");
  }
  
  sollya_mpfi_get_left(u,temp);
  sollya_mpfi_get_right(v,temp);
  ch=NULL;
  T2=(node**)safeMalloc(sizeof(node*));
  *T2=makeConstant(v);
  ch=addElement(ch,*T2); 
  T1=(node**)safeMalloc(sizeof(node*));
  *T1=makeConstant(u);
  
  ch=addElement(ch,*T1);
  
  
 
 
  
  *resP=ch;
  clearcModelComplete(t);
  sollya_mpfi_clear(temp); 
  mpfr_clear(u); 
  mpfr_clear(v); 
  sollya_mpfi_clear(ui);  
  sollya_mpfi_clear(vi); 
  for (i=0;i<n+1;i++){
      sollya_mpfi_clear(c[i]);
  } 
 free(c);
 sollya_mpfi_clear(dom);
 return 1;
}

