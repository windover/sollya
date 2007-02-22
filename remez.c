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
#include "fpminimax.h"

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


// Convert an array [a0,..,an] of PARI REAL_t values
// into a tree representing the polynomial sum(ai*x^i)
node *simple_convert_poly(GEN tab, mp_prec_t prec) {
  node *tree;
  node *temp1;
  node *temp2;
  node *temp3;
  node *temp4;
  mpfr_t *value;
  GEN tab2;
  int i;
  if (itos((GEN)(matsize(tab)[1])) == 1) {
    tree = safeMalloc(sizeof(node));
    tree->nodeType = CONSTANT;
    value = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value, (GEN)(tab[1]), GMP_RNDN);
    tree->value = value;
  }
  else {
    tab2 = cgetg(itos((GEN)(matsize(tab)[1])), t_COL);
    for (i=1;i<=itos((GEN)(matsize(tab)[1]))-1;i++) {
      tab2[i] = tab[i+1];
    }

    temp1 = simple_convert_poly(tab2, prec);

    temp2 =  safeMalloc(sizeof(node));
    temp2->nodeType = CONSTANT;
    value = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value, (GEN)(tab[1]), GMP_RNDN);
    temp2->value = value;

    temp3 = safeMalloc(sizeof(node));
    temp3->nodeType = VARIABLE;

    temp4 = safeMalloc(sizeof(node));
    temp4->nodeType = MUL;
    temp4->child1 = temp3;
    temp4->child2 = temp1;

    tree = safeMalloc(sizeof(node));
    tree->nodeType = ADD;
    tree->child1 = temp2;
    tree->child2 = temp4;
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
    if (i==deg) { 
      res[deg+1] = (long)(mpfr_to_PARI(a));
      res[deg+2] = (long)(mpfr_to_PARI(b));
      res = sort(res);
    }
    else {
      if (i==deg +1) {
	evaluateFaithful(y1, tree, a, prec);
	evaluateFaithful(y2, tree, b, prec);
	if (mpfr_cmpabs(y1,y2)>=0) res[deg+2] = (long)(mpfr_to_PARI(a));
	else res[deg+2] = (long)(mpfr_to_PARI(b));
	res = sort(res);
      }
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2);
  return res;
}


chain *quickFindZeros2(node *tree, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  node *diff_tree;
  mpfr_t *x;
  int crash=0;
  int i;
  GEN list;
  chain *res=NULL;
  rangetype range;

  diff_tree = differentiate(tree);
  list = quickFindZeros(tree, diff_tree, deg, a, b, prec, &crash);
  if (crash) {
    range.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    range.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(range.a),prec);
    mpfr_init2(*(range.b),prec);
    mpfr_set(*(range.a),a,GMP_RNDD);
    mpfr_set(*(range.b),b,GMP_RNDU);
    res = fpFindZerosFunction(tree,range,prec);
    mpfr_clear(*(range.a));
    mpfr_clear(*(range.b));
    free(range.a);
    free(range.b);
  } else {
    for(i=1;i<=itos((GEN)(matsize(list)[1]));i++) {
      x = (mpfr_t *)safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*x,prec);
      PARI_to_mpfr(*x,(GEN)(list[i]),GMP_RNDN);
      res = addElement(res, x);
    }
  }
 
  free_memory(diff_tree);
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

GEN gMyadd(GEN x, GEN y) {
  if (gsigne(x) == 0) return y;
  //else...
  if(gsigne(y) == 0) return x;
  //else...
  return gadd(x,y);

}

GEN gMysub(GEN x, GEN y) {
  if (gsigne(x) == 0) return gneg(y);
  //else...
  if(gsigne(y) == 0) return x;
  //else...
  return gsub(x,y);
}

GEN Mypowgs(GEN x, long i) {
  if (gsigne(x) == 0) {
    if (i==0) return gun;
    else return gzero;
  }
  // else...
  return gpowgs(x,i);
}



// returns 1 if deg is sufficient to approximate rhe function to eps
// returns -1 if deg is not sufficient
// 0 if we cannot determine.
int whichPoly(int deg, node *func, node *weight, mpfr_t a, mpfr_t b, mpfr_t eps) {
  ulong ltop=avma;
  mp_prec_t prec = defaultprecision;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j, res;
  GEN x,u,v,M,temp;
  mpfr_t aprime, bprime;
  node *poly;
  node *tree;
  node *diff_tree;
  node *temp1;
  chain *list;
  chain *rememberList;
  rangetype range;
  mpfr_t y,min,max;
  mpfr_t mpfrTemp;
  mp_prec_t p;
  
  mpfr_init2(mpfrTemp,mpfr_get_prec(eps));
  mpfr_abs(mpfrTemp,eps,GMP_RNDN);
  mpfr_log2(mpfrTemp,mpfrTemp,GMP_RNDU);
  p = ((mp_prec_t) (-mpfr_get_si(mpfrTemp,GMP_RNDU))) + 10;
  mpfr_clear(mpfrTemp);
  
  if (p > prec) prec = p;

  mpfr_init2(aprime,prec);
  mpfr_init2(bprime,prec);
  mpfr_init2(y,53);
  mpfr_init2(min,53);
  mpfr_init2(max,53);

  mpfr_set_inf(min,1);
  mpfr_set_d(max,0.,GMP_RNDN);

  mpfr_set(aprime,a,GMP_RNDD);
  mpfr_set(bprime,b,GMP_RNDU);
  u = mpfr_to_PARI(aprime);
  v = mpfr_to_PARI(bprime);

  // Definition of the array x of the n+2 Chebychev points
  x = cgetg(deg+3, t_COL);
  for (i=0;i<deg+2;i++) {
    x[i+1] = lsub(gdivgs(gMyadd(u,v),2),
    		  gmul(gdivgs(gMysub(v,u),2),
    		       gcos(gdivgs(gmulgs(mppi(prec_pari),2*i+1),
    				   2*deg+4),prec_pari)
    		       )
    		  );
  }

  M = cgetg(deg+3,t_MAT);
  for(j=1;j<=deg+1;j++) {
    M[j] = (long)(cgetg(deg+3,t_COL));
    for(i=1;i<=deg+2;i++) {
      coeff(M,i,j) = lmul(Mypowgs((GEN)(x[i]),(long)(j-1)), evaluate_to_PARI(weight, (GEN)(x[i]), prec));
    }
  }
  M[deg+2] = (long)(cgetg(deg+3,t_COL));
  for(i=1;i<=deg+2;i++) {
    coeff(M,i,deg+2) = (long)stoi((i % 2)*2-1);
  }


  temp = cgetg(deg+3, t_COL);
  for (i=1;i<=deg+2;i++) {
    temp[i] = (long)evaluate_to_PARI(func,(GEN)x[i],prec);
  }

  // Solves the system
  temp = gauss(M,temp);
  x = cgetg(deg+2, t_COL);
  for (i=1;i<=deg+1;i++) {
    x[i] = temp[i];
  }

  poly = simple_convert_poly(x, prec);

  temp1 =  safeMalloc(sizeof(node));
  temp1->nodeType = MUL;
  temp1->child1 = poly;
  temp1->child2 = copyTree(weight);
  
  tree = safeMalloc(sizeof(node));
  tree->nodeType = SUB;
  tree->child1 = temp1;
  tree->child2 = copyTree(func);
  
  range.a = (mpfr_t *)(&aprime);
  range.b = (mpfr_t *)(&bprime);

  diff_tree = differentiate(tree);

  list = quickFindZeros2(diff_tree, deg, aprime, bprime, defaultprecision);
  free_memory(diff_tree);

  rememberList = list;
  while(list != NULL) {
    evaluateFaithful(y,tree,*(mpfr_t *)(list->value),prec);
    if(mpfr_cmpabs(y,min)<0) mpfr_set(min,y,GMP_RNDD);
    if(mpfr_cmpabs(y,max)>0) mpfr_set(max,y,GMP_RNDU);
    list = list->next;
  }

  freeChain(rememberList, freeMpfrPtr);

  evaluateFaithful(y,tree,aprime,prec);
  if(mpfr_cmpabs(y,min)<0) mpfr_set(min,y,GMP_RNDD);
  if(mpfr_cmpabs(y,max)>0) mpfr_set(max,y,GMP_RNDU);

  evaluateFaithful(y,tree,bprime,prec);
  if(mpfr_cmpabs(y,min)<0) mpfr_set(min,y,GMP_RNDD);
  if(mpfr_cmpabs(y,max)>0) mpfr_set(max,y,GMP_RNDU);
  
  mpfr_abs(min,min,GMP_RNDN);
  mpfr_abs(max,max,GMP_RNDN);
  if(mpfr_cmp(eps,max) >= 0) res=1;
  else {
    if(mpfr_cmp(eps,min) < 0) res=-1;
    else res=0;
  }

  mpfr_clear(aprime);
  mpfr_clear(bprime);
  mpfr_clear(y);
  mpfr_clear(min);
  mpfr_clear(max);
  free_memory(tree);

  avma = ltop;

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


node* remezWithWeight(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  ulong ltop=avma;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j,k;
  GEN u, v, x, y, wVector, temp, temp_diff, temp_diff2, M;
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
    x[i+1] = lsub(gdivgs(gMyadd(u,v),2),
    		  gmul(gdivgs(gMysub(v,u),2),
    		       gcos(gdivgs(gmulgs(mppi(prec_pari),2*i+1),
    				   2*deg+4),prec_pari)
    		       )
    		  );
    // To get evenly distributed points, choose the following points :
    // x[i+1] = ladd(u, gdivgs(gmulgs(gMysub(v,u),i),(deg+1)));
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
    
    printMessage(2,"Points:\n");
    if (verbosity >= 2) {
      for(i=0;i<deg+2;i++) {
	output((GEN)(x[i+1]));
      }
    }


    wVector = cgetg(deg+3, t_COL);
    if (weight!=NULL) {
      for(i=0;i<deg+2;i++) {
	wVector[i+1] = (long)evaluate_to_PARI(weight, (GEN)(x[i+1]), prec);
      }
    }
    else {
      for(i=0;i<deg+2;i++) {
	wVector[i+1] = (long)(gun);
      }
    }
    
    j=1;
    while(curr != NULL) {
      M[j] = lcopy(temp);
      for(i=0;i<=deg+1;i++) {
	coeff(M,i+1,j) = (long)mpmul((GEN)wVector[i+1],Mypowgs(gcoeff(M,i+1,j),(long)(*((int *)(curr->value)))));
      }
      
      j++;
      curr = curr->next;
    }
    for(i=0;i<deg+2;i++) {
      temp[i+1] = (long)stoi((i % 2)*2-1);
    }
    M[deg+2] = lcopy(temp);


    printMessage(3,"Matrix:\n");
    if (verbosity >= 3) {output(M);}


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
      j = *((int *)(curr->value));
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
    x = quickFindZeros(tree_diff, tree_diff2, deg,aprime,bprime,prec,&crash_report);
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
  mpfr_clear(aprime);
  mpfr_clear(bprime);
  return res;
}







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
  mpfr_t *mpfr_ptr;

  if (lengthChain(monomials) != itos((GEN)(matsize(coeff)[1]))) {
    fprintf(stderr,"Error : inconsistant lengths in function constructPolynomial.\n");
    recoverFromError();
  }

  poly =  safeMalloc(sizeof(node));
  poly->nodeType = CONSTANT;
  mpfr_ptr = safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*mpfr_ptr, prec);
  mpfr_set_d(*mpfr_ptr, 0., GMP_RNDN);
  poly->value = mpfr_ptr;

  curr = monomials;
  while(curr != NULL) {
    temp1 = safeMalloc(sizeof(node));
    temp1->nodeType = ADD;

    temp2 = safeMalloc(sizeof(node));
    temp2->nodeType = MUL;

    temp3 = safeMalloc(sizeof(node));
    temp3->nodeType = CONSTANT;
    mpfr_ptr = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_ptr, prec);
    PARI_to_mpfr(*mpfr_ptr, (GEN)(coeff[i]), GMP_RNDN);
    temp3->value = mpfr_ptr;

    temp4 = safeMalloc(sizeof(node));
    temp4->nodeType = POW;

    temp5 = safeMalloc(sizeof(node));
    temp5->nodeType = VARIABLE;

    temp6 = safeMalloc(sizeof(node));
    temp6->nodeType = CONSTANT;
    mpfr_ptr = safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_ptr, prec);
    mpfr_set(*mpfr_ptr, *((mpfr_t *)(curr->value)), GMP_RNDN);
    temp6->value = mpfr_ptr;

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


// This function finds the local extrema of a the error function poly*w-f.
// It uses the derivative and the second derivative of these functions to
// search the zeros of (poly*w-f)' by Newton's algorithm
// It expects to find at least freeDegrees+1 alternates extrema and
// returns it as a result. An intial estimation of these points is given
// in the vector x.
// Moreover, the quality of the approximation
// (defined by abs(err_max)/abs(err_min) - 1 where err_min and err_max 
// denote the minimal and maximal extrema in absolute value) is stored
// in computedQuality.
GEN qualityOfError(mpfr_t computedQuality, GEN x,
		   node *poly, node *poly_diff, node *poly_diff2,
		   node *f, node *f_diff, node *f_diff2,
		   node *w, node *w_diff, node *w_diff2,
		   int freeDegrees, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  /*  int i, s, n, test;
  mpfr_t var1, dummy_mpfr;
  mpfr_t *y;
  node *err_diff;
  node *err_diff2;
  node *temp1;
  node *temp2;
  node *temp3;

  mpfr_init2(var1, prec);
  mpfr_init2(dummy_mpfr, 5);

  // Construction of the trees corresponding to (poly*w-f)' and (poly*w-f)''
  err_diff = safeMalloc(sizeof(node));
  err_diff->nodeType = SUB;
  temp1 = safeMalloc(sizeof(node));
  temp1->nodeType = ADD;
  temp2 = safeMalloc(sizeof(node));
  temp2->nodeType = MUL;
  temp3 = safeMalloc(sizeof(node));
  temp3->nodeType = MUL;

  temp3->child1 = poly_diff;
  temp3->child2 = w;
  temp2->child1 = poly;
  temp2->child2 = w_diff;
  temp1->child1 = temp3;
  temp1->child2 = temp2;
  err_diff->child1 = temp1
  err_diff->child2 = f_diff;

  err_diff2 = differentiate(err_diff);
  

  // If x = [x1 ... xn], we construct [y0 y1 ... yn] by
  // y0 = a, yn = b and yi = (xi + x(i+1))/2
  n = itos((GEN)(matsize(coeff)[1]));
  y = (mpfr_t *)safeMalloc((n+1)*sizeof(mpfr_t));
  mpfr_init2(y[0], prec);
  mpfr_set(y[0], a, GMP_RNDN);
  for(i=1; i<n; i++) {
    mpfr_init2(y[i], prec);
    PARI_to_mpfr(var1, (GEN)(x[i]));
    PARI_to_mpfr(y[i], (GEN)(x[i+1]));
    mpfr_add(y[i], var1, y[i], GMP_RNDN);
    mpfr_div_2ui(y[i], y[i], 1, GMP_RNDN);
  }
  mpfr_init2(y[n], prec);
  mpfr_set(y[n], n, GMP_RNDN);
  

  // Tests if we can say that there is at least one zero between each y[i]
  s = 0;
  test = 1;
  i=0;
  mpfr_set_d(var1, 0., GMP_RNDN);

  while(test && i<=n) {
    if(evaluateFaithfulWithCutOffFast(dummy_mpfr, err_diff, err_diff2, y[0], var1, prec)) {
      // we may assume that err_diff(y[i]) == 0
    }
    else { 
      if( (s<0 && mpfr_sgn(dummy_mpfr)<0) || (s>0 && mpfr_sgn(dummy_mpfr)>0) ) test=0;
    i++;
    }
*/

  node *error;
  node *error_diff;
  node *error_diff2;
  node *temp1;
  GEN y;
  int crash_report=0;
  int i,n;
  mpfr_t var, max_val, min_val;

  mpfr_init2(var, prec);
  mpfr_init2(max_val, prec);
  mpfr_init2(min_val, prec);

  mpfr_set_d(max_val, 0., GMP_RNDN);
  mpfr_set_inf(min_val, 1);

  safeMalloc(sizeof(node));
  error->nodeType = SUB;
  temp1 = safeMalloc(sizeof(node));
  temp1->nodeType = MUL;
  temp1->child1 = poly;
  temp1->child2 = w;
  error->child1 = temp1;
  error->child2 = f;

  error_diff = differentiate(error);
  error_diff2 = differentiate(error_diff);

  
  y = quickFindZeros(error_diff, error_diff2, freeDegrees-1, a, b, prec, &crash_report);
  if (crash_report == -1) {
    free_memory(error);
    free_memory(error_diff);
    free_memory(error_diff2);
    mpfr_clear(var);
    mpfr_clear(max_val);
    mpfr_clear(min_val);
    fprintf(stderr,"Error : in Remez, curves fails to oscillate sufficiently.");
    recoverFromError();
  }

  n = itos((GEN)(matsize(x)[1]));
  for(i=1;i<=n;i++) {
    PARI_to_mpfr(var, (GEN)y[i], GMP_RNDN);
    evaluateFaithful(var, error, var, prec);
    mpfr_abs(var, var, GMP_RNDN);
    if(mpfr_cmp(var, max_val) > 0) mpfr_set(max_val, var, GMP_RNDU);
    if(mpfr_cmp(var, min_val) < 0) mpfr_set(min_val, var, GMP_RNDD);
  }

  mpfr_div(var, max_val, min_val, GMP_RNDU);
  mpfr_sub_ui(var, var, 1, GMP_RNDU);
  mpfr_set(computedQuality, var, GMP_RNDU);

  free_memory(error);
  free_memory(error_diff);
  free_memory(error_diff2);
  mpfr_clear(var);
  mpfr_clear(max_val);
  mpfr_clear(min_val);
  return y;

}

node *newRemez(node *f, node *w, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec, mpfr_t quality) {
  ulong ltop=avma;
  int freeDegrees = lengthChain(monomials);
  int i,j;
  long exponent;
  GEN x, M, temp;
  mpfr_t var1, var2, var3, var4, computedQuality;
  node *temp_tree;
  node *poly;
  node *poly_diff;
  node *poly_diff2;
  node *f_diff;
  node *f_diff2;
  node *w_diff;
  node *w_diff2;
  chain *curr;

  // Initialisations and precomputations
  mpfr_init2(var1, prec);
  mpfr_init2(var2, prec);
  mpfr_init2(var3, prec);
  mpfr_init2(var4, prec);

  mpfr_init2(computedQuality, mpfr_get_prec(quality));
  mpfr_set_d(computedQuality, 1., GMP_RNDN);

  f_diff = differentiate(f);
  f_diff2 = differentiate(f_diff);
  w_diff = differentiate(w);
  w_diff2 = differentiate(w_diff);


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


  while(mpfr_cmp(computedQuality, quality)>1) {

    // Definition of the matrix M of Remez algorithm
    M = cgetg(freeDegrees+1, t_MAT);
    temp = cgetg(freeDegrees+1, t_COL);
    curr = monomials;
    for (j=1 ; j <= freeDegrees ; j++) {
      exponent = (long) (*((int *)(curr->value)));
      for (i=1 ; i <= freeDegrees+1 ; i++) {
	PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);
	evaluateFaithful(var2, w, var1, prec); // var2 = w(x[i])
	mpfr_pow_si(var1, var1, exponent, GMP_RNDN);
	mpfr_mul(var1, var1, var2, GMP_RNDN); // var1 = w(x[i])*x[i]^(curr->value)
	temp[i] = (long)(mpfr_to_PARI(var1));
      }
      M[j] = lcopy(temp);
      curr = curr->next;
    }
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      temp[i] = (long)stoi((i % 2)*2-1);  // temp = [1, -1, 1, -1 ... ]~
    }
    M[freeDegrees+1] = lcopy(temp);
    // Note that a simple optimization would be to precompute the w(x[i])
    // instead of computing it (freeDegrees+1) times
    
    
    // Determination of the polynomial corresponding to M and x
    for (i=1 ; i <= freeDegrees+1 ; i++) {
      PARI_to_mpfr(var1, (GEN)(x[i]), GMP_RNDN);
      evaluateFaithful(var1, f, var1, GMP_RNDN); // var1 = f(x[i])
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
    x = qualityOfError(computedQuality, x,
		       poly, poly_diff, poly_diff2,
		       f, f_diff, f_diff2,
		       w, w_diff, w_diff2,
		       freeDegrees, a, b, prec);

    free_memory(poly_diff);
    free_memory(poly_diff2);
  }

  
  mpfr_clear(var1);
  mpfr_clear(var2);
  mpfr_clear(var3);
  mpfr_clear(var4);
  mpfr_clear(computedQuality);
  free_memory(f_diff);
  free_memory(f_diff2);
  free_memory(w_diff);
  free_memory(w_diff2);

  avma=ltop;
  return poly;
}


node *remez(node *func, node *weight, chain *monomials, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  //  return remezWithWeight(func, NULL, monomials, a, b, prec);
  mpfr_t quality;
  node *res;
  mpfr_init2(quality, 53);
  mpfr_set_d(quality, 0.00001, GMP_RNDN);
  res = newRemez(func, weight, monomials, a, b, prec, quality);
  mpfr_clear(quality);
  return res;
}
