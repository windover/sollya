#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"
#include "infnorm.h"
#include "chain.h"
#include "double.h"
#include "main.h"
#include "proof.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define DEBUG 0
#define DEBUGMPFI 0


void printInterval(mpfi_t interval);
void freeMpfiPtr(void *i);

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


int newtonMPFR(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t x, temp1, temp2;
  unsigned long int n=1;
  int okay, lucky;

  mpfr_init2(x,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec);

  okay = 0;

  evaluate(temp1, tree, a, prec);
  if (mpfr_zero_p(temp1)) {
    mpfr_set(res,a,GMP_RNDN);
    okay = 1;
  } else {
    evaluate(temp2, tree, b, prec);
    if (mpfr_zero_p(temp2)) {
      mpfr_set(res,b,GMP_RNDN);
      okay = 1;
    } else {
      
      mpfr_add(x,a,b,GMP_RNDN);
      mpfr_div_2ui(x,x,1,GMP_RNDN);
      lucky = 0;

      while((n<=prec+10) && (mpfr_cmp(a,x) <= 0) && (mpfr_cmp(x,b) <= 0)) {
	evaluate(temp1, tree, x, prec);
	if (mpfr_zero_p(temp1)) {
	  lucky = 1;
	  break;
	}
	evaluate(temp2, diff_tree, x, prec);
	mpfr_div(temp1, temp1, temp2, GMP_RNDN);
	mpfr_sub(x, x, temp1, GMP_RNDN);
	n = 2*n;
      }

      if (mpfr_cmp(x,a) < 0) {
	mpfr_set(res,a,GMP_RNDN);
	okay = 0;
      } else {
	if (mpfr_cmp(b,x) < 0) {
	  mpfr_set(res,b,GMP_RNDN);
	  okay = 0;
	} else {
	  mpfr_set(res,x,GMP_RNDN);
	  if (!lucky) {
	    evaluate(temp1, tree, x, prec);
	    evaluate(temp2, diff_tree, x, prec);
	    mpfr_div(temp1, temp1, temp2, GMP_RNDN);
	    mpfr_abs(temp1,temp1,GMP_RNDN);
	    mpfr_abs(x,x,GMP_RNDN);
	    mpfr_div_ui(x,x,1,GMP_RNDN);
	    okay = (mpfr_cmp(temp1,x) <= 0);
	  } else {
	    okay = 1;
	  }
	}
      }
    }
  }
  mpfr_clear(x); mpfr_clear(temp1); mpfr_clear(temp2);
  return okay;
}


void makeMpfiAroundMpfr(mpfi_t res, mpfr_t x, unsigned int thousandUlps) {
  mpfr_t xp, xs;
  mp_prec_t prec;
  mpfi_t xI;


  prec = mpfr_get_prec(x);
  mpfr_init2(xp,prec);
  mpfr_init2(xs,prec);
  mpfi_init2(xI,prec);
  
  mpfr_set(xp,x,GMP_RNDD);
  mpfr_set(xs,x,GMP_RNDU);

  mpfr_nextbelow(xp);
  mpfr_nextabove(xs);

  mpfi_interv_fr(xI,xp,xs);
  
  mpfi_revert_if_needed(xI);
  
  mpfi_blow(xI,xI,(((double) thousandUlps) * 250.0));

  mpfi_set(res,xI);
  
  mpfi_clear(xI);
  mpfr_clear(xp);
  mpfr_clear(xs);
}



chain* evaluateI(mpfi_t result, node *tree, mpfi_t x, mp_prec_t prec, int simplifies, exprBoundTheo *theo) {
  mpfi_t stack1, stack2;
  mpfi_t stack3, zI, numeratorInZI, denominatorInZI, newExcludeTemp, xMXZ, temp1, temp2;
  mpfi_t *newExclude;
  mpfi_t leftConstantTerm, rightConstantTerm;
  mpfi_t leftLinearTerm, rightLinearTerm;
  mpfr_t al, ar, bl, br, xl, xr, z, z2;
  node *derivNumerator, *derivDenominator, *tempNode;
  node *derivLeft, *derivRight;
  chain *leftExcludes, *rightExcludes, *excludes, *t1, *t2;
  chain *leftExcludesConstant, *rightExcludesConstant;
  chain *leftExcludesLinear, *rightExcludesLinear;
  exprBoundTheo *leftTheo, *rightTheo, *internalTheo; 
  exprBoundTheo *leftTheoConstant, *rightTheoConstant, *leftTheoLinear, *rightTheoLinear;
  int isPolynom;

  if (theo != NULL) nullifyExprBoundTheo(theo);

  isPolynom = 0;
  internalTheo = NULL;
  if (theo != NULL) {
    isPolynom = isPolynomial(tree);
    
    if (isPolynom) {
      theo->functionType = POLYNOMIAL;
      leftTheo = NULL;
      rightTheo = NULL;
    } else {
      internalTheo = theo;
      internalTheo->functionType = tree->nodeType;
      switch (arity(tree)) {
      case 1:
	leftTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	rightTheo = NULL;
	internalTheo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeft),prec);
	break;
      case 2:
	leftTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	rightTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	internalTheo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeft),prec);
	internalTheo->boundRight = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundRight),prec);
	break;
      default:
	leftTheo = NULL;
	rightTheo = NULL;
	break;
      }
      internalTheo->theoLeft = leftTheo;
      internalTheo->theoRight = rightTheo;
    }

    theo->x = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*(theo->x),mpfi_get_prec(x));
    mpfi_set(*(theo->x),x);
    theo->function = copyTree(tree);
  } else {
    leftTheo = NULL;
    rightTheo = NULL;
  }


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
    excludes = NULL;
    break;
  case CONSTANT:
    mpfi_set_fr(stack3,*(tree->value));
    excludes = NULL;
    break;
  case ADD:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifies, rightTheo);
    mpfi_add(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    if ((mpfi_has_zero(stack3)) && (simplifies >= 0)) {

      if (internalTheo != NULL) {
	internalTheo->simplificationUsed = DECORRELATE;
	leftTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(leftTheoConstant);
	rightTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(rightTheoConstant);
	leftTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(leftTheoLinear);
	rightTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(rightTheoLinear);
	internalTheo->theoLeftConstant = leftTheoConstant;
	internalTheo->theoRightConstant = rightTheoConstant;
	internalTheo->theoLeftLinear = leftTheoLinear;
	internalTheo->theoRightLinear = rightTheoLinear;
      } else {
	leftTheoConstant = NULL;
	rightTheoConstant = NULL;
	leftTheoLinear = NULL;
	rightTheoLinear = NULL;
      }

      mpfr_init2(z,prec);
      mpfi_init2(zI,prec);
      mpfi_init2(leftConstantTerm,prec);
      mpfi_init2(rightConstantTerm,prec);
      mpfi_init2(leftLinearTerm,prec);
      mpfi_init2(rightLinearTerm,prec);
      mpfi_init2(xMXZ,prec);
      mpfi_init2(temp1,prec);
      mpfi_init2(temp2,prec);

      mpfi_mid(z,x);
      mpfi_set_fr(zI,z);

      leftExcludesConstant = evaluateI(leftConstantTerm, tree->child1, zI, prec, simplifies-1, leftTheoConstant);
      rightExcludesConstant = evaluateI(rightConstantTerm, tree->child2, zI, prec, simplifies-1, rightTheoConstant);

      derivLeft = differentiate(tree->child1);
      derivRight = differentiate(tree->child2);

      leftExcludesLinear = evaluateI(leftLinearTerm, derivLeft, x, prec, simplifies-1, leftTheoLinear);
      rightExcludesLinear = evaluateI(rightLinearTerm, derivRight, x, prec, simplifies-1, rightTheoLinear);

      mpfi_add(temp1,leftConstantTerm,rightConstantTerm);
      mpfi_add(temp2,leftLinearTerm,rightLinearTerm);

      mpfi_sub(xMXZ,x,zI);

      mpfi_mul(temp2,xMXZ,temp2);
      mpfi_add(temp1,temp1,temp2);

      mpfi_get_left(al,temp1);
      mpfi_get_right(ar,temp1);

      if (mpfr_number_p(al) && mpfr_number_p(ar)) {
	mpfi_intersect(stack3,stack3,temp1);
	excludes = concatChains(leftExcludes,rightExcludes);
	excludes = concatChains(excludes,leftExcludesConstant);
	excludes = concatChains(excludes,rightExcludesConstant);	
	excludes = concatChains(excludes,leftExcludesLinear);
	excludes = concatChains(excludes,rightExcludesLinear);

	internalTheo->boundLeftConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeftConstant),prec);
	internalTheo->boundRightConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundRightConstant),prec);
	internalTheo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeftLinear),prec);
	internalTheo->boundRightLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundRightLinear),prec);
	internalTheo->xZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->xZ),prec);
	internalTheo->xMXZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->xMXZ),prec);
	internalTheo->leftDerivative = copyTree(derivLeft);
	internalTheo->rightDerivative = copyTree(derivRight);
	mpfi_set(*(internalTheo->boundLeftConstant),leftConstantTerm);
	mpfi_set(*(internalTheo->boundRightConstant),rightConstantTerm);
	mpfi_set(*(internalTheo->boundLeftLinear),leftLinearTerm);
	mpfi_set(*(internalTheo->boundRightLinear),rightLinearTerm);
	mpfi_set(*(internalTheo->xZ),zI);
	mpfi_set(*(internalTheo->xMXZ),xMXZ);
      } else {
	if (internalTheo != NULL) {
	  internalTheo->simplificationUsed = 0;
	  freeExprBoundTheo(internalTheo->theoLeftConstant);
	  internalTheo->theoLeftConstant = NULL;
	  freeExprBoundTheo(internalTheo->theoRightConstant);
	  internalTheo->theoRightConstant = NULL;
	  freeExprBoundTheo(internalTheo->theoLeftLinear);
	  internalTheo->theoLeftLinear = NULL;
	  freeExprBoundTheo(internalTheo->theoRightLinear);
	  internalTheo->theoRightLinear = NULL;
	}
	excludes = concatChains(leftExcludes,rightExcludes);
      }

      free_memory(derivLeft);
      free_memory(derivRight);
      mpfr_clear(z);
      mpfi_clear(zI);
      mpfi_clear(xMXZ);
      mpfi_clear(temp1);
      mpfi_clear(temp2);
      mpfi_clear(leftConstantTerm);
      mpfi_clear(rightConstantTerm);
      mpfi_clear(leftLinearTerm);
      mpfi_clear(rightLinearTerm);
    } else {
      excludes = concatChains(leftExcludes,rightExcludes);
    }
    break;
  case SUB:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifies, rightTheo);
    mpfi_sub(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    if ((mpfi_has_zero(stack3)) && (simplifies >= 0)) {

      if (internalTheo != NULL) {
	internalTheo->simplificationUsed = DECORRELATE;
	leftTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(leftTheoConstant);
	rightTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(rightTheoConstant);
	leftTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(leftTheoLinear);
	rightTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	nullifyExprBoundTheo(rightTheoLinear);
	internalTheo->theoLeftConstant = leftTheoConstant;
	internalTheo->theoRightConstant = rightTheoConstant;
	internalTheo->theoLeftLinear = leftTheoLinear;
	internalTheo->theoRightLinear = rightTheoLinear;
      } else {
	leftTheoConstant = NULL;
	rightTheoConstant = NULL;
	leftTheoLinear = NULL;
	rightTheoLinear = NULL;
      }

      mpfr_init2(z,prec);
      mpfi_init2(zI,prec);
      mpfi_init2(leftConstantTerm,prec);
      mpfi_init2(rightConstantTerm,prec);
      mpfi_init2(leftLinearTerm,prec);
      mpfi_init2(rightLinearTerm,prec);
      mpfi_init2(xMXZ,prec);
      mpfi_init2(temp1,prec);
      mpfi_init2(temp2,prec);

      mpfi_mid(z,x);
      mpfi_set_fr(zI,z);

      leftExcludesConstant = evaluateI(leftConstantTerm, tree->child1, zI, prec, simplifies-1, leftTheoConstant);
      rightExcludesConstant = evaluateI(rightConstantTerm, tree->child2, zI, prec, simplifies-1, rightTheoConstant);

      derivLeft = differentiate(tree->child1);
      derivRight = differentiate(tree->child2);

      leftExcludesLinear = evaluateI(leftLinearTerm, derivLeft, x, prec, simplifies-1, leftTheoLinear);
      rightExcludesLinear = evaluateI(rightLinearTerm, derivRight, x, prec, simplifies-1, rightTheoLinear);

      mpfi_sub(temp1,leftConstantTerm,rightConstantTerm);
      mpfi_sub(temp2,leftLinearTerm,rightLinearTerm);

      mpfi_sub(xMXZ,x,zI);

      mpfi_mul(temp2,xMXZ,temp2);
      mpfi_add(temp1,temp1,temp2);

      mpfi_get_left(al,temp1);
      mpfi_get_right(ar,temp1);

      if (mpfr_number_p(al) && mpfr_number_p(ar)) {
	mpfi_intersect(stack3,stack3,temp1);
	excludes = concatChains(leftExcludes,rightExcludes);
	excludes = concatChains(excludes,leftExcludesConstant);
	excludes = concatChains(excludes,rightExcludesConstant);	
	excludes = concatChains(excludes,leftExcludesLinear);
	excludes = concatChains(excludes,rightExcludesLinear);

	internalTheo->boundLeftConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeftConstant),prec);
	internalTheo->boundRightConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundRightConstant),prec);
	internalTheo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundLeftLinear),prec);
	internalTheo->boundRightLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->boundRightLinear),prec);
	internalTheo->xZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->xZ),prec);
	internalTheo->xMXZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(internalTheo->xMXZ),prec);
	internalTheo->leftDerivative = copyTree(derivLeft);
	internalTheo->rightDerivative = copyTree(derivRight);
	mpfi_set(*(internalTheo->boundLeftConstant),leftConstantTerm);
	mpfi_set(*(internalTheo->boundRightConstant),rightConstantTerm);
	mpfi_set(*(internalTheo->boundLeftLinear),leftLinearTerm);
	mpfi_set(*(internalTheo->boundRightLinear),rightLinearTerm);
	mpfi_set(*(internalTheo->xZ),zI);
	mpfi_set(*(internalTheo->xMXZ),xMXZ);
      } else {
	if (internalTheo != NULL) {
	  internalTheo->simplificationUsed = 0;
	  freeExprBoundTheo(internalTheo->theoLeftConstant);
	  internalTheo->theoLeftConstant = NULL;
	  freeExprBoundTheo(internalTheo->theoRightConstant);
	  internalTheo->theoRightConstant = NULL;
	  freeExprBoundTheo(internalTheo->theoLeftLinear);
	  internalTheo->theoLeftLinear = NULL;
	  freeExprBoundTheo(internalTheo->theoRightLinear);
	  internalTheo->theoRightLinear = NULL;
	}
	excludes = concatChains(leftExcludes,rightExcludes);
      }

      free_memory(derivLeft);
      free_memory(derivRight);
      mpfr_clear(z);
      mpfi_clear(zI);
      mpfi_clear(xMXZ);
      mpfi_clear(temp1);
      mpfi_clear(temp2);
      mpfi_clear(leftConstantTerm);
      mpfi_clear(rightConstantTerm);
      mpfi_clear(leftLinearTerm);
      mpfi_clear(rightLinearTerm);
    } else {
      excludes = concatChains(leftExcludes,rightExcludes);
    }
    break;
  case MUL:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifies, rightTheo);
    mpfi_mul(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    excludes = concatChains(leftExcludes,rightExcludes);
    break;
  case DIV:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifies, rightTheo);

    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }

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
	
	freeChain(leftExcludes,freeMpfiPtr);
	freeChain(rightExcludes,freeMpfiPtr);

	if (internalTheo != NULL) {
	  internalTheo->simplificationUsed = HOPITAL_ON_POINT;
	  internalTheo->leftDerivative = copyTree(derivNumerator);
	  internalTheo->rightDerivative = copyTree(derivDenominator);
	  leftTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	  rightTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	  internalTheo->theoLeftLinear = leftTheoLinear;
	  internalTheo->theoRightLinear = rightTheoLinear;
	} else {
	  leftTheoLinear = NULL;
	  rightTheoLinear = NULL;
	}

	leftExcludes = evaluateI(stack1, derivNumerator, x, prec, simplifies, leftTheoLinear);
	rightExcludes = evaluateI(stack2, derivDenominator, x, prec, simplifies, rightTheoLinear);
	
	free_memory(derivNumerator);
	free_memory(derivDenominator);
	mpfi_div(stack3, stack1, stack2);
	excludes = concatChains(leftExcludes,rightExcludes);
      } else {
	/* [0;0] / [bl;br], bl,br != 0 */
	freeChain(rightExcludes,freeMpfiPtr);
	mpfi_interv_d(stack3,0.0,0.0);
	excludes = leftExcludes;
	if (internalTheo != NULL) {
	  internalTheo->simplificationUsed = NUMERATOR_IS_ZERO;
	  freeExprBoundTheo(internalTheo->theoRight);
	  internalTheo->theoRight = NULL;
	  freeMpfiPtr(internalTheo->boundRight);
	  internalTheo->boundRight = NULL;
	}
      }
    } else {
      if (mpfi_has_zero(stack2) && 
	  (simplifies >= 0)) {
	mpfr_init2(xl,prec);
	mpfr_init2(xr,prec);

	mpfi_get_left(xl,x);
	mpfi_get_right(xr,x);

	if (mpfr_cmp(xl,xr) != 0) {
	  mpfr_init2(z,prec);
	  
	  derivDenominator = differentiate(tree->child2);
	  
	  newtonMPFR(z,tree->child2,derivDenominator,xl,xr,prec);
	  
	  if (mpfr_number_p(z)) {
	    mpfi_init2(zI,prec);
	    mpfi_set_fr(zI,z);
	    mpfi_init2(numeratorInZI,prec);
	    mpfi_init2(denominatorInZI,prec);
	    
	    if (internalTheo != NULL) {
	      	  leftTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		  rightTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
	    } else {
	      leftTheoConstant = NULL;
	      rightTheoConstant = NULL;
	    }

	    t1 = evaluateI(numeratorInZI, tree->child1, zI, prec, simplifies-1, leftTheoConstant);
	    t2 = evaluateI(denominatorInZI, tree->child2, zI, prec, simplifies-1, rightTheoConstant);
	  
	    freeChain(t1,freeMpfiPtr);
	    freeChain(t2,freeMpfiPtr);

	    mpfi_get_left(al,numeratorInZI);
	    mpfi_get_right(ar,numeratorInZI);
	    mpfi_get_left(bl,denominatorInZI);
	    mpfi_get_right(br,denominatorInZI);
	    
	    if (mpfr_zero_p(al) && mpfr_zero_p(ar) && mpfr_zero_p(bl) && mpfr_zero_p(br)) {
	      /* Hopital's rule can be applied */

	      derivNumerator = differentiate(tree->child1);
	      
	      tempNode = (node *) safeMalloc(sizeof(node));
	      tempNode->nodeType = DIV;
	      tempNode->child1 = derivNumerator;
	      tempNode->child2 = copyTree(derivDenominator);
	      
	      freeChain(leftExcludes,freeMpfiPtr);
	      freeChain(rightExcludes,freeMpfiPtr);

	      if (internalTheo != NULL) {
		leftTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		nullifyExprBoundTheo(leftTheoLinear); 
		internalTheo->simplificationUsed = HOPITAL;
		internalTheo->leftDerivative = copyTree(tempNode->child1);
		internalTheo->rightDerivative = copyTree(tempNode->child2);
		internalTheo->theoLeftConstant = leftTheoConstant;
		internalTheo->theoRightConstant = rightTheoConstant;
		internalTheo->theoLeftLinear = leftTheoLinear;
		internalTheo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		mpfi_init2(*(internalTheo->boundLeftLinear),prec);
		internalTheo->boundLeftConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		mpfi_init2(*(internalTheo->boundLeftConstant),prec);
		internalTheo->boundRightConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		mpfi_init2(*(internalTheo->boundRightConstant),prec);
		mpfi_set(*(internalTheo->boundLeftConstant),numeratorInZI);
		mpfi_set(*(internalTheo->boundRightConstant),denominatorInZI);
		internalTheo->xZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		mpfi_init2(*(internalTheo->xZ),prec);
		mpfi_set(*(internalTheo->xZ),zI);
	      } else {
		leftTheoLinear = NULL;
	      }

	      excludes = evaluateI(stack3, tempNode, x, prec, simplifies-1, leftTheoLinear);

	      if (internalTheo != NULL) mpfi_set(*(internalTheo->boundLeftLinear),stack3);
	      
	      free_memory(tempNode);
	    } else {
	    
	      if (internalTheo != NULL) {
		freeExprBoundTheo(leftTheoConstant);
		freeExprBoundTheo(rightTheoConstant);
	      }
  
	      mpfr_init2(z2,prec);

	      derivNumerator = differentiate(tree->child1);

	      newtonMPFR(z2,tree->child1,derivNumerator,xl,xr,prec);

	      if (mpfr_number_p(z2)) {
		mpfi_set_fr(zI,z2);

		if (internalTheo != NULL) {
		  leftTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		  rightTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		} else {
		  leftTheoConstant = NULL;
		  rightTheoConstant = NULL;
		}
	    
		t1 = evaluateI(numeratorInZI, tree->child1, zI, prec, simplifies-1, leftTheoConstant);
		t2 = evaluateI(denominatorInZI, tree->child2, zI, prec, simplifies-1, rightTheoConstant);

		freeChain(t1,freeMpfiPtr);
		freeChain(t2,freeMpfiPtr);

		mpfi_get_left(al,numeratorInZI);
		mpfi_get_right(ar,numeratorInZI);
		mpfi_get_left(bl,denominatorInZI);
		mpfi_get_right(br,denominatorInZI);
		
		if (mpfr_zero_p(al) && mpfr_zero_p(ar) && mpfr_zero_p(bl) && mpfr_zero_p(br)) {
		  /* Hopital's rule can be applied */
		  
		  tempNode = (node *) safeMalloc(sizeof(node));
		  tempNode->nodeType = DIV;
		  tempNode->child1 = derivNumerator;
		  tempNode->child2 = copyTree(derivDenominator);

		  freeChain(leftExcludes,freeMpfiPtr);
		  freeChain(rightExcludes,freeMpfiPtr);

		  if (internalTheo != NULL) {
		    leftTheoLinear = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		    nullifyExprBoundTheo(leftTheoLinear); 
		    internalTheo->simplificationUsed = HOPITAL;
		    internalTheo->leftDerivative = copyTree(tempNode->child1);
		    internalTheo->rightDerivative = copyTree(tempNode->child2);
		    internalTheo->theoLeftConstant = leftTheoConstant;
		    internalTheo->theoRightConstant = rightTheoConstant;
		    internalTheo->theoLeftLinear = leftTheoLinear;
		    internalTheo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		    mpfi_init2(*(internalTheo->boundLeftLinear),prec);
		    internalTheo->boundLeftConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		    mpfi_init2(*(internalTheo->boundLeftConstant),prec);
		    internalTheo->boundRightConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		    mpfi_init2(*(internalTheo->boundRightConstant),prec);
		    mpfi_set(*(internalTheo->boundLeftConstant),numeratorInZI);
		    mpfi_set(*(internalTheo->boundRightConstant),denominatorInZI);
		    internalTheo->xZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		    mpfi_init2(*(internalTheo->xZ),prec);
		    mpfi_set(*(internalTheo->xZ),zI);
		  } else {
		    leftTheoLinear = NULL;
		  }

		  excludes = evaluateI(stack3, tempNode, x, prec, simplifies-1, leftTheoLinear);

		  if (internalTheo != NULL) mpfi_set(*(internalTheo->boundLeftLinear),stack3);
	      
		  free_memory(tempNode);
		} else {

		  if (internalTheo != NULL) {
		    freeExprBoundTheo(leftTheoConstant);
		    freeExprBoundTheo(rightTheoConstant);
		  }

		  newExclude = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		  mpfi_init2(*newExclude,prec);
		  makeMpfiAroundMpfr(*newExclude,z,16777216);
 		  mpfi_init2(newExcludeTemp,prec);
		  makeMpfiAroundMpfr(newExcludeTemp,z2,16777216);
		  mpfi_union(*newExclude,*newExclude,newExcludeTemp);
		  mpfi_clear(newExcludeTemp);

		  excludes = concatChains(leftExcludes,rightExcludes);
		  excludes = addElement(excludes,newExclude);

		  mpfr_clear(z2);
		  mpfi_div(stack3, stack1, stack2);
		}
	      } else {

		mpfr_clear(z2);

		newExclude = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
		mpfi_init2(*newExclude,prec);
		makeMpfiAroundMpfr(*newExclude,z,16777216);
	    	excludes = concatChains(leftExcludes,rightExcludes);
		excludes = addElement(excludes,newExclude);

		mpfi_div(stack3, stack1, stack2);
	      }
	    }

	    mpfi_clear(numeratorInZI);
	    mpfi_clear(denominatorInZI);
	    mpfi_clear(zI);
	  } else {
	    mpfi_div(stack3, stack1, stack2);
	    excludes = concatChains(leftExcludes,rightExcludes);
	  }
	  free_memory(derivDenominator);
	  mpfr_clear(z);
	} else {
	  mpfi_div(stack3, stack1, stack2);
	  excludes = concatChains(leftExcludes,rightExcludes);
	}
	mpfr_clear(xl);
	mpfr_clear(xr);
      } else {
	mpfi_div(stack3, stack1, stack2);
	excludes = concatChains(leftExcludes,rightExcludes);
      }
    }
    break;
  case SQRT:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_sqrt(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case EXP:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_exp(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_log(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG_2:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_log2(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG_10:
    evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_log10(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case SIN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_sin(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }

#if DEBUGMPFI 
    printf("mpfi_sin(");
    printInterval(stack1);
    printf(") = ");
    printInterval(stack3);
    printf("\n");
#endif    

    break;
  case COS:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_cos(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }

#if DEBUGMPFI 
    printf("mpfi_cos(");
    printInterval(stack1);
    printf(") = ");
    printInterval(stack3);
    printf("\n");
#endif    

    break;
  case TAN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_tan(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ASIN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_asin(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ACOS:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_acos(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ATAN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_atan(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case SINH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_sinh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case COSH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_cosh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case TANH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_tanh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ASINH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_asinh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ACOSH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_acosh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ATANH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_atanh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case POW:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifies, rightTheo);
    mpfi_pow(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    excludes = concatChains(leftExcludes,rightExcludes);
    break;
  case NEG:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_neg(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ABS:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_abs(stack3, stack1);  
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case DOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_round_to_double(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case DOUBLEDOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_round_to_doubledouble(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case TRIPLEDOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifies, leftTheo);
    mpfi_round_to_tripledouble(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  default:
    fprintf(stderr,"evaluateI: unknown identifier in the tree\n");
    exit(1);
  }

  mpfi_set(result,stack3);
  mpfi_revert_if_needed(result);

  if (theo != NULL) {
    theo->y = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*(theo->y),mpfi_get_prec(result));
    mpfi_set(*(theo->y),result);
  }
  mpfi_clear(stack1); 
  mpfi_clear(stack2); 
  mpfi_clear(stack3);
  mpfr_clear(al); 
  mpfr_clear(ar); 
  mpfr_clear(bl); 
  mpfr_clear(br);

  return excludes;
}

chain* evaluateITaylor(mpfi_t result, node *func, node *deriv, mpfi_t x, mp_prec_t prec, exprBoundTheo *theo) {
  mpfr_t xZ, rTl, rTr;
  mpfi_t xZI, constantTerm, linearTerm, resultTaylor, resultDirect, temp;
  chain *excludes, *directExcludes, *taylorExcludes, *taylorExcludesLinear, *taylorExcludesConstant;
  exprBoundTheo *constantTheo, *linearTheo, *directTheo;

  if (theo != NULL) {
    nullifyExprBoundTheo(theo);

    if (!isPolynomial(func)) {
      constantTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      nullifyExprBoundTheo(constantTheo);
      linearTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      nullifyExprBoundTheo(linearTheo);
      directTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      nullifyExprBoundTheo(directTheo);
      theo->functionType = func->nodeType;
    } else {
      constantTheo = NULL;
      linearTheo = NULL;
      directTheo = NULL;
      theo->functionType = POLYNOMIAL;
    }
    theo->function = copyTree(func);
    theo->x = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*(theo->x),prec);
    mpfi_set(*(theo->x),x);
    theo->y = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*(theo->y),prec);
  } else {
    constantTheo = NULL;
    linearTheo = NULL;
    directTheo = NULL;
  }

  mpfr_init2(xZ,prec);
  mpfi_init2(xZI,prec);
  mpfi_init2(temp,prec);
  mpfi_init2(constantTerm,prec);
  mpfi_init2(linearTerm,prec);
  mpfi_init2(resultTaylor,prec);
  mpfi_init2(resultDirect,prec);

  mpfr_init2(rTl,prec);
  mpfr_init2(rTr,prec);

  mpfi_mid(xZ,x);
  mpfi_set_fr(xZI,xZ);

  taylorExcludesConstant = evaluateI(constantTerm, func, xZI, prec, 2, constantTheo);
  taylorExcludesLinear = evaluateI(linearTerm, deriv, x, prec, 2, linearTheo);
  mpfi_sub(temp, x, xZI);
  mpfi_mul(linearTerm, temp, linearTerm);
  mpfi_add(resultTaylor, constantTerm, linearTerm);
  taylorExcludes = concatChains(taylorExcludesConstant, taylorExcludesLinear);
  
  directExcludes = evaluateI(resultDirect, func, x, prec, 2, directTheo);

  mpfi_get_left(rTl,resultTaylor);
  mpfi_get_right(rTr,resultTaylor);
  
  if (mpfr_number_p(rTl) && mpfr_number_p(rTr)) {
    mpfi_intersect(result,resultTaylor,resultDirect);
    excludes = concatChains(directExcludes,taylorExcludes);
    if (theo != NULL) {
      if (theo->functionType != POLYNOMIAL) {
	theo->simplificationUsed = TAYLOR;
	theo->theoLeft = directTheo;
	theo->theoLeftConstant = constantTheo;
	theo->theoLeftLinear = linearTheo;
	theo->leftDerivative = copyTree(deriv);
	theo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeft),prec);
	mpfi_set(*(theo->boundLeft),resultDirect);
	theo->boundRight = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundRight),prec);
	mpfi_set(*(theo->boundRight),resultTaylor);
	theo->boundLeftConstant = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeftConstant),prec);
	mpfi_set(*(theo->boundLeftConstant),constantTerm);
	theo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeftLinear),prec);
	mpfi_set(*(theo->boundLeftLinear),linearTerm);
	theo->xZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->xZ),prec);
	mpfi_set(*(theo->xZ),xZI);
	theo->xMXZ = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->xMXZ),prec);
	mpfi_set(*(theo->xMXZ),temp);
      }
    }
  } else {
    mpfi_set(result,resultDirect);
    freeChain(taylorExcludes,freeMpfiPtr);
    excludes = directExcludes;
    if (theo != NULL) {
      if (theo->functionType != POLYNOMIAL) {
	theo->simplificationUsed = IMPLICATION;
	theo->theoLeft = directTheo;
	theo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeft),prec);
	mpfi_set(*(theo->boundLeft),resultDirect);
	freeExprBoundTheo(constantTheo);
	freeExprBoundTheo(linearTheo);
      }
    }
  }

  mpfi_revert_if_needed(result);

  if (theo != NULL) mpfi_set(*(theo->y),result);

  mpfr_clear(xZ);
  mpfr_clear(rTl);
  mpfr_clear(rTr);
  mpfi_clear(xZI);
  mpfi_clear(temp);
  mpfi_clear(constantTerm);
  mpfi_clear(linearTerm);
  mpfi_clear(resultTaylor);
  mpfi_clear(resultDirect);

  return excludes;
}



chain *findZerosUnsimplified(node *func, node *deriv, mpfi_t range, mp_prec_t prec, mpfr_t diam, chain **noZeroProofs) {
  mpfr_t rangeDiam, l,m,r;
  chain *res, *leftchain, *rightchain;
  mpfi_t *temp;
  mpfi_t lI, rI, y;
  chain *excludes;
  chain *leftProofs, *rightProofs;
  chain **leftProofsPtr, **rightProofsPtr;
  exprBoundTheo *theo;

  leftProofs = NULL;
  rightProofs = NULL;
  if (noZeroProofs != NULL) {
    leftProofsPtr = &leftProofs;
    rightProofsPtr = &rightProofs;
    theo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
  } else {
    leftProofsPtr = NULL;
    rightProofsPtr = NULL;
    theo = NULL;
  }

  mpfi_revert_if_needed(range);
  mpfr_init2(rangeDiam,prec);
  mpfi_diam_abs(rangeDiam,range);
  if (mpfr_cmp(rangeDiam,diam) <= 0) {
    res = (chain *) safeMalloc(sizeof(chain));
    res->next = NULL;
    temp = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp,prec);
    mpfi_set(*temp,range);
    mpfi_revert_if_needed(*temp);
    res->value = temp;
  } else {
    mpfi_init2(y,prec);
    excludes = evaluateITaylor(y, func, deriv, range, prec, theo);
    freeChain(excludes,freeMpfiPtr);
    if (!mpfi_bounded_p(y)) {
      printf("Warning: during zero-search the derivative of the function evaluated to NaN or Inf in the interval ");
      printInterval(y);
      printf(".\nThe function might not be continuously differentiable in this interval.\n");
    }
    if ((!mpfi_bounded_p(y)) || mpfi_has_zero(y)) {
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

      if (theo != NULL) freeExprBoundTheo(theo);
   
      leftchain = findZerosUnsimplified(func,deriv,lI,prec,diam,leftProofsPtr);
      rightchain = findZerosUnsimplified(func,deriv,rI,prec,diam,rightProofsPtr);

      res = concatChains(leftchain,rightchain);

      if (noZeroProofs != NULL) {
	*noZeroProofs = concatChains(leftProofs,rightProofs);
      }

      mpfr_clear(l);
      mpfr_clear(m);
      mpfr_clear(r);    
      mpfi_clear(lI);
      mpfi_clear(rI);
    } else {
      res = NULL;
      if (noZeroProofs != NULL) *noZeroProofs = addElement(*noZeroProofs,theo);
    }
    mpfi_clear(y);
  }
  mpfr_clear(rangeDiam);
  return res;
}

chain *findZeros(node *func, node *deriv, mpfi_t range, mp_prec_t prec, mpfr_t diam, noZeroTheo *theo) {
  node *funcSimplified, *derivSimplified;
  chain *temp;
  chain **noZeroProofs;

  funcSimplified = horner(func);
  derivSimplified = horner(deriv);

  if (theo != NULL) {
    theo->function = copyTree(func);
    theo->derivative = copyTree(deriv);
    theo->funcEqual = (equalityTheo *) safeMalloc(sizeof(equalityTheo));
    theo->funcEqual->expr1 = copyTree(func);
    theo->funcEqual->expr2 = copyTree(funcSimplified);
    theo->derivEqual = (equalityTheo *) safeMalloc(sizeof(equalityTheo));
    theo->derivEqual->expr1 = copyTree(deriv);
    theo->derivEqual->expr2 = copyTree(derivSimplified);
    noZeroProofs = &(theo->exprBoundTheos);
  } else {
    noZeroProofs = NULL;
  }

  temp = findZerosUnsimplified(funcSimplified,derivSimplified,range,prec,diam,noZeroProofs);
  
  free_memory(funcSimplified);
  free_memory(derivSimplified);

  return temp;
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


void fprintInterval(FILE *fd, mpfi_t interval) {
  mpfr_t l,r;
  mp_prec_t prec;

  
  prec = mpfi_get_prec(interval);
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfi_get_left(l,interval);
  mpfi_get_right(r,interval);
  fprintf(fd,"[");
  fprintValue(fd,l);
  fprintf(fd,";");
  fprintValue(fd,r);
  fprintf(fd,"]");

  mpfr_clear(l);
  mpfr_clear(r);
}


void freeMpfiPtr(void *i) {
  if (i == NULL) return;
  mpfi_clear(*((mpfi_t *) i));
  free(i);
}

chain *joinAdjacentIntervals(chain *intervals, mpfr_t diam) {
  chain *newChain, *curr;
  mpfi_t *tempI;
  mp_prec_t prec, p;
  mpfr_t newLeft, newRight, l,r, mpfr_temp;

  if (intervals == NULL) return NULL;
  if (intervals->next == NULL) {
    tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
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
  mpfr_init2(mpfr_temp,prec);

  newChain = NULL;
  curr = intervals->next;
  while (curr != NULL) {
    mpfi_get_left(l,*((mpfi_t *) (curr->value)));
    mpfi_get_right(r,*((mpfi_t *) (curr->value)));
    mpfr_sub(mpfr_temp,r,newLeft,GMP_RNDN);
    if ((mpfr_cmp(l,newRight) == 0) && (mpfr_cmp(mpfr_temp,diam) < 0)) {
      mpfr_set(newRight,r,GMP_RNDN);
    } else {
      tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
      mpfi_init2(*tempI,prec);
      mpfi_interv_fr(*tempI,newLeft,newRight);
      newChain = addElement(newChain,tempI);
      mpfr_set(newLeft,l,GMP_RNDN);
      mpfr_set(newRight,r,GMP_RNDN);
    }
    curr = curr->next;
  }
  tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
  mpfi_init2(*tempI,prec);
  mpfi_interv_fr(*tempI,newLeft,newRight);
  newChain = addElement(newChain,tempI);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(newLeft);
  mpfr_clear(newRight);
  mpfr_clear(mpfr_temp);
  return newChain;
}

chain *joinAdjacentIntervalsMaximally(chain *intervals) {
  chain *newChain, *curr;
  mpfi_t *tempI;
  mp_prec_t prec, p;
  mpfr_t newLeft, newRight, l,r, mpfr_temp;

  if (intervals == NULL) return NULL;
  if (intervals->next == NULL) {
    tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
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
  mpfr_init2(mpfr_temp,prec);

  newChain = NULL;
  curr = intervals->next;
  while (curr != NULL) {
    mpfi_get_left(l,*((mpfi_t *) (curr->value)));
    mpfi_get_right(r,*((mpfi_t *) (curr->value)));
    mpfr_sub(mpfr_temp,r,newLeft,GMP_RNDN);
    if (mpfr_cmp(l,newRight) == 0) {
      mpfr_set(newRight,r,GMP_RNDN);
    } else {
      tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
      mpfi_init2(*tempI,prec);
      mpfi_interv_fr(*tempI,newLeft,newRight);
      newChain = addElement(newChain,tempI);
      mpfr_set(newLeft,l,GMP_RNDN);
      mpfr_set(newRight,r,GMP_RNDN);
    }
    curr = curr->next;
  }
  tempI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
  mpfi_init2(*tempI,prec);
  mpfi_interv_fr(*tempI,newLeft,newRight);
  newChain = addElement(newChain,tempI);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(newLeft);
  mpfr_clear(newRight);
  mpfr_clear(mpfr_temp);
  return newChain;
}



chain *excludeIntervals(chain *mainIntervals, chain *excludeIntervals) {
  chain *curr, *previous, *curr2, *temp;
  mpfi_t *interval, *exclude;
  mp_prec_t prec, p;
  mpfr_t il, ir, el, er;

  if (mainIntervals == NULL) return NULL;
  if (excludeIntervals == NULL) return mainIntervals;

  prec = 1;
  curr = mainIntervals;
  while (curr != NULL) {
    p = mpfi_get_prec(*((mpfi_t *) curr->value));
    if (p > prec) prec = p;
    curr = curr->next;
  }
  curr = excludeIntervals;
  while (curr != NULL) {
    p = mpfi_get_prec(*((mpfi_t *) curr->value));
    if (p > prec) prec = p;
    curr = curr->next;
  }

  prec += 5;

  mpfr_init2(il,prec);
  mpfr_init2(ir,prec);
  mpfr_init2(el,prec);
  mpfr_init2(er,prec);

  curr2 = excludeIntervals;
  while (curr2 != NULL) {
    exclude = (mpfi_t *) (curr2->value);
    mpfi_revert_if_needed(*exclude);
    mpfi_get_left(el,*exclude);
    mpfi_get_right(er,*exclude);
    curr = mainIntervals;
    previous = NULL;
    while (curr != NULL) {
      interval = (mpfi_t *) (curr->value);
      mpfi_revert_if_needed(*interval);
      mpfi_get_left(il,*interval);
      mpfi_get_right(ir,*interval);
      if ((mpfr_cmp(el,ir) < 0) && (mpfr_cmp(il,er) < 0)) {
	if ((mpfr_cmp(il,el) < 0) && (mpfr_cmp(er,ir) < 0)) {
	  /* We must produce two intervals [il;el] and [er;ir] */
	  mpfi_interv_fr(*interval,il,el);
	  interval = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	  mpfi_init2(*interval,prec);
	  mpfi_interv_fr(*interval,er,ir);
	  temp = (chain *) safeMalloc(sizeof(chain));
	  temp->value = interval;
	  temp->next = curr->next;
	  curr->next = temp;
	} else {
	  if (mpfr_cmp(il,el) < 0) {
	    /* We must produce one interval [il;el] */
	    mpfi_interv_fr(*interval,il,el);
	  } else {
	    if (mpfr_cmp(er,ir) < 0) {
	      /* We must produce one interval [er;ir] */
	      mpfi_interv_fr(*interval,er,ir);
	    } else {
	      /* We must remove the interval completely */
	      if (previous != NULL) {
		/* We are not the first interval in the chain */
		previous->next = curr->next;
		mpfi_clear(*interval);
		free(interval);
		free(curr);
		curr = previous;
	      } else {
		/* We are the first interval in the chain */
		if (curr->next != NULL) {
		  /* We have a successor that will become the head of the chain */
		  mainIntervals = curr->next;
		  mpfi_clear(*interval);
		  free(interval);
		  free(curr);
		  curr = mainIntervals;
		} else {
		  /* We are the first and the last element in the chain, which will be empty */
		  
		  mpfi_clear(*interval);
		  free(interval);
		  free(curr);
		  mpfr_clear(il);
		  mpfr_clear(ir);
		  mpfr_clear(el);
		  mpfr_clear(er);
		  return NULL;
		}
	      }
	    }
	  }
	}
      }
      previous = curr;
      curr = curr->next;
    }
    curr2 = curr2->next;
  }

  mpfr_clear(il);
  mpfr_clear(ir);
  mpfr_clear(el);
  mpfr_clear(er);

  return mainIntervals;
}

void *copyMpfiPtr(void *ptr) {
  mpfi_t *newMpfi;

  newMpfi = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
  mpfi_init2(*newMpfi,mpfi_get_prec(*((mpfi_t *) ptr)));
  mpfi_set(*newMpfi,*((mpfi_t *) ptr));
  return (void *) newMpfi;
}


void infnormI(mpfi_t infnormval, node *func, node *deriv, 
	      node *numeratorDeriv, node *derivNumeratorDeriv,
	      mpfi_t range, mp_prec_t prec, mpfr_t diam, 
	      chain *intervalsToExclude,
	      chain **mightExcludes,
	      infnormTheo *theo) {
  chain *curr, *zeros, *tempChain, *tempChain2, *tempChain3;
  mpfi_t *currInterval;
  mpfi_t evalFuncOnInterval, lInterv, rInterv;
  mpfr_t innerLeft, innerRight, outerLeft, outerRight, l, r, tl, tr;
  mpfr_t diamJoin;
  mp_prec_t rangePrec;
  chain *excludes, *excludesTemp;
  int i; 
  noZeroTheo *noZeros;
  exprBoundTheo *evalLeftBound, *evalRightBound, *currZeroTheo;

  currZeroTheo = NULL;
  if (theo != NULL) {
    theo->function = copyTree(func);
    theo->derivative = copyTree(deriv);
    theo->numeratorOfDerivative = copyTree(numeratorDeriv);
    theo->derivativeOfNumeratorOfDerivative = copyTree(derivNumeratorDeriv);
    theo->excludedIntervals = copyChain(intervalsToExclude,copyMpfiPtr);
    noZeros = (noZeroTheo *) safeCalloc(1,sizeof(noZeroTheo));
    theo->noZeros = noZeros;
    evalLeftBound = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
    nullifyExprBoundTheo(evalLeftBound);
    evalRightBound = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
    nullifyExprBoundTheo(evalRightBound);
    theo->evalLeftBound = evalLeftBound;
    theo->evalRightBound = evalRightBound;
    theo->domain = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    theo->infnorm = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    theo->evalOnZeros = NULL;
    mpfi_init2(*(theo->domain),mpfi_get_prec(range));
    mpfi_init2(*(theo->infnorm),mpfi_get_prec(infnormval));
    mpfi_set(*(theo->domain),range);
  } else {
    noZeros = NULL;
    evalLeftBound = NULL;
    evalRightBound = NULL;
  }
  
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

  excludes = evaluateITaylor(evalFuncOnInterval, func, deriv, lInterv, prec, evalLeftBound); 
  mpfi_get_left(outerLeft,evalFuncOnInterval);
  mpfi_get_right(outerRight,evalFuncOnInterval);
  mpfr_set(innerLeft,outerRight,GMP_RNDU);
  mpfr_set(innerRight,outerLeft,GMP_RNDD);
  excludesTemp = evaluateITaylor(evalFuncOnInterval, func, deriv, rInterv, prec, evalRightBound); 
  excludes = concatChains(excludes,excludesTemp);
  mpfi_get_left(tl,evalFuncOnInterval);
  mpfi_get_right(tr,evalFuncOnInterval);
  mpfr_min(outerLeft,outerLeft,tl,GMP_RNDD);
  mpfr_max(outerRight,outerRight,tr,GMP_RNDU);
  mpfr_min(innerLeft,innerLeft,tr,GMP_RNDU);
  mpfr_max(innerRight,innerRight,tl,GMP_RNDD); 
 

  tempChain = findZeros(numeratorDeriv,derivNumeratorDeriv,range,prec,diam,noZeros); 
  mpfr_init2(diamJoin,prec);
  mpfr_mul_2ui(diamJoin,diam,3,GMP_RNDN);
  tempChain2 = joinAdjacentIntervals(tempChain,diamJoin);
  tempChain3 = copyChain(tempChain2,copyMpfiPtr);
  mpfr_mul_2ui(diamJoin,diamJoin,2,GMP_RNDN);
  zeros = joinAdjacentIntervals(tempChain3,diamJoin);
  mpfr_clear(diamJoin);

  zeros = excludeIntervals(zeros,intervalsToExclude);

  i = 0;
  for (curr=zeros;curr!=NULL;curr=curr->next) i++;
  printMessage(1,
	  "Information: %d interval(s) have (has) been found that possibly contain(s) the zeros of the derivative.\n",i);

  curr = zeros;
  while (curr != NULL) {
    if (theo != NULL) {
      currZeroTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      nullifyExprBoundTheo(currZeroTheo);
    } else {
      currZeroTheo = NULL;
    }
    currInterval = ((mpfi_t *) (curr->value));
    excludesTemp = evaluateITaylor(evalFuncOnInterval, func, deriv, *currInterval, prec, currZeroTheo); 
    excludes = concatChains(excludes,excludesTemp);
    mpfi_get_left(tl,evalFuncOnInterval);
    mpfi_get_right(tr,evalFuncOnInterval);

    if (theo != NULL) {
      theo->evalOnZeros = addElement(theo->evalOnZeros,currZeroTheo);
    }

    if (mpfr_nan_p(tl) || mpfr_nan_p(tr)) {
      printf("Warning: NaNs occured during the interval evaluation of the zeros of the derivative.\n");
    }

    mpfr_min(outerLeft,outerLeft,tl,GMP_RNDD);
    mpfr_max(outerRight,outerRight,tr,GMP_RNDU);
    mpfr_min(innerLeft,innerLeft,tr,GMP_RNDU); 
    mpfr_max(innerRight,innerRight,tl,GMP_RNDD); 
    curr = curr->next;
  }

  freeChain(zeros,freeMpfiPtr);
  freeChain(tempChain,freeMpfiPtr);
  freeChain(tempChain2,freeMpfiPtr);
  freeChain(tempChain3,freeMpfiPtr);

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

  *mightExcludes = excludes;

  if (theo != NULL) {
    mpfi_set(*(theo->infnorm),infnormval);
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


int isTrivialInfnormCase(rangetype result, node *func) {
  int isTrivial;
  node *simplifiedFunc, *numerator, *denominator;

  isTrivial = 0;
  simplifiedFunc = horner(func);

  if (simplifiedFunc->nodeType == CONSTANT) {
    mpfr_set(*(result.a),*(simplifiedFunc->value),GMP_RNDD);
    mpfr_set(*(result.b),*(simplifiedFunc->value),GMP_RNDU);
    isTrivial = 1;
  } else {
    if (simplifiedFunc->nodeType == SUB) {
      if (isSyntacticallyEqual(simplifiedFunc->child1,simplifiedFunc->child2)) {
	mpfr_set_d(*(result.a),0.0,GMP_RNDN);
	mpfr_set_d(*(result.b),0.0,GMP_RNDN);
	isTrivial = 1;
      }
    } else {
      if (getNumeratorDenominator(&numerator, &denominator, simplifiedFunc)) {
	if ((numerator->nodeType == CONSTANT) &&
	    mpfr_zero_p(*(numerator->value))) {
	  mpfr_set_d(*(result.a),0.0,GMP_RNDN);
	  mpfr_set_d(*(result.b),0.0,GMP_RNDN);
	  isTrivial = 1;
	} else {
	  if (isSyntacticallyEqual(numerator, denominator)) {
	    mpfr_set_d(*(result.a),1.0,GMP_RNDN);
	    mpfr_set_d(*(result.b),1.0,GMP_RNDN);
	    isTrivial = 1;
	  }
	}
	free_memory(denominator);
      } 
      free_memory(numerator);
    }
  }

  free_memory(simplifiedFunc);
  return isTrivial;
}


void uncertifiedInfnorm(mpfr_t result, node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec) {
  mpfr_t z, max, temp, x1, x2, y1, y2, step;
  node *deriv;
  node *derivsecond;
  int newtonWorked;

  mpfr_init2(x1, prec);
  mpfr_init2(x2, prec);
  mpfr_init2(step, prec);
  mpfr_init2(y1, prec);
  mpfr_init2(y2, prec);


  mpfr_sub(step, b, a, GMP_RNDN);
  mpfr_div_ui(step, step, points, GMP_RNDN);
 
  if (mpfr_sgn(step) == 0) {
    printf("Warning: the given interval is reduced to one point.\n");
    evaluate(y1,tree,a,prec);
    mpfr_abs(result,y1,GMP_RNDU);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(step);
    return;
  }

  if (mpfr_sgn(step) < 0) {
    printf("Error: the interval is empty.\n");
    mpfr_set_d(result,0.,GMP_RNDN);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(step);
    return;
  }

  if (evaluateConstantExpression(y1,tree,prec)) {
    printf("Warning: the expression is constant.\n");
    mpfr_abs(result,y1,GMP_RNDU);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(step);
    return;
  }
 
  mpfr_init2(z,prec);
  mpfr_init2(max,prec);
  mpfr_init2(temp,prec);

  deriv = differentiate(tree);
  derivsecond = differentiate(deriv);

  evaluate(temp, tree, a, prec);
  if (!mpfr_nan_p(temp)) {
    mpfr_abs(max, temp, GMP_RNDU);
  } else {
    printf("Warning: the evaluation of the given function in ");
    mpfr_set(z,a,GMP_RNDN);
    printValue(&z,prec);
    printf(" gives NaN.\n");
    printf("This point will be excluded from the infnorm result.\n");
    mpfr_set_d(max,0.0,GMP_RNDU);
  }
  evaluate(temp, tree, b, prec);
  if (!mpfr_nan_p(temp)) {
      mpfr_abs(temp, temp, GMP_RNDU);
      mpfr_max(max, max, temp, GMP_RNDU);
  } else {
    printf("Warning: the evaluation of the given function in ");
    mpfr_set(z,b,GMP_RNDN);
    printValue(&z,prec);
    printf(" gives NaN\n");
    printf("This point will be excluded from the infnorm result.\n");
  }

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,x1,step,GMP_RNDU);
  if (mpfr_cmp(x2,b)>0) mpfr_set(x2,b,GMP_RNDN);
  evaluate(y1,deriv,x1,prec);
  evaluate(y2,deriv,x2,prec);
  while(mpfr_less_p(x1,b)) {
    if (mpfr_sgn(y1) != mpfr_sgn(y2)) {
      newtonWorked = newtonMPFR(z, deriv, derivsecond, x1, x2, prec);
      if (!newtonWorked) {
	printf("Warning: zero-search by Newton's method did not converge on the interval\n[");
	printValue(&x1,prec);
	printf(";");
	printValue(&x2,prec);
	printf("]\nThis (possibly maximul) point will be excluded from the infnorm result.\n");
      } else {
	if (!(mpfr_number_p(z))) {
	  printf("Warning: zero-search by Newton's method produces infinity or NaN\n");
	  printf("Will replace the zero point of the derivative by the mid-point of\nthe considered interval [");
	  printValue(&x1,prec);
	  printf(";");
	  printValue(&x2,prec);
	  printf("]\n");
	  mpfr_add(z,x1,x2,GMP_RNDN);
	  mpfr_div_ui(z,z,2,GMP_RNDN);
	}
	evaluate(temp,tree,z,prec);
	if (!mpfr_nan_p(temp)) {
	  mpfr_abs(temp, temp, GMP_RNDU);
	  mpfr_max(max, max, temp, GMP_RNDU);
	} else {
	  printf("Warning: the evaluation of the given function in ");
	  printValue(&z,prec);
	  printf(" gives NaN.\n");
	  printf("This (possibly maximum) point will be excluded from the infnorm result.\n");
	}
      }
    }
    mpfr_set(x1,x2,GMP_RNDN);
    mpfr_set(y1,y2,GMP_RNDN);
    mpfr_add(x2,x1,step, GMP_RNDU);
    if (mpfr_cmp(x2,b)>0) mpfr_set(x2,b,GMP_RNDN);
    evaluate(y2,deriv,x2,prec);
  }

  mpfr_set(result,max,GMP_RNDU);

  free_memory(deriv);
  free_memory(derivsecond);
  mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(step);
  mpfr_clear(z); mpfr_clear(max); mpfr_clear(temp); 
  return;
}




rangetype infnorm(node *func, rangetype range, chain *excludes, 
		  mp_prec_t prec, mpfr_t diam, FILE *proof) {
  rangetype res;
  mpfi_t rangeI, resI;
  mpfi_t *excludeI;
  node *deriv, *numeratorDeriv, *derivNumeratorDeriv, *denominatorDeriv, *derivDenominatorDeriv;
  mpfr_t rangeDiameter, z, ya,yb;
  chain *mightExcludes, *curr, *secondMightExcludes, *initialExcludes;
  int newtonWorked;
  mp_prec_t p, p2;
  infnormTheo *theo;


  res.a = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  res.b = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(res.a),prec);
  mpfr_init2(*(res.b),prec);

  if (isTrivialInfnormCase(res, func)) {
    if (proof != NULL) {
      printf("Warning: the infnorm on the given function is trivially calculable.\n");
      printf("No proof will be generated.\n");
    }
    return res;
  }

  curr = excludes;
  initialExcludes = NULL;
  while (curr != NULL) {
    excludeI = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    p = mpfr_get_prec(*(((rangetype *) curr->value)->a));
    p2 = mpfr_get_prec(*(((rangetype *) curr->value)->b));
    if (p2 > p) p = p2;
    if (prec > p) p = prec;
    mpfi_init2(*excludeI,p);
    mpfi_interv_fr(*excludeI,*(((rangetype *) curr->value)->a),*(((rangetype *) curr->value)->b));
    initialExcludes = addElement(initialExcludes,(void *) excludeI);
    curr = curr->next;
  }

  mpfi_init2(rangeI,prec);
  mpfi_init2(resI,prec);
  mpfr_init2(rangeDiameter,prec);
  mpfr_sub(rangeDiameter,*(range.b),*(range.a),GMP_RNDD);
  mpfr_mul(rangeDiameter,rangeDiameter,diam,GMP_RNDD);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));
  deriv = differentiate(func);
  if (getNumeratorDenominator(&numeratorDeriv,&denominatorDeriv,deriv)) {
    printf("Warning: the derivative of the function is a quotient, thus possibly not continuous in the interval.\n");
    printf("Only the zeros of the numerator will be searched and pole detection may fail.\n");
    printf("Be sure that the function is twice continuously differentiable if trusting the infnorm result.\n");

    mpfr_init2(z,prec);
    mpfr_init2(ya,prec);
    mpfr_init2(yb,prec);
    derivDenominatorDeriv = differentiate(denominatorDeriv);

    newtonWorked = newtonMPFR(z, denominatorDeriv, derivDenominatorDeriv, *(range.a), *(range.b), prec);

    if (newtonWorked && mpfr_number_p(z)) {
      evaluate(ya,numeratorDeriv,z,prec);
      evaluate(yb,denominatorDeriv,z,prec);

      mpfr_abs(ya,ya,GMP_RNDN);
      mpfr_abs(yb,yb,GMP_RNDN);

      mpfr_mul_ui(yb,yb,2,GMP_RNDN);

      if (mpfr_cmp(ya,yb) <= 0) {
	printf("Warning: the derivative of the function seems to have a extensible singularity in ");
	printValue(&z,prec);
	printf(".\n");
	printf("The infnorm result might not be trustful if the derivative cannot actually\n");
	printf("be extended in this point.\n");
      } else {
	printf("Warning: the derivative of the function seems to have a singularity in ");
	printValue(&z,prec);
	printf(".\n");
	printf("The infnorm result is likely to be wrong.\n");
      }
    } else {
      evaluate(ya,denominatorDeriv,*(range.a),prec);
      evaluate(yb,denominatorDeriv,*(range.b),prec);

      if (mpfr_sgn(ya) != mpfr_sgn(yb)) {
	printf("Warning: the derivative of the function seems to have a (extensible) singularity in the considered interval.\n");
	printf("The infnorm result might be not trustful if the function is not continuously differentiable.\n");
      } else {
	printMessage(1,"Information: the derivative seems to have no (false) pole in the considered interval.\n");
      }
    }

    mpfr_clear(z);
    mpfr_clear(ya);
    mpfr_clear(yb);
    free_memory(derivDenominatorDeriv);
    free_memory(denominatorDeriv);
  }
  derivNumeratorDeriv = differentiate(numeratorDeriv);
  mightExcludes = NULL;

  if (proof != NULL) {
    theo = (infnormTheo *) safeCalloc(1,sizeof(infnormTheo));
  } else {
    theo = NULL;
  }

  infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,
	   prec,rangeDiameter,initialExcludes,&mightExcludes,theo);

  secondMightExcludes = NULL;

  if (mightExcludes != NULL) {
    printf("Warning: to get better infnorm quality, the following domains will be excluded additionally:\n");
    curr = mightExcludes;
    while(curr != NULL) {
      printInterval(*((mpfi_t *) (curr->value)));
      printf("\n");
      curr = curr->next;
    }
    printf("\n");
    mightExcludes = concatChains(mightExcludes,initialExcludes);

    if (theo != NULL) freeInfnormTheo(theo);
    if (proof != NULL) {
      theo = (infnormTheo *) safeCalloc(1,sizeof(infnormTheo));
    } else {
      theo = NULL;
    }

    infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,
	     2*prec,rangeDiameter,mightExcludes,&secondMightExcludes,theo);

    if (secondMightExcludes != NULL) {
      printf("Warning: the following domains remain the exclusion of which could improve the result.\n");
      curr = secondMightExcludes;
      while(curr != NULL) {
	printInterval(*((mpfi_t *) (curr->value)));
	printf("\n");
	curr = curr->next;
      }
      printf("\n");
    }
  }

  if (proof != NULL) {
    printMessage(1,"Information: started writing the proof.\n");
    fprintInfnormTheo(proof,theo,1);
    printMessage(1,"Information: proof written.\n");
  }
  
  if (theo != NULL) freeInfnormTheo(theo);
  freeChain(mightExcludes,freeMpfiPtr);
  freeChain(secondMightExcludes,freeMpfiPtr);
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


void evaluateRangeFunctionFast(rangetype yrange, node *func, node *deriv, rangetype xrange, mp_prec_t prec) {
  mpfi_t x, y;
  chain *tempChain;

  mpfi_init2(x,prec);
  mpfi_init2(y,prec);
  mpfi_interv_fr(x,*(xrange.a),*(xrange.b));

  tempChain = evaluateITaylor(y, func, deriv, x, prec, NULL);

  mpfi_get_left(*(yrange.a),y);
  mpfi_get_right(*(yrange.b),y);

  freeChain(tempChain,freeMpfiPtr);
  mpfi_clear(x);
  mpfi_clear(y);
}

void evaluateRangeFunction(rangetype yrange, node *func, rangetype xrange, mp_prec_t prec) {
  node *deriv;

  deriv = differentiate(func);
  evaluateRangeFunctionFast(yrange,func,deriv,xrange,prec);
  free_memory(deriv);
}



chain* findZerosFunction(node *func, rangetype range, mp_prec_t prec, mpfr_t diam) {
  mpfi_t rangeI;
  node *deriv, *numerator, *denominator;
  mpfr_t rangeDiameter, diamJoin;
  chain *zerosI, *zeros, *curr;
  rangetype *tempRange;
  chain *tempChain, *tempChain2, *tempChain3;

  mpfi_init2(rangeI,prec);
  mpfr_init2(rangeDiameter,prec);
  mpfr_sub(rangeDiameter,*(range.b),*(range.a),GMP_RNDD);
  mpfr_mul(rangeDiameter,rangeDiameter,diam,GMP_RNDD);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));

  if (getNumeratorDenominator(&numerator,&denominator,func)) free_memory(denominator);

  deriv = differentiate(numerator);

  tempChain = findZeros(numerator,deriv,rangeI,prec,rangeDiameter,NULL);
  mpfr_init2(diamJoin,prec);
  mpfr_mul_2ui(diamJoin,diam,3,GMP_RNDN);
  tempChain2 = joinAdjacentIntervals(tempChain,diamJoin);
  tempChain3 = copyChain(tempChain2,copyMpfiPtr);
  mpfr_mul_2ui(diamJoin,diamJoin,2,GMP_RNDN);
  zerosI = joinAdjacentIntervals(tempChain3,diamJoin);
  mpfr_clear(diamJoin);

  zeros = NULL;
  curr = zerosI;
  while (curr != NULL) {
    tempRange = (rangetype *) safeMalloc(sizeof(rangetype));
    tempRange->a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    tempRange->b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(tempRange->a),prec);
    mpfr_init2(*(tempRange->b),prec);
    mpfi_get_left(*(tempRange->a),*((mpfi_t *) (curr->value)));
    mpfi_get_right(*(tempRange->b),*((mpfi_t *) (curr->value)));
    zeros = addElement(zeros,tempRange);
    curr = curr->next;
  }

  freeChain(zerosI,freeMpfiPtr);
  freeChain(tempChain,freeMpfiPtr);
  freeChain(tempChain2,freeMpfiPtr);
  freeChain(tempChain3,freeMpfiPtr);
  free_memory(numerator);
  free_memory(deriv);
  mpfi_clear(rangeI);
  mpfr_clear(rangeDiameter);
  return zeros;
}
