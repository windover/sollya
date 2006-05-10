#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"
#include "infnorm.h"
#include "chain.h"
#include "double.h"
#include "main.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define DEBUG 1
#define DEBUG2 0



void printInterval(mpfi_t interval);


void mpfi_pow(mpfi_t z, mpfi_t x, mpfi_t y) {
  mpfr_t l,r,lx,rx;
  mp_prec_t prec, precx;
  int must_divide;
  mpfi_t res;

  prec = mpfi_get_prec(y);

  mpfi_init2(res,mpfi_get_prec(z) + 10);

  mpfr_init2(l,prec);
  mpfr_init2(r,prec);

  mpfi_get_right(r,y);
  mpfi_get_left(l,y);

  if ((mpfr_cmp(l,r) == 0) && (mpfr_integer_p(l))) {
    if (mpfr_zero_p(l)) {
      mpfi_set_d(res,1.0);
    } else {
      precx = mpfi_get_prec(x);

      mpfr_init2(lx,precx);
      mpfr_init2(rx,precx);
      
      mpfi_get_right(rx,x);
      mpfi_get_left(lx,x);
     
      if (mpfr_sgn(l) < 0) {
	must_divide = 1;
	mpfr_neg(l,l,GMP_RNDN);
      } else {
	must_divide = 0;
      }
      if (mpfi_has_zero(x)) {
		mpfr_div_2ui(r,l,1,GMP_RNDN);
	if (mpfr_integer_p(r)) {   /* l is even */
	  mpfr_pow(lx,lx,l,GMP_RNDU);
	  mpfr_pow(rx,rx,l,GMP_RNDU);
	  mpfr_max(rx,lx,rx,GMP_RNDU);
	  mpfr_set_d(lx,0.0,GMP_RNDD);
	  mpfi_interv_fr(res,lx,rx);
	  mpfi_revert_if_needed(res);
	} else { /* l is odd */
	  mpfr_pow(lx,lx,l,GMP_RNDD);
	  mpfr_pow(rx,rx,l,GMP_RNDU);
	  mpfi_interv_fr(res,lx,rx);
	  mpfi_revert_if_needed(res);
	}
      } else {
	mpfr_div_2ui(r,l,1,GMP_RNDN);
	if (mpfr_integer_p(r)) {   /* l is even */
	  if (mpfr_sgn(lx) > 0) {
	    mpfr_pow(lx,lx,l,GMP_RNDD);
	    mpfr_pow(rx,rx,l,GMP_RNDU);
	    mpfi_interv_fr(res,lx,rx);
	    mpfi_revert_if_needed(res);
	  } else {
	    mpfr_pow(lx,lx,l,GMP_RNDU);
	    mpfr_pow(rx,rx,l,GMP_RNDD);
	    mpfi_interv_fr(res,lx,rx);
	    mpfi_revert_if_needed(res);
	  }
	} else { /* l is odd */
	  mpfr_pow(lx,lx,l,GMP_RNDD);
	  mpfr_pow(rx,rx,l,GMP_RNDU);
	  mpfi_interv_fr(res,lx,rx);
	  mpfi_revert_if_needed(res);
	}
      }
      if (must_divide) {
	mpfi_inv(res,res);
      }

      mpfr_clear(lx);
      mpfr_clear(rx);
    }
  } else {
    mpfi_log(res,x);
    mpfi_mul(res,res,y);
    mpfi_exp(res,res);
  }
  mpfr_clear(l);
  mpfr_clear(r);
  mpfi_set(z,res);
  mpfi_clear(res);
}


void mpfi_round_to_double(mpfi_t rop, mpfi_t op) {
  mpfr_t l,r, lres, rres;
  mp_prec_t prec;

  prec = mpfi_get_prec(op) + 10;
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfr_init2(lres,prec);
  mpfr_init2(rres,prec);

  mpfi_get_left(l,op);
  mpfi_get_right(r,op);

  mpfr_round_to_double(lres,l);
  mpfr_round_to_double(rres,r);

  mpfi_interv_fr(rop,lres,rres);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(lres);
  mpfr_clear(rres);
}

void mpfi_round_to_doubledouble(mpfi_t rop, mpfi_t op) {
  mpfr_t l,r, lres, rres;
  mp_prec_t prec;

  prec = mpfi_get_prec(op) + 10;
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfr_init2(lres,prec);
  mpfr_init2(rres,prec);

  mpfi_get_left(l,op);
  mpfi_get_right(r,op);

  mpfr_round_to_doubledouble(lres,l);
  mpfr_round_to_doubledouble(rres,r);

  mpfi_interv_fr(rop,lres,rres);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(lres);
  mpfr_clear(rres);
}

void mpfi_round_to_tripledouble(mpfi_t rop, mpfi_t op) {
  mpfr_t l,r, lres, rres;
  mp_prec_t prec;

  prec = mpfi_get_prec(op) + 10;
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfr_init2(lres,prec);
  mpfr_init2(rres,prec);

  mpfi_get_left(l,op);
  mpfi_get_right(r,op);

  mpfr_round_to_tripledouble(lres,l);
  mpfr_round_to_tripledouble(rres,r);

  mpfi_interv_fr(rop,lres,rres);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(lres);
  mpfr_clear(rres);
}


void newtonMPFR(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t x, temp1, temp2;
  mpfr_t d;
  unsigned long int n=1;
  int test=0;

  mpfr_init2(x,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec);
  mpfr_init2(d,prec);

  mpfr_sub(d,b,a,GMP_RNDN);
  test = 11 + (mpfr_get_exp(b)-prec)/mpfr_get_exp(d);

  mpfr_add(x,a,b,GMP_RNDN);
  mpfr_div_2ui(x,x,1,GMP_RNDN);
  
  while(n<=test) {
    evaluate(temp1, tree, x, prec);
    evaluate(temp2, diff_tree, x, prec);
    mpfr_div(temp1, temp1, temp2, GMP_RNDN);
    mpfr_sub(x, x, temp1, GMP_RNDN);
    n = 2*n;
  }

  mpfr_set(res,x,GMP_RNDN);
  mpfr_clear(x); mpfr_clear(temp1); mpfr_clear(temp2);
  mpfr_clear(d);
}



void evaluateI(mpfi_t result, node *tree, mpfi_t x, mp_prec_t prec) {
  mpfi_t stack1, stack2;
  mpfi_t stack3, zI, numeratorInZI, denominatorInZI;
  mpfr_t al, ar, bl, br, xl, xr, z;
  node *derivNumerator, *derivDenominator, *tempNode;
 
  mpfi_init2(stack1, prec);
  mpfi_init2(stack2, prec);
  mpfi_init2(stack3, prec);
  mpfr_init2(al,prec);
  mpfr_init2(ar,prec);
  mpfr_init2(bl,prec);
  mpfr_init2(br,prec);

  switch (tree->nodeType) {
  case VARIABLE:
    mpfi_set(stack3,x);
    break;
  case CONSTANT:
    mpfi_set_fr(stack3,*(tree->value));
    break;
  case ADD:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_add(stack3, stack1, stack2);
    break;
  case SUB:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_sub(stack3, stack1, stack2);
    break;
  case MUL:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_mul(stack3, stack1, stack2);
    break;
  case DIV:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_get_left(al,stack1);
    mpfi_get_right(ar,stack1);
    mpfi_get_left(bl,stack2);
    mpfi_get_right(br,stack2);
    if (mpfr_zero_p(al) &&
	mpfr_zero_p(ar)) {
      if (mpfr_zero_p(bl) &&
	  mpfr_zero_p(br)) {
	/* [0;0] / [0;0] */
	derivNumerator = differentiate(tree->child1);
	derivDenominator = differentiate(tree->child2);
	
	evaluateI(stack1, derivNumerator, x, prec);
	evaluateI(stack2, derivDenominator, x, prec);
	
	free_memory(derivNumerator);
	free_memory(derivDenominator);
	mpfi_div(stack3, stack1, stack2);
      } else {
	/* [0;0] / [bl;br], bl,br != 0 */
	mpfi_interv_d(stack3,0.0,0.0);
      }
    } else {
      if (mpfi_has_zero(stack2)) {
	mpfr_init2(xl,prec);
	mpfr_init2(xr,prec);
	mpfr_init2(z,prec);
	
	mpfi_get_left(xl,x);
	mpfi_get_right(xr,x);

	derivDenominator = differentiate(tree->child2);

	newtonMPFR(z,tree->child2,derivDenominator,xl,xr,prec);

	mpfi_init2(zI,prec);
	mpfi_set_fr(zI,z);
	mpfi_init2(numeratorInZI,prec);
	mpfi_init2(denominatorInZI,prec);

	evaluateI(numeratorInZI, tree->child1, zI, prec);
	evaluateI(denominatorInZI, tree->child2, zI, prec);

	mpfi_get_left(al,numeratorInZI);
	mpfi_get_right(ar,numeratorInZI);
       	mpfi_get_left(bl,denominatorInZI);
	mpfi_get_right(br,denominatorInZI);

	if (mpfr_zero_p(al) && mpfr_zero_p(ar) && mpfr_zero_p(bl) && mpfr_zero_p(br)) {
	  /* Hopital's rule can be applied */

	  derivNumerator = differentiate(tree->child1);
	  
	  tempNode = (node *) malloc(sizeof(node));
	  tempNode->nodeType = DIV;
	  tempNode->child1 = derivNumerator;
	  tempNode->child2 = copyTree(derivDenominator);

	  evaluateI(stack3, tempNode, x, prec);
	
	  free_memory(tempNode);
	} else {
	  printf("Warning: a division in interval ");
	  printInterval(x);
	  printf(" generates infinity.\nTry to exclude a domain around ");
	  printValue(&z,prec);
	  printf("\n");

	  mpfi_div(stack3, stack1, stack2);
	}

	mpfi_clear(numeratorInZI);
	mpfi_clear(denominatorInZI);
	mpfi_clear(zI);
	free_memory(derivDenominator);
	mpfr_clear(xl);
	mpfr_clear(xr);
	mpfr_clear(z);
      } else {
	mpfi_div(stack3, stack1, stack2);
      }
    }
    break;
  case SQRT:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sqrt(stack3, stack1);
    break;
  case EXP:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_exp(stack3, stack1);
    break;
  case LOG:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log(stack3, stack1);
    break;
  case LOG_2:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log2(stack3, stack1);
    break;
  case LOG_10:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log10(stack3, stack1);
    break;
  case SIN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sin(stack3, stack1);
    break;
  case COS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_cos(stack3, stack1);
    break;
  case TAN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_tan(stack3, stack1);
    break;
  case ASIN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_asin(stack3, stack1);
    break;
  case ACOS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_acos(stack3, stack1);
    break;
  case ATAN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_atan(stack3, stack1);
    break;
  case SINH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sinh(stack3, stack1);
    break;
  case COSH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_cosh(stack3, stack1);
    break;
  case TANH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_tanh(stack3, stack1);
    break;
  case ASINH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_asinh(stack3, stack1);
    break;
  case ACOSH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_acosh(stack3, stack1);
    break;
  case ATANH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_atanh(stack3, stack1);
    break;
  case POW:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_pow(stack3, stack1, stack2);
    break;
  case NEG:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_neg(stack3, stack1);
    break;
  case ABS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_abs(stack3, stack1);  
    break;
  case DOUBLE:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_round_to_double(stack3, stack1);
    break;
  case DOUBLEDOUBLE:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_round_to_doubledouble(stack3, stack1);
    break;
  case TRIPLEDOUBLE:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_round_to_tripledouble(stack3, stack1);
    break;
  default:
    fprintf(stderr,"evaluateI: unknown identifier in the tree\n");
    exit(1);
  }

  mpfi_set(result,stack3);

  mpfi_revert_if_needed(result);

  mpfi_clear(stack1); mpfi_clear(stack2); mpfi_clear(stack3);
  mpfr_clear(al); mpfr_clear(ar); mpfr_clear(bl); mpfr_clear(br);

  return;
}

void evaluateITaylor(mpfi_t result, node *func, node *deriv, mpfi_t x, mp_prec_t prec) {
  mpfr_t xZ;
  mpfi_t xZI, constantTerm, linearTerm, resultTaylor, resultDirect;

  mpfr_init2(xZ,prec);
  mpfi_init2(xZI,prec);
  mpfi_init2(constantTerm,prec);
  mpfi_init2(linearTerm,prec);
  mpfi_init2(resultTaylor,prec);
  mpfi_init2(resultDirect,prec);

  mpfi_mid(xZ,x);
  mpfi_set_fr(xZI,xZ);

  evaluateI(constantTerm, func, xZI, prec);
  evaluateI(linearTerm, deriv, x, prec);
  mpfi_sub(xZI, x, xZI);
  mpfi_mul(linearTerm, xZI, linearTerm);
  mpfi_add(resultTaylor, constantTerm, linearTerm);

  evaluateI(resultDirect, func, x, prec);

  mpfi_intersect(result,resultTaylor,resultDirect);

  mpfi_revert_if_needed(result);

#if DEBUG2
  printf("evaluateITaylor:\nfunc = ");
  printTree(func);
  printf("\nderiv = ");
  printTree(deriv);
  printf("\nx = ");
  printInterval(x);
  printf("\nresultTaylor = ");
  printInterval(resultTaylor);
  printf("\nresultDirect = ");
  printInterval(resultDirect);
  printf("\nresult = ");
  printInterval(result);
  printf("\n\n");
#endif


  mpfr_clear(xZ);
  mpfi_clear(xZI);
  mpfi_clear(constantTerm);
  mpfi_clear(linearTerm);
  mpfi_clear(resultTaylor);
  mpfi_clear(resultDirect);
}



chain *findZeros(node *func, node *deriv, mpfi_t range, mp_prec_t prec, mpfr_t diam) {
  mpfr_t rangeDiam, l,m,r;
  chain *res, *leftchain, *rightchain;
  mpfi_t *temp;
  mpfi_t lI, rI, y;

  mpfi_revert_if_needed(range);
  mpfr_init2(rangeDiam,prec);
  mpfi_diam_abs(rangeDiam,range);
  if (mpfr_cmp(rangeDiam,diam) <= 0) {
    res = (chain *) malloc(sizeof(chain));
    res->next = NULL;
    temp = (mpfi_t *) malloc(sizeof(mpfi_t));
    mpfi_init2(*temp,prec);
    mpfi_set(*temp,range);
    mpfi_revert_if_needed(*temp);
    res->value = temp;
  } else {
    mpfi_init2(y,prec);
    evaluateITaylor(y, func, deriv, range, prec);
    if (mpfi_has_zero(y)) {
      mpfr_init2(l,prec);
      mpfr_init2(m,prec);
      mpfr_init2(r,prec);
      mpfi_get_left(l,range);
      mpfi_get_right(r,range);
      mpfi_mid(m,range);
      mpfi_init2(lI,prec);
      mpfi_init2(rI,prec);
      mpfi_interv_fr(lI,l,m);
      mpfi_revert_if_needed(lI);
      mpfi_interv_fr(rI,m,r);
      mpfi_revert_if_needed(rI);
   
      leftchain = findZeros(func,deriv,lI,prec,diam);
      rightchain = findZeros(func,deriv,rI,prec,diam);

      res = concatChains(leftchain,rightchain);

      mpfr_clear(l);
      mpfr_clear(m);
      mpfr_clear(r);    
      mpfi_clear(lI);
      mpfi_clear(rI);
    } else {
      res = NULL;
    }
    mpfi_clear(y);
  }
  mpfr_clear(rangeDiam);
  return res;
}


void printInterval(mpfi_t interval) {
  mpfr_t l,r;
  mp_prec_t prec;

  prec = mpfi_get_prec(interval);
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfi_get_left(l,interval);
  mpfi_get_right(r,interval);
  printf("[");
  printValue(&l,prec);
  printf(";");
  printValue(&r,prec);
  printf("]");

  mpfr_clear(l);
  mpfr_clear(r);
}


void freeMpfiPtr(void *i) {
  mpfi_clear(*((mpfi_t *) i));
  free(i);
}

chain *joinAdjacentIntervals(chain *intervals) {
  chain *newChain, *curr;
  mpfi_t *tempI;
  mp_prec_t prec, p;
  mpfr_t newLeft, newRight, l,r;


  if (intervals == NULL) return NULL;
  if (intervals->next == NULL) {
    tempI = (mpfi_t *) malloc(sizeof(mpfi_t));
    mpfi_init2(*tempI,mpfi_get_prec(*((mpfi_t *) (intervals->value))));
    mpfi_set(*tempI,*((mpfi_t *) (intervals->value)));
    newChain = addElement(NULL,tempI);
    return newChain;
  }

  prec = mpfi_get_prec(*((mpfi_t *) (intervals->value)));
  curr = intervals->next;
  while (curr != NULL) {
    p = mpfi_get_prec(*((mpfi_t *) (curr->value)));
    if (p > prec) prec = p;
    curr = curr->next;
  }


  mpfr_init2(newLeft,prec);
  mpfr_init2(newRight,prec);
  mpfi_get_left(newLeft,*((mpfi_t *) (intervals->value)));
  mpfi_get_right(newRight,*((mpfi_t *) (intervals->value)));
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);

  newChain = NULL;
  curr = intervals->next;
  while (curr != NULL) {
    mpfi_get_left(l,*((mpfi_t *) (curr->value)));
    mpfi_get_right(r,*((mpfi_t *) (curr->value)));
    if (mpfr_cmp(l,newRight) == 0) {
      mpfr_set(newRight,r,GMP_RNDN);
    } else {
      tempI = (mpfi_t *) malloc(sizeof(mpfi_t));
      mpfi_init2(*tempI,prec);
      mpfi_interv_fr(*tempI,newLeft,newRight);
      newChain = addElement(newChain,tempI);
      mpfr_set(newLeft,l,GMP_RNDN);
      mpfr_set(newRight,r,GMP_RNDN);
    }
    curr = curr->next;
  }
  tempI = (mpfi_t *) malloc(sizeof(mpfi_t));
  mpfi_init2(*tempI,prec);
  mpfi_interv_fr(*tempI,newLeft,newRight);
  newChain = addElement(newChain,tempI);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(newLeft);
  mpfr_clear(newRight);
  return newChain;
}



void infnormI(mpfi_t infnormval, node *func, node *deriv, 
	      node *numeratorDeriv, node *derivNumeratorDeriv,
	      mpfi_t range, mp_prec_t prec, mpfr_t diam) {
  chain *curr, *zeros, *tempChain;
  mpfi_t *currInterval;
  mpfi_t evalFuncOnInterval, lInterv, rInterv;
  mpfr_t innerLeft, innerRight, outerLeft, outerRight, l, r, tl, tr;
  mp_prec_t rangePrec;
#if DEBUG
  int i; 
#endif

  mpfr_init2(innerLeft, prec);
  mpfr_init2(innerRight, prec);
  mpfr_init2(outerLeft, prec);
  mpfr_init2(outerRight, prec);
  mpfr_init2(tl, prec);
  mpfr_init2(tr, prec);
  mpfi_init2(evalFuncOnInterval,prec);

  rangePrec = mpfi_get_prec(range);
  mpfr_init2(l,rangePrec);
  mpfr_init2(r,rangePrec);
  mpfi_get_left(l,range);
  mpfi_get_right(r,range);
  mpfi_init2(rInterv, rangePrec);
  mpfi_init2(lInterv, rangePrec);
  mpfi_set_fr(rInterv,r);
  mpfi_set_fr(lInterv,l);

  evaluateITaylor(evalFuncOnInterval, func, deriv, lInterv, prec);
  mpfi_get_left(outerLeft,evalFuncOnInterval);
  mpfi_get_right(outerRight,evalFuncOnInterval);
  mpfr_set(innerLeft,outerRight,GMP_RNDU);
  mpfr_set(innerRight,outerLeft,GMP_RNDD);
  evaluateITaylor(evalFuncOnInterval, func, deriv, rInterv, prec);
  mpfi_get_left(tl,evalFuncOnInterval);
  mpfi_get_right(tr,evalFuncOnInterval);
  mpfr_min(outerLeft,outerLeft,tl,GMP_RNDD);
  mpfr_max(outerRight,outerRight,tr,GMP_RNDU);
  mpfr_min(innerLeft,innerLeft,tr,GMP_RNDU);
  mpfr_max(innerRight,innerRight,tl,GMP_RNDD); 
 
  tempChain = findZeros(numeratorDeriv,derivNumeratorDeriv,range,prec,diam);
  zeros = joinAdjacentIntervals(tempChain);
#if DEBUG
  i = 0;
  for (curr=zeros;curr!=NULL;curr=curr->next) i++;
  printf("Found %d intervals possibly containing the zeros of the derivative\n",i);
#endif


  curr = zeros;
  while (curr != NULL) {
    currInterval = ((mpfi_t *) (curr->value));
    evaluateITaylor(evalFuncOnInterval, func, deriv, *currInterval, prec);
    mpfi_get_left(tl,evalFuncOnInterval);
    mpfi_get_right(tr,evalFuncOnInterval);
    mpfr_min(outerLeft,outerLeft,tl,GMP_RNDD);
    mpfr_max(outerRight,outerRight,tr,GMP_RNDU);
    mpfr_min(innerLeft,innerLeft,tr,GMP_RNDU); 
    mpfr_max(innerRight,innerRight,tl,GMP_RNDD); 
    curr = curr->next;
  }

  freeChain(zeros,freeMpfiPtr);
  freeChain(tempChain,freeMpfiPtr);

  if (mpfr_cmp(innerLeft,innerRight) >= 0) {
    mpfr_neg(outerLeft,outerLeft,GMP_RNDN);
    mpfr_max(tr,outerLeft,outerRight,GMP_RNDU);
    mpfr_set_d(tl,0.0,GMP_RNDD);
    mpfi_interv_fr(infnormval,tl,tr);
    mpfi_revert_if_needed(infnormval);
  } else {
    mpfr_neg(innerLeft,innerLeft,GMP_RNDN);
    mpfr_neg(outerLeft,outerLeft,GMP_RNDN);
    mpfr_max(tl,innerLeft,innerRight,GMP_RNDD);
    mpfr_max(tr,outerLeft,outerRight,GMP_RNDU);
    mpfi_interv_fr(infnormval,tl,tr);
    mpfi_revert_if_needed(infnormval);
  }
  mpfr_clear(tl);
  mpfr_clear(tr);
  mpfi_clear(lInterv);
  mpfi_clear(rInterv);
  mpfr_clear(l);
  mpfr_clear(r);
  mpfi_clear(evalFuncOnInterval);
  mpfr_clear(innerLeft);
  mpfr_clear(innerRight);
  mpfr_clear(outerLeft);
  mpfr_clear(outerRight);
}





rangetype infnorm(node *func, rangetype range, mp_prec_t prec, mpfr_t diam) {
  rangetype res;
  mpfi_t rangeI, resI;
  node *deriv, *numeratorDeriv, *derivNumeratorDeriv;
  mpfr_t rangeDiameter;

  res.a = (mpfr_t*) malloc(sizeof(mpfr_t));
  res.b = (mpfr_t*) malloc(sizeof(mpfr_t));
  mpfr_init2(*(res.a),prec);
  mpfr_init2(*(res.b),prec);
  mpfi_init2(rangeI,prec);
  mpfi_init2(resI,prec);
  mpfr_init2(rangeDiameter,prec);
  mpfr_sub(rangeDiameter,*(range.b),*(range.a),GMP_RNDD);
  mpfr_mul(rangeDiameter,rangeDiameter,diam,GMP_RNDD);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));
  deriv = differentiate(func);
  numeratorDeriv = getNumerator(deriv);
  derivNumeratorDeriv = differentiate(numeratorDeriv);

  
  infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,prec,rangeDiameter);


  mpfi_revert_if_needed(resI);
  mpfi_get_left(*(res.a),resI);
  mpfi_get_right(*(res.b),resI);
  free_memory(deriv);
  free_memory(numeratorDeriv);
  free_memory(derivNumeratorDeriv);
  mpfi_clear(rangeI);
  mpfi_clear(resI);
  mpfr_clear(rangeDiameter);
  return res;
}


chain* findZerosFunction(node *func, rangetype range, mp_prec_t prec, mpfr_t diam) {
  mpfi_t rangeI;
  node *deriv, *numerator;
  mpfr_t rangeDiameter;
  chain *zerosI, *zeros, *curr;
  rangetype *tempRange;
  chain *tempChain;

  mpfi_init2(rangeI,prec);
  mpfr_init2(rangeDiameter,prec);
  mpfr_sub(rangeDiameter,*(range.b),*(range.a),GMP_RNDD);
  mpfr_mul(rangeDiameter,rangeDiameter,diam,GMP_RNDD);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));

  numerator = getNumerator(func);
  deriv = differentiate(numerator);

  tempChain = findZeros(numerator,deriv,rangeI,prec,rangeDiameter);
  zerosI = joinAdjacentIntervals(tempChain);

  zeros = NULL;
  curr = zerosI;
  while (curr != NULL) {
    tempRange = (rangetype *) malloc(sizeof(rangetype));
    tempRange->a = (mpfr_t *) malloc(sizeof(mpfr_t));
    tempRange->b = (mpfr_t *) malloc(sizeof(mpfr_t));
    mpfr_init2(*(tempRange->a),prec);
    mpfr_init2(*(tempRange->b),prec);
    mpfi_get_left(*(tempRange->a),*((mpfi_t *) (curr->value)));
    mpfi_get_right(*(tempRange->b),*((mpfi_t *) (curr->value)));
    zeros = addElement(zeros,tempRange);
    curr = curr->next;
  }

  freeChain(zerosI,freeMpfiPtr);
  freeChain(tempChain,freeMpfiPtr);
  free_memory(numerator);
  free_memory(deriv);
  mpfi_clear(rangeI);
  mpfr_clear(rangeDiameter);
  return zeros;
}
