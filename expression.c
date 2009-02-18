/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.fr
sylvain.chevillard@ens-lyon.fr
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinity norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*/

#include <mpfr.h>
#include <mpfi.h>
#include <gmp.h>
#include "expression.h"
#include <stdio.h> /* fprinft, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <string.h>
#include <errno.h>
#include "general.h"
#include "double.h"
#include "miniparser.h"
#include "chain.h"

#define MAXDIFFSIMPLSIZE 100
#define MAXDIFFSIMPLDEGREE 25

void simplifyMpfrPrec(mpfr_t rop, mpfr_t op) {
  mpz_t mant;
  mp_exp_t expo;
  mp_prec_t prec;
  mpfr_t x;
  unsigned int dyadicValue;
  int p;

  if (mpfr_number_p(op) && (!mpfr_zero_p(op))) {
    mpz_init(mant);
    expo = mpfr_get_z_exp(mant,op);
    prec = mpz_sizeinbase(mant, 2);
    dyadicValue = mpz_scan1(mant, 0);
    p = prec - dyadicValue;
    if (p < 12) prec = 12; else prec = p; 
    mpfr_init2(x,prec);
    mpfr_set_z(x,mant,GMP_RNDN);
    mpfr_mul_2si(x,x,expo,GMP_RNDN);
    if (mpfr_cmp(x,op) == 0) {
      mpfr_set_prec(rop,prec);
      mpfr_set(rop,x,GMP_RNDN);
    } else {
      prec = mpfr_get_prec(op);
      mpfr_set_prec(x,prec);
      mpfr_set(x,op,GMP_RNDN);
      mpfr_set_prec(rop,prec);
      mpfr_set(rop,x,GMP_RNDN);
    }
    mpfr_clear(x);
    mpz_clear(mant);
  } else {
    prec = mpfr_get_prec(op);
    mpfr_init2(x,prec);
    mpfr_set(x,op,GMP_RNDN);
    mpfr_set_prec(rop,prec);
    mpfr_set(rop,x,GMP_RNDN);
    mpfr_clear(x);
  }
}



void mpfr_from_mpfi(mpfr_t rop, mpfr_t op, int n, int (*mpfifun)(mpfi_t, mpfi_t, int)) {
  mpfi_t opI, ropI;

  mpfi_init2(opI,mpfr_get_prec(op));
  mpfi_init2(ropI,mpfr_get_prec(rop)+2);
  mpfi_set_fr(opI,op);

  mpfifun(ropI,opI,n);
  
  mpfi_mid(rop,ropI);

  mpfi_clear(opI);
  mpfi_clear(ropI);
}

void free_memory(node *tree) {
  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    free(tree);
    break;
  case CONSTANT:
    mpfr_clear(*(tree->value));
    free(tree->value);
    free(tree);
    break;
  case ADD:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case SUB:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case MUL:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case DIV:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case SQRT:
    free_memory(tree->child1);
    free(tree);
    break;
  case EXP:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG_2:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG_10:
    free_memory(tree->child1);
    free(tree);
    break;
  case SIN:
    free_memory(tree->child1);
    free(tree);
    break;
  case COS:
    free_memory(tree->child1);
    free(tree);
    break;
  case TAN:
    free_memory(tree->child1);
    free(tree);
    break;
  case ASIN:
    free_memory(tree->child1);
    free(tree);
    break;
  case ACOS:
    free_memory(tree->child1);
    free(tree);
    break;
  case ATAN:
    free_memory(tree->child1);
    free(tree);
    break;
  case SINH:
    free_memory(tree->child1);
    free(tree);
    break;
  case COSH:
    free_memory(tree->child1);
    free(tree);
    break;
  case TANH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ASINH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ACOSH:
    free_memory(tree->child1);
    free(tree);
    break;
  case ATANH:
    free_memory(tree->child1);
    free(tree);
    break;
  case POW:
    free_memory(tree->child1);
    free_memory(tree->child2);
    free(tree);
    break;
  case NEG:
    free_memory(tree->child1);
    free(tree);
    break;
  case ABS:
    free_memory(tree->child1);
    free(tree);
    break;
  case DOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case DOUBLEDOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case TRIPLEDOUBLE:
    free_memory(tree->child1);
    free(tree);
    break;
  case ERF: 
    free_memory(tree->child1);
    free(tree);
    break;
  case ERFC:
    free_memory(tree->child1);
    free(tree);
    break;
  case LOG_1P:
    free_memory(tree->child1);
    free(tree);
    break;
  case EXP_M1:
    free_memory(tree->child1);
    free(tree);
    break;
  case DOUBLEEXTENDED:
    free_memory(tree->child1);
    free(tree);
    break;
  case LIBRARYFUNCTION:
    free_memory(tree->child1);
    free(tree);
    break;
  case CEIL:
    free_memory(tree->child1);
    free(tree);
    break;
  case FLOOR:
    free_memory(tree->child1);
    free(tree);
    break;
  case PI_CONST:
    free(tree);
    break;
  default:
   fprintf(stderr,"Error: free_memory: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}




void fprintHeadFunction(FILE *fd,node *tree, char *x, char *y) {
  int i;

  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (x != NULL) fprintf(fd,"%s",x); else fprintf(fd,"x");
    break;
  case CONSTANT:
    fprintValue(fd,*(tree->value));
    break;
  case ADD:
    fprintf(fd,"%s + %s",x,y);
    break;
  case SUB:
    fprintf(fd,"%s - %s",x,y);
    break;
  case MUL:
    fprintf(fd,"%s * %s",x,y);
    break;
  case DIV:
    fprintf(fd,"%s / %s",x,y);
    break;
  case SQRT:
    fprintf(fd,"sqrt(%s)",x);
    break;
  case EXP:
    fprintf(fd,"exp(%s)",x);
    break;
  case LOG:
    fprintf(fd,"log(%s)",x);
    break;
  case LOG_2:
    fprintf(fd,"log2(%s)",x);
    break;
  case LOG_10:
    fprintf(fd,"log10(%s)",x);
    break;
  case SIN:
    fprintf(fd,"sin(%s)",x);
    break;
  case COS:
    fprintf(fd,"cos(%s)",x);
    break;
  case TAN:
    fprintf(fd,"tan(%s)",x);
    break;
  case ASIN:
    fprintf(fd,"asin(%s)",x);
    break;
  case ACOS:
    fprintf(fd,"acos(%s)",x);
    break;
  case ATAN:
    fprintf(fd,"atan(%s)",x);
    break;
  case SINH:
    fprintf(fd,"sinh(%s)",x);
    break;
  case COSH:
    fprintf(fd,"cosh(%s)",x);
    break;
  case TANH:
    fprintf(fd,"tanh(%s)",x);
    break;
  case ASINH:
    fprintf(fd,"asinh(%s)",x);
    break;
  case ACOSH:
    fprintf(fd,"acosh(%s)",x);
    break;
  case ATANH:
    fprintf(fd,"atanh(%s)",x);
    break;
  case POW:
    fprintf(fd,"%s^%s",x,y);
    break;
  case NEG:
    fprintf(fd,"-%s",x);
    break;
  case ABS:
    fprintf(fd,"abs(%s)",x);
    break;
  case DOUBLE:
    fprintf(fd,"double(%s)",x);
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(%s)",x);
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(%s)",x);
    break;
  case ERF: 
    fprintf(fd,"erf(%s)",x);
    break;
  case ERFC:
    fprintf(fd,"erfc(%s)",x);
    break;
  case LOG_1P:
    fprintf(fd,"log1p(%s)",x);
    break;
  case EXP_M1:
    fprintf(fd,"expm1(%s)",x);
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(%s)",x);
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,"diff(");
      }
      fprintf(fd,"%s(%s)",tree->libFun->functionName,x);
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,")");
      }
    }
    break;
  case CEIL:
    fprintf(fd,"ceil(%s)",x);
    break;
  case FLOOR:
    fprintf(fd,"floor(%s)",x);
    break;
  case PI_CONST:
    fprintf(fd,"pi");
    break;
  default:
   fprintf(stderr,"fprintHeadFunction: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}

int precedence(node *tree) {
  switch (tree->nodeType) {
  case CONSTANT:
  case VARIABLE:
  case PI_CONST:
    return 1;
    break;
  case ADD:
  case SUB:
    return 2;
    break;
  case MUL:
    return 3;
    break;
  case DIV:
    return 4;
    break;
  case NEG:
    return 5;
    break;
  case POW:
    return 6;
    break;
  default:
    return 7; 
  }
  return 0;
}


int isInfix(node *tree) {
  char *str;
  int res;
  switch(tree->nodeType) {
  case CONSTANT: 
    if (mpfr_sgn(*(tree->value)) < 0) return 1;
    if ((dyadic == 2) || (dyadic == 3)) {
      str = sprintValue(tree->value);
      res = (strchr(str,'*') != NULL);
      free(str);
      return res;
    }
    break;
  case PI_CONST:
  case ADD:
  case SUB:
  case MUL:
  case DIV:
  case POW:
  case NEG:
    return 1;
    break;
  default: return 0;
  }
  return 0;
}

void removeTrailingZeros(char *outbuf, char *inbuf) {
  char *temp, *temp2, *temp3;

  temp = inbuf; temp2 = outbuf; temp3 = outbuf;
  while ((temp != NULL) && (*temp != '\0')) {
    *temp2 = *temp;
    if (*temp2 != '0') {
      temp3 = temp2;
    }
    temp2++;
    temp++;
  }
  temp3++;
  *temp3 = '\0';
}

void printHexadecimalValue(mpfr_t x);

void printValue(mpfr_t *value) {
  char *str;

  str = sprintValue(value);
  printf("%s",str);
  free(str);
}

char *sprintMidpointMode(mpfr_t a, mpfr_t b) {
  mp_exp_t e1, e2;
  char *str1, *str2, *str, *str3;
  mpfr_t aP, bP;
  int sign, len1, len2, len, i;
  mp_prec_t prec, p;
  char *s1, *s2;
  int possibleLength;

  if (mpfr_sgn(a) != mpfr_sgn(b)) return NULL;

  if (mpfr_zero_p(a)) {
    str = safeCalloc(7,sizeof(char));
    sprintf(str,"[0]");
    return str;
  }

  prec = mpfr_get_prec(a);
  p = mpfr_get_prec(b);

  if (p > prec) prec = p;

  mpfr_init2(aP,prec);
  mpfr_init2(bP,prec);

  sign = mpfr_sgn(a);
  if (sign > 0) {
    mpfr_set(aP,a,GMP_RNDN);
    mpfr_set(bP,b,GMP_RNDN);
  } else {
    mpfr_neg(aP,b,GMP_RNDN);
    mpfr_neg(bP,a,GMP_RNDN);
  }

  str1 = mpfr_get_str(NULL,&e1,10,0,aP,GMP_RNDD);  
  str2 = mpfr_get_str(NULL,&e2,10,0,bP,GMP_RNDU);  

  str3 = safeCalloc(strlen(str1) + 1, sizeof(char));
  removeTrailingZeros(str3,str1);
  free(str1);
  str1 = str3;

  str3 = safeCalloc(strlen(str2) + 1, sizeof(char));
  removeTrailingZeros(str3,str2);
  free(str2);
  str2 = str3;

  if (e1 == e2) {
    if (strcmp(str1,str2) == 0) {
      mpfr_set(aP,a,GMP_RNDN);
      str3 = sprintValue(&aP);
      str = (char *) safeCalloc(strlen(str3) + 3, sizeof(char));
      sprintf(str,"[%s]",str3);
      free(str3);
    } else { 

      if (str1[0] == str2[0]) {
	len1 = strlen(str1);
	len2 = strlen(str2);
	len = len1;
	if (len2 < len) len = len2;
	i = 0;
	while ((i < len) && (str1[i] == str2[i])) {
	  i++;
	}
	possibleLength = i;
	s1 = mpfr_get_str(NULL,&e1,10,possibleLength+1,aP,GMP_RNDD);  
	s2 = mpfr_get_str(NULL,&e2,10,possibleLength+1,bP,GMP_RNDU); 
	
	if (e1 == e2) {
	  if (s1[0] == s2[0]) {
	    len1 = strlen(s1);
	    len2 = strlen(s2);
	    len = len1;
	    if (len2 < len) len = len2;
	    str = (char *) safeCalloc(len+6,sizeof(char));
	    i = 0;
	    while ((i < len) && (s1[i] == s2[i])) {
	      str[i] = s1[i];
	      i++;
	    }
	    str[i] = '~';
	    if (sign > 0) 
	      str[i+1] = s1[i];
	    else
	      str[i+1] = s2[i];
	    str[i+2] = '/';
	    if (sign > 0) 
	      str[i+3] = s2[i];
	    else 
	      str[i+3] = s1[i];
	    str[i+4] = '~';
	    str3 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	    removeTrailingZeros(str3,str);
	    free(str);
	    str = str3;
	    str3 = (char *) safeCalloc(strlen(str)+69,sizeof(char));
	    if (sign < 0) {
	      if (e1 == 0) {
		sprintf(str3,"-0.%s",str);
	      } else {
		sprintf(str3,"-0.%se%d",str,(int)e1);
	      }
	    } else {
	      if (e1 == 0) {
		sprintf(str3,"0.%s",str);
	      } else {
		sprintf(str3,"0.%se%d",str,(int)e1);
	      }
	    }
	    free(str);
	    str = str3;
	    str3 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	    sprintf(str3,"%s",str);
	    free(str);
	    str = str3;
	  } else {
	    str = NULL;
	  }
	} else {
	  str = NULL;
	}
	free(s1);
	free(s2);
      } else {
	str = NULL;
      }
    }
  } else {
    str = NULL;
  }

  mpfr_free_str(str1);      
  mpfr_free_str(str2);      

  mpfr_clear(aP);
  mpfr_clear(bP);
  return str;
}

char *sPrintBinary(mpfr_t x) {
  mpfr_t xx;
  int negative;
  mp_prec_t prec;
  mp_exp_t expo;
  char *raw, *formatted, *temp1, *temp2, *str3;
  char *temp3=NULL;
  char *resultStr;
  int len;

  prec = mpfr_get_prec(x);
  mpfr_init2(xx,prec);
  mpfr_abs(xx,x,GMP_RNDN);
  negative = 0;
  if (mpfr_sgn(x) < 0) negative = 1;
  raw = mpfr_get_str(NULL,&expo,2,0,xx,GMP_RNDN);
  if (raw == NULL) {
    printf("Error: unable to get a string for the given number.\n");
    recoverFromError();
  } else {
    formatted = safeCalloc(strlen(raw) + 3, sizeof(char));
    temp1 = raw; temp2 = formatted;
    if (negative) {
      *temp2 = '-';
      temp2++;
    }
    *temp2 = *temp1; temp2++; temp1++;
    if (*temp1 != '\0') { 
      *temp2 = '.'; 
      temp2++;
    }
    while (*temp1 != '\0') {
      *temp2 = *temp1;
      temp2++; temp1++;
    }
    str3 = (char *) safeCalloc(strlen(formatted)+2,sizeof(char));
    removeTrailingZeros(str3,formatted);
    len = strlen(str3) - 1;
    if (str3[len] == '.') {
      str3[len] = '\0';
    }
    if (!mpfr_zero_p(x)) {
      if (mpfr_number_p(x)) {
	temp3 = (char *) safeCalloc(strlen(str3)+74,sizeof(char));
	if ((((int) expo)-1) != 0) 
	  sprintf(temp3,"%s_2 * 2^(%d)",str3,((int)expo)-1);  
	else
	  sprintf(temp3,"%s_2",str3);  
      } else {
	temp3 = (char *) safeCalloc(strlen(raw) + 2,sizeof(char));
	if (negative) 
	  sprintf(temp3,"-%s",raw); 
	else 
	  sprintf(temp3,"%s",raw); 
      }
    }
    else {
      temp3 = (char *) safeCalloc(2,sizeof(char));
      sprintf(temp3,"0");
    }
    free(formatted);
    free(str3);
  }
  mpfr_free_str(raw);  
  mpfr_clear(xx);
  resultStr = (char *) safeCalloc(strlen(temp3) + 1,sizeof(char));
  sprintf(resultStr,"%s",temp3);
  free(temp3);
  return resultStr;
}

char *sPrintHexadecimal(mpfr_t x) {
  mpfr_t xx;
  int negative;
  mp_prec_t prec;
  mp_exp_t expo;
  char *raw, *formatted, *temp1, *temp2, *str3;
  char *temp3 = NULL;
  char *resultStr;

  prec = mpfr_get_prec(x);
  mpfr_init2(xx,prec);
  mpfr_abs(xx,x,GMP_RNDN);
  negative = 0;
  if (mpfr_sgn(x) < 0) negative = 1;
  raw = mpfr_get_str(NULL,&expo,16,0,xx,GMP_RNDN);
  if (raw == NULL) {
    printf("Error: unable to get a string for the given number.\n");
    recoverFromError();
  } else {
    formatted = safeCalloc(strlen(raw) + 3, sizeof(char));
    temp1 = raw; temp2 = formatted;
    *temp2 = *temp1; temp2++; temp1++;
    *temp2 = '.'; temp2++;
    while (*temp1 != '\0') {
      *temp2 = *temp1;
      temp2++; temp1++;
    }
    str3 = (char *) safeCalloc(strlen(formatted)+2,sizeof(char));
    removeTrailingZeros(str3,formatted);    
    if (!mpfr_zero_p(x)) {
      if (mpfr_number_p(x)) {
	temp3 = (char *) safeCalloc(strlen(str3)+74,sizeof(char));
	if (negative) {
	  sprintf(temp3,"-0x%sp%d",str3,4 * (((int)expo)-1)); 
	} else {
	  sprintf(temp3,"0x%sp%d",str3,4 * (((int)expo)-1)); 
	}
      } else {
	temp3 = (char *) safeCalloc(strlen(raw) + 2,sizeof(char));
	if (negative) 
	  sprintf(temp3,"-%s",raw); 
	else 
	  sprintf(temp3,"%s",raw); 
      }
    }
    else {
      temp3 = (char *) safeCalloc(2,sizeof(char));
      sprintf(temp3,"0");
    }
    free(formatted);
    free(str3);
  }
  mpfr_free_str(raw);  
  mpfr_clear(xx);
  resultStr = (char *) safeCalloc(strlen(temp3) + 1,sizeof(char));
  sprintf(resultStr,"%s",temp3);
  free(temp3);
  return resultStr;
}


void printBinary(mpfr_t x) {
  char *str;

  str = sPrintBinary(x);
  printf("%s",str);
  free(str);
}

void printHexadecimalValue(mpfr_t x) {
  char *str;

  str = sPrintHexadecimal(x);
  printf("%s",str);
  free(str);
}



char *sprintValue(mpfr_t *aValue) {
  mpfr_t y;
  char *str, *str2, *str3;
  mp_exp_t e, expo;
  int t, l, i;
  char *buffer, *tempBuf, *finalBuffer;
  char *tempBufOld;
  char *str4;
  mpfr_t temp;
  mp_prec_t prec2, prec, p;
  mpfr_t *value, myValue;
  char *res;
  
  p = mpfr_get_prec(*aValue);  
  mpfr_init2(myValue,p);
  simplifyMpfrPrec(myValue, *aValue);
  if ((p > tools_precision) && (mpfr_get_prec(myValue) < tools_precision)) {
    if (tools_precision < p) p = tools_precision;
    mpfr_set_prec(myValue,p);
    mpfr_set(myValue,*aValue,GMP_RNDN);
  }
  value = &myValue;
  
  if (dyadic == 4) {
    res = sPrintHexadecimal(*value);
    mpfr_clear(myValue);
    return res;
  }

  if (dyadic == 3) {
    res = sPrintBinary(*value);
    mpfr_clear(myValue);
    return res;
  } 

  prec = mpfr_get_prec(*value);

  if (mpfr_number_p(*value)) {
    prec2 = prec;
    while (prec2 >= tools_precision) {
      mpfr_init2(temp,prec2);
      mpfr_set(temp,*value,GMP_RNDN);
      if (mpfr_cmp(temp,*value) != 0) {
	mpfr_clear(temp);
	prec2++;
	break;
      }
      mpfr_clear(temp);
      prec2--;
    }
    if (prec2 > prec) prec2 = prec;
    if (prec2 < tools_precision) prec2 = tools_precision;
    prec = prec2;
  }
  buffer = safeCalloc(2 * prec + 7 + (sizeof(mp_exp_t) * 4) + 1, sizeof(char));
  tempBuf = buffer;
  mpfr_init2(y,prec);

  t = mpfr_get_si(*value,GMP_RNDN);
  mpfr_set_si(y,t,GMP_RNDN);
  if ((mpfr_cmp(y,*value) == 0) && (mpfr_number_p(*value))) {
    tempBuf += sprintf(tempBuf,"%d",t);
  } else { 
    mpfr_set(y,*value,GMP_RNDN);
    if (mpfr_sgn(y) < 0) {
      tempBuf += sprintf(tempBuf,"-"); mpfr_neg(y,y,GMP_RNDN);
    }
    if ((dyadic == 1) || (dyadic == 2)) {
      if (!mpfr_number_p(*value)) {
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	tempBuf += sprintf(tempBuf,"%s",str);
      } else {
	expo = mpfr_get_exp(y);
	if (mpfr_set_exp(y,prec)) {
	  printMessage(1,"\nWarning: %d is not in the current exponent range of a variable. Values displayed may be wrong.\n",(int)(prec));
	}
	expo -= prec;
	while (mpfr_integer_p(y)) {
	  mpfr_div_2ui(y,y,1,GMP_RNDN);
	  expo += 1;
	}
	expo--;
	if (mpfr_mul_2ui(y,y,1,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"\nWarning: rounding occurred during displaying a value. Values displayed may be wrong.\n");
	  }
	}
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	str2 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	strncpy(str2,str,e);
	if (dyadic == 1) 
	  tempBuf += sprintf(tempBuf,"%sb%d",str2,(int)expo);
	else
	  tempBuf += sprintf(tempBuf,"%s * 2^(%d)",str2,(int)expo);
	free(str2);
      }
      mpfr_free_str(str);      
    } else {
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      if (mpfr_number_p(*value)) {
	str3 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	removeTrailingZeros(str3,str);
	if (e == 0) {
	  tempBufOld = tempBuf;
	  str4 = (char *) safeCalloc(strlen(str3)+1,sizeof(char));
	  mpfr_init2(temp,prec);
	  for (i=0;i<(int)strlen(str3);i++) {
	    str4[i] = str3[i];
	    tempBuf = tempBufOld;
	    tempBuf += sprintf(tempBuf,"0.%s",str4);   
	    mpfr_set_str(temp,buffer,10,GMP_RNDN);
	    if (mpfr_cmp(temp,*value) == 0) break;
	  }
	  free(str4);
	  mpfr_clear(temp);
	} else {
	  l = strlen(str3);
	  if ((e > 0) && (l <= e) && (e <= 16)) {
	    tempBuf += sprintf(tempBuf,"%s",str3);
	    for (i=l;i<e;i++) tempBuf += sprintf(tempBuf,"0");
	  } else {
	    tempBufOld = tempBuf;
	    str4 = (char *) safeCalloc(strlen(str3)+1,sizeof(char));
	    mpfr_init2(temp,prec);
	    for (i=0;i<(int)strlen(str3);i++) {
	      str4[i] = str3[i];
	      tempBuf = tempBufOld;
	      if (e-1 == 0) {
		if (strlen(str4) > 1) {
		  tempBuf += sprintf(tempBuf,"%c.%s",*str4,str4+1);   
		} else {
		  tempBuf += sprintf(tempBuf,"%c",*str4);
		}
	      } else {
		if (strlen(str4) > 1) {
		  tempBuf += sprintf(tempBuf,"%c.%se%d",*str4,str4+1,(int)e-1);   
		} else {
		  tempBuf += sprintf(tempBuf,"%ce%d",*str4,(int)e-1);   
		}
	      }
	      mpfr_set_str(temp,buffer,10,GMP_RNDN);
	      if (mpfr_cmp(temp,*value) == 0) break;
	    }
	    free(str4);
	    mpfr_clear(temp);
	  }
	}
	free(str3);
      } else {
	tempBuf += sprintf(tempBuf,"%s",str);
      }
      mpfr_free_str(str);      
    }
  }
  mpfr_clear(y);
  
  finalBuffer = (char *) safeCalloc(strlen(buffer)+1,sizeof(char));
  sprintf(finalBuffer,"%s",buffer);
  free(buffer);
  mpfr_clear(myValue);
  return finalBuffer;
}


void printMpfr(mpfr_t x) {
  mpfr_t tmp;
  mp_prec_t prec;

  prec = mpfr_get_prec(x);
  mpfr_init2(tmp,prec);
  mpfr_set(tmp,x,GMP_RNDN);

  printValue(&tmp);
  printf("\n");

  mpfr_clear(tmp);
}


void fprintValueWithPrintMode(FILE *fd, mpfr_t value) {
  char *str;
  mpfr_t temp;
  mp_prec_t p;

  p = mpfr_get_prec(value);
  mpfr_init2(temp,p);
  mpfr_set(temp,value,GMP_RNDN);
  str = sprintValue(&temp);
  mpfr_clear(temp);
  fprintf(fd,"%s",str);
  free(str);
  
}

void fprintTreeWithPrintMode(FILE *fd, node *tree) {
  int pred, i;

  if (fullParentheses) pred = 100; else pred = precedence(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename != NULL) {
      fprintf(fd,"%s",variablename);
    } else {
      printMessage(1,"Warning: the current free variable has not been bound. Nevertheless it must be printed.\n");
      printMessage(1,"Will bind the current free variable to \"x\".\n");
      variablename = (char *) safeCalloc(2,sizeof(char));
      variablename[0] = 'x';
      fprintf(fd,"%s",variablename);
    }
    break;
  case CONSTANT:
    fprintValueWithPrintMode(fd,*(tree->value));
    break;
  case ADD:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,")");
    fprintf(fd," + ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      fprintf(fd,")");
    break;
  case SUB:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,")");
    fprintf(fd," - ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      fprintf(fd,")");
    break;
  case MUL:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,")");
    fprintf(fd," * ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      fprintf(fd,")");
    break;
  case DIV:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      fprintf(fd,")");
    fprintf(fd," / ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      fprintf(fd,")");
    break;
  case SQRT:
    fprintf(fd,"sqrt(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP:
    fprintf(fd,"exp(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG:
    fprintf(fd,"log(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_2:
    fprintf(fd,"log2(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_10:
    fprintf(fd,"log10(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SIN:
    fprintf(fd,"sin(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COS:
    fprintf(fd,"cos(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TAN:
    fprintf(fd,"tan(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASIN:
    fprintf(fd,"asin(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOS:
    fprintf(fd,"acos(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATAN:
    fprintf(fd,"atan(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SINH:
    fprintf(fd,"sinh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COSH:
    fprintf(fd,"cosh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TANH:
    fprintf(fd,"tanh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASINH:
    fprintf(fd,"asinh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOSH:
    fprintf(fd,"acosh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATANH:
    fprintf(fd,"atanh(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case POW:
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      fprintf(fd,")");
    fprintf(fd,"^");
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) {
      fprintf(fd,"(");
    }
    fprintTreeWithPrintMode(fd,tree->child2);
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) {
      fprintf(fd,")");
    }
    break;
  case NEG:
    fprintf(fd,"-");
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      fprintf(fd,"(");
    fprintTreeWithPrintMode(fd,tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      fprintf(fd,")");
    break;
  case ABS:
    fprintf(fd,"abs(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLE:
    fprintf(fd,"double(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERF: 
    fprintf(fd,"erf(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERFC:
    fprintf(fd,"erfc(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_1P:
    fprintf(fd,"log1p(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP_M1:
    fprintf(fd,"expm1(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,"diff(");
      }
      fprintf(fd,"%s(",tree->libFun->functionName);
      fprintTreeWithPrintMode(fd,tree->child1);
      fprintf(fd,")");
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,")");
      }
    }
    break;
  case CEIL:
    fprintf(fd,"ceil(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case FLOOR:
    fprintf(fd,"floor(");
    fprintTreeWithPrintMode(fd,tree->child1);
    fprintf(fd,")");
    break;
  case PI_CONST:
    fprintf(fd,"pi");
    break;
  default:
   fprintf(stderr,"Error: fprintTreeWithPrintMode: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}






void fprintValue(FILE *fd, mpfr_t value) {
  mpfr_t y;
  char *str, *str2;
  mp_exp_t e, expo;
  mp_prec_t prec;

  if (mpfr_zero_p(value)) {
    fprintf(fd,"0");
  } else {
    prec = mpfr_get_prec(value);
    mpfr_init2(y,prec+10);
    mpfr_set(y,value,GMP_RNDN);
    if (mpfr_sgn(y) < 0) {
      fprintf(fd,"-"); mpfr_neg(y,y,GMP_RNDN);
    }
    if (!mpfr_number_p(value)) {
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      fprintf(fd,"%s",str);
    } else {
      expo = mpfr_get_exp(y);
      if (mpfr_set_exp(y,prec+10)) {
	printMessage(1,"\nWarning: upon printing to a file: %d is not in the current exponent range of a variable. Values printed may be wrong.\n",(int)(prec+10));
      }
      expo -= prec+10;
      while (mpfr_integer_p(y)) {
	mpfr_div_2ui(y,y,1,GMP_RNDN);
	expo += 1;
      }
      expo--;
      if (mpfr_mul_2ui(y,y,1,GMP_RNDN) != 0) {
	if (!noRoundingWarnings) {
	  printMessage(1,"\nWarning: upon printing to a file: rounding occurred. Values printed may be wrong.\n");
	}
      }
      str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
      str2 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
      strncpy(str2,str,e);
      fprintf(fd,"%sb%d",str2,(int)expo);
      free(str2);
    }
    free(str);
    mpfr_clear(y);
  }
}

void fprintValueForXml(FILE *fd, mpfr_t value) {
  mpfr_t y, h;
  char *str, *str2;
  mp_exp_t e, expo;
  mp_prec_t prec;
  int negate, val;

  if (mpfr_zero_p(value)) {
    fprintf(fd,"<cn type=\"integer\" base=\"10\"> 0 </cn>\n");
  } else {
    prec = mpfr_get_prec(value);
    mpfr_init2(y,prec+10);
    mpfr_set(y,value,GMP_RNDN);
    val = mpfr_get_si(y,GMP_RNDN);
    mpfr_init2(h,prec);
    mpfr_set_si(h,val,GMP_RNDN);
    if (mpfr_number_p(y) && (mpfr_cmp(h,y) == 0)) {
      mpfr_clear(h);
      fprintf(fd,"<cn type=\"integer\" base=\"10\"> %d </cn>\n",val);
    } else {
      mpfr_clear(h);
      negate = 0;
      if (mpfr_sgn(y) < 0) {
	negate = 1; mpfr_neg(y,y,GMP_RNDN);
      } 
      if (!mpfr_number_p(value)) {
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	if (!negate) 
	  fprintf(fd,"<cn type=\"real\"> %s </cn>\n",str);
	else 
	  fprintf(fd,"<cn type=\"real\"> -%s </cn>\n",str);
      } else {
	expo = mpfr_get_exp(y);
	if (mpfr_set_exp(y,prec+10)) {
	  printMessage(1,"\nWarning: upon printing to a file: %d is not in the current exponent range of a variable. Values printed may be wrong.\n",(int)(prec+10));
	}
	expo -= prec+10;
	while (mpfr_integer_p(y)) {
	  mpfr_div_2ui(y,y,1,GMP_RNDN);
	  expo += 1;
	}
	expo--;
	if (mpfr_mul_2ui(y,y,1,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"\nWarning: upon printing to a file: rounding occurred. Values printed may be wrong.\n");
	  }
	}
	str = mpfr_get_str(NULL,&e,10,0,y,GMP_RNDN);
	str2 = (char *) safeCalloc(strlen(str)+1,sizeof(char));
	strncpy(str2,str,e);
	if (!negate) {
	  fprintf(fd,"<apply>\n");
	  fprintf(fd,"<times/>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> %s </cn>\n",str2);
	  fprintf(fd,"<apply>\n");
	  fprintf(fd,"<power/>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> 2 </cn>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> %d </cn>\n",(int) expo);
	  fprintf(fd,"</apply>\n");
	  fprintf(fd,"</apply>\n");
	} else {
	  fprintf(fd,"<apply>\n");
	  fprintf(fd,"<times/>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> -%s </cn>\n",str2);
	  fprintf(fd,"<apply>\n");
	  fprintf(fd,"<power/>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> 2 </cn>\n");
	  fprintf(fd,"<cn type=\"integer\" base=\"10\"> %d </cn>\n",(int) expo);
	  fprintf(fd,"</apply>\n");
	  fprintf(fd,"</apply>\n");
	}
	free(str2);
      }
    }
    mpfr_clear(y);
  }
}



void printTree(node *tree) {
  int pred, i;

  if (fullParentheses) pred = 100; else pred = precedence(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    printf("%s",variablename);
    break;
  case CONSTANT:
    printValue(tree->value);
    break;
  case ADD:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf(")");
    printf(" + ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf(")");
    break;
  case SUB:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf(")");
    printf(" - ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      printf(")");
    break;
  case MUL:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf(")");
    printf(" * ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      printf(")");
    break;
  case DIV:
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      printf(")");
    printf(" / ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      printf("(");
    printTree(tree->child2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      printf(")");
    break;
  case SQRT:
    printf("sqrt(");
    printTree(tree->child1);
    printf(")");
    break;
  case EXP:
    printf("exp(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG:
    printf("log(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG_2:
    printf("log2(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG_10:
    printf("log10(");
    printTree(tree->child1);
    printf(")");
    break;
  case SIN:
    printf("sin(");
    printTree(tree->child1);
    printf(")");
    break;
  case COS:
    printf("cos(");
    printTree(tree->child1);
    printf(")");
    break;
  case TAN:
    printf("tan(");
    printTree(tree->child1);
    printf(")");
    break;
  case ASIN:
    printf("asin(");
    printTree(tree->child1);
    printf(")");
    break;
  case ACOS:
    printf("acos(");
    printTree(tree->child1);
    printf(")");
    break;
  case ATAN:
    printf("atan(");
    printTree(tree->child1);
    printf(")");
    break;
  case SINH:
    printf("sinh(");
    printTree(tree->child1);
    printf(")");
    break;
  case COSH:
    printf("cosh(");
    printTree(tree->child1);
    printf(")");
    break;
  case TANH:
    printf("tanh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ASINH:
    printf("asinh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ACOSH:
    printf("acosh(");
    printTree(tree->child1);
    printf(")");
    break;
  case ATANH:
    printf("atanh(");
    printTree(tree->child1);
    printf(")");
    break;
  case POW:
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf(")");
    printf("^");
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) {
      printf("(");
    }
    printTree(tree->child2);
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) {
      printf(")");
    }
    break;
  case NEG:
    printf("-");
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf("(");
    printTree(tree->child1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      printf(")");
    break;
  case ABS:
    printf("abs(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLE:
    printf("double(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLEDOUBLE:
    printf("doubledouble(");
    printTree(tree->child1);
    printf(")");
    break;
  case TRIPLEDOUBLE:
    printf("tripledouble(");
    printTree(tree->child1);
    printf(")");
    break;
  case ERF: 
    printf("erf(");
    printTree(tree->child1);
    printf(")");
    break;
  case ERFC:
    printf("erfc(");
    printTree(tree->child1);
    printf(")");
    break;
  case LOG_1P:
    printf("log1p(");
    printTree(tree->child1);
    printf(")");
    break;
  case EXP_M1:
    printf("expm1(");
    printTree(tree->child1);
    printf(")");
    break;
  case DOUBLEEXTENDED:
    printf("doubleextended(");
    printTree(tree->child1);
    printf(")");
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	printf("diff(");
      }
      printf("%s(",tree->libFun->functionName);
      printTree(tree->child1);
      printf(")");
      for (i=1;i<=tree->libFunDeriv;i++) {
	printf(")");
      }
    }
    break;
  case CEIL:
    printf("ceil(");
    printTree(tree->child1);
    printf(")");
    break;
  case FLOOR:
    printf("floor(");
    printTree(tree->child1);
    printf(")");
    break;
  case PI_CONST:
    printf("pi");
    break;
  default:
   fprintf(stderr,"Error: printTree: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}

char *sprintTree(node *tree) {
  int pred, i;
  char *buffer, *buffer1, *buffer2, *finalBuffer, *tempBuf;

  buffer1 = NULL;
  buffer2 = NULL;
  if (fullParentheses) pred = 100; else pred = precedence(tree);
  switch (tree->nodeType) {
  case VARIABLE:
    buffer = (char *) safeCalloc(strlen(variablename)+1,sizeof(char));
    sprintf(buffer,"%s",variablename);
    break;
  case CONSTANT:
    buffer = sprintValue(tree->value);
    break;
  case ADD:
    buffer1 = sprintTree(tree->child1);
    buffer2 = sprintTree(tree->child2);
    buffer = (char *) safeCalloc(strlen(buffer1) + strlen(buffer2) + 9, sizeof(char));
    tempBuf = buffer;
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,")");
    tempBuf += sprintf(tempBuf," + ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      tempBuf += sprintf(tempBuf,")");
    break;
  case SUB:
    buffer1 = sprintTree(tree->child1);
    buffer2 = sprintTree(tree->child2);
    buffer = (char *) safeCalloc(strlen(buffer1) + strlen(buffer2) + 9, sizeof(char));
    tempBuf = buffer;
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,")");
    tempBuf += sprintf(tempBuf," - ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      tempBuf += sprintf(tempBuf,")");
    break;
  case MUL:
    buffer1 = sprintTree(tree->child1);
    buffer2 = sprintTree(tree->child2);
    buffer = (char *) safeCalloc(strlen(buffer1) + strlen(buffer2) + 9, sizeof(char));
    tempBuf = buffer;
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,")");
    tempBuf += sprintf(tempBuf," * ");
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer2);
    if (isInfix(tree->child2) && (precedence(tree->child2) < pred)) 
      tempBuf += sprintf(tempBuf,")");
    break;
  case DIV:
    buffer1 = sprintTree(tree->child1);
    buffer2 = sprintTree(tree->child2);
    buffer = (char *) safeCalloc(strlen(buffer1) + strlen(buffer2) + 9, sizeof(char));
    tempBuf = buffer;
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer1);
    if (isInfix(tree->child1) && (precedence(tree->child1) < pred) && (tree->child1->nodeType != CONSTANT)) 
      tempBuf += sprintf(tempBuf,")");
    tempBuf += sprintf(tempBuf," / ");
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer2);
    if (isInfix(tree->child2) && (precedence(tree->child2) <= pred)) 
      tempBuf += sprintf(tempBuf,")");
    break;
  case SQRT:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"sqrt(%s)",buffer1);
    break;
  case EXP:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"exp(%s)",buffer1);
    break;
  case LOG:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"log(%s)",buffer1);
    break;
  case LOG_2:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"log2(%s)",buffer1);
    break;
  case LOG_10:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"log10(%s)",buffer1);
    break;
  case SIN:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"sin(%s)",buffer1);
    break;
  case COS:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"cos(%s)",buffer1);
    break;
  case TAN:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"tan(%s)",buffer1);
    break;
  case ASIN:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"asin(%s)",buffer1);
    break;
  case ACOS:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"acos(%s)",buffer1);
    break;
  case ATAN:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"atan(%s)",buffer1);
    break;
  case SINH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"sinh(%s)",buffer1);
    break;
  case COSH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"cosh(%s)",buffer1);
    break;
  case TANH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"tanh(%s)",buffer1);
    break;
  case ASINH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"asinh(%s)",buffer1);
    break;
  case ACOSH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"acosh(%s)",buffer1);
    break;
  case ATANH:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"atanh(%s)",buffer1);
    break;
  case POW:
    buffer1 = sprintTree(tree->child1);
    buffer2 = sprintTree(tree->child2);
    buffer = (char *) safeCalloc(strlen(buffer1) + strlen(buffer2) + 9, sizeof(char));
    tempBuf = buffer;
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer1);
    if (isInfix(tree->child1) && (precedence(tree->child1) <= pred)) 
      tempBuf += sprintf(tempBuf,")");
    tempBuf += sprintf(tempBuf,"^");
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) 
      tempBuf += sprintf(tempBuf,"(");
    tempBuf += sprintf(tempBuf,"%s",buffer2);
    if (isInfix(tree->child2) && ((precedence(tree->child2) <= pred)
				  || ((tree->child2->nodeType == CONSTANT) 
				      && ((dyadic == 2) || (dyadic == 3))))) 
      tempBuf += sprintf(tempBuf,")");
    break;
  case NEG:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 4, sizeof(char));
    if (isInfix(tree->child1)) sprintf(buffer,"-(%s)",buffer1); else sprintf(buffer,"-%s",buffer1);
    break;
  case ABS:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"abs(%s)",buffer1);
    break;
  case DOUBLE:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 10, sizeof(char));
    sprintf(buffer,"double(%s)",buffer1);
    break;
  case DOUBLEDOUBLE:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 16, sizeof(char));
    sprintf(buffer,"doubledouble(%s)",buffer1);
    break;
  case TRIPLEDOUBLE:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 16, sizeof(char));
    sprintf(buffer,"tripledouble(%s)",buffer1);
    break;
  case ERF: 
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"erf(%s)",buffer1);
    break;
  case ERFC:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"erfc(%s)",buffer1);
    break;
  case LOG_1P:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"log1p(%s)",buffer1);
    break;
  case EXP_M1:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"expm1(%s)",buffer1);
    break;
  case DOUBLEEXTENDED:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 19, sizeof(char));
    sprintf(buffer,"doubleextended(%s)",buffer1);
    break;
  case LIBRARYFUNCTION:
    {
      buffer1 = sprintTree(tree->child1);
      buffer = (char *) safeCalloc(strlen(buffer1) + strlen(tree->libFun->functionName) + 4 + (6 * tree->libFunDeriv),sizeof(char));
      tempBuf = buffer;
      for (i=1;i<=tree->libFunDeriv;i++) {
	tempBuf += sprintf(tempBuf,"diff(");
      }
      tempBuf += sprintf(tempBuf,"%s(%s)",tree->libFun->functionName,buffer1);
      for (i=1;i<=tree->libFunDeriv;i++) {
	tempBuf += sprintf(tempBuf,")");
      }
    }
    break;
  case CEIL:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 8, sizeof(char));
    sprintf(buffer,"ceil(%s)",buffer1);
    break;
  case FLOOR:
    buffer1 = sprintTree(tree->child1);
    buffer = (char *) safeCalloc(strlen(buffer1) + 9, sizeof(char));
    sprintf(buffer,"floor(%s)",buffer1);
    break;
  case PI_CONST:
    buffer = (char *) safeCalloc(3, sizeof(char));
    sprintf(buffer,"pi");
    break;
  default:
   fprintf(stderr,"Error: sprintTree: unknown identifier in the tree\n");
   exit(1);
  }

  finalBuffer = (char *) safeCalloc(strlen(buffer)+1,sizeof(char));
  sprintf(finalBuffer,"%s",buffer);
  free(buffer);
  if (buffer1 != NULL) free(buffer1);
  if (buffer2 != NULL) free(buffer2);
  return finalBuffer;
}


void fprintTree(FILE *fd, node *tree) {
  int i;

  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename != NULL) fprintf(fd,"%s",variablename); else fprintf(fd,"x");
    break;
  case CONSTANT:
    fprintValue(fd,*(tree->value));
    break;
  case ADD:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," + ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case SUB:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," - ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case MUL:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," * ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case DIV:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd," / ");
    if (isInfix(tree->child2)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child2);
    if (isInfix(tree->child2)) 
      fprintf(fd,")");
    break;
  case SQRT:
    fprintf(fd,"sqrt(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP:
    fprintf(fd,"exp(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG:
    fprintf(fd,"log(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_2:
    fprintf(fd,"log2(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_10:
    fprintf(fd,"log10(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SIN:
    fprintf(fd,"sin(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COS:
    fprintf(fd,"cos(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TAN:
    fprintf(fd,"tan(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASIN:
    fprintf(fd,"asin(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOS:
    fprintf(fd,"acos(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATAN:
    fprintf(fd,"atan(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SINH:
    fprintf(fd,"sinh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COSH:
    fprintf(fd,"cosh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TANH:
    fprintf(fd,"tanh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASINH:
    fprintf(fd,"asinh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOSH:
    fprintf(fd,"acosh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATANH:
    fprintf(fd,"atanh(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case POW:
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    fprintf(fd,"^(");
    fprintTree(fd,tree->child2);
    fprintf(fd,")");
    break;
  case NEG:
    fprintf(fd,"-");
    if (isInfix(tree->child1)) 
      fprintf(fd,"(");
    fprintTree(fd,tree->child1);
    if (isInfix(tree->child1)) 
      fprintf(fd,")");
    break;
  case ABS:
    fprintf(fd,"abs(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLE:
    fprintf(fd,"double(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERF: 
    fprintf(fd,"erf(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERFC:
    fprintf(fd,"erfc(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_1P:
    fprintf(fd,"log1p(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP_M1:
    fprintf(fd,"expm1(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,"diff(");
      }
      fprintf(fd,"%s(",tree->libFun->functionName);
      fprintTree(fd,tree->child1);
      fprintf(fd,")");
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,")");
      }
    }
    break;
  case CEIL:
    fprintf(fd,"ceil(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case FLOOR:
    fprintf(fd,"floor(");
    fprintTree(fd,tree->child1);
    fprintf(fd,")");
    break;
  case PI_CONST:
    fprintf(fd,"pi");
    break;
  default:
   fprintf(stderr,"Error: fprintTree: unknown identifier in the tree\n");
   exit(1);
  }
  return;
}




node* copyTree(node *tree) {
  node *copy;
  mpfr_t *value;
  mp_prec_t prec, p;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    prec = tools_precision;
    p = mpfr_get_prec(*(tree->value));
    if (p > prec) prec = p;
    mpfr_init2(*value,prec);
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = copyTree(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = copyTree(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = copyTree(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = copyTree(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = copyTree(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = copyTree(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = copyTree(tree->child1);
    copy->child2 = copyTree(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = copyTree(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = copyTree(tree->child1);
    break;
  case ERF: 
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = copyTree(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = copyTree(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = copyTree(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = copyTree(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = copyTree(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = copyTree(tree->child1);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = copyTree(tree->child1);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = copyTree(tree->child1);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: copyTree: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}

node *dividePolynomialByPowerOfVariableUnsafe(node *tree, int alpha);

node* simplifyTreeErrorfreeInner(node *tree, int rec) {
  node *simplChild1, *simplChild2, *simplified, *recsimplified;
  mpfr_t *value;
  mpfr_t temp;
  mp_prec_t prec, p;
  int alpha, beta;
  node *temp1, *temp2, *temp3, *temp4;

  
  if ((tree->nodeType == DIV) && 
      (isPolynomial(tree->child1)) &&
      (isPolynomial(tree->child1)) &&
      ((alpha = getMaxPowerDivider(tree->child1)) > 0) && 
      ((beta = getMaxPowerDivider(tree->child2)) > 0)) {
    if (alpha == beta) {
      temp1 = dividePolynomialByPowerOfVariableUnsafe(tree->child1, alpha);
      temp2 = dividePolynomialByPowerOfVariableUnsafe(tree->child2, alpha);
      temp3 = (node *) safeMalloc(sizeof(node));
      temp3->nodeType = DIV;
      temp3->child1 = temp1;
      temp3->child2 = temp2;
      temp4 = simplifyTreeErrorfreeInner(temp3,rec);
      free_memory(temp3);
      return temp4;
    } else {
      temp1 = (node *) safeMalloc(sizeof(node));
      temp1->nodeType = DIV;
      temp1->child1 = copyTree(tree->child1);
      temp2 = (node *) safeMalloc(sizeof(node));
      temp1->child2 = temp2;
      temp2->nodeType = POW;
      temp2->child1 = (node *) safeMalloc(sizeof(node));
      temp2->child1->nodeType = VARIABLE;
      temp2->child2 = (node *) safeMalloc(sizeof(node));
      temp2->child2->nodeType = CONSTANT;
      temp2->child2->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(temp2->child2->value),8 * sizeof(int) + 10);
      mpfr_set_si(*(temp2->child2->value),alpha,GMP_RNDN);
      temp3 = simplifyTreeErrorfreeInner(temp1, rec);
      free_memory(temp1);
      temp1 = (node *) safeMalloc(sizeof(node));
      temp1->nodeType = DIV;
      temp1->child1 = copyTree(tree->child2);
      temp2 = (node *) safeMalloc(sizeof(node));
      temp1->child2 = temp2;
      temp2->nodeType = POW;
      temp2->child1 = (node *) safeMalloc(sizeof(node));
      temp2->child1->nodeType = VARIABLE;
      temp2->child2 = (node *) safeMalloc(sizeof(node));
      temp2->child2->nodeType = CONSTANT;
      temp2->child2->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(temp2->child2->value),8 * sizeof(int) + 10);
      mpfr_set_si(*(temp2->child2->value),beta,GMP_RNDN);
      temp4 = simplifyTreeErrorfreeInner(temp1, rec);
      free_memory(temp1);
      temp1 = (node *) safeMalloc(sizeof(node));
      temp1->nodeType = DIV;
      temp1->child1 = temp3;
      temp1->child2 = temp4;
      temp2 = simplifyTreeErrorfreeInner(temp1, rec);
      free_memory(temp1);
      if (alpha > beta) {
	temp1 = (node *) safeMalloc(sizeof(node));
	temp1->nodeType = POW;
	temp1->child1 = (node *) safeMalloc(sizeof(node));
	temp1->child1->nodeType = VARIABLE;
	temp1->child2 = (node *) safeMalloc(sizeof(node));
	temp1->child2->nodeType = CONSTANT;
	temp1->child2->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(temp1->child2->value),8 * sizeof(int) + 10);
	mpfr_set_si(*(temp1->child2->value),alpha - beta,GMP_RNDN);
      } else {
	temp3 = (node *) safeMalloc(sizeof(node));
	temp3->nodeType = POW;
	temp3->child1 = (node *) safeMalloc(sizeof(node));
	temp3->child1->nodeType = VARIABLE;
	temp3->child2 = (node *) safeMalloc(sizeof(node));
	temp3->child2->nodeType = CONSTANT;
	temp3->child2->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(temp3->child2->value),8 * sizeof(int) + 10);
	mpfr_set_si(*(temp3->child2->value),beta - alpha,GMP_RNDN);
	temp1 = (node *) safeMalloc(sizeof(node));
	temp1->nodeType = DIV;
	temp1->child2 = temp3;
	temp1->child1 = (node *) safeMalloc(sizeof(node));
	temp1->child1->nodeType = CONSTANT;
	temp1->child1->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(temp1->child1->value),12);
	mpfr_set_si(*(temp1->child1->value),1,GMP_RNDN);
      }
      temp4 = (node *) safeMalloc(sizeof(node));
      temp4->nodeType = MUL;
      temp4->child1 = temp2;
      temp4->child2 = simplifyTreeErrorfreeInner(temp1,rec);
      free_memory(temp1);
      return temp4;
    }
  }



  switch (tree->nodeType) {
  case VARIABLE:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = VARIABLE;
    break;
  case CONSTANT:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,mpfr_get_prec(*(tree->value)) + 10);
    simplifyMpfrPrec(*value, *(tree->value));
    simplified->value = value;
    break;
  case ADD:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplChild2 = simplifyTreeErrorfreeInner(tree->child2,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      prec = 2 * tools_precision;
      p = 2 * mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      p = 2 * mpfr_get_prec(*(simplChild2->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_add(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ADD;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free(simplified);
	simplified = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  if (simplChild1->nodeType == NEG) {
	    simplified->nodeType = SUB;
	    simplified->child1 = simplChild2;
	    simplified->child2 = copyTree(simplChild1->child1);
	    free_memory(simplChild1);
	    if (rec > 0) {
	      recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
	      free_memory(simplified);
	      simplified = recsimplified;
	    }
	  } else {
	    if (simplChild2->nodeType == NEG) {
	      simplified->nodeType = SUB;
	      simplified->child1 = simplChild1;
	      simplified->child2 = copyTree(simplChild2->child1);
	      free_memory(simplChild2);
	      if (rec > 0) {
		recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
		free_memory(simplified);
		simplified = recsimplified;
	      }
	    } else {
	      if (isSyntacticallyEqual(simplChild1,simplChild2)) {
		simplified->nodeType = MUL;
		simplified->child1 = (node *) safeMalloc(sizeof(node));
		simplified->child1->nodeType = CONSTANT;
		simplified->child1->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
		mpfr_init2(*(simplified->child1->value),tools_precision);
		mpfr_set_d(*(simplified->child1->value),2.0,GMP_RNDN);
		simplified->child2 = simplChild1;
		free_memory(simplChild2);
		if (rec > 0) {
		  recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
		  free_memory(simplified);
		  simplified = recsimplified;
		}
	      } else {
		simplified->nodeType = ADD;
		simplified->child1 = simplChild1;
		simplified->child2 = simplChild2;
	      }
	    }
	  }
	}
      }
    }
    break;
  case SUB:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplChild2 = simplifyTreeErrorfreeInner(tree->child2,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      prec = 2 * tools_precision;
      p = 2 * mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      p = 2 * mpfr_get_prec(*(simplChild2->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_sub(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SUB;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	simplified->nodeType = NEG;
	simplified->child1 = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  if (isSyntacticallyEqual(simplChild1,simplChild2)) {
	    free_memory(simplChild1);
	    free_memory(simplChild2);
	    simplified->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    simplified->value = value;
	    mpfr_set_d(*value,0.0,GMP_RNDN);
	  } else {
	    if (simplChild2->nodeType == NEG) {
	      simplified->nodeType = ADD;
	      simplified->child1 = simplChild1;
	      simplified->child2 = copyTree(simplChild2->child1);
	      free_memory(simplChild2);
	    } else {
	      if ((simplChild1->nodeType == EXP) &&
		  (simplChild2->nodeType == CONSTANT) &&
		  (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
		simplified->nodeType = EXP_M1;
		simplified->child1 = copyTree(simplChild1->child1);
		free_memory(simplChild1);
		free_memory(simplChild2);
	      } else {
		simplified->nodeType = SUB;
		simplified->child1 = simplChild1;
		simplified->child2 = simplChild2;
	      }
	    }
	  }
	}
      }
    }
    break;
  case MUL:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplChild2 = simplifyTreeErrorfreeInner(tree->child2,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      prec = 2 * tools_precision;
      p = 2 * mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      p = 2 * mpfr_get_prec(*(simplChild2->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_mul(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = MUL;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if (((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) ||
	  ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value))))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild1->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild1->value),1.0) == 0)) {
	  free_memory(simplChild1);
	  free(simplified);
	  simplified = simplChild2;
	} else {
	  if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	    free_memory(simplChild2);
	    free(simplified);
	    simplified = simplChild1;
	  } else {
	    if ((simplChild1->nodeType == DIV) &&
		(simplChild1->child1->nodeType == CONSTANT) &&
		(mpfr_cmp_d(*(simplChild1->child1->value),1.0) == 0)) {
	      simplified->nodeType = DIV;
	      simplified->child1 = simplChild2;
	      simplified->child2 = copyTree(simplChild1->child2);
	      free_memory(simplChild1);
	    } else {
	      if ((simplChild2->nodeType == DIV) &&
		  (simplChild2->child1->nodeType == CONSTANT) &&
		  (mpfr_cmp_d(*(simplChild2->child1->value),1.0) == 0)) {
		simplified->nodeType = DIV;
		simplified->child1 = simplChild1;
		simplified->child2 = copyTree(simplChild2->child2);
		free_memory(simplChild2);
	      } else {
		if ((simplChild1->nodeType == NEG) &&
		    (simplChild2->nodeType == NEG)) {
		  simplified->nodeType = MUL;
		  simplified->child1 = copyTree(simplChild1->child1);
		  simplified->child2 = copyTree(simplChild2->child1);
		  free_memory(simplChild1);
		  free_memory(simplChild2);
		} else {
		  if (simplChild1->nodeType == NEG) {
		    simplified->nodeType = NEG;
		    simplified->child1 = (node *) safeMalloc(sizeof(node));
		    simplified->child1->nodeType = MUL;
		    simplified->child1->child1 = copyTree(simplChild1->child1);
		    simplified->child1->child2 = simplChild2;
		    free_memory(simplChild1);
		  } else {
		    if (simplChild2->nodeType == NEG) {
		      simplified->nodeType = NEG;
		      simplified->child1 = (node *) safeMalloc(sizeof(node));
		      simplified->child1->nodeType = MUL;
		      simplified->child1->child2 = copyTree(simplChild2->child1);
		      simplified->child1->child1 = simplChild1;
		      free_memory(simplChild2);
		    } else {
		      if ((simplChild1->nodeType == MUL) &&
			  (isConstant(simplChild2)) &&
			  (isConstant(simplChild1->child1))) {
			simplified->nodeType = MUL;
			simplified->child2 = simplChild1->child2;
			simplified->child1 = simplChild1;
			simplChild1->child2 = simplChild2;
			if (rec > 0) {
			  recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
			  free_memory(simplified);
			  simplified = recsimplified;
			}
		      } else {
			if ((simplChild1->nodeType == MUL) &&
			    (isConstant(simplChild2)) &&
			    (isConstant(simplChild1->child2))) {
			  simplified->nodeType = MUL;
			  simplified->child2 = simplChild1->child1;
			  simplified->child1 = simplChild1;
			  simplChild1->child1 = simplChild2;
			  if (rec > 0) {
			    recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
			    free_memory(simplified);
			    simplified = recsimplified;
			  }
			} else {
			  if ((simplChild2->nodeType == MUL) &&
			      (isConstant(simplChild1)) &&
			      (isConstant(simplChild2->child1))) {
			    simplified->nodeType = MUL;
			    simplified->child1 = simplChild2->child2;
			    simplified->child2 = simplChild2;
			    simplChild2->child2 = simplChild1;
			    if (rec > 0) {
			      recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
			      free_memory(simplified);
			      simplified = recsimplified;
			    }
			  } else {
			    if ((simplChild2->nodeType == MUL) &&
				(isConstant(simplChild1)) &&
				(isConstant(simplChild2->child2))) {
			      simplified->nodeType = MUL;
			      simplified->child1 = simplChild2->child1;
			      simplified->child2 = simplChild2;
			      simplChild2->child1 = simplChild1;
			      if (rec > 0) {
				recsimplified = simplifyTreeErrorfreeInner(simplified,rec-1);
				free_memory(simplified);
				simplified = recsimplified;
			      }
			    } else {
			      if ((simplChild2->nodeType == DIV) && 
				  (isSyntacticallyEqual(simplChild1,simplChild2->child2))) {
				free(simplified);
				free_memory(simplChild1);
				free_memory(simplChild2->child2);
				simplified = simplChild2->child1;
				free(simplChild2);
			      } else {
				if ((simplChild1->nodeType == DIV) && 
				    (isSyntacticallyEqual(simplChild2,simplChild1->child2))) {
				  free(simplified);
				  free_memory(simplChild2);
				  free_memory(simplChild1->child2);
				  simplified = simplChild1->child1;
				  free(simplChild1);
				} else {
				  simplified->nodeType = MUL;
				  simplified->child1 = simplChild1;
				  simplified->child2 = simplChild2;
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    break;
  case DIV:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplChild2 = simplifyTreeErrorfreeInner(tree->child2,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      prec = 2 * tools_precision;
      p = 2 * mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      p = 2 * mpfr_get_prec(*(simplChild2->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_div(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = DIV;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  if (isSyntacticallyEqual(simplChild1,simplChild2)) {
	    simplified->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    simplified->value = value;
	    mpfr_set_d(*value,1.0,GMP_RNDN);
	    free_memory(simplChild1);
	    free_memory(simplChild2);
	  } else {
	    if ((simplChild1->nodeType == NEG) &&
		(simplChild2->nodeType == NEG)) {
	      simplified->nodeType = DIV;
	      simplified->child1 = copyTree(simplChild1->child1);
	      simplified->child2 = copyTree(simplChild2->child1);
	      free_memory(simplChild1);
	      free_memory(simplChild2);
	    } else {
	      if (simplChild1->nodeType == NEG) {
		simplified->nodeType = NEG;
		simplified->child1 = (node *) safeMalloc(sizeof(node));
		simplified->child1->nodeType = DIV;
		simplified->child1->child1 = copyTree(simplChild1->child1);
		simplified->child1->child2 = simplChild2;
		free_memory(simplChild1);
	      } else {
		if (simplChild2->nodeType == NEG) {
		  simplified->nodeType = NEG;
		  simplified->child1 = (node *) safeMalloc(sizeof(node));
		  simplified->child1->nodeType = DIV;
		  simplified->child1->child2 = copyTree(simplChild2->child1);
		  simplified->child1->child1 = simplChild1;
		  free_memory(simplChild2);
		} else {
		  if (simplChild2->nodeType == DIV) {
		    simplified->nodeType = MUL;
		    simplified->child1 = simplChild1;
		    simplified->child2 = simplChild2->child2;
		    simplChild2->child2 = simplChild2->child1;
		    simplChild2->child1 = simplified->child2;
		    simplified->child2 = simplChild2;
		    if (rec > 0) {
		      recsimplified = simplifyTreeErrorfreeInner(simplified,rec);
		      free_memory(simplified);
		      simplified = recsimplified;
		    }
		  } else {
		    if (simplChild1->nodeType == DIV) {
		      simplified->nodeType = DIV;
		      simplified->child1 = simplChild1->child1;
		      simplified->child2 = simplChild1;
		      simplChild1->nodeType = MUL;
		      simplChild1->child1 = simplChild2;
		      if (rec > 0) {
			recsimplified = simplifyTreeErrorfreeInner(simplified,rec);
			free_memory(simplified);
			simplified = recsimplified;
		      }
		    } else {
		      if ((simplChild1->nodeType == SIN) &&
			  (simplChild2->nodeType == COS) &&
			  (isSyntacticallyEqual(simplChild1->child1,simplChild2->child1))) {
			simplified->nodeType = TAN;
			simplified->child1 = copyTree(simplChild1->child1);
			free_memory(simplChild1);
			free_memory(simplChild2);
		      } else {
			simplified->nodeType = DIV;
			simplified->child1 = simplChild1;
			simplified->child2 = simplChild2;
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    break;
  case SQRT:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      prec = tools_precision;
      p = mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_sqrt(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SQRT;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      if ((simplChild1->nodeType == POW) &&
	  (simplChild1->child2->nodeType == CONSTANT) &&
	  (mpfr_cmp_d(*(simplChild1->child2->value),2.0) == 0.0)) {
	simplified->nodeType = ABS;
	simplified->child1 = copyTree(simplChild1->child1);
	free_memory(simplChild1);
      } else {
	simplified->nodeType = SQRT;
	simplified->child1 = simplChild1;
      }
    }
    break;
  case EXP:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_exp(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = EXP;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = EXP;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      if ((simplChild1->nodeType == ADD) &&
	  (simplChild1->child1->nodeType == CONSTANT) &&
	  (mpfr_cmp_d(*(simplChild1->child1->value),1.0) == 0.0)) {
	simplified->nodeType = LOG_1P;
	simplified->child1 = copyTree(simplChild1->child2);
	free_memory(simplChild1);
      } else {
	if ((simplChild1->nodeType == ADD) &&
	    (simplChild1->child2->nodeType == CONSTANT) &&
	    (mpfr_cmp_d(*(simplChild1->child2->value),1.0) == 0.0)) {
	  simplified->nodeType = LOG_1P;
	  simplified->child1 = copyTree(simplChild1->child1);
	  free_memory(simplChild1);
	} else {
	  if (simplChild1->nodeType == EXP) {
	    free(simplified);
	    simplified = copyTree(simplChild1->child1);
	    free_memory(simplChild1);
	  } else {
	    simplified->nodeType = LOG;
	    simplified->child1 = simplChild1;
	  }
	}
      }
    }
    break;
  case LOG_2:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log2(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_2;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_2;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_10:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log10(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_10;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_10;
      simplified->child1 = simplChild1;
    }
    break;
  case SIN:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sin(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SIN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = SIN;
      simplified->child1 = simplChild1;
    }
    break;
  case COS:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_cos(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = COS;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = COS;
      simplified->child1 = simplChild1;
    }
    break;
  case TAN:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_tan(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = TAN;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TAN;
      simplified->child1 = simplChild1;
    }
    break;
  case ASIN:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      mpfr_init2(temp,53);
      mpfr_set_ui(temp,1,GMP_RNDN);
      if (mpfr_cmp(temp, *(simplChild1->value)) == 0) {
	mpfr_set_ui(*(simplChild1->value),2,GMP_RNDN);
	simplified->child2 = simplChild1;
	simplified->nodeType = DIV;
	simplified->child1 = (node *) safeMalloc(sizeof(node));
	simplified->child1->nodeType = PI_CONST;
      } else {
	mpfr_set_si(temp,-1,GMP_RNDN);
	if (mpfr_cmp(temp, *(simplChild1->value)) == 0) {
	  mpfr_set_si(*(simplChild1->value),-2,GMP_RNDN);
	  simplified->child2 = simplChild1;
	  simplified->nodeType = DIV;
	  simplified->child1 = (node *) safeMalloc(sizeof(node));
	  simplified->child1->nodeType = PI_CONST;
	} else {
	  simplified->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  simplified->value = value;
	  if ((mpfr_asin(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	      (!mpfr_number_p(*value))) {
	    simplified->nodeType = ASIN;
	    simplified->child1 = simplChild1;
	    mpfr_clear(*value);
	    free(value);
	  } else {
	    free_memory(simplChild1);
	  }
	}
      }
      mpfr_clear(temp);
    } else {
      simplified->nodeType = ASIN;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOS:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      mpfr_init2(temp,53);
      mpfr_set_si(temp,-1,GMP_RNDN);
      if (mpfr_cmp(temp, *(simplChild1->value)) == 0) {
	mpfr_set_ui(*(simplChild1->value),1,GMP_RNDN);
	simplified->child2 = simplChild1;
	simplified->nodeType = DIV;
	simplified->child1 = (node *) safeMalloc(sizeof(node));
	simplified->child1->nodeType = PI_CONST;
      } else {
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	simplified->value = value;
	if ((mpfr_acos(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	    (!mpfr_number_p(*value))) {
	  simplified->nodeType = ACOS;
	  simplified->child1 = simplChild1;
	  mpfr_clear(*value);
	  free(value);
	} else {
	  free_memory(simplChild1);
	}
      }
      mpfr_clear(temp);
    } else {
      simplified->nodeType = ACOS;
      simplified->child1 = simplChild1;
    }
    break;
  case ATAN:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      mpfr_init2(temp,53);
      mpfr_set_ui(temp,1,GMP_RNDN);
      if (mpfr_cmp(temp, *(simplChild1->value)) == 0) {
	mpfr_set_ui(*(simplChild1->value),4,GMP_RNDN);
	simplified->child2 = simplChild1;
	simplified->nodeType = DIV;
	simplified->child1 = (node *) safeMalloc(sizeof(node));
	simplified->child1->nodeType = PI_CONST;
      } else {
	mpfr_set_si(temp,-1,GMP_RNDN);
	if (mpfr_cmp(temp, *(simplChild1->value)) == 0) {
	  mpfr_set_si(*(simplChild1->value),-4,GMP_RNDN);
	  simplified->child2 = simplChild1;
	  simplified->nodeType = DIV;
	  simplified->child1 = (node *) safeMalloc(sizeof(node));
	  simplified->child1->nodeType = PI_CONST;
	} else {
	  simplified->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  simplified->value = value;
	  if ((mpfr_atan(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	      (!mpfr_number_p(*value))) {
	    simplified->nodeType = ATAN;
	    simplified->child1 = simplChild1;
	    mpfr_clear(*value);
	    free(value);
	  } else {
	    free_memory(simplChild1);
	  }
	}
      }
      mpfr_clear(temp);
    } else {
      simplified->nodeType = ATAN;
      simplified->child1 = simplChild1;
    }
    break;
  case SINH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_sinh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = SINH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = SINH;
      simplified->child1 = simplChild1;
    }
    break;
  case COSH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_cosh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = COSH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = COSH;
      simplified->child1 = simplChild1;
    }
    break;
  case TANH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_tanh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = TANH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TANH;
      simplified->child1 = simplChild1;
    }
    break;
  case ASINH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_asinh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ASINH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ASINH;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOSH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_acosh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ACOSH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ACOSH;
      simplified->child1 = simplChild1;
    }
    break;
  case ATANH:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_atanh(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ATANH;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ATANH;
      simplified->child1 = simplChild1;
    }
    break;
  case POW:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplChild2 = simplifyTreeErrorfreeInner(tree->child2,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_pow(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = POW;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
	free_memory(simplChild2);
      }
    } else {
      if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	free(simplified);
	free_memory(simplChild2);
	simplified = simplChild1;
      } else {
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if ((simplChild2->nodeType == CONSTANT) &&
	    (simplChild1->nodeType == POW) && 
	    (simplChild1->child2->nodeType == CONSTANT) &&
	    (mpfr_mul(*value,*(simplChild2->value),*(simplChild1->child2->value),GMP_RNDN) == 0)) {
	  free(simplified);
	  simplified = simplChild1;
	  mpfr_clear(*(simplified->child2->value));
	  free(simplified->child2->value);
	  simplified->child2->value = value;
	  free_memory(simplChild2);
	} else {
	  mpfr_clear(*value);
	  free(value);
	  if ((simplChild2->nodeType == CONSTANT) &&
	      (mpfr_cmp_d(*(simplChild2->value),2.0) == 0) &&
	      (simplChild1->nodeType == SQRT)) {	    
	    free(simplified);
	    simplified = copyTree(simplChild1->child1);
	    free_memory(simplChild1);
	    free_memory(simplChild2);
	  } else {
	    simplified->nodeType = POW;
	    simplified->child1 = simplChild1;
	    simplified->child2 = simplChild2;
	  }
	}
      }
    }
    break;
  case NEG:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      prec = tools_precision;
      p = mpfr_get_prec(*(simplChild1->value));
      if (p > prec) prec = p;
      prec += 10;
      if (prec > 256 * tools_precision) prec = 256 * tools_precision;
      mpfr_init2(*value,prec);
      simplified->value = value;
      if ((mpfr_neg(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = NEG;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      if (simplChild1->nodeType == NEG) {
	free(simplified);
	simplified = copyTree(simplChild1->child1);
	free_memory(simplChild1);
      } else {
	simplified->nodeType = NEG;
	simplified->child1 = simplChild1;
      }
    }
    break;
  case ABS:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_abs(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ABS;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      if (simplChild1->nodeType == ABS) {
	simplified->nodeType = ABS;
	simplified->child1 = copyTree(simplChild1->child1);
	free_memory(simplChild1);
      } else {
	simplified->nodeType = ABS;
	simplified->child1 = simplChild1;
      }
    }
    break;
  case DOUBLE:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_double(*value, *(simplChild1->value)); 
      if (!mpfr_number_p(*value)) {
	simplified->nodeType = DOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEDOUBLE:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubledouble(*value, *(simplChild1->value)); 
      if (!mpfr_number_p(*value)) {
	simplified->nodeType = DOUBLEDOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case TRIPLEDOUBLE:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_tripledouble(*value, *(simplChild1->value)); 
      if (!mpfr_number_p(*value)) {
	simplified->nodeType = TRIPLEDOUBLE;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = TRIPLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case ERF: 
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_erf(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ERF;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ERF;
      simplified->child1 = simplChild1;
    }
    break;
  case ERFC:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_erfc(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = ERFC;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = ERFC;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_1P:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_log1p(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = LOG_1P;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = LOG_1P;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP_M1:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_expm1(*value, *(simplChild1->value), GMP_RNDN) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = EXP_M1;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = EXP_M1;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEEXTENDED:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubleextended(*value, *(simplChild1->value)); 
      if (!mpfr_number_p(*value)) {
	simplified->nodeType = DOUBLEEXTENDED;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = DOUBLEEXTENDED;
      simplified->child1 = simplChild1;
    }
    break;
  case LIBRARYFUNCTION:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = LIBRARYFUNCTION;
    simplified->libFun = tree->libFun;
    simplified->libFunDeriv = tree->libFunDeriv;
    simplified->child1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    break;
  case CEIL:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_ceil(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = CEIL;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = CEIL;
      simplified->child1 = simplChild1;
    }
    break;
  case FLOOR:
    simplChild1 = simplifyTreeErrorfreeInner(tree->child1,rec);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      if ((mpfr_floor(*value, *(simplChild1->value)) != 0) || 
	  (!mpfr_number_p(*value))) {
	simplified->nodeType = FLOOR;
	simplified->child1 = simplChild1;
	mpfr_clear(*value);
	free(value);
      } else {
	free_memory(simplChild1);
      }
    } else {
      simplified->nodeType = FLOOR;
      simplified->child1 = simplChild1;
    }
    break;
  case PI_CONST:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = PI_CONST;
    break;
  default:
    fprintf(stderr,"Error: simplifyTreeErrorfreeInner: unknown identifier in the tree\n");
    exit(1);
  }

  return simplified;
}

node *simplifyTreeErrorfree(node *tree) {
  node *temp;
  temp = simplifyTreeErrorfreeInner(tree,1);
  if (verbosity >= 7) {
    if (!isSyntacticallyEqual(temp,tree)) {
      if (verbosity < 9) {
	printMessage(7,"Information: an expression has been simplified.\n");
      } else {
	changeToWarningMode();
	printMessage(9,"Information: expression '");
	printTree(tree);
	printMessage(9,"' has been simplified to expression '");
	printTree(temp);
	printMessage(9,"'.\n");
	restoreMode();
      }
    }
  }
  return temp;
}


int isPolynomial(node *tree);
node *differentiatePolynomialUnsafe(node *tree);

node* differentiateUnsimplified(node *tree) {
  node *derivative;
  mpfr_t *mpfr_temp;
  node *temp_node, *temp_node2, *temp_node3, *f_diff, *g_diff, *f_copy, *g_copy, *g_copy2, *h_copy, *h_copy2;
  node *temp_node4, *f_copy2, *temp_node5;

  if (isConstant(tree)) {
    mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
    temp_node = (node*) safeMalloc(sizeof(node));
    temp_node->nodeType = CONSTANT;
    temp_node->value = mpfr_temp;
    derivative = temp_node;    
  } else {
    if (isPolynomial(tree)) {
      derivative = differentiatePolynomialUnsafe(tree);
    } else {
      
      switch (tree->nodeType) {
      case VARIABLE:
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case CONSTANT:
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;    
	break;
      case ADD:
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = ADD;
	temp_node->child1 = differentiateUnsimplified(tree->child1);
	temp_node->child2 = differentiateUnsimplified(tree->child2);
	derivative = temp_node;
	break;
      case SUB:
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = SUB;
	temp_node->child1 = differentiateUnsimplified(tree->child1);
	temp_node->child2 = differentiateUnsimplified(tree->child2);
	derivative = temp_node;
	break;
      case MUL:
	if (tree->child1->nodeType == CONSTANT) {
	  f_diff = differentiateUnsimplified(tree->child2);
	  g_copy = copyTree(tree->child1);
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = g_copy;
	  temp_node->child2 = f_diff;
	  derivative = temp_node;
	} else {
	  if (tree->child2->nodeType == CONSTANT) {
	    f_diff = differentiateUnsimplified(tree->child1);
	    g_copy = copyTree(tree->child2);
	    temp_node = (node*) safeMalloc(sizeof(node));
	    temp_node->nodeType = MUL;
	    temp_node->child2 = g_copy;
	    temp_node->child1 = f_diff;
	    derivative = temp_node;
	  } else {
	    f_copy = copyTree(tree->child1);
	    g_copy = copyTree(tree->child2);
	    f_diff = differentiateUnsimplified(tree->child1);
	    g_diff = differentiateUnsimplified(tree->child2);
	    temp_node = (node*) safeMalloc(sizeof(node));
	    temp_node->nodeType = ADD;
	    temp_node2 = (node*) safeMalloc(sizeof(node));
	    temp_node2->nodeType = MUL;
	    temp_node3 = (node*) safeMalloc(sizeof(node));
	    temp_node3->nodeType = MUL;
	    temp_node->child1 = temp_node2;
	    temp_node->child2 = temp_node3;
	    temp_node2->child1 = f_copy;
	    temp_node2->child2 = g_diff;
	    temp_node3->child1 = g_copy;
	    temp_node3->child2 = f_diff;
	    derivative = temp_node;
	  }
	}
	break;
      case DIV:
	f_copy = copyTree(tree->child1);
	g_copy = copyTree(tree->child2);
	f_diff = differentiateUnsimplified(tree->child1);
	g_diff = differentiateUnsimplified(tree->child2);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = SUB;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node->child1 = temp_node2;
	temp_node->child2 = temp_node3;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = f_diff;
	temp_node3->child1 = f_copy;
	temp_node3->child2 = g_diff;
	g_copy = copyTree(tree->child2);
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = POW;
	temp_node2->child1 = g_copy;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node4->value = mpfr_temp;
	temp_node2->child2 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = DIV;
	temp_node3->child1 = temp_node;
	temp_node3->child2 = temp_node2;
	derivative = temp_node3;
	break;
      case SQRT:
	h_copy = copyTree(tree);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = temp_node3;
	temp_node2->child2 = h_copy;
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = DIV;
	temp_node->child1 = g_diff;
	temp_node->child2 = temp_node2;
	derivative = temp_node;
	break;
      case EXP:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = EXP;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;    
	derivative = temp_node;
	break;
      case LOG:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node2->child2 = g_copy;    
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case LOG_2:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node2->child2 = temp_node3;
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = LOG;
	temp_node3->child2 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case LOG_10:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node2->child2 = temp_node3;
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = LOG;
	temp_node3->child2 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,10.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case SIN:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = COS;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;
	derivative = temp_node;
	break;
      case COS:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SIN;
	temp_node2->child1 = g_copy;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node2;
	temp_node->child1 = temp_node3;
	derivative = temp_node;
	break;
      case TAN:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	h_copy = copyTree(tree);
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node4->value = mpfr_temp;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = POW;
	temp_node2->child2 = temp_node3;
	temp_node3->child1 = h_copy;
	temp_node3->child2 = temp_node4;
	derivative = temp_node;
	break;
      case ASIN:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = POW;
	temp_node3->child1 = g_copy;
	temp_node5 = (node*) safeMalloc(sizeof(node));
	temp_node5->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node5->value = mpfr_temp;
	temp_node3->child2 = temp_node5;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ACOS:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ATAN:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = g_copy2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = ADD;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = temp_node2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node2->child2 = temp_node4;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case SINH:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = COSH;
	temp_node2->child1 = g_copy;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case COSH:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SINH;
	temp_node2->child1 = g_copy;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case TANH:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = SUB;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	h_copy = copyTree(tree);
	h_copy2 = copyTree(tree);
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node2->child2 = temp_node3;
	temp_node3->child1 = h_copy;
	temp_node3->child2 = h_copy2;
	derivative = temp_node;
	break;
      case ASINH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ACOSH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = DIV;
	temp_node->child1 = temp_node4;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = MUL;
	temp_node3->child1 = g_copy;
	temp_node3->child2 = g_copy2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = ADD;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,-1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node2;
	temp_node4->child2 = temp_node3;
	derivative = temp_node;
	break;
      case ATANH:
	g_copy = copyTree(tree->child1);
	g_copy2 = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = MUL;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = g_copy2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = SUB;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = temp_node2;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	temp_node2->child2 = temp_node4;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case POW:
	if (tree->child2->nodeType == CONSTANT) {
	  g_copy = copyTree(tree->child2);
	  g_copy2 = copyTree(tree->child2);
	  f_diff = differentiateUnsimplified(tree->child1);      
	  f_copy = copyTree(tree->child1);
	  temp_node2 = (node*) safeMalloc(sizeof(node));
	  temp_node2->nodeType = MUL;
	  temp_node2->child1 = g_copy;
	  temp_node2->child2 = f_diff;
	  temp_node3 = (node*) safeMalloc(sizeof(node));
	  temp_node3->nodeType = SUB;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = CONSTANT;
	  mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*mpfr_temp,tools_precision);
	  mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	  temp_node4->value = mpfr_temp;
	  temp_node3->child2 = temp_node4;
	  temp_node3->child1 = g_copy2;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = POW;
	  temp_node4->child1 = f_copy;
	  temp_node4->child2 = temp_node3;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = temp_node4;
	  temp_node->child2 = temp_node2;
	  derivative = temp_node;
	} else {
	  h_copy = copyTree(tree);
	  f_diff = differentiateUnsimplified(tree->child1);
	  f_copy = copyTree(tree->child1);
	  f_copy2 = copyTree(tree->child1);
	  g_copy = copyTree(tree->child2);
	  g_diff = differentiateUnsimplified(tree->child2);
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = LOG;
	  temp_node4->child1 = f_copy;
	  temp_node3 = (node*) safeMalloc(sizeof(node));
	  temp_node3->nodeType = MUL;
	  temp_node3->child1 = g_diff;
	  temp_node3->child2 = temp_node4;
	  temp_node2 = (node*) safeMalloc(sizeof(node));
	  temp_node2->nodeType = MUL;
	  temp_node2->child1 = f_diff;
	  temp_node2->child2 = g_copy;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = DIV;
	  temp_node->child1 = temp_node2;
	  temp_node->child2 = f_copy2;
	  temp_node4 = (node*) safeMalloc(sizeof(node));
	  temp_node4->nodeType = ADD;
	  temp_node4->child1 = temp_node;
	  temp_node4->child2 = temp_node3;
	  temp_node = (node*) safeMalloc(sizeof(node));
	  temp_node->nodeType = MUL;
	  temp_node->child1 = h_copy;
	  temp_node->child2 = temp_node4;
	  derivative = temp_node;
	}
	break;
      case NEG:
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = NEG;
	temp_node->child1 = g_diff;
	derivative = temp_node;
	break;
      case ABS:
	g_copy = copyTree(tree->child1);
	h_copy = copyTree(tree);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;
	temp_node2->child2 = h_copy;
	derivative = temp_node;
	break;
      case DOUBLE:
	printMessage(1,
		     "Warning: the double rounding operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case DOUBLEDOUBLE:
	printMessage(1,
		     "Warning: the double-double rounding operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case TRIPLEDOUBLE:
	printMessage(1,
		     "Warning: the triple-double rounding operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case ERF: 
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = ATAN;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node4;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = POW;
	temp_node4->child1 = g_copy;
	temp_node4->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = EXP;
	temp_node4->child1 = temp_node3;
	temp_node2->child1 = temp_node4;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case ERFC:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = ATAN;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = SQRT;
	temp_node3->child1 = temp_node4;
	temp_node2->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,2.0,GMP_RNDN);
	temp_node3->nodeType = CONSTANT;
	temp_node3->value = mpfr_temp;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = POW;
	temp_node4->child1 = g_copy;
	temp_node4->child2 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node4 = (node *) safeMalloc(sizeof(node));
	temp_node4->nodeType = EXP;
	temp_node4->child1 = temp_node3;
	temp_node3 = (node *) safeMalloc(sizeof(node));
	temp_node3->nodeType = NEG;
	temp_node3->child1 = temp_node4;
	temp_node2->child1 = temp_node3;
	temp_node->child1 = temp_node2;
	derivative = temp_node;
	break;
      case LOG_1P:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = DIV;
	temp_node->child1 = temp_node2;
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node4 = (node*) safeMalloc(sizeof(node));
	temp_node4->nodeType = ADD;
	temp_node4->child1 = temp_node3;
	temp_node4->child2 = g_copy;
	temp_node2->child2 = temp_node4;    
	temp_node3 = (node*) safeMalloc(sizeof(node));
	temp_node3->nodeType = CONSTANT;
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
	temp_node3->value = mpfr_temp;
	temp_node2->child1 = temp_node3;
	derivative = temp_node;
	break;
      case EXP_M1:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = EXP;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;    
	derivative = temp_node;
	break;
      case DOUBLEEXTENDED:
	printMessage(1,
		     "Warning: the double-extended rounding operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case LIBRARYFUNCTION:
	g_copy = copyTree(tree->child1);
	g_diff = differentiateUnsimplified(tree->child1);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = MUL;
	temp_node->child2 = g_diff;
	temp_node2 = (node*) safeMalloc(sizeof(node));
	temp_node2->nodeType = LIBRARYFUNCTION;
	temp_node2->libFun = tree->libFun;
	temp_node2->libFunDeriv = tree->libFunDeriv + 1;
	temp_node->child1 = temp_node2;
	temp_node2->child1 = g_copy;    
	derivative = temp_node;
	break;
      case CEIL:
	printMessage(1,
		     "Warning: the ceil operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case FLOOR:
	printMessage(1,
		     "Warning: the floor operator is not differentiable.\nReplacing it by a constant function when differentiating.\n");
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;
	break;
      case PI_CONST:
	mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*mpfr_temp,tools_precision);
	mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
	temp_node = (node*) safeMalloc(sizeof(node));
	temp_node->nodeType = CONSTANT;
	temp_node->value = mpfr_temp;
	derivative = temp_node;    
	break;
      default:
	fprintf(stderr,"Error: differentiateUnsimplified: unknown identifier in the tree\n");
	exit(1);
      }
    }
  }
  return derivative;
}

int isHorner(node *);
int isCanonical(node *);

node* differentiate(node *tree) {
  node *temp, *temp3;

  printMessage(10,"Information: formally differentiating a function.\n");
  
  if (verbosity >= 11) {
    changeToWarningMode();
    printMessage(11,"Information: differentiating the expression '");
    printTree(tree);
    printf("'\n");
    restoreMode();
  }

  if (isPolynomial(tree) && (isHorner(tree) || isCanonical(tree))) {
    temp = differentiateUnsimplified(tree);
  } else {
    if ((treeSize(tree) > MAXDIFFSIMPLSIZE) || (getDegree(tree) > MAXDIFFSIMPLDEGREE)) {
      printMessage(7,"Information: will not simplify the given expression before differentiating because it is too big.\n");
      temp = differentiateUnsimplified(tree);
    } else {
      temp3 = simplifyTreeErrorfree(tree);
      temp = differentiateUnsimplified(temp3);
      free_memory(temp3);
    }
  }
  return temp;
}


int evaluateConstantExpression(mpfr_t result, node *tree, mp_prec_t prec) {
  mpfr_t stack1, stack2;
  int isConstant;

  mpfr_init2(stack1, prec);
  mpfr_init2(stack2, prec);

  switch (tree->nodeType) {
  case VARIABLE:
    isConstant = 0;
    break;
  case CONSTANT:
    mpfr_set(result, *(tree->value), GMP_RNDN);
    isConstant = 1;
    break;
  case ADD:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_add(result, stack1, stack2, GMP_RNDN);
    break;
  case SUB:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_sub(result, stack1, stack2, GMP_RNDN);
    break;
  case MUL:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_mul(result, stack1, stack2, GMP_RNDN);
    break;
  case DIV:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_div(result, stack1, stack2, GMP_RNDN);
    break;
  case SQRT:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sqrt(result, stack1, GMP_RNDN);
    break;
  case EXP:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_exp(result, stack1, GMP_RNDN);
    break;
  case LOG:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log(result, stack1, GMP_RNDN);
    break;
  case LOG_2:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG_10:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log10(result, stack1, GMP_RNDN);
    break;
  case SIN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sin(result, stack1, GMP_RNDN);
    break;
  case COS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_cos(result, stack1, GMP_RNDN);
    break;
  case TAN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_tan(result, stack1, GMP_RNDN);
    break;
  case ASIN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_asin(result, stack1, GMP_RNDN);
    break;
  case ACOS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_acos(result, stack1, GMP_RNDN);
    break;
  case ATAN:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_atan(result, stack1, GMP_RNDN);
    break;
  case SINH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_sinh(result, stack1, GMP_RNDN);
    break;
  case COSH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_cosh(result, stack1, GMP_RNDN);
    break;
  case TANH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_tanh(result, stack1, GMP_RNDN);
    break;
  case ASINH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_asinh(result, stack1, GMP_RNDN);
    break;
  case ACOSH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_acosh(result, stack1, GMP_RNDN);
    break;
  case ATANH:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_atanh(result, stack1, GMP_RNDN);
    break;
  case POW:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    isConstant = evaluateConstantExpression(stack2, tree->child2, prec);
    if (!isConstant) break;
    mpfr_pow(result, stack1, stack2, GMP_RNDN);
    break;
  case NEG:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_neg(result, stack1, GMP_RNDN);
    break;
  case ABS:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_abs(result, stack1, GMP_RNDN);
    break;
  case DOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_double(result, stack1);
    break;
  case DOUBLEDOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_doubledouble(result, stack1);
  case TRIPLEDOUBLE:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_tripledouble(result, stack1);
    break;
  case ERF:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_erf(result, stack1, GMP_RNDN);
    break;
  case ERFC:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_erfc(result, stack1, GMP_RNDN);
    break;
  case LOG_1P:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_log1p(result, stack1, GMP_RNDN);
    break;
  case EXP_M1:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_expm1(result, stack1, GMP_RNDN);
    break;
  case DOUBLEEXTENDED:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_round_to_doubleextended(result, stack1);
    break;
  case LIBRARYFUNCTION:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_from_mpfi(result, stack1, tree->libFunDeriv, tree->libFun->code);
    break;
  case CEIL:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_ceil(result, stack1);
    break;
  case FLOOR:
    isConstant = evaluateConstantExpression(stack1, tree->child1, prec);
    if (!isConstant) break;
    mpfr_floor(result, stack1);
    break;
  case PI_CONST:
    mpfr_const_pi(result, GMP_RNDN);
    isConstant = 1;
    break;
  default:
    fprintf(stderr,"Error: evaluateConstantExpression: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return isConstant;
} 


node* simplifyTreeInner(node *tree) {
  node *simplChild1, *simplChild2, *simplified;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = VARIABLE;
    break;
  case CONSTANT:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    simplifyMpfrPrec(*value,*(tree->value));
    simplified->value = value;
    break;
  case ADD:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplChild2 = simplifyTreeInner(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_add(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free(simplified);
	simplified = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = ADD;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case SUB:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplChild2 = simplifyTreeInner(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sub(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	simplified->nodeType = NEG;
	simplified->child1 = simplChild2;
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value)))) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = SUB;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case MUL:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplChild2 = simplifyTreeInner(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_mul(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if (((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) ||
	  ((simplChild2->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild2->value))))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild1->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild1->value),1.0) == 0)) {
	  free_memory(simplChild1);
	  free(simplified);
	  simplified = simplChild2;
	} else {
	  if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	    free_memory(simplChild2);
	    free(simplified);
	    simplified = simplChild1;
	  } else {
	    simplified->nodeType = MUL;
	    simplified->child1 = simplChild1;
	    simplified->child2 = simplChild2;
	  }
	}
      }
    }
    break;
  case DIV:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplChild2 = simplifyTreeInner(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_div(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild1->nodeType == CONSTANT) && (mpfr_zero_p(*(simplChild1->value)))) {
	free_memory(simplChild1);
	free_memory(simplChild2);
	simplified->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	simplified->value = value;
	mpfr_set_d(*value,0.0,GMP_RNDN);
      } else {
	if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	  free_memory(simplChild2);
	  free(simplified);
	  simplified = simplChild1;
	} else {
	  simplified->nodeType = DIV;
	  simplified->child1 = simplChild1;
	  simplified->child2 = simplChild2;
	}
      }
    }
    break;
  case SQRT:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sqrt(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SQRT;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_exp(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = EXP;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_2:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log2(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_2;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_10:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log10(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_10;
      simplified->child1 = simplChild1;
    }
    break;
  case SIN:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SIN;
      simplified->child1 = simplChild1;
    }
    break;
  case COS:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_cos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COS;
      simplified->child1 = simplChild1;
    }
    break;
  case TAN:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_tan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TAN;
      simplified->child1 = simplChild1;
    }
    break;
  case ASIN:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_asin(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASIN;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOS:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_acos(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOS;
      simplified->child1 = simplChild1;
    }
    break;
  case ATAN:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_atan(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATAN;
      simplified->child1 = simplChild1;
    }
    break;
  case SINH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_sinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = SINH;
      simplified->child1 = simplChild1;
    }
    break;
  case COSH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_cosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = COSH;
      simplified->child1 = simplChild1;
    }
    break;
  case TANH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_tanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TANH;
      simplified->child1 = simplChild1;
    }
    break;
  case ASINH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_asinh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ASINH;
      simplified->child1 = simplChild1;
    }
    break;
  case ACOSH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_acosh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ACOSH;
      simplified->child1 = simplChild1;
    }
    break;
  case ATANH:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_atanh(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ATANH;
      simplified->child1 = simplChild1;
    }
    break;
  case POW:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplChild2 = simplifyTreeInner(tree->child2);
    simplified = (node*) safeMalloc(sizeof(node));
    if ((simplChild1->nodeType == CONSTANT) && (simplChild2->nodeType == CONSTANT)) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_pow(*value, *(simplChild1->value), *(simplChild2->value), GMP_RNDN);
      free_memory(simplChild1);
      free_memory(simplChild2);
    } else {
      if ((simplChild2->nodeType == CONSTANT) && (mpfr_cmp_d(*(simplChild2->value),1.0) == 0)) {
	free(simplified);
	free_memory(simplChild2);
	simplified = simplChild1;
      } else {
	simplified->nodeType = POW;
	simplified->child1 = simplChild1;
	simplified->child2 = simplChild2;
      }
    }
    break;
  case NEG:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_neg(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = NEG;
      simplified->child1 = simplChild1;
    }
    break;
  case ABS:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_abs(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ABS;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLE:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_double(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEDOUBLE:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubledouble(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case TRIPLEDOUBLE:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_tripledouble(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = TRIPLEDOUBLE;
      simplified->child1 = simplChild1;
    }
    break;
  case ERF:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_erf(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ERF;
      simplified->child1 = simplChild1;
    }
    break;
  case ERFC:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_erfc(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = ERFC;
      simplified->child1 = simplChild1;
    }
    break;
  case LOG_1P:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_log1p(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LOG_1P;
      simplified->child1 = simplChild1;
    }
    break;
  case EXP_M1:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_expm1(*value, *(simplChild1->value), GMP_RNDN);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = EXP_M1;
      simplified->child1 = simplChild1;
    }
    break;
  case DOUBLEEXTENDED:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_round_to_doubleextended(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = DOUBLEEXTENDED;
      simplified->child1 = simplChild1;
    }
    break;
  case LIBRARYFUNCTION:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_from_mpfi(*value, *(simplChild1->value), tree->libFunDeriv, tree->libFun->code);
      free_memory(simplChild1);
    } else {
      simplified->nodeType = LIBRARYFUNCTION;
      simplified->child1 = simplChild1;
      simplified->libFun = tree->libFun;
      simplified->libFunDeriv = tree->libFunDeriv;
    }
    break;
  case CEIL:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_ceil(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = CEIL;
      simplified->child1 = simplChild1;
    }
    break;
  case FLOOR:
    simplChild1 = simplifyTreeInner(tree->child1);
    simplified = (node*) safeMalloc(sizeof(node));
    if (simplChild1->nodeType == CONSTANT) {
      simplified->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      simplified->value = value;
      mpfr_floor(*value, *(simplChild1->value));
      free_memory(simplChild1);
    } else {
      simplified->nodeType = FLOOR;
      simplified->child1 = simplChild1;
    }
    break;
  case PI_CONST:
    simplified = (node*) safeMalloc(sizeof(node));
    simplified->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_const_pi(*value,GMP_RNDN);
    simplified->value = value;
    break;
  default:
    fprintf(stderr,"Error: simplifyTreeInner: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }

  return simplified;
}

node *simplifyTree(node *tree) {
  node *temp, *temp2;

  temp = simplifyTreeErrorfree(tree);
  temp2 = simplifyTreeInner(temp);
  free_memory(temp);
  return temp2;
}


void evaluate(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec) {
  mpfr_t stack1, stack2;

  mpfr_init2(stack1, prec);
  mpfr_init2(stack2, prec);

  switch (tree->nodeType) {
  case VARIABLE:
    mpfr_set(result, x, GMP_RNDN);
    break;
  case CONSTANT:
    mpfr_set(result, *(tree->value), GMP_RNDN);
    break;
  case ADD:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_add(result, stack1, stack2, GMP_RNDN);
    break;
  case SUB:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_sub(result, stack1, stack2, GMP_RNDN);
    break;
  case MUL:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_mul(result, stack1, stack2, GMP_RNDN);
    break;
  case DIV:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_div(result, stack1, stack2, GMP_RNDN);
    break;
  case SQRT:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sqrt(result, stack1, GMP_RNDN);
    break;
  case EXP:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_exp(result, stack1, GMP_RNDN);
    break;
  case LOG:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log(result, stack1, GMP_RNDN);
    break;
  case LOG_2:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log2(result, stack1, GMP_RNDN);
    break;
  case LOG_10:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log10(result, stack1, GMP_RNDN);
    break;
  case SIN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sin(result, stack1, GMP_RNDN);
    break;
  case COS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_cos(result, stack1, GMP_RNDN);
    break;
  case TAN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_tan(result, stack1, GMP_RNDN);
    break;
  case ASIN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_asin(result, stack1, GMP_RNDN);
    break;
  case ACOS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_acos(result, stack1, GMP_RNDN);
    break;
  case ATAN:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_atan(result, stack1, GMP_RNDN);
    break;
  case SINH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_sinh(result, stack1, GMP_RNDN);
    break;
  case COSH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_cosh(result, stack1, GMP_RNDN);
    break;
  case TANH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_tanh(result, stack1, GMP_RNDN);
    break;
  case ASINH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_asinh(result, stack1, GMP_RNDN);
    break;
  case ACOSH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_acosh(result, stack1, GMP_RNDN);
    break;
  case ATANH:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_atanh(result, stack1, GMP_RNDN);
    break;
  case POW:
    evaluate(stack1, tree->child1, x, prec);
    evaluate(stack2, tree->child2, x, prec);
    mpfr_pow(result, stack1, stack2, GMP_RNDN);
    break;
  case NEG:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_neg(result, stack1, GMP_RNDN);
    break;
  case ABS:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_abs(result, stack1, GMP_RNDN);
    break;
  case DOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_double(result, stack1);
    break;
  case DOUBLEDOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_doubledouble(result, stack1);
    break;
  case TRIPLEDOUBLE:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_tripledouble(result, stack1);
    break;
  case ERF:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_erf(result, stack1, GMP_RNDN);
    break;
  case ERFC:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_erfc(result, stack1, GMP_RNDN);
    break;
  case LOG_1P:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_log1p(result, stack1, GMP_RNDN);
    break;
  case EXP_M1:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_expm1(result, stack1, GMP_RNDN);
    break;
  case DOUBLEEXTENDED:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_round_to_doubleextended(result, stack1);
    break;
  case LIBRARYFUNCTION:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_from_mpfi(result, stack1, tree->libFunDeriv, tree->libFun->code);
    break;
  case CEIL:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_ceil(result, stack1);
    break;
  case FLOOR:
    evaluate(stack1, tree->child1, x, prec);
    mpfr_floor(result, stack1);
    break;
  case PI_CONST:
    mpfr_const_pi(result, GMP_RNDN);
    break;
  default:
    fprintf(stderr,"Error: evaluate: unknown identifier in the tree\n");
    exit(1);
  }

  mpfr_clear(stack1); mpfr_clear(stack2);
  return;
}


int arity(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
  case PI_CONST:
    return 0;
    break;
  case ADD:
    return 2;
    break;
  case SUB:
    return 2;
    break;
  case MUL:
    return 2;
    break;
  case DIV:
    return 2;
    break;
  case SQRT:
    return 1;
    break;
  case EXP:
    return 1;
    break;
  case LOG:
    return 1;
    break;
  case LOG_2:
    return 1;
    break;
  case LOG_10:
    return 1;
    break;
  case SIN:
    return 1;
    break;
  case COS:
    return 1;
    break;
  case TAN:
    return 1;
    break;
  case ASIN:
    return 1;
    break;
  case ACOS:
    return 1;
    break;
  case ATAN:
    return 1;
    break;
  case SINH:
    return 1;
    break;
  case COSH:
    return 1;
    break;
  case TANH:
    return 1;
    break;
  case ASINH:
    return 1;
    break;
  case ACOSH:
    return 1;
    break;
  case ATANH:
    return 1;
    break;
  case POW:
    return 2;
    break;
  case NEG:
    return 1;
    break;
  case ABS:
    return 1;
    break;
  case DOUBLE:
    return 1;
    break;
  case DOUBLEDOUBLE:
    return 1;
    break;
  case TRIPLEDOUBLE:
    return 1;
    break;
  case ERF:
    return 1;
    break;
  case ERFC:
    return 1;
    break;
  case LOG_1P:
    return 1;
    break;
  case EXP_M1:
    return 1;
    break;
  case DOUBLEEXTENDED:
    return 1;
    break;
  case LIBRARYFUNCTION:
    return 1;
    break;
  case CEIL:
    return 1;
    break;
  case FLOOR:
    return 1;
    break;
  default:
    fprintf(stderr,"Error: arity: unknown identifier in the tree\n");
    exit(1);
  }
}


int isSyntacticallyEqual(node *tree1, node *tree2) {

  if (tree1->nodeType != tree2->nodeType) return 0;
  if (tree1->nodeType == PI_CONST) return 1;
  if ((tree1->nodeType == LIBRARYFUNCTION) && 
      ((tree1->libFun != tree2->libFun) ||
       (tree1->libFunDeriv != tree2->libFunDeriv))) return 0;
  if (tree1->nodeType == CONSTANT) {
    if (mpfr_equal_p(*(tree1->value),*(tree2->value))) 
      return 1;
    else 
      return 0;
  }
  if (tree1->nodeType == VARIABLE) return 1;

  if (arity(tree1) == 1) {
    if (!isSyntacticallyEqual(tree1->child1,tree2->child1)) return 0;
  } else {
    if (!isSyntacticallyEqual(tree1->child1,tree2->child1)) return 0;
    if (!isSyntacticallyEqual(tree1->child2,tree2->child2)) return 0;
  }

  return 1;
}



int isConstant(node *tree);

int isPolynomial(node *tree) {
  int res;
  node *temp;
  
  if (isConstant(tree)) return 1;

  switch (tree->nodeType) {
  case VARIABLE:
    res = 1;
    break;
  case CONSTANT:
    res = 1;
    break;
  case ADD:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case SUB:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case MUL:
    res = isPolynomial(tree->child1) && isPolynomial(tree->child2);
    break;
  case DIV:
    res = isPolynomial(tree->child1) && isConstant(tree->child2);
    break;
  case SQRT:
    res = 0;
    break;
  case EXP:
    res = 0;
    break;
  case LOG:
    res = 0;
    break;
  case LOG_2:
    res = 0;
    break;
  case LOG_10:
    res = 0;
    break;
  case SIN:
    res = 0;
    break;
  case COS:
    res = 0;
    break;
  case TAN:
    res = 0;
    break;
  case ASIN:
    res = 0;
    break;
  case ACOS:
    res = 0;
    break;
  case ATAN:
    res = 0;
    break;
  case SINH:
    res = 0;
    break;
  case COSH:
    res = 0;
    break;
  case TANH:
    res = 0;
    break;
  case ASINH:
    res = 0;
    break;
  case ACOSH:
    res = 0;
    break;
  case ATANH:
    res = 0;
    break;
  case POW:
    {
      res = 0;
      if (isConstant(tree)) {
	res = 1;
      } else {
	if (isPolynomial(tree->child1)) {
	  if (tree->child2->nodeType == CONSTANT) 
	    temp = tree->child2; 
	  else 
	    temp = simplifyTreeErrorfree(tree->child2);
	  if (temp->nodeType == CONSTANT) {
	    if (mpfr_integer_p(*(temp->value))) {
	      if (mpfr_sgn(*(temp->value)) >= 0) {
		res = 1;
	      }
	    }
	  }
	  if (tree->child2->nodeType != CONSTANT) free_memory(temp);
	}
      }
    }
    break;
  case NEG:
    res = isPolynomial(tree->child1);
    break;
  case ABS:
    res = 0;
    break;
  case DOUBLE:
    res = 0;
    break;
  case DOUBLEDOUBLE:
    res = 0;
    break;
  case TRIPLEDOUBLE:
    res = 0;
    break;
  case ERF:
    res = 0;
    break;
  case ERFC:
    res = 0;
    break;
  case LOG_1P:
    res = 0;
    break;
  case EXP_M1:
    res = 0;
    break;
  case DOUBLEEXTENDED:
    res = 0;
    break;
  case LIBRARYFUNCTION:
    res = 0;
    break;
  case CEIL:
    res = 0;
    break;
  case FLOOR:
    res = 0;
    break;
  case PI_CONST:
    res = 1;
    break;
  default:
    fprintf(stderr,"Error: isPolynomial: unknown identifier in the tree\n");
    exit(1);
  }
 return res;
}

#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) < (b) ? (a) : (b)

int getDegreeUnsafe(node *tree) {
  int l, r;
  mpfr_t temp;

  if (isConstant(tree)) return 0;

  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
  case PI_CONST:
    return 0;
    break;
  case ADD:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return MAX(l,r);
    break;
  case SUB:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return MAX(l,r);
    break;
  case MUL:
    l = getDegreeUnsafe(tree->child1);
    r = getDegreeUnsafe(tree->child2);
    return l + r;
    break;
  case DIV:
    return getDegreeUnsafe(tree->child1);
    break;
  case POW:
    {
      l = getDegreeUnsafe(tree->child1);
      if (tree->child2->nodeType != CONSTANT) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occurred. The exponent in a power operator is not constant.\n");
	exit(1);
      }
      if (!mpfr_integer_p(*(tree->child2->value))) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occurred. The exponent in a power operator is not integer.\n");
	exit(1);
      }
      if (mpfr_sgn(*(tree->child2->value)) < 0) {
	fprintf(stderr,"Error: getDegreeUnsafe: an error occurred. The exponent in a power operator is negative.\n");
	exit(1);
      }

      r = (int) mpfr_get_d(*(tree->child2->value),GMP_RNDN);
      mpfr_init2(temp,mpfr_get_prec(*(tree->child2->value)) + 10);
      mpfr_set_si(temp,r,GMP_RNDN);
      if (mpfr_cmp(*(tree->child2->value),temp) != 0) {
	printMessage(1, "Warning: tried to compute polynomial degree of an expression using a power operator with an exponent");
	printMessage(1," which cannot be represented on an integer variable.\n");
	mpfr_clear(temp);
	return -1;
      }
      mpfr_clear(temp);
      return l * r;
    }
    break;
  case NEG:
    return getDegreeUnsafe(tree->child1);
    break;
  default:
    fprintf(stderr,"Error: getDegreeUnsafe: an error occurred on handling the expression tree\n");
    exit(1);
  }
}

int getDegree(node *tree) {
  if (!isPolynomial(tree)) return -1;
  return getDegreeUnsafe(tree);
}

int getMaxPowerDividerUnsafe(node *tree) {
  int l, r;
  mpfr_t temp;

  if (isConstant(tree)) return 0;

  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
  case PI_CONST:
    return 0;
    break;
  case ADD:
    l = getMaxPowerDividerUnsafe(tree->child1);
    r = getMaxPowerDividerUnsafe(tree->child2);
    return MIN(l,r);
    break;
  case SUB:
    l = getMaxPowerDividerUnsafe(tree->child1);
    r = getMaxPowerDividerUnsafe(tree->child2);
    return MIN(l,r);
    break;
  case MUL:
    l = getMaxPowerDividerUnsafe(tree->child1);
    r = getMaxPowerDividerUnsafe(tree->child2);
    return l + r;
    break;
  case DIV:
    return getMaxPowerDividerUnsafe(tree->child1);
    break;
  case POW:
    {
      l = getMaxPowerDividerUnsafe(tree->child1);
      if (tree->child2->nodeType != CONSTANT) {
	fprintf(stderr,"Error: getMaxPowerDividerUnsafe: an error occurred. The exponent in a power operator is not constant.\n");
	exit(1);
      }
      if (!mpfr_integer_p(*(tree->child2->value))) {
	fprintf(stderr,"Error: getMaxPowerDividerUnsafe: an error occurred. The exponent in a power operator is not integer.\n");
	exit(1);
      }
      if (mpfr_sgn(*(tree->child2->value)) < 0) {
	fprintf(stderr,"Error: getMaxPowerDividerUnsafe: an error occurred. The exponent in a power operator is negative.\n");
	exit(1);
      }

      r = (int) mpfr_get_d(*(tree->child2->value),GMP_RNDN);
      mpfr_init2(temp,mpfr_get_prec(*(tree->child2->value)) + 10);
      mpfr_set_si(temp,r,GMP_RNDN);
      if (mpfr_cmp(*(tree->child2->value),temp) != 0) {
	printMessage(1,
"Warning: tried to compute degree of maximal polynomial divider of a polynomial in an expression using a power operator with an exponent ");
	printMessage(1,"which cannot be represented on an integer variable.\n");
	mpfr_clear(temp);
	return -1;
      }
      mpfr_clear(temp);
      return l * r;
    }
    break;
  case NEG:
    return getMaxPowerDividerUnsafe(tree->child1);
    break;
  default:
    fprintf(stderr,"Error: getMaxPowerDividerUnsafe: an error occurred on handling the expression tree\n");
    exit(1);
  }
}

int getMaxPowerDivider(node *tree) {
  if (!isPolynomial(tree)) return -1;
  return getMaxPowerDividerUnsafe(tree);
}





node* makeBinomial(node *a, node *b, int n, int s) {
  node *tree, *coeff, *aPow, *bPow, *tempNode, *tempNode2;
  mpfr_t *coeffVal, *mpfr_temp;
  unsigned int i;
  mpz_t coeffGMP;
  mp_prec_t prec;
  
  tree = (node*) safeMalloc(sizeof(node));
  tree->nodeType = CONSTANT;
  mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*mpfr_temp,tools_precision);
  mpfr_set_d(*mpfr_temp,0.0,GMP_RNDN);
  tree->value = mpfr_temp;
  mpz_init(coeffGMP);
  for (i=0;i<=((unsigned int) n);i++) {
    mpz_bin_uiui(coeffGMP,(unsigned int) n,i);
    prec = mpz_sizeinbase (coeffGMP, 2) + 10;
    if (prec < tools_precision) prec = tools_precision;
    coeffVal = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*coeffVal,prec);
    if(mpfr_set_z(*coeffVal,coeffGMP,GMP_RNDN) != 0) {
      if (!noRoundingWarnings) {
	printMessage(1,"Warning: on expanding a power operator a rounding occurred when calculating a binomial coefficient.\n");
	printMessage(1,"Try to increase the working precision.\n");
      }
    }
    if ((s < 0) && (((((unsigned int) n) - i) & 1) != 0)) {
      mpfr_neg(*coeffVal,*coeffVal,GMP_RNDN);
    }
    coeff = (node*) safeMalloc(sizeof(node));
    coeff->nodeType = CONSTANT;
    coeff->value = coeffVal;
    aPow = (node*) safeMalloc(sizeof(node));
    aPow->nodeType = POW;
    aPow->child1 = copyTree(a);
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    if(mpfr_set_ui(*mpfr_temp,i,GMP_RNDN) != 0) {
      if (!noRoundingWarnings) {
	printMessage(1,"Warning: on expanding a power operator a rounding occurred when calculating an exponent constant.\n");
	printMessage(1,"Try to increase the working precision.\n");
      }
    }
    tempNode->value = mpfr_temp;
    aPow->child2 = tempNode;
    bPow = (node*) safeMalloc(sizeof(node));
    bPow->nodeType = POW;
    bPow->child1 = copyTree(b);
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*mpfr_temp,tools_precision);
    if(mpfr_set_ui(*mpfr_temp,((unsigned int) n) - i,GMP_RNDN) != 0) {
      printMessage(1,"Warning: on expanding a power operator a rounding occurred when calculating an exponent constant.\n");
      printMessage(1,"Try to increase the working precision.\n");
    }
    tempNode->value = mpfr_temp;
    bPow->child2 = tempNode;
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = MUL;
    tempNode->child1 = coeff;
    tempNode->child2 = aPow;
    tempNode2 = (node*) safeMalloc(sizeof(node));
    tempNode2->nodeType = MUL;
    tempNode2->child1 = tempNode;
    tempNode2->child2 = bPow;
    tempNode = (node*) safeMalloc(sizeof(node));
    tempNode->nodeType = ADD;
    tempNode->child1 = tree;
    tempNode->child2 = tempNode2;
    tree = tempNode;
  }
  mpz_clear(coeffGMP);

  return tree;
}


node* expandPowerInPolynomialUnsafe(node *tree) {
  node *copy, *left, *tempTree, *tempTree2, *tempTree3;
  int r, i;
  mpfr_t temp;
  mpfr_t *value;

  if (isConstant(tree)) return copyTree(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    return copyTree(tree);
    break;
  case CONSTANT:
  case PI_CONST:
    return copyTree(tree);
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;    
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    copy->child2 = expandPowerInPolynomialUnsafe(tree->child2);
    return copy;
    break;
  case POW:
    {
      left = expandPowerInPolynomialUnsafe(tree->child1);
      if (tree->child2->nodeType != CONSTANT) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred. The exponent in a power operator is not constant.\n");
	exit(1);
      }
      if (!mpfr_integer_p(*(tree->child2->value))) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred. The exponent in a power operator is not integer.\n");
	exit(1);
      }
      if (mpfr_sgn(*(tree->child2->value)) < 0) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred. The exponent in a power operator is negative.\n");
	exit(1);
      }

      r = (int) mpfr_get_d(*(tree->child2->value),GMP_RNDN);
      mpfr_init2(temp,mpfr_get_prec(*(tree->child2->value)) + 10);
      mpfr_set_si(temp,r,GMP_RNDN);
      if (mpfr_cmp(*(tree->child2->value),temp) != 0) {
	fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred. Tried to expand an expression using a power operator with an exponent ");
	fprintf(stderr,"which cannot be represented on an integer variable.\n");
	mpfr_clear(temp);
	exit(1);
      }
      mpfr_clear(temp);
      if (r > 1) {
	switch (left->nodeType) {
	case VARIABLE:
	case CONSTANT:
	case PI_CONST:
	  tempTree = copyTree(left);
	  for (i=1;i<r;i++) {
	    tempTree2 = (node *) safeMalloc(sizeof(node));
	    tempTree2->nodeType = MUL;
	    tempTree2->child1 = tempTree;
	    tempTree2->child2 = copyTree(left);
	    tempTree = tempTree2;
	  }
	  break;
	case ADD:
	  tempTree = makeBinomial(left->child1,left->child2,r,1);
	  break;
	case SUB:
	  tempTree = makeBinomial(left->child1,left->child2,r,-1);
	  break;
	case MUL:
	  tempTree = (node *) safeMalloc(sizeof(node));
	  tempTree->nodeType = MUL;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child1);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child1 = tempTree2;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child2);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child2 = tempTree2;
	  break;
	case DIV:
	  tempTree = (node *) safeMalloc(sizeof(node));
	  tempTree->nodeType = DIV;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child1);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child1 = tempTree2;
	  tempTree2 = (node *) safeMalloc(sizeof(node));
	  tempTree2->nodeType = POW;
	  tempTree2->child1 = copyTree(left->child2);
	  tempTree3 = (node*) safeMalloc(sizeof(node));
	  tempTree3->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_si(*value,r,GMP_RNDN);
	  tempTree3->value = value;
	  tempTree2->child2 = tempTree3;
	  tempTree->child2 = tempTree2;
	  break;
	case NEG:
	  if (r & 1) {
	    /* r is odd */
	    tempTree = (node *) safeMalloc(sizeof(node));
	    tempTree->nodeType = NEG;
	    tempTree2 = (node *) safeMalloc(sizeof(node));
	    tempTree2->nodeType = POW;
	    tempTree2->child1 = copyTree(left->child1);
	    tempTree3 = (node*) safeMalloc(sizeof(node));
	    tempTree3->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    mpfr_set_si(*value,r,GMP_RNDN);
	    tempTree3->value = value;
	    tempTree2->child2 = tempTree3;
	    tempTree->child1 = tempTree2;
	  } else {
	    tempTree = (node *) safeMalloc(sizeof(node));
	    tempTree->nodeType = POW;
	    tempTree->child1 = copyTree(left->child1);
	    tempTree3 = (node*) safeMalloc(sizeof(node));
	    tempTree3->nodeType = CONSTANT;
	    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*value,tools_precision);
	    mpfr_set_si(*value,r,GMP_RNDN);
	    tempTree3->value = value;
	    tempTree->child2 = tempTree3;
	  }
	  break;
	default:
	  if (isConstant(left)) return copyTree(tree);

	  fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred on handling the expanded expression subtree\n");
	  exit(1);
	}
	copy = expandPowerInPolynomialUnsafe(tempTree);
	free_memory(tempTree);
      } else {
	if (r == 1) {
	  copy = copyTree(left);
	} else {
	  copy = (node*) safeMalloc(sizeof(node));
	  copy->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  mpfr_set_d(*value,1.0,GMP_RNDN);
	  copy->value = value;
	}
      }
      free_memory(left);
      return copy;
    }
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expandPowerInPolynomialUnsafe(tree->child1);
    return copy;
    break;
  default:

    if (isConstant(tree)) return copyTree(tree);

    fprintf(stderr,"Error: expandPowerInPolynomialUnsafe: an error occurred on handling the expression tree\n");
    exit(1);
  }
}

node* expandPowerInPolynomial(node *tree) {
  if (getDegree(tree) < 0) return copyTree(tree);
  return expandPowerInPolynomialUnsafe(tree);
}



node* expandDivision(node *tree) {
  node *copy, *left, *right, *tempNode;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case DIV:
    left = expandDivision(tree->child1);
    right = expandDivision(tree->child2);
    if (right->nodeType == DIV) {
      tempNode = right->child1;
      right->child1 = right->child2;
      right->child2 = tempNode;
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = MUL;
      copy->child1 = left;
      copy->child2 = right;
    } else {
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = DIV;
      copy->child1 = left;
      copy->child2 = right;
    }
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = expandDivision(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = expandDivision(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = expandDivision(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = expandDivision(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = expandDivision(tree->child1);
    copy->child2 = expandDivision(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = expandDivision(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = expandDivision(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = expandDivision(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = expandDivision(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = expandDivision(tree->child1);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = expandDivision(tree->child1);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = expandDivision(tree->child1);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: expandDivision: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}



node* expandPolynomialUnsafe(node *tree) {
  node *left, *right, *copy, *tempNode, *tempNode2, *tempNode3, *tempNode4; 
  mpfr_t *value;

  if (isConstant(tree)) return copyTree(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    return copyTree(tree);
    break;
  case CONSTANT:
  case PI_CONST:
    return copyTree(tree);
    break;
  case ADD:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = left;
    copy->child2 = right;
    return copy;    
    break;
  case SUB:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = left;
    copy->child2 = right;
    return copy;
    break;
  case MUL:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    switch (left->nodeType) {
    case VARIABLE:
    case CONSTANT:
    case PI_CONST:
      if (isConstant(right)) {
	copy = (node*) safeMalloc(sizeof(node));
	copy->nodeType = MUL;
	copy->child1 = left;
	copy->child2 = right;
      } else {
	switch (right->nodeType) {
	case VARIABLE:
	case CONSTANT:
	case PI_CONST:
	  copy = (node*) safeMalloc(sizeof(node));
	  copy->nodeType = MUL;
	  copy->child1 = left;
	  copy->child2 = right;
	  break;  
	default:
	  tempNode = (node*) safeMalloc(sizeof(node));
	  tempNode->nodeType = MUL;
	  tempNode->child1 = right;
	  tempNode->child2 = left;
	  copy = expandPolynomialUnsafe(tempNode);
	  free_memory(tempNode);
	}
      }
      break;
    case MUL:
      switch (right->nodeType) {
      case ADD:
      case SUB:
      case NEG:
      case DIV:      
	tempNode = (node*) safeMalloc(sizeof(node));
	tempNode->nodeType = MUL;
	tempNode->child1 = right;
	tempNode->child2 = left;
	copy = expandPolynomialUnsafe(tempNode);
	free_memory(tempNode);
	break;
      default:
	copy = (node*) safeMalloc(sizeof(node));
	copy->nodeType = MUL;
	copy->child1 = left;
	copy->child2 = right;
	break;  
      }
      break;  
    case ADD:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = ADD;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);
      break;
    case SUB:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = SUB;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case NEG:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = NEG;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case DIV:
      if (isConstant(left)) {
	if (isConstant(right)) {
	  copy = (node*) safeMalloc(sizeof(node));
	  copy->nodeType = MUL;
	  copy->child1 = left;
	  copy->child2 = right;
	} else {
	  switch (right->nodeType) {
	  case ADD:
	  case SUB:
	  case NEG:
	  case DIV:      
	    tempNode = (node*) safeMalloc(sizeof(node));
	    tempNode->nodeType = MUL;
	    tempNode->child1 = right;
	    tempNode->child2 = left;
	    copy = expandPolynomialUnsafe(tempNode);
	    free_memory(tempNode);
	    break;
	  default:
	    copy = (node*) safeMalloc(sizeof(node));
	    copy->nodeType = MUL;
	    copy->child1 = left;
	    copy->child2 = right;
	    break;  
	  }  
	}
      } else {
	tempNode = (node*) safeMalloc(sizeof(node));
	tempNode->nodeType = MUL;
	tempNode2 = (node*) safeMalloc(sizeof(node));
	tempNode2->nodeType = MUL;
	tempNode3 = (node*) safeMalloc(sizeof(node));
	tempNode3->nodeType = DIV;
	tempNode4 = (node*) safeMalloc(sizeof(node));
	tempNode4->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	mpfr_set_d(*value,1.0,GMP_RNDN);
	tempNode4->value = value;
	tempNode3->child1 = tempNode4;
	tempNode3->child2 = copyTree(left->child2);
	tempNode2->child1 = copyTree(left->child1);
	tempNode2->child2 = right;
	tempNode->child1 = tempNode3;
	tempNode->child2 = tempNode2;
	free_memory(left);
	copy = expandPolynomialUnsafe(tempNode);
	free_memory(tempNode);
      }      
      break;
    default:
      if (isConstant(left)) {
	if (isConstant(right)) {
	  return copyTree(tree);
	} else {
	  tempNode = (node*) safeMalloc(sizeof(node));
	  tempNode->nodeType = MUL;
	  tempNode->child1 = right;
	  tempNode->child2 = left;
	  copy = expandPolynomialUnsafe(tempNode);
	  free_memory(tempNode);
	  return copy;
	}
      } else {
	fprintf(stderr,"Error: expandPolynomialUnsafe: an error occurred on handling the MUL left rewritten expression subtree\n");
	exit(1);
      }
    }
    return copy;
    break;
  case DIV:
    left = expandPolynomialUnsafe(tree->child1);
    right = expandPolynomialUnsafe(tree->child2);
    switch (left->nodeType) {
    case CONSTANT:
    case PI_CONST:
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = DIV;
      copy->child1 = left;
      copy->child2 = right;
      break;  
    case VARIABLE:
      copy = (node*) safeMalloc(sizeof(node));
      copy->nodeType = MUL;
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = DIV;
      tempNode->child2 = right;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      tempNode2->value = value;
      tempNode->child1 = tempNode2;
      copy->child2 = left;
      copy->child1 = tempNode;
      break;
    case ADD:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = ADD;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);
      break;
    case SUB:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = SUB;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = copyTree(right);
      tempNode3->child1 = copyTree(left->child2);
      tempNode3->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode3;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case MUL:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = MUL;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode3 = (node*) safeMalloc(sizeof(node));
      tempNode3->nodeType = CONSTANT;
      value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      tempNode3->value = value;
      tempNode4 = (node*) safeMalloc(sizeof(node));
      tempNode4->nodeType = MUL;
      tempNode2->child1 = tempNode3;
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      tempNode->child2 = tempNode4;
      tempNode4->child1 = copyTree(left->child1);
      tempNode4->child2 = copyTree(left->child2);
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case DIV:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = DIV;
      tempNode->child1 = copyTree(left->child1);
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = MUL;
      tempNode2->child1 = copyTree(left->child2);
      tempNode2->child2 = right;
      tempNode->child2 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    case NEG:
      tempNode = (node*) safeMalloc(sizeof(node));
      tempNode->nodeType = NEG;
      tempNode2 = (node*) safeMalloc(sizeof(node));
      tempNode2->nodeType = DIV;
      tempNode2->child1 = copyTree(left->child1);
      tempNode2->child2 = right;
      tempNode->child1 = tempNode2;
      free_memory(left);
      copy = expandPolynomialUnsafe(tempNode);
      free_memory(tempNode);      
      break;
    default: 
      if (isConstant(left)) {
	return copyTree(tree);
      } else {
	fprintf(stderr,"Error: expandPolynomialUnsafe: an error occurred on handling the DIV left rewritten expression subtree\n");
	exit(1);
      }
    }
    return copy;
    break;
  case NEG:
    left = expandPolynomialUnsafe(tree->child1);
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = left;
    return copy;
    break;
  default:
    if (isConstant(tree)) {
      return copyTree(tree);
    } else {
      fprintf(stderr,"Error: expandPolynomialUnsafe: an error occurred on handling the expression tree\n");
      exit(1);
    }
  }
}



node* expandPolynomial(node *tree) {
  node *temp, *temp2;
  if (getDegree(tree) < 0) return copyTree(tree);
  temp = expandPowerInPolynomialUnsafe(tree);
  temp2 = expandPolynomialUnsafe(temp);
  free_memory(temp);
  return temp2;
}

node* expandUnsimplified(node *tree) {
  node *copy;
  mpfr_t *value;

  if (!isConstant(tree) && isPolynomial(tree)) return expandPolynomial(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = expand(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = expand(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = expand(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = expand(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = expand(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = expand(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = expand(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = expand(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = expand(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = expand(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = expand(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = expand(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = expand(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = expand(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = expand(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = expand(tree->child1);
    copy->child2 = expand(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = expand(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = expand(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = expand(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = expand(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = expand(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = expand(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = expand(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = expand(tree->child1);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = expand(tree->child1);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = expand(tree->child1);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: expand: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}

node* expand(node *tree) {
  node *temp, *temp2, *temp3;
  temp3 = expandDivision(tree);
  temp = expandUnsimplified(temp3);
  temp2 = simplifyTreeErrorfree(temp);
  free_memory(temp);
  free_memory(temp3);
  return temp2;
}



int isConstant(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    return 0;
    break;
  case CONSTANT:
  case PI_CONST:
    return 1;
    break;
  case ADD:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case SUB:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case MUL:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case DIV:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case SQRT:
    return isConstant(tree->child1);
    break;
  case EXP:
    return isConstant(tree->child1);
    break;
  case LOG:
    return isConstant(tree->child1);
    break;
  case LOG_2:
    return isConstant(tree->child1);
    break;
  case LOG_10:
    return isConstant(tree->child1);
    break;
  case SIN:
    return isConstant(tree->child1);
    break;
  case COS:
    return isConstant(tree->child1);
    break;
  case TAN:
    return isConstant(tree->child1);
    break;
  case ASIN:
    return isConstant(tree->child1);
    break;
  case ACOS:
    return isConstant(tree->child1);
    break;
  case ATAN:
    return isConstant(tree->child1);
    break;
  case SINH:
    return isConstant(tree->child1);
    break;
  case COSH:
    return isConstant(tree->child1);
    break;
  case TANH:
    return isConstant(tree->child1);
    break;
  case ASINH:
    return isConstant(tree->child1);
    break;
  case ACOSH:
    return isConstant(tree->child1);
    break;
  case ATANH:
    return isConstant(tree->child1);
    break;
  case POW:
    return (isConstant(tree->child1) & isConstant(tree->child2));
    break;
  case NEG:
    return isConstant(tree->child1);
    break;
  case ABS:
    return isConstant(tree->child1);
    break;
  case DOUBLE:
    return isConstant(tree->child1);
    break;
  case DOUBLEDOUBLE:
    return isConstant(tree->child1);
    break;
  case TRIPLEDOUBLE:
    return isConstant(tree->child1);
    break;
  case ERF:
    return isConstant(tree->child1);
    break;
  case ERFC:
    return isConstant(tree->child1);
    break;
  case LOG_1P:
    return isConstant(tree->child1);
    break;
  case EXP_M1:
    return isConstant(tree->child1);
    break;
  case DOUBLEEXTENDED:
    return isConstant(tree->child1);
    break;
  case LIBRARYFUNCTION:
    return isConstant(tree->child1);
    break;
  case CEIL:
    return isConstant(tree->child1);
    break;
  case FLOOR:
    return isConstant(tree->child1);
    break;
  default:
   fprintf(stderr,"Error: isConstant: unknown identifier in the tree\n");
   exit(1);
  }
}



int isMonomial(node *tree) {

  switch (tree->nodeType) {
  case MUL:
    return (isMonomial(tree->child1) & isMonomial(tree->child2));
    break;
  case NEG:
    return isMonomial(tree->child1);
    break;
  case VARIABLE:
    return 1;
    break;
  case DIV:
    return (isConstant(tree->child2)) & isMonomial(tree->child1);
  default: 
    return isConstant(tree);
  }
  return 0;
}



node* getCoefficientsInMonomialUnsafe(node *polynom) {
  node *leftSub, *rightSub, *coeffs;
  mpfr_t *value;

  if (isConstant(polynom)) return copyTree(polynom);

  if (polynom->nodeType == VARIABLE) return NULL;
 
  if (polynom->nodeType == MUL) {
    leftSub = getCoefficientsInMonomialUnsafe(polynom->child1);
    rightSub = getCoefficientsInMonomialUnsafe(polynom->child2);
    if ((leftSub == NULL) && (rightSub == NULL)) return NULL;
    if (leftSub == NULL) return rightSub;
    if (rightSub == NULL) return leftSub;
    coeffs = (node*) safeMalloc(sizeof(node));
    coeffs->nodeType = MUL;
    coeffs->child1 = leftSub;
    coeffs->child2 = rightSub;
    return coeffs;
  }

  if (polynom->nodeType == DIV) {
    leftSub = getCoefficientsInMonomialUnsafe(polynom->child1);
    if (leftSub == NULL) {
      coeffs = (node*) safeMalloc(sizeof(node));
      coeffs->nodeType = DIV;
      coeffs->child1 = (node *) safeMalloc(sizeof(node));
      coeffs->child1->nodeType = CONSTANT;
      coeffs->child1->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(coeffs->child1->value),10);
      mpfr_set_d(*(coeffs->child1->value),1.0,GMP_RNDN);
      coeffs->child2 = copyTree(polynom->child2);
    } else {
      coeffs = (node*) safeMalloc(sizeof(node));
      coeffs->nodeType = DIV;
      coeffs->child1 = leftSub;
      coeffs->child2 = copyTree(polynom->child2);
    }
    return coeffs;
  }


  if (polynom->nodeType == NEG) {
    leftSub = getCoefficientsInMonomialUnsafe(polynom->child1);
    rightSub = (node *) safeMalloc(sizeof(node));
    rightSub->nodeType = CONSTANT;
    value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set_d(*value,-1.0,GMP_RNDN);
    rightSub->value = value;
    if (leftSub == NULL) return rightSub;
    coeffs = (node*) safeMalloc(sizeof(node));
    coeffs->nodeType = MUL;
    coeffs->child1 = leftSub;
    coeffs->child2 = rightSub;
    return coeffs;
  }

  fprintf(stderr,"Error: getCoefficientsInMonomialUnsafe: an error occurred. The expression does not have the correct monomial form.\n");
  exit(1);
  return NULL;
}


void getCoefficientsUnsafe(node **monomials, node *polynom, int sign) {
  int degree;
  node *temp, *coeff, *temp2;
  mpfr_t *value;
  node *simplified, *simplifiedTemp;

 
  if (isMonomial(polynom)) {
    degree = getDegree(polynom);
    coeff = getCoefficientsInMonomialUnsafe(polynom);
    if (coeff == NULL) {
      coeff = (node *) safeMalloc(sizeof(node));
      coeff->nodeType = CONSTANT;
      value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*value,tools_precision);
      mpfr_set_d(*value,1.0,GMP_RNDN);
      coeff->value = value;
    }
    temp = monomials[degree];
    if (temp == NULL) {
      if (sign < 0) {
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = NEG;
	temp2->child1 = coeff;
	coeff = temp2;
      }
      temp = coeff;
    } else {
      temp2 = (node*) safeMalloc(sizeof(node));
      if (sign > 0) temp2->nodeType = ADD; else temp2->nodeType = SUB;
      temp2->child1 = temp;
      temp2->child2 = coeff;
      temp = temp2;
    }
    monomials[degree] = temp;
    return;
  }

  if (polynom->nodeType == ADD) {
    getCoefficientsUnsafe(monomials,polynom->child1,sign);
    getCoefficientsUnsafe(monomials,polynom->child2,sign);
    return;
  }

  if (polynom->nodeType == SUB) {
    getCoefficientsUnsafe(monomials,polynom->child1,sign);
    getCoefficientsUnsafe(monomials,polynom->child2,-sign);
    return;
  }

  if (polynom->nodeType == NEG) {
    getCoefficientsUnsafe(monomials,polynom->child1,-sign);
    return;
  }  
 

  simplifiedTemp = expandPowerInPolynomialUnsafe(polynom);
  simplified = expandPolynomialUnsafe(simplifiedTemp);

  if (verbosity >= 7) {
    changeToWarningMode();
    printMessage(7,"Warning: recursion on coefficients extraction:\n");
    printTree(polynom);
    printMessage(7,"\ntransformed to\n");
    printTree(simplified); printf("\n");
    restoreMode();
  }

  getCoefficientsUnsafe(monomials, simplified, sign);  

  free_memory(simplifiedTemp);
  free_memory(simplified);

}

int isPowerOfVariable(node *);

void getCoefficientsHornerUnsafe(node **coefficients, node *poly, int offset, int sign) {
  int deg, newSign;
  node *newCoeff, *temp;

  if (isConstant(poly)) {
    newCoeff = copyTree(poly);
  } else {
    if (poly->nodeType == SUB) newSign = -1; else newSign = 1;
    newCoeff = copyTree(poly->child1);
    if ((poly->child2->nodeType == MUL) &&
	isConstant(poly->child2->child1) &&
	isPowerOfVariable(poly->child2->child2)) {
      deg = getDegree(poly->child2->child2);
      getCoefficientsHornerUnsafe(coefficients,poly->child2->child1,offset+deg,sign*newSign);
    } else {
      if ((poly->child2->nodeType == MUL) && 
	  (poly->child2->child1->nodeType == MUL) &&
	  isPowerOfVariable(poly->child2->child1->child1) &&
	  isConstant(poly->child2->child1->child2) &&
	  isConstant(poly->child2->child2)) {
	deg = getDegree(poly->child2->child1->child1);
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp->child1 = copyTree(poly->child2->child1->child2);
	temp->child2 = copyTree(poly->child2->child2);
	getCoefficientsHornerUnsafe(coefficients,temp,offset+deg,sign*newSign);
	free_memory(temp);
      } else {
	if (isPowerOfVariable(poly->child2)) {
	  deg = getDegree(poly->child2);
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = CONSTANT;
	  temp->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(temp->value),17);
	  mpfr_set_d(*(temp->value),1.0,GMP_RNDN);
	  getCoefficientsHornerUnsafe(coefficients,temp,offset+deg,sign*newSign);
	  free_memory(temp);
	} else {
	  deg = getDegree(poly->child2->child1);
	  getCoefficientsHornerUnsafe(coefficients,poly->child2->child2,offset+deg,sign*newSign);
	}
      }
    }
  }
  
  if (coefficients[offset] == NULL) {
    if (sign == -1) {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = NEG;
      temp->child1 = newCoeff;
      coefficients[offset] = temp;
    } else {
      coefficients[offset] = newCoeff;
    }
  } else {
    temp = (node *) safeMalloc(sizeof(node));
    if (sign == 1) temp->nodeType = ADD; else temp->nodeType = SUB;
    temp->child1 = coefficients[offset];
    temp->child2 = newCoeff;
    coefficients[offset] = temp;
  }

}

void getCoefficientsHorner(node **coefficients, node *poly) {
  int offset;

  printMessage(7,"Information: extraction of coefficient terms from a polynomial uses a special algorithm for Horner forms.\n");

  if (poly->nodeType == MUL) {
    offset = getDegree(poly->child1);
    getCoefficientsHornerUnsafe(coefficients,poly->child2,offset,1);
    return;
  }
  getCoefficientsHornerUnsafe(coefficients,poly,0,1);
}

int isPowerOfVariable(node *);
int isCanonicalMonomial(node *);

void getCoefficientsCanonicalUnsafe(node **coefficients, node *poly) {
  int deg, sign;
  node *newCoeff, *temp;

  if (isConstant(poly)) {
    sign = 1;
    deg = 0;
    newCoeff = copyTree(poly);
  } else {
    if (isCanonicalMonomial(poly)) {
      deg = getDegree(poly);
      sign = 1;
      if (isPowerOfVariable(poly)) {
	  newCoeff = (node *) safeMalloc(sizeof(node));
	  newCoeff->nodeType = CONSTANT;
	  newCoeff->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(newCoeff->value),17);
	  mpfr_set_d(*(newCoeff->value),1.0,GMP_RNDN);
      } else {
	newCoeff = copyTree(poly->child1);
      }
    } else {
      getCoefficientsCanonicalUnsafe(coefficients,poly->child1);
      if (poly->nodeType == ADD) sign = 1; else sign = -1;
      if (isConstant(poly->child2)) {
	deg = 0;
	newCoeff = copyTree(poly->child2);
      } else {
	deg = getDegree(poly->child2);
	if (isPowerOfVariable(poly->child2)) {
	  newCoeff = (node *) safeMalloc(sizeof(node));
	  newCoeff->nodeType = CONSTANT;
	  newCoeff->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(newCoeff->value),17);
	  mpfr_set_d(*(newCoeff->value),1.0,GMP_RNDN);
	} else {
	  newCoeff = copyTree(poly->child2->child1);
	}
      }
    }
  }

  if (coefficients[deg] == NULL) {
    if (sign == -1) {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = NEG;
      temp->child1 = newCoeff;
      coefficients[deg] = temp;
    } else {
      coefficients[deg] = newCoeff;
    }
  } else {
    temp = (node *) safeMalloc(sizeof(node));
    if (sign == 1) temp->nodeType = ADD; else temp->nodeType = SUB;
    temp->child1 = coefficients[deg];
    temp->child2 = newCoeff;
    coefficients[deg] = temp;
  }

}

void getCoefficientsCanonical(node **coefficients, node *poly) {

  printMessage(7,"Information: extraction of coefficient terms from a polynomial uses a special algorithm for canonical forms.\n");

  getCoefficientsCanonicalUnsafe(coefficients, poly);
}


int isHorner(node *);
int isCanonical(node *);

node *dividePolynomialByPowerOfVariableUnsafe(node *tree, int alpha);

void getCoefficients(int *degree, node ***coefficients, node *poly) {
  node *temp, *temp2, *temp3, *temp4;
  int i,k,j, mpd;
  node **coefficients1, **coefficients2;
  int degree1, degree2;
  mpfr_t y;

  *degree = getDegree(poly);
  if (*degree < 0) {
    printMessage(1,"Warning: Tried to get coefficients of an expression that is not a polynomial.\n");
    return;
  }

  *coefficients = (node**) safeCalloc((*degree + 1),sizeof(node*));
  for (i=0;i<=*degree;i++) (*coefficients)[i] = NULL;

  
  if (isHorner(poly)) {
    getCoefficientsHorner(*coefficients,poly);
    return;
  }

  if (isCanonical(poly)) {
    getCoefficientsCanonical(*coefficients,poly);
    return;
  }
  

  if ((poly->nodeType == ADD) || (poly->nodeType == SUB)) {
    getCoefficients(&degree1, &coefficients1, poly->child1);
    getCoefficients(&degree2, &coefficients2, poly->child2);
    for (i=0;i<=degree1;i++) {
      (*coefficients)[i] = coefficients1[i];
    }
    free(coefficients1);
    for (i=0;i<=degree2;i++) {
      if (coefficients2[i] != NULL) {
	if ((*coefficients)[i] == NULL) {
	  if (poly->nodeType == SUB) {
	    temp = (node *) safeMalloc(sizeof(node));
	    temp->nodeType = NEG;
	    temp->child1 = coefficients2[i];
	    (*coefficients)[i] = temp;
	  } else {
	    (*coefficients)[i] = coefficients2[i];
	  }
	  
	} else {
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = poly->nodeType;
	  temp->child1 = (*coefficients)[i];
	  temp->child2 = coefficients2[i];
	  (*coefficients)[i] = temp;
	}
      }
    }
    free(coefficients2);
    return;
  }

  if (poly->nodeType == MUL) {
    getCoefficients(&degree1, &coefficients1, poly->child1);
    getCoefficients(&degree2, &coefficients2, poly->child2);
    for (i=0;i<=degree1;i++) {
      for (k=0;k<=degree2;k++) {
	if ((coefficients1[i] != NULL) && (coefficients2[k] != NULL)) {
	  j = i + k;
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = MUL;
	  temp->child1 = copyTree(coefficients1[i]);
	  temp->child2 = copyTree(coefficients2[k]);
	  if ((*coefficients)[j] == NULL) {
	    (*coefficients)[j] = temp;
	  } else {
	    temp2 = (node *) safeMalloc(sizeof(node));
	    temp2->nodeType = ADD;
	    temp2->child1 = (*coefficients)[j];
	    temp2->child2 = temp;
	    (*coefficients)[j] = temp2;
	  }
	}
      }
    }
    for (i=0;i<=degree1;i++) free_memory(coefficients1[i]);
    for (i=0;i<=degree2;i++) free_memory(coefficients2[i]);
    free(coefficients1);
    free(coefficients2);
    return;
  }

  if ((poly->nodeType == POW) &&
      (poly->child2->nodeType == CONSTANT) &&
      (mpfr_integer_p(*(poly->child2->value)))) {
    k = mpfr_get_si(*(poly->child2->value),GMP_RNDN);
    mpfr_init2(y,8 * sizeof(int) + 10);
    mpfr_set_si(y,k,GMP_RNDN);
    if ((mpfr_cmp(y,*(poly->child2->value)) == 0) &&
	(k > 0) && 
	((mpd = getMaxPowerDivider(poly->child1)) > 0)) {
      temp = dividePolynomialByPowerOfVariableUnsafe(poly->child1, mpd);
      temp2 = (node *) safeMalloc(sizeof(node));
      temp2->nodeType = POW;
      temp2->child1 = temp;
      temp2->child2 = copyTree(poly->child2);
      getCoefficients(&degree1, &coefficients1, temp2);
      free_memory(temp2);
      for (i=0;i<=degree1;i++) 
	(*coefficients)[i + k * mpd] = coefficients1[i];
      free(coefficients1);    
      mpfr_clear(y);
      return;
    }
    mpfr_clear(y);
  }


  temp = simplifyTreeErrorfree(poly);
  temp2 = expandPowerInPolynomialUnsafe(temp);
  temp3 = expandPolynomialUnsafe(temp2);
  temp4 = simplifyTreeErrorfree(temp3);

  getCoefficientsUnsafe(*coefficients,temp4,1);

  free_memory(temp);
  free_memory(temp2);
  free_memory(temp3);
  free_memory(temp4);
}



node* hornerPolynomialUnsafe(node *tree) {
  node *copy, *temp, *temp2, *temp3, *temp4, *simplified;
  node **monomials;
  int degree, i, k, e;
  mpfr_t *value;
  
  simplified = simplifyTreeErrorfree(tree);

  if (isHorner(simplified)) {
    degree = getDegree(simplified);
    monomials = (node**) safeCalloc((degree + 1),sizeof(node*));
    for (i=0;i<=degree;i++) monomials[i] = NULL;
    getCoefficientsHorner(monomials,simplified);
  } else {
    if (isCanonical(simplified)) {
      degree = getDegree(simplified);
      monomials = (node**) safeCalloc((degree + 1),sizeof(node*));
      for (i=0;i<=degree;i++) monomials[i] = NULL;
      getCoefficientsCanonical(monomials,simplified);
    } else {
      getCoefficients(&degree,&monomials,simplified);
    }
  }

  if (monomials[degree] == NULL) {
    fprintf(stderr,
"Error: hornerPolynomialUnsafe: an error occurred. The coefficient of a monomial with the polynomial's degree exponent is zero.\n");
    exit(1);
    return NULL;
  }

  copy = copyTree(monomials[degree]);

  for (i=degree-1;i>=0;i--) {
    if (monomials[i] == NULL) {
      if ((i == 0)) {
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp->child1 = temp2;
	temp->child2 = copy;
	copy = temp;
      } else {
	for (k=i-1;((monomials[k]==NULL) && (k > 0));k--);
	e = (i - k) + 1;
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp3 = (node *) safeMalloc(sizeof(node));
	temp3->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,e,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: rounding occurred on representing a monomial power exponent with %d bits.\n",
			 (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	}
	temp3->value = value;
	temp4 = (node *) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp2;
	temp4->child2 = temp3;
	temp->child1 = temp4;
	temp->child2 = copy;
	copy = temp;
	if (monomials[k] != NULL) {
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = ADD;
	  temp->child1 = copyTree(monomials[k]);
	  temp->child2 = copy;
	  copy = temp;
	}
	i = k;
      }
    } else {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = MUL;
      temp2 = (node *) safeMalloc(sizeof(node));
      temp2->nodeType = VARIABLE;
      temp->child1 = temp2;
      temp->child2 = copy;
      copy = temp;
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = ADD;
      temp->child1 = copyTree(monomials[i]);
      temp->child2 = copy;
      copy = temp;
    }
  }
  

  for (i=0;i<=degree;i++) {
    if (monomials[i] != NULL) free_memory(monomials[i]);
  }
  free(monomials);

  free_memory(simplified);
  return copy;
}

node* dividePolynomialByPowerOfVariableUnsafe(node *tree, int alpha) {
  node *copy, *temp, *temp2, *temp3, *temp4, *simplified;
  node **monomials;
  int degree, i, k, e;
  mpfr_t *value;
  
  simplified = simplifyTreeErrorfree(tree);

  getCoefficients(&degree,&monomials,simplified);

  if (alpha > 0) {
    for (i=0;i<alpha;i++) 
      if (monomials[i] != NULL) free_memory(monomials[i]);
    for (i=alpha;i<=degree;i++) {
      monomials[i-alpha] = monomials[i];
    }
    degree = degree - alpha;
  }


  if (monomials[degree] == NULL) {
    fprintf(stderr,
"Error: hornerPolynomialUnsafe: an error occurred. The coefficient of a monomial with the polynomial's degree exponent is zero.\n");
    exit(1);
    return NULL;
  }

  copy = copyTree(monomials[degree]);

  for (i=degree-1;i>=0;i--) {
    if (monomials[i] == NULL) {
      if ((i == 0)) {
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp->child1 = temp2;
	temp->child2 = copy;
	copy = temp;
      } else {
	for (k=i-1;((monomials[k]==NULL) && (k > 0));k--);
	e = (i - k) + 1;
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp3 = (node *) safeMalloc(sizeof(node));
	temp3->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,e,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: rounding occurred on representing a monomial power exponent with %d bits.\n",
			 (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	}
	temp3->value = value;
	temp4 = (node *) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp2;
	temp4->child2 = temp3;
	temp->child1 = temp4;
	temp->child2 = copy;
	copy = temp;
	if (monomials[k] != NULL) {
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = ADD;
	  temp->child1 = copyTree(monomials[k]);
	  temp->child2 = copy;
	  copy = temp;
	}
	i = k;
      }
    } else {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = MUL;
      temp2 = (node *) safeMalloc(sizeof(node));
      temp2->nodeType = VARIABLE;
      temp->child1 = temp2;
      temp->child2 = copy;
      copy = temp;
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = ADD;
      temp->child1 = copyTree(monomials[i]);
      temp->child2 = copy;
      copy = temp;
    }
  }
  

  for (i=0;i<=degree;i++) {
    if (monomials[i] != NULL) free_memory(monomials[i]);
  }
  free(monomials);

  free_memory(simplified);
  return copy;
}



node* hornerPolynomial(node *tree) {
  node *temp;
  
  if (isConstant(tree)) return copyTree(tree);
  if (getDegree(tree) < 0) return copyTree(tree);
  if (isHorner(tree)) {
    printMessage(7,"Information: no Horner simplification will be performed because the given tree is already in Horner form.\n");
    return copyTree(tree);
  }
  
  temp = hornerPolynomialUnsafe(tree);
  
  return temp;
}


node* hornerUnsimplified(node *tree) {
  node *copy;
  mpfr_t *value;

  if (isPolynomial(tree)) return hornerPolynomial(tree);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = horner(tree->child1);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = horner(tree->child1);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = horner(tree->child1);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = horner(tree->child1);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = horner(tree->child1);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = horner(tree->child1);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = horner(tree->child1);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = horner(tree->child1);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = horner(tree->child1);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = horner(tree->child1);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = horner(tree->child1);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = horner(tree->child1);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = horner(tree->child1);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = horner(tree->child1);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = horner(tree->child1);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = horner(tree->child1);
    copy->child2 = horner(tree->child2);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = horner(tree->child1);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = horner(tree->child1);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = horner(tree->child1);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = horner(tree->child1);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = horner(tree->child1);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = horner(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = horner(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = horner(tree->child1);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = horner(tree->child1);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = horner(tree->child1);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: horner: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


int isPowerOfVariable(node *tree) {
  if (tree->nodeType == VARIABLE) return 1;
  if ((tree->nodeType == POW) &&
      (tree->child1->nodeType == VARIABLE) &&
      (tree->child2->nodeType == CONSTANT) && 
      mpfr_integer_p(*(tree->child2->value))) return 1;
  return 0;
}

int isHornerUnsafe(node *tree) {
  if (isConstant(tree)) return 1;
  if (((tree->nodeType == ADD) || (tree->nodeType == SUB)) &&
      isConstant(tree->child1) &&
      (tree->child2->nodeType == MUL) &&
      isPowerOfVariable(tree->child2->child1) &&
      isHornerUnsafe(tree->child2->child2)) return 1;
  if (((tree->nodeType == ADD) || (tree->nodeType == SUB)) &&
      isConstant(tree->child1) &&
      isPowerOfVariable(tree->child2)) return 1;
  if (((tree->nodeType == ADD) || (tree->nodeType == SUB)) &&
      isConstant(tree->child1) &&
      (tree->child2->nodeType == MUL) &&
      (tree->child2->child1->nodeType == MUL) &&
      isPowerOfVariable(tree->child2->child1->child1) &&
      isConstant(tree->child2->child1->child2) &&
      isConstant(tree->child2->child2)) return 1;
  if (((tree->nodeType == ADD) || (tree->nodeType == SUB)) &&
      isConstant(tree->child1) &&
      (tree->child2->nodeType == MUL) &&
      isConstant(tree->child2->child1) &&
      isPowerOfVariable(tree->child2->child2)) return 1;
  return 0;
}

int isHorner(node *tree) {
  if ((tree->nodeType == ADD) || (tree->nodeType == SUB)) 
    return isHornerUnsafe(tree);
  if (tree->nodeType == MUL) {
    return isPowerOfVariable(tree->child1) && isHornerUnsafe(tree->child2);
  }
  return 0;
}


node* horner(node *tree) {
  node *temp, *temp2, *temp3;
  int i;

  if (isHorner(tree)) {
    printMessage(7,"Information: no Horner simplification will be performed because the given tree is already in Horner form.\n");
    return copyTree(tree);
  }

  temp3 = simplifyTreeErrorfree(tree);

  i = 0;
  do {
    temp = hornerUnsimplified(temp3);
    temp2 = simplifyTreeErrorfree(temp);
    free_memory(temp);
    free_memory(temp3);
    temp3 = temp2;
    i++;
  } while ((!isHorner(temp3)) && (i < 2));

  return temp3;
}


node *differentiatePolynomialHornerUnsafe(node *tree) {
  int degree, i, k, e;
  node **monomials;
  node *temp, *temp2, *temp3, *temp4, *copy;
  mpfr_t *value;
  mp_prec_t prec;

  getCoefficients(&degree,&monomials,tree);

  if (monomials[0] != NULL) free_memory(monomials[0]);

  for (i=1;i<=degree;i++) {
    if (monomials[i] != NULL) {
      if (monomials[i]->nodeType == CONSTANT) {
	value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,mpfr_get_prec(*(monomials[i]->value))+(sizeof(int)*8));
	if (mpfr_mul_si(*value,*(monomials[i]->value),i,GMP_RNDN) != 0)
	  printMessage(1,"Warning: rounding occurred while differentiating a polynomial in Horner form.\n");
	mpfr_clear(*(monomials[i]->value));
	free(monomials[i]->value);
	monomials[i]->value = value;
	temp = monomials[i];
      } else {
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp->child1 = (node *) safeMalloc(sizeof(node));
	temp->child1->nodeType = CONSTANT;
	temp->child1->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	prec = 8 * sizeof(int) + 10; if (tools_precision > prec) prec = tools_precision;
	mpfr_init2(*(temp->child1->value),prec);
	if (mpfr_set_si(*(temp->child1->value),i,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: on differentiating a polynomial in Horner form rounding occurred while representing the degree of a monomial on a constant of the given precision\n");
	  }
	}
	temp->child2 = monomials[i];
      }
      monomials[i-1] = temp;
    } else {
      monomials[i-1] = NULL;
    }
  }
  
  degree--;

  copy = copyTree(monomials[degree]);

  for (i=degree-1;i>=0;i--) {
    if (monomials[i] == NULL) {
      if ((i == 0)) {
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp->child1 = temp2;
	temp->child2 = copy;
	copy = temp;
      } else {
	for (k=i-1;((monomials[k]==NULL) && (k > 0));k--);
	e = (i - k) + 1;
	temp = (node *) safeMalloc(sizeof(node));
	temp->nodeType = MUL;
	temp2 = (node *) safeMalloc(sizeof(node));
	temp2->nodeType = VARIABLE;
	temp3 = (node *) safeMalloc(sizeof(node));
	temp3->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,e,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: rounding occurred on representing a monomial power exponent with %d bits.\n",
			 (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	}
	temp3->value = value;
	temp4 = (node *) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp2;
	temp4->child2 = temp3;
	temp->child1 = temp4;
	temp->child2 = copy;
	copy = temp;
	if (monomials[k] != NULL) {
	  temp = (node *) safeMalloc(sizeof(node));
	  temp->nodeType = ADD;
	  temp->child1 = copyTree(monomials[k]);
	  temp->child2 = copy;
	  copy = temp;
	}
	i = k;
      }
    } else {
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = MUL;
      temp2 = (node *) safeMalloc(sizeof(node));
      temp2->nodeType = VARIABLE;
      temp->child1 = temp2;
      temp->child2 = copy;
      copy = temp;
      temp = (node *) safeMalloc(sizeof(node));
      temp->nodeType = ADD;
      temp->child1 = copyTree(monomials[i]);
      temp->child2 = copy;
      copy = temp;
    }
  }
  

  for (i=0;i<=degree;i++) {
    if (monomials[i] != NULL) free_memory(monomials[i]);
  }
  free(monomials);

  return copy;
}

node *differentiatePolynomialUnsafe(node *tree) {
  node *copy, *temp, *temp2, *temp3, *temp4, *temp5;
  int degree, i;
  node **monomials;
  mpfr_t *value;

  if (isHorner(tree)) {
    printMessage(25,"Information: differentiating a polynomial in Horner form uses a special algorithm.\n");
    return differentiatePolynomialHornerUnsafe(tree);
  } 

  degree = getDegree(tree);

  if (degree == 0) {
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    mpfr_set_d(*value,0.0,GMP_RNDN);
    copy->value = value;
  } else {
       
    getCoefficients(&degree,&monomials,tree);
 
  
    if (monomials[degree] == NULL) {
      fprintf(stderr,
	     "Error: differentiatePolynomialUnsafe: an error occurred. The coefficient of a monomial with the polynomial's degree exponent is zero.\n"
	     );
      exit(1);
      return NULL;
    }
    
    
    if (degree >= 2) {
      if (degree > 2) {
	temp = copyTree(monomials[degree]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree,GMP_RNDN) != 0) {
	  if (!noRoundingWarnings) {
	    printMessage(1,"Warning: rounding occurred on differentiating a polynomial. A constant could not be written on %d bits.\n",
			 (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	}
	temp2->value = value;
	temp3 = (node*) safeMalloc(sizeof(node));
	temp3->nodeType = MUL;
	temp3->child1 = temp2;
	temp3->child2 = temp;
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree-1,GMP_RNDN) != 0) {
	  printMessage(1,
		 "Warning: rounding occurred on differentiating a polynomial. An exponent constant could not be written on %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp2->value = value;
	temp = (node*) safeMalloc(sizeof(node));
	temp->nodeType = VARIABLE;
	temp4 = (node*) safeMalloc(sizeof(node));
	temp4->nodeType = POW;
	temp4->child1 = temp;
	temp4->child2 = temp2;
	temp5 = (node*) safeMalloc(sizeof(node));
	temp5->nodeType = MUL;
	temp5->child1 = temp3;
	temp5->child2 = temp4;
	copy = temp5;
      } else {
	temp = copyTree(monomials[degree]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = CONSTANT;
	value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*value,tools_precision);
	if (mpfr_set_si(*value,degree,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: rounding occurred on differentiating a polynomial. A constant could not be written on %d bits.\n",
		 (int) tools_precision);
	  printMessage(1,"Try to increase the precision.\n");
	}
	temp2->value = value;
	temp3 = (node*) safeMalloc(sizeof(node));
	temp3->nodeType = MUL;
	temp3->child1 = temp2;
	temp3->child2 = temp;
	temp = (node*) safeMalloc(sizeof(node));
	temp->nodeType = VARIABLE;
	temp4 = (node*) safeMalloc(sizeof(node));
	temp4->nodeType = MUL;
	temp4->child1 = temp3;
	temp4->child2 = temp;
	copy = temp4;
      }
          
      for (i=degree-1;i>1;i--) {
	if (monomials[i] != NULL) {
	  temp = copyTree(monomials[i]);
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  if (mpfr_set_si(*value,i,GMP_RNDN) != 0) {
	    printMessage(1,"Warning: rounding occurred on differentiating a polynomial. A constant could not be written on %d bits.\n",
		   (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	  temp2->value = value;
	  temp3 = (node*) safeMalloc(sizeof(node));
	  temp3->nodeType = MUL;
	  temp3->child1 = temp2;
	  temp3->child2 = temp;
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = CONSTANT;
	  value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*value,tools_precision);
	  if (mpfr_set_si(*value,i-1,GMP_RNDN) != 0) {
	    printMessage(1,
		   "Warning: rounding occurred on differentiating a polynomial. An exponent constant could not be written on %d bits.\n",
		   (int) tools_precision);
	    printMessage(1,"Try to increase the precision.\n");
	  }
	  temp2->value = value;
	  temp = (node*) safeMalloc(sizeof(node));
	  temp->nodeType = VARIABLE;
	  temp4 = (node*) safeMalloc(sizeof(node));
	  temp4->nodeType = POW;
	  temp4->child1 = temp;
	  temp4->child2 = temp2;
	  temp5 = (node*) safeMalloc(sizeof(node));
	  temp5->nodeType = MUL;
	  temp5->child1 = temp3;
	  temp5->child2 = temp4;
	  temp = copy;
	  temp2 = (node*) safeMalloc(sizeof(node));
	  temp2->nodeType = ADD;
	  temp2->child1 = temp5;
	  temp2->child2 = temp;
	  copy = temp2;      
	} 
      }
      
      if (monomials[1] != NULL) {
	temp = copyTree(monomials[1]);
	temp2 = (node*) safeMalloc(sizeof(node));
	temp2->nodeType = ADD;
	temp2->child1 = temp;
	temp2->child2 = copy;
	copy = temp2;      
      } 
    } else {
      copy = copyTree(monomials[1]);
    }
  
    for (i=0;i<=degree;i++) {
      if (monomials[i] != NULL) free_memory(monomials[i]);
    }
    free(monomials);
  } 

  return copy;
}


int getNumeratorDenominator(node **numerator, node **denominator, node *tree) {
  if (tree->nodeType == DIV) {
    *numerator = copyTree(tree->child1);
    *denominator = copyTree(tree->child2);
    return 1;
  }
  else {
    *numerator = copyTree(tree);
    *denominator = NULL;
    return 0;
  }
}


node *substitute(node* tree, node *t) {
  node *copy;
  mpfr_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = copyTree(t);
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,mpfr_get_prec(*(tree->value)));
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = substitute(tree->child1,t);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = substitute(tree->child1,t);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = substitute(tree->child1,t);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = substitute(tree->child1,t);
    copy->child2 = substitute(tree->child2,t);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ERF:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = substitute(tree->child1,t);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = substitute(tree->child1,t);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = substitute(tree->child1,t);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = substitute(tree->child1,t);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = substitute(tree->child1,t);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = substitute(tree->child1,t);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = substitute(tree->child1,t);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: substitute: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}

int readHexadecimal(mpfr_t rop, char *c) {
  mpfr_t vrd, vru;
  mp_prec_t p;
  int res, resA, resB;
  char *c2;
  
  c2 = (char *) safeCalloc(strlen(c) + 2, sizeof(char));
  strcpy(c2, c);

  if (c2[strlen(c2) - 1] == 'p') c2[strlen(c2)] = '0';


  p = mpfr_get_prec(rop);

  mpfr_init2(vrd, p);
  mpfr_init2(vru, p);
  
  resA = mpfr_set_str(vrd, c2, 16, GMP_RNDD);
  resB = mpfr_set_str(vru, c2, 16, GMP_RNDU);

  if (!resA && !resB) {
    if (mpfr_cmp(vrd,vru) == 0) {
      mpfr_set(rop,vrd,GMP_RNDN);
      res = 1;
    } else {
      resA = mpfr_set_str(vrd, c2, 16, GMP_RNDN);
      if (!resA) {
	mpfr_set(rop, vrd, GMP_RNDN);
	res = 0;
      } else {
	mpfr_set_nan(rop);
	res = 0;
      }
    }
  } else {
    mpfr_set_nan(rop);
    res = 0;
  }

  mpfr_clear(vrd);
  mpfr_clear(vru);
  free(c2);

  return res;
}


int readDyadic(mpfr_t res, char *c) {
  char *mantissa, *exponent, *curr, *curr2;  
  mpfr_t mant, expo, temp1, temp2;
  mp_prec_t prec;
  int rounding;

  mantissa = (char *) safeCalloc(strlen(c)+1,sizeof(char));
  exponent = (char *) safeCalloc(strlen(c)+1,sizeof(char));
  curr = c; curr2 = mantissa;
  while ((*curr != '\0') && (*curr != 'b') && (*curr != 'B')) {
    *curr2 = *curr;
    curr2++;
    curr++;
  }
  if (*curr != '\0') curr++;
  curr2 = exponent;
  while (*curr != '\0') {
    *curr2 = *curr;
    curr2++;
    curr++;
  }

  rounding = 1;

  prec = mpfr_get_prec(res);
  mpfr_init2(mant,prec);
  mpfr_init2(expo,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec); 

  mpfr_set_str(temp1,mantissa,10,GMP_RNDU);
  mpfr_set_str(temp2,mantissa,10,GMP_RNDD);
  if (mpfr_cmp(temp1,temp2) != 0) {
    rounding = 0;
    mpfr_set_str(temp1,mantissa,10,GMP_RNDN);
  }
  if (mpfr_set(mant,temp1,GMP_RNDN) != 0) {
    rounding = 0;
  }
  mpfr_set_str(temp1,exponent,10,GMP_RNDU);
  mpfr_set_str(temp2,exponent,10,GMP_RNDD);
  if (mpfr_cmp(temp1,temp2) != 0) {
    rounding = 0;
    mpfr_set_str(temp1,exponent,10,GMP_RNDN);
  }
  if (mpfr_exp2(expo,temp1,GMP_RNDN) != 0) {
    rounding = 0;
  }
  if (mpfr_mul(res,mant,expo,GMP_RNDN) != 0) {
    rounding = 0;
  }
 
  if (!mpfr_number_p(res)) rounding = 1;

  mpfr_clear(mant);
  mpfr_clear(expo);
  mpfr_clear(temp1);
  mpfr_clear(temp2);
  free(mantissa);
  free(exponent);
  return rounding;
}

node *makePolynomial(mpfr_t *coefficients, int degree) {
  node *tempTree, *tempTree2, *tempTree3;
  int i;
  
  tempTree = (node *) safeMalloc(sizeof(node));
  tempTree->nodeType = CONSTANT;
  tempTree->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempTree->value),mpfr_get_prec(coefficients[degree]));
  mpfr_set(*(tempTree->value),coefficients[degree],GMP_RNDN);
  for (i=degree-1;i>=0;i--) {
    tempTree2 = (node *) safeMalloc(sizeof(node));
    tempTree2->nodeType = MUL;
    tempTree3 = (node *) safeMalloc(sizeof(node));
    tempTree3->nodeType = VARIABLE;
    tempTree2->child1 = tempTree3;
    tempTree2->child2 = tempTree;
    tempTree = (node *) safeMalloc(sizeof(node));
    tempTree->nodeType = ADD;
    tempTree->child2 = tempTree2;
    tempTree3 = (node *) safeMalloc(sizeof(node));
    tempTree3->nodeType = CONSTANT;
    tempTree3->value = (mpfr_t *) safeMalloc(sizeof(node));
    mpfr_init2(*(tempTree3->value),mpfr_get_prec(coefficients[i]));
    mpfr_set(*(tempTree3->value),coefficients[i],GMP_RNDN);
    tempTree->child1 = tempTree3;
  }
  tempTree2 = horner(tempTree);
  free_memory(tempTree);
  return tempTree2;
}


int treeSize(node *tree) {
  if (tree == NULL) return 0;
  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
  case PI_CONST:
    return 1;
    break;
  case ADD:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case SUB:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case MUL:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case DIV:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case SQRT:
    return treeSize(tree->child1) + 1;
    break;
  case EXP:
    return treeSize(tree->child1) + 1;
    break;
  case LOG:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_2:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_10:
    return treeSize(tree->child1) + 1;
    break;
  case SIN:
    return treeSize(tree->child1) + 1;
    break;
  case COS:
    return treeSize(tree->child1) + 1;
    break;
  case TAN:
    return treeSize(tree->child1) + 1;
    break;
  case ASIN:
    return treeSize(tree->child1) + 1;
    break;
  case ACOS:
    return treeSize(tree->child1) + 1;
    break;
  case ATAN:
    return treeSize(tree->child1) + 1;
    break;
  case SINH:
    return treeSize(tree->child1) + 1;
    break;
  case COSH:
    return treeSize(tree->child1) + 1;
    break;
  case TANH:
    return treeSize(tree->child1) + 1;
    break;
  case ASINH:
    return treeSize(tree->child1) + 1;
    break;
  case ACOSH:
    return treeSize(tree->child1) + 1;
    break;
  case ATANH:
    return treeSize(tree->child1) + 1;
    break;
  case POW:
    return treeSize(tree->child1) + treeSize(tree->child2) + 1;
    break;
  case NEG:
    return treeSize(tree->child1) + 1;
    break;
  case ABS:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLEDOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case TRIPLEDOUBLE:
    return treeSize(tree->child1) + 1;
    break;
  case ERF:
    return treeSize(tree->child1) + 1;
    break;
  case ERFC:
    return treeSize(tree->child1) + 1;
    break;
  case LOG_1P:
    return treeSize(tree->child1) + 1;
    break;
  case EXP_M1:
    return treeSize(tree->child1) + 1;
    break;
  case DOUBLEEXTENDED:
    return treeSize(tree->child1) + 1;
    break;
  case LIBRARYFUNCTION:    
    return treeSize(tree->child1) + 1;
    break;
  case CEIL:
    return treeSize(tree->child1) + 1;
    break;
  case FLOOR:
    return treeSize(tree->child1) + 1;
    break;
  default:
   fprintf(stderr,"Error: treeSize: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return -1;
}



int highestDegreeOfPolynomialSubexpression(node *tree) {
  int l, r;

  if (isPolynomial(tree)) return getDegree(tree);

  switch (arity(tree)) {
  case 2:
    l = highestDegreeOfPolynomialSubexpression(tree->child1);
    r = highestDegreeOfPolynomialSubexpression(tree->child2);
    return l > r ? l : r;
    break;
  case 1:
    return highestDegreeOfPolynomialSubexpression(tree->child1);
    break;
  case 0:
    return getDegree(tree);
    break;
  default: 
    fprintf(stderr,"Error: unknown arity of an operator.\n");
    exit(1);
  }

  return -1;
}



node *getIthCoefficient(node *poly, int i) {
  node *tempNode;
  node **coefficients;
  int degree, k;

  if ((!isPolynomial(poly)) || (i < 0)) {
    tempNode = (node *) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(tempNode->value),10);
    mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
    return tempNode;
  } 

  getCoefficients(&degree, &coefficients, poly);

  if ((i > degree) || (coefficients[i] == NULL)) {
    tempNode = (node *) safeMalloc(sizeof(node));
    tempNode->nodeType = CONSTANT;
    tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(tempNode->value),10);
    mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
  } else {
    tempNode = copyTree(coefficients[i]);
  }
  
  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) free_memory(coefficients[k]);
  }

  free(coefficients);

  return tempNode;
}


node *getSubpolynomial(node *poly, chain *monomials, int fillDegrees, mp_prec_t prec) {
  node *tempNode, *tempNode2, *tempNode3;
  node **coefficients;
  int degree, k, currDeg, maxDegree;
  chain *curr;

  tempNode = (node *) safeMalloc(sizeof(node));
  tempNode->nodeType = CONSTANT;
  tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempNode->value),prec);
  mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);

  if (!isPolynomial(poly)) {
    return tempNode;
  } 

  getCoefficients(&degree, &coefficients, poly);

  curr = monomials;

  maxDegree = -1;

  while (curr != NULL) {
    currDeg = *((int *) (curr->value));
    if (currDeg > maxDegree) maxDegree = currDeg;
    if ((currDeg >= 0) && (currDeg <= degree) && (coefficients[currDeg] != NULL)) {
      tempNode2 = (node *) safeMalloc(sizeof(node));
      tempNode2->nodeType = POW;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = CONSTANT;
      tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(tempNode3->value),prec);
      if (mpfr_set_si(*(tempNode3->value),currDeg,GMP_RNDN) != 0) {
	printMessage(1,"Warning: during subpolynomial extraction, the exponent of a power could not be represented exactly on with the given precision.\n");
      }
      tempNode2->child2 = tempNode3;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = VARIABLE;
      tempNode2->child1 = tempNode3;
      tempNode3 = (node *) safeMalloc(sizeof(node));
      tempNode3->nodeType = MUL;
      tempNode3->child2 = tempNode2;
      tempNode3->child1 = copyTree(coefficients[currDeg]);
      tempNode2 = (node *) safeMalloc(sizeof(node));
      tempNode2->nodeType = ADD;
      tempNode2->child2 = tempNode3;
      tempNode2->child1 = tempNode;
      tempNode = tempNode2;
    }
    curr = curr->next;
  }

  if (fillDegrees) {
    for (k=maxDegree+1;k<=degree;k++) {
      if (coefficients[k] != NULL) {
	tempNode2 = (node *) safeMalloc(sizeof(node));
	tempNode2->nodeType = POW;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = CONSTANT;
	tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(tempNode3->value),prec);
	if (mpfr_set_si(*(tempNode3->value),k,GMP_RNDN) != 0) {
	  printMessage(1,"Warning: during subpolynomial extraction, the exponent of a power could not be represented exactly on with the given precision.\n");
	}
	tempNode2->child2 = tempNode3;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = VARIABLE;
	tempNode2->child1 = tempNode3;
	tempNode3 = (node *) safeMalloc(sizeof(node));
	tempNode3->nodeType = MUL;
	tempNode3->child2 = tempNode2;
	tempNode3->child1 = copyTree(coefficients[k]);
	tempNode2 = (node *) safeMalloc(sizeof(node));
	tempNode2->nodeType = ADD;
	tempNode2->child2 = tempNode3;
	tempNode2->child1 = tempNode;
	tempNode = tempNode2;
      }
    }
  }


  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) free_memory(coefficients[k]);
  }

  free(coefficients);

  tempNode2 = horner(tempNode);

  free_memory(tempNode);
  
  return tempNode2;
}

node *makeCanonicalPolyUnsafe(node *poly, mp_prec_t prec) {
  node **coefficients;
  int degree, k;
  node *tempNode, *tempNode2, *tempNode3;

  getCoefficients(&degree, &coefficients, poly);

  tempNode = (node *) safeMalloc(sizeof(node));
  tempNode->nodeType = CONSTANT;
  tempNode->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(tempNode->value),prec);
  mpfr_set_d(*(tempNode->value),0.0,GMP_RNDN);
  for (k=0;k<=degree;k++) {
    if (coefficients[k] != NULL) {
      if (k == 0) {
	tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = ADD;
	  tempNode2->child2 = coefficients[k];
	  tempNode2->child1 = tempNode;
	  tempNode = tempNode2;
      } else {
	if (k == 1) {
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = VARIABLE;
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = MUL;
	  tempNode2->child2 = tempNode3;
	  tempNode2->child1 = coefficients[k];
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = ADD;
	  tempNode3->child2 = tempNode2;
	  tempNode3->child1 = tempNode;
	  tempNode = tempNode3;
	} else {
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = POW;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = CONSTANT;
	  tempNode3->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(tempNode3->value),prec);
	  if (mpfr_set_si(*(tempNode3->value),k,GMP_RNDN) != 0) {
	    printMessage(1,"Warning: during transformation to canonical form, the exponent of a power could not be represented exactly on with the given precision.\n");
	  }
	  tempNode2->child2 = tempNode3;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = VARIABLE;
	  tempNode2->child1 = tempNode3;
	  tempNode3 = (node *) safeMalloc(sizeof(node));
	  tempNode3->nodeType = MUL;
	  tempNode3->child2 = tempNode2;
	  tempNode3->child1 = coefficients[k];
	  tempNode2 = (node *) safeMalloc(sizeof(node));
	  tempNode2->nodeType = ADD;
	  tempNode2->child2 = tempNode3;
	  tempNode2->child1 = tempNode;
	  tempNode = tempNode2;
	}
      }
    }
  }

  free(coefficients);

  tempNode2 = simplifyTreeErrorfree(tempNode);

  free_memory(tempNode);

  return tempNode2;
}


int isCanonicalMonomial(node *tree) {

  if (isConstant(tree)) return 1;

  if (isPowerOfVariable(tree)) return 1;
  
  if ((tree->nodeType == MUL) && 
      isConstant(tree->child1) &&
      isPowerOfVariable(tree->child2)) return 1;

  return 0;
}


int isCanonicalUnsafe(node *tree) {
  int deg1, deg2;
  
  if (isConstant(tree) || isCanonicalMonomial(tree)) return 1;

  if ((tree->nodeType == ADD) || (tree->nodeType == SUB)) {
    if (!isCanonicalUnsafe(tree->child1)) return 0;
    if (!isCanonicalMonomial(tree->child2)) return 0;
    deg1 = getDegree(tree->child1);
    deg2 = getDegree(tree->child2);
    if (deg1 >= deg2) return 0;
    return 1;
  }

  return 0;
}


int isCanonical(node *tree) {
  return isCanonicalUnsafe(tree);
}



node *makeCanonical(node *tree, mp_prec_t prec) {
  node *copy;
  mpfr_t *value;

  if (isCanonical(tree)) {
    printMessage(7,"Information: no canonical form simplification will be performed because the given tree is already canonical.\n");
    return copyTree(tree);
  }

  if (isPolynomial(tree)) return makeCanonicalPolyUnsafe(tree,prec);

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CONSTANT;
    value = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*value,tools_precision);
    simplifyMpfrPrec(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ADD;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case SUB:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SUB;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case MUL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = MUL;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case DIV:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DIV;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case SQRT:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SQRT;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case EXP:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_2:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_2;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_10:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_10;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case SIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SIN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case COS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TAN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ASIN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASIN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ACOS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ATAN:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATAN;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case SINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = SINH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case COSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = COSH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TANH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ASINH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ASINH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ACOSH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ACOSH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ATANH:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ATANH;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case POW:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = POW;
    copy->child1 = makeCanonical(tree->child1,prec);
    copy->child2 = makeCanonical(tree->child2,prec);
    break;
  case NEG:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = NEG;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ABS:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ABS;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEDOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case TRIPLEDOUBLE:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = TRIPLEDOUBLE;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ERF: 
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERF;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case ERFC:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = ERFC;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LOG_1P:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LOG_1P;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case EXP_M1:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = EXP_M1;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case DOUBLEEXTENDED:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = DOUBLEEXTENDED;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case LIBRARYFUNCTION:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = LIBRARYFUNCTION;
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case CEIL:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = CEIL;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case FLOOR:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = FLOOR;
    copy->child1 = makeCanonical(tree->child1,prec);
    break;
  case PI_CONST:
    copy = (node*) safeMalloc(sizeof(node));
    copy->nodeType = PI_CONST;
    break;
  default:
   fprintf(stderr,"Error: makeCanonical: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


node *makeVariable() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = VARIABLE;

  return res;
}

node *makeConstant(mpfr_t x) {
  node *res;
  
  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CONSTANT;
  res->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(res->value),mpfr_get_prec(x));
  mpfr_set(*(res->value),x,GMP_RNDN);

  return res;
}

node *makeBinary(node *op1, node *op2, int opType) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = opType;
  res->child1 = op1;
  res->child2 = op2;

  return res;
}

node *makeUnary(node *op1, int opType) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = opType;
  res->child1 = op1;

  return res;
}


node *makeAdd(node *op1, node *op2) {
  return makeBinary(op1,op2,ADD);
}

node *makeSub(node *op1, node *op2) {
  return makeBinary(op1,op2,SUB);
}

node *makeMul(node *op1, node *op2) {
  return makeBinary(op1,op2,MUL);
}

node *makeDiv(node *op1, node *op2) {
  return makeBinary(op1,op2,DIV);
}

node *makeSqrt(node *op1) {
  return makeUnary(op1,SQRT);
}

node *makeExp(node *op1) {
  return makeUnary(op1,EXP);
}

node *makeLog(node *op1) {
  return makeUnary(op1,LOG);
}

node *makeLog2(node *op1) {
  return makeUnary(op1,LOG_2);
}

node *makeLog10(node *op1) {
  return makeUnary(op1,LOG_10);
}

node *makeSin(node *op1) {
  return makeUnary(op1,SIN);
}

node *makeCos(node *op1) {
  return makeUnary(op1,COS);
}

node *makeTan(node *op1) {
  return makeUnary(op1,TAN);
}

node *makeAsin(node *op1) {
  return makeUnary(op1,ASIN);
}

node *makeAcos(node *op1) {
  return makeUnary(op1,ACOS);
}

node *makeAtan(node *op1) {
  return makeUnary(op1,ATAN);
}

node *makePow(node *op1, node *op2) {
  return makeBinary(op1,op2,POW);
}

node *makeNeg(node *op1) {
  return makeUnary(op1,NEG);
}

node *makeAbs(node *op1) {
  return makeUnary(op1,ABS);
}

node *makeDouble(node *op1) {
  return makeUnary(op1,DOUBLE);
}

node *makeDoubledouble(node *op1) {
  return makeUnary(op1,DOUBLEDOUBLE);
}

node *makeTripledouble(node *op1) {
  return makeUnary(op1,TRIPLEDOUBLE);
}

node *makeErf(node *op1 ) {
  return makeUnary(op1,ERF);
}

node *makeErfc(node *op1) {
  return makeUnary(op1,ERFC);
}

node *makeLog1p(node *op1) {
  return makeUnary(op1,LOG_1P);
}

node *makeExpm1(node *op1) {
  return makeUnary(op1,EXP_M1);
}

node *makeDoubleextended(node *op1) {
  return makeUnary(op1,DOUBLEEXTENDED);
}

node *makeCeil(node *op1) {
  return makeUnary(op1,CEIL);
}

node *makeFloor(node *op1) {
  return makeUnary(op1,FLOOR);
}

node *makePi() {
  node *res;
  
  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PI_CONST;

  return res;
}

node *makeSinh(node *op1) {
  return makeUnary(op1,SINH);
}

node *makeCosh(node *op1) {
  return makeUnary(op1,COSH);
}

node *makeTanh(node *op1) {
  return makeUnary(op1,TANH);
}

node *makeAsinh(node *op1) {
  return makeUnary(op1,ASINH);
}

node *makeAcosh(node *op1) {
  return makeUnary(op1,ACOSH);
}

node *makeAtanh(node *op1) {
  return makeUnary(op1,ATANH);
}


node *parseString(char *str) {
  node *result;

  startBuffer(str);
  if (!miniyyparse()) {
    result = minitree;
  } else {
    result = NULL;
  }
  endBuffer();

  return result;
}


int readDecimalConstant(mpfr_t result, char *str) {
  mpfr_t a,b;
  int ternary;

  mpfr_init2(a,tools_precision);
  mpfr_init2(b,tools_precision);

  mpfr_set_str(a,str,10,GMP_RNDD);
  mpfr_set_str(b,str,10,GMP_RNDU);    
  if (mpfr_cmp(a,b) != 0) {
    if (!noRoundingWarnings) {
      printMessage(1,
		   "Warning: Rounding occurred when converting the constant \"%s\" to floating-point with %d bits.\n",
		   str,(int) tools_precision);
      printMessage(1,"If safe computation is needed, try to increase the precision.\n");
    }
    ternary = mpfr_set_str(a,str,10,GMP_RNDN);
  } else {
    ternary = 0;
  }

  mpfr_set_prec(result, tools_precision);
  mpfr_set(result,a,GMP_RNDN);

  mpfr_clear(a);
  mpfr_clear(b);

  return ternary;
}
