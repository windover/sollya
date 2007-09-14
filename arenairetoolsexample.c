#include "arenaireplot.h"
#include <setjmp.h>
#include <stdio.h>

/* Example for the usage of the arenairetools library 

   Compile with something similar to

       gcc -Wall -c arenairetoolsexample.c
       gcc -L. -Wall -o arenairetoolsexample arenairetoolsexample.o -ltools


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

    fprintf(stderr,"An error occured in the arenairetools library.\n");
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
