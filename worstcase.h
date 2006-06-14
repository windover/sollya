#ifndef WORSTCASE_H
#define WORSTCASE_H


#include <mpfr.h>
#include "expression.h"


void printWorstCases(node *func, mpfr_t inputprec, rangetype inputExponRange, mpfr_t outputprec, mpfr_t epsilon, mp_prec_t prec);




#endif /* ifdef WORSTCASE_H*/
