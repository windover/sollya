#ifndef PLOT_H
#define PLOT_H

#include <mpfr.h>
#include "expression.h"
#include "chain.h"

#define PLOTFILE 0
#define PLOTPOSTSCRIPT 1
#define PLOTPOSTSCRIPTFILE 2

#define MAX_VALUE_GNUPLOT 0.898846567431157854072637118658521783990352837629224983e308

void plotTree(chain *treeList, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec, char *name, int type);



#endif /* ifdef PLOT_H*/
