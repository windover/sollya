#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <mpfr.h>
#include <stdio.h>
#include "chain.h"

extern int miniyyparse();
extern void startBuffer(char *str);
extern void endBuffer(void);

#define VARIABLE 0
#define CONSTANT 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define SQRT 6
#define EXP 7
#define LOG 8
#define LOG_2 9
#define LOG_10 10
#define SIN 11
#define COS 12
#define TAN 13
#define ASIN 14
#define ACOS 15
#define ATAN 16
#define SINH 17
#define COSH 18
#define TANH 19
#define ASINH 20
#define ACOSH 21
#define ATANH 22
#define POW 23
#define NEG 24
#define ABS 25
#define DOUBLE 26
#define DOUBLEDOUBLE 27
#define TRIPLEDOUBLE 28
#define POLYNOMIAL 29
#define ERF 30
#define ERFC 31
#define LOG_1P 32
#define EXP_M1 33
#define DOUBLEEXTENDED 34


typedef struct nodeStruct node;

struct nodeStruct 
{
  int nodeType;
  mpfr_t *value;
  node *child1;
  node *child2;
};

typedef struct rangetypeStruct rangetype;

struct rangetypeStruct
{
  mpfr_t *a;
  mpfr_t *b;
};


void printTree(node *tree);
node* differentiate(node *tree);
node* simplifyTree(node *tree); 
void free_memory(node *tree);
int evaluateConstantExpression(mpfr_t result, node *tree, mp_prec_t prec);
void evaluate(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec);
void printValue(mpfr_t *value, mp_prec_t prec);
node* copyTree(node *tree);
node* horner(node *tree);
int getDegree(node *tree);
node* expand(node *tree);
node* simplifyTreeErrorfree(node *tree);
int getNumeratorDenominator(node **numerator, node **denominator, node *tree);
node *substitute(node* tree, node *t);
int readDyadic(mpfr_t res, char *c);
int isPolynomial(node *tree);
int arity(node *tree);
void fprintValue(FILE *fd, mpfr_t value);
void fprintTree(FILE *fd, node *tree);
int isSyntacticallyEqual(node *tree1, node *tree2);
void fprintHeadFunction(FILE *fd,node *tree, char *x, char *y);
int isConstant(node *tree);
void getCoefficients(int *degree, node ***coefficients, node *poly);
void *copyTreeOnVoid(void *tree);
void freeMemoryOnVoid(void *tree);
void freeRangetypePtr(void *ptr);
void *copyRangetypePtr(void *ptr);
node *makePolynomial(mpfr_t *coefficients, int degree);
int treeSize(node *tree);
void printMpfr(mpfr_t x);
int highestDegreeOfPolynomialSubexpression(node *tree);
node *getIthCoefficient(node *poly, int i);
node *getSubpolynomial(node *poly, chain *monomials, int fillDegrees, mp_prec_t prec);
node *makeCanonical(node *func, mp_prec_t prec);
char *sprintTree(node *tree);
char *sprintValue(mpfr_t *value, mp_prec_t prec);
void printBinary(mpfr_t x);
int isHorner(node *tree);
int isCanonical(node *tree);
char *sprintMidpointMode(mpfr_t a, mpfr_t b);

node *makeVariable();
node *makeConstant(mpfr_t x);
node *makeAdd(node *op1, node *op2);
node *makeSub(node *op1, node *op2);
node *makeMul(node *op1, node *op2);
node *makeDiv(node *op1, node *op2);
node *makeSqrt(node *op1);
node *makeExp(node *op1);
node *makeLog(node *op1);
node *makeLog2(node *op1);
node *makeLog10(node *op1);
node *makeSin(node *op1);
node *makeCos(node *op1);
node *makeTan(node *op1);
node *makeAsin(node *op1);
node *makeAcos(node *op1);
node *makeAtan(node *op1);
node *makePow(node *op1, node *op2);
node *makeNeg(node *op1);
node *makeAbs(node *op1);
node *makeDouble(node *op1);
node *makeDoubledouble(node *op1);
node *makeTripledouble(node *op1);
node *makeErf(node *op1);
node *makeErfc(node *op1);
node *makeLog1p(node *op1);
node *makeExpm1(node *op1);
node *makeDoubleextended(node *op1);

node *parseString(char *str); 


#endif /* ifdef EXPRESSION_H*/
