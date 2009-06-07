/*

Copyright 2008 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.org
sylvain.chevillard@ens-lyon.org
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinity norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

*/

#include "sollya.h"
#include <setjmp.h>
#include <stdio.h>

/* Example for the usage of libsollya

   Compile with something similar to

       gcc -Wall -c libsollyaexample.c
       gcc -L./.libs -Wall -o libsollyaexample libsollyaexample.o -lsollya


   The example...

   1.) Initializes the library
   2.) Computes a Remez polynomial for log(1 + x) with relative error
   3.) Computes a Remez polynomial for log(1 + x) with relative error with wrong base
   4.) Calls error handler because of failure
   5.) Frees the library

   The usage of the recovering functionality is not mandatory. In the case
   of an error the library ends the program with return code 1.

*/

int main(int argc, char *argv[]) {
  jmp_buf recover;

  node *tempNode, *tempNode2, *tempNode3;
  chain *tempChain;
  mpfr_t a;
  mpfr_t b;

  /* Start initialization */
  
  initTool();

  if (setjmp(recover)) {
    /* If we are here, we have come back from an error in the library */

    fprintf(stderr,"An error occurred in the sollya library.\n");
    finishTool();
    return 1;
  }
  setRecoverEnvironment(&recover);

  /* End of initialization */
  

  tempNode = parseString("1/log(1 + x)");
  tempNode2 = parseString("1");

  tempChain = makeIntPtrChainFromTo(1,5);

  mpfr_init2(a,12);
  mpfr_init2(b,12);

  mpfr_set_d(a,-0.25,GMP_RNDN);
  mpfr_set_d(b,0.25,GMP_RNDN);

  tempNode3 = remez(tempNode2, tempNode, tempChain, a, b, NULL, getToolPrecision());

  mpfr_clear(a);
  mpfr_clear(b);


  printTree(tempNode3);
  printf("\n");

  free_memory(tempNode);
  free_memory(tempNode2);
  free_memory(tempNode3);

  freeChain(tempChain,freeIntPtr);

  /* Second example that calls a error recovery function */

  tempNode = parseString("1/log(1 + x)");
  tempNode2 = parseString("1");

  tempChain = makeIntPtrChainFromTo(0,5);

  mpfr_init2(a,12);
  mpfr_init2(b,12);

  mpfr_set_d(a,-0.25,GMP_RNDN);
  mpfr_set_d(b,0.25,GMP_RNDN);

  tempNode3 = remez(tempNode2, tempNode, tempChain, a, b, NULL, getToolPrecision());

  mpfr_clear(a);
  mpfr_clear(b);


  printTree(tempNode3);
  printf("\n");

  free_memory(tempNode);
  free_memory(tempNode2);
  free_memory(tempNode3);

  freeChain(tempChain,freeIntPtr);

  /* End the tool */

  finishTool();

  return 0;
}
