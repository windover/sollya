#include <mpfr.h>
#include <gmp.h>
#include "proof.h"
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "infnorm.h"
#include "main.h"



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
  fprintf(fd,"Theorem %d:\nFor all %s in ",theo->number,variablename);
  fprintInterval(fd,*(theo->x));
  fprintf(fd,". ");
  fprintTree(fd,theo->function);
  fprintf(fd," is in ");
  fprintInterval(fd,*(theo->y));
  fprintf(fd,"\n");
}


int fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start) {
  int freeNumber; 

  freeNumber = numberExprBoundTheo(theo,start);
  fprintExprBoundTheoDoWork(fd, theo);
  return freeNumber;
}


int fprintEqualityTheo(FILE *fd, equalityTheo *theo, int start) {
  
  theo->number = start;
  fprintf(fd,"Theorem %d:\n",start);
  fprintTree(fd,theo->expr1);
  fprintf(fd," = ");
  fprintTree(fd,theo->expr2);
  fprintf(fd,"\n");
  return start+1;
}

void freeEqualityTheo(equalityTheo *theo) {
  free_memory(theo->expr1);
  free_memory(theo->expr2);
  free(theo);
}


int fprintNoZeroTheo(FILE *fd, noZeroTheo *theo, int start) {
  int nextNumber;
  chain *curr;

  nextNumber = start;

  nextNumber = fprintEqualityTheo(fd,theo->funcEqual,nextNumber);
  nextNumber = fprintEqualityTheo(fd,theo->derivEqual,nextNumber);

  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    nextNumber = fprintExprBoundTheo(fd,((exprBoundTheo *) (curr->value)),nextNumber);
    curr = curr->next;
  }

  theo->number = nextNumber;
  nextNumber++;

  fprintf(fd,"Theorem %d:\n",theo->number);
  fprintf(fd,"The function f(%s) = ",variablename);
  fprintTree(fd,theo->function);
  fprintf(fd," has no zeros in the following domain(s):\n");
  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    fprintInterval(fd,*(((exprBoundTheo *) (curr->value))->x));
    curr = curr->next;
  }
  fprintf(fd,"\n");

  return nextNumber;
}


void freeExprBoundTheoOnVoid(void *theo) {
  freeExprBoundTheo((exprBoundTheo *) theo);
}

void freeNoZeroTheo(noZeroTheo *theo) {
  free_memory(theo->function);
  free_memory(theo->derivative);
  freeEqualityTheo(theo->funcEqual);
  freeEqualityTheo(theo->derivEqual);
  freeChain(theo->exprBoundTheos,freeExprBoundTheoOnVoid);
  free(theo);
}

int fprintInfnormTheo(FILE *fd, infnormTheo *theo, int start) {
  int nextNumber;
  chain *curr;

  nextNumber = start;
  nextNumber = fprintNoZeroTheo(fd,theo->noZeros,nextNumber);
  nextNumber = fprintExprBoundTheo(fd,theo->evalLeftBound,nextNumber);
  nextNumber = fprintExprBoundTheo(fd,theo->evalRightBound,nextNumber);

  curr = theo->evalOnZeros;
  while (curr != NULL) {
    nextNumber = fprintExprBoundTheo(fd,((exprBoundTheo *) (curr->value)),nextNumber);
    curr = curr->next;
  }

  theo->number = nextNumber;
  nextNumber++;

  fprintf(fd,"Theorem %d:\n",theo->number);
  fprintf(fd,"Let be f(%s) = ",variablename);
  fprintTree(fd,theo->function);
  fprintf(fd,"\nThe infinite norm of f(%s) for %s in ",variablename,variablename);
  fprintInterval(fd,*(theo->domain));
  fprintf(fd," ");
  if (theo->excludedIntervals != NULL) {
    fprintf(fd,"without the (union of the) following interval(s)\n");
    curr = theo->excludedIntervals;
    while (curr != NULL) {
      fprintInterval(fd,*((mpfi_t *) (curr->value)));
      fprintf(fd,"\n");
      curr = curr->next;
    }
  }
  fprintf(fd,"is bounded by ");
  fprintInterval(fd,*(theo->infnorm));
  fprintf(fd,"\n");

  return nextNumber;
}


void freeInfnormTheo(infnormTheo *theo) {
  free_memory(theo->function);
  freeMpfiPtr(theo->domain);
  freeMpfiPtr(theo->infnorm);
  free_memory(theo->derivative);
  free_memory(theo->numeratorOfDerivative);
  free_memory(theo->derivativeOfNumeratorOfDerivative);
  freeChain(theo->excludedIntervals,freeMpfiPtr);
  freeNoZeroTheo(theo->noZeros);
  freeExprBoundTheo(theo->evalLeftBound);
  freeExprBoundTheo(theo->evalRightBound);
  freeChain(theo->evalOnZeros,freeExprBoundTheoOnVoid);
  free(theo);
}
