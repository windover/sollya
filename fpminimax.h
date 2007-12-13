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

#ifndef FPMINIMAX_H
#define FPMINIMAX_H


#include <stdio.h>
#include <mpfr.h>
#include "expression.h"
#include "chain.h"


#define DOUBLE_FORMAT 1
#define DOUBLEDOUBLE_FORMAT 2
#define TRIPLEDOUBLE_FORMAT 3
#define PRECISION_FORMAT 4
#define MI_FORMAT 5
#define TI_FORMAT 6

#define ABSOLUTE_ERROR 1 
#define RELATIVE_ERROR 2
#define WEIGHTFUNCTION_ERROR 3

#define EQUI_POINTS 1
#define CHEB_POINTS 2
#define REMEZ_POINTS 3
#define USER_POINTS 4


typedef struct formatStruct formatType;

struct formatStruct 
{
  int formatType;
  int prec;
  mpfr_t *tiValue;
};

typedef struct errorStruct errorType;

struct errorStruct 
{
  int errorType;
  node *weightFunction;
};

typedef struct pointsStruct pointsType;

struct pointsStruct 
{
  int pointsType;
  chain *pointsList;
};


node *rationalApprox(mpfr_t x, unsigned int n);
node *fpminimax(node *expr, chain *monomials, chain *formats, mpfr_t a, mpfr_t b, 
		errorType *error, pointsType *points, int quality, FILE *fd);

void freeFormatTypePtr(void *ptr);
void freeErrorTypePtr(void *ptr);
void freePointsTypePtr(void *ptr);
void freeMpfrPtr(void *ptr);


#endif /* ifdef FPMINIMAX_H*/
