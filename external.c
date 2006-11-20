#include <unistd.h> /* execve, fork, daemon */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <gmp.h>
#include <mpfr.h>
#include "expression.h"
#include "external.h"
#include "plot.h"
#include "infnorm.h"
#include "main.h"

extern int fileNumber;

int bashExecute(char *command) {
  int i;
  i = system(command);

  return WEXITSTATUS(i);
}


void externalPlot(char *library, mpfr_t a, mpfr_t b, mp_prec_t samplingPrecision, int random, node *func, int mode, mp_prec_t prec, char *name, int type) {
  void *descr;
  void  (*myFunction)(mpfr_t, mpfr_t);
  char *error;
  mpfr_t x_h,x,y,temp,perturb,ulp,min_value;
  double xd, yd;
  FILE *file;
  gmp_randstate_t state;

  if (name != NULL) printf("name = \"%s\", type = %d\n",name,type);

  gmp_randinit_default (state);

  if(samplingPrecision > prec) {
    fprintf(stderr, "Error: you must use a sampling precision lower than the current precision\n");
    return;
  }

  descr = dlopen(library, RTLD_LAZY);
  if (descr==NULL) {
    fprintf(stderr, "Error: the given library (%s) is not available!\n",library);
    return;
  }

  dlerror(); /* Clear any existing error */
  myFunction = (void (*)(mpfr_t, mpfr_t)) dlsym(descr, "f");
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "Error: the function f cannot be found in library %s (%s)\n",library,error);
    return;
  }
  
  /* Beginning of the interesting part of the code */
  file = fopen("/tmp/arenairetools-0001.p", "w");
  if (file == NULL) {
    fprintf(stderr,"Error: the file /tmp/arenairetools-0001.p requested by plot could not be opened for writing: ");
    fprintf(stderr,"\"%s\".\n",strerror(errno));
    return;
  }
  fprintf(file, "# Gnuplot script generated by ArenairePlot\n");
  fprintf(file, "set xrange [%e:%e]\n", mpfr_get_d(a, GMP_RNDD),mpfr_get_d(b, GMP_RNDU));
  fprintf(file, "plot \"/tmp/arenairetools-0001.dat\" using 1:2 with dots t \"\"\n");
  fclose(file);

  file = fopen("/tmp/arenairetools-0001.dat", "w");
  if (file == NULL) {
    fprintf(stderr,"Error: the file /tmp/arenairetools-0001.dat requested by plot could not be opened for writing: ");
    fprintf(stderr,"\"%s\".\n",strerror(errno));
    return;
  }

  mpfr_init2(x_h,samplingPrecision);
  mpfr_init2(perturb, prec);
  mpfr_init2(x,prec);
  mpfr_init2(y,prec);
  mpfr_init2(temp,prec);
  mpfr_init2(ulp,prec);
  mpfr_init2(min_value,53);

  mpfr_sub(min_value, b, a, GMP_RNDN);
  mpfr_div_2ui(min_value, min_value, 12, GMP_RNDN);

  mpfr_set(x_h,a,GMP_RNDD);
  
  while(mpfr_less_p(x_h,b)) {
    mpfr_set(x, x_h, GMP_RNDN); // exact
    
    if (mpfr_zero_p(x_h)) {
      mpfr_set(x_h, min_value, GMP_RNDU);
    }
    else {
      if (mpfr_cmpabs(x_h, min_value) < 0) mpfr_set_d(x_h, 0., GMP_RNDN);
      else mpfr_nextabove(x_h);
    }

    if(random) {
      mpfr_sub(ulp, x_h, x, GMP_RNDN);
      mpfr_urandomb(perturb, state);
      mpfr_mul(perturb, perturb, ulp, GMP_RNDN);
      mpfr_add(x, x, perturb, GMP_RNDN);
    }

    (*myFunction)(temp,x);
    evaluateFaithful(y, func, x,prec);
    mpfr_sub(temp, temp, y, GMP_RNDN);
    if(mode==RELATIVE) mpfr_div(temp, temp, y, GMP_RNDN);
    xd =  mpfr_get_d(x, GMP_RNDN);
    if (xd >= MAX_VALUE_GNUPLOT) xd = MAX_VALUE_GNUPLOT;
    if (xd <= -MAX_VALUE_GNUPLOT) xd = -MAX_VALUE_GNUPLOT;
    fprintf(file, "%1.50e",xd);
    if (!mpfr_number_p(temp)) {
      printMessage(2,"Information: function undefined or not evaluable in point %s = ",variablename);
      if (verbosity >= 2) printValue(&x,prec);
      printMessage(2,"\nThis point will not be plotted.\n");
    }
    yd = mpfr_get_d(temp, GMP_RNDN);
    if (yd >= MAX_VALUE_GNUPLOT) yd = MAX_VALUE_GNUPLOT;
    if (yd <= -MAX_VALUE_GNUPLOT) yd = -MAX_VALUE_GNUPLOT;
    fprintf(file, "\t%1.50e\n", yd);
  }

  fclose(file);
 
  /* End of the interesting part.... */

  dlclose(descr);
  mpfr_clear(x);
  mpfr_clear(y);
  mpfr_clear(x_h);
  mpfr_clear(temp);
  mpfr_clear(perturb);
  mpfr_clear(ulp);
  mpfr_clear(min_value);

  if (fork()==0) {
    daemon(0,1);
    execlp("gnuplot", "gnuplot", "-persist", "/tmp/arenairetools-0001.p", NULL);
    perror("An error occured when calling gnuplot ");
    exit(1);
  }
  else wait(NULL);

  return;
}
