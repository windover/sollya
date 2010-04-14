/*

Copyright 2009-2010 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

and by

LORIA (CNRS, INPL, INRIA, UHP, U-Nancy 2)

Contributors S. Chevillard, M. Joldes

sylvain.chevillard@ens-lyon.fr
mioara.joldes@ens-lyon.fr

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

#ifndef TAYLORFORM_H
#define TAYLORFORM_H

#include "expression.h"
#include "chain.h"

void boundTranslatedPolynomialByHorner(mpfi_t bound, int n, mpfi_t *coeffs, mpfi_t x0, mpfi_t I);
void polynomialBoundSharp(mpfi_t *bound, int n, mpfi_t *coeffs, mpfi_t x0, mpfi_t I);

/* This function transforms a polynomial with interval coeffs
   into a poly with mpfr coeffs and a small remainder */
void mpfr_get_poly(mpfr_t *rc, mpfi_t *errors_array, mpfi_t rest, int n, mpfi_t *p, mpfi_t x0, mpfi_t x);

/* Taylor model structure:
     n - order: polynomial of degree n-1, remainder of order O(x^n)
     rem_bound - bound for the remainder f-T
     poly_array - array of coeffs for the polynomial (mpfi's) in basis (x-x0)
     poly_bound - bound for the polynomial (helpful for computations)
     x - interval on which the tm is computed
     x0 - interval around the expansion point
*/
typedef struct tmdl {
int n; 
mpfi_t rem_bound;
mpfi_t *poly_array;
mpfi_t poly_bound;
mpfi_t x;
mpfi_t x0;

} tModel;

tModel* createEmptytModel(int n,  mpfi_t x0, mpfi_t x);
void cleartModel(tModel *t);
void copytModel(tModel *t, tModel *tt);
void printtModel(tModel *t);

void consttModel(tModel*t, mpfi_t ct); 
void addition_TM(tModel *t,tModel *t1, tModel *t2, int mode);
void ctMultiplication_TM(tModel*d, tModel*s, mpfi_t c, int mode);
void multiplication_TM(tModel *t, tModel *t1, tModel *t2, int mode);

void composition_TM(tModel *t,tModel *g, tModel *f, int mode);

void taylorform(node **T, chain **errors, mpfi_t **delta,
		node *f, int n, mpfi_t *x0, mpfi_t *d, int mode);

#endif /* TAYLORFORM_H */
