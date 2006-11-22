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


node *rationalApprox(mpfr_t x, int n);
node *fpminimax(node *expr, chain *monomials, chain *formats, mpfr_t a, mpfr_t b, 
		errorType *error, pointsType *points, int quality, FILE *fd);

void freeFormatTypePtr(void *ptr);
void freeErrorTypePtr(void *ptr);
void freePointsTypePtr(void *ptr);



#endif /* ifdef FPMINIMAX_H*/
