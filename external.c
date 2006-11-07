#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dlfcn.h>
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


void externalPlot(char *library, mpfr_t a, mpfr_t b, mp_prec_t samplingPrecision, int random, node *func, int mode, mp_prec_t prec) {
  void *descr;
  void *myFunction;
  char *error;

  descr = dlopen(library, RTLD_LAZY);
  if (descr==NULL) {
    fprintf(stderr, "Error: the given library (%s) is not available!\n",library);
    return;
  }

  myFunction = dlsym(descr, "f");
  if (myFunction==NULL) {
    fprintf(stderr, "Error: the function f cannot be found in library %s!\n",library);
    return;
    }

  return;

  
}
