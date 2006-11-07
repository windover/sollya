#include<stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include "expression.h"
#include "external.h"
#include "main.h"



int bashExecute(char *command) {
  int i;
  i = system(command);

  return WEXITSTATUS(i);
}


void externalPlot(char *library, mpfr_t a, mpfr_t b, mp_prec_t samplingPrecision, int random, mp_prec_t prec) {


}
