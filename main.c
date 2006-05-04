#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>
#include "main.h"
#include "plot.h"
#include "expression.h"
#include "remez.h"
#include "infnorm.h"



char *variablename = NULL;
mp_prec_t defaultprecision = DEFAULTPRECISION;
int defaultpoints = DEFAULTPOINTS;
mp_prec_t tools_precision = DEFAULTPRECISION;
mp_prec_t prec_temp;
char **endptr;
unsigned long int points;
mpfr_t *mpfr_temp;
mpfr_t *mpfr_temp2;
rangetype range_temp;
node *temp_node; 
int int_temp;
double double_temp;

extern int yyparse();
extern FILE *yyin;


void printPrompt(void) {
  fflush(stdout);
  fflush(stdin);
  printf("> ");
  fflush(stdout);
  fflush(stdin);
  clearerr(stdin);
}


int main(int argc, char *argv[])
{

  pari_init(1000000, 2);
  printPrompt();
 
  endptr = (char**) malloc(sizeof(char*));
  yyin = stdin;

  while (!feof(yyin)) {
    yyparse();
  }
  
  free(endptr);

  fclose(yyin);
  return 0;
}

