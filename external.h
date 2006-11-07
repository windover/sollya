#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <mpfr.h>
#include "expression.h"

int bashExecute(char *command);
void externalPlot(char *library, mpfr_t a, mpfr_t b, mp_prec_t samplingPrecision, int random, mp_prec_t prec);


#endif /* ifdef EXTERNAL_H*/
