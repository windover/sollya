#ifndef IMPLEMENT_H
#define IMPLEMENT_H


#include <mpfr.h>
#include <stdio.h>
#include "expression.h"
#include "main.h"

#define CODESIZE 4000000

int implementpoly(node *func, rangetype range, mpfr_t *accur, int variablePrecision, FILE *fd, char *name, mp_prec_t prec);



#endif /* ifdef IMPLEMENT_H*/
