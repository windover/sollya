#ifndef MAIN_H
#define MAIN_H


#include <mpfr.h>
#include "expression.h"
#include "chain.h"

#define DEFAULTPOINTS 1000
#define DEFAULTPRECISION 120
#define DEFAULTDIAM 1e-4


extern char *variablename;
extern char *currentVariable;
extern char *currentString;
extern mp_prec_t tools_precision;
extern char **endptr;
extern unsigned long int points;
extern mpfr_t *mpfr_temp;
extern mpfr_t *mpfr_temp2;
extern rangetype range_temp;
extern rangetype range_temp2;
extern rangetype *rangeTempPtr;
extern node *temp_node; 
extern node *temp_node2;
extern mp_prec_t defaultprecision;
extern int defaultpoints;
extern int int_temp;
extern mp_prec_t prec_temp;
extern double double_temp;
extern int promptToBePrinted;
extern int handlingError;
extern chain *symbolTable;
extern char *temp_string;
extern chain *chain_temp;
extern chain *chain_temp2;
extern int dyadic;
extern FILE *temp_fd;

void printPrompt(void);
void recoverFromError(void);
void demaskString(char*, char*);

#endif /* ifdef MAIN_H*/
