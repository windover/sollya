#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "main.h"
#include "plot.h"
#include "expression.h"
#include "remez.h"
#include "infnorm.h"
#include "assignment.h"


char *variablename = NULL;
char *currentVariable = NULL;
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
int promptToBePrinted;
jmp_buf recoverEnvironment;
int handlingError;
chain *symbolTable = NULL;
char *temp_string;

extern int yyparse();
extern FILE *yyin;


void signalHandler(int i) {
  printf("\n\n");
  fflush(stdout);
  exit(0);
}


void recoverFromError(void) {
  handlingError = 1;
  longjmp(recoverEnvironment,1);
  return;
}


void printPrompt(void) {
  fflush(stdout);
  fflush(stdin);
  fflush(stderr);
  printf("> ");
  fflush(stdout);
  fflush(stdin);
  fflush(stderr);
}


int main(int argc, char *argv[]) {
  
  pari_init(3000000, 2);

  signal(SIGINT,signalHandler);

  endptr = (char**) malloc(sizeof(char*));
  yyin = stdin;

  printPrompt();
  while (!feof(yyin)) {
    if (setjmp(recoverEnvironment)) {
      printf("Warning: an error occured on internal computation. The last command could not be executed. May leak memory.\n");
    }
    if (yyparse()) break;    
    promptToBePrinted = 1;
  }

  printf("\n");
  
  free(endptr);
  freeSymbolTable(symbolTable);

  fclose(yyin);
  return 0;
}

