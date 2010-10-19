/*

Copyright 2007-2010 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

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

/* TODO: normalize [NaN, 1] to [Nan, NaN] */

void sollya_mpfi_nan_normalize(sollya_mpfi_t rop) {
  /* HACK ALERT: For performance reasons, we will access the internals
     of an mpfi_t !!!
  */
  if (mpfr_nan_p(&(rop->left))) mpfr_set(&(rop->right),&(rop->left),GMP_RNDN);
  else if (mpfr_nan_p(&(rop->right))) mpfr_set(&(rop->left),&(rop->right),GMP_RNDN);
}

int sollya_mpfi_abs(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_abs(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_acos(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_acos(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_acosh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_acosh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_add(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_add(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_add_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  res = mpfi_add_ui(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_asin(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_asin(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_asinh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_asinh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_atan(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_atan(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_atanh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_atanh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_blow(sollya_mpfi_t rop, sollya_mpfi_t op1, double op2) {
  int res;

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

  res = mpfi_cos(rop,op);
  /* If op contains Nan -> returns Nan */
  /* If op contains Infty -> returns [-1,1] */

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_cosh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_cosh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_diam(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_diam(rop,op);

  return res;
}


int sollya_mpfi_diam_abs(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_diam_abs(rop,op);

  return res;
}


int sollya_mpfi_div(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_div(rop,op1,op2);
  /* 0/0 -> NaN 
     0/anything else -> 0
     anything else / something containing 0 (inside) -> [-Inf, Inf]
     anything / [0,b] -> limit of anything/[eps, b] when eps->0
     idem with [a,0]
     1/[-Inf, -Inf] -> 0
     [-Inf,+Inf]/[-Inf, -Inf] -> 0
     idem of [Inf, Inf]
     [Inf, Inf]/[-Inf, -Inf] -> NaN
     [-Inf, -Inf]/[-Inf, -Inf] -> NaN
  */

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_div_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  res = mpfi_div_ui(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_exp(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_exp(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_expm1(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_expm1(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_get_left(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_get_left(rop,op);

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

  res = mpfi_has_zero(op);

  return res;
}


int sollya_mpfi_inf_p(sollya_mpfi_t op) {
  int res;

  res = mpfi_inf_p(op);

  return res;
}


void sollya_mpfi_init2(sollya_mpfi_t rop, mp_prec_t op) {
  mpfi_init2(rop,op);
}


int sollya_mpfi_intersect(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_intersect(rop,op1,op2);

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

  res = mpfi_inv(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_is_inside(sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_is_inside(op1,op2);

  return res;
}


int sollya_mpfi_is_nonneg(sollya_mpfi_t op) {
  int res;

  res = mpfi_is_nonneg(op);

  return res;
}


int sollya_mpfi_is_nonpos(sollya_mpfi_t op) {
  int res;

  res = mpfi_is_nonpos(op);

  return res;
}


int sollya_mpfi_is_pos(sollya_mpfi_t op) {
  int res;

  res = mpfi_is_pos(op);

  return res;
}


int sollya_mpfi_is_zero(sollya_mpfi_t op) {
  int res;

  res = mpfi_is_zero(op);

  return res;
}


int sollya_mpfi_log(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_log(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log10(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_log10(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log1p(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_log1p(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_log2(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_log2(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_mid(mpfr_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_mid(rop,op);

  return res;
}


int sollya_mpfi_mul(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_mul(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_mul_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

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

  res = mpfi_sin(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sinh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_sinh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sqr(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_sqr(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sqrt(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_sqrt(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_sub(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub_fr(sollya_mpfi_t rop, sollya_mpfi_t op1, mpfr_t op2) {
  int res;

  res = mpfi_sub_fr(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_sub_ui(sollya_mpfi_t rop, sollya_mpfi_t op1, unsigned long op2) {
  int res;

  res = mpfi_sub_ui(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_tan(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_tan(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_tanh(sollya_mpfi_t rop, sollya_mpfi_t op) {
  int res;

  res = mpfi_tanh(rop,op);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_ui_div(sollya_mpfi_t rop, unsigned long op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_ui_div(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


int sollya_mpfi_union(sollya_mpfi_t rop, sollya_mpfi_t op1, sollya_mpfi_t op2) {
  int res;

  res = mpfi_union(rop,op1,op2);

  sollya_mpfi_nan_normalize(rop);

  return res;
}


