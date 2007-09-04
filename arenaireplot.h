#ifndef ARENAIREPLOT_H
#define ARENAIREPLOT_H

#include <mpfr.h>
#include <mpfr.h>

typedef struct chainStruct chain;
struct chainStruct 
{
  void *value;
  chain *next;
};


typedef struct libraryHandleStruct libraryHandle;
struct libraryHandleStruct 
{
  char *libraryName;
  void *libraryDescriptor;
  chain *functionList;
};

typedef struct libraryFunctionStruct libraryFunction;
struct libraryFunctionStruct 
{
  char *functionName;
  int (*code)(mpfi_t, mpfi_t, int);
};


typedef struct nodeStruct node;
struct nodeStruct 
{
  int nodeType;
  mpfr_t *value;
  node *child1;
  node *child2;
  libraryFunction *libFun;
  int libFunDeriv;
  char *string;
  chain *arguments;
};

typedef struct rangetypeStruct rangetype;
struct rangetypeStruct
{
  mpfr_t *a;
  mpfr_t *b;
};

extern node *makeVariable();
extern node *makeConstant(mpfr_t x);
extern node *makeAdd(node *op1, node *op2);
extern node *makeSub(node *op1, node *op2);
extern node *makeMul(node *op1, node *op2);
extern node *makeDiv(node *op1, node *op2);
extern node *makeSqrt(node *op1);
extern node *makeExp(node *op1);
extern node *makeLog(node *op1);
extern node *makeLog2(node *op1);
extern node *makeLog10(node *op1);
extern node *makeSin(node *op1);
extern node *makeCos(node *op1);
extern node *makeTan(node *op1);
extern node *makeAsin(node *op1);
extern node *makeAcos(node *op1);
extern node *makeAtan(node *op1);
extern node *makePow(node *op1, node *op2);
extern node *makeNeg(node *op1);
extern node *makeAbs(node *op1);
extern node *makeDouble(node *op1);
extern node *makeDoubledouble(node *op1);
extern node *makeTripledouble(node *op1);
extern node *makeErf(node *op1);
extern node *makeErfc(node *op1);
extern node *makeLog1p(node *op1);
extern node *makeExpm1(node *op1);
extern node *makeDoubleextended(node *op1);
extern node *makeCeil(node *op1);
extern node *makeFloor(node *op1);
extern node *makePi();
extern node *makeSinh(node *op1);
extern node *makeCosh(node *op1);
extern node *makeTanh(node *op1);
extern node *makeAsinh(node *op1);
extern node *makeAcosh(node *op1);
extern node *makeAtanh(node *op1);

extern node *parseString(char *str); 

extern void free_memory(node *tree);

extern void printTree(node *tree);
extern void fprintTree(FILE *fd, node *tree);
extern char *sprintTree(node *tree);

extern node* copyTree(node *tree);
extern node* differentiate(node *tree);
extern node* simplifyTree(node *tree); 
extern node* simplifyTreeErrorfree(node *tree);
extern node* horner(node *tree);
extern node* expand(node *tree);
extern node *substitute(node* tree, node *t);
extern node *makeCanonical(node *func, mp_prec_t prec);

extern node *makePolynomial(mpfr_t *coefficients, int degree);
extern node *getIthCoefficient(node *poly, int i);
extern void getCoefficients(int *degree, node ***coefficients, node *poly);

extern void evaluateFaithful(mpfr_t result, node *tree, mpfr_t x, mp_prec_t prec);
extern int evaluateFaithfulWithCutOff(mpfr_t result, node *func, mpfr_t x, mpfr_t cutoff, mp_prec_t startprec);

extern int getDegree(node *tree);
extern int isPolynomial(node *tree);
extern int isSyntacticallyEqual(node *tree1, node *tree2);
extern int isConstant(node *tree);
extern int isHorner(node *tree);
extern int isCanonical(node *tree);

extern rangetype infnorm(node *func, rangetype range, chain *excludes, mp_prec_t prec, mpfr_t diam, FILE *proof);
extern void uncertifiedInfnorm(mpfr_t result, node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);
extern int checkInfnorm(node *func, rangetype range, mpfr_t infnormval, mpfr_t diam, mp_prec_t prec);

extern int newtonMPFR(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mp_prec_t prec);
extern int newtonMPFRWithStartPoint(mpfr_t res, node *tree, node *diff_tree, mpfr_t a, mpfr_t b, mpfr_t start, mp_prec_t prec);
extern chain* findZerosFunction(node *func, rangetype range, mp_prec_t prec, mpfr_t diam);
extern chain* fpFindZerosFunction(node *func, rangetype range, mp_prec_t prec);

extern node* remez(node *func, node *weight, chain* monom, mpfr_t a, mpfr_t b, mpfr_t *requestedQuality, mp_prec_t prec);
extern rangetype guessDegree(node *func, node *weight, mpfr_t a, mpfr_t b, mpfr_t eps);

extern void freeChain(chain *c, void (*f) (void *));
extern chain *addElement(chain *c, void *elem);
extern void *first(chain *c);
extern chain *tail(chain *c);
extern chain *copyChain(chain *c, void * (*f) (void *));
extern chain *concatChains(chain *c1, chain *c2);
extern int lengthChain(chain *c);
extern void sortChain(chain *c,  int (*f) (void *, void *));


#endif
