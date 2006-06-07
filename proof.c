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
  if (theo == NULL) return;
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

void nullifyExprBoundTheo(exprBoundTheo *theo) {
  theo->function = NULL;
  theo->functionType = 0;
  theo->x = NULL;
  theo->boundLeft = NULL;
  theo->boundRight = NULL;
  theo->y = NULL;
  theo->theoLeft = NULL;
  theo->theoRight = NULL;
  theo->simplificationUsed = 0;
  theo->leftDerivative = NULL;
  theo->rightDerivative = NULL;
  theo->xZ = NULL;
  theo->xMXZ = NULL;
  theo->theoLeftConstant = NULL;
  theo->theoRightConstant = NULL;
  theo->boundLeftConstant = NULL;
  theo->boundRightConstant = NULL;
  theo->theoLeftLinear = NULL;
  theo->theoRightLinear = NULL;
  theo->boundLeftLinear = NULL;
  theo->boundRightLinear = NULL;
  theo->number = 0;
}


int exprBoundTheoIsTrivial(exprBoundTheo *theo) {
  if (theo->function == NULL) return 0;
  if ((theo->function->nodeType == CONSTANT) || (theo->function->nodeType == VARIABLE)) return 1;
  return 0;
}



int fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start) {
  int nextnumber;
  
  if (theo == NULL) return start;

  if (exprBoundTheoIsTrivial(theo)) return start;

  nextnumber = start;
  if (theo->theoLeft != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeft,nextnumber);
  if (theo->theoRight != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRight,nextnumber);
  if (theo->theoLeftConstant != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeftConstant,nextnumber);
  if (theo->theoRightConstant != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRightConstant,nextnumber);
  if (theo->theoLeftLinear != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeftLinear, nextnumber);
  if (theo->theoRightLinear != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRightLinear,nextnumber);
  theo->number = nextnumber; nextnumber++; 
  fprintf(fd,"Theorem %d:\nFor all %s in ",theo->number,variablename);
  if (theo->x != NULL) fprintInterval(fd,*(theo->x));
  fprintf(fd,". ");
  fprintTree(fd,theo->function);
  fprintf(fd," is in ");
  if (theo->y != NULL) fprintInterval(fd,*(theo->y));
  fprintf(fd,"\n\nProof:\n");
  
  fprintf(fd,"ASSUME THIS !");

  fprintf(fd,"\n\n");
  return nextnumber;
}


int equalityTheoIsTrivial(equalityTheo *theo) {
  return isSyntacticallyEqual(theo->expr1,theo->expr2);
}

int fprintEqualityTheo(FILE *fd, equalityTheo *theo, int start) {

  if (theo == NULL) return start;
  
  if (equalityTheoIsTrivial(theo)) return start;

  theo->number = start;
  fprintf(fd,"Theorem %d:\n",start);
  fprintTree(fd,theo->expr1);
  fprintf(fd," = ");
  fprintTree(fd,theo->expr2);
  fprintf(fd,"\n\n");
  return start+1;
}

void freeEqualityTheo(equalityTheo *theo) {
  if (theo == NULL) return;
  free_memory(theo->expr1);
  free_memory(theo->expr2);
  free(theo);
}

void fprintDerivativeLemma(FILE *fd, node *func, node *deriv, int theoNumber, int subNumber) {
  if (func == NULL) return;
  if (deriv == NULL) return;
  
  fprintf(fd,"Lemma %d.%d:\n",theoNumber,subNumber);
  fprintf(fd,"The first derivative of\nf(%s) = ",variablename);
  fprintTree(fd,func);
  fprintf(fd,"\nwith respect to %s is\nf\'(%s) = ",variablename,variablename);
  fprintTree(fd,deriv);
  fprintf(fd,"\n\n");
}

  
void fprintNumeratorSufficesLemma(FILE *fd, node *func, node *numerator, int theoNumber, int subNumber) {
  if (func == NULL) return;
  if (numerator == NULL) return;
  
  fprintf(fd,"Lemma %d.%d:\n",theoNumber,subNumber);
  fprintf(fd,"The set of the zeros of the function\nf(%s) = ",variablename);
  fprintTree(fd,func);
  fprintf(fd,"\nis included in the set of the zeros of the function\ng(%s) = ",variablename);
  fprintTree(fd,numerator);
  fprintf(fd,"\n\n");
  fprintf(fd,"Proof:\n");
  if (func->nodeType == DIV) {
    fprintf(fd,"The function f(%s) is a fraction. The function g(%s) is the numerator of this fraction.\n",
	    variablename,variablename);
  } else {
    if (isSyntacticallyEqual(func,numerator)) 
      fprintf(fd,"The functions f(%s) and g(%s) are equal.\n",variablename,variablename);
    else 
      fprintf(fd,"The functions f(%s) and g(%s) can be shown to be equal.\n",variablename,variablename);
  }
  fprintf(fd,"\n");
}

int fprintNoZeroTheo(FILE *fd, noZeroTheo *theo, int start) {
  int nextNumber;
  chain *curr;

  if (theo == NULL) return start;

  nextNumber = start;

  nextNumber = fprintEqualityTheo(fd,theo->funcEqual,nextNumber);
  nextNumber = fprintEqualityTheo(fd,theo->derivEqual,nextNumber);

  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    nextNumber = fprintExprBoundTheo(fd,((exprBoundTheo *) (curr->value)),nextNumber);
    curr = curr->next;
  }

  theo->number = nextNumber;
  fprintDerivativeLemma(fd,theo->function,theo->derivative,theo->number,1);
  nextNumber++;

  fprintf(fd,"Theorem %d:\n",theo->number);
  fprintf(fd,"The function f(%s) = ",variablename);
  fprintTree(fd,theo->function);
  fprintf(fd," has no zeros in the following domain(s):\n");
  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    fprintInterval(fd,*(((exprBoundTheo *) (curr->value))->x));
    fprintf(fd,"\n");
    curr = curr->next;
  }
  fprintf(fd,"\n\n");
  fprintf(fd,"Proof:\n");
  fprintf(fd,"As per lemma %d.%d, the derivative of f(%s) is f\'(%s) = ",theo->number,1,variablename,variablename);
  fprintTree(fd,theo->derivative);
  fprintf(fd,".\n");
  if (!equalityTheoIsTrivial(theo->derivEqual)) {
    fprintf(fd,"As per theorem %d, f'(%s) can be written also ",theo->derivEqual->number,variablename);
    fprintTree(fd,theo->derivEqual->expr2);
    fprintf(fd,"\nIn the following assume this equality.\n");
  }
  if (!equalityTheoIsTrivial(theo->funcEqual)) {
    fprintf(fd,"As per theorem %d, f(%s) can be written also ",theo->funcEqual->number,variablename);
    fprintTree(fd,theo->funcEqual->expr2);
    fprintf(fd,"\nIn the following assume this equality.\n");
  }
  fprintf(fd,"Theorem(s) ");
  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    if ((curr->next == NULL) && (curr != theo->exprBoundTheos)) fprintf(fd,"and ");
    fprintf(fd,"%d",((exprBoundTheo *) (curr->value))->number);
    if (curr->next != NULL) fprintf(fd,", ");
    curr = curr->next;
  }
  fprintf(fd,"\nshow (using f'(%s)) that all images f(%s) for %s in one of the domains\n",
	  variablename,variablename,variablename);
  fprintf(fd,"given in this theorem are contained in (the union of) the following interval(s)\n");
  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    fprintInterval(fd,*(((exprBoundTheo *) (curr->value))->y));
    fprintf(fd,"\n");
    curr = curr->next;
  }
  fprintf(fd,"Clearly, none of these intervals (this interval) contains zero.\n");
  fprintf(fd,"Thus f(%s) has no zero in the given intervals.",variablename);
  fprintf(fd,"\n\n");
  return nextNumber;
}


void freeExprBoundTheoOnVoid(void *theo) {
  freeExprBoundTheo((exprBoundTheo *) theo);
}

void freeNoZeroTheo(noZeroTheo *theo) {
  if (theo == NULL) return;
  free_memory(theo->function);
  free_memory(theo->derivative);
  freeEqualityTheo(theo->funcEqual);
  freeEqualityTheo(theo->derivEqual);
  freeChain(theo->exprBoundTheos,freeExprBoundTheoOnVoid);
  free(theo);
}

void doNothing(void *arg) {
  return;
}

int fprintInfnormTheo(FILE *fd, infnormTheo *theo, int start) {
  int nextNumber;
  chain *curr, *zeroFree, *joinedZeroFree, *temp;

  if (theo == NULL) return start;

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
  fprintDerivativeLemma(fd,theo->function,theo->derivative,theo->number,1);
  fprintNumeratorSufficesLemma(fd,theo->derivative,theo->numeratorOfDerivative,theo->number,2);
  fprintDerivativeLemma(fd,theo->numeratorOfDerivative,theo->derivativeOfNumeratorOfDerivative,theo->number,3);
  nextNumber++;

  fprintf(fd,"Theorem %d:\n",theo->number);
  fprintf(fd,"Assuming that f is C^2, the infinite norm of\nf(%s) = ",variablename);
  fprintTree(fd,theo->function);
  fprintf(fd,"\nfor %s in ",variablename);
  if (theo->domain != NULL) fprintInterval(fd,*(theo->domain));
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
  if (theo->infnorm != NULL)  fprintInterval(fd,*(theo->infnorm));
  fprintf(fd,"\n\n");
  fprintf(fd,"Proof:\n");
  fprintf(fd,"As per lemma %d.%d, the derivative f'(%s) of the given function f(%s) is\nf'(%s) = ",
	  theo->number,1,variablename,variablename,variablename);
  fprintTree(fd,theo->derivative);
  fprintf(fd,
    ".\nLemma %d.%d shows that the set of the zeros of f'(%s), i.e. of the local extrema of f(%s) (since f is C^2), is a\n",
	  theo->number,2,variablename,variablename);
  fprintf(fd,"subset of the zeros of\ng(%s) = ",variablename);
  fprintTree(fd,theo->numeratorOfDerivative);
  fprintf(fd,".\nThe derivative of g(%s) is g'(%s) = ",variablename,variablename);
  fprintTree(fd,theo->derivativeOfNumeratorOfDerivative);
  fprintf(fd," as shown by lemma %d.%d.\n",theo->number,3);
  fprintf(fd,"As a consequence of theorem %d, g(%s) has no zero in the following domains:\n",
	  theo->noZeros->number,variablename);
  zeroFree = NULL;
  curr = theo->noZeros->exprBoundTheos;
  while (curr != NULL) {
    zeroFree = addElement(zeroFree,((exprBoundTheo *) (curr->value))->x);
    curr = curr->next;
  }
  temp = copyChain(zeroFree,copyMpfiPtr);
  freeChain(zeroFree,doNothing);
  zeroFree = temp;
  joinedZeroFree = joinAdjacentIntervalsMaximally(zeroFree);
  freeChain(zeroFree,freeMpfiPtr);
  curr = joinedZeroFree;
  while (curr != NULL) {
    fprintInterval(fd,*((mpfi_t *) (curr->value)));
    fprintf(fd,"\n");
    curr = curr->next;
  }
  freeChain(joinedZeroFree,freeMpfiPtr);
  fprintf(fd,"This intervals and the following\n");
  curr = theo->evalOnZeros;
  while (curr != NULL) {
    fprintInterval(fd,*(((exprBoundTheo *) (curr->value))->x));
    fprintf(fd,"\n");
    curr = curr->next;
  }
  fprintf(fd,"are a complete partitioning of the domain ");
  fprintInterval(fd,*(theo->domain));
  if (theo->excludedIntervals != NULL) {
    fprintf(fd," without the (union of the) following interval(s)\n");
    curr = theo->excludedIntervals;
    while (curr != NULL) {
      fprintInterval(fd,*((mpfi_t *) (curr->value)));
      fprintf(fd,"\n");
      curr = curr->next;
    }
  }
  fprintf(fd,".\n");


  fprintf(fd,"\n\n");
  return nextNumber;
}


void freeInfnormTheo(infnormTheo *theo) {
  if (theo == NULL) return;
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
