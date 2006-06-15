#ifndef PROOF_H
#define PROOF_H


#include <mpfr.h>
#include <mpfi.h>
#include <stdio.h>
#include "expression.h"
#include "chain.h"


#define TAYLOR 1
#define HOPITAL_ON_POINT 2
#define NUMERATOR_IS_ZERO 3
#define HOPITAL 4
#define IMPLICATION 5
#define DECORRELATE 6

typedef struct exprBoundTheoStruct exprBoundTheo;

struct exprBoundTheoStruct
{
  node *function;
  int functionType;
  mpfi_t *x;
  mpfi_t *boundLeft;
  mpfi_t *boundRight;
  mpfi_t *y;
  exprBoundTheo *theoLeft;
  exprBoundTheo *theoRight;
  int simplificationUsed;
  node *leftDerivative;
  node *rightDerivative;
  mpfi_t *xZ;
  mpfi_t *xMXZ;
  exprBoundTheo *theoLeftConstant;
  exprBoundTheo *theoRightConstant;
  mpfi_t *boundLeftConstant;
  mpfi_t *boundRightConstant;
  exprBoundTheo *theoLeftLinear;
  exprBoundTheo *theoRightLinear;
  mpfi_t *boundLeftLinear;
  mpfi_t *boundRightLinear;
  int number;
};

typedef struct equalityTheoStruct equalityTheo;

struct equalityTheoStruct
{
  node *expr1;
  node *expr2;
  int number;
};

typedef struct noZeroTheoStruct noZeroTheo;

struct noZeroTheoStruct
{
  node *function;
  node *derivative;
  equalityTheo *funcEqual;
  equalityTheo *derivEqual;
  chain *exprBoundTheos;
  int number;
};

typedef struct infnormTheoStruct infnormTheo;

struct infnormTheoStruct
{
  node *function;
  mpfi_t *domain;
  mpfi_t *infnorm;
  node *derivative;
  node *numeratorOfDerivative;
  node *derivativeOfNumeratorOfDerivative;
  chain *excludedIntervals;
  noZeroTheo *noZeros;
  exprBoundTheo *evalLeftBound;
  exprBoundTheo *evalRightBound;
  chain *evalOnZeros;
  int number;
};



int fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start);
void freeExprBoundTheo(exprBoundTheo *theo);
void nullifyExprBoundTheo(exprBoundTheo *theo);
int fprintNoZeroTheo(FILE *fd, noZeroTheo *theo, int start);
void freeNoZeroTheo(noZeroTheo *theo);
int fprintInfnormTheo(FILE *fd, infnormTheo *theo, int start);
void freeInfnormTheo(infnormTheo *theo);

#endif /* ifdef PROOF_H*/
