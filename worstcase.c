#include <mpfr.h>
#include <gmp.h>
#include "worstcase.h"
#include <stdio.h> /* fprinft, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <string.h>
#include <errno.h>
#include "main.h"
#include "infnorm.h"
#include "double.h"

int mpfrToInt(int *res, mpfr_t val) {
  mpfr_t verg;


  if (!mpfr_integer_p(val)) {
    printMessage(1,"Warning: an expression given in this context does not evaluate to integer.\n");
    *res = 0;
    return 0;
  }

  *res = mpfr_get_si(val,GMP_RNDN);
  
  mpfr_init2(verg,mpfr_get_prec(val));

  if (mpfr_set_si(verg,*res,GMP_RNDN) != 0) {
    printMessage(1,"Warning: rounding occured on reconverting back an integer variable.\n");
    *res = 0;
    mpfr_clear(verg);
    return 0;
  }

  if (mpfr_cmp(verg,val) != 0) {
    printMessage(1,"Warning: an expression given in this context does not evaluate to a machine integer.\n");
    *res = 0;
    mpfr_clear(verg);
    return 0;
  }

  mpfr_clear(verg);
  return 1;
}


void printWorstCases(node *func, 
		     mpfr_t inputprec, rangetype inputExponRange, 
		     mpfr_t outputprec, mpfr_t epsilon, mp_prec_t prec, FILE *fd) {
  int inputprecision, outputprecision, firstexponent, lastexponent;
  mpfr_t temp, temp2, x, y, yR, xL;
  double eps;
  long long int i;

  printf("prec = %d\n",(int) prec);

  if (!(mpfrToInt(&inputprecision, inputprec) &&
	mpfrToInt(&outputprecision, outputprec) &&
	mpfrToInt(&firstexponent, *(inputExponRange.a)) &&
	mpfrToInt(&lastexponent, *(inputExponRange.b)))) {
    printMessage(1,"Warning: an error occured. The last command will not succeed. This is harmless.\n");
    return;
  }

  if ((inputprecision < 10) || (outputprecision < 10)) {
    printMessage(1,"Warning: input and outputprecision must be greater or equal to 10.\n");
    printMessage(1,"Warning: an error occured. The last command will not succeed. This is harmless.\n");
    return;
  }

  if ((prec < (mp_prec_t) inputprecision) || (prec < (mp_prec_t) outputprecision)) {
    printMessage(1,"Warning: the internal precision is less than the input or output precision.\n");
    printMessage(1,"Try to increase the tool's precision.\n");
    printMessage(1,"Warning: an error occured. The last command will not succeed. This is harmless.\n");
    return;
  }

  mpfr_init2(temp,prec);
  mpfr_init2(temp2,prec);

  mpfr_mul_2ui(temp,epsilon,(unsigned int) (outputprecision + 1),GMP_RNDN);
  mpfr_set_d(temp2,1.0,GMP_RNDN);

  if (mpfr_cmp(temp,temp2) >= 0) {
    printMessage(1,"Warning: the epsilon asked is greater than half an ulp of a %d bit format.\n",
		 outputprecision);
    printMessage(1,"Warning: an error occured. The last command will not succeed. This is harmless.\n");
    mpfr_clear(temp);
    mpfr_clear(temp2);
    return;
  }

  if (mpfr_sgn(epsilon) < 0) {
    printMessage(1,"Warning: the epsilon given is negative. Will take its abolute value.\n");
    mpfr_abs(epsilon,epsilon,GMP_RNDN);
  }

  mpfr_init2(x,inputprecision);
  mpfr_init2(xL,inputprecision);
  mpfr_init2(yR,outputprecision);
  mpfr_init2(y,prec);

  mpfr_set_d(x,1.0,GMP_RNDN);
  mpfr_mul_2si(x,x,firstexponent,GMP_RNDN);

  mpfr_set_d(xL,1.0,GMP_RNDN);
  mpfr_mul_2si(xL,xL,lastexponent-1,GMP_RNDN);
  mpfr_nextbelow(x);

  if (mpfr_cmp(x,xL) > 0) {
    mpfr_swap(x,xL);
  }


  i = 0;
  while (mpfr_cmp(x,xL) <= 0) {
    if (verbosity >= 2) {
      if ((i % 1000) == 0) printMessage(2,"Information: %d cases handled.\n",i);
      i++;
    }

    mpfr_set(temp,x,GMP_RNDN);

    evaluate(y,func,temp,prec);

    mpfr_set(yR,y,GMP_RNDN);
    mpfr_sub(temp2,y,yR,GMP_RNDN);
    mpfr_abs(temp2,temp2,GMP_RNDN);
    if (mpfr_zero_p(y)) {
      printMessage(1,"Warning: the given function evaluates to 0 on ");
      if (verbosity >= 1) printValue(&x,mpfr_get_prec(x));
      printMessage(1,"\nThe rounding error will be considered as an absolute one.\n");
    } else {
      mpfr_div(temp2,temp2,y,GMP_RNDN);
    }
    
    if (mpfr_cmp(temp2,epsilon) <= 0) {
      printf("%s = ",variablename);
      printValue(&x,mpfr_get_prec(x));
      printf("\t\tf(%s) = ",variablename);
      printValue(&yR,mpfr_get_prec(yR));
      printf("\t\teps = ");
      printValue(&temp2,mpfr_get_prec(temp2));
      mpfr_log2(temp,temp2,GMP_RNDN);
      eps = mpfr_get_d(temp,GMP_RNDN);
      printf(" = 2^(%f) \n",eps);
      if (fd != NULL) {
	fprintf(fd,"%s = ",variablename);
	fprintValue(fd,x);
	fprintf(fd,"\tf(%s) = ",variablename);
	fprintValue(fd,yR);
	fprintf(fd,"\teps = ");
	fprintValue(fd,temp2);
	fprintf(fd," = 2^(%f) ",eps);
	if (mpfr_zero_p(y)) {
	  fprintf(fd,"ABSOLUTE");
	} 
	fprintf(fd,"\n");
      }
    }

    mpfr_nextabove(x);
  }  

  mpfr_clear(temp);
  mpfr_clear(temp2);
  mpfr_clear(x);
  mpfr_clear(xL);
  mpfr_clear(y);
  mpfr_clear(yR);
}


int searchGalValue(chain *funcs, mpfr_t foundValue, mpfr_t startValue, mp_prec_t searchPrec, int steps, 
		    chain *imageFormats, chain *epsilons, mp_prec_t prec) {
  mpfr_t currLeft, currRight;
  mpfr_t yCurrLeft, yCurrRight;
  mpfr_t yCurrLeftRound, yCurrRightRound;
  mpfr_t errorLeft, errorRight;
  mp_prec_t p;
  unsigned long long int t;
  int res;
  int numberFuncs, numberFormats, numberEpsilons;
  chain *myFuncs;
  chain *currFunc, *currFormat, *currEpsilon;

  if (steps > 63) {
    printMessage(1,"Warning: cannot perform more than 63 steps. Will decrease step number to 63.\n");
    steps = 63;
  }

  p = prec;
  if (searchPrec > p) p = searchPrec;
  if (p < 165) p = 165;

  if (mpfr_get_prec(foundValue) < searchPrec) {
    printMessage(1,"Warning: the search precision is higher than the current precision of the tool.\nNo search is possible.\n");
    return 0;
  }

  numberFuncs = lengthChain(funcs);
  numberFormats = lengthChain(imageFormats);
  numberEpsilons = lengthChain(epsilons);

  if ((numberFuncs != numberFormats) ||
      (numberFuncs != numberEpsilons)) {
    printMessage(1,"Warning: the numbers of the given functions, formats and accuracies differ.\nNo search is possible.\n");
    return 0;
  }

  myFuncs = copyChain(funcs, copyTreeOnVoid);
 
  mpfr_init2(currLeft, searchPrec);
  mpfr_init2(currRight, searchPrec);
  mpfr_init2(yCurrLeft, p);
  mpfr_init2(yCurrRight, p);
  mpfr_init2(yCurrLeftRound, p);
  mpfr_init2(yCurrRightRound, p);
  mpfr_init2(errorLeft, p);
  mpfr_init2(errorRight, p);


  if ((mpfr_set(currLeft,startValue,GMP_RNDN) != 0) ||
      (mpfr_set(currRight,startValue,GMP_RNDN) != 0)) {
    printMessage(1,"Warning: the given start point is too precise for the given search precision.\n");
    printMessage(1,"It has been rounded to: ");
    if (verbosity >= 1) {
      printMpfr(currLeft);
    }
  }

  t = 1;
  t <<= steps;
  while (t > 0) {
    res = 1;
    currFunc = myFuncs;
    currFormat = imageFormats;
    currEpsilon = epsilons;
    while ((currFunc != NULL) && (currFormat != NULL) && (currEpsilon != NULL)) {
      evaluateFaithful(yCurrLeft, (node *) (currFunc->value), currLeft, p);
      mpfr_round_to_format(yCurrLeftRound, yCurrLeft, *((int *) (currFormat->value)));
      mpfr_sub(errorLeft,yCurrLeftRound,yCurrLeft,GMP_RNDN);
      mpfr_div(errorLeft,errorLeft,yCurrLeft,GMP_RNDN);
      if (!(mpfr_number_p(errorLeft) && (mpfr_cmpabs(errorLeft,*((mpfr_t *) (currEpsilon->value))) <= 0))) {
	res = 0;
	break;
      }
      currFunc = currFunc->next;
      currFormat = currFormat->next;
      currEpsilon = currEpsilon->next;
    }
    if (res) {
      mpfr_set(foundValue,currLeft,GMP_RNDN);
      break;
    }
    res = 1;
    currFunc = myFuncs;
    currFormat = imageFormats;
    currEpsilon = epsilons;
    while ((currFunc != NULL) && (currFormat != NULL) && (currEpsilon != NULL)) {
      evaluateFaithful(yCurrRight, (node *) (currFunc->value), currRight, p);
      mpfr_round_to_format(yCurrRightRound, yCurrRight, *((int *) (currFormat->value)));
      mpfr_sub(errorRight,yCurrRightRound,yCurrRight,GMP_RNDN);
      mpfr_div(errorRight,errorRight,yCurrRight,GMP_RNDN);
      if (!(mpfr_number_p(errorRight) && (mpfr_cmpabs(errorRight,*((mpfr_t *) (currEpsilon->value))) <= 0))) {
	res = 0;
	break;
      }
      currFunc = currFunc->next;
      currFormat = currFormat->next;
      currEpsilon = currEpsilon->next;
    }
    if (res) {
      mpfr_set(foundValue,currRight,GMP_RNDN);
      break;
    }
    mpfr_nextbelow(currLeft);
    mpfr_nextabove(currRight);
    t--;
  }
  
  mpfr_clear(currLeft);
  mpfr_clear(currRight);
  mpfr_clear(yCurrLeft);
  mpfr_clear(yCurrRight);
  mpfr_clear(yCurrLeftRound);
  mpfr_clear(yCurrRightRound);
  mpfr_clear(errorLeft);
  mpfr_clear(errorRight);

  freeChain(myFuncs, freeMemoryOnVoid);

  return res;
}
