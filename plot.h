#ifndef PLOT_H
#define PLOT_H

#include <mpfr.h>
#include "expression.h"
#include "chain.h"

#define PLOTFILE 0
#define PLOTPOSTSCRIPT 1
#define PLOTPDF 2
#define PLOTPOSTSCRIPTFILE 3
#define PLOTPDFFILE 4

void plotTree(chain *treeList, mpfr_t a, mpfr_t b, unsigned long int points, mp_prec_t prec, char *name, int type);



#endif /* ifdef PLOT_H*/
