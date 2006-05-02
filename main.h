#ifndef MAIN_H
#define MAIN_H


#include <mpfr.h>
#include "expression.h"

#define DEFAULTPOINTS 1000
#define DEFAULTPRECISION 120
#define DEFAULTDIAM 1e-6


extern char *variablename;
extern mp_prec_t precision;
extern char **endptr;
extern unsigned long int points;
extern mpfr_t *mpfr_temp;
extern mpfr_t *mpfr_temp2;
extern rangetype range_temp;
extern node *temp_node; 
extern mp_prec_t defaultprecision;
extern int defaultpoints;
extern int int_temp;
extern mp_prec_t prec_temp;

void printPrompt(void);


#endif /* ifdef MAIN_H*/
