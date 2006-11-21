#ifndef MAIN_H
#define MAIN_H


#include <mpfr.h>
#include "expression.h"
#include "chain.h"
#include "fpminimax.h"

#define DEFAULTPOINTS 501
#define DEFAULTPRECISION 165
#define DEFAULTDIAM 1e-4
#define DEFAULTDIAM2 2e-3
#define DEFAULTTAYLORRECURSIONS 0



typedef struct doubleChainStruct doubleChain;

struct doubleChainStruct {
  chain *a;
  chain *b;
};

extern char *variablename;
extern char *currentVariable;
extern char *currentString;
extern mp_prec_t tools_precision;
extern char **endptr;
extern unsigned long int points;
extern mpfr_t *mpfr_temp;
extern mpfr_t *mpfr_temp2;
extern mpfr_t *mpfr_temp3;
extern rangetype range_temp;
extern rangetype range_temp2;
extern rangetype *rangeTempPtr;
extern node *temp_node; 
extern node *temp_node2;
extern mp_prec_t defaultprecision;
extern int defaultpoints;
extern int taylorrecursions;
extern int int_temp;
extern int int_temp2;
extern mp_prec_t prec_temp;
extern double double_temp;
extern int promptToBePrinted;
extern int handlingError;
extern chain *symbolTable;
extern chain *symbolTable2;
extern char *temp_string;
extern chain *chain_temp;
extern chain *chain_temp2;
extern int dyadic;
extern FILE *temp_fd;
extern int *intTempPtr;
extern int verbosity;
extern doubleChain *doubleChainTemp;
extern formatType *formatTypeTemp;
extern errorType *errorTypeTemp;
extern pointsType *pointsTypeTemp;
extern int eliminatePrompt;
extern mp_prec_t tempPrec;
extern int canonical;

void printPrompt(void);
void recoverFromError(void);
void demaskString(char*, char*);
void *safeCalloc (size_t nmemb, size_t size);
void *safeMalloc (size_t size);
int printMessage(int verb, const char *format, ...);

#endif /* ifdef MAIN_H*/
