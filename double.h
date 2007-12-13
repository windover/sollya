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

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
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
knowledge of the CeCILL license and that you accept its terms.

*/

#ifndef DOUBLE_H
#define DOUBLE_H

#include <mpfr.h>
#include "expression.h"
#include "chain.h"

int round_to_format(mpfr_t rop, mpfr_t op, int prec, mp_rnd_t mode);
int mpfr_round_to_double(mpfr_t rop, mpfr_t op);
int mpfr_round_to_doubledouble(mpfr_t rop, mpfr_t op);
int mpfr_round_to_tripledouble(mpfr_t rop, mpfr_t op);
int mpfr_round_to_doubleextended(mpfr_t rop, mpfr_t op);
int printDoubleInHexa(mpfr_t x);
int printSimpleInHexa(mpfr_t x);
int readHexa(mpfr_t res, char *c);
node *roundPolynomialCoefficients(node *poly, chain *formats, mp_prec_t prec);
int printDoubleExpansion(mpfr_t x);
int printPolynomialAsDoubleExpansion(node *poly, mp_prec_t prec);
void mpfr_round_to_format(mpfr_t rop, mpfr_t op, int format);
int mpfr_mant_exp(mpfr_t rop, mp_exp_t *expo, mpfr_t op);
int roundRangeCorrectly(mpfr_t rop, mpfr_t a, mpfr_t b);

#endif /* ifdef DOUBLE_H*/
