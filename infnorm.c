/*

Copyright 2007 by 

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
it offers a certified infinite norm, an automatic polynomial
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
#include "expression.h"
#include "infnorm.h"
#include "chain.h"
#include "double.h"
#include "general.h"
#include "proof.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

#define DEBUG 0
#define DEBUGMPFI 0
#define DIFFSIZE 5000000


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

void mpfi_round_to_doubleextended(mpfi_t rop, mpfi_t op) {
  mpfr_t l,r, lres, rres;
  mp_prec_t prec;

  prec = mpfi_get_prec(op) + 10;
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfr_init2(lres,prec);
  mpfr_init2(rres,prec);

  mpfi_get_left(l,op);
  mpfi_get_right(r,op);

  mpfr_round_to_doubleextended(lres,l);
  mpfr_round_to_doubleextended(rres,r);

  mpfi_interv_fr(rop,lres,rres);

  mpfr_clear(l);
  mpfr_clear(r);
  mpfr_clear(lres);
  mpfr_clear(rres);
}


void mpfi_erf(mpfi_t rop, mpfi_t op) {
  mpfr_t opl, opr, ropl, ropr;

  mpfr_init2(opl,mpfi_get_prec(op));
  mpfr_init2(opr,mpfi_get_prec(op));

  mpfr_init2(ropl,mpfi_get_prec(rop));
  mpfr_init2(ropr,mpfi_get_prec(rop));
  
  mpfi_get_left(opl,op);
  mpfi_get_right(opr,op);
  
  mpfr_erf(ropl,opl,GMP_RNDD);
  mpfr_erf(ropr,opr,GMP_RNDU);

  mpfi_interv_fr(rop,ropl,ropr);
  mpfi_revert_if_needed(rop);

  mpfr_clear(opl);
  mpfr_clear(opr);
  mpfr_clear(ropl);
  mpfr_clear(ropr);
}

void mpfi_erfc(mpfi_t rop, mpfi_t op) {
  mpfr_t opl, opr, ropl, ropr;

  mpfr_init2(opl,mpfi_get_prec(op));
  mpfr_init2(opr,mpfi_get_prec(op));

  mpfr_init2(ropl,mpfi_get_prec(rop));
  mpfr_init2(ropr,mpfi_get_prec(rop));
  
  mpfi_get_left(opl,op);
  mpfi_get_right(opr,op);
  
  mpfr_erfc(ropl,opr,GMP_RNDD);
  mpfr_erfc(ropr,opl,GMP_RNDU);

  mpfi_interv_fr(rop,ropl,ropr);
  mpfi_revert_if_needed(rop);

  mpfr_clear(opl);
  mpfr_clear(opr);
  mpfr_clear(ropl);
  mpfr_clear(ropr);
}

void mpfi_ceil(mpfi_t rop, mpfi_t op) {
  mpfr_t opl, opr, ropl, ropr;

  mpfr_init2(opl,mpfi_get_prec(op));
  mpfr_init2(opr,mpfi_get_prec(op));

  mpfr_init2(ropl,mpfi_get_prec(op));
  mpfr_init2(ropr,mpfi_get_prec(op));
  
  mpfi_get_left(opl,op);
  mpfi_get_right(opr,op);
  
  mpfr_ceil(ropl,opr);
  mpfr_ceil(ropr,opl);

  mpfi_interv_fr(rop,ropl,ropr);
  mpfi_revert_if_needed(rop);

  mpfr_clear(opl);
  mpfr_clear(opr);
  mpfr_clear(ropl);
  mpfr_clear(ropr);
}

void mpfi_floor(mpfi_t rop, mpfi_t op) {
  mpfr_t opl, opr, ropl, ropr;

  mpfr_init2(opl,mpfi_get_prec(op));
  mpfr_init2(opr,mpfi_get_prec(op));

  mpfr_init2(ropl,mpfi_get_prec(op));
  mpfr_init2(ropr,mpfi_get_prec(op));
  
  mpfi_get_left(opl,op);
  mpfi_get_right(opr,op);
  
  mpfr_floor(ropl,opr);
  mpfr_floor(ropr,opl);

  mpfi_interv_fr(rop,ropl,ropr);
  mpfi_revert_if_needed(rop);

  mpfr_clear(opl);
  mpfr_clear(opr);
  mpfr_clear(ropl);
  mpfr_clear(ropr);
}


int newtonMPFRWithStartPoint(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mpfr_t start, mp_prec_t prec) {
  mpfr_t x, x2, temp1, temp2, am, bm;
  unsigned long int n=1;
  int okay, lucky, hasZero, i, freeTrees;
  node *myTree, *myDiffTree;

  freeTrees = 0;
  if (tree->nodeType == DIV) {
    freeTrees = 1;
    myTree = copyTree(tree->child1);
    myDiffTree = differentiate(myTree);
  } else {
    myTree = tree;
    myDiffTree = diff_tree;
  }

  mpfr_init2(x,prec);
  mpfr_init2(x2,prec);
  mpfr_init2(temp1,prec);
  mpfr_init2(temp2,prec);
  mpfr_init2(am,prec/2);
  mpfr_init2(bm,prec/2);
  mpfr_set(am,a,GMP_RNDN);
  mpfr_nextbelow(am);
  mpfr_nextbelow(am);
  mpfr_set(bm,b,GMP_RNDN);
  mpfr_nextabove(am);
  mpfr_nextabove(bm);

  okay = 0;

  if (mpfr_sgn(a) != mpfr_sgn(b)) {
    mpfr_set_d(x,0.0,GMP_RNDN);
    evaluate(temp1, myTree, x, prec);
    if (mpfr_zero_p(temp1)) {
      mpfr_set(res,x,GMP_RNDN);
      okay = 1;
    }
  }

  if (!okay) {
    evaluate(temp1, myTree, a, prec);
    if (mpfr_zero_p(temp1)) {
      mpfr_set(res,a,GMP_RNDN);
      okay = 1;
    } else {
      evaluate(temp2, myTree, b, prec);
      if (mpfr_zero_p(temp2)) {
	mpfr_set(res,b,GMP_RNDN);
	okay = 1;
      } else {
	
	mpfr_mul(temp1,temp1,temp2,GMP_RNDN);
	hasZero = (mpfr_sgn(temp1) <= 0);

	mpfr_set(x,start,GMP_RNDN);
	lucky = 0;
	
	i = 5000;
	while((n<=prec+25) && (mpfr_cmp(am,x) <= 0) && (mpfr_cmp(x,bm) <= 0) && (i > 0)) {
	  evaluate(temp1, myTree, x, prec);
	  if (mpfr_zero_p(temp1)) {
	    lucky = 1;
	    break;
	  }
	  evaluate(temp2, myDiffTree, x, prec);
	  mpfr_div(temp1, temp1, temp2, GMP_RNDN);
	  mpfr_sub(x2, x, temp1, GMP_RNDN);
	  if (mpfr_cmp(x2,x) == 0) break;
	  if (mpfr_zero_p(x) || mpfr_zero_p(x2)) {
	    n *= 2;
	  } else {
	    if (mpfr_get_exp(x) == mpfr_get_exp(x2)) {
	      n *= 2;
	    } else {
	      i--;
	    }
	  }
	  mpfr_set(x,x2,GMP_RNDN);
	}
	
	if (mpfr_cmp(x,a) < 0) {
	  mpfr_set(res,a,GMP_RNDN);
	  if (hasZero) {
	    okay = 1;
	  } else {
	    evaluate(temp1, myTree, x, prec);
	    evaluate(temp2, myDiffTree, x, prec);
	    mpfr_div(temp1, temp1, temp2, GMP_RNDN);
	    mpfr_sub(x, x, temp1, GMP_RNDN);
	    if (mpfr_cmp(x,a) >= 0) {
	      okay = 1;
	    } else {
	      okay = 0;
	    }
	  }
	} else {
	  if (mpfr_cmp(b,x) < 0) {
	    mpfr_set(res,b,GMP_RNDN);
	    if (hasZero) {
	      okay = 1;
	    } else {
	      evaluate(temp1, myTree, x, prec);
	      evaluate(temp2, myDiffTree, x, prec);
	      mpfr_div(temp1, temp1, temp2, GMP_RNDN);
	      mpfr_sub(x, x, temp1, GMP_RNDN);
	      if (mpfr_cmp(b,x) >= 0) {
		okay = 1;
	      } else {
		okay = 0;
	      }
	    }
	  } else {
	    mpfr_set(res,x,GMP_RNDN);
	    if (!lucky) {
	      evaluate(temp1, myTree, x, prec);
	      evaluate(temp2, myDiffTree, x, prec);
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
  }

  if (freeTrees) {
    free_memory(myTree);
    free_memory(myDiffTree);
  }

  mpfr_clear(x); mpfr_clear(temp1); mpfr_clear(temp2); mpfr_clear(x2); mpfr_clear(am); mpfr_clear(bm);
  return okay;
}



int newtonMPFR(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  mpfr_t start;
  int result;

  mpfr_init2(start,prec);
  mpfr_add(start,a,b,GMP_RNDN);
  mpfr_div_2ui(start,start,1,GMP_RNDN);

  result = newtonMPFRWithStartPoint(res, tree, diff_tree, a, b, start, prec);

  mpfr_clear(start);

  return result;
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



chain* evaluateI(mpfi_t result, node *tree, mpfi_t x, mp_prec_t prec, int simplifiesA, int simplifiesB, mpfr_t *hopitalPoint, exprBoundTheo *theo) {
  mpfi_t stack1, stack2;
  mpfi_t stack3, zI, numeratorInZI, denominatorInZI, newExcludeTemp, xMXZ, temp1, temp2, tempA, tempB;
  mpfi_t *newExclude;
  mpfi_t leftConstantTerm, rightConstantTerm;
  mpfi_t leftLinearTerm, rightLinearTerm;
  mpfr_t al, ar, bl, br, xl, xr, z, z2;
  mpfr_t *newHopitalPoint;
  node *derivNumerator, *derivDenominator, *tempNode;
  node *derivLeft, *derivRight;
  chain *leftExcludes, *rightExcludes, *excludes, *t1, *t2;
  chain *leftExcludesConstant, *rightExcludesConstant;
  chain *leftExcludesLinear, *rightExcludesLinear;
  exprBoundTheo *leftTheo, *rightTheo, *internalTheo; 
  exprBoundTheo *leftTheoConstant, *rightTheoConstant, *leftTheoLinear, *rightTheoLinear;
  int isPolynom;
  int xIsPoint;

  excludes = NULL;

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

  mpfi_diam_abs(al,x);

  if (mpfr_zero_p(al)) xIsPoint = 1; else xIsPoint = 0;

  if (xIsPoint) printMessage(12,"Information: while evaluating no decorrelation test will be performed because the ordinate interval is point.\n");

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
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifiesA, simplifiesB, NULL, rightTheo);
    mpfi_add(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    if ((simplifiesA > 0) && (mpfi_has_zero(stack3)) && (!mpfi_has_zero(stack1)) && (!mpfi_has_zero(stack2)) && !xIsPoint) {

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
      mpfi_init2(tempA,prec);
      mpfi_init2(tempB,prec);

      mpfi_mid(z,x);
      mpfi_set_fr(zI,z);

      leftExcludesConstant = evaluateI(leftConstantTerm, tree->child1, zI, prec, simplifiesA-1, simplifiesB, NULL, leftTheoConstant);
      rightExcludesConstant = evaluateI(rightConstantTerm, tree->child2, zI, prec, simplifiesA-1, simplifiesB, NULL, rightTheoConstant);

      printMessage(12,"Information: Differentiating while evaluating for decorrelation.\n");

      derivLeft = differentiate(tree->child1);
      derivRight = differentiate(tree->child2);

      leftExcludesLinear = evaluateI(leftLinearTerm, derivLeft, x, prec, simplifiesA-1, simplifiesB, NULL, leftTheoLinear);
      rightExcludesLinear = evaluateI(rightLinearTerm, derivRight, x, prec, simplifiesA-1, simplifiesB, NULL, rightTheoLinear);

      mpfi_add(tempA,leftConstantTerm,rightConstantTerm);
      mpfi_add(tempB,leftLinearTerm,rightLinearTerm);

      mpfi_sub(xMXZ,x,zI);

      mpfi_mul(temp2,xMXZ,tempB);
      mpfi_add(temp1,tempA,temp2);

      mpfi_get_left(al,temp1);
      mpfi_get_right(ar,temp1);

      if (mpfr_number_p(al) && mpfr_number_p(ar)) {

	printMessage(8,"Information: decorrelating an interval addition.\n");
	if (verbosity >= 12) {
	  printf("Decorrelating on function\n");
	  printTree(tree);
	  printf("\nconstant term:\n");
	  printInterval(tempA);
	  printf("\nlinear term:\n");
	  printInterval(tempB);
	  printf("\ntranslated interval:\n");
	  printInterval(xMXZ);
	  printf("\nTaylor evaluation:\n");
	  printInterval(temp1);
	  printf("\ndirect evaluation:\n");
	  printInterval(stack3);
	  printf("\n");
	}

	mpfi_intersect(stack3,stack3,temp1);
	excludes = concatChains(leftExcludes,rightExcludes);
	excludes = concatChains(excludes,leftExcludesConstant);
	excludes = concatChains(excludes,rightExcludesConstant);	
	excludes = concatChains(excludes,leftExcludesLinear);
	excludes = concatChains(excludes,rightExcludesLinear);


	if (internalTheo != NULL) {
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
	}
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
      mpfi_clear(tempA);
      mpfi_clear(tempB);
      mpfi_clear(leftConstantTerm);
      mpfi_clear(rightConstantTerm);
      mpfi_clear(leftLinearTerm);
      mpfi_clear(rightLinearTerm);
    } else {
      excludes = concatChains(leftExcludes,rightExcludes);
    }
    break;
  case SUB:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifiesA, simplifiesB, NULL, rightTheo);
    mpfi_sub(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    if ((simplifiesA > 0) && (mpfi_has_zero(stack3)) && (!mpfi_has_zero(stack1)) && (!mpfi_has_zero(stack2)) && !xIsPoint) {

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
      mpfi_init2(tempA,prec);
      mpfi_init2(tempB,prec);


      mpfi_mid(z,x);
      mpfi_set_fr(zI,z);

      leftExcludesConstant = evaluateI(leftConstantTerm, tree->child1, zI, prec, simplifiesA-1, simplifiesB, NULL, leftTheoConstant);
      rightExcludesConstant = evaluateI(rightConstantTerm, tree->child2, zI, prec, simplifiesA-1, simplifiesB, NULL, rightTheoConstant);

      printMessage(12,"Information: Differentiating while evaluating for decorrelation.\n");

      derivLeft = differentiate(tree->child1);
      derivRight = differentiate(tree->child2);

      leftExcludesLinear = evaluateI(leftLinearTerm, derivLeft, x, prec, simplifiesA-1, simplifiesB, NULL, leftTheoLinear);
      rightExcludesLinear = evaluateI(rightLinearTerm, derivRight, x, prec, simplifiesA-1, simplifiesB, NULL, rightTheoLinear);

      mpfi_sub(tempA,leftConstantTerm,rightConstantTerm);
      mpfi_sub(tempB,leftLinearTerm,rightLinearTerm);

      mpfi_sub(xMXZ,x,zI);

      mpfi_mul(temp2,xMXZ,tempB);
      mpfi_add(temp1,tempA,temp2);

      mpfi_get_left(al,temp1);
      mpfi_get_right(ar,temp1);

      if (mpfr_number_p(al) && mpfr_number_p(ar)) {

	printMessage(8,"Information: decorrelating an interval substraction.\n");
	if (verbosity >= 12) {
	  printf("Decorrelating on function\n");
	  printTree(tree);
	  printf("\nconstant term:\n");
	  printInterval(tempA);
	  printf("\nlinear term:\n");
	  printInterval(tempB);
	  printf("\ntranslated interval:\n");
	  printInterval(xMXZ);
	  printf("\nTaylor evaluation:\n");
	  printInterval(temp1);
	  printf("\ndirect evaluation:\n");
	  printInterval(stack3);
	  printf("\n");
	}

	mpfi_intersect(stack3,stack3,temp1);
	excludes = concatChains(leftExcludes,rightExcludes);
	excludes = concatChains(excludes,leftExcludesConstant);
	excludes = concatChains(excludes,rightExcludesConstant);	
	excludes = concatChains(excludes,leftExcludesLinear);
	excludes = concatChains(excludes,rightExcludesLinear);

	if (internalTheo != NULL) {
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
	}
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
      mpfi_clear(tempA);
      mpfi_clear(tempB);
      mpfi_clear(leftConstantTerm);
      mpfi_clear(rightConstantTerm);
      mpfi_clear(leftLinearTerm);
      mpfi_clear(rightLinearTerm);
    } else {
      excludes = concatChains(leftExcludes,rightExcludes);
    }
    break;
  case MUL:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifiesA, simplifiesB, NULL, rightTheo);
    mpfi_mul(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    excludes = concatChains(leftExcludes,rightExcludes);
    break;
  case DIV:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifiesA, simplifiesB, NULL, rightTheo);

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
	  mpfr_zero_p(br) &&
	  (simplifiesB > 0)) {
	/* [0;0] / [0;0] */

	printMessage(12,"Information: Differentiating while evaluating for Hopital's rule.\n");
	derivNumerator = differentiate(tree->child1);
	derivDenominator = differentiate(tree->child2);
	
	freeChain(leftExcludes,freeMpfiPtr);
	freeChain(rightExcludes,freeMpfiPtr);

	printMessage(8,"Information: using Hopital's rule on point division.\n");
	if (verbosity >= 9) {
	  printf("Information: entering interval was \n");
	  printInterval(x);
	  printf("\n");

	}

	if (verbosity >= 12) {
	  printf("Hopital's rule is used on function\n");
	  printTree(tree);
	  printf("\n");
	}

	if (verbosity >= 15) {
	  printf("The derivative of the numerator is\n");
	  printTree(derivNumerator);
	  printf("\n");
	  printf("The derivative of the denominator is\n");
	  printTree(derivDenominator);
	  printf("\n");
	}

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

	leftExcludes = evaluateI(stack1, derivNumerator, x, prec, simplifiesA, simplifiesB-1, NULL, leftTheoLinear);
	rightExcludes = evaluateI(stack2, derivDenominator, x, prec, simplifiesA, simplifiesB-1, NULL, rightTheoLinear);
	
	free_memory(derivNumerator);
	free_memory(derivDenominator);
	mpfi_div(stack3, stack1, stack2);
	excludes = concatChains(leftExcludes,rightExcludes);
      } else {
	/* [0;0] / [bl;br], bl,br != 0 */
	freeChain(rightExcludes,freeMpfiPtr);

	printMessage(8,"Information: simplifying an interval division with 0 point numerator.\n");
	if (verbosity >= 12) {
	  printf("Simplification on function\n");
	  printTree(tree);
	  printf("\n");
	}


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
	  (simplifiesB > 0)) {
	mpfr_init2(xl,prec);
	mpfr_init2(xr,prec);

	mpfi_get_left(xl,x);
	mpfi_get_right(xr,x);

	if (mpfr_cmp(xl,xr) != 0) {
	  
	  printMessage(12,"Information: Differentiating while evaluating for Hopital's rule.\n");
	  derivDenominator = differentiate(tree->child2);
	  
	  if ((simplifiesB == (hopitalrecursions + 1)) || (hopitalPoint == NULL)){
	    mpfr_init2(z,prec);
	    newtonMPFR(z,tree->child2,derivDenominator,xl,xr,prec);
	    newHopitalPoint = &z;
	  } else {
	    mpfr_init2(z,mpfr_get_prec(*hopitalPoint));
	    mpfr_set(z,*hopitalPoint,GMP_RNDN);
	    newHopitalPoint = hopitalPoint;
	  }
	  
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

	    t1 = evaluateI(numeratorInZI, tree->child1, zI, prec, simplifiesA, simplifiesB-1, newHopitalPoint, leftTheoConstant);
	    t2 = evaluateI(denominatorInZI, tree->child2, zI, prec, simplifiesA, simplifiesB-1, newHopitalPoint, rightTheoConstant);
	  
	    freeChain(t1,freeMpfiPtr);
	    freeChain(t2,freeMpfiPtr);

	    mpfi_get_left(al,numeratorInZI);
	    mpfi_get_right(ar,numeratorInZI);
	    mpfi_get_left(bl,denominatorInZI);
	    mpfi_get_right(br,denominatorInZI);
	    
	    if (mpfr_zero_p(al) && mpfr_zero_p(ar) && mpfr_zero_p(bl) && mpfr_zero_p(br)) {
	      /* Hopital's rule can be applied */

	      printMessage(12,"Information: Differentiating while evaluating for Hopital's rule.\n");
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

	      if (simplifiesB == (hopitalrecursions + 1)) {
		printMessage(8,"Information: using Hopital's rule (general case) on denominator zero.\n");
		if (verbosity >= 10) {
		  printf("Hopital's rule is used on function\n");
		  printTree(tree);
		  printf(" in point ");
		  printMpfr(z);
		}
	      }

	      if (simplifiesB != (hopitalrecursions + 1)) {
		printMessage(8,"Information: recursion on use of Hopital's rule\n");
		if (verbosity >= 10) {
		  printf("Reused Hopital's rule point is ");
		  printMpfr(*hopitalPoint);
		}
	      }

	      if (verbosity >= 15) {
		printf("Information in Hopital: The simplified function is\n");
		printTree(tempNode);
		printf("\n");
	      }
	      
	      excludes = evaluateI(stack3, tempNode, x, prec, simplifiesA, simplifiesB-1, newHopitalPoint, leftTheoLinear);
	      
	      if (internalTheo != NULL) mpfi_set(*(internalTheo->boundLeftLinear),stack3);
	      
	      free_memory(tempNode);
	    } else {
	      if (internalTheo != NULL) {
		freeExprBoundTheo(leftTheoConstant);
		freeExprBoundTheo(rightTheoConstant);
	      }
  
	      printMessage(12,"Information: Differentiating while evaluating for Hopital's rule.\n");
	      derivNumerator = differentiate(tree->child1);

	      if ((simplifiesB == (hopitalrecursions + 1)) || (hopitalPoint == NULL)) {
		mpfr_init2(z2,prec);
		newtonMPFR(z2,tree->child1,derivNumerator,xl,xr,prec);
		newHopitalPoint = &z2;
	      } else {
		mpfr_init2(z2,mpfr_get_prec(*hopitalPoint));
		mpfr_set(z2,*hopitalPoint,GMP_RNDN);
		newHopitalPoint = hopitalPoint;
	      }

	      if (mpfr_number_p(z2)) {
		mpfi_set_fr(zI,z2);

		if (internalTheo != NULL) {
		  leftTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		  rightTheoConstant = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
		} else {
		  leftTheoConstant = NULL;
		  rightTheoConstant = NULL;
		}
	    
		t1 = evaluateI(numeratorInZI, tree->child1, zI, prec, simplifiesA, simplifiesB-1, newHopitalPoint, leftTheoConstant);
		t2 = evaluateI(denominatorInZI, tree->child2, zI, prec, simplifiesA, simplifiesB-1, newHopitalPoint, rightTheoConstant);

		freeChain(t1,freeMpfiPtr);
		freeChain(t2,freeMpfiPtr);

		mpfi_get_left(al,numeratorInZI);
		mpfi_get_right(ar,numeratorInZI);
		mpfi_get_left(bl,denominatorInZI);
		mpfi_get_right(br,denominatorInZI);
		
		if (mpfr_zero_p(al) && mpfr_zero_p(ar) && mpfr_zero_p(bl) && mpfr_zero_p(br)) {

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

		  if (simplifiesB == (hopitalrecursions + 1)) {
		    printMessage(8,"Information: using Hopital's rule (general case) on numerator zero.\n");
		    if (verbosity >= 10) {
		      printf("Hopital's rule is used on function\n");
		      printTree(tree);
		      printf(" in point ");
		      printMpfr(z);
		    }
		  }

		  if (simplifiesB != (hopitalrecursions + 1)) {
		    printMessage(8,"Information: recursion on use of Hopital's rule\n");
		    if (verbosity >= 10) {
		      printf("Reused Hopital's rule point is ");
		      printMpfr(*hopitalPoint);
		    }
		  }
		  
		  if (verbosity >= 15) {
		    printf("Information in Hopital: The simplified function is\n");
		    printTree(tempNode);
		    printf("\n");
		  }


		  excludes = evaluateI(stack3, tempNode, x, prec, simplifiesA, simplifiesB-1, newHopitalPoint, leftTheoLinear);

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
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_sqrt(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case EXP:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_exp(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_log(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG_2:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_log2(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG_10:
    evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_log10(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case SIN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
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
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
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
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_tan(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ASIN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_asin(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ACOS:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_acos(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ATAN:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_atan(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case SINH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_sinh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case COSH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_cosh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case TANH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_tanh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ASINH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_asinh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ACOSH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_acosh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ATANH:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_atanh(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case POW:
    leftExcludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    rightExcludes = evaluateI(stack2, tree->child2, x, prec, simplifiesA, simplifiesB, NULL, rightTheo);
    mpfi_pow(stack3, stack1, stack2);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
      mpfi_set(*(internalTheo->boundRight),stack2);
    }
    excludes = concatChains(leftExcludes,rightExcludes);
    break;
  case NEG:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_neg(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ABS:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_abs(stack3, stack1);  
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case DOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_round_to_double(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case DOUBLEDOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_round_to_doubledouble(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case TRIPLEDOUBLE:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_round_to_tripledouble(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ERF:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_erf(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case ERFC:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_erfc(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LOG_1P:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_log1p(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case EXP_M1:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_expm1(stack3, stack1);  
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case DOUBLEEXTENDED:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_round_to_doubleextended(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case LIBRARYFUNCTION:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    tree->libFun->code(stack3, stack1, tree->libFunDeriv);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case CEIL:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_ceil(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case FLOOR:
    excludes = evaluateI(stack1, tree->child1, x, prec, simplifiesA, simplifiesB, NULL, leftTheo);
    mpfi_floor(stack3, stack1);
    if (internalTheo != NULL) {
      mpfi_set(*(internalTheo->boundLeft),stack1);
    }
    break;
  case PI_CONST:
    mpfi_const_pi(stack3);
    excludes = NULL;
    break;
  default:
    fprintf(stderr,"Error: evaluateI: unknown identifier in the tree\n");
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

chain* evaluateITaylor(mpfi_t result, node *func, node *deriv, mpfi_t x, mp_prec_t prec, int recurse, exprBoundTheo *theo);

chain* evaluateITaylorOnDiv(mpfi_t result, node *func, mpfi_t x, mp_prec_t prec, int recurse, exprBoundTheo *theo) {
  node *numerator, *denominator, *derivNumerator, *derivDenominator;
  chain *excludes, *numeratorExcludes, *denominatorExcludes;
  exprBoundTheo *numeratorTheo, *denominatorTheo;
  mpfi_t resultNumerator, resultDenominator, resultIndirect;

  if (func->nodeType == DIV) {
    numerator = func->child1;
    denominator = func->child2;
    derivNumerator = differentiate(numerator);
    derivDenominator = differentiate(denominator);
    mpfi_init2(resultNumerator, prec);
    mpfi_init2(resultDenominator, prec);
    mpfi_init2(resultIndirect, prec);

    if (theo != NULL) {
      numeratorTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      denominatorTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
    } else {
      numeratorTheo = NULL;
      denominatorTheo = NULL;
    }
    
    numeratorExcludes = evaluateITaylor(resultNumerator, numerator, derivNumerator, x, prec, recurse, numeratorTheo);
    denominatorExcludes = evaluateITaylor(resultDenominator, denominator, derivDenominator, x, prec, recurse, denominatorTheo);
    excludes = concatChains(numeratorExcludes,denominatorExcludes);    
    mpfi_div(resultIndirect, resultNumerator, resultDenominator);
    if (mpfi_bounded_p(resultIndirect)) {
      mpfi_set(result, resultIndirect);
      if (theo != NULL) {
	theo->functionType = func->nodeType;
	theo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeft),prec);
	theo->boundRight = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundRight),prec);
	theo->theoLeft = numeratorTheo;
	theo->theoRight = denominatorTheo;
	theo->x = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->x),mpfi_get_prec(x));
	mpfi_set(*(theo->x),x);
	theo->function = copyTree(func);
	theo->y = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->y),mpfi_get_prec(result));
	mpfi_set(*(theo->y),result);
      }
    } else {
      freeChain(excludes,freeMpfiPtr); 
      if (theo != NULL) {
	freeExprBoundTheo(numeratorTheo);
	freeExprBoundTheo(denominatorTheo);
      }
      excludes = evaluateI(result, func, x, prec, 0, hopitalrecursions+1, NULL, theo);
    }
    
    mpfi_clear(resultNumerator);
    mpfi_clear(resultDenominator);
    mpfi_clear(resultIndirect);     
    free_memory(derivNumerator);
    free_memory(derivDenominator);
    return excludes;
  } else {
    return evaluateI(result, func, x, prec, 0, hopitalrecursions+1, NULL, theo);
  }
}

chain* evaluateITaylor(mpfi_t result, node *func, node *deriv, mpfi_t x, mp_prec_t prec, int recurse, exprBoundTheo *theo) {
  mpfr_t xZ, rTl, rTr, leftX, rightX;
  mpfi_t xZI, xZI2, constantTerm, linearTerm, resultTaylor, resultDirect, temp, temp2;
  chain *excludes, *directExcludes, *taylorExcludes, *taylorExcludesLinear, *taylorExcludesConstant;
  exprBoundTheo *constantTheo, *linearTheo, *directTheo;
  node *nextderiv;
  int size;

  mpfr_init2(leftX,mpfi_get_prec(x));
  mpfr_init2(rightX,mpfi_get_prec(x));
  
  mpfi_get_left(leftX,x);
  mpfi_get_right(rightX,x);

  if ((mpfr_cmp(leftX,rightX) == 0) || (deriv == NULL)) {
    if (deriv != NULL) 
      printMessage(9,"Information: avoiding using Taylor's formula on a point interval.\n");
    else 
      printMessage(9,"Warning: no Taylor evaluation is possible because no derivative has been given.\n");
    

    excludes = evaluateI(result, func, x, prec, 1, hopitalrecursions+1, NULL, theo);

    mpfr_clear(leftX);
    mpfr_clear(rightX);
    
    return excludes;
  }


  printMessage(9,"Information: evaluating a function in interval arithmetic using Taylor's formula.\n");
  if (verbosity >= 12) {
    printf("Information: the function is\n");
    printTree(func);
    printf("\nIts derivative is\n");
    printTree(deriv);
    printf("\n");
  }

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
  mpfi_init2(temp2,prec);
  mpfi_init2(constantTerm,prec);
  mpfi_init2(linearTerm,prec);
  mpfi_init2(resultTaylor,prec);
  mpfi_init2(resultDirect,prec);

  mpfr_init2(rTl,prec);
  mpfr_init2(rTr,prec);

  mpfi_mid(xZ,x);
  mpfi_set_fr(xZI,xZ);


  if ((recurse > 0) && (func->nodeType != DIV)) {
    nextderiv = differentiate(deriv);
    size = treeSize(nextderiv);

    if (size > DIFFSIZE) {
	printMessage(1,"Waring: during recursive Taylor evaluation the expression of a derivative has become\n");
	printMessage(1,"as great that it contains more than %d nodes.\n",DIFFSIZE);
	printMessage(1,"Will now stop recursive Taylor evaluation on this expression.\n");
	printMessage(2,"Information: the size of the derivative is %d, we had %d recursion(s) left.\n",size,recurse-1);
	taylorExcludesLinear = evaluateI(linearTerm, deriv, x, prec, 1, hopitalrecursions+1, NULL, linearTheo);
    } else {
      taylorExcludesLinear = evaluateITaylor(linearTerm, deriv, nextderiv, x, prec, recurse - 1, linearTheo);
    }
    
    free_memory(nextderiv);
  } else {
    taylorExcludesLinear = evaluateI(linearTerm, deriv, x, prec, 1, hopitalrecursions+1, NULL, linearTheo);
  }

  if (!mpfi_has_zero(linearTerm)) {

    printMessage(12,"Information: the linear term during Taylor evaluation does not change its sign.\n");
    printMessage(12,"Simplifying by taking the convex hull of the evaluations on the endpoints.\n");

 
    mpfi_init2(xZI2,prec);
    
    mpfi_set_fr(xZI,leftX);
    mpfi_set_fr(xZI2,rightX);

    directExcludes = evaluateI(resultDirect, func, xZI, prec, 0, hopitalrecursions+1, NULL, directTheo);
    taylorExcludesConstant = evaluateI(constantTerm, func, xZI2, prec, 1, hopitalrecursions+1, NULL, constantTheo);

    mpfi_union(result,resultDirect,constantTerm);
    
    if (theo != NULL) {
      if (theo->functionType != POLYNOMIAL) {
	theo->simplificationUsed = MONOTONOCITY;
	theo->theoLeft = directTheo;
	theo->theoRight = constantTheo;
	theo->theoLeftLinear = linearTheo;
	theo->leftDerivative = copyTree(deriv);
	theo->boundLeft = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeft),prec);
	mpfi_set(*(theo->boundLeft),resultDirect);
	theo->theoRight = constantTheo;
	theo->boundRight = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundRight),prec);
	mpfi_set(*(theo->boundRight),constantTerm);
	theo->boundLeftLinear = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
	mpfi_init2(*(theo->boundLeftLinear),prec);
	mpfi_set(*(theo->boundLeftLinear),linearTerm);
      }
    }

      excludes = concatChains(directExcludes,taylorExcludesConstant);
      excludes = concatChains(taylorExcludesLinear,excludes);

      mpfi_clear(xZI2);

  } else {

    taylorExcludesConstant = evaluateI(constantTerm, func, xZI, prec, 1, hopitalrecursions+1, NULL, constantTheo);
    
    mpfi_sub(temp, x, xZI);
    mpfi_mul(temp2, temp, linearTerm);
    mpfi_add(resultTaylor, constantTerm, temp2);
    taylorExcludes = concatChains(taylorExcludesConstant, taylorExcludesLinear);
  
    if (deriv != NULL) 
      directExcludes = evaluateITaylorOnDiv(resultDirect, func, x, prec, recurse, directTheo);
    else 
      directExcludes = evaluateI(resultDirect, func, x, prec, 0, hopitalrecursions+1, NULL, directTheo);

    if (verbosity >= 12) {
      printf("Information: Taylor evaluation: domain:\n");
      printInterval(x);
      printf("\nconstant term:\n");
      printInterval(constantTerm);
      printf("\nlinear term:\n");
      printInterval(linearTerm);
      printf("\ntranslated interval:\n");
      printInterval(temp);
      printf("\nmultiplied linear term:\n");
      printInterval(temp2);
      printf("\ndirect evaluation:\n");
      printInterval(resultDirect);
      printf("\n");
    }

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
  }

  mpfi_revert_if_needed(result);

  if (theo != NULL) mpfi_set(*(theo->y),result);

  mpfr_clear(xZ);
  mpfr_clear(rTl);
  mpfr_clear(rTr);
  mpfi_clear(xZI);
  mpfi_clear(temp);
  mpfi_clear(temp2);
  mpfi_clear(constantTerm);
  mpfi_clear(linearTerm);
  mpfi_clear(resultTaylor);
  mpfi_clear(resultDirect);
  mpfr_clear(leftX);
  mpfr_clear(rightX);

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

  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfi_get_left(l,range);
  mpfi_get_right(r,range);
  mpfr_nextabove(l); mpfr_nextabove(l); mpfr_nextabove(l); mpfr_nextabove(l);

  if ((mpfr_cmp(rangeDiam,diam) <= 0) || (mpfr_cmp(l,r) >= 0)) {
    res = (chain *) safeMalloc(sizeof(chain));
    res->next = NULL;
    temp = (mpfi_t *) safeMalloc(sizeof(mpfi_t));
    mpfi_init2(*temp,prec);
    mpfi_set(*temp,range);
    mpfi_revert_if_needed(*temp);
    res->value = temp;
  } else {
    mpfi_init2(y,prec);
    excludes = evaluateITaylor(y, func, deriv, range, prec, taylorrecursions, theo);
    freeChain(excludes,freeMpfiPtr);
    if (!mpfi_bounded_p(y)) {
      printMessage(1,"Warning: during zero-search the derivative of the function evaluated to NaN or Inf in the interval ");
      if (verbosity >= 1) printInterval(range);
      printMessage(1,".\nThe function might not be continuously differentiable in this interval.\n");
    }
    if ((!mpfi_bounded_p(y)) || mpfi_has_zero(y)) {
      mpfr_init2(m,prec);
      mpfi_get_left(l,range);

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


      mpfr_clear(m);    
      mpfi_clear(lI);
      mpfi_clear(rI);
    } else {
      res = NULL;
      if (noZeroProofs != NULL) *noZeroProofs = addElement(*noZeroProofs,theo);
    }
    mpfi_clear(y);
  }
  mpfr_clear(l);
  mpfr_clear(r);
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

  printMessage(3,"Information: invoking the recursive interval zero search.\n");
  temp = findZerosUnsimplified(funcSimplified,derivSimplified,range,prec,diam,noZeroProofs);
  printMessage(3,"Information: the recursive interval zero search has finished.\n");
  
  free_memory(funcSimplified);
  free_memory(derivSimplified);

  return temp;
}



void printInterval(mpfi_t interval) {
  mpfr_t l,r;
  mp_prec_t prec;
  char *temp_string;

  prec = mpfi_get_prec(interval);
  mpfr_init2(l,prec);
  mpfr_init2(r,prec);
  mpfi_get_left(l,interval);
  mpfi_get_right(r,interval);

  if ((dyadic == 0) && (midpointMode == 1)) {
    temp_string = sprintMidpointMode(l, r);
    if (temp_string != NULL) {
      printf("%s ",temp_string);
      free(temp_string);
    } else {
      printf("[");
      printValue(&l,prec);
      printf(";");
      printValue(&r,prec);
      printf("]");
    }
  } else {
    printf("[");
    printValue(&l,prec);
    printf(";");
    printValue(&r,prec);
    printf("]");
  }

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

  excludes = evaluateITaylor(evalFuncOnInterval, func, deriv, lInterv, prec, taylorrecursions, evalLeftBound); 
  mpfi_get_left(outerLeft,evalFuncOnInterval);
  mpfi_get_right(outerRight,evalFuncOnInterval);
  mpfr_set(innerLeft,outerRight,GMP_RNDU);
  mpfr_set(innerRight,outerLeft,GMP_RNDD);
  excludesTemp = evaluateITaylor(evalFuncOnInterval, func, deriv, rInterv, prec, taylorrecursions, evalRightBound); 
  excludes = concatChains(excludes,excludesTemp);
  mpfi_get_left(tl,evalFuncOnInterval);
  mpfi_get_right(tr,evalFuncOnInterval);
  mpfr_min(outerLeft,outerLeft,tl,GMP_RNDD);
  mpfr_max(outerRight,outerRight,tr,GMP_RNDU);
  mpfr_min(innerLeft,innerLeft,tr,GMP_RNDU);
  mpfr_max(innerRight,innerRight,tl,GMP_RNDD); 
 
  printMessage(3,"Information: invoking interval zero search.\n");
  tempChain = findZeros(numeratorDeriv,derivNumeratorDeriv,range,prec,diam,noZeros); 
  printMessage(3,"Information: interval zero search is done.\n");
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
  printMessage(2,
	  "Information: %d interval(s) have (has) been found that possibly contain(s) the zeros of the derivative.\n",i);

  curr = zeros;
  while (curr != NULL) {

    if (verbosity >= 7) {
      printf("Information:\nCurrent inner enclosure: [");
      printValue(&innerLeft,prec);
      printf(";");
      printValue(&innerRight,prec);
      printf("]\nCurrent outer enclosure: [");
      printValue(&outerLeft,prec);
      printf(";");
      printValue(&outerRight,prec);
      printf("]\n");
    }

    if (theo != NULL) {
      currZeroTheo = (exprBoundTheo *) safeCalloc(1,sizeof(exprBoundTheo));
      nullifyExprBoundTheo(currZeroTheo);
    } else {
      currZeroTheo = NULL;
    }
    currInterval = ((mpfi_t *) (curr->value));
    excludesTemp = evaluateITaylor(evalFuncOnInterval, func, deriv, *currInterval, prec, taylorrecursions, currZeroTheo); 

    if (verbosity >= 7) {
      printf("Information: The function evaluates on\n");
      printInterval(*currInterval);
      printf(" to\n");
      printInterval(evalFuncOnInterval);
      printf("\n");
    }

    excludes = concatChains(excludes,excludesTemp);
    mpfi_get_left(tl,evalFuncOnInterval);
    mpfi_get_right(tr,evalFuncOnInterval);

    if (theo != NULL) {
      theo->evalOnZeros = addElement(theo->evalOnZeros,currZeroTheo);
    }

    if (mpfr_nan_p(tl) || mpfr_nan_p(tr)) {
      printMessage(1,"Warning: NaNs occurred during the interval evaluation of the zeros of the derivative.\n");
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

  if (mightExcludes == NULL) {
    freeChain(excludes,freeMpfiPtr);
  } else {
    *mightExcludes = excludes;
  }

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
  mpfr_t z, max, temp, x1, x2, y1, y2, step, s, derivCutOff;
  node *deriv;
  node *derivsecond;
  int newtonWorked;
  int i,k;

  mpfr_init2(x1, prec);
  mpfr_init2(x2, prec);
  mpfr_init2(step, prec);
  mpfr_init2(y1, prec);
  mpfr_init2(y2, prec);
  mpfr_init2(s, prec);

  if ( (!mpfr_number_p(a)) || (!mpfr_number_p(b)) ) {
    printMessage(1,"Warning: a bound of the interval is infinite or NaN.\n");
    printMessage(1,"This command cannot handle such intervals.\n");
    mpfr_set_nan(result);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(step); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(s);
    return;
  }

  mpfr_sub(step, b, a, GMP_RNDN);
  mpfr_div_ui(step, step, points, GMP_RNDN);
 
  if (mpfr_sgn(step) == 0) {
    printMessage(1,"Warning: the given interval is reduced to one point.\n");
    evaluateFaithful(y1,tree,a,prec);
    mpfr_abs(result,y1,GMP_RNDU);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(step); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(s);
    return;
  }

  if (mpfr_sgn(step) < 0) {
    printMessage(1,"Warning: the interval is empty.\n");
    mpfr_set_d(result,0.,GMP_RNDN);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(step); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(s);
    return;
  }

  if (isConstant(tree)) {
    evaluateFaithful(y1,tree,a,prec);
    printMessage(1,"Warning: the expression is constant.\n");
    mpfr_abs(result,y1,GMP_RNDU);
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(step); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(s);
    return;
  }
 
  mpfr_init2(z,prec);
  mpfr_init2(max,prec);
  mpfr_init2(temp,prec);
  mpfr_init2(derivCutOff,prec);
  mpfr_set_d(derivCutOff,1.0,GMP_RNDN);
  mpfr_div_2ui(derivCutOff,derivCutOff,4 * prec,GMP_RNDN);

  deriv = differentiate(tree);
  derivsecond = differentiate(deriv);

  evaluateFaithful(temp, tree, a, prec);
  if (!mpfr_nan_p(temp)) {
    mpfr_abs(max, temp, GMP_RNDU);
    if (verbosity >= 3) { 
      printf("Information: current max is "); printValue(&max,prec);
      printf(" and is reached at "); printMpfr(a);
    }
  } else {
    printMessage(1,"Warning: the evaluation of the given function in ");
    mpfr_set(z,a,GMP_RNDN);
    if (verbosity >= 1) printValue(&z,prec);
    printMessage(1," gives NaN.\n");
    printMessage(1,"This point will be excluded from the infnorm result.\n");
    mpfr_set_d(max,1.0,GMP_RNDU);
    mpfr_div_2ui(max,max,(prec * 64),GMP_RNDN);
  }
  evaluateFaithful(temp, tree, b, prec);
  if (!mpfr_nan_p(temp)) {
      mpfr_abs(temp, temp, GMP_RNDU);
      if ((verbosity >= 3) && (mpfr_cmp(b, max) > 0)) { 
	printf("Information: current max is "); printValue(&temp,prec);
	printf(" and is reached at "); printMpfr(b);
      }
      mpfr_max(max, max, temp, GMP_RNDU);
  } else {
    printMessage(1,"Warning: the evaluation of the given function in ");
    mpfr_set(z,b,GMP_RNDN);
    if (verbosity >= 1) printValue(&z,prec);
    printMessage(1," gives NaN\n");
    printMessage(1,"This point will be excluded from the infnorm result.\n");
  }

  mpfr_set(x1,a,GMP_RNDN);
  mpfr_add(x2,x1,step,GMP_RNDU);
  if (mpfr_cmp(x2,b)>0) mpfr_set(x2,b,GMP_RNDN);
  evaluate(y1,deriv,x1,prec);
  evaluate(y2,deriv,x2,prec);
  i = 0; k = 0;
  while(mpfr_less_p(x1,b)) {
    i++; k++;
    if (i == 100) {
      i = 0;
      printMessage(2,"Information: %d out of %d points have been handled.\n",k,points);
    }
    
    evaluate(s,tree,x1,2 * prec);
    if ((mpfr_cmpabs(s,max) > 0) || (!mpfr_number_p(s))) {
      evaluateFaithfulWithCutOffFast(s,tree,deriv,x1,max,prec);
    }
    if (mpfr_number_p(s)) {
      mpfr_abs(s,s,GMP_RNDN);
      if ((verbosity >= 3) && (mpfr_cmp(s, max) > 0)) { 
	printf("Information: current max is "); printValue(&s,prec);
	printf(" and is reached at "); printMpfr(x1);
      }
      mpfr_max(max,max,s,GMP_RNDU);
    }
    if (mpfr_sgn(y1) != mpfr_sgn(y2)) {
      newtonWorked = newtonMPFR(z, deriv, derivsecond, x1, x2, prec);
      if (!newtonWorked) {
	printMessage(1,"Warning: zero-search by Newton's method did not converge\n");
	printMessage(2,"The function was\n");
	if (verbosity >= 2) printTree(deriv);
	printMessage(2,"\nThe interval was\n[");
	if (verbosity >= 2) printValue(&x1,prec);
	printMessage(2,";");
	if (verbosity >= 2) printValue(&x2,prec);
	printMessage(2,"]\n");
	printMessage(1,"This (possibly maximum) point will be excluded from the infnorm result.\n");
      } else {
	if (!(mpfr_number_p(z))) {
	  printMessage(1,"Warning: zero-search by Newton's method produces infinity or NaN.\n");
	  printMessage(1,"Will replace the zero point of the derivative by the mid-point of\nthe considered interval [");
	  if (verbosity >= 1) printValue(&x1,prec);
	  printMessage(1,";");
	  if (verbosity >= 1) printValue(&x2,prec);
	  printMessage(1,"]\n");
	  mpfr_add(z,x1,x2,GMP_RNDN);
	  mpfr_div_ui(z,z,2,GMP_RNDN);
	}
	evaluateFaithfulWithCutOff(temp,tree,z,max,prec);
	if (!mpfr_nan_p(temp)) {
	  mpfr_abs(temp, temp, GMP_RNDU);
	  if ((verbosity >= 3) && (mpfr_cmp(temp, max) > 0)) { 
	    printf("Information: current max is "); printValue(&temp,prec);
	    printf(" and is reached at "); printMpfr(z);
	  }
	  mpfr_max(max, max, temp, GMP_RNDU);
	} else {
	  printMessage(1,"Warning: the evaluation of the given function in ");
	  if (verbosity >= 1) printValue(&z,prec);
	  printMessage(1," gives NaN.\n");
	  printMessage(1,"This (possibly maximum) point will be excluded from the infnorm result.\n");
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
    mpfr_clear(x1); mpfr_clear(x2); mpfr_clear(step); mpfr_clear(y1); mpfr_clear(y2); mpfr_clear(s);
  mpfr_clear(z); mpfr_clear(max); mpfr_clear(temp); mpfr_clear(derivCutOff);
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

  if ((!mpfr_number_p(*(range.a))) || (!mpfr_number_p(*(range.b)))) {
    printMessage(1,"Warning: the bounds of the range an infinite norm is to be computed on are not numbers.\n");
    if (proof != NULL) {
      printMessage(1,"Warning: no proof will be generated.\n");
    }
    mpfr_set_d(*(res.a),0.0,GMP_RNDN);
    mpfr_set_inf(*(res.b),1);
    return res;
  }
  
  if ((mpfr_cmp(*(range.a),*(range.b)) == 0) && (proof == NULL)) {
    evaluateRangeFunctionFast(res, func, NULL, range, prec);
    mpfr_abs(*(res.a),*(res.a),GMP_RNDN);
    mpfr_abs(*(res.b),*(res.b),GMP_RNDN);
    if (mpfr_cmp(*(res.a),*(res.b)) > 0) {
      mpfr_init2(z,prec);
      mpfr_set(z,*(res.b),GMP_RNDN);
      mpfr_set(*(res.b),*(res.a),GMP_RNDN);
      mpfr_set(*(res.a),z,GMP_RNDN);
      mpfr_clear(z);
    }
    return res;
  }

  if (isTrivialInfnormCase(res, func)) {
    if (proof != NULL) {
      printMessage(1,"Warning: the infnorm on the given function is trivially calculable.\n");
      printMessage(1,"No proof will be generated.\n");
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
    printMessage(1,"Warning: the derivative of the function is a quotient, thus possibly not continuous in the interval.\n");
    printMessage(1,"Only the zeros of the numerator will be searched and pole detection may fail.\n");
    printMessage(1,"Be sure that the function is twice continuously differentiable if trusting the infnorm result.\n");

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
	printMessage(1,"Warning: the derivative of the function seems to have a extensible singularity in ");
	if (verbosity >= 1) printValue(&z,prec);
	printMessage(1,".\n");
	printMessage(1,"The infnorm result might not be trustful if the derivative cannot actually\n");
	printMessage(1,"be extended in this point.\n");
      } else {
	printMessage(1,"Warning: the derivative of the function seems to have a singularity in ");
	if (verbosity >= 1) printValue(&z,prec);
	printMessage(1,".\n");
	printMessage(1,"The infnorm result is likely to be wrong.\n");
      }
    } else {
      evaluate(ya,denominatorDeriv,*(range.a),prec);
      evaluate(yb,denominatorDeriv,*(range.b),prec);

      if (mpfr_sgn(ya) != mpfr_sgn(yb)) {
	printMessage(1,"Warning: the derivative of the function seems to have a (extensible) singularity in the considered interval.\n");
	printMessage(1,"The infnorm result might be not trustful if the function is not continuously differentiable.\n");
      } else {
	printMessage(2,"Information: the derivative seems to have no (false) pole in the considered interval.\n");
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

  printMessage(3,"Information: invoking the interval infnorm subfunction.\n");

  infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,
	   prec,rangeDiameter,initialExcludes,&mightExcludes,theo);

  printMessage(3,"Information: interval infnorm subfunction has finished.\n");

  secondMightExcludes = NULL;

  if (mightExcludes != NULL) {
    printMessage(1,"Warning: to get better infnorm quality, the following domains will be excluded additionally:\n");
    if (verbosity >= 1) {
      curr = mightExcludes;
      while(curr != NULL) {
	printInterval(*((mpfi_t *) (curr->value)));
	printf("\n");
	curr = curr->next;
      }
      printf("\n");
    }
    mightExcludes = concatChains(mightExcludes,initialExcludes);

    if (theo != NULL) freeInfnormTheo(theo);
    if (proof != NULL) {
      theo = (infnormTheo *) safeCalloc(1,sizeof(infnormTheo));
    } else {
      theo = NULL;
    }
    
    printMessage(3,"Information: invoking the interval infnorm subfunction on additional excludes.\n");

    infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,
	     2*prec,rangeDiameter,mightExcludes,&secondMightExcludes,theo);

    printMessage(3,"Information: interval infnorm subfunction on additional excludes has finished.\n");

    if (secondMightExcludes != NULL) {
      printMessage(1,"Warning: the following domains remain the exclusion of which could improve the result.\n");
      if (verbosity >= 1) {
	curr = secondMightExcludes;
	while(curr != NULL) {
	  printInterval(*((mpfi_t *) (curr->value)));
	  printf("\n");
	  curr = curr->next;
	}
	printf("\n");
      }
    }
  }

  if (proof != NULL) {
    printMessage(2,"Information: started writing the proof.\n");
    fprintInfnormTheo(proof,theo,1);
    printMessage(2,"Information: proof written.\n");
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

  tempChain = evaluateITaylor(y, func, deriv, x, prec, taylorrecursions, NULL);

  mpfi_get_left(*(yrange.a),y);
  mpfi_get_right(*(yrange.b),y);

  freeChain(tempChain,freeMpfiPtr);
  mpfi_clear(x);
  mpfi_clear(y);
}

void evaluateRangeFunction(rangetype yrange, node *func, rangetype xrange, mp_prec_t prec) {
  node *deriv, *temp, *temp2, *numerator, *denominator, *f;

  temp = differentiate(func);
  deriv = horner(temp);
  temp2 = horner(func);

  f = NULL;

  if (getNumeratorDenominator(&numerator,&denominator,temp2)) {
    if (isSyntacticallyEqual(numerator, denominator)) {
      mpfr_set_d(*(yrange.a),1.0,GMP_RNDD);
      mpfr_set_d(*(yrange.b),1.0,GMP_RNDU);
      free_memory(numerator);
      free_memory(denominator);
      free_memory(deriv);
      free_memory(temp);
      free_memory(temp2);
      return;
    } else {
      f = copyTree(temp2);
    }
    free_memory(numerator);
    free_memory(denominator);
  } else {
    f = numerator;
  }

  evaluateRangeFunctionFast(yrange,f,deriv,xrange,prec);
  free_memory(deriv);
  free_memory(temp);
  free_memory(temp2);
  free_memory(f);
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


int checkInfnormI(node *func, node *deriv, mpfi_t infnormval, mpfi_t range, mpfr_t diam, mp_prec_t prec) {
  mpfi_t evaluateOnRange, rangeLeft, rangeRight;
  chain *tempChain;
  mpfr_t l,m,r, diamRange;
  int resultLeft, resultRight;

  mpfi_init2(evaluateOnRange,prec);

  tempChain = evaluateITaylor(evaluateOnRange, func, deriv, range, prec, taylorrecursions, NULL);

  freeChain(tempChain,freeMpfiPtr);

  if (mpfi_is_inside(evaluateOnRange, infnormval)) {
    /* Simple end case: the interval evaluation is contained in the given interval for infnorm */
    mpfi_clear(evaluateOnRange);
    return 1;
  }

  mpfr_init2(diamRange,prec);
  mpfi_diam(diamRange,range);

  if (mpfr_cmp(diamRange,diam) <= 0) {
    /* Simple end case: the range to test is already smaller than diam but we could not check */
    if (verbosity >= 2) {
      printf("Information: could not check the infinite norm on the domain\n");
      printInterval(range);
      printf("\nThe function evaluates here to\n");
      printInterval(evaluateOnRange);
      printf("\n");
    }
    mpfi_clear(evaluateOnRange);
    mpfr_clear(diamRange);
    return 0;
  }

  mpfr_init2(l,prec);
  mpfr_init2(m,prec);
  mpfr_init2(r,prec);
  mpfi_init2(rangeLeft,prec);
  mpfi_init2(rangeRight,prec);
  
  mpfi_get_left(l,range);
  mpfi_mid(m,range);
  mpfi_get_right(r,range);
  
  mpfi_interv_fr(rangeLeft,l,m);
  mpfi_interv_fr(rangeRight,m,r);

  /* Recurse on half the range */
  
  resultLeft = 0;
  resultRight = 0;

  resultLeft = checkInfnormI(func, deriv, infnormval, rangeLeft, diam, prec);
  if (resultLeft || (verbosity >= 4)) resultRight = checkInfnormI(func, deriv, infnormval, rangeRight, diam, prec);

  mpfi_clear(rangeRight);
  mpfi_clear(rangeLeft);
  mpfr_clear(r);
  mpfr_clear(m);
  mpfr_clear(l);
  mpfi_clear(evaluateOnRange);
  mpfr_clear(diamRange);

  return (resultLeft & resultRight);
}


int checkInfnorm(node *func, rangetype range, mpfr_t infnormval, mpfr_t diam, mp_prec_t prec) {
  node *deriv;
  mpfi_t rangeI, infnormvalI;
  mpfr_t rangeDiameter, tempLeft, tempRight;
  int result;

  mpfi_init2(rangeI,prec);
  mpfi_init2(infnormvalI,prec);
  mpfr_init2(rangeDiameter,prec);
  mpfr_init2(tempLeft,prec);
  mpfr_init2(tempRight,prec);

  mpfr_sub(rangeDiameter,*(range.b),*(range.a),GMP_RNDD);
  mpfr_mul(rangeDiameter,rangeDiameter,diam,GMP_RNDD);
  mpfi_interv_fr(rangeI,*(range.a),*(range.b));
  mpfr_abs(tempRight,infnormval,GMP_RNDU);
  mpfr_neg(tempLeft,tempRight,GMP_RNDD);
  mpfi_interv_fr(infnormvalI,tempLeft,tempRight);
  deriv = differentiate(func);

  result = checkInfnormI(func, deriv, infnormvalI, rangeI, rangeDiameter, prec);
  
  mpfr_clear(tempLeft);
  mpfr_clear(tempRight);
  mpfr_clear(rangeDiameter);
  mpfi_clear(infnormvalI);
  mpfi_clear(rangeI);

  return result;
}


void evaluateConstantWithErrorEstimate(mpfr_t res, mpfr_t err, node *func, mpfr_t x, mp_prec_t prec) {
  rangetype xrange, yrange;
  mpfr_t temp;

  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));

  mpfr_init2(*(xrange.a), prec);
  mpfr_init2(*(xrange.b), prec);
  mpfr_init2(*(yrange.a), prec);
  mpfr_init2(*(yrange.b), prec);
  mpfr_init2(temp,prec + 10);
  
  mpfr_set(*(xrange.a),x,GMP_RNDD);
  mpfr_set(*(xrange.b),x,GMP_RNDU);
  
  evaluateRangeFunction(yrange, func, xrange, prec);

  mpfr_add(temp,*(yrange.a),*(yrange.b),GMP_RNDN);
  mpfr_div_2ui(temp,temp,1,GMP_RNDN);
  mpfr_set(res,temp,GMP_RNDN);

  if (mpfr_zero_p(res)) {
    if (mpfr_zero_p(*(yrange.a)) && mpfr_zero_p(*(yrange.b))) {
      mpfr_set_d(err,0.0,GMP_RNDN);
    } else {
      mpfr_set_d(temp,1.0,GMP_RNDN);
      mpfr_div(temp,temp,res,GMP_RNDN);
      mpfr_set(err,temp,GMP_RNDU);
    }
  } else {
    mpfr_abs(*(yrange.a),*(yrange.a),GMP_RNDN);
    mpfr_abs(*(yrange.b),*(yrange.b),GMP_RNDN);
    if (mpfr_cmp(*(yrange.b),*(yrange.a)) > 0) {
      mpfr_set(*(yrange.a),*(yrange.b),GMP_RNDN);
    }
    mpfr_abs(temp,temp,GMP_RNDN);
    mpfr_sub(*(yrange.a),*(yrange.a),temp,GMP_RNDU);
    mpfr_div(err,*(yrange.a),temp,GMP_RNDU);
  }


  mpfr_clear(*(xrange.a));
  mpfr_clear(*(xrange.b));
  mpfr_clear(*(yrange.a));
  mpfr_clear(*(yrange.b));
  mpfr_init2(temp,prec);
  free(xrange.a);
  free(xrange.b);
  free(yrange.a);
  free(yrange.b);
}

chain* findZerosByNewton(node *func, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  node *deriv;
  mpfr_t resNewtonStep, ap, bp, step, yAp, yBp;
  int newtonOkay;
  mpfr_t *newZero;
  chain *fpZeros;

  fpZeros = NULL;
  deriv = differentiate(func);
  mpfr_init2(resNewtonStep,prec);
  mpfr_init2(ap,prec);
  mpfr_init2(bp,prec);
  mpfr_init2(step,prec);
  mpfr_init2(yAp,prec);
  mpfr_init2(yBp,prec);
  
  mpfr_sub(step,b,a,GMP_RNDU);
  if (mpfr_zero_p(step)) {
    evaluate(resNewtonStep,func,a,prec);
    newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*newZero,prec);
    mpfr_set(*newZero,resNewtonStep,GMP_RNDN);
    fpZeros = addElement(fpZeros,newZero);
  } else {
    mpfr_div_ui(step,step,defaultpoints,GMP_RNDU);    
    mpfr_set(ap,a,GMP_RNDD);
    while (mpfr_cmp(ap,b) < 0) {
      mpfr_add(bp,ap,step,GMP_RNDN);
      mpfr_min(bp,bp,b,GMP_RNDU);
      
      newtonOkay = newtonMPFR(resNewtonStep, func, deriv, ap, bp, prec);
      
      if (newtonOkay) {
	newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*newZero,prec);
	mpfr_set(*newZero,resNewtonStep,GMP_RNDN);
	fpZeros = addElement(fpZeros,newZero);
      } else {
	evaluateFaithful(yAp, func, ap, prec);
	evaluateFaithful(yBp, func, bp, prec);
	if (mpfr_number_p(yAp) && mpfr_number_p(yBp) &&
	    (mpfr_sgn(yAp) != mpfr_sgn(yBp))) {
	  newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*newZero,prec);
	  mpfr_set(*newZero,ap,GMP_RNDN);
	  mpfr_add(*newZero,*newZero,bp,GMP_RNDN);
	  mpfr_div_2ui(*newZero,*newZero,1,GMP_RNDN);
	  fpZeros = addElement(fpZeros,newZero);
	}
      }
      
      mpfr_set(ap,bp,GMP_RNDN);
    }
  }
  mpfr_clear(step);
  mpfr_clear(bp);
  mpfr_clear(ap);
  mpfr_clear(yAp);
  mpfr_clear(yBp);
  mpfr_clear(resNewtonStep);
  free_memory(deriv);
  return fpZeros;
}



chain* fpFindZerosFunction(node *func, rangetype range, mp_prec_t prec) {
  mpfr_t diam;
  chain *intervalZeros, *fpZeros, *temp, *fpZerosOnInterval, *fpZeros2, *curr;
  mpfr_t *newZero;
  mpfr_t before, after, yBefore, yAfter, y, compare;
  int addToList, removedFromList;
  unsigned int oldDefaultPoints;

  
  oldDefaultPoints = defaultpoints;
  defaultpoints = defaultpoints >> 4;

  mpfr_init2(diam,prec+50);
  mpfr_set_d(diam,DEFAULTDIAM2,GMP_RNDN);

  intervalZeros = findZerosFunction(func, range, prec, diam);
  
  mpfr_clear(diam);

  fpZeros = NULL;

  while (intervalZeros != NULL) {
    fpZerosOnInterval = findZerosByNewton(func, 
					  *(((rangetype *) (intervalZeros->value))->a), 
					  *(((rangetype *) (intervalZeros->value))->b), 
					  4*prec);
    fpZeros = concatChains(fpZeros, fpZerosOnInterval);
    mpfr_clear(*(((rangetype *) (intervalZeros->value))->a));
    mpfr_clear(*(((rangetype *) (intervalZeros->value))->b));
    free(((rangetype *) (intervalZeros->value))->a);
    free(((rangetype *) (intervalZeros->value))->b);
    free(intervalZeros->value);
    temp = intervalZeros->next;
    free(intervalZeros);
    intervalZeros = temp;
  }
  

  mpfr_init2(compare,prec);
  mpfr_set_d(compare,1.0,GMP_RNDN);
  mpfr_div_ui(compare,compare,prec,GMP_RNDN);
  fpZeros2 = NULL;
  curr = fpZeros;
  while (curr != NULL) {
    while ((curr->next != NULL) && (mpfr_cmp(*((mpfr_t *) (curr->value)),*((mpfr_t *) (curr->next->value))) == 0))
      curr = curr->next;
    newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*newZero,prec);
    mpfr_set(*newZero,*((mpfr_t *) (curr->value)),GMP_RNDN);
    fpZeros2 = addElement(fpZeros2,newZero);
    if ((!mpfr_zero_p(*newZero)) && (mpfr_cmpabs(*newZero,compare) <= 0)) {
      newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*newZero,prec);
      mpfr_set_d(*newZero,0.0,GMP_RNDN);
      fpZeros2 = addElement(fpZeros2,newZero);
    }
    curr = curr->next;
  }
  mpfr_clear(compare);

  while (fpZeros != NULL) {
    mpfr_clear(*((mpfr_t*) (fpZeros->value)));
    free((fpZeros->value));
    temp = fpZeros->next;
    free(fpZeros);
    fpZeros = temp;
  }

  mpfr_init2(before,prec);
  mpfr_init2(after,prec);
  mpfr_init2(yAfter,prec);
  mpfr_init2(yBefore,prec);
  mpfr_init2(y,prec);

  removedFromList = 0;
  fpZeros = NULL;
  while (fpZeros2 != NULL) {
    
    addToList = 0;

    evaluateFaithful(y, func, *((mpfr_t *) (fpZeros2->value)), prec);

    if (mpfr_zero_p(y) || (!mpfr_number_p(y)) || mpfr_zero_p(*((mpfr_t *) (fpZeros2->value)))) {
      addToList = 1;
    } else {

      mpfr_set(before,*((mpfr_t *) (fpZeros2->value)),GMP_RNDN);
      mpfr_set(after,*((mpfr_t *) (fpZeros2->value)),GMP_RNDN);
      mpfr_nextabove(after);
      mpfr_nextbelow(before);

      evaluateFaithful(yAfter, func, after, prec);
      evaluateFaithful(yBefore, func, before, prec);
      
      if ((!mpfr_number_p(yAfter)) || (!mpfr_number_p(yBefore))) {
	addToList = 1;
      } else {
	if (mpfr_sgn(yAfter) != mpfr_sgn(yBefore)) {
	  addToList = 1;
	} else {
	  if (mpfr_number_p(y)) {
	    if (mpfr_sgn(y) != mpfr_sgn(yAfter)) {
	      addToList = 1;
	    } else {
	      removedFromList = 1;
	      if (verbosity >= 2) {
		printMessage(2,"Information: removing possible zero in ");
		printMpfr(*((mpfr_t *) (fpZeros2->value)));
		printMessage(3,"Information: removing because all signs are equal.\n");
	      }
	    }
	  } else {
	    removedFromList = 1;
	    if (verbosity >= 2) {
	      printMessage(2,"Information: removing possible zero in ");
	      printMpfr(*((mpfr_t *) (fpZeros2->value)));
	      printMessage(3,"Information: removing because predecessor and successor signs are equal.\n");
	    }
	  }
	}
      }
    }

    if (addToList) {
      fpZeros = addElement(fpZeros,fpZeros2->value);
    }
    temp = fpZeros2->next;
    free(fpZeros2);
    fpZeros2 = temp;
  }

  if (removedFromList) {
    printMessage(1,"Warning: actual zero filter has removed at least one possible zero of higher order.\n");
  }

  mpfr_clear(before);
  mpfr_clear(after);
  mpfr_clear(yBefore);
  mpfr_clear(yAfter);
  mpfr_clear(y);

  sortChain(fpZeros,  cmpMpfrPtr);

  fpZeros2 = NULL;
  curr = fpZeros;
  while (curr != NULL) {
    while ((curr->next != NULL) && (mpfr_cmp(*((mpfr_t *) (curr->value)),*((mpfr_t *) (curr->next->value))) == 0))
      curr = curr->next;
    newZero = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*newZero,mpfr_get_prec(*((mpfr_t *) (curr->value))));
    mpfr_set(*newZero,*((mpfr_t *) (curr->value)),GMP_RNDN);
    fpZeros2 = addElement(fpZeros2,newZero);
    curr = curr->next;
  }

  while (fpZeros != NULL) {
    mpfr_clear(*((mpfr_t*) (fpZeros->value)));
    free((fpZeros->value));
    temp = fpZeros->next;
    free(fpZeros);
    fpZeros = temp;
  }

  defaultpoints = oldDefaultPoints;

  return fpZeros2;
}


chain *uncertifiedZeroDenominators(node *tree, mpfr_t a, mpfr_t b, mp_prec_t prec) {
  chain *leftPoles, *rightPoles, *newZeros;
  rangetype range;

  if (tree == NULL) return NULL;
  switch (tree->nodeType) {
  case VARIABLE:
    return NULL;
    break;
  case CONSTANT:
  case PI_CONST:
    return NULL;
    break;
  case ADD:
    leftPoles = uncertifiedZeroDenominators(tree->child1,a,b,prec);
    rightPoles = uncertifiedZeroDenominators(tree->child2,a,b,prec);
    return concatChains(leftPoles,rightPoles);
    break;
  case SUB:
    leftPoles = uncertifiedZeroDenominators(tree->child1,a,b,prec);
    rightPoles = uncertifiedZeroDenominators(tree->child2,a,b,prec);
    return concatChains(leftPoles,rightPoles);
    break;
  case MUL:
    leftPoles = uncertifiedZeroDenominators(tree->child1,a,b,prec);
    rightPoles = uncertifiedZeroDenominators(tree->child2,a,b,prec);
    return concatChains(leftPoles,rightPoles);
    break;
  case DIV:
    leftPoles = uncertifiedZeroDenominators(tree->child1,a,b,prec);
    rightPoles = uncertifiedZeroDenominators(tree->child2,a,b,prec);
    range.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    range.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(range.a),prec);
    mpfr_init2(*(range.b),prec);
    mpfr_set(*(range.a),a,GMP_RNDD);
    mpfr_set(*(range.b),b,GMP_RNDU);
    newZeros = fpFindZerosFunction(tree->child2, range, prec);
    mpfr_clear(*(range.a));
    mpfr_clear(*(range.b));
    free(range.a);
    free(range.b);
    leftPoles = concatChains(leftPoles,rightPoles);
    return concatChains(leftPoles,newZeros);
    break;
  case SQRT:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case EXP:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case LOG:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case LOG_2:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case LOG_10:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case SIN:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case COS:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case TAN:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ASIN:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ACOS:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ATAN:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case SINH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case COSH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case TANH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ASINH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ACOSH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ATANH:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case POW:
    leftPoles = uncertifiedZeroDenominators(tree->child1,a,b,prec);
    rightPoles = uncertifiedZeroDenominators(tree->child2,a,b,prec);
    return concatChains(leftPoles,rightPoles);
    break;
  case NEG:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ABS:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case DOUBLE:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case DOUBLEDOUBLE:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case TRIPLEDOUBLE:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ERF:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case ERFC:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case LOG_1P:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case EXP_M1:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case DOUBLEEXTENDED:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case LIBRARYFUNCTION:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case CEIL:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  case FLOOR:
    return uncertifiedZeroDenominators(tree->child1,a,b,prec);
    break;
  default:
   fprintf(stderr,"Error: uncertifiedZeroDenominators: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return NULL;
}


int isEvaluable(node *func, mpfr_t x, mpfr_t *y, mp_prec_t prec) {
  mpfr_t val;
  rangetype xrange, yrange;

  mpfr_init2(val,prec);
  evaluate(val,func,x,prec);
  if (mpfr_number_p(val)) {
    if (y != NULL) {
      mpfr_set(*y,val,GMP_RNDN);
    }
    mpfr_clear(val);
    return ISFLOATINGPOINTEVALUABLE;
  }

  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));

  mpfr_init2(*(xrange.a),prec);
  mpfr_init2(*(xrange.b),prec);
  mpfr_init2(*(yrange.a),prec);
  mpfr_init2(*(yrange.b),prec);

  mpfr_set(*(xrange.a),x,GMP_RNDD);
  mpfr_set(*(xrange.b),x,GMP_RNDU);

  evaluateRangeFunction(yrange, func, xrange, prec);

  if (mpfr_number_p(*(yrange.a)) && mpfr_number_p(*(yrange.b))) {
    mpfr_add(val,*(yrange.a),*(yrange.b),GMP_RNDN);
    mpfr_div_2ui(val,val,1,GMP_RNDN);
    if (!mpfr_number_p(val)) {
      mpfr_clear(val);
      mpfr_clear(*(xrange.a));
      mpfr_clear(*(xrange.b));
      mpfr_clear(*(yrange.a));
      mpfr_clear(*(yrange.b));
      free(xrange.a);
      free(xrange.b);
      free(yrange.a);
      free(yrange.b);
      return ISNOTEVALUABLE;
    }
    if (y != NULL) {
      mpfr_set(*y,val,GMP_RNDN);
    }
    mpfr_clear(val);
    mpfr_clear(*(xrange.a));
    mpfr_clear(*(xrange.b));
    mpfr_clear(*(yrange.a));
    mpfr_clear(*(yrange.b));
    free(xrange.a);
    free(xrange.b);
    free(yrange.a);
    free(yrange.b);
    return ISHOPITALEVALUABLE;
  } 

  mpfr_clear(*(xrange.a));
  mpfr_clear(*(xrange.b));
  mpfr_clear(*(yrange.a));
  mpfr_clear(*(yrange.b));
  free(xrange.a);
  free(xrange.b);
  free(yrange.a);
  free(yrange.b);
  return ISNOTEVALUABLE;
}

int evaluateWithAccuracyEstimate(node *func, mpfr_t x, mpfr_t y, mpfr_t accur, mp_prec_t prec) {
  rangetype xrange, yrange;

  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));

  mpfr_init2(*(xrange.a),prec);
  mpfr_init2(*(xrange.b),prec);
  mpfr_init2(*(yrange.a),prec);
  mpfr_init2(*(yrange.b),prec);

  mpfr_set(*(xrange.a),x,GMP_RNDD);
  mpfr_set(*(xrange.b),x,GMP_RNDU);

  evaluateRangeFunction(yrange, func, xrange, prec);

  mpfr_add(*(xrange.a),*(yrange.a),*(yrange.b),GMP_RNDN);
  mpfr_div_2ui(*(xrange.a),*(xrange.a),1,GMP_RNDN);
  mpfr_set(y,*(xrange.a),GMP_RNDN);

  /* We have a zero in the output interval or are not a number */
  if ((mpfr_sgn(*(yrange.a)) != mpfr_sgn(*(yrange.b))) || (!mpfr_number_p(y))) {
    mpfr_clear(*(xrange.a));
    mpfr_clear(*(xrange.b));
    mpfr_clear(*(yrange.a));
    mpfr_clear(*(yrange.b));
    free(xrange.a);
    free(xrange.b);
    free(yrange.a);
    free(yrange.b);
    return 0;
  }
  
  /* We have the exact interval [0;0] with an error of 0 */
  if (mpfr_zero_p(*(yrange.a)) && mpfr_zero_p(*(yrange.b))) {
    mpfr_set_d(accur,0.0,GMP_RNDN);
    mpfr_clear(*(xrange.a));
    mpfr_clear(*(xrange.b));
    mpfr_clear(*(yrange.a));
    mpfr_clear(*(yrange.b));
    free(xrange.a);
    free(xrange.b);
    free(yrange.a);
    free(yrange.b);
    return 1;
  }

  if (mpfr_cmp(y,*(yrange.b)) > 0) {
    mpfr_set(*(yrange.b),y,GMP_RNDU);
  }

  if (mpfr_cmp(y,*(yrange.a)) < 0) {
    mpfr_set(*(yrange.a),y,GMP_RNDD);
  }

  mpfr_abs(*(yrange.a),*(yrange.a),GMP_RNDD);
  mpfr_abs(*(yrange.b),*(yrange.b),GMP_RNDD);
  mpfr_min(*(xrange.a),*(yrange.a),*(yrange.b),GMP_RNDD);
  mpfr_max(*(xrange.b),*(yrange.a),*(yrange.b),GMP_RNDU);

  mpfr_sub(*(xrange.b),*(xrange.b),*(xrange.a),GMP_RNDU);

  mpfr_div(*(xrange.b),*(xrange.b),*(xrange.a),GMP_RNDU);
  mpfr_mul_2ui(*(xrange.b),*(xrange.b),1,GMP_RNDU);
  mpfr_set(accur,*(xrange.b),GMP_RNDU);

  mpfr_clear(*(xrange.a));
  mpfr_clear(*(xrange.b));
  mpfr_clear(*(yrange.a));
  mpfr_clear(*(yrange.b));
  free(xrange.a);
  free(xrange.b);
  free(yrange.a);
  free(yrange.b);

  return 1;
}


int evaluateWithAccuracy(node *func, mpfr_t x, mpfr_t y, mpfr_t accur, 
			 mp_prec_t minprec, mp_prec_t maxprec, mp_prec_t *needPrec) {
  mpfr_t temp, currY, currX, currAccur, resY;
  mp_prec_t p;
  int res, okay;

  if (mpfr_sgn(accur) <= 0) return 0;

  mpfr_init2(temp,minprec);
  mpfr_set_d(temp,1.0,GMP_RNDN);
  p = mpfr_get_prec(y);
  if (maxprec < p) p = maxprec;
  mpfr_div_2ui(temp,temp,p,GMP_RNDN);
  if (mpfr_cmp(accur,temp) < 0) {
    mpfr_clear(temp);
    return 0;
  }
  mpfr_clear(temp);

  mpfr_init2(currAccur,mpfr_get_prec(accur));

  p = minprec;
  if ((mpfr_get_prec(y) + 10) > minprec) minprec = mpfr_get_prec(y) + 10;

  res = 0; okay = 0;
  while (p <= maxprec) {
    mpfr_init2(currY,p);
    mpfr_init2(currX,p);
    mpfr_set(currX,x,GMP_RNDN);
    res = evaluateWithAccuracyEstimate(func, currX, currY, currAccur, p);
    mpfr_clear(currX);

    if (res && (mpfr_cmp(currAccur,accur) <= 0)) {
      mpfr_init2(resY,mpfr_get_prec(currY));
      mpfr_set(resY,currY,GMP_RNDN);
      mpfr_clear(currY);
      okay = 1;
      break;
    }
    mpfr_clear(currY);
    p *= 2;
  }
  
  if (okay) {
    mpfr_set(y,resY,GMP_RNDN);
    mpfr_clear(resY);
    if (needPrec != NULL) {
      *needPrec = p;
    }
  }

  mpfr_clear(currAccur);
  return okay;
}


int evaluateFaithfulOrFail(node *func, mpfr_t x, mpfr_t y, unsigned int precFactor, mp_prec_t *needPrec) {
  mp_prec_t startPrec, endPrec, p;
  mpfr_t accur;
  int res;

  p = mpfr_get_prec(y);
  startPrec = p + 10;
  endPrec = startPrec * precFactor;

  mpfr_init2(accur,startPrec);
  mpfr_set_d(accur,1.0,GMP_RNDN);
  mpfr_div_2ui(accur,accur,p,GMP_RNDD);

  res = evaluateWithAccuracy(func, x, y, accur, startPrec, endPrec, needPrec);
  
  mpfr_clear(accur);
  
  return res;
}

int evaluateFaithful(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec) {
  mp_prec_t startPrec, p;
  mpfr_t cutoff;
  int res;

  p = mpfr_get_prec(result);
  startPrec = p + 10;
  if (prec > startPrec) startPrec = prec;

  mpfr_init2(cutoff,startPrec);
  mpfr_set_d(cutoff,0.0,GMP_RNDN);

  res = evaluateFaithfulWithCutOffFast(result, tree, NULL, x, cutoff, startPrec);
  
  mpfr_clear(cutoff);

  if (!res) {
    printMessage(4,"Warning: evaluateFaithful returned NaN.\n");
    mpfr_set_nan(result);
  }

  return res;

}

int determineHeuristicTaylorRecursions(node *func) {
  int highestDegree, sizeOfFunc, sizeOfCurrDeriv, i;
  node *temp, *temp2;

  highestDegree = highestDegreeOfPolynomialSubexpression(func);

  sizeOfFunc = treeSize(func);

  temp = differentiate(func);
  sizeOfCurrDeriv = treeSize(temp);
  i = -1;

  while ((highestDegree >= 0) && (((double) sizeOfCurrDeriv) <= ((double) 4) * ((double) sizeOfFunc))) {
    temp2 = differentiate(temp);
    free_memory(temp);
    temp = temp2;
    sizeOfCurrDeriv = treeSize(temp);
    i++;
    highestDegree--;
  }
  
  free_memory(temp);

  return i < 0 ? 0 : i;
}



int accurateInfnorm(mpfr_t result, node *func, rangetype range, chain *excludes, mp_prec_t startPrec) {
  rangetype res;
  mpfi_t rangeI, resI;
  mpfi_t *excludeI;
  node *deriv, *numeratorDeriv, *derivNumeratorDeriv, *denominatorDeriv, *derivDenominatorDeriv;
  mpfr_t rangeDiameter, z, ya,yb;
  chain *curr, *initialExcludes;
  int newtonWorked;
  mp_prec_t p, p2, prec;
  mpfr_t startDiam, currDiameter, resultUp, resultDown, stopDiameter;
  int okay, oldtaylorrecursions, t;

  
  prec = startPrec;
  p = mpfr_get_prec(result);

  mpfr_init2(resultUp,p);
  mpfr_init2(resultDown,p);

  if (p > prec) {
    prec = p;
    printMessage(1,"Warning: starting intermediate precision increased to %d bits.\n",prec);
  }

  res.a = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  res.b = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(res.a),prec);
  mpfr_init2(*(res.b),prec);

  if (isTrivialInfnormCase(res, func)) {
    printMessage(2,"Information: the infnorm on the given function is trivially calculable.\n");
    mpfr_set(result,*(res.a),GMP_RNDU);
    mpfr_clear(*(res.a));
    mpfr_clear(*(res.b));
    free(res.a);
    free(res.b);
    return 1;
  }

  oldtaylorrecursions = taylorrecursions;
  t = determineHeuristicTaylorRecursions(func);
  if ((t > oldtaylorrecursions) && (t < ((oldtaylorrecursions + 1) * 2))) {
    taylorrecursions = t;
    printMessage(3,"Information: the number of Taylor recursions has temporarily been set to %d.\n",taylorrecursions);
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

  mpfr_init2(startDiam,prec);
  mpfr_set_d(startDiam,DEFAULTDIAM,GMP_RNDD);

  mpfr_mul(rangeDiameter,rangeDiameter,startDiam,GMP_RNDD);
  
  mpfr_clear(startDiam);

  mpfi_interv_fr(rangeI,*(range.a),*(range.b));
  deriv = differentiate(func);

  if (getNumeratorDenominator(&numeratorDeriv,&denominatorDeriv,deriv)) {
    printMessage(1,"Warning: the derivative of the function is a quotient, thus possibly not continuous in the interval.\n");
    printMessage(1,"Only the zeros of the numerator will be searched and pole detection may fail.\n");
    printMessage(1,"Be sure that the function is twice continuously differentiable if trusting the infnorm result.\n");

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
	printMessage(1,"Warning: the derivative of the function seems to have a extensible singularity in ");
	if (verbosity >= 1) printValue(&z,prec);
	printMessage(1,".\n");
	printMessage(1,"The infnorm result might not be trustful if the derivative cannot actually\n");
	printMessage(1,"be extended in this point.\n");
      } else {
	printMessage(1,"Warning: the derivative of the function seems to have a singularity in ");
	if (verbosity >= 1) printValue(&z,prec);
	printMessage(1,".\n");
	printMessage(1,"The infnorm result is likely to be wrong.\n");
      }
    } else {
      evaluate(ya,denominatorDeriv,*(range.a),prec);
      evaluate(yb,denominatorDeriv,*(range.b),prec);

      if (mpfr_sgn(ya) != mpfr_sgn(yb)) {
	printMessage(1,"Warning: the derivative of the function seems to have a (extensible) singularity in the considered interval.\n");
	printMessage(1,"The infnorm result might be not trustful if the function is not continuously differentiable.\n");
      } else {
	printMessage(2,"Information: the derivative seems to have no (false) pole in the considered interval.\n");
      }
    }

    mpfr_clear(z);
    mpfr_clear(ya);
    mpfr_clear(yb);
    free_memory(derivDenominatorDeriv);
    free_memory(denominatorDeriv);
  }
  derivNumeratorDeriv = differentiate(numeratorDeriv);

  mpfr_init2(currDiameter, prec);
  mpfr_init2(stopDiameter, prec);

  mpfr_div_2ui(stopDiameter,rangeDiameter,20,GMP_RNDD);

  okay = 0;

  while (prec <= 512 * startPrec) {

    mpfr_set(currDiameter,rangeDiameter,GMP_RNDD);

    while (mpfr_cmp(currDiameter,stopDiameter) >= 0) {

      infnormI(resI,func,deriv,numeratorDeriv,derivNumeratorDeriv,rangeI,
	       prec,currDiameter,initialExcludes,NULL,NULL);
    
      mpfi_revert_if_needed(resI);
      mpfi_get_left(resultDown,resI);
      mpfi_get_right(resultUp,resI);

      if (mpfr_cmp(resultDown,resultUp) == 0) {
	okay = 1;
	break;
      }

      mpfr_nextabove(resultDown);

      if (mpfr_cmp(resultDown,resultUp) == 0) {
	okay = 1;
	break;
      }
    
      mpfr_div_2ui(currDiameter,currDiameter,2,GMP_RNDD);

      printMessage(4,"Information: the absolute diameter is now ");
      if (verbosity >= 4) {
	printMpfr(currDiameter);
      }
      printMessage(4,"The current intermediate precision is %d bits.\n",(int) prec);

    }

    if (okay) break;

    prec *= 2;

    printMessage(4,"Information: the intermediate precision is now %d bits.\n",(int) prec);

  }

  if (okay) mpfr_set(result,resultUp,GMP_RNDU);

  mpfr_clear(stopDiameter);
  mpfr_clear(currDiameter);
  free_memory(deriv);
  free_memory(numeratorDeriv);
  free_memory(derivNumeratorDeriv);
  mpfi_clear(rangeI);
  mpfi_clear(resI);
  mpfr_clear(rangeDiameter);
  mpfr_clear(resultUp);
  mpfr_clear(resultDown);

  taylorrecursions = oldtaylorrecursions;

  return okay;
}


int evaluateFaithfulWithCutOffFast(mpfr_t result, node *func, node *deriv, mpfr_t x, mpfr_t cutoff, mp_prec_t startprec) {
  mp_prec_t p, prec, oldPrec, oldPrec2;
  rangetype xrange, yrange;
  int okay;
  mpfr_t resUp, resDown;


  prec = mpfr_get_prec(result);
  p = mpfr_get_prec(x);
  if (p > prec) prec = p;
  if (startprec > prec) prec = startprec;

  oldPrec = tools_precision;
  oldPrec2 = defaultprecision;

  tools_precision = prec;
  defaultprecision = prec;

  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  
  mpfr_init2(resUp,prec);
  mpfr_init2(resDown,prec);

  yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));

  p = 4 * prec;
  okay = 0;
  while (p < prec * 512) {
    mpfr_init2(*(yrange.a),p);
    mpfr_init2(*(yrange.b),p);
    mpfr_init2(*(xrange.a),p);
    mpfr_init2(*(xrange.b),p);
    mpfr_set(*(xrange.a),x,GMP_RNDD);
    mpfr_set(*(xrange.b),x,GMP_RNDU);
    evaluateRangeFunctionFast(yrange, func, deriv, xrange, p);
    mpfr_set(resDown,*(yrange.a),GMP_RNDN);
    mpfr_set(resUp,*(yrange.b),GMP_RNDN);
    if (mpfr_cmp(resDown,resUp) == 0) 
      okay = 1;
    mpfr_nextabove(resDown);
    if (mpfr_cmp(resDown,resUp) == 0) 
      okay = 1;
    if (okay == 0) {
      if ((mpfr_cmpabs(*(yrange.a),cutoff) < 0) && (mpfr_cmpabs(*(yrange.b),cutoff) < 0)) {
	mpfr_add(*(yrange.a),*(yrange.b),*(yrange.a),GMP_RNDN);
	mpfr_div_2ui(*(yrange.a),*(yrange.a),1,GMP_RNDN);
	mpfr_set(resUp,*(yrange.a),GMP_RNDN);
	okay = 2;
      } 
    }
    mpfr_clear(*(yrange.a));
    mpfr_clear(*(yrange.b));
    mpfr_clear(*(xrange.a));
    mpfr_clear(*(xrange.b));
    if (okay > 0) break;
    p *= 2;
  }

  if (okay > 0) {
    mpfr_set(result,resUp,GMP_RNDN);
  } else {
    mpfr_set_nan(result);
  }
  
  free(yrange.a);
  free(yrange.b);
  free(xrange.a);
  free(xrange.b);

  mpfr_clear(resUp);
  mpfr_clear(resDown);


  tools_precision = oldPrec;
  defaultprecision = oldPrec2;

  return okay;
}

int evaluateFaithfulWithCutOff(mpfr_t result, node *func, mpfr_t x, mpfr_t cutoff, mp_prec_t startprec) {
  node *deriv;
  int res;

  if ((2*startprec) < (mpfr_get_prec(result) + 10)) {
    printMessage(12,"Information: Differentiating while evaluating because start precision (%d bits) too low.\n",
		 (int)startprec);
    deriv = differentiate(func); 
  }else deriv = NULL;
  res = evaluateFaithfulWithCutOffFast(result, func, deriv, x, cutoff, startprec);
  if (deriv != NULL) free_memory(deriv);
  return res;
}
