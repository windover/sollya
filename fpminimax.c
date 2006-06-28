#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "main.h"
#include "expression.h"
#include "chain.h"
#include "fpminimax.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>


void freeFormatTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((formatType *) ptr)->formatType == TI_FORMAT) {
    mpfr_clear(*(((formatType *) ptr)->tiValue));
    free(((formatType *) ptr)->tiValue);
  }
  free((formatType *) ptr);
}

void freeErrorTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((errorType *) ptr)->errorType == WEIGHTFUNCTION_ERROR) {
    free_memory(((errorType *) ptr)->weightFunction);
  }
  free((errorType *) ptr);
}

void freeMpfrPtr(void *ptr) {
  if (ptr == NULL) return;

  mpfr_clear(*((mpfr_t *) ptr));
  free((mpfr_t *) ptr);
}

void freePointsTypePtr(void *ptr) {

  if (ptr == NULL) return;

  if (((pointsType *) ptr)->pointsType == USER_POINTS) {
    freeChain(((pointsType *) ptr)->pointsList,freeMpfrPtr);
  }
  free((errorType *) ptr);
}




void affiche_format(formatType *f) {
  switch (f->formatType) {
  case DOUBLE_FORMAT:
    printf("D ");
    break;
  case DOUBLEDOUBLE_FORMAT:
    printf("DD ");
    break;
  case TRIPLEDOUBLE_FORMAT:
    printf("TD ");
    break;
  case PRECISION_FORMAT:
    printf("%d ",f->prec);
    break;
  case MI_FORMAT:
    printf("%d ",f->prec);
    break;
  case TI_FORMAT:
    printValue(f->tiValue,50);
    printf(" ");
    break;
  default:
    printf("Urrglh ");
  }
}

node *fpminimax(node *expr, chain *monomials, chain *formats, mpfr_t a, mpfr_t b, 
		errorType *error, pointsType *points, int quality, FILE *fd) {

  /* Preconditions encore a tester sur les arguments:

     (i) Il n'y a pas de doublons dans les monomes demandes (comme dans Remez)
     (ii) La fonction de poids est bien definie
     (iii) Le nombre de points donnes par l utilisateur est le bon
     
     Deja teste

     Le nombre de formats donnes est egal au nombre de monomes donnes.

  */
  chain *toto;
  mpfr_t titi;
  mpfr_init2(titi,tools_precision);

  printf("Fonction : ");
  printTree(expr);
  printf("\n");

  toto = monomials;
  printf("Monomials : ");
  while(toto!=NULL) {
    printf("%d ",*((int *)(toto->value)));
    toto = toto->next;
  }
  printf("\n");

  toto = formats;
  printf("Formats : ");
  while(toto!=NULL) {
    affiche_format((formatType *)(toto->value));
    toto = toto->next;
  }
  printf("\n");

  printf("a : ");
  mpfr_set(titi,a,GMP_RNDN);
  printValue(&titi,50);
  printf("\n");

  printf("b : ");
  mpfr_set(titi,b,GMP_RNDN);
  printValue(&titi,50);
  printf("\n");

  printf("Erreur : ");
  if (error==NULL) printf("default\n");
  else {
    switch (error->errorType) {
    case ABSOLUTE_ERROR:
      printf("absolute\n");
      break;
    case RELATIVE_ERROR:
      printf("relative\n");
      break;
    case WEIGHTFUNCTION_ERROR:
      printTree(error->weightFunction);
      printf("\n");
      break;
    default:
      printf("Urgglh\n");
    }
  }

  printf("Points : ");
  if (points==NULL) printf("default\n");
  else {
    switch (points->pointsType) {
    case EQUI_POINTS:
      printf("equi.\n");
      break;
    case CHEB_POINTS:
      printf("cheb.\n");
      break;
    case REMEZ_POINTS:
      printf("remez\n");
      break;
    case USER_POINTS:
      toto = points->pointsList;
      printf("user-defined : ");
      while(toto!=NULL) {
	printValue((mpfr_t *)(toto->value),50);
	printf(" ");
	toto = toto->next;
      }
      printf("\n");
      break;
    default:
      printf("Urgglh\n");
    }
  }

  printf("Quality :");
  if(quality<=0) printf("default\n");
  else printf("%d\n",quality);

  printf("File argument :");
  if(fd==NULL) printf("no file\n");
  else fprintf(fd,"Coucou\n");

  mpfr_clear(titi);
  return copyTree(expr);
}



