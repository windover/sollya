#ifndef PLOT_H
#define PLOT_H

#include <mpfr.h>
#include "expression.h"

void plotTree(node *tree, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec);



#endif /* ifdef PLOT_H*/
