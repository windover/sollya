#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <mpfr.h>
#include "expression.h"

#define RELATIVE 0
#define ABSOLUTE 1

int bashExecute(char *command);
void externalPlot(char *library, mpfr_t a, mpfr_t b, mp_prec_t samplingPrecision, int random, node *func, int mode, mp_prec_t prec, char *name, int type);


#endif /* ifdef EXTERNAL_H*/
