#ifndef IMPLEMENT_H
#define IMPLEMENT_H


#include <mpfr.h>
#include <stdio.h>
#include "expression.h"
#include "main.h"

#define CODESIZE 4000000


node *implementpoly(node *func, rangetype range, mpfr_t *accur, int variablePrecision, 
		    FILE *fd, char *name, int honorCoeffPrec, mp_prec_t prec, FILE *gappaFD);



#endif /* ifdef IMPLEMENT_H*/
