#include <pari/pari.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdio.h> /* fprintf, fopen, fclose, */
#include <stdlib.h> /* exit, free, mktemp */
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>
#include "main.h"
#include "plot.h"
#include "expression.h"
#include "remez.h"
#include "infnorm.h"
#include "assignment.h"
#include <pari/paripriv.h>
#include <termios.h>

#define PARIMEMSIZE 3000000



char *variablename = NULL;
char *currentVariable = NULL;
char *currentString = NULL;
mp_prec_t defaultprecision = DEFAULTPRECISION;
int defaultpoints = DEFAULTPOINTS;
mp_prec_t tools_precision = DEFAULTPRECISION;
int taylorrecursions = DEFAULTTAYLORRECURSIONS;
mp_prec_t prec_temp;
char **endptr;
unsigned long int points;
mpfr_t *mpfr_temp;
mpfr_t *mpfr_temp2;
mpfr_t *mpfr_temp3;
rangetype range_temp;
rangetype range_temp2;
node *temp_node; 
node *temp_node2;
int int_temp;
int int_temp2;
double double_temp;
int promptToBePrinted;
jmp_buf recoverEnvironment;
int handlingError;
chain *symbolTable = NULL;
chain *symbolTable2 = NULL;
char *temp_string;
chain *chain_temp;
chain *chain_temp2;
ulong ltop;
rangetype *rangeTempPtr;
int dyadic = 0;
FILE *temp_fd;
int *intTempPtr = NULL;
int verbosity = 1;
doubleChain *doubleChainTemp;
formatType *formatTypeTemp;
errorType *errorTypeTemp;
pointsType *pointsTypeTemp;
int eliminatePrompt;
mp_prec_t tempPrec;
int handlingCtrlC;
int fileNumber = 0;

#define NEWPARIVERSION

#ifdef NEWPARIVERSION 

#define PARIENVIRONMENT GP_DATA->env
extern gp_data *GP_DATA;

#else 

#define PARIENVIRONMENT environnement
extern jmp_buf environnement;

#endif

extern int yyparse();
extern FILE *yyin;
extern void yyrestart(FILE *);

void *safeCalloc (size_t nmemb, size_t size) {
  void *ptr;
  ptr = calloc(nmemb,size);
  if (ptr == NULL) {
    fprintf(stderr,"Error: calloc could not succeed. No more memory left.\n");
    exit(1);
  }
  return ptr;
}

void *safeMalloc (size_t size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr,"Error: malloc could not succeed. No more memory left.\n");
    exit(1);
  }
  return ptr;
}

void *safeRealloc (void *ptr, size_t size) {
  void *newPtr;
  newPtr = realloc(ptr,size);
  if ((size != 0) && (newPtr == NULL)) {
    fprintf(stderr,"Error: realloc could not succeed. No more memory left.\n");
    exit(1);
  }
  return newPtr;
}

/* The gp signature for realloc is strange, we have to wrap our function */
void *wrapSafeRealloc(void *ptr, size_t old_size, size_t new_size) {
   return (void *) safeRealloc(ptr,new_size);
}


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


int printMessage(int verb, const char *format, ...) {
  va_list varlist;
  
  if (verbosity < verb) return 0;
  
  va_start(varlist,format);

  return vprintf(format,varlist);
}



void signalHandler(int i) {
  fflush(stdout); fflush(stderr);
  switch (i) {
  case SIGINT: 
    if (eliminatePrompt == 1) {
      printf("\n");
      free(endptr);
      freeSymbolTable(symbolTable,freeMemoryOnVoid);
      freeSymbolTable(symbolTable2,freeRangetypePtr);
      if(currentVariable != NULL) free(currentVariable);
      if(variablename != NULL) free(variablename);
      removePlotFiles();
      fclose(yyin);
      exit(0);
    } else {
      handlingCtrlC = 1;
      yyrestart(yyin);
    }
    break;
  case SIGSEGV:
    fprintf(stderr,"Warning: handling signal SIGSEGV\n");
    break;
  case SIGBUS:
    fprintf(stderr,"Warning: handling signal SIGBREAK\n");
    break;
  case SIGFPE:
    fprintf(stderr,"Warning: handling signal SIGFPE\n");
    break;
  case SIGPIPE:
    fprintf(stderr,"Warning: handling signal SIGPIPE\n");
    break;
  default:
    fprintf(stderr,"Error: must handle an unknown signal.\n");
    exit(1);
  }
  promptToBePrinted = 1;
  recoverFromError();
}


void recoverFromError(void) {
  handlingError = 1;
  avma = ltop;
  longjmp(recoverEnvironment,1);
  return;
}


void printPrompt(void) {
  if (eliminatePrompt) return;
  fflush(stdout);
  fflush(stdin);
  fflush(stderr);
  printf("> ");
  fflush(stdout);
  fflush(stdin);
  fflush(stderr);
}


int main(int argc, char *argv[]) {
  struct termios termAttr;
  sigset_t mask;
  
  eliminatePrompt = 0;
  if (tcgetattr(0,&termAttr) == -1) eliminatePrompt = 1;
  yyin = stdin;
  
  pari_init(PARIMEMSIZE, 2);
  mp_set_memory_functions(safeMalloc,wrapSafeRealloc,NULL);
  ltop = avma;
  

  if (setjmp(PARIENVIRONMENT)) {
    fprintf(stderr,"Error: an error occured in the PARI subsystem.\n");
    recoverFromError();
  }
 
  sigemptyset(&mask);
  sigaddset(&mask,SIGINT);
  sigaddset(&mask,SIGSEGV);
  sigaddset(&mask,SIGBUS);
  sigaddset(&mask,SIGFPE);
  sigaddset(&mask,SIGPIPE);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  signal(SIGINT,signalHandler);
  signal(SIGSEGV,signalHandler);
  signal(SIGBUS,signalHandler);
  signal(SIGFPE,signalHandler);
  signal(SIGPIPE,signalHandler);
  handlingCtrlC = 0;
  
  endptr = (char**) safeMalloc(sizeof(char*));

  printPrompt();
  while (1) {
    if (setjmp(recoverEnvironment)) {
      if (handlingCtrlC) 
	printMessage(1,"Warning: the last command has been interrupted. May leak memory.\n");
      else 
	printMessage(1,"Warning: the last command could not be executed. May leak memory.\n");
      handlingCtrlC = 0;
      sigemptyset(&mask);
      sigaddset(&mask,SIGINT);
      sigaddset(&mask,SIGSEGV);
      sigaddset(&mask,SIGBUS);
      sigaddset(&mask,SIGFPE);
      sigaddset(&mask,SIGPIPE);
      sigprocmask(SIG_UNBLOCK, &mask, NULL);
      signal(SIGINT,signalHandler);
      signal(SIGSEGV,signalHandler);
      signal(SIGBUS,signalHandler);
      signal(SIGFPE,signalHandler);
      signal(SIGPIPE,signalHandler);
      if (promptToBePrinted) {
	printPrompt();
	promptToBePrinted = 0;
      }
    }
    if (yyparse()) break;  
    promptToBePrinted = 1;
  }

  printf("\n");
  
  free(endptr);
  freeSymbolTable(symbolTable,freeMemoryOnVoid);
  freeSymbolTable(symbolTable2,freeRangetypePtr);
  if(currentVariable != NULL) free(currentVariable);
  if(variablename != NULL) free(variablename);
  
  removePlotFiles();
  fclose(yyin);
  return 0;
}

