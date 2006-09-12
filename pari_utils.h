#ifndef PARIUTILS_H
#define PARIUTILS_H

#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>

#include "main.h"

GEN mpfr_to_PARI(mpfr_t x);

void PARI_to_mpfr(mpfr_t y, GEN x, mp_rnd_t rnd);

GEN evaluate_to_PARI(node *tree, GEN x, mp_prec_t prec);

void testPari(void);

#endif /* ifdef REMEZ_H*/
