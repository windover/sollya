#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "expression.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

void DEBUG(char *s) { printf(s); }

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


// Renvoie un vecteur contenant les zéros de tree sur [a;b]
// Les calculs sont effectués à la précsion prec.
// deg est une indication sur le nombre de zéros auquel s'attendre
GEN quickFindZeros(node *tree,int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  GEN res;
  long int n = 100*(deg+2);
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
	printf("The function oscillate too much. Nevertheless, we try to continue\n");
      else res[i] = (long)(mpfr_to_PARI(x1));
       
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_add(x2,x2,h,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    evaluate(y2, tree, x2, prec);
  }
  
  if (i<deg) printf("The function fails to oscillate enough. Good luck for you.\n");
  else {
    if (i==deg) { res[deg+1] = (long)(mpfr_to_PARI(a)); res[deg+2] = (long)(mpfr_to_PARI(b)); }
    else { // i = deg +1
      evaluate(y1, tree, a, prec);
      evaluate(y2, tree, b, prec);
      if (mpfr_greater_p(a,b)) res[deg+2] = (long)(mpfr_to_PARI(a));
      else res[deg+2] = (long)(mpfr_to_PARI(b));
    }
  }

  mpfr_clear(h); mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2);
  return sort(res);
}



double computeRatio(node *tree, GEN x, mp_prec_t prec) {
  int i;
  GEN min, max, temp;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;

  min = evaluate_to_PARI(tree, (GEN)(x[1]), prec);
  min = gabs(min,prec_pari);
  max = gcopy(min);

  for(i=0;i<lg(x)-1;i++) {
    temp = evaluate_to_PARI(tree, (GEN)(x[i+1]), prec);
    temp = gabs(temp,prec_pari);
    if (gcmp(min,temp)>0) min = temp;
    if (gcmp(temp,max)>0) max = temp;
  }

  return rtodbl(gdiv(gsub(max,min),min));
}



node* remez(node *func, int deg, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  ulong ltop=avma;
  long prec_pari = 2 + (prec + BITS_IN_LONG - 1)/BITS_IN_LONG;
  int i,j;
  GEN u, v, x, temp, temp_diff, M;
  node *tree;
  node *tree_diff;
  node *res;
  int test=1;

  u = mpfr_to_PARI(a);
  v = mpfr_to_PARI(b);

  // Définition du vecteur x de n+2 points de Chebychev
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

  // Boucle principale
  while(test) {

    // Définition de la matrice M de Remez associée aux points x_i
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
    
    
    // Définition du vecteur f(x)
    for(i=0;i<deg+2;i++) {
      temp[i+1] = (long)evaluate_to_PARI(func, (GEN)(x[i+1]), prec);
    }
    
    // Résolution du système
    temp = gauss(M,temp);

    // Dérivation formelle du polynôme contenu dans temp
    for(i=0;i<deg+2;i++) {
      temp_diff[i+1] = lmulrs((GEN)(temp[i+1]),(long)i);
    }
    
    // Construction de la fonction f'-p'
    tree_diff = malloc(sizeof(node));
    tree_diff->nodeType = SUB;
    tree_diff->child1 = differentiate(func);
    tree_diff->child2 = convert_poly(2,deg+1, temp_diff, prec);

    // Recherche des zéros de f'-p'
    x = quickFindZeros(tree_diff,deg,a,b,prec);

    // Construction de la fonction f-p
    tree = malloc(sizeof(node));
    tree->nodeType = SUB;
    tree->child1 = copyTree(func);
    tree->child2 = convert_poly(1,deg+1, temp, prec);

    printf("Étape n° %d\n",test);
    test++;
    if (computeRatio(tree, x, prec)<0.0001) {
      test = 0;
      res = copyTree(tree->child2);
    }

    free_memory(tree_diff);
    free_memory(tree);
  }

   avma = ltop;
   return res;
}
