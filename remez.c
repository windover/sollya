#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "expression.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>



// Aucune gestion des NaN, Inf, et dénormalisés.
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

  setexpo(res,prec+e-1);
  setsigne(res,s);

  mpz_clear(m);
  return res;
}


// Aucune gestion des NaN, Inf, et dénormalisés.
// Pas de gestion du type de x : il faut que ce soit un t_REAL
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


// Convertit un tableau [a0,..,an] de PARI REAL_t
// en un arbre représentant le polynôme sum(ai*x^i)
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

node* remez(node *func, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  ulong lbot, ltop=avma;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j;
  GEN u, v, x, temp, M;
  node *tree;

  u = mpfr_to_PARI(a);
  v = mpfr_to_PARI(b);

  
  // Définition du vecteur x de n+2 points de Chebychev
  x = cgetg(deg+3,t_COL);
  for (i=0;i<deg+2;i++) {
    x[i+1] = lsub(gdivgs(gadd(u,v),2),
		  gmul(gdivgs(gsub(v,u),2),
		       gcos(gdivgs(gmulgs(mppi(prec_pari),2*i+1),
				   2*deg+4),prec_pari)
		       )
		  );
  }
  
  
  // Définition de la matrice M de Remez associée aux points x_i
  temp = cgetg(deg+3, t_COL);
  for (i=0;i<deg+2;i++) {
    temp[i+1] = lcopy(gun);
  }
  M = cgetg(deg+3,t_MAT);
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


  // Définition du vecteur f(x)
  for(i=0;i<deg+2;i++) {
    temp[i+1] = (long)evaluate_to_PARI(func, (GEN)(x[i+1]), prec);
  }

  // Résolution du système
  temp = gauss(M,temp);

  // Construction de la fonction f-p
  tree = malloc(sizeof(node));
  tree->nodeType = SUB;
  tree->child1 = copyTree(func);
  tree->child2 = convert_poly(1,deg+1, temp, prec);

  // DEBUG
  printf(" La matrice M calculée est : ");output(M);printf("\n");
  printf(" Le vecteur solution est : ");output(temp);printf("\n");
  printf(" La fonction à optimiser est : ");printTree(tree);printf("\n");
  return func;


  /*  mpfr_t x,y;
  mpfr_init2(x,prec);
  mpfr_init2(y,prec);
  mpfr_set(x,a,GMP_RNDN);
  mpfr_set(y,b,GMP_RNDN);
  printf("Invoked remez with degree %d on range [",deg);
  printValue(&x,prec);
  printf(";");
  printValue(&y,prec);
  printf("]\n");
  mpfr_clear(x);
  mpfr_clear(y);
  return copyTree(func);*/
}



