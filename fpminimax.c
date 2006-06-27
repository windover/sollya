#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include "main.h"
#include "expression.h"
#include "chain.h"
#include "fpminimax.h"

#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>

node *fpminimax(node *expr, chain *monomials, chain *formats, mpfr_t a, mpfr_t b, 
		errorType *error, pointsType *points, int quality, FILE *fd) {
  return copyTree(expr);
}
