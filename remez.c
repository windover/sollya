#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "expression.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

// NaN, Inf, and denormalized not handled.
GEN mpfr_to_PARI(mpfr_t x) {
  mp_exp_t e;
  mp_prec_t prec,q,r;
  mpz_t m;
  int s;
  GEN res;

  mpz_init(m);

  prec = mpfr_get_prec(x);
  s = mpfr_sgn(x);
  e = mpfr_get_z_exp(m,x);
  if (s<0) mpz_neg(m,m);
  r = prec % BITS_IN_LONG;
  q = prec/BITS_IN_LONG;
  if (r==0) { r = BITS_IN_LONG; q--; } 
  mpz_mul_2exp(m, m, BITS_IN_LONG-r);
  res = cgetr(q+3);
  mpz_export(&(res[2]),NULL,1,BITS_IN_LONG/8,0,0,m);

  if (prec+e-1 < -HIGHEXPOBIT) {
    setsigne(res,0);
    res[2]=0;
  }
  else {
    setexpo(res,prec+e-1);
    setsigne(res,s);
  }

  mpz_clear(m);
  return res;
}


// NaN, Inf, and denormalized not handled.
// No check of the type of x is made (t_REAL or t_INT)
void PARI_to_mpfr(mpfr_t y, GEN x, mp_rnd_t rnd) {
  long length;
  mpz_t m;
  int s;

  mpz_init(m);

  s = gsigne(x);
  length = lg(x)-2;
  mpz_import(m,length,1,BITS_IN_LONG/8,0,0,&(x[2]));

  mpfr_set_z(y,m,rnd);
  mpfr_set_exp(y,(mp_prec_t)(gexpo(x)+1));
  if (s<0) mpfr_neg(y,y,GMP_RNDN);

  mpz_clear(m);
  return;
}


GEN evaluate_to_PARI(node *tree, GEN x, mp_prec_t prec) {
  GEN res;
  mpfr_t res_mpfr, x_mpfr;
 
  mpfr_init2(x_mpfr, prec);
  mpfr_init2(res_mpfr, prec);

  PARI_to_mpfr(x_mpfr, x, GMP_RNDN);
  evaluate(res_mpfr, tree, x_mpfr, prec);
  res = mpfr_to_PARI(res_mpfr);

  mpfr_clear(x_mpfr);
  mpfr_clear(res_mpfr);
  return res;
}


// Convert an array [a0,..,an] of PARI REAL_t values
// into a tree representing the polynomial sum(ai*x^i)
node *convert_poly(int first_index, int last_index, GEN tab, mp_prec_t prec) {
  node *tree;
  node *temp1;
  node *temp2;
  mpfr_t *value;

  if (first_index == last_index) {
    tree = malloc(sizeof(node));
    tree->nodeType = CONSTANT;
    value = malloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value, (GEN)(tab[first_index]), GMP_RNDN);
    tree->value = value;
  }
  else {
    temp1 = convert_poly(first_index+1, last_index, tab, prec);

    temp2 = malloc(sizeof(node));
    temp2->nodeType = CONSTANT;
    value = malloc(sizeof(mpfr_t));
    mpfr_init2(*value, prec);
    PARI_to_mpfr(*value,(GEN)(tab[first_index]), GMP_RNDN);
    temp2->value = value;

    tree = malloc(sizeof(node));
    tree->nodeType = ADD;
    tree->child1 = temp2;

    temp2 = malloc(sizeof(node));
    temp2->nodeType = MUL;
    temp2->child2 = temp1;
    
    temp1 = malloc(sizeof(node));
    temp1->nodeType = VARIABLE;
    temp2->child1 = temp1;

    tree->child2 = temp2;
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
    evaluate(temp1, tree, x, prec);
    evaluate(temp2, diff_tree, x, prec);
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
  evaluate(y1, tree, x1, prec);
  evaluate(y2, tree, x2, prec);
  while(mpfr_lessequal_p(x2,b)) {
    if (mpfr_sgn(y1) != mpfr_sgn(y2)) {
      i++;
      if(i>deg+2)
	printf("The function oscillates too much. Nevertheless, we try to continue.\n");
      else res[i] = (long)(newton(tree, diff_tree, x1, x2, prec));       
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_add(x2,x2,h,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluate(y2, tree, x2, prec);
  }
  
  if (i<deg) {
    printf("The function fails to oscillate enough.\n");
    *crash_report = -1;
  }
  else {
    if (i==deg) { res[deg+1] = (long)(mpfr_to_PARI(a)); res[deg+2] = (long)(mpfr_to_PARI(b)); }
    else { // i = deg +1
      evaluate(y1, tree, a, prec);
      evaluate(y2, tree, b, prec);
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
  evaluate(min, tree, temp, prec);
  mpfr_abs(min,min,GMP_RNDN);
  mpfr_set(max,min,GMP_RNDN);

  for(i=0;i<lg(x)-1;i++) {
    PARI_to_mpfr(temp, (GEN)(x[i+1]), GMP_RNDN);
    evaluate(temp, tree, temp, prec);
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



node* remez(node *func, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  ulong ltop=avma;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j;
  GEN u, v, x, y, temp, temp_diff, temp_diff2, M;
  node *tree;
  node *tree_diff;
  node *tree_diff2;
  node *res;
  int test=1, crash_report;
  printf("Estimation of the necessary size : %lu\n",prec_pari*sizeof(long)*(deg+2)*(deg+10));

  tree = malloc(sizeof(node));
  tree->nodeType = SUB;
  tree->child1 = copyTree(func);

  tree_diff = malloc(sizeof(node));
  tree_diff->nodeType = SUB;
  tree_diff->child1 = differentiate(func);

  tree_diff2 = malloc(sizeof(node));
  tree_diff2->nodeType = SUB;
  tree_diff2->child1 = differentiate(tree_diff->child1);

  u = mpfr_to_PARI(a);
  v = mpfr_to_PARI(b);

  // Definition of the array x of the n+2 Chebychev points
  x = cgetg(deg+3, t_COL);
  for (i=0;i<deg+2;i++) {
    x[i+1] = lsub(gdivgs(gadd(u,v),2),
		  gmul(gdivgs(gsub(v,u),2),
		       gcos(gdivgs(gmulgs(mppi(prec_pari),2*i+1),
				   2*deg+4),prec_pari)
		       )
		  );
  }
  

  M = cgetg(deg+3,t_MAT);
  temp = cgetg(deg+3, t_COL);
  temp_diff = cgetg(deg+3, t_COL);
  temp_diff2 = cgetg(deg+3, t_COL);

  // Main loop
  while(test) {

    // Definition of the Remez matrix M with respect to the point x_i
    for (i=0;i<deg+2;i++) {
      temp[i+1] = lcopy(gun);
    }
    for(j=0;j<deg+1;j++) {
      M[j+1] = lcopy(temp);
      for(i=0;i<deg+2;i++) {
	temp[i+1] = lmul((GEN)temp[i+1],(GEN)x[i+1]);
      }
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
    for(i=0;i<deg+1;i++) {
      temp_diff[i+1] = lmulrs((GEN)(temp[i+1]),(long)i);
    }
    
    // Formally derive the polynomial stored in temp_diff
    for(i=0;i<deg;i++) {
      temp_diff2[i+2] = lmulrs((GEN)(temp_diff[i+2]),(long)i);
    }

    // Construction of the function f-p
    tree->child2 = convert_poly(1,deg+1, temp, prec);

    // Construction of the function f'-p'
    tree_diff->child2 = convert_poly(2,deg+1, temp_diff, prec);

    // Construction of the function f''-p''
    tree_diff2->child2 = convert_poly(3,deg+1, temp_diff2, prec);

    // Searching the zeros of f'-p'
    crash_report = 0;
    x = quickFindZeros(tree_diff, tree_diff2, deg,a,b,prec,&crash_report);
    if (crash_report == -1) {
      free_memory(tree);
      free_memory(tree_diff);
      free_memory(tree_diff2);
      avma = ltop;
      return copyTree(func);
    }

    // DEBUG
    printf("Step %d ; quality of the approximation : %e. Computed value of epsilon : ",test,computeRatio(tree, x, prec));output((GEN)(temp[i+2]));
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
  avma = ltop;
  return res;
}
