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


void doNothing(void *arg) {
  return;
}

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

void fprintDerivativeLemma(FILE *fd, node *func, node *deriv, int theoNumber, int subNumber) {
  int restoreNullPtr;
  char *var = "x";

  if (func == NULL) return;
  if (deriv == NULL) return;

  restoreNullPtr = 0;
  if (variablename == NULL) {
    variablename = var;
    restoreNullPtr = 1;
  }
  
  fprintf(fd,"Lemma %d.%d:\n",theoNumber,subNumber);
  fprintf(fd,"The first derivative of\nf(%s) = ",variablename);
  fprintTree(fd,func);
  fprintf(fd,"\nwith respect to %s is\nf\'(%s) = ",variablename,variablename);
  fprintTree(fd,deriv);
  fprintf(fd,"\n\n");

  if (restoreNullPtr) variablename = NULL;
}


int fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start) {
  int nextnumber, restoreNullPtr;
  char *var = "x";
  char *fx, *gx;
  
  if (theo == NULL) return start;

  if (exprBoundTheoIsTrivial(theo)) return start;

  restoreNullPtr = 0;
  if (variablename == NULL) {
    variablename = var;
    restoreNullPtr = 1;
  }

  nextnumber = start;
  if (theo->theoLeft != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeft,nextnumber);
  if (theo->theoRight != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRight,nextnumber);
  if (theo->theoLeftConstant != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeftConstant,nextnumber);
  if (theo->theoRightConstant != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRightConstant,nextnumber);
  if (theo->theoLeftLinear != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoLeftLinear, nextnumber);
  if (theo->theoRightLinear != NULL) nextnumber = fprintExprBoundTheo(fd,theo->theoRightLinear,nextnumber);
  theo->number = nextnumber; nextnumber++; 
  if (theo->simplificationUsed == TAYLOR) {
    fprintDerivativeLemma(fd, theo->function, theo->leftDerivative, theo->number, 1);
  }
  if ((theo->simplificationUsed == DECORRELATE) || 
      (theo->simplificationUsed == HOPITAL) ||
      (theo->simplificationUsed == HOPITAL_ON_POINT)) {
    fprintDerivativeLemma(fd, theo->theoLeft->function, theo->leftDerivative, theo->number, 1);
    fprintDerivativeLemma(fd, theo->theoRight->function, theo->rightDerivative, theo->number, 2);
  }
  
  fprintf(fd,"Theorem %d:\nFor all %s in ",theo->number,variablename);
  if (theo->x != NULL) fprintInterval(fd,*(theo->x));
  fprintf(fd,". ");
  fprintTree(fd,theo->function);
  fprintf(fd," is in ");
  if (theo->y != NULL) fprintInterval(fd,*(theo->y));
  fprintf(fd,"\nProof:\n");
  if (theo->functionType == POLYNOMIAL) {
    fprintf(fd,"The given expression is a polynomial. The given bound can be verified by the Gappa tool.\n");
  } else {
    switch (theo->simplificationUsed) {
    case TAYLOR:
      fprintf(fd,"Theorem %d shows that for all %s in the given domain the given expression is bounded by ",
	      theo->theoLeft->number, variablename);
      fprintInterval(fd,*(theo->boundLeft));
      fprintf(fd,".\nFurther lemma %d.%d shows that the derivative of the given expression is ",
	      theo->number,1);
      fprintTree(fd,theo->leftDerivative);
      fprintf(fd,".\nOn the given domain, the values taken by this derivative are bounded by ");
      fprintInterval(fd,*(theo->boundLeftLinear));
      if (!exprBoundTheoIsTrivial(theo->theoLeftLinear)) {
	fprintf(fd," as shown by theorem %d.\n",theo->theoLeftLinear->number);
      } else {
	fprintf(fd," as is trivially clear.\n");
      }
      fprintf(fd,"The (quasi-) point interval _xZ = ");
      fprintInterval(fd,*(theo->xZ));
      fprintf(fd,
	   " is contained in the given domain.\nFor values %s in this interval _xZ, the given expression is bounded by ",
	      variablename);
      fprintInterval(fd,*(theo->boundLeftConstant));
      if (!exprBoundTheoIsTrivial(theo->theoLeftConstant)) {
	fprintf(fd," as shown by theorem %d.\n",theo->theoLeftConstant->number);
      } else {
	fprintf(fd," as is trivially clear.\n");
      }
      fprintf(fd,"Let _X be the given domain. The interval evaluation of (_X - _xZ) is bounded by ");
      fprintInterval(fd,*(theo->xMXZ));
      fprintf(fd,".\nBy Taylor\'s theorem the given expression is therefore bounded by ");
      fprintInterval(fd,*(theo->boundRight));
      fprintf(fd,".\nThe bounding domain for the expression given in this theorem is the intersection of\n");
      fprintf(fd,"the bound obtained by directly bounding the expression given above and the bound by\n");
      fprintf(fd,"Taylor\'s theorem.\n");
      break;
    case DECORRELATE:
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintf(fd,"The given expression is of the form ");
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd,"\nwhere f(%s) = ",variablename);
      fprintTree(fd,theo->theoLeft->function);
      fprintf(fd,"\nand g(%s) = ",variablename);
      fprintTree(fd,theo->theoRight->function);
      if (!exprBoundTheoIsTrivial(theo->theoLeft)) {
	fprintf(fd,"\nAs per theorem %d, for %s in the given domain, f(%s) is bounded by ",
		theo->theoLeft->number,variablename,variablename);
      } else {
	fprintf(fd,"\nTrivially for %s in the given domain, f(%s) is bounded by ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundLeft));
      if (!exprBoundTheoIsTrivial(theo->theoRight)) {
	fprintf(fd,"\nAs per theorem %d, for %s in the given domain, g(%s) is bounded by ",
		theo->theoRight->number,variablename,variablename);
      } else {
	fprintf(fd,"\nTrivially for %s in the given domain, g(%s) is bounded by ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundRight));
      fprintf(fd,"\nAs shown by lemma %d.%d, the derivative of f(%s) is ",
	      theo->number,1,variablename);
      fprintTree(fd,theo->leftDerivative);
      fprintf(fd,"\nFurther by lemma %d.%d, we know that the derivative of g(%s) is ",
	      theo->number,2,variablename);
      fprintTree(fd,theo->rightDerivative);
      fprintf(fd,"\nThe (quasi-) point interval _xZ = ");
      fprintInterval(fd,*(theo->xZ));
      fprintf(fd," is contained in the given domain.\n");
      if (!exprBoundTheoIsTrivial(theo->theoLeftConstant)) {
	fprintf(fd,"As per theorem %d, for %s in this interval _xZ, f(%s) is bounded by\n_xC = ",
		theo->theoLeftConstant->number, variablename, variablename);
      } else {
	fprintf(fd,"Trivially, for %s in this interval _xZ, f(%s) is bounded by\n_xC = ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundLeftConstant));
      fprintf(fd,"\n");
      if (!exprBoundTheoIsTrivial(theo->theoRightConstant)) {
	fprintf(fd,"As per theorem %d, for %s in the interval _xZ, g(%s) is bounded by\n_yC = ",
		theo->theoRightConstant->number, variablename,variablename);
      } else {
	fprintf(fd,"Trivially, for %s in this interval _xZ, g(%s) is bounded by\n_yC = ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundRightConstant));
      fprintf(fd,".\nLet _X be the given domain. The interval evaluation of (_X - _xZ) gives ");
      fprintInterval(fd,*(theo->xMXZ));
      fprintf(fd,".\n");
      if (!exprBoundTheoIsTrivial(theo->theoLeftLinear)) {
	fprintf(fd,"As per theorem %d, for %s in the given domain, the derivative of f(%s) is bounded by\n_xL = ",
		theo->theoLeftLinear->number, variablename,variablename);
      } else {
	fprintf(fd,"Trivially, for %s in the given domain, the derivative of f(%s) is bounded by\n_xL = ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundLeftLinear));
      fprintf(fd,".\n");
      if (!exprBoundTheoIsTrivial(theo->theoRightLinear)) {
	fprintf(fd,"As per theorem %d, for %s in the given domain, the derivative of g(%s) is bounded by\n_yL = ",
		theo->theoRightLinear->number, variablename, variablename);
      } else {
	fprintf(fd,"Trivially, for %s in the given domain, the derivative of g(%s) is bounded by\n_yL = ",
		variablename,variablename);
      }
      fprintInterval(fd,*(theo->boundRightLinear));
      fprintf(fd,".\nUsing Taylor\'s theorem, one verifies that the images of the given expression, function in %s,\n",
	      variablename);
      fprintf(fd,"for %s in the given domain, are contained in the intersection of the interval evaluation of\n",
	      variablename);
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd," and of (");
      fprintHeadFunction(fd,theo->function,"_xC","_yC");
      fprintf(fd,") + (X - _xZ) * (");
      fprintHeadFunction(fd,theo->function,"_xL","_yL");
      fprintf(fd,").\nThey are therefore included in the bound\n");
      fprintInterval(fd,*(theo->y));
      fprintf(fd,"\nthat has had to be shown.\n");
      break;
    case HOPITAL_ON_POINT:
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintf(fd,"The given expression is of the form ");
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd,"\nwhere f(%s) = ",variablename);
      fprintTree(fd,theo->theoLeft->function);
      fprintf(fd,"\nand g(%s) = ",variablename);
      fprintTree(fd,theo->theoRight->function);
      if (!exprBoundTheoIsTrivial(theo->theoLeft)) {
	fprintf(fd,"As per theorem %d, ",theo->theoLeft->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"for all %s in the given domain, f(%s) is bounded by the point interval ",variablename,variablename);
      fprintInterval(fd,*(theo->boundLeft));
      fprintf(fd," and therefore constant zero.\n");
      if (!exprBoundTheoIsTrivial(theo->theoRight)) {
	fprintf(fd,"As per theorem %d, ",theo->theoRight->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"for all %s in the given domain, g(%s) is bounded by the point interval ",variablename,variablename);
      fprintInterval(fd,*(theo->boundLeft));
      fprintf(fd," and therefore constant zero, too.\nBy H�pital's rule, the given expression");
      fprintf(fd," is bounded by the interval division of boundings\n");
      fprintf(fd,"of the derivatives of the numerator f(%s) and denominator g(%s) of the given expression.\n",
	      variablename,variablename);
      fprintf(fd,"As per lemma %d.%d, the derivative of f(%s) is ",theo->number,1,variablename);
      fprintTree(fd,theo->leftDerivative);
      fprintf(fd,"As per lemma %d.%d, the derivative of g(%s) is ",theo->number,2,variablename);
      fprintTree(fd,theo->rightDerivative);
      if (!exprBoundTheoIsTrivial(theo->theoLeftLinear)) {
	fprintf(fd,"As shown by theorem %d, ",theo->theoLeftLinear->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"this derivative of f(%s) for %s in the given domain is bounded by ",variablename,variablename);
      fprintInterval(fd,*(theo->theoLeftLinear->y));
      fprintf(fd,".\n");
      if (!exprBoundTheoIsTrivial(theo->theoRightLinear)) {
	fprintf(fd,"As shown by theorem %d, ",theo->theoRightLinear->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"the given derivative of g(%s) for %s in the given domain is bounded by ",variablename,variablename);
      fprintInterval(fd,*(theo->theoRightLinear->y));
      fprintf(fd,".\n");
      fprintf(fd,"This yields to the following bound for the given expression with %s in the given domain: ",
	      variablename);
      fprintInterval(fd,*(theo->y));
      fprintf(fd,".\nThis is the bound that has had to be shown.\n");
      break;
    case NUMERATOR_IS_ZERO:
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintf(fd,"The given expression is of the form ");
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd,"\nwhere f(%s) = ",variablename);
      fprintTree(fd,theo->theoLeft->function);
      fprintf(fd,"\nand g(%s) is some function in %s.\n",variablename,variablename);
      if (exprBoundTheoIsTrivial(theo->theoLeft)) {
	fprintf(fd,"Trivially, ");
      } else {
	fprintf(fd,"As per theorem %d, ",theo->theoLeft->number);
      }
      fprintf(fd,"for %s in the given domain, f(%s) is in ",variablename,variablename);
      fprintInterval(fd,*(theo->boundLeft));
      fprintf(fd,", i.e. constant zero.\n");
      fprintf(fd,"Therefore the given expression is constant zero, i.e. bounded by ");
      fprintInterval(fd,*(theo->y));
      fprintf(fd,".\n");
      break;
    case HOPITAL:
      fprintf(fd,"The given expression is of the form ");
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintHeadFunction(fd,theo->function,fx,gx);
      fprintf(fd,"\nwhere f(%s) = ",variablename);
      fprintTree(fd,theo->theoLeft->function);
      fprintf(fd,"\nand g(%s) = ",variablename);
      fprintTree(fd,theo->theoRight->function);
      fprintf(fd,"\nLet _xZ be the point interval _xZ = ");
      fprintInterval(fd,*(theo->xZ));
      fprintf(fd,". This interval is contained in the given domain.\n");
      if (!exprBoundTheoIsTrivial(theo->theoLeftConstant)) {
	fprintf(fd,"As per theorem %d, ",theo->theoLeftConstant->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"the images of f(%s) for %s in _xZ are in the point interval [0;0].\n",
	      variablename,variablename);
      fprintf(fd,"f(%s) is therefore constant zero in this interval _xZ.\n", variablename);
      if (!exprBoundTheoIsTrivial(theo->theoRightConstant)) {
	fprintf(fd,"As per theorem %d, ",theo->theoRightConstant->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"the images of g(%s) for %s in _xZ are in the point interval [0;0].\n",
	      variablename,variablename);
      fprintf(fd,"g(%s) is therefore constant zero in this interval _xZ.\n", variablename);
      fprintf(fd,"H�pital's rule, i.e. a first order Taylor expansion of f(%s) and g(%s), can therefore\n",
	      variablename,variablename);
      fprintf(fd,"be used for bounding the given expression, which will be replaced by f'(%s)/g'(%s).\n",
	      variablename,variablename);
      fprintf(fd,"Lemma %d.%d shows that f'(%s) is\nf'(%s) = ",theo->number,1,variablename,variablename);
      fprintTree(fd,theo->leftDerivative);
      fprintf(fd,"\nLemma %d.%d shows that g'(%s) is\ng'(%s) = ",theo->number,2,variablename,variablename);
      fprintTree(fd,theo->rightDerivative);
      fprintf(fd,"\n");
      if (!exprBoundTheoIsTrivial(theo->theoLeftLinear)) {
	fprintf(fd,"As per theorem %d, ",theo->theoLeftLinear->number);
      } else {
	fprintf(fd,"Trivially, ");
      }
      fprintf(fd,"f'(%s)/g'(%s) is bounded by ",variablename,variablename);
      fprintInterval(fd,*(theo->boundLeftLinear));
      fprintf(fd,".\nThis is bound that has had to be proven.\n");
      free(fx);
      free(gx);
      break;
    case IMPLICATION:
      fprintf(fd,"The theorem is a direct consequence of theorem %d.\n",theo->theoLeft->number);
      break;
    default:
      fprintf(fd,"The given expression is of the form ");
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd,".\n");
      switch (arity(theo->function)) {
      case 1:
	if (!exprBoundTheoIsTrivial(theo->theoLeft)) {
	  fprintf(fd,"As per theorem %d, for %s in the given domain, f(%s) = ",
		  theo->theoLeft->number,variablename,variablename);
	  fprintTree(fd,theo->theoLeft->function);
	  fprintf(fd," is bounded by ");
	} else {
	  fprintf(fd,"For %s in the given domain, the value of f(%s) = ",variablename,variablename);
	  fprintTree(fd,theo->theoLeft->function);
	  fprintf(fd," is trivially bounded by ");
	}
	fprintInterval(fd,*(theo->boundLeft));
	fprintf(fd,"\nUsing this bound for the argument f(%s) of ",variablename);
	break;
      case 2:
	if (!exprBoundTheoIsTrivial(theo->theoLeft)) {
	  fprintf(fd,"As per theorem %d, for %s in the given domain, f(%s) = ",
		  theo->theoLeft->number,variablename,variablename);
	  fprintTree(fd,theo->theoLeft->function);
	  fprintf(fd," is bounded by ");
	} else {
	  fprintf(fd,"For %s in the given domain, the value of f(%s) = ",variablename,variablename);
	  fprintTree(fd,theo->theoLeft->function);
	  fprintf(fd," is trivially bounded by ");
	}
	fprintInterval(fd,*(theo->boundLeft));
	fprintf(fd,".\n");
	if (!exprBoundTheoIsTrivial(theo->theoRight)) {
	  fprintf(fd,"As per theorem %d, for %s in the given domain, g(%s) = ",
		  theo->theoRight->number,variablename,variablename);
	  fprintTree(fd,theo->theoRight->function);
	  fprintf(fd," is bounded by ");
	} else {
	  fprintf(fd,"For %s in the given domain, the value of g(%s)  = ",variablename,variablename);
	  fprintTree(fd,theo->theoRight->function);
	  fprintf(fd," is trivially bounded by ");
	}
	fprintInterval(fd,*(theo->boundRight));
	fprintf(fd,"\nUsing these bounds for the arguments f(%s) and g(%s) of ",variablename,variablename);
	break;
      default:
	fprintf(fd,"The expression is a constant. Its bounding is trivial. Using this constant value\n");
      }
      fx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      gx = (char *) safeCalloc(strlen(variablename)+4,sizeof(char));
      sprintf(fx,"f(%s)",variablename);
      sprintf(gx,"g(%s)",variablename);
      fprintHeadFunction(fd,theo->function,fx,gx);
      free(fx);
      free(gx);
      fprintf(fd,", one can show the given bound for the given function.\n");
    }
  }
  fprintf(fd,"\n");

  if (restoreNullPtr) {
    variablename = NULL;
  }

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


  
void fprintNumeratorSufficesLemma(FILE *fd, node *func, node *numerator, int theoNumber, int subNumber) {
  int restoreNullPtr;
  char *var = "x";
  
  if (func == NULL) return;
  if (numerator == NULL) return;

  restoreNullPtr = 0;
  if (variablename == NULL) {
    variablename = var;
    restoreNullPtr = 1;
  }

  
  fprintf(fd,"Lemma %d.%d:\n",theoNumber,subNumber);
  fprintf(fd,"The set of the zeros of the function\nf(%s) = ",variablename);
  fprintTree(fd,func);
  fprintf(fd,"\nis included in the set of the zeros of the function\ng(%s) = ",variablename);
  fprintTree(fd,numerator);
  fprintf(fd,"\n");
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

  if (restoreNullPtr) variablename = NULL;
}

int fprintNoZeroTheo(FILE *fd, noZeroTheo *theo, int start) {
  int nextNumber, restoreNullPtr;
  chain *curr, *zeroFree, *joinedZeroFree, *temp;
  char *var = "x";

  if (theo == NULL) return start;

  restoreNullPtr = 0;
  if (variablename == NULL) {
    variablename = var;
    restoreNullPtr = 1;
  }

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
  fprintf(fd,"Further, more strictly speaking, the function f(%s) has no zero in the following domains:\n",variablename);
  zeroFree = NULL;
  curr = theo->exprBoundTheos;
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
  fprintf(fd,"\n");
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
  fprintf(fd,"\nshow(s) (using f'(%s)) that all images f(%s) for %s in one of the domains\n",
	  variablename,variablename,variablename);
  fprintf(fd,"given in this theorem are contained in (the union of) the following interval(s)\n");
  curr = theo->exprBoundTheos;
  while (curr != NULL) {
    fprintInterval(fd,*(((exprBoundTheo *) (curr->value))->y));
    fprintf(fd,"\n");
    curr = curr->next;
  }
  fprintf(fd,"Clearly, none of these intervals (this interval) contains zero.\n");
  fprintf(fd,"Thus f(%s) has no zero in the given intervals.\n",variablename);
  fprintf(fd,"Concerning the second (shorter) list of intervals, on remarks that it is a union of the\n");
  fprintf(fd,"intervals in the first list.");
  fprintf(fd,"\n\n");

  if (restoreNullPtr) variablename = NULL;

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


int fprintInfnormTheo(FILE *fd, infnormTheo *theo, int start) {
  int nextNumber, innerLeftNumber, innerRightNumber, num, restoreNullPtr;
  chain *curr, *zeroFree, *joinedZeroFree, *temp;
  mpfr_t a, b, l, u, fr, fl, tl, tr;
  mp_prec_t p, prec;
  mpfi_t *currMpfi;
  char *var = "x";

  if (theo == NULL) return start;

  restoreNullPtr = 0;
  if (variablename == NULL) {
    variablename = var;
    restoreNullPtr = 1;
  }

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
  fprintf(fd,"\n");
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
  fprintf(fd,"As per theorem %d, g(%s) has no zero in the following domains:\n",
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
  fprintf(fd,"This intervals and the following, whose set will be notated Z,\n");
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
  fprintf(fd,".\nTheorems %d and %d show that the absolute value of f(%s) on the bounds of the given domain a = ",
	  theo->evalLeftBound->number, theo->evalRightBound->number, variablename);
  mpfr_init2(a,mpfi_get_prec(*(theo->domain)));
  mpfr_init2(b,mpfi_get_prec(*(theo->domain)));  
  mpfi_get_left(a,*(theo->domain));
  mpfi_get_right(b,*(theo->domain));
  fprintValue(fd,a);
  fprintf(fd," and b = ");
  fprintValue(fd,b);
  fprintf(fd,"\nis less than or equal to the upper bound u = ");
  mpfr_init2(u,mpfi_get_prec(*(theo->infnorm)));
  mpfr_init2(l,mpfi_get_prec(*(theo->infnorm)));  
  mpfi_get_left(l,*(theo->infnorm));
  mpfi_get_right(u,*(theo->infnorm));
  fprintValue(fd,u);
  fprintf(fd," given for the infinite norm.\nTheorem(s) ");
  curr = theo->evalOnZeros;
  while (curr != NULL) {
    if ((curr->next == NULL) && (curr != theo->evalOnZeros)) fprintf(fd,"and ");
    fprintf(fd,"%d",((exprBoundTheo *) (curr->value))->number);
    if (curr->next != NULL) fprintf(fd,", ");
    curr = curr->next;
  }
  fprintf(fd," show(s) using f'(%s) that the absolute value of f(%s) is less than or equal to this upper bound u\n",
	  variablename,variablename);
  fprintf(fd,"on all domains Z where g(%s) may have a zero, i.e. where f'(%s) may have a zero and f(%s) a local extremum.\n",
	  variablename, variablename,variablename);
  fprintf(fd,"Theorem %d shows that there are no other domains with zeros of f'(%s) and we have shown that\n",
	  theo->noZeros->number,variablename);
  fprintf(fd,"the partitioning is complete.\n");
  prec = mpfi_get_prec(*(theo->evalLeftBound->y));
  p = mpfi_get_prec(*(theo->evalRightBound->y));
  if (p > prec) prec = p;
  curr = theo->evalOnZeros;
  while (curr != NULL) {
    p = mpfi_get_prec(*(((exprBoundTheo *) (curr->value))->y));
    if (p > prec) prec = p;
    curr = curr->next;
  }
  mpfr_init2(fl,prec);
  mpfr_init2(fr,prec);
  mpfr_init2(tl,prec);
  mpfr_init2(tr,prec);
  mpfi_get_left(fr,*(theo->evalLeftBound->y));
  mpfi_get_right(fl,*(theo->evalLeftBound->y));
  innerLeftNumber = theo->evalLeftBound->number;
  innerRightNumber = theo->evalLeftBound->number;
  mpfi_get_left(tl,*(theo->evalRightBound->y));
  mpfi_get_right(tr,*(theo->evalRightBound->y));
  if (mpfr_less_p(tr,fl)) {
    mpfr_set(fl,tr,GMP_RNDN);
    innerLeftNumber = theo->evalRightBound->number;
  }
  if (mpfr_greater_p(tl,fr)) {
    mpfr_set(fr,tl,GMP_RNDN);
    innerRightNumber = theo->evalRightBound->number;
  }
  curr = theo->evalOnZeros;
  while (curr != NULL) {
    currMpfi = ((exprBoundTheo *) curr->value)->y;
    mpfi_get_left(tl,*currMpfi);
    mpfi_get_right(tr,*currMpfi);
    if (mpfr_less_p(tr,fl)) {
      mpfr_set(fl,tr,GMP_RNDN);
      innerLeftNumber = ((exprBoundTheo *) curr->value)->number;
    }
    if (mpfr_greater_p(tl,fr)) {
      mpfr_set(fr,tl,GMP_RNDN);
      innerRightNumber = ((exprBoundTheo *) curr->value)->number;
    } 
    curr = curr->next;
  }
  if (mpfr_greater_p(fl,fr)) {
    fprintf(fd,"Theorem %d shows that on a domain bound or a domain containing a zero of f'(%s)\n",
	    innerLeftNumber,variablename);
    fprintf(fd,"the value of f(%s) can principally be as great as ",variablename);
    fprintValue(fd,fl);
    fprintf(fd,".\nTheorem %d shows that on a domain bound or a domain containing a zero of f'(%s)\n",
	    innerRightNumber,variablename);
    fprintf(fd,"the value of f(%s) can principally as small as ",variablename);
    fprintValue(fd,fr);
    fprintf(fd,".\nThe lower bound for the infinite norm on f(%s) in the given domain l = ",variablename);
    fprintValue(fd,l);
    fprintf(fd," is therefore the best lower bound that can be shown in this proof.\n");
  } else {
    mpfr_neg(fl,fl,GMP_RNDN);
    if (mpfr_greater_p(fl,fr)) {
      mpfr_set(fr,fl,GMP_RNDN);
      num = innerLeftNumber;
    } else {
      num = innerRightNumber;
    }
    fprintf(fd,"Theorem %d shows that on a domain bound or a domain containing a zero of f'(%s)\n",
	    num,variablename);
    fprintf(fd,"the absolute value of f(%s) is not less than the lower bound l = ",variablename);
    fprintValue(fd,l);
    fprintf(fd," given for the infinite norm.");
  }
  fprintf(fd,"\n\n");
  mpfr_clear(a);
  mpfr_clear(b);
  mpfr_clear(u);
  mpfr_clear(l);
  mpfr_clear(fr);
  mpfr_clear(fl);
  mpfr_clear(tr);
  mpfr_clear(tl);

  if (restoreNullPtr) variablename = NULL;

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