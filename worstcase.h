#ifndef WORSTCASE_H
#define WORSTCASE_H


#include <mpfr.h>
#include <stdio.h>
#include "expression.h"


void printWorstCases(node *func, mpfr_t inputprec, rangetype inputExponRange, mpfr_t outputprec, mpfr_t epsilon, mp_prec_t prec, FILE *fd);
int searchGalValue(node *func, mpfr_t foundValue, mpfr_t startValue, mp_prec_t searchPrec, int steps, 
		    int imageFormat, mpfr_t epsilon, mp_prec_t prec);



#endif /* ifdef WORSTCASE_H*/
