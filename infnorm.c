#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"
#include "infnorm.h"
#include "chain.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define DEBUG 0

typedef struct nodeIStruct nodeI;

struct nodeIStruct 
{
  int nodeType;
  mpfi_t *value;
  nodeI *child1;
  nodeI *child2;
};


void freeNodeI(nodeI *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    free(tree);
    break;
  case CONSTANT:
    mpfi_clear(*(tree->value));
    free(tree->value);
    free(tree);
    break;
  case ADD:
    freeNodeI(tree->child1);
    freeNodeI(tree->child2);
    free(tree);
    break;
  case SUB:
    freeNodeI(tree->child1);
    freeNodeI(tree->child2);
    free(tree);
    break;
  case MUL:
    freeNodeI(tree->child1);
    freeNodeI(tree->child2);
    free(tree);
    break;
  case DIV:
    freeNodeI(tree->child1);
    freeNodeI(tree->child2);
    free(tree);
    break;
  case SQRT:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case EXP:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case LOG:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case LOG2:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case LOG10:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case SIN:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case COS:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case TAN:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ASIN:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ACOS:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ATAN:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case SINH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case COSH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case TANH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ASINH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ACOSH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ATANH:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case POW:
    freeNodeI(tree->child1);
    freeNodeI(tree->child2);
    free(tree);
    break;
  case NEG:
    freeNodeI(tree->child1);
    free(tree);
    break;
  case ABS:
    freeNodeI(tree->child1);
    free(tree);
    break;
  default:
   fprintf(stderr,"freeNodeI: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;
}


nodeI* expressionToIntervalExpression(node *tree, mp_prec_t prec) {
  nodeI *copy;
  mpfi_t *value;

  switch (tree->nodeType) {
  case VARIABLE:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = VARIABLE;
    break;
  case CONSTANT:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = CONSTANT;
    value = (mpfi_t*) malloc(sizeof(mpfi_t));
    mpfi_init2(*value,prec);
    mpfi_set_fr(*value,*(tree->value));
    copy->value = value;
    break;
  case ADD:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ADD;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    copy->child2 = expressionToIntervalExpression(tree->child2,prec);
    break;
  case SUB:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = SUB;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    copy->child2 = expressionToIntervalExpression(tree->child2,prec);
    break;
  case MUL:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = MUL;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    copy->child2 = expressionToIntervalExpression(tree->child2,prec);
    break;
  case DIV:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = DIV;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    copy->child2 = expressionToIntervalExpression(tree->child2,prec);
    break;
  case SQRT:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = SQRT;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case EXP:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = EXP;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case LOG:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = LOG;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case LOG2:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = LOG2;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case LOG10:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = LOG10;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case SIN:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = SIN;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case COS:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = COS;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case TAN:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = TAN;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ASIN:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ASIN;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ACOS:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ACOS;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ATAN:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ATAN;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case SINH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = SINH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case COSH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = COSH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case TANH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = TANH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ASINH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ASINH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ACOSH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ACOSH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ATANH:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ATANH;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case POW:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = POW;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    copy->child2 = expressionToIntervalExpression(tree->child2,prec);
    break;
  case NEG:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = NEG;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  case ABS:
    copy = (nodeI*) malloc(sizeof(nodeI));
    copy->nodeType = ABS;
    copy->child1 = expressionToIntervalExpression(tree->child1,prec);
    break;
  default:
   fprintf(stderr,"expressionToIntervalExpression: unknown identifier in the tree\n");
   exit(1);
  }
  return copy;
}


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


void evaluateI(mpfi_t result, nodeI *tree, mpfi_t x, mp_prec_t prec) {
  mpfi_t stack1, stack2;

  mpfi_init2(stack1, prec);
  mpfi_init2(stack2, prec);

  switch (tree->nodeType) {
  case VARIABLE:
    mpfi_set(result, x);
    break;
  case CONSTANT:
    mpfi_set(result, *(tree->value));
    break;
  case ADD:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_add(result, stack1, stack2);
    break;
  case SUB:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_sub(result, stack1, stack2);
    break;
  case MUL:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_mul(result, stack1, stack2);
    break;
  case DIV:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_div(result, stack1, stack2);
    break;
  case SQRT:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sqrt(result, stack1);
    break;
  case EXP:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_exp(result, stack1);
    break;
  case LOG:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log(result, stack1);
    break;
  case LOG2:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log2(result, stack1);
    break;
  case LOG10:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_log10(result, stack1);
    break;
  case SIN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sin(result, stack1);
    break;
  case COS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_cos(result, stack1);
    break;
  case TAN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_tan(result, stack1);
    break;
  case ASIN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_asin(result, stack1);
    break;
  case ACOS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_acos(result, stack1);
    break;
  case ATAN:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_atan(result, stack1);
    break;
  case SINH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_sinh(result, stack1);
    break;
  case COSH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_cosh(result, stack1);
    break;
  case TANH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_tanh(result, stack1);
    break;
  case ASINH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_asinh(result, stack1);
    break;
  case ACOSH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_acosh(result, stack1);
    break;
  case ATANH:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_atanh(result, stack1);
    break;
  case POW:
    evaluateI(stack1, tree->child1, x, prec);
    evaluateI(stack2, tree->child2, x, prec);
    mpfi_pow(result, stack1, stack2);
    break;
  case NEG:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_neg(result, stack1);
    break;
  case ABS:
    evaluateI(stack1, tree->child1, x, prec);
    mpfi_abs(result, stack1);
  default:
    fprintf(stderr,"evaluateI: unknown identifier in the tree\n");
    exit(1);
  }

  mpfi_clear(stack1); mpfi_clear(stack2);
  return;
}

void evaluateITaylor(mpfi_t result, nodeI *func, nodeI *deriv, mpfi_t x, mp_prec_t prec) {
  mpfr_t xZ;
  mpfi_t xZI, constantTerm, linearTerm;

  mpfr_init2(xZ,prec);
  mpfi_init2(xZI,prec);
  mpfi_init2(constantTerm,prec);
  mpfi_init2(linearTerm,prec);

  mpfi_mid(xZ,x);
  mpfi_set_fr(xZI,xZ);

  evaluateI(constantTerm, func, xZI, prec);
  evaluateI(linearTerm, deriv, x, prec);
  mpfi_sub(xZI, x, xZI);
  mpfi_mul(linearTerm, xZI, linearTerm);
  mpfi_add(result, constantTerm, linearTerm);

  mpfr_clear(xZ);
  mpfi_clear(xZI);
  mpfi_clear(constantTerm);
  mpfi_clear(linearTerm);
}



chain *findZeros(nodeI *func, nodeI *deriv, mpfi_t range, mp_prec_t prec, mpfr_t diam) {
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

      res = concat(leftchain,rightchain);

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


void infnormI(mpfi_t infnormval, nodeI *func, nodeI *deriv, nodeI *second, mpfi_t range, mp_prec_t prec, mpfr_t diam) {
  chain *curr, *zeros;
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
 
#if DEBUG
  printf("Computing intervals possibly containing the zeros of the derivative\n");
#endif
  zeros = findZeros(deriv,second,range,prec,diam);
#if DEBUG
  i = 0;
  for (curr=zeros;curr!=NULL;curr=curr->next) i++;
  printf("Found %d intervals possibly containing the zeros of the derivative\nHandling them\n",i);
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
#if DEBUG
  printf("Done\n"); 
#endif

  freeChain(zeros,freeMpfiPtr);

  if (mpfr_cmp(innerLeft,innerRight) > 0) {
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
  nodeI *funcI, *derivI, *secondI;
  node *deriv, *second;

  res.a = (mpfr_t*) malloc(sizeof(mpfr_t));
  res.b = (mpfr_t*) malloc(sizeof(mpfr_t));
  mpfr_init2(*(res.a),prec);
  mpfr_init2(*(res.b),prec);
  mpfi_init2(rangeI,prec);
  mpfi_init2(resI,prec);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));
  funcI = expressionToIntervalExpression(func,prec);
  deriv = differentiate(func);
  second = differentiate(deriv);
  derivI = expressionToIntervalExpression(deriv,prec);
  secondI = expressionToIntervalExpression(second,prec);

  infnormI(resI,funcI,derivI,secondI,rangeI,prec,diam);


  mpfi_revert_if_needed(resI);
  mpfi_get_left(*(res.a),resI);
  mpfi_get_right(*(res.b),resI);
  freeNodeI(funcI);
  freeNodeI(derivI);
  freeNodeI(secondI);
  free_memory(deriv);
  free_memory(second);
  mpfi_clear(rangeI);
  mpfi_clear(resI);
  return res;
}
