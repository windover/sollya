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




node *fpminimax(node *expr, chain *monomials, chain *formats, mpfr_t a, mpfr_t b, 
		errorType *error, pointsType *points, int quality, FILE *fd) {

  /* Preconditions encore a tester sur les arguments:

     (i) Il n'y a pas de doublons dans les monomes demandes (comme dans Remez)
     (ii) La fonction de poids est bien definie
     (iii) Le nombre de points donnes par l utilisateur est le bon
     
     Deja teste

     Le nombre de formats donnes est egal au nombre de monomes donnes.

  */



  return copyTree(expr);
}



