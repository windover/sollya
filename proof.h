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
#define MONOTONOCITY 7

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


#define GAPPA_CONST 1
#define GAPPA_ADD_EXACT 2
#define GAPPA_MUL_EXACT 3
#define GAPPA_ADD_DOUBLE 4
#define GAPPA_MUL_DOUBLE 5
#define GAPPA_RENORMALIZE 6
#define GAPPA_ADD_REL 7
#define GAPPA_MUL_REL 8
#define GAPPA_FMA_REL 9
#define GAPPA_COPY 10

typedef struct gappaAssignmentStruct gappaAssignment;

struct gappaAssignmentStruct
{
  int opType;
  int relErrBits;
  int resultType;
  int resultOverlap;
  char *resultVariable;
  int operand1UsedType;
  int operand1ComingType;
  char *operand1Variable;
  int operand2UsedType;
  int operand2ComingType;
  char *operand2Variable;
  double constHi;
  double constMi;
  double constLo;
};

typedef struct gappaProofStruct gappaProof;

struct gappaProofStruct
{
  char *variableName;
  mpfr_t a, b;
  int variableType;
  int resultType;
  node *polynomToImplement;
  node *polynomImplemented;
  chain *gappaAssignments;
};




int fprintExprBoundTheo(FILE *fd, exprBoundTheo *theo, int start);
void freeExprBoundTheo(exprBoundTheo *theo);
void nullifyExprBoundTheo(exprBoundTheo *theo);
int fprintNoZeroTheo(FILE *fd, noZeroTheo *theo, int start);
void freeNoZeroTheo(noZeroTheo *theo);
int fprintInfnormTheo(FILE *fd, infnormTheo *theo, int start);
void freeInfnormTheo(infnormTheo *theo);

gappaAssignment *newGappaOperation(int opType, int relErrBits, 
				   int resultType, int resultOverlap, char *resultVariable,
				   int operand1UsedType, int operand1ComingType, char *operand1Variable,
				   int operand2UsedType, int operand2ComingType, char *operand2Variable);
gappaAssignment *newGappaConstant(int resultType, char *resultVariable, double constHi, double constMi, double constLo);

void freeGappaProof(gappaProof *proof);
int fprintGappaProof(FILE *fd, gappaProof *proof);



#endif /* ifdef PROOF_H*/
