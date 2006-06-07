#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <mpfr.h>
#include <stdio.h>



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


void plotTree(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);
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


#endif /* ifdef EXPRESSION_H*/
