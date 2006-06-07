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
char *currentString = NULL;
mp_prec_t defaultprecision = DEFAULTPRECISION;
int defaultpoints = DEFAULTPOINTS;
mp_prec_t tools_precision = DEFAULTPRECISION;
mp_prec_t prec_temp;
char **endptr;
unsigned long int points;
mpfr_t *mpfr_temp;
mpfr_t *mpfr_temp2;
rangetype range_temp;
rangetype range_temp2;
node *temp_node; 
node *temp_node2;
int int_temp;
double double_temp;
int promptToBePrinted;
jmp_buf recoverEnvironment;
int handlingError;
chain *symbolTable = NULL;
char *temp_string;
chain *chain_temp;
chain *chain_temp2;
ulong ltop;
rangetype *rangeTempPtr;
int dyadic = 0;
FILE *temp_fd;

extern jmp_buf environnement;

extern int yyparse();
extern FILE *yyin;

void demaskString(char *dest, char *src) {
  char *curr, *curr2;
  char internalBuf[4];
  int i;

  for (i=0;i<4;i++) internalBuf[i] = '\0';
  curr2 = dest;
  for (curr=src;*curr != '\0';curr++) {
    if (*curr != '\\') {
      *curr2++ = *curr;
    } else {
      curr++;
      if (*curr == '\0') break;
      switch (*curr) {
      case '\\': 
	*curr2++ = '\\';
	break;
      case '"': 
	*curr2++ = '"';
	break;
      case '?': 
	*curr2++ = '?';
	break;
      case '\'': 
	*curr2++ = '\'';
	break;
      case 'n': 
	*curr2++ = '\n';
	break;
      case 't': 
	*curr2++ = '\t';
	break;
      case 'a': 
	*curr2++ = '\a';
	break;
      case 'b': 
	*curr2++ = '\b';
	break;
      case 'f': 
	*curr2++ = '\f';
	break;
      case 'r': 
	*curr2++ = '\r';
	break;
      case 'v': 
	*curr2++ = '\v';
	break;
      case 'x':
	curr++;
        i = 0;
	while ((i < 2) && (*curr != '\0') && 
	       (((*curr >= '0') && (*curr <= '9')) ||
		((*curr >= 'A') && (*curr <= 'F')) ||
		((*curr >= 'a') && (*curr <= 'f')))) {
	  internalBuf[i] = *curr;
	  curr++; i++;
	}
	curr--;
	for (i=0;i<2;i++) {
	  if ((internalBuf[i] >= 'a') && (internalBuf[i] <= 'f')) {
	    internalBuf[i] = (internalBuf[i] - 'a') + 'A';
	  }
	}
	*curr2++ = (char) strtol(internalBuf,NULL,16);
	break;
      default:
	i = 0;
	while ((i < 3) && (*curr != '\0') && (*curr >= '0') && (*curr <= '7')) {
	  internalBuf[i] = *curr;
	  curr++; i++;
	}
	curr--;
	*curr2++ = (char) strtol(internalBuf,NULL,8);
      }
    }
  }
}


void signalHandler(int i) {
  printf("\n\n");
  fflush(stdout);
  promptToBePrinted = 1;
  switch (i) {
  case SIGINT:   
    exit(0);
  case SIGSEGV:
    printf("Warning: handling signal SIGSEGV\n");
    break;
  case SIGBUS:
    printf("Warning: handling signal SIGBREAK\n");
    break;
  case SIGFPE:
    printf("Warning: handling signal SIGFPE\n");
    break;
  case SIGPIPE:
    printf("Warning: handling signal SIGPIPE\n");
    break;
  default:
    printf("Error: must handle an unknown signal.\n");
    exit(1);
  }
  recoverFromError();
}


void recoverFromError(void) {
  handlingError = 1;
  avma = ltop;
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
  ltop = avma;
  if (setjmp(environnement)) {
    printf("Error: an error occured in the PARI subsystem.\n");
    recoverFromError();
  }


  signal(SIGINT,signalHandler);
  signal(SIGSEGV,signalHandler);
  signal(SIGBUS,signalHandler);
  signal(SIGFPE,signalHandler);
  signal(SIGPIPE,signalHandler);

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

