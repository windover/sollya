#include <mpfr.h>
#include <gmp.h>
#include "proof.h"
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "infnorm.h"

/*
  node *function;
  int functionType;
  mpfi_t *x;
  mpfi_t *boundLeft;
  mpfi_t *boundRight;
  mpfi_t *y;
  exprBoundTheo *theoLeft;
  exprBoundTheo *theoRight;
  int simplificationUsed;
  node *leftDerivative;
  node *rightDerivative;
  mpfi_t *xZ;
  mpfi_t *xMXZ;
  exprBoundTheo *theoLeftDeriv;
  exprBoundTheo *theoRightDeriv;
  mpfi_t *boundLeftDeriv;
  mpfi_t *boundRightDeriv;
  int number;
*/


void freeExprBoundTheo(exprBoundTheo *theo) {
  if (theo->function != NULL) {
    free_memory(theo->function);
  }
  if (theo->x != NULL) {
    mpfi_clear(*(theo->x));
    free(theo->x);
  }
  if (theo->boundLeft != NULL) {
    mpfi_clear(*(theo->boundLeft));
    free(theo->boundLeft);
  }
  if (theo->boundRight != NULL) {
    mpfi_clear(*(theo->boundRight));
    free(theo->boundRight);
  }
  if (theo->y != NULL) {
    mpfi_clear(*(theo->y));
    free(theo->y);
  }
  if (theo->theoLeft != NULL) {
    freeExprBoundTheo(theo->theoLeft);
  }
  if (theo->theoRight != NULL) {
    freeExprBoundTheo(theo->theoRight);
  }
  if (theo->xZ != NULL) {
    mpfi_clear(*(theo->xZ));
    free(theo->xZ);
  }
  if (theo->xMXZ != NULL) {
    mpfi_clear(*(theo->xMXZ));
    free(theo->xMXZ);
  }
  if (theo->leftDerivative != NULL) {
    free_memory(theo->leftDerivative);
  }
  if (theo->rightDerivative != NULL) {
    free_memory(theo->rightDerivative);
  }
  if (theo->theoLeftLinear != NULL) {
    freeExprBoundTheo(theo->theoLeftLinear);
  }
  if (theo->theoRightLinear != NULL) {
    freeExprBoundTheo(theo->theoRightLinear);
  }
  if (theo->theoLeftConstant != NULL) {
    freeExprBoundTheo(theo->theoLeftConstant);
  }
  if (theo->theoRightConstant != NULL) {
    freeExprBoundTheo(theo->theoRightConstant);
  }
  if (theo->boundLeftLinear != NULL) {
    mpfi_clear(*(theo->boundLeftLinear));
    free(theo->boundLeftLinear);
  }
  if (theo->boundRightLinear != NULL) {
    mpfi_clear(*(theo->boundRightLinear));
    free(theo->boundRightLinear);
  }
  if (theo->boundLeftConstant != NULL) {
    mpfi_clear(*(theo->boundLeftConstant));
    free(theo->boundLeftConstant);
  }
  if (theo->boundRightConstant != NULL) {
    mpfi_clear(*(theo->boundRightConstant));
    free(theo->boundRightConstant);
  }
  free(theo);
}


int numberExprBoundTheo(exprBoundTheo *theo, int start) {
  int s;

  s = start;
  if (theo->theoLeft != NULL) s = numberExprBoundTheo(theo->theoLeft,s);
  if (theo->theoRight != NULL) s = numberExprBoundTheo(theo->theoRight,s);
  if (theo->theoLeftConstant != NULL) s = numberExprBoundTheo(theo->theoLeftConstant,s);
  if (theo->theoRightConstant != NULL) s = numberExprBoundTheo(theo->theoRightConstant,s);
  if (theo->theoLeftLinear != NULL) s = numberExprBoundTheo(theo->theoLeftLinear,s);
  if (theo->theoRightLinear != NULL) s = numberExprBoundTheo(theo->theoRightLinear,s);
  theo->number = s;
  return s + 1;
}




void fprintExprBoundTheoDoWork(FILE *fd, exprBoundTheo *theo) {
  if (theo->theoLeft != NULL) fprintExprBoundTheoDoWork(fd,theo->theoLeft);
  if (theo->theoRight != NULL) fprintExprBoundTheoDoWork(fd,theo->theoRight);
  if (theo->theoLeftConstant != NULL) fprintExprBoundTheoDoWork(fd,theo->theoLeftConstant);
  if (theo->theoRightConstant != NULL) fprintExprBoundTheoDoWork(fd,theo->theoRightConstant);
  if (theo->theoLeftLinear != NULL) fprintExprBoundTheoDoWork(fd,theo->theoLeftLinear);
  if (theo->theoRightLinear != NULL) fprintExprBoundTheoDoWork(fd,theo->theoRightLinear);
  fprintf(fd,"Theorem %d:\nFor all x in ",theo->number);
  fprintInterval(fd,*(theo->x));
  fprintf(fd,". ");
  fprintTree(fd,theo->function);
  fprintf(fd," is in ");
  fprintInterval(fd,*(theo->y));
  fprintf(fd,"\n");
}


void fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start) {

  numberExprBoundTheo(theo,start);
  fprintExprBoundTheoDoWork(fd, theo);
}
