/*

Copyright 2007-2010 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

and

Laboratoire d'Informatique de Paris 6, equipe PEQUAN,
UPMC Universite Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France.

Contributors Ch. Lauter, S. Chevillard

christoph.lauter@ens-lyon.org
sylvain.chevillard@ens-lyon.org

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

#include "mpfi-compat.h"

void sollya_mpfi_nan_normalize(sollya_mpfi_t rop) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if (mpfr_nan_p(&(rop->left))) mpfr_set(&(rop->right),&(rop->left),GMP_RNDN);
  else if (mpfr_nan_p(&(rop->right))) mpfr_set(&(rop->left),&(rop->right),GMP_RNDN);
}

int sollya_mpfi_test_emptyset(int *res, sollya_mpfi_t rop, sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if ((!mpfi_nan_p(op)) && 
      (mpfr_cmp(&(op->left),&(op->right)) > 0)) {
    mpfr_set_inf(&(rop->left),1);
    mpfr_set_inf(&(rop->right),-1);
    *res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    return 1;
  } 

  return 0;
}

int mpfrIsPositiveInfinity(mpfr_t op) {
  return (mpfr_inf_p(op) && (mpfr_sgn(op) > 0));
}

int mpfrIsNegativeInfinity(mpfr_t op) {
  return (mpfr_inf_p(op) && (mpfr_sgn(op) < 0));
}

int sollyaMpfiHasPositiveNumbers(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return ((!mpfi_nan_p(op)) && 
	  (mpfr_cmp(&(op->left),&(op->right)) <= 0) &&
	  (mpfr_sgn(&(op->right)) > 0));
}

int sollyaMpfiHasNegativeNumbers(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return ((!mpfi_nan_p(op)) && 
	  (mpfr_cmp(&(op->left),&(op->right)) <= 0) &&
	  (mpfr_sgn(&(op->left)) < 0));
}

int sollyaMpfiHasPositiveInfinity(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return (mpfrIsPositiveInfinity(&(op->left)) || mpfrIsPositiveInfinity(&(op->right)));
}

int sollyaMpfiIsPositiveInfinity(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return (mpfrIsPositiveInfinity(&(op->left)) && mpfrIsPositiveInfinity(&(op->right)));
}

int sollyaMpfiHasNegativeInfinity(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return (mpfrIsNegativeInfinity(&(op->left)) || mpfrIsNegativeInfinity(&(op->right)));
}

int sollyaMpfiIsNegativeInfinity(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return (mpfrIsNegativeInfinity(&(op->left)) && mpfrIsNegativeInfinity(&(op->right)));
}

int sollyaMpfiHasZero(sollya_mpfi_t op) {
  return ((!mpfi_nan_p(op)) && mpfi_has_zero(op));
}

int sollyaMpfiIsZero(sollya_mpfi_t op) {
  return ((!mpfi_nan_p(op)) && mpfi_is_zero(op));
}

int sollyaMpfiHasNaN(sollya_mpfi_t op) {
  return mpfi_nan_p(op);
}

int sollyaMpfiHasZeroInside(sollya_mpfi_t op) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  return ((!(mpfr_nan_p(&(op->left)) || mpfr_nan_p(&(op->right)))) && ((mpfr_sgn(&(op->left)) * mpfr_sgn(&(op->right))) < 0));
}

int sollyaMpfiHasInfinity(sollya_mpfi_t op) {
  return ((!mpfi_nan_p(op)) && mpfi_inf_p(op));
}

int sollyaMpfiIsInfinity(sollya_mpfi_t op) {
  return (sollyaMpfiIsPositiveInfinity(op) || sollyaMpfiIsNegativeInfinity(op));
}

int sollya_mpfi_abs(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_abs(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_acos(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_acos(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_acosh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_acosh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_add(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;
  if (sollya_mpfi_test_emptyset(&res, rop, op2)) return res;

  res = mpfi_add(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_add_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;

  res = mpfi_add_ui(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_asin(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_asin(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_asinh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_asinh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_atan(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_atan(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_atanh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_atanh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_blow(sollya_mpfi_t rop, sollya_mpfi_t op1, double op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;

  res = mpfi_blow(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_bounded_p(sollya_mpfi_t op) {
  int res;

  res = mpfi_bounded_p(op);

  return res;
}


void sollya_mpfi_clear(sollya_mpfi_t op) {
  mpfi_clear(op);
}


int sollya_mpfi_const_pi(sollya_mpfi_t rop) {
  int res;

  res = mpfi_const_pi(rop);

  return res;
}


int sollya_mpfi_cos(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasInfinity(op) && (!sollyaMpfiHasNaN(op))) {
    mpfi_interv_si(rop,-1,1);
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    res = mpfi_cos(rop,op);
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_cosh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_cosh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_diam(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if ((!mpfi_nan_p(op)) && 
      (mpfr_cmp(&(op->left),&(op->right)) > 0)) {
    mpfr_set_nan(rop);
    return 0;
  }

  res = mpfi_diam(rop,op);

  return res;
}


int sollya_mpfi_diam_abs(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if ((!mpfi_nan_p(op)) && 
      (mpfr_cmp(&(op->left),&(op->right)) > 0)) {
    mpfr_set_nan(rop);
    return 0;
  }

  res = mpfi_diam_abs(rop,op);

  return res;
}


int sollya_mpfi_div(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;
  int sign;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;
  if (sollya_mpfi_test_emptyset(&res, rop, op2)) return res;

  /* Cases for the division:
     # op1 = NaN or op2 = NaN -> NaN
     # op1 empty or op2 empty -> empty
     # If op1 = [0] :
         # If op2 = [0] -> NaN
         # Else -> [0]    the argument here is: even if op2 contains 0,
                                                the function op1/y is 0 everywhere
                                                so we define it at y=0 by
                                                continuity.
     # If op1 = [+Inf] or op1 = [-Inf] :
         # If op2 = [+Inf] or op2 = [-Inf] -> NaN
         # If op2 does not contain 0 -> sgn(op2)*Inf  the argument is: even
                                                      if op2 contains an Inf,
                                                      the function op1/y is constant
                                                      to Inf everywhere, so we
                                                      define it at Inf as this constant.
         # Else -> [-Inf, Inf]     this holds even when op2=[0]. The argument here is:
                                   Inf/[0] is an Inf but we do not know its sign. So
                                   we return [-Inf, Inf] and we are sure.

     Now, we know that op1 is neither [0], nor [-Inf] or [+Inf]
     #  If op2 = [0] -> [-Inf, Inf]    the argument here is: even if op1 contains 0,
                                      x/[0] is always -Inf or +Inf, hence we
                                      define it at 0 by continuity as -Inf or +Inf.
                                      Sadly, we do not know the sign of 0, so we have
                                      to return [-Inf, +Inf] as a result
     # If op2 = [-Inf] or [+Inf] -> [0]     (even if op1 contains 0: by continuity)

     Now, we know that neither op1 nor op2 are singular point intervals
     # If op2 does not contain 0 -> mpfi_div(op1, op2)
     # If op2 has 0 inside -> [-Inf, +Inf]
     # If op2 = [0, b] :
         # If op1 = [u, v] with 0<=u ->  [u/b, +Inf]
         # If op1 = [u, v] with v<=0 ->  [-Inf, v/b]
         # Else -> [-Inf, +Inf]
     # Else (op2 = [a, 0]) :
         # If op1 = [u, v] with 0<=u ->  [-Inf, u/a]
         # If op1 = [u, v] with v<=0 ->  [v/a, +Inf]
         # Else -> [-Inf, +Inf]
  */     
  if (sollyaMpfiHasNaN(op1) || sollyaMpfiHasNaN(op2)) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    if (sollyaMpfiIsZero(op1)) {
      // Here op1 = [0]
      //
      if (sollyaMpfiIsZero(op2)) {
	// Here [0] / [0]
	//
	/* HACK ALERT: For performance reasons, we will access the internals
	   of an mpfi_t !!!
	*/
	mpfr_set_nan(&(rop->left));
	mpfr_set_nan(&(rop->right));
	res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
      } else {
	// Here op1 = [0], op2 != [0], op2 != [NaN]
	//
	// Return [0]
	//
	res = mpfi_set_si(rop,0);
      }
    } else {
      // Here op1 != [0]
      //
      if (sollyaMpfiIsInfinity(op1)) {
	// Here op1 = [+/-Inf]
	//
	if (sollyaMpfiIsInfinity(op2)) {
	  // Here op1 = [+/-Inf], op2 = [+/-Inf]
	  //
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_nan(&(rop->left));
	  mpfr_set_nan(&(rop->right));
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  // Here op1 = [+/-Inf], op2 != [+/-Inf]
	  //
	  if (sollyaMpfiHasZero(op2)) {
	    // Here op1 = [+/-Inf], op2 != [+/-Inf], 0 \in op2
	    //
	    res = mpfi_set(rop,op1);
	  } else {
	    // Here op1 = [+/-Inf], op2 != [+/-Inf], 0 \not \in op2
	    //
	    sign = (sollyaMpfiHasPositiveNumbers(op2) ? +1 : -1);
	    res = mpfi_mul_si(rop,op1,sign);
	  }
	}
      } else {
	// Here op1 != [0], op1 != [+/-Inf]
	//
	if (sollyaMpfiIsZero(op2)) {
	  // Here op1 != [0], op1 != [+/-Inf], op2 = [0]
	  //
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_set_inf(&(rop->right),+1);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  // Here op1 != [0], op1 != [+/-Inf], op2 != [0]
	  //
	  if (sollyaMpfiIsInfinity(op2)) {
	    // Here op1 != [0], op1 != [+/-Inf], op2 = [+/-Inf]
	    //
	    res = mpfi_set_si(rop,0);
	  } else {
	    // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
	    //
	    if (sollyaMpfiHasZero(op2)) {
	      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
	      // 0 \in op2
	      //
	      if (sollyaMpfiHasZeroInside(op2)) {
		// Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		// 0 \in op2
		// \exists a,b; a < 0 < b; op2 = [a;b]
		//
		/* HACK ALERT: For performance reasons, we will access the internals
		   of an mpfi_t !!!
		*/
		mpfr_set_inf(&(rop->left),-1);
		mpfr_set_inf(&(rop->right),+1);
		res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	      } else {
		// Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		// 0 \in op2
		// \not ( \exists a,b; a < 0 < b; op2 = [a;b] )
		//
		if (sollyaMpfiHasPositiveNumbers(op2)) {
		  // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		  // 0 \in op2
		  // \exists b; b > 0; op2 = [0;b]
		  //
		  /* HACK ALERT: For performance reasons, we will access the internals
		     of an mpfi_t !!!
		  */
		  if (mpfr_sgn(&(op1->left)) >= 0) {
		    // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		    // 0 \in op2
		    // \exists b; b > 0; op2 = [0;b]
		    // \exists u; u >= 0; op1 = [u;v]
		    //
		    mpfr_set_inf(&(rop->right),1);
		    if (mpfr_div(&(rop->left),&(op1->left),&(op2->right),GMP_RNDD) == 0) {
		      res = MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
		    } else {
		      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		    }
		  } else {
		    // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		    // 0 \in op2
		    // \exists b; b > 0; op2 = [0;b]
		    // \not (\exists u; u >= 0; op1 = [u;v])
		    //
		    /* HACK ALERT: For performance reasons, we will access the internals
		       of an mpfi_t !!!
		    */
		    if (mpfr_sgn(&(op1->right)) <= 0) {
		      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		      // 0 \in op2
		      // \exists b; b > 0; op2 = [0;b]
		      // \exists v; v<= 0; op1 = [u;v])
		      //
		      mpfr_set_inf(&(rop->left),-1);
		      if (mpfr_div(&(rop->right),&(op1->right),&(op2->right),GMP_RNDU) == 0) {
			res = MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
		      } else {
			res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		      }
		    } else {
		      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		      // 0 \in op2
		      // \exists b; b > 0; op2 = [0;b]
		      // \exists u,v; u < 0 < v; op1 = [u;v])
		      //
		      /* HACK ALERT: For performance reasons, we will access the internals
			 of an mpfi_t !!!
		      */
		      mpfr_set_inf(&(rop->left),-1);
		      mpfr_set_inf(&(rop->right),+1);
		      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		    }
		  }
		} else {
		  // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		  // 0 \in op2
		  // \exists a; a < 0; op2 = [a;0]
		  //
		  /* HACK ALERT: For performance reasons, we will access the internals
		     of an mpfi_t !!!
		  */
		  if (mpfr_sgn(&(op1->left)) >= 0) {
		    // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		    // 0 \in op2
		    // \exists a; a < 0; op2 = [a;0]
		    // \exists u; u >= 0; op1 = [u;v]
		    //
		    mpfr_set_inf(&(rop->left),-1);
		    if (mpfr_div(&(rop->right),&(op1->left),&(op2->left),GMP_RNDU) == 0) {
		      res = MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
		    } else {
		      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		    }
		  } else {
		    // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		    // 0 \in op2
		    // \exists a; a < 0; op2 = [a;0]
		    // \not (\exists u; u >= 0; op1 = [u;v])
		    //
		    /* HACK ALERT: For performance reasons, we will access the internals
		       of an mpfi_t !!!
		    */
		    if (mpfr_sgn(&(op1->right)) <= 0) {
		      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		      // 0 \in op2
		      // \exists a; a < 0; op2 = [a;0]
		      // \exists v; v<= 0; op1 = [u;v])
		      //
		      mpfr_set_inf(&(rop->right),1);
		      if (mpfr_div(&(rop->left),&(op1->right),&(op2->left),GMP_RNDD) == 0) {
			res = MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
		      } else {
			res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		      }
		    } else {
		      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
		      // 0 \in op2
		      // \exists a; a < 0; op2 = [a;0]
		      // \exists u,v; u < 0 < v; op1 = [u;v])
		      //
		      /* HACK ALERT: For performance reasons, we will access the internals
			 of an mpfi_t !!!
		      */
		      mpfr_set_inf(&(rop->left),-1);
		      mpfr_set_inf(&(rop->right),+1);
		      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
		    }
		  }
		}
	      }
	    } else {
	      // Here op1 != [0], op1 != [+/-Inf], op2 != [0], op2 != [+/-Inf]
	      // 0 \not \in op2
	      //
	      res = mpfi_div(rop,op1,op2);
	    }
	  }
	}
      }
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_div_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;
  mpfi_t temp;

  mpfi_init2(temp,8 * sizeof(op2));
  mpfi_set_ui(temp,op2);

  res = sollya_mpfi_div(rop,op1,temp);

  mpfi_clear(temp);

  return res;
}


int sollya_mpfi_exp(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_exp(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_expm1(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_expm1(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_get_left(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_get_left(rop,op);

  return res;
}

int sollya_mpfi_get_fr(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_get_fr(rop,op);

  return res;
}

mp_prec_t sollya_mpfi_get_prec(sollya_mpfi_t op) {
  mp_prec_t res;

  res = mpfi_get_prec(op);

  return res;
}


int sollya_mpfi_get_right(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_get_right(rop,op);

  return res;
}


char * sollya_mpfi_get_version() {
  char *res;

  res = mpfi_get_version();

  return res;
}


int sollya_mpfi_has_zero(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_has_zero(op));

  return res;
}


int sollya_mpfi_inf_p(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_inf_p(op));

  return res;
}


void sollya_mpfi_init2(sollya_mpfi_t rop, mp_prec_t op) {
  mpfi_init2(rop,op);
}


int sollya_mpfi_intersect(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;
  if (sollya_mpfi_test_emptyset(&res, rop, op2)) return res;

  if (sollyaMpfiHasNaN(op1) || sollyaMpfiHasNaN(op2)) {
      /* HACK ALERT: For performance reasons, we will access the internals
	 of an mpfi_t !!!
      */
      mpfr_set_nan(&(rop->left));
      mpfr_set_nan(&(rop->right));
      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    res = mpfi_intersect(rop,op1,op2);

    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    if ((!mpfi_nan_p(rop)) && 
	(mpfr_cmp(&(rop->left),&(rop->right)) > 0)) {
      mpfr_set_inf(&(rop->left),1);
      mpfr_set_inf(&(rop->right),-1);
      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_interv_d(sollya_mpfi_t rop, double op1, double op2) {
  int res;

  res = mpfi_interv_d(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_interv_fr(sollya_mpfi_t rop, mpfr_t op1, mpfr_t op2) {
  int res;

  res = mpfi_interv_fr(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_interv_si(sollya_mpfi_t rop, long op1, long op2) {
  int res;

  res = mpfi_interv_si(rop,op1,op2);

  return res;
}


int sollya_mpfi_inv(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;
  mpfi_t temp;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  mpfi_init2(temp,12);
  mpfi_set_si(temp,1);

  res = sollya_mpfi_div(rop,temp,op);

  mpfi_clear(temp);

  return res;
}


int sollya_mpfi_is_inside(sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if ((!mpfi_nan_p(op1)) && 
      (mpfr_cmp(&(op1->left),&(op1->right)) > 0)) {
    return 0;
  }

  if ((!mpfi_nan_p(op2)) && 
      (mpfr_cmp(&(op2->left),&(op2->right)) > 0)) {
    return 1;
  }

  res = ((!(mpfi_nan_p(op1) || mpfi_nan_p(op2))) && mpfi_is_inside(op1,op2));

  return res;
}


int sollya_mpfi_is_nonneg(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_is_nonneg(op));

  return res;
}


int sollya_mpfi_is_nonpos(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_is_nonpos(op));

  return res;
}


int sollya_mpfi_is_pos(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_is_pos(op));

  return res;
}


int sollya_mpfi_is_zero(sollya_mpfi_t op) {
  int res;

  res = ((!mpfi_nan_p(op)) && mpfi_is_zero(op));

  return res;
}


int sollya_mpfi_log(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasNaN(op)) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    if (sollyaMpfiHasZero(op)) {
      if (sollyaMpfiHasNegativeNumbers(op)) {
	/* HACK ALERT: For performance reasons, we will access the internals
	   of an mpfi_t !!!
	*/
	mpfr_set_nan(&(rop->left));
	mpfr_set_nan(&(rop->right));
	res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
      } else {
	if (sollyaMpfiIsZero(op)) {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_set_inf(&(rop->right),-1);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  if (mpfr_log(&(rop->right),&(op->right),GMP_RNDU) == 0) {
	    res = MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
	  } else {
	    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	  }
	}
      }
    } else {
      res = mpfi_log(rop,op);
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log10(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasNaN(op)) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    if (sollyaMpfiHasZero(op)) {
      if (sollyaMpfiHasNegativeNumbers(op)) {
	/* HACK ALERT: For performance reasons, we will access the internals
	   of an mpfi_t !!!
	*/
	mpfr_set_nan(&(rop->left));
	mpfr_set_nan(&(rop->right));
	res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
      } else {
	if (sollyaMpfiIsZero(op)) {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_set_inf(&(rop->right),-1);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  if (mpfr_log10(&(rop->right),&(op->right),GMP_RNDU) == 0) {
	    res = MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
	  } else {
	    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	  }
	}
      }
    } else {
      res = mpfi_log10(rop,op);
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log2(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasNaN(op)) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    if (sollyaMpfiHasZero(op)) {
      if (sollyaMpfiHasNegativeNumbers(op)) {
	/* HACK ALERT: For performance reasons, we will access the internals
	   of an mpfi_t !!!
	*/
	mpfr_set_nan(&(rop->left));
	mpfr_set_nan(&(rop->right));
	res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
      } else {
	if (sollyaMpfiIsZero(op)) {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_set_inf(&(rop->right),-1);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  if (mpfr_log2(&(rop->right),&(op->right),GMP_RNDU) == 0) {
	    res = MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
	  } else {
	    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	  }
	}
      }
    } else {
      res = mpfi_log2(rop,op);
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log1p(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res, gtMOne, eqMOne;
  mpfr_t tempMpfr;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasNaN(op)) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_init2(tempMpfr,12);
    mpfr_set_si(tempMpfr,-1,GMP_RNDN);
    gtMOne = (mpfr_cmp(&(op->left),tempMpfr) > 0);
    eqMOne = (mpfr_cmp(&(op->left),tempMpfr) == 0);
    if (!(gtMOne || eqMOne)) {
      /* HACK ALERT: For performance reasons, we will access the internals
	 of an mpfi_t !!!
      */
      mpfr_set_nan(&(rop->left));
      mpfr_set_nan(&(rop->right));
      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    } else {
      if (eqMOne) {
	/* HACK ALERT: For performance reasons, we will access the internals
	   of an mpfi_t !!!
	*/	
	if (mpfr_cmp(&(op->left),&(op->right)) == 0) {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_set_inf(&(rop->right),-1);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	} else {
	  /* HACK ALERT: For performance reasons, we will access the internals
	     of an mpfi_t !!!
	  */
	  mpfr_set_inf(&(rop->left),-1);
	  mpfr_log1p(&(rop->right),&(op->right),GMP_RNDU);
	  res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
	}
      } else {
	res = mpfi_log1p(rop,op);
      }
    }
    mpfr_clear(tempMpfr);
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_mid(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if ((!mpfi_nan_p(op)) && 
      (mpfr_cmp(&(op->left),&(op->right)) > 0)) {
    mpfr_set_nan(rop);
    return 0;
  }

  res = mpfi_mid(rop,op);

  return res;
}


int sollya_mpfi_mul(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  /* Theoretical cases for the multiplication (for the practical implementation, see below)
     # op1 = NaN or op2 = NaN -> NaN
     # op1 empty or op2 empty -> empty
     # If op1 = [0] :
         # If op2 = [-Inf] or [+Inf] -> NaN
         # Else -> [0]    the argument here is: even if op2 contains an Inf,
                                                the function op1*y is 0 everywhere
                                                so we define it at y=Inf by
                                                continuity.
     # If op1 = [+Inf] or op1 = [-Inf] :
         # If op2 = [0] -> NaN
         # If op2 does not contain 0 -> sgn(op1)*sgn(op2)*Inf
         # Else -> [-Inf, Inf]    The argument here is: Inf*y is an +/-Inf for
                                  every y. By continuity at y=0, we define it
                                  as an Inf (we do not know its sign however,
                                  but who cares: we return [-Inf, +Inf] anyway)

     Now, we know that op1 is neither [0], nor [-Inf] or [+Inf]
     # If op2 = [0] -> [0]  (because op1*op2 = op2*op1)
     # If op2 = [-Inf] or [+Inf] :
         # If op1 does not contain 0 -> sgn(op1)*sgn(op2)*Inf
         # Else -> [-Inf, +Inf]

     Now, we know that neither op1 nor op2 are singular point intervals
     # Else -> mpfi_mul(op1, op2)

     Practical implementation: we can expect that MPFI behaves well in most of the cases
     and use the following simple implementation which should be correct:
     
     # op1 = NaN or op2 = NaN -> NaN
     # op1 empty or op2 empty -> empty
     # If (op1 = [0]) and (op2 = [-Inf] or op2 = [+Inf]) -> NaN
     # If (op2 = [0]) and (op1 = [-Inf] or op1 = [+Inf]) -> NaN
     # Else -> mpfi_mul(op1, op2)
  */     

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;
  if (sollya_mpfi_test_emptyset(&res, rop, op2)) return res;

  if ((sollyaMpfiHasNaN(op1) || sollyaMpfiHasNaN(op2)) ||
      ((sollyaMpfiIsZero(op1) && sollyaMpfiIsInfinity(op2)) ||
       (sollyaMpfiIsZero(op2) && sollyaMpfiIsInfinity(op1)))) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_nan(&(rop->left));
    mpfr_set_nan(&(rop->right));
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    res = mpfi_mul(rop,op1,op2);
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_mul_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  /* WARNING: case (op1=[-Inf] or op1=[+Inf]) and (op2=0) to be checked */
  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;

  res = mpfi_mul_ui(rop,op1,op2);

  return res;
}


int sollya_mpfi_nan_p(sollya_mpfi_t op) {
  int res;

  res = mpfi_nan_p(op);

  return res;
}


int sollya_mpfi_neg(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_neg(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_revert_if_needed(sollya_mpfi_t rop) {
  int res;

  res = mpfi_revert_if_needed(rop);

  return res;
}


int sollya_mpfi_set(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_set(rop,op);

  return res;
}


int sollya_mpfi_set_d(sollya_mpfi_t rop, double op) {
  int res;

  res = mpfi_set_d(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_set_fr(sollya_mpfi_t rop, mpfr_t op) {
  int res;

  res = mpfi_set_fr(rop,op);

  return res;
}


void sollya_mpfi_set_prec(sollya_mpfi_t rop, mp_prec_t op) {
  mpfi_set_prec(rop,op);
}


int sollya_mpfi_set_q(sollya_mpfi_t rop, mpq_t op) {
  int res;

  res = mpfi_set_q(rop,op);

  return res;
}


int sollya_mpfi_set_si(sollya_mpfi_t rop, long op) {
  int res;

  res = mpfi_set_si(rop,op);

  return res;
}


int sollya_mpfi_set_ui(sollya_mpfi_t rop, unsigned long op) {
  int res;

  res = mpfi_set_ui(rop,op);

  return res;
}


int sollya_mpfi_sin(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasInfinity(op) && (!sollyaMpfiHasNaN(op))) {
    mpfi_interv_si(rop,-1,1);
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    res = mpfi_sin(rop,op);
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sinh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_sinh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sqr(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_sqr(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sqrt(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_sqrt(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;
  if (sollya_mpfi_test_emptyset(&res, rop, op2)) return res;

  res = mpfi_sub(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub_fr(sollya_mpfi_t rop, sollya_mpfi_t op1, mpfr_t op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;

  res = mpfi_sub_fr(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op1)) return res;

  res = mpfi_sub_ui(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_tan(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  if (sollyaMpfiHasInfinity(op) && (!sollyaMpfiHasNaN(op))) {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    mpfr_set_inf(&(rop->left),-1);
    mpfr_set_inf(&(rop->right),1);
    res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    res = mpfi_tan(rop,op);
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_tanh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  if (sollya_mpfi_test_emptyset(&res, rop, op)) return res;

  res = mpfi_tanh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}

int sollya_mpfi_ui_div(sollya_mpfi_t rop, unsigned long op1, sollya_mpfi_t op2) {
  int res;
  mpfi_t temp;

  mpfi_init2(temp,8 * sizeof(op1));
  mpfi_set_ui(temp,op1);

  res = sollya_mpfi_div(rop,temp,op2);

  mpfi_clear(temp);

  return res;
}

int sollya_mpfi_union(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  if (sollyaMpfiHasNaN(op1) || sollyaMpfiHasNaN(op2)) {
      /* HACK ALERT: For performance reasons, we will access the internals
	 of an mpfi_t !!!
      */
      mpfr_set_nan(&(rop->left));
      mpfr_set_nan(&(rop->right));
      res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
  } else {
    /* HACK ALERT: For performance reasons, we will access the internals
       of an mpfi_t !!!
    */
    if ((!mpfi_nan_p(op1)) && 
	(mpfr_cmp(&(op1->left),&(op1->right)) > 0)) {
      if ((!mpfi_nan_p(op2)) && 
	  (mpfr_cmp(&(op2->left),&(op2->right)) > 0)) {
	mpfr_set_inf(&(rop->left),1);
	mpfr_set_inf(&(rop->right),-1);
	res = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
      } else {
	res = mpfi_set(rop,op2);
      }
    } else {
      if ((!mpfi_nan_p(op2)) && 
	  (mpfr_cmp(&(op2->left),&(op2->right)) > 0)) {
	res = mpfi_set(rop,op1);
      } else {
	res = mpfi_union(rop,op1,op2);
      }
    }
  }

  sollya_mpfi_nan_normalize(rop);

  return res;
}


