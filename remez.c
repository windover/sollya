#include <gmp.h>
#include <mpfr.h>
#include "chain.h"
#include "general.h"
#include "infnorm.h"
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define coeff(i,j,n) ((i)-1)*(n)+(j)-1

void printMatrix(mpfr_t *M, int n) {
  int i,j;
  printf("[");
  for(i=1;i<=n;i++) {
    for(j=1;j<=n;j++) {
      printValue(&M[coeff(i,j,n)],53); if(j!=n)printf(", ");
    }
    if(i!=n) printf(";\n");
  }
  printf("]\n");
  return;
}

void system_solve(mpfr_t *res, mpfr_t *M, mpfr_t *b, int n, mp_prec_t prec) {
  chain *i_list=NULL;
  chain *j_list=NULL;
  chain *curri;
  chain *currj;
  int i0, j0, i, j, k;
  int *var;
  mpfr_t max,lambda;
  int *order_i = safeMalloc(n*sizeof(int));
  int *order_j = safeMalloc(n*sizeof(int));

  mpfr_init2(max, 53);
  mpfr_init2(lambda, prec);

  for(i=1;i<=n;i++) {
    var = safeMalloc(sizeof(int));
    *var = i;
    i_list = addElement(i_list, (void *)var);
  }
  for(j=1;j<=n;j++) {
    var = safeMalloc(sizeof(int));
    *var = j;
    j_list = addElement(j_list, (void *)var);
  }


  // Triangulation by Gaussian elimination
  for(k=1;k<=n;k++) {
    mpfr_set_d(max, 0., GMP_RNDN); //exact

    // In this part, we search for the bigger element of the matrix
    curri = i_list;
    while(curri!=NULL) {
      currj = j_list;
      while(currj!=NULL) {
	i = *(int *)(curri->value);
	j = *(int *)(currj->value);
	if(mpfr_cmpabs(M[coeff(i,j,n)],max)>0) {
	  i0 = i;
	  j0 = j;
	  mpfr_set(max, M[coeff(i,j,n)], GMP_RNDN);
	}
	currj = currj->next;
      }
      curri = curri->next;
    }
    
    i_list = removeInt(i_list, i0);
    j_list = removeInt(j_list, j0);

    order_i[k-1] = i0;
    order_j[k-1] = j0;

    // Here we update the matrix and the second member
    curri = i_list;
    while(curri!=NULL) {
      i = *(int *)(curri->value);
      mpfr_div(lambda, M[coeff(i,j0,n)], M[coeff(i0,j0,n)], GMP_RNDN);
      mpfr_neg(lambda, lambda, GMP_RNDN);

      currj = j_list;
      while(currj!=NULL) {
	j = *(int *)(currj->value);
	mpfr_fma(M[coeff(i,j,n)], lambda, M[coeff(i0,j,n)], M[coeff(i,j,n)], GMP_RNDN);
	currj = currj->next;
      }

      mpfr_fma(b[i-1], lambda, b[i0-1], b[i-1], GMP_RNDN);
      mpfr_set_d(M[coeff(i,j0,n)], 0., GMP_RNDN); // this line is not useful strictly speaking
      curri = curri->next;
    }
  }
  /*********************************************************************/


  // Resolution of the system itself
  for(i=1;i<=n;i++) {
    var = safeMalloc(sizeof(int));
    *var = i;
    i_list = addElement(i_list, (void *)var);
  }

  for(k=n;k>=1;k--) {
    i0 = order_i[k-1];
    j0 = order_j[k-1];
    mpfr_div(res[j0-1], b[i0-1], M[coeff(i0,j0,n)], GMP_RNDN);
    i_list = removeInt(i_list, i0);

    curri = i_list;
    while(curri!=NULL) {
      i = *(int *)(curri->value);
      mpfr_neg(M[coeff(i,j0,n)], M[coeff(i,j0,n)], GMP_RNDN);
      mpfr_fma(b[i-1], M[coeff(i,j0,n)], res[j0-1], b[i-1], GMP_RNDN);
      curri=curri->next;
    }
  }

  free(order_i);
  free(order_j);
  freeChain(i_list, freeIntPtr);
  freeChain(j_list, freeIntPtr);
  mpfr_clear(max);
  mpfr_clear(lambda);
  return;
}


// Bubble sort
void mpfr_sort(mpfr_t *vect, int n, mp_prec_t prec) {
  int i,j;
  mpfr_t var;

  mpfr_init2(var, prec);

  for(i=1;i<=n-1;i++) {
    for(j=n;j>=i+1;j--) {
      if(mpfr_cmp(vect[j-1], vect[j-2])<=0) {
	mpfr_set(var, vect[j-1], GMP_RNDN);
	mpfr_set(vect[j-1], vect[j-2], GMP_RNDN);
	mpfr_set(vect[j-2], var, GMP_RNDN);
      }
    }
  }

  mpfr_clear(var);
  return;
}



// Constructs the tree corresponding to p = sum(coeff(i) X^monomials[i])
// The array coeff is supposed to have at least so many elements as monomials
node *constructPolynomial(mpfr_t *coeff, chain *monomials, mp_prec_t prec) {
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
    mpfr_set(*ptr, coeff[i-1], GMP_RNDN);
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
void findZero(mpfr_t res, node *f, node *f_diff, mpfr_t a, mpfr_t b, int sgnfa, mpfr_t *x0, int n, mp_prec_t prec) {
  node *iterator;
  node *temp1;
  mpfr_t u, v, x, xNew, temp, y, zero_mpfr;
  mp_prec_t estim_prec;
  int r, nbr_iter,test, n_expo, sgnfu;

  sgnfu = sgnfa;

  mpfr_init2(x,prec);
  mpfr_init2(xNew,prec);
  mpfr_init2(y,prec);
  mpfr_init2(u, mpfr_get_prec(a));
  mpfr_init2(v, mpfr_get_prec(b));
  mpfr_init2(zero_mpfr,53);

  mpfr_set(u,a,GMP_RNDD);
  mpfr_set(v,b,GMP_RNDU); // both exacts

  if(x0!=NULL) mpfr_set(x,*x0,GMP_RNDN);
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
    r = evaluateFaithfulWithCutOffFast(xNew, iterator, NULL, x, zero_mpfr, prec);
    if(r==0) mpfr_set_d(xNew,0,GMP_RNDN);

    if( (mpfr_cmp(u,xNew)>=0) || (mpfr_cmp(xNew,v)>=0) || ((!mpfr_number_p(xNew)) && (r==1)) ) {
      if(verbosity>=4) {
	printf("Entering in a rescue case of Newton's algorithm\n");
	printMpfr(xNew);
      }
      
      // We do a step of binary search
      mpfr_add(xNew,u,v,GMP_RNDN);
      mpfr_div_2ui(xNew, xNew, 1, GMP_RNDN);
      r = evaluateFaithfulWithCutOffFast(y, f, f_diff, xNew, zero_mpfr, prec); // y=f[(u+v)/2]

      if((!mpfr_number_p(y)) && (r==1)) {
	fprintf(stderr,"/*Warning: Newton algorithm encountered numerical problems*/\n");
	if(verbosity>=2) {
	  printf("This function seems to be undefined at this point :"); printTree(f); printMpfr(xNew);
	}

	mpfr_set(res, xNew, GMP_RNDN);
	free_memory(iterator);
	mpfr_clear(x);
	mpfr_clear(xNew);
	mpfr_clear(y);
	mpfr_clear(u);
	mpfr_clear(v);
	mpfr_clear(zero_mpfr);
	return;
      }
      if ((r==0) || mpfr_zero_p(y)) { //y=f[u+v]/2] is an exact 0
	printMessage(4,"Information: an exact zero has been found by Newton's algorithm\n");

	mpfr_set(res, xNew, GMP_RNDN);
	free_memory(iterator);
	mpfr_clear(x);
	mpfr_clear(xNew);
	mpfr_clear(y);
	mpfr_clear(u);
	mpfr_clear(v);
	mpfr_clear(zero_mpfr);
	return;
      }
    
      // Now y is a non-zero real number
      if(mpfr_zero_p(y) || !mpfr_number_p(y))
	fprintf(stderr, "This message means that there is a bug in Newton's algorithm. Please report.\n");
      if(sgnfu==mpfr_sgn(y)) {
	mpfr_set(u,xNew,GMP_RNDD);
	sgnfu=mpfr_sgn(y);
      }
      else mpfr_set(v,xNew,GMP_RNDU);

      if (mpfr_equal_p(u,v)) {
	printMessage(4,"Information: in Newton's algorithm, the interval has been reducted to a single point.\n");

	mpfr_set(res, u, GMP_RNDN);
	free_memory(iterator);
	mpfr_clear(x);
	mpfr_clear(xNew);
	mpfr_clear(y);
	mpfr_clear(u);
	mpfr_clear(v);
	mpfr_clear(zero_mpfr);
	return;
      }

      mpfr_add(xNew,u,v,GMP_RNDN);
      mpfr_div_2ui(xNew,xNew,1,GMP_RNDN);
      if(mpfr_sgn(u)*mpfr_sgn(v)!=1) {
	// 0 lies in [u;v]
	if((!mpfr_zero_p(x)) && (!mpfr_zero_p(xNew))) n_expo+= mpfr_get_exp(x)-mpfr_get_exp(xNew);
	estim_prec=1;
      }
      else {
	n_expo = 0; // since 0 does not lie in [u;v], n_expo is useless
	mpfr_init2(temp,10);
	mpfr_sub(temp,v,u,GMP_RNDN);
	if(mpfr_cmp_abs(v,u)) estim_prec = mpfr_get_exp(temp) - mpfr_get_exp(u) - 1;
	else estim_prec = mpfr_get_exp(temp) - mpfr_get_exp(v) - 1;
	mpfr_clear(temp);
      }
    }
    else {
      if((!mpfr_zero_p(x)) && (!mpfr_zero_p(xNew))) {
	if(mpfr_get_exp(x)!=mpfr_get_exp(xNew)) { 
	  n_expo+= mpfr_get_exp(x)-mpfr_get_exp(xNew);
	  estim_prec=1;
	}
	else estim_prec=estim_prec*2;
      }
    }

    if ( ((n!=0) && (nbr_iter==n)) || mpfr_equal_p(x,xNew) || (n_expo>5000) || (estim_prec>prec)) test=0;


    nbr_iter++;
    mpfr_set(x,xNew,GMP_RNDN);
  }

  nbr_iter--;

  if(n_expo>5000) {
    mpfr_set(xNew,x,GMP_RNDN);
    mpfr_set_d(x,0.,GMP_RNDN);
    r = evaluateFaithfulWithCutOffFast(x, f, f_diff, x, zero_mpfr, prec);
    if(mpfr_zero_p(x) || (r==0)) mpfr_set_d(x,0.,GMP_RNDN);
    else mpfr_set(x,xNew,GMP_RNDN);
  }

  if(verbosity>=3) {
    printf("Newton made %d iterations\n",nbr_iter);
  }
  
  if(verbosity>=4) {
    printf("Newton's result :");
    printMpfr(x); evaluateFaithful(y,f,x,prec); printMpfr(y);
  }

  mpfr_set(res, x, GMP_RNDN);

  free_memory(iterator);
  mpfr_clear(x);
  mpfr_clear(xNew);
  mpfr_clear(y);
  mpfr_clear(u);
  mpfr_clear(v);
  mpfr_clear(zero_mpfr);
  return;
}

// Just a wrapper
void newton(mpfr_t res, node *f, node *f_diff, mpfr_t a, mpfr_t b, int sgnfa, mp_prec_t prec) {
  findZero(res, f, f_diff, a, b, sgnfa, NULL, 0, prec);
  return;
}


// Finds the zeros of a function on an interval.
chain *uncertifiedFindZeros(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec) {
  mpfr_t zero_mpfr, h, x1, x2, y1, y2;
  mpfr_t *temp;
  node *diff_tree;
  chain *result=NULL;

  mpfr_init2(h,prec);
  mpfr_init2(y1,prec);
  mpfr_init2(y2,prec);
  mpfr_init2(x1,prec);
  mpfr_init2(x2,prec);
  mpfr_init2(zero_mpfr,prec);

  diff_tree = differentiate(tree);

  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_sub(h,b,a,GMP_RNDD);
  mpfr_div_si(h,h,points,GMP_RNDD);

  mpfr_set(x1,b,GMP_RNDN);
  mpfr_sub(x2,b,h,GMP_RNDD);

  evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, x1, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  /* Little trick: if a=b, h=0, thus x1=x2=a=b */
  /* By doing this, we avoid entering the loop */
  if(mpfr_equal_p(a,b)) { mpfr_nextbelow(x2); }

  while(mpfr_greaterequal_p(x2,a)) {
    if((mpfr_sgn(y1)==0) || (mpfr_sgn(y2)==0) || (mpfr_sgn(y1) != mpfr_sgn(y2))) {
      if (mpfr_sgn(y1)==0) {
	  temp = safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*temp, prec);
	  mpfr_set(*temp, x1, GMP_RNDN);
	  result = addElement(result, temp);
      }
      else {
	if (mpfr_sgn(y2)!=0) {
	  temp = safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*temp, prec);
	  newton(*temp, tree, diff_tree, x2, x1, mpfr_sgn(y2), prec);
	  result = addElement(result, temp);
	}
      }
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_sub(x2,x2,h,GMP_RNDD);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  }

  if(! mpfr_equal_p(x1,a)) {
    mpfr_set(x2,a,GMP_RNDU);
    evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
    if (mpfr_sgn(y1)==0) {
      temp = safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*temp, prec);
      mpfr_set(*temp, x1, GMP_RNDN);
      result = addElement(result, temp);
    }
    if (mpfr_sgn(y2)==0) {
      temp = safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*temp, prec);
      mpfr_set(*temp, x2, GMP_RNDN);
      result = addElement(result, temp);
    }
    if( (mpfr_sgn(y1)!=0) && (mpfr_sgn(y2)!=0) && (mpfr_sgn(y1) != mpfr_sgn(y2)) ) {
      temp = safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*temp, prec);
      newton(*temp, tree, diff_tree, x2, x1, mpfr_sgn(y2), prec);
      result = addElement(result, temp);
    }
  }
  else { // x1=a
    if (mpfr_sgn(y1)==0) {
      temp = safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*temp, prec);
      mpfr_set(*temp, x1, GMP_RNDN);
      result = addElement(result, temp);
    }
  }
  mpfr_clear(h);
  mpfr_clear(y1);
  mpfr_clear(y2);
  mpfr_clear(x1);
  mpfr_clear(x2);
  mpfr_clear(zero_mpfr);
  
  return result;
}


// Returns a PARI array containing the zeros of tree on [a;b]
// deg+1 indicates the number of zeros which we are expecting.
void quickFindZeros(mpfr_t *res, node *tree, node *diff_tree, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec, int *crash_report) {
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

  mpfr_sub(h,b,a,GMP_RNDD);
  mpfr_div_si(h,h,n,GMP_RNDD);

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,a,h,GMP_RNDN);

  evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, x1, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  while(mpfr_lessequal_p(x2,b)) {
    if((mpfr_sgn(y1)==0) || (mpfr_sgn(y2)==0) || (mpfr_sgn(y1) != mpfr_sgn(y2))) {
      i++;
      if(i>deg+2)
	printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
      else {
	if (mpfr_sgn(y1)==0) {
	  mpfr_set(res[i-1], x1, GMP_RNDN);
	  if(mpfr_sgn(y2)==0) {
	    i++;
	    if(i>deg+2)
	      printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
	    else mpfr_set(res[i-1], x2, GMP_RNDN);
	  }
	}
	else {
	  if (mpfr_sgn(y2)==0) mpfr_set(res[i-1], x2, GMP_RNDN);
	  else newton(res[i-1], tree, diff_tree, x1, x2, mpfr_sgn(y1), prec);
	}
      }
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
      mpfr_set(res[deg], a, GMP_RNDN);
      mpfr_set(res[deg+1], b, GMP_RNDN);
      mpfr_sort(res, deg+2, prec);
    }
    else {
      if (i==deg +1) {
	evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, a, zero_mpfr, prec);
	evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, b, zero_mpfr, prec);
	if (mpfr_cmpabs(y1,y2)>0) mpfr_set(res[deg+1], a, GMP_RNDN);
	else mpfr_set(res[deg+1], b, GMP_RNDN);
	mpfr_sort(res, deg+2, prec);
      }
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(zero_mpfr);
  return;
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
int qualityOfError(mpfr_t computedQuality, mpfr_t infiniteNorm, mpfr_t *x,
		   node *poly, node *poly_diff, node *poly_diff2,
		   node *f, node *f_diff, node *f_diff2,
		   node *w, node *w_diff, node *w_diff2,
		   int freeDegrees, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  node *error;
  node *temp1;
  node *error_diff;
  node *error_diff2;
  int test, i, r;
  int case1, case2, case2b, case3;
  int *s;
  mpfr_t *y;
  mpfr_t var_mpfr, dummy_mpfr, dummy_mpfr2, max_val, min_val, zero_mpfr;
  mpfr_t *z;
  
  int crash_report = 0;
  int n = freeDegrees+1;
  
  mpfr_init2(var_mpfr, prec);
  mpfr_init2(zero_mpfr, 53);
  mpfr_init2(max_val, prec);
  mpfr_init2(min_val, prec);
  mpfr_init2(dummy_mpfr, 5);
  mpfr_init2(dummy_mpfr2, 53);

  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  z = safeMalloc(n*sizeof(mpfr_t));
  for(i=1;i<=n;i++) mpfr_init2(z[i-1],prec);

  
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

  temp1 = simplifyTreeErrorfree(error);
  free_memory(error);
  error = temp1;

  if(verbosity>=3) printf("Constructing the error' tree... \n");
  error_diff = differentiate(error);
  temp1 = simplifyTreeErrorfree(error_diff);
  free_memory(error_diff);
  error_diff = temp1;

  if(verbosity>=3) printf("Constructing the error'' trees... \n");
  error_diff2 = differentiate(error_diff);
  temp1 = simplifyTreeErrorfree(error_diff2);
  free_memory(error_diff2);
  error_diff2 = temp1;
  
  if(verbosity>=3) printf("Computing the yi... \n");
  // If x = [x1 ... xn], we construct [y0 y1 ... yn] by
  // y0 = (a+x1)/2, yn = (xn+b)/2 and yi = (xi + x(i+1))/2
  y = (mpfr_t *)safeMalloc((n+1)*sizeof(mpfr_t));
  mpfr_init2(y[0], prec);
  mpfr_add(y[0], x[0], a, GMP_RNDN);
  mpfr_div_2ui(y[0], y[0], 1, GMP_RNDN);
  
  for(i=1; i<n; i++) {
    mpfr_init2(y[i], prec);
    mpfr_add(y[i], x[i-1], x[i], GMP_RNDN);
    mpfr_div_2ui(y[i], y[i], 1, GMP_RNDN);
  }

  mpfr_init2(y[n], prec);
  mpfr_add(y[n], x[n-1], b, GMP_RNDN);
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
    if((case1 || case2b) && (s[0]*s[1]<=0)) {
      if(s[0]==0) mpfr_set(z[0], a, GMP_RNDN);
      else {
	if(s[1]==0) mpfr_set(z[0], y[1], GMP_RNDN);
	else findZero(z[0], error_diff, error_diff2,y[0],y[1],s[0],NULL,2,prec);
      }
    }
    if((case1 || case2b) && (s[0]*s[1]>0)) mpfr_set(z[0], a, GMP_RNDN);
    if(case2 || case3) findZero(z[0], error_diff, error_diff2, y[0], y[1], s[0], &x[0], 2, prec);
    
    for(i=1;i<=n-2;i++) findZero(z[i], error_diff, error_diff2, y[i], y[i+1], s[i], &x[i], 2, prec);

    if((case1 || case2) && (s[n-1]*s[n]<=0)) {
      if(s[n]==0) mpfr_set(z[n-1], b, GMP_RNDN);
      else {
	if(s[n-1]==0) mpfr_set(z[n-1], y[n-1], GMP_RNDN);
	else findZero(z[n-1], error_diff, error_diff2, y[n-1], y[n], s[n-1], NULL, 2, prec);
      }
    }

    if((case1 || case2) && (s[n-1]*s[n]>0)) mpfr_set(z[n-1],b,GMP_RNDN);
    if(case2b || case3) findZero(z[n-1], error_diff, error_diff2, y[n-1], y[n], s[n-1], &x[n-1], 2, prec);
  }
  else {
    printMessage(1,"Warning in Remez: a slower algorithm is used for this step\n");
    quickFindZeros(z, error_diff, error_diff2, freeDegrees-1, a, b, prec, &crash_report);
    if(crash_report==-1) {
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
      for(i=1;i<=n;i++) {
	mpfr_clear(z[i-1]);
      }
      free(z);

      return -1;
    }
  }

  if(verbosity>=3) {
    printf("The new points are : ");
    for(i=1; i<=n; i++) printMpfr(z[i-1]);
  }

  // Test the quality of the current error

  mpfr_set_d(max_val, 0., GMP_RNDN);
  mpfr_set_inf(min_val, 1);

  if((computedQuality!=NULL) || (infiniteNorm != NULL)) {
    for(i=1;i<=n;i++) {
      r = evaluateFaithfulWithCutOffFast(var_mpfr, error, error_diff, z[i-1], zero_mpfr, prec);
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
  for(i=1;i<=n;i++) {
    mpfr_set(x[i-1], z[i-1], GMP_RNDN);
    mpfr_clear(z[i-1]);
  }
  free(z);

  return 0;
}

node *remezAux(node *f, node *w, chain *monomials, mpfr_t u, mpfr_t v, mp_prec_t prec, mpfr_t quality) {
  int freeDegrees = lengthChain(monomials);
  int i,j, r, count, test, crash;
  mpfr_t zero_mpfr, var1, var2, var3, computedQuality, infiniteNorm;
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
  node **monomials_tree;
  mpfr_t *x;
  mpfr_t *M;
  mpfr_t *b;
  mpfr_t *ai_vect;


  if(verbosity>=3) {
    printf("Entering in Remez function...\n");
    printf("Required quality :"); printMpfr(quality);
  }

  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);
  mpfr_init2(var3, prec);

  mpfr_init2(zero_mpfr, 53);
  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_init2(computedQuality, mpfr_get_prec(quality));
  mpfr_set_inf(computedQuality, 1);
  mpfr_init2(infiniteNorm, 53);

  M = safeMalloc((freeDegrees+1)*(freeDegrees+1)*sizeof(mpfr_t));
  b = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  ai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  x = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  
  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_init2(M[coeff(i,j,freeDegrees+1)],prec);
    }
    mpfr_init2(b[j-1], prec);
    mpfr_init2(ai_vect[j-1], prec);
    mpfr_init2(x[j-1], prec);
  }


  if(verbosity>=3)  printf("Differentiating functions...\n");
  pushTimeCounter();
  poly = NULL;
  f_diff = differentiate(f);
  f_diff2 = differentiate(f_diff);
  w_diff = differentiate(w);
  w_diff2 = differentiate(w_diff);
  popTimeCounter("Remez: differentiating the functions");


  if(verbosity>=3)  printf("Computing monomials...\n");
  pushTimeCounter();
  monomials_tree = safeMalloc(freeDegrees*sizeof(node *));
  curr = monomials;
  for(j=0;j<freeDegrees;j++) {
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

    monomials_tree[j] = temp_tree3;
    curr=curr->next;
  }
  popTimeCounter("Remez: computing monomials");


  count = 0;

  // Definition of the array x of the n+2 Chebychev points

  if(verbosity>=3) {
    printf("Computing an initial points set...\n");
  }
  pushTimeCounter();

  /*************************************************************/
  mpfr_const_pi(var1, GMP_RNDN);
  mpfr_div_si(var1, var1, (long)freeDegrees, GMP_RNDN); // var1 = Pi/freeDegrees
  mpfr_sub(var2, u, v, GMP_RNDN);
  mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (u-v)/2
  mpfr_add(var3, u, v, GMP_RNDN);
  mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (u+v)/2
  
  for (i=1 ; i <= freeDegrees+1 ; i++) {
    mpfr_mul_si(x[i-1], var1, i-1, GMP_RNDN);
    mpfr_cos(x[i-1], x[i-1], GMP_RNDN);
    mpfr_fma(x[i-1], x[i-1], var2, var3, GMP_RNDN); // x_i = [cos((i-1)*Pi/freeDegrees)]*(u-v)/2 + (u+v)/2
  }
  /*************************************************************/


  /*************************************************************/
  /*                  Manually chosen points                   */
  // assume the list of points to be stored in variable list:
  // run:   i=0; for t in list do {write("mpfr_set_str(x[",i,"],\"",t,"\", 10, GMP_RNDN);\n"); i=i+1;} ;
  //  mpfr_set_str(x[0],"-0.3125e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[1],"-0.30584696851836061231178794452190602808051522319263946458708614667e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[2],"-0.28501111491205151104325157864034898021348356159961735558618431475e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[3],"-0.24886449463478475396949237795739500812185286056353102927127228394e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[4],"-0.19762290147941257522128271303067067541838484524908767960712080225e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[5],"-0.13250854683846223359806734141844877411014570720332055635801288526e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[6],"-0.56244711839221576562527112094385137737475296714313660806835935129e-2", 10, GMP_RNDN);
  //  mpfr_set_str(x[7],"0.28391683750101442278882006705620645329423774729985858978557164229e-2", 10, GMP_RNDN);
  //  mpfr_set_str(x[8],"0.11863948153667030697792566482168683761732741161430970590458867454e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[9],"0.20401920326072435911649203711058280321795097964607742385634405983e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[10],"0.2657769766120891383383375050507639378011506820549866146399169124e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[11],"0.30106407715604841735213313137699925783784565233826547024950086538e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[12],"0.3124e-1", 10, GMP_RNDN);
  //  mpfr_set_str(x[13],"0.3125e-1", 10, GMP_RNDN);
  /*************************************************************/



  /*************************************************************/
  /*                 Evenly distributed points                 */
  //mpfr_sub(var1, v, u, GMP_RNDN);
  //mpfr_div_si(var1, var1, (long)(freeDegrees), GMP_RNDN); // var1 = (v-u)/freeDegrees
  
  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(x[i-1], var1, i-1, GMP_RNDN);
  //  mpfr_add(x[i-1], x[i-1], u, GMP_RNDN);
  //}
  /*************************************************************/


  /*************************************************************/
  /*                  Alternative Cheb points                  */
  //mpfr_const_pi(var1, GMP_RNDN);
  //mpfr_div_si(var1, var1, 2*((long)freeDegrees+1), GMP_RNDN); // var1 = Pi/(2*freeDegrees+2)
  //mpfr_sub(var2, u, v, GMP_RNDN);
  //mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (u-v)/2
  //mpfr_add(var3, u, v, GMP_RNDN);
  //mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (u+v)/2

  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(x[i-1], var1, 2*i-1, GMP_RNDN);
  //  mpfr_cos(x[i-1], x[i-1], GMP_RNDN);
  //  mpfr_fma(x[i-1], x[i-1], var2, var3, GMP_RNDN); // x_i=[cos((2i-1)*Pi/(2freeDegrees+2))]*(u-v)/2 + (u+v)/2
  //}
  /*************************************************************/

  popTimeCounter("Remez: computing initial points set");
  if(verbosity>=4) {
    printf("Computed points set:\n");
    for(i=1;i<=freeDegrees+1;i++) printMpfr(x[i-1]);
  }
  
  while((mpfr_cmp(computedQuality, quality)>0) && (count<1000)) {
    free_memory(poly);

    // Definition of the matrix M of Remez algorithm
    if(verbosity>=3) {
      printf("Step %d\n",count);
      printf("Computing the matrix...\n");
    }
    pushTimeCounter();

    for (i=1 ; i <= freeDegrees+1 ; i++) {
      r = evaluateFaithfulWithCutOffFast(var1, w, NULL, x[i-1], zero_mpfr, prec);
      if((r==1) && (mpfr_number_p(var1))) test=1;
      else test=0;
		 
      for (j=1 ; j <= freeDegrees ; j++) {
	if(test==1) {
	  r = evaluateFaithfulWithCutOffFast(var2, monomials_tree[j-1], NULL, x[i-1], zero_mpfr, prec);
	  if((r==1) && (mpfr_number_p(var2))) {
	    mpfr_mul(var2, var1, var2, GMP_RNDN);
	    mpfr_set(M[coeff(i,j,freeDegrees+1)],var2,GMP_RNDN);
	  }
	}
	if((test==0) || (r==0) || (!mpfr_number_p(var2))) {
	  printMessage(2,"Information: the construction of M[%d,%d] uses a slower algorithm\n",i,j);
	  temp_tree = safeMalloc(sizeof(node));
	  temp_tree->nodeType = MUL;
	  temp_tree->child1 = copyTree(monomials_tree[j-1]);
	  temp_tree->child2 = copyTree(w);
	  
	  temp_tree2 = simplifyTreeErrorfree(temp_tree);
	  free_memory(temp_tree);
	  temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
	  
	  r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, x[i-1], zero_mpfr, prec);

	  if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
	  mpfr_set(M[coeff(i,j,freeDegrees+1)],var1,GMP_RNDN);

	  free_memory(temp_tree);
	}
      }
    }

    for (i=1 ; i <= freeDegrees+1 ; i++) {
      mpfr_set_si(M[coeff(i, freeDegrees+1, freeDegrees+1)], (i % 2)*2-1,GMP_RNDN);
    }

    popTimeCounter("Remez: computing the matrix");

    if(verbosity>=5) {
      printf("The computed matrix is "); printMatrix(M, freeDegrees+1);
    }
        
    
    // Determination of the polynomial corresponding to M and x
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      r = evaluateFaithfulWithCutOffFast(var1, f, NULL, x[i-1], zero_mpfr, prec); // var1=f(x_i)
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);

      mpfr_set(b[i-1],var1,GMP_RNDN);
    }

    if(verbosity>=3) printf("Resolving the system...\n");

    pushTimeCounter();
    system_solve(ai_vect, M, b, freeDegrees+1, prec);
    popTimeCounter("Remez: solving the system");

    poly = constructPolynomial(ai_vect, monomials, prec);

    if(verbosity>=4) {
      printf("The computed polynomial is "); printTree(poly); printf("\n");
    }

    // Computing the useful derivatives of functions
    if(verbosity>=3) {
      printf("Differentiating the computed polynomial...\n");
    }
    
    pushTimeCounter();
    
    temp_tree = horner(poly);
    free_memory(poly);
    poly = temp_tree;

    poly_diff = differentiate(poly);
    poly_diff2 = differentiate(poly_diff);
    
    popTimeCounter("Remez: differentiating the polynomial");

    if(verbosity>=3) {
      printf("Searching extrema of the error function...\n");
    }
    
    // Find extremas and tests the quality of the current approximation
    pushTimeCounter();
    crash = qualityOfError(computedQuality, infiniteNorm, x,
			   poly, poly_diff, poly_diff2,
			   f, f_diff, f_diff2,
			   w, w_diff, w_diff2,
			   freeDegrees, u, v, prec);
    popTimeCounter("Remez: computing the quality of approximation");

    if(crash==-1) {
      for(j=0;j<freeDegrees;j++) {
	free_memory(monomials_tree[j]);
      }
      free(monomials_tree);
      
      for(j=1;j<=freeDegrees+1;j++) mpfr_clear(x[j-1]);
      free(x);

      free_memory(poly_diff);
      free_memory(poly_diff2);
      mpfr_clear(zero_mpfr);
      mpfr_clear(var1);
      mpfr_clear(var2);
      mpfr_clear(var3);
      free_memory(f_diff);
      free_memory(f_diff2);
      free_memory(w_diff);
      free_memory(w_diff2);
      mpfr_clear(computedQuality);
      mpfr_clear(infiniteNorm);

      for(j=1; j <= freeDegrees+1 ; j++) {
	for(i=1; i<= freeDegrees+1; i++) {
	  mpfr_clear(M[coeff(i,j,freeDegrees+1)]);
	}
	mpfr_clear(b[j-1]);
	mpfr_clear(ai_vect[j-1]);
      }
      free(M);
      free(b);
      free(ai_vect);

      recoverFromError();
    }
      
    if(verbosity>=4) {    
      printf("New points set:\n");
      for(i=1;i<=freeDegrees+1;i++) printMpfr(x[i-1]);
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


  for(j=0;j<freeDegrees;j++) {
    free_memory(monomials_tree[j]);
  }
  free(monomials_tree);

  for(i=1; i<=freeDegrees+1; i++) {
    mpfr_clear(x[i-1]);
  }
  free(x);


  mpfr_clear(zero_mpfr);
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(var3);
  free_memory(f_diff);
  free_memory(f_diff2);
  free_memory(w_diff);
  free_memory(w_diff2);

  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_clear(M[coeff(i,j,freeDegrees+1)]);
    }
    mpfr_clear(b[j-1]);
    mpfr_clear(ai_vect[j-1]);
  }
  free(M);
  free(b);
  free(ai_vect);

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
  
node *remez(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mpfr_t *requestedQuality, mp_prec_t prec) {
  mpfr_t quality;
  node *res;
  chain *monomials2;

  mpfr_init2(quality, 53);
  if (requestedQuality==NULL) mpfr_set_d(quality, 0.00001, GMP_RNDN);
  else mpfr_abs(quality, *requestedQuality, GMP_RNDN);
  
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
int whichPoly(int deg, node *f, node *w, mpfr_t u, mpfr_t v, mpfr_t eps) {
  mp_prec_t prec = defaultprecision;
  int freeDegrees = deg+1;
  chain *monomials;
  int *var;
  int res;
  
  int i,j, r, count, test, crash;
  mpfr_t zero_mpfr, var1, var2, var3, computedQuality, infiniteNorm;
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
  node **monomials_tree;
  mpfr_t *x;
  mpfr_t *M;
  mpfr_t *b;
  mpfr_t *ai_vect;


  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);
  mpfr_init2(var3, prec);

  mpfr_init2(zero_mpfr, 53);
  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_init2(computedQuality, prec);
  mpfr_set_inf(computedQuality, 1);
  mpfr_init2(infiniteNorm, 53);

  M = safeMalloc((freeDegrees+1)*(freeDegrees+1)*sizeof(mpfr_t));
  b = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  ai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  x = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  
  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_init2(M[coeff(i,j,freeDegrees+1)],prec);
    }
    mpfr_init2(b[j-1], prec);
    mpfr_init2(ai_vect[j-1], prec);
    mpfr_init2(x[j-1], prec);
  }

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


  monomials_tree = safeMalloc(freeDegrees*sizeof(node *));
  curr = monomials;
  for(j=0;j<freeDegrees;j++) {
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

    monomials_tree[j] = temp_tree3;
    curr=curr->next;
  }


  count = 0;

  // Definition of the array x of the n+2 Chebychev points


  /*************************************************************/
  mpfr_const_pi(var1, GMP_RNDN);
  mpfr_div_si(var1, var1, (long)freeDegrees, GMP_RNDN); // var1 = Pi/freeDegrees
  mpfr_sub(var2, u, v, GMP_RNDN);
  mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (u-v)/2
  mpfr_add(var3, u, v, GMP_RNDN);
  mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (u+v)/2

  for (i=1 ; i <= freeDegrees+1 ; i++) {
    mpfr_mul_si(x[i-1], var1, i-1, GMP_RNDN);
    mpfr_cos(x[i-1], x[i-1], GMP_RNDN);
    mpfr_fma(x[i-1], x[i-1], var2, var3, GMP_RNDN); // x_i = [cos((i-1)*Pi/freeDegrees)]*(u-v)/2 + (u+v)/2
  }
  /*************************************************************/


  /*************************************************************/
  /*                 Evenly distributed points                 */
  //x = cgetg(freeDegrees + 2, t_COL);
  //mpfr_sub(x[i-1], v, u, GMP_RNDN);
  //mpfr_div_si(x[i-1], x[i-1], (long)(freeDegrees), GMP_RNDN); // x_i = (v-u)/freeDegrees
  //
  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(x[i-1], x[i-1], i-1, GMP_RNDN);
  //  mpfr_add(x[i-1], x[i-1], u, GMP_RNDN);
  //}
  /*************************************************************/


  /*************************************************************/
  /*                  Alternative Cheb points                  */
  //x = cgetg(freeDegrees + 2, t_COL);
  //mpfr_const_pi(var1, GMP_RNDN);
  //mpfr_div_si(var1, var1, 2*((long)freeDegrees+1), GMP_RNDN); // var1 = Pi/(2*freeDegrees+2)
  //mpfr_sub(var2, u, v, GMP_RNDN);
  //mpfr_div_2ui(var2, var2, 1, GMP_RNDN); // var2 = (u-v)/2
  //mpfr_add(var3, u, v, GMP_RNDN);
  //mpfr_div_2ui(var3, var3, 1, GMP_RNDN); // var3 = (u+v)/2

  //for (i=1 ; i <= freeDegrees+1 ; i++) {
  //  mpfr_mul_si(x[i-1], var1, 2*i-1, GMP_RNDN);
  //  mpfr_cos(x[i-1], x[i-1], GMP_RNDN);
  //  mpfr_fma(x[i-1], x[i-1], var2, var3, GMP_RNDN); // x_i=[cos((2i-1)*Pi/(2freeDegrees+2))]*(u-v)/2 + (u+v)/2
  //}
  /*************************************************************/
  
    // Definition of the matrix M of Remez algorithm
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      r = evaluateFaithfulWithCutOffFast(var1, w, NULL, x[i-1], zero_mpfr, prec);
      if((r==1) && (mpfr_number_p(var1))) test=1;
      else test=0;
		 
      for (j=1 ; j <= freeDegrees ; j++) {
	if(test==1) {
	  r = evaluateFaithfulWithCutOffFast(var2, monomials_tree[j-1], NULL, x[i-1], zero_mpfr, prec);
	  if((r==1) && (mpfr_number_p(var2))) {
	    mpfr_mul(var2, var1, var2, GMP_RNDN);
	    mpfr_set(M[coeff(i,j,freeDegrees+1)],var2,GMP_RNDN);
	  }
	}
	if((test==0) || (r==0) || (!mpfr_number_p(var2))) {
	  printMessage(2,"Information: the construction of M[%d,%d] uses a slower algorithm\n",i,j);
	  temp_tree = safeMalloc(sizeof(node));
	  temp_tree->nodeType = MUL;
	  temp_tree->child1 = copyTree(monomials_tree[j-1]);
	  temp_tree->child2 = copyTree(w);
	  
	  temp_tree2 = simplifyTreeErrorfree(temp_tree);
	  free_memory(temp_tree);
	  temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
	  
	  r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, x[i-1], zero_mpfr, prec);
	  if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
	  mpfr_set(M[coeff(i,j,freeDegrees+1)],var1,GMP_RNDN);

	  free_memory(temp_tree);
	}
      }
    }

    for (i=1 ; i <= freeDegrees+1 ; i++) {
      mpfr_set_si(M[coeff(i, freeDegrees+1, freeDegrees+1)], (i % 2)*2-1,GMP_RNDN);
    }

        
    // Determination of the polynomial corresponding to M and x
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      r = evaluateFaithfulWithCutOffFast(var1, f, NULL, x[i-1], zero_mpfr, prec); // var1=f(x_i)
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);

      mpfr_set(b[i-1],var1,GMP_RNDN);
    }

    system_solve(ai_vect, M, b, freeDegrees+1, prec);
    poly = constructPolynomial(ai_vect, monomials, prec);


    // Computing the useful derivatives of functions
    temp_tree = horner(poly);
    free_memory(poly);
    poly = temp_tree;

    poly_diff = differentiate(poly);
    poly_diff2 = differentiate(poly_diff);
    
    
    // Find extremas and tests the quality of the current approximation
    crash = qualityOfError(computedQuality, infiniteNorm, x,
			   poly, poly_diff, poly_diff2,
			   f, f_diff, f_diff2,
			   w, w_diff, w_diff2,
			   freeDegrees, u, v, prec);
    
    if(crash==-1) {
      for(j=0;j<freeDegrees;j++) {
	free_memory(monomials_tree[j]);
      }
      free(monomials_tree);
      
      for(j=1;j<=freeDegrees+1;j++) mpfr_clear(x[j-1]);
      free(x);

      free_memory(poly_diff);
      free_memory(poly_diff2);
      mpfr_clear(zero_mpfr);
      mpfr_clear(var1);
      mpfr_clear(var2);
      mpfr_clear(var3);
      free_memory(f_diff);
      free_memory(f_diff2);
      free_memory(w_diff);
      free_memory(w_diff2);
      mpfr_clear(computedQuality);
      mpfr_clear(infiniteNorm);

      for(j=1; j <= freeDegrees+1 ; j++) {
	for(i=1; i<= freeDegrees+1; i++) {
	  mpfr_clear(M[coeff(i,j,freeDegrees+1)]);
	}
	mpfr_clear(b[j-1]);
	mpfr_clear(ai_vect[j-1]);
      }
      free(M);
      free(b);
      free(ai_vect);

      recoverFromError();
    }

  
  if(mpfr_cmp(eps,infiniteNorm) >= 0) res=1;
  else {
    mpfr_add_ui(computedQuality, computedQuality, 1, GMP_RNDU);
    mpfr_div(infiniteNorm, infiniteNorm, computedQuality, GMP_RNDD);
    if(mpfr_cmp(eps,infiniteNorm) < 0) res=-1;
    else res=0;
  }

  
  for(j=0;j<freeDegrees;j++) {
    free_memory(monomials_tree[j]);
  }
  free(monomials_tree);
  
  for(j=1;j<=freeDegrees+1;j++) mpfr_clear(x[j-1]);
  free(x);
  
  free_memory(poly_diff);
  free_memory(poly_diff2);
  mpfr_clear(zero_mpfr);
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(var3);
  free_memory(f_diff);
  free_memory(f_diff2);
  free_memory(w_diff);
  free_memory(w_diff2);
  mpfr_clear(computedQuality);
  mpfr_clear(infiniteNorm);
  
  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_clear(M[coeff(i,j,freeDegrees+1)]);
    }
    mpfr_clear(b[j-1]);
    mpfr_clear(ai_vect[j-1]);
  }
  free(M);
  free(b);
  free(ai_vect);
  
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
    while(res!=-1) {
      n_min--;
      res = whichPoly(n_min,func,weight,a,b,eps);
    }
    n_min = n_min + 1;
    res=0;
    while(res!=1) {
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
