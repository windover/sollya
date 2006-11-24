#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "pari_utils.h"
#include "main.h"
#include "expression.h"
#include "chain.h"
#include "remez.h"
#include "infnorm.h"
#include "plot.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>


// Convert an array [a0,..,an] of PARI REAL_t values
// using the chain [k0,...,kn] of ints
// into a tree representing the polynomial sum(ai*x^ki)
node *convert_poly(int first_index, int last_index, GEN tab, chain *monomials, mp_prec_t prec) {
  node *tree;
  node *temp1;
  node *temp2;
  node *temp3;
  node *temp4;
  node *temp5;
  node *temp6;
  mpfr_t *value;
  mpfr_t *value2;

  if (lengthChain(monomials) != (last_index-first_index)+1) {
    fprintf(stderr,"Error : in Remez, trying to convert an array of coefficients with respect to a list of monomials with different length.\n");
    recoverFromError();
  }

  if(lengthChain(monomials) == 0) {
    tree = safeMalloc(sizeof(node));
    tree->nodeType = CONSTANT;    
    value = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    mpfr_set_d(*value, 0., GMP_RNDN);
    tree->value = value;
    return tree;
  }

  if (first_index == last_index) {
    tree = safeMalloc(sizeof(node));
    tree->nodeType = MUL;

    temp1 = safeMalloc(sizeof(node));
    temp1->nodeType = CONSTANT;
    value = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value, (GEN)(tab[first_index]), GMP_RNDN);
    temp1->value = value;
    tree->child1 = temp1;

    temp2 = safeMalloc(sizeof(node));
    temp2->nodeType = POW;
    temp3 = safeMalloc(sizeof(node));
    temp3->nodeType = VARIABLE;
    temp2->child1 = temp3;

    temp4 = safeMalloc(sizeof(node));
    temp4->nodeType = CONSTANT;
    value2 = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value2, prec);
    mpfr_set_si(*value2, *((int *) monomials->value), GMP_RNDN);
    temp4->value = value2;
    temp2->child2 = temp4;
    tree->child2 = temp2;
  }
  else {
    temp1 = convert_poly(first_index+1, last_index, tab, monomials->next, prec);

    tree = safeMalloc(sizeof(node));
    tree->nodeType = ADD;
    tree->child2 = temp1;

    temp2 = safeMalloc(sizeof(node));
    temp2->nodeType = MUL;

    temp3 = safeMalloc(sizeof(node));
    temp3->nodeType = CONSTANT;
    value = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value, (GEN)(tab[first_index]), GMP_RNDN);
    temp3->value = value;

    temp4 = safeMalloc(sizeof(node));
    temp4->nodeType = POW;
    
    temp5 = safeMalloc(sizeof(node));
    temp5->nodeType = VARIABLE;

    temp6 = safeMalloc(sizeof(node));
    temp6->nodeType = CONSTANT;
    value2 = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value2, prec);
    mpfr_set_si(*value2, *((int *) monomials->value), GMP_RNDN);
    temp6->value = value2;

    temp4->child1 = temp5;
    temp4->child2 = temp6;
    temp2->child1 = temp3;
    temp2->child2 = temp4;
    tree->child1 = temp2;
  }

  return tree;
}


// Find the unique root of tree in [a;b]
GEN newton(node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t x, temp1, temp2;
  mpfr_t d;
  GEN res;
  unsigned long int n=1;
  int test=0;

  mpfr_init2(x,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec);
  mpfr_init2(d,53);

  mpfr_sub(d,b,a,GMP_RNDN);
  test = 1 + (mpfr_get_exp(b)-prec)/mpfr_get_exp(d);

  mpfr_add(x,a,b,GMP_RNDN);
  mpfr_div_2ui(x,x,1,GMP_RNDN);
  
  while(n<=test) {
    evaluateFaithful(temp1, tree, x, prec);
    evaluateFaithful(temp2, diff_tree, x, prec);
    mpfr_div(temp1, temp1, temp2, GMP_RNDN);
    mpfr_sub(x, x, temp1, GMP_RNDN);
    n = 2*n;
  }

  res = mpfr_to_PARI(x);
  mpfr_clear(x); mpfr_clear(temp1); mpfr_clear(temp2);
  mpfr_clear(d);
  return res;
}

// Returns a PARI array containing the zeros of tree on [a;b]
// The compuations are made with precision prec.
// deg indicates the number of zeros which we are expecting.
GEN quickFindZeros(node *tree, node *diff_tree, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec, int *crash_report) {
  GEN res;
  long int n = 50*(deg+2);
  long int i=0;
  mpfr_t h, x1, x2, y1, y2;

  mpfr_init2(h,prec);
  mpfr_init2(y1,prec);
  mpfr_init2(y2,prec);
  mpfr_init2(x1,prec);
  mpfr_init2(x2,prec);

  res = cgetg(deg+3, t_COL);

  mpfr_sub(h,b,a,GMP_RNDD);
  mpfr_div_si(h,h,n,GMP_RNDD);

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,a,h,GMP_RNDN);
  evaluateFaithful(y1, tree, x1, prec);
  evaluateFaithful(y2, tree, x2, prec);
  while(mpfr_lessequal_p(x2,b)) {
    if (mpfr_sgn(y1) != mpfr_sgn(y2)) {
      i++;
      if(i>deg+2)
	printMessage(1,"Warning: the function oscillates too much. Nevertheless, we try to continue.\n");
      else res[i] = (long)(newton(tree, diff_tree, x1, x2, prec));       
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_add(x2,x2,h,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluateFaithful(y2, tree, x2, prec);
  }
  
  if (i<deg) {
    printMessage(1,"Warning: the function fails to oscillate enough.\n");
    *crash_report = -1;
  }
  else {
    if (i==deg) { res[deg+1] = (long)(mpfr_to_PARI(a)); res[deg+2] = (long)(mpfr_to_PARI(b)); }
    else { // i = deg +1
      evaluateFaithful(y1, tree, a, prec);
      evaluateFaithful(y2, tree, b, prec);
      if (mpfr_greater_p(a,b)) res[deg+2] = (long)(mpfr_to_PARI(a));
      else res[deg+2] = (long)(mpfr_to_PARI(b));
      res = sort(res);
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2);
  return res;
}



double computeRatio(node *tree, GEN x, mp_prec_t prec) {
  int i;
  mpfr_t min, max, temp;
  double res;

  mpfr_init2(min,prec);
  mpfr_init2(max,prec);
  mpfr_init2(temp,prec);

  PARI_to_mpfr(temp, (GEN)(x[1]), GMP_RNDN);
  evaluateFaithful(min, tree, temp, prec);
  mpfr_abs(min,min,GMP_RNDN);
  mpfr_set(max,min,GMP_RNDN);

  for(i=0;i<lg(x)-1;i++) {
    PARI_to_mpfr(temp, (GEN)(x[i+1]), GMP_RNDN);
    evaluateFaithful(temp, tree, temp, prec);
    mpfr_abs(temp,temp,GMP_RNDN);
    if (mpfr_greater_p(min,temp)) mpfr_set(min,temp,GMP_RNDN);
    if (mpfr_greater_p(temp,max)) mpfr_set(max,temp,GMP_RNDN);
  }

  mpfr_sub(temp, max, min, GMP_RNDU);
  mpfr_div(temp, temp, min, GMP_RNDU);
  res = mpfr_get_d(temp, GMP_RNDU);

  mpfr_clear(min);
  mpfr_clear(max);
  mpfr_clear(temp);

  return res;
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


// Gives the monomials corresponding to the derivative of the argument m
chain *deriveMonomials(chain *m) {
  chain *res;
  chain *curr;
  int *elem;

  res = NULL;
  curr = m;
  while(curr!=NULL) {
    if (*((int *)(curr->value)) != 0) {
      elem = (int *) safeMalloc(sizeof(int));
      *elem = (*((int *)(curr->value))) - 1;
      res = addElement(res,elem);
    }
    curr = curr->next;
  }

  sortChain(res,cmpIntPtr);
  return res;
}


long lMypowgs(GEN x, long i) {
  if (gsigne(x) == 0) {
    if (i==0) return (long)(gun);
    else return (long)(gzero);
  }
  // else...
  return lpowgs(x,i);
}


node* remez(node *func, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  ulong ltop=avma;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j,k;
  GEN u, v, x, y, temp, temp_diff, temp_diff2, M;
  node *tree;
  node *tree_diff;
  node *tree_diff2;
  node *res = NULL;
  int test=1, crash_report;
  int deg, deg_diff, deg_diff2;
  chain *monomials_diff;
  chain *monomials_diff2;
  chain *curr;
  mpfr_t aprime, bprime;

  sortChain(monomials,cmpIntPtr);

  if (!testMonomials(monomials)) {
    fprintf(stderr,"Error: monomial degree is given twice in argument to Remez algorithm.\n");
    recoverFromError();
  }

  deg = lengthChain(monomials) - 1;
 
  tree = safeMalloc(sizeof(node));
  tree->nodeType = SUB;
  tree->child1 = copyTree(func);

  tree_diff = safeMalloc(sizeof(node));
  tree_diff->nodeType = SUB;
  tree_diff->child1 = differentiate(func);

  tree_diff2 = safeMalloc(sizeof(node));
  tree_diff2->nodeType = SUB;
  tree_diff2->child1 = differentiate(tree_diff->child1);

  monomials_diff = deriveMonomials(monomials);
  monomials_diff2 = deriveMonomials(monomials_diff);

  mpfr_init2(aprime,prec);
  mpfr_init2(bprime,prec);
  mpfr_set(aprime,a,GMP_RNDD);
  mpfr_set(bprime,b,GMP_RNDU);
  u = mpfr_to_PARI(aprime);
  v = mpfr_to_PARI(bprime);

  // Definition of the array x of the n+2 Chebychev points
  x = cgetg(deg+3, t_COL);
  for (i=0;i<deg+2;i++) {
    x[i+1] = lsub(gdivgs(gadd(u,v),2),
    		  gmul(gdivgs(gsub(v,u),2),
    		       gcos(gdivgs(gmulgs(mppi(prec_pari),2*i+1),
    				   2*deg+4),prec_pari)
    		       )
    		  );
    // To get evenly distributed points, choose the following points :
    // x[i+1] = ladd(u, gdivgs(gmulgs(gsub(v,u),i),(deg+1)));
  }

  M = cgetg(deg+3,t_MAT);
  temp = cgetg(deg+3, t_COL);
  temp_diff = cgetg(deg+3, t_COL);
  temp_diff2 = cgetg(deg+3, t_COL);
 
 // Main loop
  while(test) {

    // Definition of the Remez matrix M with respect to the point x_i
    curr = monomials;
    temp = gcopy(x);

    j=1;
    while(curr != NULL) {
      M[j] = lcopy(temp);
      for(i=0;i<=deg+1;i++) {
	coeff(M,i+1,j) = lMypowgs(gcoeff(M,i+1,j),(long)(*((int *)(curr->value))));
      }
      j++;
      curr = curr->next;
    }
    for(i=0;i<deg+2;i++) {
      temp[i+1] = (long)stoi((i % 2)*2-1);
    }
    M[deg+2] = lcopy(temp);
    
    
    // Definition of the array f(x)
    for(i=0;i<deg+2;i++) {
      temp[i+1] = (long)evaluate_to_PARI(func, (GEN)(x[i+1]), prec);
    }
    y = gcopy((GEN)(temp[1]));

    // Solves the system
    temp = gauss(M,temp);

    // Tests if the precision is sufficient
    /*if (gexpo((GEN)(temp[deg+2])) < gexpo(y)-prec+15) {
      printf("Warning : the precision seems to be not sufficient to compute the polynomial. ");
      printf("Please increase the precision. ");
      output(temp);
      printf("Since epsilon is near 2^(%d) and the value of your function is near 2^(%d), ",(int)(gexpo((GEN)(temp[deg+2]))),(int)(gexpo(y)));
      printf("we suggest you to set prec to %d.\n",(int)(-gexpo((GEN)(temp[deg+2]))+gexpo(y)+20));
      return copyTree(func);
      }*/
    
    // Formally derive the polynomial stored in temp
    curr = monomials;
    deg_diff = 0;
    k = 1;
    while(curr!=NULL) {
      j = (*((int *)(curr->value)));
      if (j!=0) {
	deg_diff++;
	temp_diff[deg_diff] = lmulrs((GEN)(temp[k]),(long)(j));
      }
      k++;
      curr = curr->next;
    }


    // Formally derive the polynomial stored in temp_diff
    curr = monomials_diff;
    deg_diff2 = 0;
    k=1;
    while(curr!=NULL) {
      j = (*((int *)(curr->value)));
      if (j!=0) {
	deg_diff2++;
	temp_diff2[deg_diff2] = lmulrs((GEN)(temp_diff[k]),(long)(j));
      }
      k++;
      curr = curr->next;
    }

    // Construction of the function f-p
    tree->child2 = convert_poly(1,deg+1, temp, monomials, prec);

    // Construction of the function f'-p'
    tree_diff->child2 = convert_poly(1,deg_diff, temp_diff, monomials_diff, prec);

    // Construction of the function f''-p''
    tree_diff2->child2 = convert_poly(1,deg_diff2, temp_diff2, monomials_diff2, prec);

    // Searching the zeros of f'-p'
    crash_report = 0;
    x = quickFindZeros(tree_diff, tree_diff2, deg,a,b,prec,&crash_report);
    if (crash_report == -1) {
      free_memory(tree);
      free_memory(tree_diff);
      free_memory(tree_diff2);
      freeChain(monomials_diff,freeIntPtr);
      freeChain(monomials_diff2,freeIntPtr);
      avma = ltop;
      return copyTree(func);
    }

    // DEBUG
    printMessage(4,"Step %d ; quality of the approximation : %e. Computed value of epsilon : ",test,computeRatio(tree, x, prec)); 
    if (verbosity >= 4) {
      output((GEN)(temp[deg+2]));
      struct chainStruct c = {tree,NULL};
      plotTree(&c,a,b,500,prec,NULL,0);
      //printTree(tree);
      //for(i=0;i<100000;i++){}
    }

    test++;
    if (computeRatio(tree, x, prec)<0.0001) {
      test = 0;
      res = copyTree(tree->child2);
    }

    //allocatemoremem(0);

    free_memory(tree_diff2->child2);
    free_memory(tree_diff->child2);
    free_memory(tree->child2);
  }

  free_memory(tree_diff2->child1);
  free_memory(tree_diff->child1);
  free_memory(tree->child1);
  free(tree);
  free(tree_diff);
  free(tree_diff2);
  freeChain(monomials_diff,freeIntPtr);
  freeChain(monomials_diff2,freeIntPtr);
  avma = ltop;
  return res;
}
