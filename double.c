#include <gmp.h>
#include <mpfr.h>
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include "expression.h"
#include "double.h"
#include "main.h"
#include "infnorm.h"

typedef union {
  int32_t i[2]; 
  double d;
} db_number;


int round_to_format(mpfr_t rop, mpfr_t op, int prec, mp_rnd_t mode) {
  mpfr_t res;
  int round_dir;

  mpfr_init2(res,(mp_prec_t)prec);
  
  round_dir = mpfr_set(res,op, mode);
  if (mpfr_set(rop, res, GMP_RNDN) != 0) {
    printMessage(1,"Warning: an undesired rounding occured on invoking round_to_format.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }

  mpfr_clear(res);
  return round_dir;
}

int mpfr_round_to_double(mpfr_t rop, mpfr_t op) {
  double d;
  int res;

  if (mpfr_get_prec(op) < 53) {
    printMessage(1,"Warning: rounding a value computed on less than 53 bits to double precision.\n");
  }

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(rop,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double precision rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }
  
  res = mpfr_cmp(rop,op);

  return res;
}

int mpfr_round_to_doubledouble(mpfr_t rop, mpfr_t op) {
  double d;
  mpfr_t accu, temp, rest;
  mp_prec_t prec;
  int res;

  prec = mpfr_get_prec(op);
  if (prec < 106) {
    printMessage(1,"Warning: rounding a value computed on less than 106 bits to double-double precision.\n");
    prec = 106;
  }

  mpfr_init2(accu, prec);
  mpfr_init2(temp, prec);
  mpfr_init2(rest, prec);

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(accu,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_set(rop,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the double-double rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }

  res = mpfr_cmp(rop,op);

  mpfr_clear(accu);
  mpfr_clear(temp);
  mpfr_clear(rest);
  return res;
}

int mpfr_round_to_tripledouble(mpfr_t rop, mpfr_t op) {
  double d;
  mpfr_t accu, temp, rest;
  mp_prec_t prec;
  int res;

  prec = mpfr_get_prec(op);
  if (prec < 159) {
    printMessage(1,"Warning: rounding a value computed on less than 159 bits to triple-double precision\n");
    prec = 159;
  }

  mpfr_init2(accu, prec);
  mpfr_init2(temp, prec);
  mpfr_init2(rest, prec);

  d = mpfr_get_d(op,GMP_RNDN);
  if (mpfr_set_d(accu,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_sub(rest,op,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  d = mpfr_get_d(rest,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on recasting to MPFR. This should not occur.\n");
  }
  if (mpfr_add(accu,accu,temp,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"The rounding occured on substracting in MPFR. This should not occur.\n");
  }
  if (mpfr_set(rop,accu,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the triple-double rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }

  res = mpfr_cmp(rop,op);

  mpfr_clear(accu);
  mpfr_clear(temp);
  mpfr_clear(rest);

  return res;
}


int printDoubleInHexa(mpfr_t x) {
  int res;
  double d;
  mpfr_t temp;
  db_number xdb, endianessdb;

  mpfr_init2(temp,mpfr_get_prec(x));
  
  d = mpfr_get_d(x,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: rounding occured unexpectedly on reconverting a double value.\n");
  }
  
  res = mpfr_cmp(temp,x);

  if (res) 
    printMessage(1,"Warning: rounding occured before printing a value as a double.\n");

  xdb.d = d;
  endianessdb.d = 1.0;
  if ((endianessdb.i[1] == 0x3ff00000) && (endianessdb.i[0] == 0)) {
    printf("0x%08x%08x\n",xdb.i[1],xdb.i[0]);
  } else {
    if ((endianessdb.i[0] == 0x3ff00000) && (endianessdb.i[1] == 0)) {
      printf("0x%08x%08x\n",xdb.i[0],xdb.i[1]);
    } else {
      printMessage(1,"Warning: could not figure out the endianess of the system. Will print 1.0 instead of the value.\n");
      printf("0x3ff0000000000000\n");
    }
  }

  mpfr_clear(temp);
  return res;
}


int readHexa(mpfr_t res, char *c) {
  int ret, i;
  int32_t msb, lsb;
  double x;
  char msbstr[9], lsbstr[9];
  db_number xdb, endianessdb;
  
  x = 1.0;
  c += 2; /* Skip over "0x" */
  for (i=0;i<9;i++) {
    msbstr[i] = '\0';
    lsbstr[i] = '\0';
  }
  for (i=0;i<8;i++) {
    msbstr[i] = *c;
    c++;
  }
  for (i=0;i<8;i++) {
    lsbstr[i] = *c;
    c++;
  }

  msb = strtoll(msbstr,NULL,16);
  lsb = strtoll(lsbstr,NULL,16);

  endianessdb.d = 1.0;
  if ((endianessdb.i[1] == 0x3ff00000) && (endianessdb.i[0] == 0)) {
    xdb.i[1] = msb;
    xdb.i[0] = lsb;
  } else {
    if ((endianessdb.i[0] == 0x3ff00000) && (endianessdb.i[1] == 0)) {
      xdb.i[0] = msb;
      xdb.i[1] = lsb;
    } else {
      printMessage(1,"Warning: could not figure out the endianess of the system. Will read 1.0 instead of the value.\n");
      xdb.d = 1.0;
    }
  }

  x = xdb.d;

  if (mpfr_set_d(res,x,GMP_RNDN) != 0) ret = 0; else ret = 1;
  return ret;
}


node *roundPolynomialCoefficients(node *poly, chain *formats, mp_prec_t prec) {
  int degree, listLength, i, deg, res, fillUp, k;
  chain *curr;
  int *formatsArray, *tempArray;
  node *roundedPoly, *temp;
  node **coefficients;
  mpfr_t *fpcoefficients;
  mpfr_t tempMpfr;

  degree = getDegree(poly);

  if (degree < 0) {
    printMessage(1,"Warning: the given function is not a polynomial.\n");
    return copyTree(poly);
  }

  listLength = lengthChain(formats);

  if (listLength > (degree + 1)) {
    printMessage(1,"Warning: the number of the given formats does not correspond to the degree of the given polynomial.\n");
    return copyTree(poly);
  }

  if (*((int *) formats->value) == -1) {
    fillUp = 1;
    curr = formats->next;
  } else {
    curr = formats;
    fillUp = 0;
    if (listLength != (degree + 1)) {
      printMessage(1,"Warning: the number of the given formats does not correspond to the degree of the given polynomial.\n");
      return copyTree(poly);
    }
  }
  
  tempArray = (int *) safeCalloc(degree + 1,sizeof(int));

  i = 0;
  while (curr != NULL) {
    tempArray[i] = *((int *) curr->value);
    i++;
    curr = curr->next;
  }
  k = i;
  
  formatsArray = (int *) safeCalloc(degree + 1,sizeof(int));

  if (fillUp) {
    for (i=k-1;i>=0;i--) {
      formatsArray[(k-1) - i] = tempArray[i];
    }
    for (i=k;i<=degree;i++) {
      formatsArray[i] = formatsArray[k-1];
    }
  } else {
    for (i=degree;i>=0;i--) {
      formatsArray[degree - i] = tempArray[i];
    }
  }

  free(tempArray);

  getCoefficients(&deg,&coefficients,poly);

  if (deg != degree) {
    printMessage(1,"Warning: an error occured while extracting the coefficients of the polynomial.\n");
    for (i=0;i<=deg;i++) {
      if (coefficients[i] != NULL) free_memory(coefficients[i]);
    }
    free(coefficients);
    return copyTree(poly);
  }

  fpcoefficients = (mpfr_t *) safeCalloc(degree+1,sizeof(mpfr_t));

  mpfr_init2(tempMpfr,prec > 160 ? prec : 160);

  res = 0;

  for (i=0;i<=degree;i++) {
    if (coefficients[i] != NULL) {
      temp = simplifyTreeErrorfree(coefficients[i]);
      if (temp->nodeType != CONSTANT) {
	printMessage(1,"Warning: the %dth coefficient of the given polynomial does not evaluate to a floating-point constant without any rounding.\n",i);
	printMessage(1,"Will evaluate the coefficient in the current precision in floating-point before rounding to the target format.\n");
	mpfr_init2(fpcoefficients[i],prec);
	evaluateConstantExpression(fpcoefficients[i], temp, prec);
	res = 1;
      } else {
	mpfr_init2(fpcoefficients[i],mpfr_get_prec(*(temp->value)));
	mpfr_set(fpcoefficients[i],*(temp->value),GMP_RNDN);
      }
      free_memory(temp);
    } else {
      mpfr_init2(fpcoefficients[i],prec);
      mpfr_set_d(fpcoefficients[i],0.0,GMP_RNDN);
    }
    switch (formatsArray[i]) {
    case 4:
      if (mpfr_round_to_doubleextended(tempMpfr, fpcoefficients[i]) != 0) res = 1;
      break;
    case 3:
      if (mpfr_round_to_tripledouble(tempMpfr, fpcoefficients[i]) != 0) res = 1;
      break;
    case 2:
      if (mpfr_round_to_doubledouble(tempMpfr, fpcoefficients[i]) != 0) res = 1;
      break;
    case 1:
      if (mpfr_round_to_double(tempMpfr, fpcoefficients[i]) != 0) res = 1;
      break;
    default:
      printMessage(1,"Warning: unknown expansion format found. No rounding will be performed.\n");
      mpfr_set(tempMpfr,fpcoefficients[i],GMP_RNDN);
    }
    if (mpfr_set(fpcoefficients[i],tempMpfr,GMP_RNDN) != 0) {
      printMessage(1,"Warning: double rounding occured on internal handling of a coefficient.\nTry to increase the precision.\n");
    }
  }

  if (res) {
    printMessage(2,"Information: at least one coefficient has been rounded.\n");
  } else {
    printMessage(2,"Information: there has not been any rounding of the coefficients.\n");
  }

  roundedPoly = makePolynomial(fpcoefficients, degree);

  for (i=0;i<=degree;i++) mpfr_clear(fpcoefficients[i]);
  free(fpcoefficients);
  free(formatsArray);
  mpfr_clear(tempMpfr);
  return roundedPoly;
}

int mpfr_round_to_doubleextended(mpfr_t rop, mpfr_t op) {
  mpfr_t intermediate;
  int res;

  if (mpfr_get_prec(op) < 64) {
    printMessage(1,"Warning: rounding a value computed on less than 64 bits to doubleextended precision.\n");
  }

  mpfr_init2(intermediate,64);
  mpfr_set(intermediate,op,GMP_RNDN);
  if (mpfr_set(rop,intermediate,GMP_RNDN) != 0) {
    printMessage(1,"Warning: double rounding occured on invoking the doubleextended precision rounding operator.\n");
    printMessage(1,"Try to increase the working precision.\n");
  }
  
  mpfr_clear(intermediate);

  res = mpfr_cmp(rop,op);

  return res;
}


int printDoubleExpansion(mpfr_t x) {
  double d;
  mpfr_t temp, rest;
  db_number xdb, endianessdb;
  int noBrackets, roundingOccured;

  mpfr_init2(temp,mpfr_get_prec(x));
  mpfr_init2(rest,mpfr_get_prec(x));

  mpfr_set(rest,x,GMP_RNDN);

  roundingOccured = 0;
  noBrackets = 0;
  d = mpfr_get_d(x,GMP_RNDN);
  if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
    printMessage(1,"Warning: rounding occured unexpectedly on reconverting a double value.\n");
    roundingOccured = 1;
  }

  if (!mpfr_number_p(temp)) {
    printMessage(1,"Warning: will not print a number that is not real as a double expansion.\n");
    printValue(&temp,mpfr_get_prec(temp));
    mpfr_clear(temp);
    mpfr_clear(rest);
    return 1;
  }

  if (mpfr_cmp(temp,x) == 0) 
    noBrackets = 1;

  if (!noBrackets) 
    printf("(");

  do {
    d = mpfr_get_d(rest,GMP_RNDN);
    if (mpfr_set_d(temp,d,GMP_RNDN) != 0) {
      printMessage(1,"Warning: rounding occured unexpectedly on reconverting a double value.\n");
      roundingOccured = 1;
    }
    
    xdb.d = d;
    endianessdb.d = 1.0;
    if ((endianessdb.i[1] == 0x3ff00000) && (endianessdb.i[0] == 0)) {
      printf("0x%08x%08x",xdb.i[1],xdb.i[0]);
    } else {
      if ((endianessdb.i[0] == 0x3ff00000) && (endianessdb.i[1] == 0)) {
	printf("0x%08x%08x",xdb.i[0],xdb.i[1]);
      } else {
	printMessage(1,"Warning: could not figure out the endianess of the system. Will print 1.0 instead of the value.\n");
	printf("0x3ff0000000000000\n");
	roundingOccured = 1;
      }
    }

    if (mpfr_sub(rest,rest,temp,GMP_RNDN) != 0) {
      printMessage(1,"Warning: rounding occured unexpectedly on subtracting.\n");
      roundingOccured = 1;
    }
    
    if ((d != 0.0) && (!mpfr_zero_p(rest))) {
      printf(" + ");
    }

  } while ((d != 0.0) && (!mpfr_zero_p(rest)));

  if (!noBrackets) 
    printf(")");


  if (!mpfr_zero_p(rest)) {
    printMessage(1,"\nWarning: the expansion is not complete because of the limited exponent range of double precision.");
    roundingOccured = 1;
  }

  mpfr_clear(temp);
  mpfr_clear(rest);
  return roundingOccured;
}

int printPolynomialAsDoubleExpansion(node *poly, mp_prec_t prec) {
  int degree, roundingOccured, i, k, l;
  node **coefficients;
  node *tempNode, *simplifiedTreeSafe, *simplifiedTree, *myTree;
  mpfr_t tempValue, tempValue2;

  roundingOccured = 0;

  tempNode = horner(poly);
  simplifiedTreeSafe = simplifyTreeErrorfree(tempNode);
  free_memory(tempNode);
  simplifiedTree = simplifyTree(simplifiedTreeSafe);

  if (!isPolynomial(simplifiedTreeSafe)) {
    if (!isPolynomial(simplifiedTree)) {
      printMessage(1,"Warning: the given expression is not a polynomial.");
      free_memory(simplifiedTree);
      free_memory(simplifiedTreeSafe);
      return -1;
    } else {
      printMessage(1,"Warning: rounding occured while simplifying to a polynomial form.\n");
      roundingOccured = 1;
      myTree = simplifiedTree;
      free_memory(simplifiedTreeSafe);
    }
  } else {
    myTree = simplifiedTreeSafe;
    free_memory(simplifiedTree);
  }

  getCoefficients(&degree, &coefficients, myTree);

  mpfr_init2(tempValue,prec);
  mpfr_init2(tempValue2,prec);
  mpfr_set_d(tempValue2,1.0,GMP_RNDN);

  k = 0; l = 0;
  for (i=0;i<=degree;i++) {
    if (coefficients[i] != NULL) {
      if (k > 0) {
	if (k == 1) {
	  printf("%s * ",variablename);
	} else {
	  printf("%s^%d * ",variablename,k);
	}
      }

      if ((i != degree) && (i != 0)) {
	printf("(");
	l++;
      }

      tempNode = simplifyTreeErrorfree(coefficients[i]);
      if (tempNode->nodeType == CONSTANT) {
	roundingOccured |=  printDoubleExpansion(*(tempNode->value));
      } else {
	if (!isConstant(tempNode)) {
	  printMessage(1,"Error: a coefficient of a polynomial is not constant.\n");
	  recoverFromError();
	}
	evaluateFaithful(tempValue, tempNode, tempValue2, GMP_RNDN);
	printDoubleExpansion(tempValue);
	roundingOccured = 1;
      }
      free_memory(tempNode);
      free_memory(coefficients[i]);
      k = 1;

      if (i != degree) {
	printf(" + ");
      }
    } else {
      k++;
    }
  }
  for (i=0;i<l;i++) 
    printf(")");

  free(coefficients);
  mpfr_clear(tempValue);
  mpfr_clear(tempValue2);
  free_memory(myTree);

  return roundingOccured;
}


void mpfr_round_to_format(mpfr_t rop, mpfr_t op, int format) {
  switch (format) {
  case 4:
    mpfr_round_to_doubleextended(rop, op);
    break;
  case 3:
    mpfr_round_to_tripledouble(rop, op);
    break;
  case 2:
    mpfr_round_to_doubledouble(rop, op);
    break;
  case 1:
    mpfr_round_to_double(rop, op);
    break;
  default:
    fprintf(stderr,"Error: mpfr_round_to_format: unknown format type.\n");
    exit(1);
  }
}


int mpfr_mant_exp(mpfr_t rop, mp_exp_t *expo, mpfr_t op) {
  mp_exp_t e;
  mp_prec_t p;
  mpfr_t temp;
  int res;

  if (!mpfr_number_p(op)) {
    *expo = 0;
    return mpfr_set(rop,op,GMP_RNDN);
  }

  if (mpfr_zero_p(op)) {
    *expo = 0;
    return mpfr_set(rop,op,GMP_RNDN);
  }

  p = mpfr_get_prec(op);  
  mpfr_init2(temp,p);
  mpfr_set(temp,op,GMP_RNDN);
  
  e = mpfr_get_exp(temp) - p;
  mpfr_set_exp(temp,p);
  
  while (mpfr_integer_p(temp)) {
    mpfr_div_2ui(temp,temp,1,GMP_RNDN);
    e++;
  }
  mpfr_mul_2ui(temp,temp,1,GMP_RNDN);
  e--;
  
  *expo = e;
  res = mpfr_set(rop,temp,GMP_RNDN);

  mpfr_clear(temp);

  return res;
}


