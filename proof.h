#ifndef PROOF_H
#define PROOF_H


#include <mpfr.h>
#include <mpfi.h>
#include "expression.h"

#define TAYLOR 1
#define HOPITAL_ON_POINT 2
#define NUMERATOR_IS_ZERO 3
#define HOPITAL 4
#define IMPLICATION 5

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

void fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start);
void freeExprBoundTheo(exprBoundTheo *theo);


#endif /* ifdef PROOF_H*/
