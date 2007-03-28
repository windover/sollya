#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "pari_utils.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>


// Constructs the tree corresponding to p = sum(coeff(i) X^monomials[i])
node *constructPolynomial(GEN coeff, chain *monomials, mp_prec_t prec) {
  int i=1;
  chain *curr;
  node *temp1;
  node *temp2;
  node *temp3;
  node *temp4;
  node *temp5;
  node *temp6;
  node *poly;
  mpfr_t *ptr;

  if (lengthChain(monomials) != itos((GEN)(matsize(coeff)[1]))-1) {
    fprintf(stderr,"Error : inconsistant lengths in function constructPolynomial.\n");
    recoverFromError();
  }

  poly =  safeMalloc(sizeof(node));
  poly->nodeType = CONSTANT;
  ptr = safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*ptr, prec);
  mpfr_set_d(*ptr, 0., GMP_RNDN);
  poly->value = ptr;

  curr = monomials;
  while(curr != NULL) {
    temp1 = safeMalloc(sizeof(node));
    temp1->nodeType = ADD;

    temp2 = safeMalloc(sizeof(node));
    temp2->nodeType = MUL;

    temp3 = safeMalloc(sizeof(node));
    temp3->nodeType = CONSTANT;
    ptr = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*ptr, prec);
    PARI_to_mpfr(*ptr, (GEN)(coeff[i]), GMP_RNDN);
    temp3->value = ptr;

    temp4 = safeMalloc(sizeof(node));
    temp4->nodeType = POW;

    temp5 = safeMalloc(sizeof(node));
    temp5->nodeType = VARIABLE;

    temp6 = safeMalloc(sizeof(node));
    temp6->nodeType = CONSTANT;
    ptr = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*ptr, prec);
    mpfr_set_si(*ptr, *((int *)(curr->value)), GMP_RNDN);
    temp6->value = ptr;

    temp4->child1 = temp5;
    temp4->child2 = temp6;
    temp2->child1 = temp3;
    temp2->child2 = temp4;
    temp1->child1 = temp2;
    temp1->child2 = poly;
    poly = temp1;
    i++;
    curr = curr->next;
  }

  return poly;
}



// This function finds an approximate zero of a function f
// (which derivative if f_diff) in the interval [a;b]
// using x0 as an initial guess of the zero
// If n=0 the algorithm stops when the computed zero is
// a precise estimation of the real zero.
// If n<>0, n steps are computed.
// The algorithm uses Newton's method
// It is assumed that f(a)f(b)<=0 and x0 in [a;b]
GEN findZero(node *f, node *f_diff, mpfr_t a, mpfr_t b, int sgnfa, GEN x0, int n, mp_prec_t prec) {
  node *iterator;
  node *temp1;
  mpfr_t x, y, zero_mpfr;
  mp_prec_t estim_prec;
  int r, nbr_iter,test, n_expo;
  GEN res;

  mpfr_init2(x,prec);
  mpfr_init2(y,prec);
  mpfr_init2(zero_mpfr,53);


  if(x0!=NULL) PARI_to_mpfr(x,x0,GMP_RNDN);
  else {
    mpfr_add(x,a,b,GMP_RNDN);
    mpfr_div_2ui(x,x,1,GMP_RNDN);
  }

  if(verbosity>=4) {
    printf("Newton's call with parameters :"); printTree(f); printf("\n");
    printMpfr(a); printMpfr(b);
    printMpfr(x); evaluateFaithful(y,f,x,prec); printMpfr(y);
  }

  mpfr_set_d(zero_mpfr,0.,GMP_RNDN);
  n_expo = 0;
  estim_prec = 1;

  iterator = safeMalloc(sizeof(node));
  iterator->nodeType = SUB;
  temp1 = safeMalloc(sizeof(node));
  temp1->nodeType = VARIABLE;
  iterator->child1 = temp1;
  
  temp1 = safeMalloc(sizeof(node));
  temp1->nodeType = DIV;
  temp1->child1 = copyTree(f);
  temp1->child2 = copyTree(f_diff);
  iterator->child2 = temp1;

  nbr_iter=1;
  test=1;
  while(test) {
    r = evaluateFaithfulWithCutOffFast(y, iterator, NULL, x, zero_mpfr, prec);
    if((!mpfr_number_p(y)) && (r==1)) {
      fprintf(stderr,"Warning: Newton algorithm encountered numerical problems\n");
      res = mpfr_to_PARI(x);
      free_memory(iterator);
      mpfr_clear(x);
      mpfr_clear(y);
      mpfr_clear(zero_mpfr);
      return res;
    }
    if(r==0) mpfr_set_d(y,0,GMP_RNDN);
    
    if((mpfr_cmp(a,y)>=0) || (mpfr_cmp(y,b)>=0)) {
      if(verbosity>=4) {
	printf("Entering in a rescue case of Newton's algorithm\n");
	printMpfr(y);
      }
      
      // Since Newton go out of the interval, we make a step of binary search
      r = evaluateFaithfulWithCutOffFast(y, f, f_diff, x, zero_mpfr, prec);

      if((!mpfr_number_p(y)) && (r==1)) {
	fprintf(stderr,"Warning: Newton algorithm encountered numerical problems\n");
	res = mpfr_to_PARI(x);
	free_memory(iterator);
	mpfr_clear(x);
	mpfr_clear(y);
	mpfr_clear(zero_mpfr);
	return res;
      }
      if(r==0) mpfr_set_d(y,0,GMP_RNDN);
    
      if(sgnfa==mpfr_sgn(y)) {
	mpfr_add(y,x,b,GMP_RNDN);
	mpfr_div_2ui(y,y,1,GMP_RNDN);
      }
      else {
	mpfr_add(y,a,x,GMP_RNDN);
	mpfr_div_2ui(y,y,1,GMP_RNDN);
      }
    }
  
    if(n!=0) {if(nbr_iter==n) test=0;}
    else {
      if(mpfr_equal_p(x,y)) test=0;
      else {
	if((!mpfr_zero_p(x)) && (!mpfr_zero_p(y))) {
	  if(mpfr_get_exp(x)!=mpfr_get_exp(y)) { n_expo++; estim_prec=1; }
	  else estim_prec=estim_prec*2;
	}
	
	if((n_expo>5000) || (estim_prec>prec)) test=0;
      }
    }

    nbr_iter++;
    mpfr_set(x,y,GMP_RNDN);
  }

  nbr_iter--;

  if(n_expo>5000) {
    mpfr_set(y,x,GMP_RNDN);
    mpfr_set_d(x,0.,GMP_RNDN);
    r = evaluateFaithfulWithCutOffFast(x, f, f_diff, x, zero_mpfr, prec);
    if(mpfr_zero_p(x) || (r==0)) mpfr_set_d(x,0.,GMP_RNDN);
    else mpfr_set(x,y,GMP_RNDN);
  }

  if(verbosity>=3) {
    printf("Newton made %d iterations\n",nbr_iter);
  }
  
  if(verbosity>=4) {
    printf("Newton's result :");
    printMpfr(x); evaluateFaithful(y,f,x,prec); printMpfr(y);
  }

  res = mpfr_to_PARI(x);

  free_memory(iterator);
  mpfr_clear(x);
  mpfr_clear(y);
  mpfr_clear(zero_mpfr);
  return res;
}

// Just a wrapper
GEN newton(node *f, node *f_diff, mpfr_t a, mpfr_t b, int sgnfa, mp_prec_t prec) {
  return findZero(f, f_diff, a, b, sgnfa, NULL, 0, prec);
}


// Returns a PARI array containing the zeros of tree on [a;b]
// deg+1 indicates the number of zeros which we are expecting.
GEN quickFindZeros(node *tree, node *diff_tree, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec, int *crash_report) {
  GEN res;
  long int n = 50*(deg+2);
  long int i=0;
  mpfr_t h, x1, x2, y1, y2, zero_mpfr;
  
  mpfr_init2(h,prec);
  mpfr_init2(y1,prec);
  mpfr_init2(y2,prec);
  mpfr_init2(x1,prec);
  mpfr_init2(x2,prec);
  mpfr_init2(zero_mpfr,prec);

  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  res = cgetg(deg+3, t_COL);

  mpfr_sub(h,b,a,GMP_RNDD);
  mpfr_div_si(h,h,n,GMP_RNDD);

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,a,h,GMP_RNDN);

  evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, x1, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  while(mpfr_lessequal_p(x2,b)) {
    if (mpfr_sgn(y1) != mpfr_sgn(y2)) {
      i++;
      if(i>deg+2)
	printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
      else res[i] = (long)(newton(tree, diff_tree, x1, x2, mpfr_sgn(y1), prec));       
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_add(x2,x2,h,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  }
  
  if (i<deg) {
    printMessage(1,"Warning: the function fails to oscillate enough.\n");
    *crash_report = -1;
  }
  else {
    if (i==deg) { 
      res[deg+1] = (long)(mpfr_to_PARI(a));
      res[deg+2] = (long)(mpfr_to_PARI(b));
      res = sort(res);
    }
    else {
      if (i==deg +1) {
	evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, a, zero_mpfr, prec);
	evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, b, zero_mpfr, prec);
	if (mpfr_cmpabs(y1,y2)>0) res[deg+2] = (long)(mpfr_to_PARI(a));
	else res[deg+2] = (long)(mpfr_to_PARI(b));
	res = sort(res);
      }
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(zero_mpfr);
  return res;
}




// This function finds the local extrema of a the error function poly*w-f.
// It uses the derivative and the second derivative of these functions to
// search the zeros of (poly*w-f)' by Newton's algorithm
// It expects to find at least freeDegrees+1 alternates extrema and
// returns it as a result. An intial estimation of these points is given
// in the vector x.
// Moreover, the quality of the approximation
// (defined by abs(err_max)/abs(err_min) - 1 where err_min and err_max 
// denote the minimal and maximal extrema in absolute value) is stored
// in computedQuality and the infinite norm is stored in infiniteNorm
// if these parameters are non NULL.
GEN qualityOfError(mpfr_t computedQuality, mpfr_t infiniteNorm, GEN x,
		   node *poly, node *poly_diff, node *poly_diff2,
		   node *f, node *f_diff, node *f_diff2,
		   node *w, node *w_diff, node *w_diff2,
		   int freeDegrees, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  node *error;
  node *temp1;
  node *error_diff;
  node *error_diff2;
  int n, test, i, r;
  int case1, case2, case2b, case3;
  int *s;
  mpfr_t *y;
  mpfr_t var_mpfr, dummy_mpfr, dummy_mpfr2, max_val, min_val, zero_mpfr;
  GEN z;
  
  int crash_report=0;
  
  mpfr_init2(var_mpfr, prec);
  mpfr_init2(zero_mpfr, 53);
  mpfr_init2(max_val, prec);
  mpfr_init2(min_val, prec);
  mpfr_init2(dummy_mpfr, 5);
  mpfr_init2(dummy_mpfr2, 53);

  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);
  
  // Construction of the trees corresponding to (poly*w-f)' and (poly*w-f)''
  if(verbosity>=3) printf("Constructing the error tree... \n");

  error = safeMalloc(sizeof(node));
  error->nodeType = SUB;
  temp1 = safeMalloc(sizeof(node));
  temp1->nodeType = MUL;
  temp1->child1 = copyTree(poly);
  temp1->child2 = copyTree(w);
  error->child1 = temp1;
  error->child2 = copyTree(f);
  if(verbosity>=3) printf("Simplifying the error tree... \n");
  temp1 = simplifyTreeErrorfree(error);
  free_memory(error);
  error = temp1;

  if(verbosity>=3) printf("Constructing the error' tree... \n");
  error_diff = differentiate(error);
  if(verbosity>=3) printf("Simplifying the error' tree... \n");
  temp1 = simplifyTreeErrorfree(error_diff);
  free_memory(error_diff);
  error_diff = temp1;

  if(verbosity>=3) printf("Constructing the error'' trees... \n");
  error_diff2 = differentiate(error_diff);
  if(verbosity>=3) printf("Simplifying the error'' tree... \n");
  temp1 = simplifyTreeErrorfree(error_diff2);
  free_memory(error_diff2);
  error_diff2 = temp1;
  
  if(verbosity>=3) printf("Computing the yi... \n");
  // If x = [x1 ... xn], we construct [y0 y1 ... yn] by
  // y0 = (a+x1)/2, yn = (xn+b)/2 and yi = (xi + x(i+1))/2
  n = itos((GEN)(matsize(x)[1]));
  y = (mpfr_t *)safeMalloc((n+1)*sizeof(mpfr_t));
  mpfr_init2(y[0], prec);
  PARI_to_mpfr(var_mpfr, (GEN)(x[1]), GMP_RNDN);
  mpfr_set(y[0], a, GMP_RNDN);
  mpfr_add(y[0], var_mpfr, y[0], GMP_RNDN);
  mpfr_div_2ui(y[0], y[0], 1, GMP_RNDN);
  
  for(i=1; i<n; i++) {
    mpfr_init2(y[i], prec);
    PARI_to_mpfr(var_mpfr, (GEN)(x[i]), GMP_RNDN);
    PARI_to_mpfr(y[i], (GEN)(x[i+1]), GMP_RNDN);
    mpfr_add(y[i], var_mpfr, y[i], GMP_RNDN);
    mpfr_div_2ui(y[i], y[i], 1, GMP_RNDN);
  }

  mpfr_init2(y[n], prec);
  PARI_to_mpfr(var_mpfr, (GEN)(x[n]), GMP_RNDN);
  mpfr_set(y[n], b, GMP_RNDN);
  mpfr_add(y[n], var_mpfr, y[n], GMP_RNDN);
  mpfr_div_2ui(y[n], y[n], 1, GMP_RNDN);

  if(verbosity>=3) {
    printf("The computed yi are : ");
    for(i=0;i<=n;i++) {printMpfr(y[i]); printf(" ");}
    printf("\n");
  }
  

  // We call *case 1* the case where x1=a and xn=b
  // We call *case 2* the case where x1<>a and xn=b
  // and *case 2bis* the symetrical case
  // We call *case 3* the case where x1<>a and xn<>b


  if (mpfr_equal_p(y[0], a) &&  mpfr_equal_p(y[n],b)) {
    case1 = 1; case2 = 0; case2b = 0; case3 = 0;
  }
  else {
    if ((! mpfr_equal_p(y[0], a)) &&  mpfr_equal_p(y[n],b)) {
      case1 = 0; case2 = 1; case2b = 0; case3 = 0;
    }
    else {      
      if (mpfr_equal_p(y[0], a) &&  (! mpfr_equal_p(y[n],b))) {
	case1 = 0; case2 = 0; case2b = 1; case3 = 0;
      }
      else {
	case1 = 0; case2 = 0; case2b = 0; case3 = 1;
      }
    }
  }

  if(verbosity>=3) {
    printf("We are in case : ");
    if(case1) printf("1\n");
    if(case2) printf("2\n");
    if(case2b) printf("2bis\n");
    if(case3) printf("3\n");
  }



  // If one of error_diff(y0) .... error_diff(yn) is a real NaN
  // (i.e. if evaluateFaithfulWithCutOffFast returns 1 and store a NaN)
  // this leads to numerical problems -> we use quikFindZeros

  // If sgn(error_diff(yi))*sgn(error_diff(y(i+1))) > 0 for some i=1..n-2
  // If we are in case 2 and sgn(error_diff(y0))*sgn(error_diff(y1)) > 0
  // If we are in case 2bis and sgn(error_diff(y(n-1)))*sgn(error_diff(yn)) > 0
  // If we are in case 3 and one of this two last condition is not fulfilled
  // this means the hypothesis (xi ~ zeros of error_diff) is false -> quickFindZeros

  // If we are in case 1 : if sgn(error_diff(y0))*sgn(error_diff(y1)) > 0 (the most probable)
  // we have a problem if error(y0) is a real NaN or if sgn(error(y0))*sgn(error_diff(y0))>0
  // if sgn(error_diff(y(n-1)))*sgn(error_diff(yn)) > 0 (the most probable)
  // we have a problem if error(yn) is a real NaN or if sgn(error(yn))*sgn(error_diff(yn))<0

  // If we are in case 2 if sgn(error_diff(y(n-1)))*sgn(error_diff(yn)) > 0 (the most probable)
  // we have a problem if error(yn) is a real NaN or if sgn(error(yn))*sgn(error_diff(yn))<0
  
  // If we are in case 2bis, if sgn(error_diff(y0))*sgn(error_diff(y1)) > 0 (the most probable)
  // we have a problem if error(y0) is a real NaN or if sgn(error(y0))*sgn(error_diff(y0))>0
  

  s = (int *)safeMalloc((n+1)*sizeof(int));
  test = 1;
  i = 0;
  while(test && (i<=n)) {
    r = evaluateFaithfulWithCutOffFast(dummy_mpfr, error_diff, error_diff2, y[i], zero_mpfr, prec);
    if((!mpfr_number_p(dummy_mpfr)) && (r==1)) test=0;
    else { 
      if(r==0) s[i]=0;
      else s[i] = mpfr_sgn(dummy_mpfr);
    }
    i++;
  }

  if(verbosity>=3) {
    if(test) {
      printf("The computed signs are : ");
      for(i=0;i<=n;i++) printf("%d  ",s[i]);
      printf("\n");
    }
    else printf("Test is false because signs could not be evaluated\n");
  }
  

  if(test) {
    i = 1;
    while(test && (i<=n-2)) {
      if(s[i]*s[i+1] > 0) test=0;
      i++;
    }
  }
  if(test && case2 && (s[0]*s[1]>0)) test=0;
  if(test && case2b && (s[n-1]*s[n]>0)) test=0;
  if(test && case3 && ((s[0]*s[1]>0) || (s[n-1]*s[n]>0))) test=0;

  if(test && (case1 || case2b) && (s[0]*s[1]>0)) {
    r = evaluateFaithfulWithCutOffFast(dummy_mpfr, error, error_diff, y[0], zero_mpfr, prec);
    if((!mpfr_number_p(dummy_mpfr)) && (r==1)) test=0;
    else { 
      if((r!=0) && (mpfr_sgn(dummy_mpfr)*s[0] > 0)) test=0;
    }
  }

  if(test && (case1 || case2) && (s[n-1]*s[n]>0)) {
    r = evaluateFaithfulWithCutOffFast(dummy_mpfr, error, error_diff, y[n], zero_mpfr, prec);
    if((!mpfr_number_p(dummy_mpfr)) && (r==1)) test=0;
    else { 
      if((r!=0) && (mpfr_sgn(dummy_mpfr)*s[n] < 0)) test=0;
    }
  }

  if(test) {
    z = cgetg(n+1, t_COL);
    if((case1 || case2b) && (s[0]*s[1]<=0)) z[1] = (long)findZero(error_diff, error_diff2,y[0],y[1],s[0],NULL,2,prec);
    if((case1 || case2b) && (s[0]*s[1]>0)) z[1] = (long)mpfr_to_PARI(a);
    if(case2 || case3) z[1] = (long)findZero(error_diff, error_diff2, y[0], y[1], s[0], (GEN)(x[1]), 2, prec);
    
    for(i=1;i<=n-2;i++) z[i+1] = (long)findZero(error_diff, error_diff2, y[i], y[i+1], s[i], (GEN)(x[i+1]), 2, prec);

    if((case1 || case2) && (s[n-1]*s[n]<=0)) z[n] = (long)findZero(error_diff, error_diff2, y[n-1], y[n], s[n-1], NULL, 2, prec);
    if((case1 || case2) && (s[n-1]*s[n]>0)) z[n] = (long)mpfr_to_PARI(b);
    if(case2b || case3) z[n] = (long)findZero(error_diff, error_diff2, y[n-1], y[n], s[n-1], (GEN)(x[n]), 2, prec);
  }
  else {
    printMessage(1,"Warning in Remez: a slower algorithm is used for this step\n");
    z = quickFindZeros(error_diff, error_diff2, freeDegrees-1, a, b, prec, &crash_report);
    if(crash_report==-1) z=x;
  }

  if(verbosity>=3) {
    printf("The new points are : "); output(z);
  }

  // Test the quality of the current error

  mpfr_set_d(max_val, 0., GMP_RNDN);
  mpfr_set_inf(min_val, 1);

  if((computedQuality!=NULL) || (infiniteNorm != NULL)) {
    for(i=1;i<=n;i++) {
      PARI_to_mpfr(var_mpfr, (GEN)z[i], GMP_RNDN);
      
      r = evaluateFaithfulWithCutOffFast(var_mpfr, error, error_diff, var_mpfr, zero_mpfr, prec);
      if(r==0) mpfr_set_d(var_mpfr, 0., GMP_RNDN);
      
      mpfr_abs(var_mpfr, var_mpfr, GMP_RNDN);
      if(mpfr_cmp(var_mpfr, max_val) > 0) mpfr_set(max_val, var_mpfr, GMP_RNDU);
      if(mpfr_cmp(var_mpfr, min_val) < 0) mpfr_set(min_val, var_mpfr, GMP_RNDD);
    }

    mpfr_div(var_mpfr, max_val, min_val, GMP_RNDU);
    mpfr_sub_ui(var_mpfr, var_mpfr, 1, GMP_RNDU);
  }

  if(computedQuality!=NULL) mpfr_set(computedQuality, var_mpfr, GMP_RNDU);
  if(infiniteNorm!=NULL) mpfr_set(infiniteNorm, max_val, GMP_RNDU);

  if(verbosity>=3) {
    mpfr_set(dummy_mpfr2,max_val,GMP_RNDN);
    printf("Current norm: "); printValue(&dummy_mpfr2, 5) ;
    mpfr_set(dummy_mpfr2,var_mpfr,GMP_RNDN);
    printf(" (1 +/- "); printValue(&dummy_mpfr2, 5);
    printf(")\n");
  }


  free_memory(error);
  free_memory(error_diff);
  free_memory(error_diff2);
  mpfr_clear(var_mpfr);
  mpfr_clear(zero_mpfr);
  mpfr_clear(dummy_mpfr);
  mpfr_clear(dummy_mpfr2);
  mpfr_clear(max_val);
  mpfr_clear(min_val);
  free(s);

  for(i=0;i<=n;i++)  mpfr_clear(y[i]);
  free(y);
  
  if(crash_report==-1) return NULL;
  else return z;
}

node *remezAux(node *f, node *w, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec, mpfr_t quality) {
  ulong ltop=avma;
  int freeDegrees = lengthChain(monomials);
  int i,j, r, count;
  GEN x, M, temp;
  mpfr_t zero_mpfr, var1, var2, var3, var4, computedQuality, infiniteNorm;
  mpfr_t *ptr;
  node *temp_tree;
  node *temp_tree2;
  node *temp_tree3;
  node *poly;
  node *poly_diff;
  node *poly_diff2;
  node *f_diff;
  node *f_diff2;
  node *w_diff;
  node *w_diff2;
  chain *curr;

  if(verbosity>=3) {
    printf("Entering in Remez function...\n");
    printf("Required quality :"); printMpfr(quality);
  }

  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);
  mpfr_init2(var3, prec);
  mpfr_init2(var4, prec);

  mpfr_init2(zero_mpfr, 53);
  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_init2(computedQuality, mpfr_get_prec(quality));
  mpfr_set_d(computedQuality, 1., GMP_RNDN);
  mpfr_init2(infiniteNorm, 53);

  if(verbosity>=3) {
    printf("Differentiating functions...\n");
  }

  poly = NULL;
  f_diff = differentiate(f);
  f_diff2 = differentiate(f_diff);
  w_diff = differentiate(w);
  w_diff2 = differentiate(w_diff);

  count = 0;

  // Definition of the array x of the n+2 Chebychev points

  if(verbosity>=3) {
    printf("Computing an initial points set...\n");
  }

  /*************************************************************/
  x = cgetg(freeDegrees + 2, t_COL);
  mpfr_const_pi(var1, GMP_RNDN);
  mpfr_div_si(var1, var1, (long)freeDegrees, GMP_RNDN); // var1 = Pi/freeDegrees
  mpfr_sub(var2, a, b, GMP_RNDN);
  mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (a-b)/2
  mpfr_add(var3, a, b, GMP_RNDN);
  mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (a+b)/2

  for (i=1 ; i <= freeDegrees+1 ; i++) {
    mpfr_mul_si(var4, var1, i-1, GMP_RNDN);
    mpfr_cos(var4, var4, GMP_RNDN);
    mpfr_fma(var4, var4, var2, var3, GMP_RNDN); // var4 = [cos((i-1)*Pi/freeDegrees)]*(a-b)/2 + (a+b)/2
    x[i] = (long)(mpfr_to_PARI(var4));
  }
  /*************************************************************/


  /*************************************************************/
  /*                 Evenly distributed points                 */
  //x = cgetg(freeDegrees + 2, t_COL);
  //mpfr_sub(var1, b, a, GMP_RNDN);
  //mpfr_div_si(var1, var1, (long)(freeDegrees), GMP_RNDN); // var1 = (b-a)/freeDegrees
  //
  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(var1, var1, i-1, GMP_RNDN);
  //  mpfr_add(var1, var1, a, GMP_RNDN);
  //  x[i] = (long)(mpfr_to_PARI(var1));
  //}
  /*************************************************************/


  /*************************************************************/
  /*                  Alternative Cheb points                  */
  //x = cgetg(freeDegrees + 2, t_COL);
  //mpfr_const_pi(var1, GMP_RNDN);
  //mpfr_div_si(var1, var1, 2*((long)freeDegrees+1), GMP_RNDN); // var1 = Pi/(2*freeDegrees+2)
  //mpfr_sub(var2, a, b, GMP_RNDN);
  //mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (a-b)/2
  //mpfr_add(var3, a, b, GMP_RNDN);
  //mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (a+b)/2

  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(var4, var1, 2*i-1, GMP_RNDN);
  //  mpfr_cos(var4, var4, GMP_RNDN);
  //  mpfr_fma(var4, var4, var2, var3, GMP_RNDN); // var4=[cos((2i-1)*Pi/(2freeDegrees+2))]*(a-b)/2 + (a+b)/2
  //  x[i] = (long)(mpfr_to_PARI(var4));
  //}
  /*************************************************************/

  if(verbosity>=4) {
    printf("Computed points set :"); output(x);
  }
  
  while((mpfr_cmp(computedQuality, quality)>0) && (count<1000)) {
    free_memory(poly);

    // Definition of the matrix M of Remez algorithm
    if(verbosity>=3) {
      printf("Step %d\n",count);
      printf("Computing the matrix...\n");
    }

    M = cgetg(freeDegrees+2, t_MAT);
    temp = cgetg(freeDegrees+2, t_COL);
    curr = monomials;
    for (j=1 ; j <= freeDegrees ; j++) {
      temp_tree = safeMalloc(sizeof(node));
      temp_tree->nodeType = VARIABLE;
      temp_tree2 = safeMalloc(sizeof(node));
      temp_tree2->nodeType = CONSTANT;
      ptr = safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*ptr, prec);
      mpfr_set_si(*ptr, (long) (*((int *)(curr->value))), GMP_RNDN);
      temp_tree2->value = ptr;

      temp_tree3 = safeMalloc(sizeof(node));
      temp_tree3->nodeType = POW;
      temp_tree3->child1 = temp_tree;
      temp_tree3->child2 = temp_tree2;

      temp_tree = safeMalloc(sizeof(node));
      temp_tree->nodeType = MUL;
      temp_tree->child1 = temp_tree3;
      temp_tree->child2 = copyTree(w);

      temp_tree2 = simplifyTreeErrorfree(temp_tree);
      free_memory(temp_tree);
      temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
      
      for (i=1 ; i <= freeDegrees+1 ; i++) {
	PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);

	r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, var1, zero_mpfr, prec);
	if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);

	temp[i] = (long)(mpfr_to_PARI(var1));
      }
      M[j] = lcopy(temp);
      free_memory(temp_tree);
      curr = curr->next;
    }

    for (i=1 ; i <= freeDegrees+1 ; i++) {
      temp[i] = (long)stoi((i % 2)*2-1);  // temp = [1, -1, 1, -1 ... ]~
    }
    M[freeDegrees+1] = lcopy(temp);

    if(verbosity>=5) {
      printf("The computed matrix is "); output(M);
    }
    
    // Note that a simple optimization would be to precompute the w(x[i])
    // instead of computing it (freeDegrees+1) times
    
    
    // Determination of the polynomial corresponding to M and x
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);

      r = evaluateFaithfulWithCutOffFast(var1, f, NULL, var1, zero_mpfr, prec); // var1=f(x[i])
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);

      temp[i] = (long)(mpfr_to_PARI(var1));
    }
    temp = gauss(M,temp);
    poly = constructPolynomial(temp, monomials, prec);

    if(verbosity>=4) {
      printf("The computed polynomial is "); printTree(poly); printf("\n");
    }

    // Computing the useful derivatives of functions
    if(verbosity>=3) {
      printf("Differentiating the computed polynomial...\n");
    }
    
    poly_diff = differentiate(poly);
    poly_diff2 = differentiate(poly_diff);
    
    temp_tree = horner(poly);
    free_memory(poly);
    poly = temp_tree;
    
    temp_tree = horner(poly_diff);
    free_memory(poly_diff);
    poly_diff = temp_tree;
    
    temp_tree = horner(poly_diff2);
    free_memory(poly_diff2);
    poly_diff2 = temp_tree;
    
    if(verbosity>=3) {
      printf("Searching extrema of the error function...\n");
    }
    
    // Find extremas and tests the quality of the current approximation
    x = qualityOfError(computedQuality, infiniteNorm, x,
		       poly, poly_diff, poly_diff2,
		       f, f_diff, f_diff2,
		       w, w_diff, w_diff2,
		       freeDegrees, a, b, prec);
    
    if(x==NULL) {
      free_memory(poly_diff);
      free_memory(poly_diff2);
      mpfr_clear(zero_mpfr);
      mpfr_clear(var1);
      mpfr_clear(var2);
      mpfr_clear(var3);
      mpfr_clear(var4);
      free_memory(f_diff);
      free_memory(f_diff2);
      free_memory(w_diff);
      free_memory(w_diff2);
      mpfr_clear(computedQuality);
      mpfr_clear(infiniteNorm);
      avma=ltop;
      recoverFromError();
    }
      
    if(verbosity>=4) {    
      printf("New points set: "); output(x);
    }
    if(verbosity>=3) {
      printf("Current quality: "); printMpfr(computedQuality);
    }

    count++;

    free_memory(poly_diff);
    free_memory(poly_diff2);
  }
  
  if(verbosity>=2) {
      printf("Remez finished after %d steps\n",count);
      printf("The computed infnorm is "); printValue(&infiniteNorm, 53) ; printf("\n");
      printf("The polynomial is optimal within a factor 1 +/- "); printValue(&computedQuality, 5);
      printf("\n");
    }

  mpfr_clear(zero_mpfr);
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(var3);
  mpfr_clear(var4);
  free_memory(f_diff);
  free_memory(f_diff2);
  free_memory(w_diff);
  free_memory(w_diff2);

  avma=ltop;
  if (mpfr_cmp(computedQuality, quality)>0) {
    fprintf(stderr, "Error in Remez: the algorithm does not converge.\n");
    mpfr_clear(computedQuality);
    recoverFromError();
  }

  mpfr_clear(computedQuality);
  mpfr_clear(infiniteNorm);
  return poly;
}


// Suppose that the list monom is sorted.
// Tests whether monom contains two equal ints.
int testMonomials(chain *monom) {
  chain *curr;

  if (monom == NULL) return 1;
  
  curr = monom;
  while (curr->next != NULL) {
    if (*((int *) (curr->value)) == *((int *) (curr->next->value))) return 0;
    curr = curr->next;
  }

  return 1;
}

void *copyInt(void *n) {
  int *n2;
  n2 = safeMalloc(sizeof(int));
  *n2 = *((int *)n);
  return n2;
}
  
node *remez(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t quality;
  node *res;
  chain *monomials2;

  mpfr_init2(quality, 53);
  mpfr_set_d(quality, 0.00001, GMP_RNDN);
  
  monomials2 = copyChain(monomials, &copyInt);

  sortChain(monomials2,cmpIntPtr);

  if (!testMonomials(monomials2)) {
    fprintf(stderr,"Error: monomial degree is given twice in argument to Remez algorithm.\n");
    recoverFromError();
  }

  res = remezAux(func, weight, monomials2, a, b, prec, quality);

  freeChain(monomials2, freeIntPtr);
  mpfr_clear(quality);
  return res;
}


// returns 1 if deg is sufficient to approximate the function to eps
// returns -1 if deg is not sufficient
// 0 if we cannot determine.
int whichPoly(int deg, node *f, node *w, mpfr_t a, mpfr_t b, mpfr_t eps) {
  ulong ltop=avma;
  mp_prec_t prec = defaultprecision;
  int freeDegrees = deg+1;
  int i,j,r, res;
  int *var;
  GEN x, M, temp;
  mpfr_t zero_mpfr, var1, var2, var3, var4, computedQuality, infiniteNorm;
  mpfr_t *ptr;
  node *temp_tree;
  node *temp_tree2;
  node *temp_tree3;
  node *poly;
  node *poly_diff;
  node *poly_diff2;
  node *f_diff;
  node *f_diff2;
  node *w_diff;
  node *w_diff2;
  chain *monomials;
  chain *curr;

  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);
  mpfr_init2(var3, prec);
  mpfr_init2(var4, prec);

  mpfr_init2(zero_mpfr, 53);
  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_init2(computedQuality, defaultprecision);
  mpfr_set_d(computedQuality, 1., GMP_RNDN);
  mpfr_init2(infiniteNorm, 53);

  f_diff = differentiate(f);
  f_diff2 = differentiate(f_diff);
  w_diff = differentiate(w);
  w_diff2 = differentiate(w_diff);

  monomials=NULL;
  for(i=0;i<=deg;i++) {
    var = safeMalloc(sizeof(int));
    *var = i;
    monomials = addElement(monomials, (void *)var);
  }

  // Definition of the array x of the n+2 Chebychev points
  x = cgetg(freeDegrees + 2, t_COL);
  mpfr_const_pi(var1, GMP_RNDN);
  mpfr_div_si(var1, var1, (long)freeDegrees, GMP_RNDN); // var1 = Pi/freeDegrees
  mpfr_sub(var2, a, b, GMP_RNDN);
  mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (a-b)/2
  mpfr_add(var3, a, b, GMP_RNDN);
  mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (a+b)/2

  for (i=1 ; i <= freeDegrees+1 ; i++) {
    mpfr_mul_si(var4, var1, i-1, GMP_RNDN);
    mpfr_cos(var4, var4, GMP_RNDN);
    mpfr_fma(var4, var4, var2, var3, GMP_RNDN); // var4 = [cos((i-1)*Pi/freeDegrees)]*(a-b)/2 + (a+b)/2
    x[i] = (long)(mpfr_to_PARI(var4));
  }
  /*************************************************************/

  // Definition of the matrix M of Remez algorithm
  
  M = cgetg(freeDegrees+2, t_MAT);
  temp = cgetg(freeDegrees+2, t_COL);
  curr = monomials;
  for (j=1 ; j <= freeDegrees ; j++) {
    temp_tree = safeMalloc(sizeof(node));
    temp_tree->nodeType = VARIABLE;
    temp_tree2 = safeMalloc(sizeof(node));
    temp_tree2->nodeType = CONSTANT;
    ptr = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*ptr, prec);
    mpfr_set_si(*ptr, (long) (*((int *)(curr->value))), GMP_RNDN);
    temp_tree2->value = ptr;
    
    temp_tree3 = safeMalloc(sizeof(node));
    temp_tree3->nodeType = POW;
    temp_tree3->child1 = temp_tree;
    temp_tree3->child2 = temp_tree2;
    
    temp_tree = safeMalloc(sizeof(node));
    temp_tree->nodeType = MUL;
    temp_tree->child1 = temp_tree3;
    temp_tree->child2 = copyTree(w);
    
    temp_tree2 = simplifyTreeErrorfree(temp_tree);
    free_memory(temp_tree);
    temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
    
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);
      
      r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, var1, zero_mpfr, prec);
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
      
      temp[i] = (long)(mpfr_to_PARI(var1));
    }
    M[j] = lcopy(temp);
    free_memory(temp_tree);
    curr = curr->next;
  }

  for (i=1 ; i <= freeDegrees+1 ; i++) {
    temp[i] = (long)stoi((i % 2)*2-1);  // temp = [1, -1, 1, -1 ... ]~
  }
  M[freeDegrees+1] = lcopy(temp);

  // Determination of the polynomial corresponding to M and x
  for (i=1 ; i <= freeDegrees+1 ; i++) {
    PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);
    
    r = evaluateFaithfulWithCutOffFast(var1, f, NULL, var1, zero_mpfr, prec); // var1=f(x[i])
    if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
    
    temp[i] = (long)(mpfr_to_PARI(var1));
  }
  temp = gauss(M,temp);
  poly = constructPolynomial(temp, monomials, prec);

  // Computing the useful derivatives of functions
    
  poly_diff = differentiate(poly);
  poly_diff2 = differentiate(poly_diff);
  
  temp_tree = horner(poly);
  free_memory(poly);
  poly = temp_tree;
  
  temp_tree = horner(poly_diff);
  free_memory(poly_diff);
  poly_diff = temp_tree;
  
  temp_tree = horner(poly_diff2);
  free_memory(poly_diff2);
  poly_diff2 = temp_tree;
  
  // Find extremas and tests the quality of the current approximation
  x = qualityOfError(computedQuality, infiniteNorm, x,
		     poly, poly_diff, poly_diff2,
		     f, f_diff, f_diff2,
		     w, w_diff, w_diff2,
		     freeDegrees, a, b, prec);
  
  if(mpfr_cmp(eps,infiniteNorm) >= 0) res=1;
  else {
    mpfr_add_ui(computedQuality, computedQuality, 1, GMP_RNDU);
    mpfr_div(infiniteNorm, infiniteNorm, computedQuality, GMP_RNDD);
    if(mpfr_cmp(eps,infiniteNorm) < 0) res=-1;
    else res=0;
  }

  freeChain(monomials, freeIntPtr);

  if(x==NULL) res=0;
  
  free_memory(poly);
  free_memory(poly_diff);
  free_memory(poly_diff2);
  mpfr_clear(zero_mpfr);
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(var3);
  mpfr_clear(var4);
  free_memory(f_diff);
  free_memory(f_diff2);
  free_memory(w_diff);
  free_memory(w_diff2);

  avma=ltop;

  mpfr_clear(computedQuality);
  mpfr_clear(infiniteNorm);

  return res;
}

rangetype guessDegree(node *func, node *weight, mpfr_t a, mpfr_t b, mpfr_t eps) {
  int n_min=1;
  int n_max=10;
  int res=-1;
  int test=1;
  rangetype range;
  mpfr_t *u;
  mpfr_t *v;
  int old_verbosity = verbosity;
  verbosity = 0;
  int number_points = defaultpoints;
  defaultpoints = 5;

  while(res==-1 && (n_max < 100)) {
    res = whichPoly(n_max, func, weight, a, b, eps);
    if(res==-1) {
      n_min=n_max;
      n_max = n_max*2;
    }
    else {
      if(res==0) {
	n_max=n_max*2;
      }
    }
  }
  
  // This case shouldn't happen...
  if (n_max >=100) {
    fprintf(stderr, "Warning in guessdegree: the result may be not trustable\n");
    res = -1;
    while(res<0 && (n_min <= 100)) {
      n_min++;
      res = whichPoly(n_min,func,weight,a,b,eps);
    }

    u = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    v = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*u,defaultprecision);
    mpfr_init2(*v,defaultprecision);
    if (res<0) mpfr_set_inf(*u,1);
    else mpfr_set_ui(*u, n_min, GMP_RNDN);
    mpfr_set_inf(*v, 1);
    range.a = u;
    range.b = v;
    defaultpoints=number_points;
    verbosity = old_verbosity;
    return range;
  }
  // else...

  while(test && (n_max-n_min > 1)) {
    res = whichPoly((n_min+n_max)/2, func, weight, a, b, eps);
    if(res==1) n_max=(n_min+n_max)/2;
    else {
      if(res==-1) n_min=(n_min+n_max)/2;
      else test=0;
    }
  }

  if(test) n_min=n_max;
  else {
    res=0;
    n_min = (n_min+n_max)/2;
    n_max = n_min;
    while(res==0) {
      n_min--;
      res = whichPoly(n_min,func,weight,a,b,eps);
    }
    n_min = n_min + 1;
    res=0;
    while(res==0) {
      n_max++;
      res = whichPoly(n_max,func,weight,a,b,eps);
    }
  }
  
  u = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
  v = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*u,defaultprecision);
  mpfr_init2(*v,defaultprecision);
  mpfr_set_ui(*u, n_min, GMP_RNDN);
  mpfr_set_ui(*v, n_max, GMP_RNDN);
  range.a = u;
  range.b = v;
  defaultpoints=number_points;
  verbosity = old_verbosity;
  return range;
}



// temporary definition until fpminimax.c is updated
node* remezWithWeight(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  return (copyTree(func));
}
