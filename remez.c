/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.fr
sylvain.chevillard@ens-lyon.fr
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinite norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
herefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*/

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
  i0 = j0 = -1;
  for(k=1;k<=n;k++) {
    mpfr_set_d(max, 0., GMP_RNDN); //exact

    // In this part, we search for the bigger element of the matrix
    curri = i_list;
    while(curri!=NULL) {
      currj = j_list;
      while(currj!=NULL) {
	i = *(int *)(curri->value);
	j = *(int *)(currj->value);
	if(mpfr_cmpabs(M[coeff(i,j,n)],max)>=0) {
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

  if(verbosity>=7) {
    changeToWarningMode();
    printf("Newton's call with parameters :"); printTree(f); printf("\n");
    printMpfr(a); printMpfr(b);
    printMpfr(x); evaluateFaithful(y,f,x,prec); printMpfr(y);
    restoreMode();
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
      if(verbosity>=6) {
	changeToWarningMode();
	printf("Entering in a rescue case of Newton's algorithm\n");
	printMpfr(xNew);
	restoreMode();
      }
      
      // We do a step of binary search
      mpfr_add(xNew,u,v,GMP_RNDN);
      mpfr_div_2ui(xNew, xNew, 1, GMP_RNDN);
      r = evaluateFaithfulWithCutOffFast(y, f, f_diff, xNew, zero_mpfr, prec); // y=f[(u+v)/2]

      if((!mpfr_number_p(y)) && (r==1)) {
	fprintf(stderr,"/*Warning: Newton's algorithm encountered numerical problems*/\n");
	if(verbosity>=2) {
	  changeToWarningMode();
	  printf("The function "); printTree(f); printf(" seems to be undefined at this point: ");  printMpfr(xNew);
	  restoreMode();
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
	if(mpfr_cmp_abs(v,u)>0) estim_prec = mpfr_get_exp(temp) - mpfr_get_exp(u) - 1;
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

  if(verbosity>=7) {
    changeToWarningMode();
    printf("Newton made %d iterations\n",nbr_iter);
    restoreMode();
  }
  
  if(verbosity>=7) {
    changeToWarningMode();
    printf("Newton's result :");
    printMpfr(x); evaluateFaithful(y,f,x,prec); printMpfr(y);
    restoreMode();
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
  
  free_memory(diff_tree);

  return result;
}

// Perform a step of exchange algorithm
// newx is the point to be inserted
// err_newx is the corresponding error
// lambdai_vect is the vector of lambda_i corresponding to vector x
// epsilon is the current radius of reference
//   note that (p*w-f)(x_{n+1})= epsilon by definition
//   and lambda_{n+1} = -1 by definition
//   Thus the rule is
//            * take the max of mu/lambda if sgn(err_newx)*sgn(epsilon)=-1
//            * take the min otherwise
// n is the number of elements in x
void single_step_remez(mpfr_t newx, mpfr_t err_newx, mpfr_t *x,
		       node **monomials_tree,
		       node *w,
		       mpfr_t *lambdai_vect,
		       mpfr_t epsilon,
		       int n, mp_prec_t prec) {
  int freeDegrees = n-1;
  int test,i,j,r, argmaxi, argmini;
  mpfr_t *N;
  mpfr_t *c;
  mpfr_t *mui_vect;
  node *temp_tree;
  node *temp_tree2;
  mpfr_t zero_mpfr, var1, var2;
  mpfr_t maxi;
  mpfr_t mini;
  
  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);

  mpfr_init2(zero_mpfr, 53);
  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  mpfr_init2(maxi, prec);
  mpfr_init2(mini, prec);
  
  N = safeMalloc(freeDegrees*freeDegrees*sizeof(mpfr_t));
  c = safeMalloc(freeDegrees*sizeof(mpfr_t));
  mui_vect = safeMalloc(freeDegrees*sizeof(mpfr_t));
  
  // Initialization of mui_vect
  for(j=1; j <= freeDegrees ; j++) {
    for(i=1; i<= freeDegrees; i++) {
      mpfr_init2(N[coeff(i,j,freeDegrees)],prec);
    }
    mpfr_init2(c[j-1], prec);
    mpfr_init2(mui_vect[j-1], prec);
  }

  // Computation of the matrix
  for (i=1 ; i <= freeDegrees ; i++) {
    r = evaluateFaithfulWithCutOffFast(var1, w, NULL, x[i-1], zero_mpfr, prec);
    if((r==1) && (mpfr_number_p(var1))) test=1;
    else test=0;
    
    for (j=1 ; j <= freeDegrees ; j++) {
      if(test==1) {
	r = evaluateFaithfulWithCutOffFast(var2, monomials_tree[j-1], NULL, x[i-1], zero_mpfr, prec);
	if((r==1) && (mpfr_number_p(var2))) {
	  mpfr_mul(var2, var1, var2, GMP_RNDN);
	  mpfr_set(N[coeff(j,i,freeDegrees)],var2,GMP_RNDN);
	}
      }
      if((test==0) || (r==0) || (!mpfr_number_p(var2))) {
	temp_tree = safeMalloc(sizeof(node));
	temp_tree->nodeType = MUL;
	temp_tree->child1 = copyTree(monomials_tree[j-1]);
	temp_tree->child2 = copyTree(w);
	
	temp_tree2 = simplifyTreeErrorfree(temp_tree);
	free_memory(temp_tree);
	temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
	
	r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, x[i-1], zero_mpfr, prec);
	
	if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
	mpfr_set(N[coeff(j,i,freeDegrees)],var1,GMP_RNDN);
	free_memory(temp_tree);
      }
    }
  }

  // Computation of the vector corresponding to the new point
  r = evaluateFaithfulWithCutOffFast(var1, w, NULL, newx, zero_mpfr, prec);
  if((r==1) && (mpfr_number_p(var1))) test=1;
  else test=0;
  
  for (j=1 ; j <= freeDegrees ; j++) {
    if(test==1) {
      r = evaluateFaithfulWithCutOffFast(var2, monomials_tree[j-1], NULL, newx, zero_mpfr, prec);
      if((r==1) && (mpfr_number_p(var2))) {
	mpfr_mul(var2, var1, var2, GMP_RNDN);
	mpfr_set(c[j-1],var2,GMP_RNDN);
      }
    }
    if((test==0) || (r==0) || (!mpfr_number_p(var2))) {
      temp_tree = safeMalloc(sizeof(node));
      temp_tree->nodeType = MUL;
      temp_tree->child1 = copyTree(monomials_tree[j-1]);
      temp_tree->child2 = copyTree(w);
      
      temp_tree2 = simplifyTreeErrorfree(temp_tree);
      free_memory(temp_tree);
      temp_tree = temp_tree2; // temp_tree = x^(monomials[j])*w(x)
      
      r = evaluateFaithfulWithCutOffFast(var1, temp_tree, NULL, newx, zero_mpfr, prec);
      
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);
      mpfr_set(c[j-1], var1, GMP_RNDN);
      free_memory(temp_tree);
    }
  }



  // Resolution of the system
  system_solve(mui_vect , N, c, freeDegrees, prec);

  // Finding the maximum and minimum
  mpfr_set(maxi, zero_mpfr, GMP_RNDN);
  argmaxi=freeDegrees;
  mpfr_set(mini, zero_mpfr, GMP_RNDN);
  argmini=freeDegrees;

  for(i=freeDegrees-1;i>=0;i--) {
    mpfr_div(var1, mui_vect[i], lambdai_vect[i], GMP_RNDN);
    if (mpfr_cmp(var1, maxi)>0) {
      mpfr_set(maxi, var1, GMP_RNDN);
      argmaxi=i;
    }
    if (mpfr_cmp(var1, mini)<0) {
      mpfr_set(mini, var1, GMP_RNDN);
      argmini=i;
    }
  }


  // Introduce newx
  if(mpfr_sgn(err_newx)*mpfr_sgn(epsilon)==1) {
    if(verbosity>=3) {
      changeToWarningMode();
      printf("Remez: exchange algorithm takes the minimum (");
      printValue(&mini, 53);
      printf(") at place %d\n",argmini);
      restoreMode();
    }
    mpfr_set(x[argmini], newx, GMP_RNDN);
  }
  else {
    if(verbosity>=3) {
      changeToWarningMode();
      printf("Remez: exchange algorithm takes the maximum (");
      printValue(&maxi, 53);
      printf(") at place %d\n",argmaxi);
      restoreMode();
    }
    mpfr_set(x[argmaxi], newx, GMP_RNDN);
  }

  mpfr_sort(x, freeDegrees+1, prec);

  
  // Freeing the memory
  
  for(j=1; j <= freeDegrees ; j++) {
    for(i=1; i<= freeDegrees; i++) {
      mpfr_clear(N[coeff(i,j,freeDegrees)]);
    }
    mpfr_clear(c[j-1]);
    mpfr_clear(mui_vect[j-1]);
  }
  free(N);
  free(c);
  free(mui_vect);

  mpfr_clear(zero_mpfr);
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(maxi);
  mpfr_clear(mini);

  return;
}


// Returns a PARI array containing the zeros of tree on [a;b]
// deg+1 indicates the number of zeros which we are expecting.
// error' = tree  and tree' = diff_tree
void quickFindZeros(mpfr_t *res, mpfr_t *curr_points,
		    node *error, node *tree, node *diff_tree,
		    node **monomials_tree, node *w, mpfr_t *lambdai_vect, mpfr_t epsilon, int HaarCompliant,
		    int deg,
		    mpfr_t a, mpfr_t b, mp_prec_t prec) {
  long int n = 50*(deg+2);
  long int i=0;

  /* The variable test is used to check that the maximum (in absolute value)
     of the error will be inserted in the new list of points.
     If it is not the case, a step of the exchange algorithm is performed */
  int test=0;
  mpfr_t h, x1, x2, x, y1, y2, zero_mpfr, maxi, argmaxi, z, alpha1, alpha2, alpha;

  mpfr_init2(h,prec);
  mpfr_init2(y1,prec);
  mpfr_init2(y2,prec);
  mpfr_init2(x1,prec);
  mpfr_init2(x2,prec);
  mpfr_init2(x, prec);
  mpfr_init2(zero_mpfr,prec);
  mpfr_init2(z, prec);
  mpfr_init2(maxi, prec);
  mpfr_init2(argmaxi, prec);
  mpfr_init2(alpha1, 24);
  mpfr_init2(alpha2, 24);
  mpfr_init2(alpha, 24);

  mpfr_set_d(zero_mpfr, 0., GMP_RNDN);

  evaluateFaithfulWithCutOffFast(z, error, tree, a, zero_mpfr, prec);
  mpfr_set(maxi,z,GMP_RNDN);
  mpfr_set(argmaxi,a,GMP_RNDN);
  evaluateFaithfulWithCutOffFast(z, error, tree, b, zero_mpfr, prec);
  if (mpfr_cmpabs(z,maxi)>0) {
    mpfr_set(maxi,z,GMP_RNDN);
    mpfr_set(argmaxi,b,GMP_RNDN);
  }

  mpfr_sub(h,b,a,GMP_RNDD);
  mpfr_div_si(h,h,n,GMP_RNDD);

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,a,h,GMP_RNDN);

  evaluateFaithfulWithCutOffFast(y1, tree, diff_tree, x1, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(alpha1, diff_tree, NULL, x1, zero_mpfr, prec);
  evaluateFaithfulWithCutOffFast(alpha2, diff_tree, NULL, x2, zero_mpfr, prec);

  while(mpfr_lessequal_p(x2,b)) {
    if( (mpfr_sgn(y1)==0) || (mpfr_sgn(y2)==0) || (mpfr_sgn(y1) != mpfr_sgn(y2))) {
      if (mpfr_sgn(y1)==0) {
	evaluateFaithfulWithCutOffFast(z, error, tree, x1, zero_mpfr, prec);
	if (mpfr_sgn(z)*mpfr_sgn(alpha1)<0) {
	  i++;
	  if(i>deg+2)
	    printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
	  else mpfr_set(res[i-1], x1, GMP_RNDN);
	}
	if (mpfr_cmpabs(z,maxi)>0) {
	  if ( (i>deg+2)||(mpfr_sgn(z)*mpfr_sgn(alpha1)>=0) ) test=0;
	  else test=1;
	  mpfr_set(maxi,z,GMP_RNDN);
	  mpfr_set(argmaxi,x1,GMP_RNDN);
	}
	
	/* if(mpfr_sgn(y2)==0) {
	     evaluateFaithfulWithCutOffFast(z, error, tree, x2, zero_mpfr, prec);
	     if (mpfr_sgn(z)*mpfr_sgn(alpha2)<0) {
	       i++;
	       if(i>deg+2)
	         printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
	       else mpfr_set(res[i-1], x2, GMP_RNDN);
	     }
	     if (mpfr_cmpabs(z,maxi)>0) {
	       if ( (i>deg+2)||(mpfr_sgn(z)*mpfr_sgn(alpha2)>=0) ) test=0;
	       else test=1;
	       mpfr_set(maxi,z,GMP_RNDN);
	       mpfr_set(argmaxi,x2,GMP_RNDN);
	     }
	   }
         */
      }
      else {
	if (mpfr_sgn(y2)==0) {
	  evaluateFaithfulWithCutOffFast(z, error, tree, x2, zero_mpfr, prec);
	  if (mpfr_sgn(z)*mpfr_sgn(alpha2)<0) {
	    i++;
	    if(i>deg+2)
	      printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
	    else mpfr_set(res[i-1], x2, GMP_RNDN);
	  }
	  if (mpfr_cmpabs(z,maxi)>0) {
	    if ( (i>deg+2) || (mpfr_sgn(z)*mpfr_sgn(alpha2)>=0) ) test=0;
	    else test=1;	
	    mpfr_set(maxi,z,GMP_RNDN);
	    mpfr_set(argmaxi,x2,GMP_RNDN);
	  }
	}
	else {
	  newton(x, tree, diff_tree, x1, x2, mpfr_sgn(y1), prec);
	  evaluateFaithfulWithCutOffFast(z, error, tree, x , zero_mpfr, prec);
	  evaluateFaithfulWithCutOffFast(alpha, diff_tree, NULL, x , zero_mpfr, prec);
	  if (mpfr_sgn(z)*mpfr_sgn(alpha)<0) {
	    i++;
	    if(i>deg+2)
	      printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
	    else mpfr_set(res[i-1], x, GMP_RNDN);
	  }
	  if (mpfr_cmpabs(z,maxi)>0) {
	    if ( (i>deg+2) || (mpfr_sgn(z)*mpfr_sgn(alpha)>=0) ) test=0;
	    else test=1;
	    mpfr_set(maxi,z,GMP_RNDN);
	    mpfr_set(argmaxi,x,GMP_RNDN);
	  }
	}
      }
    }
    
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_add(x2,x2,h,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluateFaithfulWithCutOffFast(y2, tree, diff_tree, x2, zero_mpfr, prec);
    evaluateFaithfulWithCutOffFast(alpha2, diff_tree, NULL, x2, zero_mpfr, prec);
  }
  
  if ((i<deg)||(i>deg+2)||(!HaarCompliant)||(!test)) {
    /* printMessage(1,"Warning: the function fails to oscillate enough.\n");
       printMessage(1,"Check Haar condition and/or increase precision.\n");
       *crash_report = -1; */
    test=0;
    printMessage(2, "Performing an exchange step...\n");
    if (verbosity>=4) {
      changeToWarningMode();
      printf("Computed infinite norm : "); printMpfr(maxi);
      printf("Reached at point "); printMpfr(argmaxi);
      restoreMode();
    }
    for(i=0;i<deg+2;i++) mpfr_set(res[i], curr_points[i], GMP_RNDN);
    single_step_remez(argmaxi, maxi, res, monomials_tree, w, lambdai_vect, epsilon, deg+2, prec);
  }
  else {
    // in this branch test=1
    if (i==deg) { 
      mpfr_set(res[deg], a, GMP_RNDN);
      mpfr_set(res[deg+1], b, GMP_RNDN);
      mpfr_sort(res, deg+2, prec);
    }
    else {
      if (i==deg+1) {
	evaluateFaithfulWithCutOffFast(y1, error, tree, a, zero_mpfr, prec);
	evaluateFaithfulWithCutOffFast(y2, error, tree, res[0], zero_mpfr, prec);
	if (mpfr_sgn(y1)==mpfr_sgn(y2))  mpfr_set(res[deg+1], b, GMP_RNDN);
	else {
	  evaluateFaithfulWithCutOffFast(y1,  error, tree, b, zero_mpfr, prec);
	  evaluateFaithfulWithCutOffFast(y2,  error, tree, res[deg], zero_mpfr, prec);
	  if (mpfr_sgn(y1)==mpfr_sgn(y2))  mpfr_set(res[deg+1], a, GMP_RNDN);
	  else {
	    evaluateFaithfulWithCutOffFast(y1,  error, tree, a, zero_mpfr, prec);
	    evaluateFaithfulWithCutOffFast(y2,  error, tree, b, zero_mpfr, prec);
	    if (mpfr_cmpabs(y1,y2)>0) mpfr_set(res[deg+1], a, GMP_RNDN);
	    else mpfr_set(res[deg+1], b, GMP_RNDN);
	  }
	}
	mpfr_sort(res, deg+2, prec);
      }
    }
  }

  if(test) {
    /* since we did not perform an exchange step, 
       we have to check that the pseudo-alternating condition 
       is fulfilled */

    test=1;
    for(i=0; (i<deg+2)&&test ;i++) {
      evaluateFaithfulWithCutOffFast(z, error, tree, res[i] , zero_mpfr, prec);
      if ( mpfr_sgn(z)*mpfr_sgn(lambdai_vect[i])*mpfr_sgn(epsilon) >= 0 ) test=0;
    }
    if(!test) {
      printMessage(2, "Failed to find pseudo-alternating points. Performing an exchange step...\n");
      if (verbosity>=4) {
	changeToWarningMode();
	printf("Computed infinite norm : "); printMpfr(maxi);
	printf("Reached at point "); printMpfr(argmaxi);
	restoreMode();
      }
      for(i=0;i<deg+2;i++) mpfr_set(res[i], curr_points[i], GMP_RNDN);
      single_step_remez(argmaxi, maxi, res, monomials_tree, w, lambdai_vect, epsilon, deg+2, prec);
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(x); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(zero_mpfr); mpfr_clear(z); mpfr_clear(maxi); mpfr_clear(argmaxi); mpfr_clear(alpha1); mpfr_clear(alpha2); mpfr_clear(alpha);
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
		   node *poly, node *f, node *w,
		   node **monomials_tree, mpfr_t *lambdai_vect, mpfr_t epsilon, int HaarCompliant,
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
  if(verbosity>=8) { 	changeToWarningMode(); printf("Constructing the error tree... \n"); restoreMode(); }
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

  if(verbosity>=8) { 	changeToWarningMode(); printf("Constructing the error' tree... \n"); restoreMode(); }
  error_diff = differentiate(error);
  temp1 = simplifyTreeErrorfree(error_diff);
  free_memory(error_diff);
  error_diff = temp1;

  if(verbosity>=8) { 	changeToWarningMode(); printf("Constructing the error'' trees... \n"); restoreMode(); }
  error_diff2 = differentiate(error_diff);
  temp1 = simplifyTreeErrorfree(error_diff2);
  free_memory(error_diff2);
  error_diff2 = temp1;
  
  if(verbosity>=6) { 	changeToWarningMode(); printf("Computing the yi... \n"); restoreMode(); }
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

  if(verbosity>=6) {
    changeToWarningMode();
    printf("The computed yi are : ");
    for(i=0;i<=n;i++) {printMpfr(y[i]); printf(" ");}
    printf("\n");
    restoreMode();
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

  if(verbosity>=6) {
    changeToWarningMode();
    printf("We are in case : ");
    if(case1) printf("1\n");
    if(case2) printf("2\n");
    if(case2b) printf("2bis\n");
    if(case3) printf("3\n");
    restoreMode();
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

  if(verbosity>=6) {
    changeToWarningMode();
    if(test) {
      printf("The computed signs are : ");
      for(i=0;i<=n;i++) printf("%d  ",s[i]);
      printf("\n");
    }
    else printf("Test is false because signs could not be evaluated\n");
    restoreMode();
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

  if(test && HaarCompliant) {
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



    // We expect error(z[i]) ~ - sgn(lambda[i])*epsilon
    // We check the sign of error at these points and for z[i]<>a,b, we check the sign of error''
    test=1;
    for(i=1; (i<=n) && test; i++) {
      r = evaluateFaithfulWithCutOffFast(var_mpfr, error, error_diff, z[i-1], zero_mpfr, prec);
      if(r==0) mpfr_set_d(var_mpfr, 0., GMP_RNDN);

      if ( mpfr_sgn(var_mpfr)*mpfr_sgn(lambdai_vect[i-1])*mpfr_sgn(epsilon) >= 0 ) test=0;
    
      if ( (!mpfr_equal_p(z[i-1],a)) && (!mpfr_equal_p(z[i-1],b)) ) {
	r = evaluateFaithfulWithCutOffFast(var_mpfr, error_diff2, NULL, z[i-1], zero_mpfr, prec);
	if(r==0) mpfr_set_d(var_mpfr, 0., GMP_RNDN);
      
	if(-mpfr_sgn(var_mpfr)*mpfr_sgn(epsilon)*mpfr_sgn(lambdai_vect[i-1]) >= 0) test=0;
      }
    }
  
    if (!test) {
      printMessage(1,"Warning in Remez: main heuristic failed. A slower algorithm is used for this step\n");
      quickFindZeros(z, x, error, error_diff, error_diff2, monomials_tree, w, lambdai_vect, epsilon, HaarCompliant, freeDegrees-1, a, b, prec);

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
  }
  else {
    printMessage(1,"Warning in Remez: a slower algorithm is used for this step");
    if(!HaarCompliant) printMessage(1," (pseudo-alternation condition changed)");
    printMessage(1,"\n");
    quickFindZeros(z, x, error, error_diff, error_diff2, monomials_tree, w, lambdai_vect, epsilon, HaarCompliant, freeDegrees-1, a, b, prec);

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
    changeToWarningMode();
    printf("The new points are : ");
    for(i=1; i<=n; i++) printMpfr(z[i-1]);
    restoreMode();
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
    changeToWarningMode();
    mpfr_set(dummy_mpfr2,max_val,GMP_RNDN);
    printf("Current norm: "); printValue(&dummy_mpfr2, 5) ;
    mpfr_set(dummy_mpfr2,var_mpfr,GMP_RNDN);
    printf(" (1 +/- "); printValue(&dummy_mpfr2, 5);
    printf(")\n");
    restoreMode();
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
  int i,j, r, count, test, crash, HaarCompliant;
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
  mpfr_t *N;
  mpfr_t *b;
  mpfr_t *c;
  mpfr_t *ai_vect;
  mpfr_t *lambdai_vect;
  mpfr_t *previous_lambdai_vect;
  mpfr_t perturb;
  gmp_randstate_t random_state;

  gmp_randinit_default(random_state);
  gmp_randseed_ui(random_state, 65845285);
  
  if(verbosity>=3) {
    changeToWarningMode();
    printf("Entering in Remez function...\n");
    printf("Required quality :"); printMpfr(quality);
    restoreMode();
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
  N = safeMalloc(freeDegrees*freeDegrees*sizeof(mpfr_t));
  b = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  c = safeMalloc(freeDegrees*sizeof(mpfr_t));
  ai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  lambdai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  previous_lambdai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  x = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));
  
  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_init2(M[coeff(i,j,freeDegrees+1)],prec);
    }
    mpfr_init2(b[j-1], prec);
    mpfr_init2(ai_vect[j-1], prec);
    mpfr_init2(x[j-1], prec);
  }

  for(j=1; j <= freeDegrees ; j++) {
    for(i=1; i<= freeDegrees; i++) {
      mpfr_init2(N[coeff(i,j,freeDegrees)],prec);
    }
    mpfr_init2(c[j-1], prec);
    mpfr_init2(lambdai_vect[j-1], prec);
    mpfr_init2(previous_lambdai_vect[j-1], prec);
  }
  mpfr_init2(lambdai_vect[freeDegrees], prec);
  mpfr_init2(previous_lambdai_vect[freeDegrees], prec);
  mpfr_set_si(lambdai_vect[freeDegrees],-1,GMP_RNDN);
  mpfr_set_si(previous_lambdai_vect[freeDegrees],-1,GMP_RNDN);


  if(verbosity>=8)  { changeToWarningMode(); printf("Differentiating functions...\n"); restoreMode(); }
  pushTimeCounter();
  poly = NULL;
  f_diff = differentiate(f);
  f_diff2 = differentiate(f_diff);
  w_diff = differentiate(w);
  w_diff2 = differentiate(w_diff);
  popTimeCounter("Remez: differentiating the functions");


  if(verbosity>=8)  { changeToWarningMode(); printf("Computing monomials...\n"); restoreMode(); }
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

  if(verbosity>=8) {
    changeToWarningMode();
    printf("Computing an initial points set...\n");
    restoreMode();
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

  /* Random pertubration of the points... */
  mpfr_init2(perturb, prec);
  for(i=2;i<=freeDegrees;i++) {
    mpfr_urandomb(perturb, random_state);
    mpfr_mul_2ui(perturb, perturb, 1, GMP_RNDN);
    mpfr_sub_ui(perturb, perturb, 1, GMP_RNDN);
    mpfr_div_2ui(perturb, perturb, 2, GMP_RNDN); // perturb \in [-1/4; 1/4]

    mpfr_sub(var1, x[i-1], x[i-2], GMP_RNDN);
    mpfr_sub(var2, x[i], x[i-1], GMP_RNDN);
    if (mpfr_cmpabs(var1,var2)>0) mpfr_mul(var3, var2, perturb, GMP_RNDN);
    else mpfr_mul(var3, var1, perturb, GMP_RNDN);
    mpfr_add(x[i-1], x[i-1], var3, GMP_RNDN);
  }
  mpfr_clear(perturb);


  /*************************************************************/


  /*************************************************************/
  /*                  Manually chosen points                   */
  // assume the list of points to be stored in variable list:
  // run:   i=0; for t in list do {write("mpfr_set_str(x[",i,"],\"",t,"\", 10, GMP_RNDN);\n"); i=i+1;} ;

  /*   mpfr_set_str(x[0],"-0.3125e-1", 10, GMP_RNDN); */
  /*   mpfr_set_str(x[1],"-0.270866924296709954921192919457109841628145246303031e-1", 10, GMP_RNDN); */
  /*   mpfr_set_str(x[2],"-0.156792125481182037300460865714390558114871681447265e-1", 10, GMP_RNDN); */
  /*   mpfr_set_str(x[3],"0.270866923865259682207709736846537325622398567463872667e-1", 10, GMP_RNDN); */


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
    changeToWarningMode();
    printf("Computed points set:\n");
    for(i=1;i<=freeDegrees+1;i++) printMpfr(x[i-1]);
    restoreMode();
  }
  
  while((mpfr_cmp(computedQuality, quality)>0) && (count<120)) {
    free_memory(poly);

    // Definition of the matrices M and N of Remez algorithm
    // N lets us determine the modified alternation property
    // M lets us solve the interpolation problem
    if(verbosity>=3) {
      changeToWarningMode();
      printf("Step %d\n",count);
      printf("Computing the matrix...\n");
      restoreMode();
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
	    if (i<=freeDegrees) mpfr_set(N[coeff(j,i,freeDegrees)],var2,GMP_RNDN);
	    else mpfr_set(c[j-1],var2,GMP_RNDN);
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
	  if (i<=freeDegrees) mpfr_set(N[coeff(j,i,freeDegrees)],var1,GMP_RNDN);
	  else mpfr_set(c[j-1], var1, GMP_RNDN);
	  free_memory(temp_tree);
	}
      }
    }

    system_solve( lambdai_vect , N, c, freeDegrees, prec);

    HaarCompliant=1;
    for(i=1; i<=freeDegrees+1; i++) {
      if (mpfr_sgn(lambdai_vect[i-1])*mpfr_sgn(previous_lambdai_vect[i-1])<=0) HaarCompliant=0;
    }
    if(count==0) HaarCompliant=1;


    for (i=1 ; i <= freeDegrees+1 ; i++) {
      if (mpfr_sgn(lambdai_vect[i-1])>0)
	mpfr_set_si(M[coeff(i, freeDegrees+1, freeDegrees+1)], 1 ,GMP_RNDN);
      else {
	if (mpfr_sgn(lambdai_vect[i-1])<0)
	  mpfr_set_si(M[coeff(i, freeDegrees+1, freeDegrees+1)], -1 ,GMP_RNDN);
	else {
	  printMessage(1,"Warning: degenerated system in a non Haar context. The algorithm may be incorrect.\n");
	  mpfr_set_si(M[coeff(i, freeDegrees+1, freeDegrees+1)], 1 ,GMP_RNDN);
	}
      }
    }

    if(verbosity>=4) {
      changeToWarningMode();
      printf("Signs for pseudo-alternating condition : [");
      for (i=1 ; i <= freeDegrees ; i++) {
	printValue(&M[coeff(i, freeDegrees+1, freeDegrees+1)],10);
	printf(", ");
      }
      printf("-1]\n");
      restoreMode();
    }

    popTimeCounter("Remez: computing the matrix");

    if(verbosity>=7) {
      changeToWarningMode();
      printf("The computed matrix is "); printMatrix(M, freeDegrees+1);
      restoreMode();
    }
        
    
    // Determination of the polynomial corresponding to M and x
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      r = evaluateFaithfulWithCutOffFast(var1, f, NULL, x[i-1], zero_mpfr, prec); // var1=f(x_i)
      if(r==0) mpfr_set_d(var1, 0., GMP_RNDN);

      mpfr_set(b[i-1],var1,GMP_RNDN);
    }

    if(verbosity>=8) { changeToWarningMode(); printf("Resolving the system...\n"); restoreMode(); }

    pushTimeCounter();
    system_solve(ai_vect, M, b, freeDegrees+1, prec);
    popTimeCounter("Remez: solving the system");

    poly = constructPolynomial(ai_vect, monomials, prec);

    if(verbosity>=4) {
      changeToWarningMode();
      printf("The computed polynomial is "); printTree(poly); printf("\n");
      restoreMode();
    }
    if(verbosity>=3) {
      changeToWarningMode();
      printf("Current value of epsilon : "); printValue(&ai_vect[freeDegrees],53); printf("\n");
      restoreMode();
    }

    // Plotting the error curve
/*     node *plotTemp; */
/*     chain *plotList=NULL; */
/*     plotTemp = makeSub(makeMul(copyTree(poly),copyTree(w)),copyTree(f)); */
/*     plotList=addElement(plotList, plotTemp); */
/*     plotTree(plotList,u,v,defaultpoints,prec,NULL,0); */
/*     free_memory(plotTemp); */
    //    freeChain(plotList, doNothing);

    // Computing the useful derivatives of functions
    if(verbosity>=8) {
      changeToWarningMode();
      printf("Differentiating the computed polynomial...\n");
      restoreMode();
    }
    
    pushTimeCounter();
    
    temp_tree = horner(poly);
    free_memory(poly);
    poly = temp_tree;

    poly_diff = differentiate(poly);
    poly_diff2 = differentiate(poly_diff);
    
    popTimeCounter("Remez: differentiating the polynomial");

    if(verbosity>=8) {
      changeToWarningMode();
      printf("Searching extrema of the error function...\n");
      restoreMode();
    }
    
    // Find extremas and tests the quality of the current approximation
    pushTimeCounter();

    crash = qualityOfError(computedQuality, infiniteNorm, x,
			   poly, f, w,
			   monomials_tree, lambdai_vect, ai_vect[freeDegrees], HaarCompliant,
			   freeDegrees, u, v, prec);
    popTimeCounter("Remez: computing the quality of approximation");

    if(crash==-1) {

      // temporary check until I patch the algorithm in order to handle
      // correctly cases when the error oscillates too much
      mpfr_t ninf;
      mpfr_init2(ninf, 53);
      
      temp_tree = makeSub(makeMul(copyTree(poly), copyTree(w)), copyTree(f));
      uncertifiedInfnorm(ninf, temp_tree, u, v, getToolPoints(), prec);

      if(verbosity>=1) {
	changeToWarningMode();
	printf("The best polynomial obtained gives an error of ");
	printMpfr(ninf);
	printf("\n");
	restoreMode();
      }

      free_memory(temp_tree);
      mpfr_clear(ninf);
      // end of the temporary check


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

      for(j=1; j <= freeDegrees ; j++) {
	for(i=1; i<= freeDegrees; i++) {
	  mpfr_clear(N[coeff(i,j,freeDegrees)]);
	}
	mpfr_clear(c[j-1]);
	mpfr_clear(lambdai_vect[j-1]);
	mpfr_clear(previous_lambdai_vect[j-1]);
      }
      mpfr_clear(lambdai_vect[freeDegrees]);
      mpfr_clear(previous_lambdai_vect[freeDegrees]);
      free(N);
      free(c);
      free(lambdai_vect);
      free(previous_lambdai_vect);

      recoverFromError();
    }
      
    if(verbosity>=3) {
      changeToWarningMode();
      printf("Current quality: "); printMpfr(computedQuality);
      restoreMode();
    }

    count++;
    for(i=1; i<=freeDegrees+1; i++) {
      mpfr_set(previous_lambdai_vect[i-1], lambdai_vect[i-1], GMP_RNDN);
    }



    free_memory(poly_diff);
    free_memory(poly_diff2);
  }


  // temporary check until I patch the algorithm in order to handle
  // correctly cases when the error oscillates too much
  mpfr_t ninf;
  mpfr_init2(ninf, 53);

  temp_tree = makeSub(makeMul(copyTree(poly), copyTree(w)), copyTree(f));
  uncertifiedInfnorm(ninf, temp_tree, u, v, getToolPoints(), prec);
  free_memory(temp_tree);

  mpfr_add_ui(computedQuality, computedQuality, 1, GMP_RNDU);
  mpfr_mul(computedQuality, computedQuality, ninf, GMP_RNDU);
  mpfr_div(computedQuality, computedQuality, infiniteNorm, GMP_RNDU);
  mpfr_sub_ui(computedQuality, computedQuality, 1, GMP_RNDU);

  mpfr_clear(ninf);

  if(mpfr_cmp(computedQuality, quality)>0) {
    fprintf(stderr, "Error: Remez algorithm failed (too many oscillations?)\n");
    fprintf(stderr, "Please report the bug.\n");
  }
  // end of the temporary check

  
  if(verbosity>=2) {
    changeToWarningMode();
    printf("Remez finished after %d steps\n",count);
    printf("The computed infnorm is "); printValue(&infiniteNorm, 53) ; printf("\n");
    printf("The polynomial is optimal within a factor 1 +/- "); printValue(&computedQuality, 5); printf("\n");
    if(verbosity>=5) { printf("Computed poly: "); printTree(poly); printf("\n");}
    restoreMode();
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

  for(j=1; j <= freeDegrees ; j++) {
    for(i=1; i<= freeDegrees; i++) {
      mpfr_clear(N[coeff(i,j,freeDegrees)]);
    }
    mpfr_clear(c[j-1]);
    mpfr_clear(lambdai_vect[j-1]);
    mpfr_clear(previous_lambdai_vect[j-1]);
  }
  mpfr_clear(lambdai_vect[freeDegrees]);
  mpfr_clear(previous_lambdai_vect[freeDegrees]);
  free(N);
  free(c);
  free(lambdai_vect);
  free(previous_lambdai_vect);

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

  if (mpfr_equal_p(a,b))
    printMessage(1,"Warning: the input interval is reduced to a single point. The algorithm may not converge.\n");

  res = remezAux(func, weight, monomials2, a, b, prec, quality);

  freeChain(monomials2, freeIntPtr);
  mpfr_clear(quality);
  return res;
}


// returns 1 if deg is sufficient to approximate the function to eps
// returns -1 if deg is not sufficient
// 0 if we cannot determine.
int whichPoly(int deg, node *f, node *w, mpfr_t u, mpfr_t v, mpfr_t eps, int verb, int npoints) {
  mp_prec_t prec = defaultprecision;
  int freeDegrees = deg+1;
  chain *monomials;
  int *var;
  int res;
  
  int i,j, r, count, test, crash;
  mpfr_t zero_mpfr, var1, var2, var3, computedQuality, infiniteNorm;
  mpfr_t *ptr;
  mpfr_t *lambdai_vect;
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
  
  lambdai_vect = safeMalloc((freeDegrees+1)*sizeof(mpfr_t));

  for(j=1; j <= freeDegrees+1 ; j++) {
    for(i=1; i<= freeDegrees+1; i++) {
      mpfr_init2(M[coeff(i,j,freeDegrees+1)],prec);
    }
    mpfr_init2(b[j-1], prec);
    mpfr_init2(ai_vect[j-1], prec);
    mpfr_init2(x[j-1], prec);
  }

  i=-1;
  for(j=freeDegrees+1; j >= 1 ; j--) {
    mpfr_init2(lambdai_vect[j-1], prec);
    mpfr_set_si(lambdai_vect[j-1],i, GMP_RNDN);
    i=-i;
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
			   poly, f, w,
			   monomials_tree, lambdai_vect, ai_vect[freeDegrees], 1,
			   freeDegrees, u, v, prec);
    
    if(crash==-1) {
      verbosity=verb;
      defaultpoints=npoints;
      printMessage(1, "Warning: the function fails to oscillate enough.\n");
      printMessage(1, "Try to increase precision.\n");
      if (verbosity>=2) {
	changeToWarningMode();
	printf("The computed polynomial was: ");printTree(poly);
	printf("\n");
	restoreMode();
      }

      for(j=0;j<freeDegrees;j++) {
	free_memory(monomials_tree[j]);
      }
      free(monomials_tree);

      for(j=1;j<=freeDegrees+1;j++) {
	mpfr_clear(lambdai_vect[j-1]);
	mpfr_clear(x[j-1]);
      }
      free(x);
      free(lambdai_vect);

      free_memory(poly);
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

      freeChain(monomials,freeIntPtr);

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
  
  for(j=1;j<=freeDegrees+1;j++) {
    mpfr_clear(lambdai_vect[j-1]);
    mpfr_clear(x[j-1]);
  }
  free(x);
  free(lambdai_vect);
  free_memory(poly);
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
  
  freeChain(monomials, freeIntPtr);

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
    res = whichPoly(n_max, func, weight, a, b, eps, old_verbosity, number_points);
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
      res = whichPoly(n_min,func,weight,a,b,eps, old_verbosity, number_points);
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
    res = whichPoly((n_min+n_max)/2, func, weight, a, b, eps, old_verbosity, number_points);
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
      res = whichPoly(n_min,func,weight,a,b,eps, old_verbosity, number_points);
    }
    n_min = n_min + 1;
    res=0;
    while(res!=1) {
      n_max++;
      res = whichPoly(n_max,func,weight,a,b,eps, old_verbosity, number_points);
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
//node* remezWithWeight(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
//  return (copyTree(func));
//}
