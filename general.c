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
#include "parser.h"
#include <pari/paripriv.h>
#include <termios.h>
#include <sys/time.h>
#include <time.h>
#include "execute.h"

#if HAVE_BACKTRACE
#include <execinfo.h>
#endif


/* STATE OF THE TOOL */

char *variablename = NULL;
mp_prec_t defaultprecision = DEFAULTPRECISION;
mp_prec_t tools_precision = DEFAULTPRECISION;
int defaultpoints = DEFAULTPOINTS;
int taylorrecursions = DEFAULTTAYLORRECURSIONS;
int dyadic = 0;
int verbosity = 1;
int canonical = 0;
int fileNumber = 0;
int autosimplify = 1;
int timecounting = 0;
chain *timeStack=NULL;
int fullParentheses=0;
int midpointMode = 0;
int hopitalrecursions = DEFAULTHOPITALRECURSIONS;
mpfr_t statediam;

int eliminatePromptBackup;
ulong ltop;
chain *readStack = NULL;
chain *readStackTemp = NULL;
chain *readStack2 = NULL;
void *scanner = NULL;
int promptToBePrinted = 0;

node *parsedThing = NULL;
node *parsedThingIntern = NULL;

jmp_buf recoverEnvironment;
jmp_buf recoverEnvironmentError;
int handlingCtrlC = 0;
int recoverEnvironmentReady = 0;
int exitInsteadOfRecover = 1;
int numberBacktrace = 1;

chain *symbolTable = NULL;

/* END OF STATE OF THE TOOL */

/* HELPER VARIABLES FOR THE LEXER/ PARSER */

char *newReadFilename = NULL;
char *newReadFilenameTemp = NULL;
FILE **tempFDPtr;
FILE *temp_fd;
char *constBuffer = NULL;
char *constBuffer2 = NULL;
char *tempString = NULL;
char *tempString2 = NULL;

/* END OF HELPER VARIABLES */

/* HELPER VARIABLES FOR LEGACY MINIPARSER */

node * temp_node;
mpfr_t *mpfr_temp;
mpfr_t *mpfr_temp2;
node *minitree;

/* END OF HELPER VARIABLES */


extern int yyparse();
extern void yylex_destroy(void *);
extern int yylex_init(void **);
extern int yylex(void *);



#define PARIENVIRONMENT GP_DATA->env
extern gp_data *GP_DATA;


#define BACKTRACELENGTH 100

void *rpl_malloc(size_t n) {
  if (n == 0)
    n = 1;
  return malloc (n);
}


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
  if (size == 0) 
    ptr = malloc(1);
  else
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

int removeSpaces(char *outbuf, char *inbuf) {
  char *temp, *temp2;
  int removed;

  removed = 0;
  temp = inbuf; temp2 = outbuf;
  while ((temp != NULL) && (*temp != '\0')) {
    if (*temp != ' ') {
      *temp2 = *temp;
      temp2++;
    } else {
      removed = 1;
    }
    temp++;
  }

  return removed;
}

int removeMidpointMode(char *outbuf, char *inbuf) {
  char *temp, *temp2;
  int removed;

  removed = 0;

  temp = inbuf;
  temp2 = outbuf;

  while (*temp != '\0') {
    if (*temp != '~') {
      *temp2 = *temp;
      temp2++;
      temp++;
    } else {
      temp++;
      while ((*temp != '\0') && (*temp != '~')) temp++;
      if (*temp != '\0') temp++;
      removed = 1;
    }
  }

  return removed;
}

void newReadFileStarted() {

}

void carriageReturnLexed() {
  if (promptToBePrinted) printPrompt();
}

void newTokenLexed() {
  promptToBePrinted = 0;
}


int printMessage(int verb, const char *format, ...) {
  va_list varlist;
  
  if (verbosity < verb) return 0;
  
  va_start(varlist,format);

  return vprintf(format,varlist);
}


void freeCounter(void) {
  freeChain(timeStack, free);
  timeStack=NULL;
  return;
}

void pushTimeCounter(void) {
  struct timeval *buf;
  if(timecounting==1) {
    buf = safeMalloc(sizeof(struct timeval));
    if(gettimeofday(buf,NULL)!=0)
      fprintf(stderr, "Error: unable to use the timer. Measures may be untrustable\n");
    timeStack = addElement(timeStack, buf);
  }
  return;
}

void popTimeCounter(char *s) {
  struct timeval *buf_init;
  struct timeval *buf_final;

  long int days, hours, minutes, seconds, milliseconds, microseconds;

  chain *prev;
  if((timecounting==1)&&(timeStack!=NULL)) {
    buf_final = safeMalloc(sizeof(struct timeval));
    if(gettimeofday(buf_final,NULL)!=0)
      fprintf(stderr, "Error: unable to use the timer. Measures may be untrustable\n");
    buf_init = timeStack->value;

    seconds = (long int)(buf_final->tv_sec) - (long int)(buf_init->tv_sec);
    microseconds = (long int)(buf_final->tv_usec) - (long int)(buf_init->tv_usec);

    if (microseconds < 0) {
      microseconds += 1000000l;
      seconds--;
    }

    milliseconds = microseconds / 1000;

    if((milliseconds>0)||(seconds>0)) {
      printMessage(0, "Information: %s spent ", s);
      if(seconds!=0) {
	minutes = seconds / 60;
	seconds = seconds % 60;
	hours = minutes / 60;
	minutes = minutes % 60;
	days = hours / 24;
	hours = hours % 24;
	
	if(days!=0) printMessage(0, "%d days, ", days);
	if(hours!=0) printMessage(0, "%d hours, ", hours);
	if(minutes!=0) printMessage(0, "%d minutes, ", minutes);
	if(seconds!=0) printMessage(0, "%d seconds, ", seconds);
      }
      printMessage(0, "%d ms\n", milliseconds);
    }

    prev = timeStack;
    timeStack = timeStack->next;
    free(prev);
    free(buf_init);
    free(buf_final);
  }
  return;
}



void printBacktrace() {
#if HAVE_BACKTRACE
  void *array[BACKTRACELENGTH];
  size_t size;
  char **strings;
  size_t i;

  if (numberBacktrace > 0) {

    size = backtrace (array, BACKTRACELENGTH);
    strings = backtrace_symbols (array, size);

    fprintf(stderr,"The current stack is:\n\n");

    for (i=0; i<size; i++)
      fprintf(stderr,"%s\n", strings[i]);

    free (strings);
    numberBacktrace--;

  }
#endif 
}


void signalHandler(int i) {
  switch (i) {
  case SIGINT: 
    handlingCtrlC = 1;
    break;
  case SIGSEGV:
    fprintf(stderr,"Warning: handling signal SIGSEGV\n");
    printBacktrace(); 
    fprintf(stderr,"\n");
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
  if (recoverEnvironmentReady) {
    if (exitInsteadOfRecover) {
      fprintf(stderr,"Error: the recover environment has not been initialized. Exiting.\n");
      exit(1);
    }
    avma = ltop;
    longjmp(recoverEnvironment,1);
  } 
}

void recoverFromError(void) {
  if (exitInsteadOfRecover) {
    fprintf(stderr,"Error: the recover environment has not been initialized. Exiting.\n");
    exit(1);
  }
  avma = ltop;
  longjmp(recoverEnvironmentError,1);
}


void printPrompt(void) {
  if (eliminatePromptBackup) return;
  if (readStack != NULL) return;
  printf("> ");
}

void initSignalHandler() {
  sigset_t mask;

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
}

void blockSignals() {
  sigset_t mask;

  sigemptyset(&mask);

  if (readStack != NULL) sigaddset(&mask,SIGINT);
  sigaddset(&mask,SIGSEGV);
  sigaddset(&mask,SIGBUS);
  sigaddset(&mask,SIGFPE);
  sigaddset(&mask,SIGPIPE);
  sigprocmask(SIG_BLOCK, &mask, NULL);
}

void freeTool() {
  if(variablename != NULL) free(variablename);
  if(newReadFilename != NULL) free(newReadFilename);

  if (!(eliminatePromptBackup == 1)) {
    removePlotFiles();
  }

  while ((readStack != NULL) && (readStack2 != NULL)) {
    temp_fd = *((FILE **) (readStack2->value));
    fclose(temp_fd);
    free(readStack2->value);
    readStackTemp = readStack2->next;
    free(readStack2);
    readStack2 = readStackTemp;
    free(readStack->value);
    readStackTemp = readStack->next;
    free(readStack);
    readStack = readStackTemp;
  }
  avma = ltop;
  pari_close();
  yylex_destroy(scanner);
  freeLibraries();
  freeCounter();
  freeSymbolTable(symbolTable, freeThingOnVoid);
  symbolTable = NULL;
  mpfr_clear(statediam);
}

void initToolDefaults() {
  ltop = avma;
  if(variablename != NULL) free(variablename); 
  variablename = NULL;
  defaultprecision = DEFAULTPRECISION;
  tools_precision = DEFAULTPRECISION;
  defaultpoints = DEFAULTPOINTS;
  taylorrecursions = DEFAULTTAYLORRECURSIONS;
  dyadic = 0;
  verbosity = 1;
  canonical = 0;
  fileNumber = 0;
  autosimplify = 1;
  timecounting = 0;
  timeStack=NULL;
  fullParentheses=0;
  midpointMode = 0;
  hopitalrecursions = DEFAULTHOPITALRECURSIONS;
  symbolTable = NULL;
  mpfr_init2(statediam,10);
  mpfr_set_d(statediam,DEFAULTDIAM,GMP_RNDN);
}

void restartTool() {
  freeSymbolTable(symbolTable, freeThingOnVoid);
  symbolTable = NULL;
  freeLibraries();
  initToolDefaults();
}

char *getNameOfVariable() {
  char *str;
  if (variablename == NULL) return NULL;
  str = (char *) safeCalloc(strlen(variablename)+1,sizeof(char));
  strcpy(str,variablename);
  return str;
}

int setNameOfVariable(char *str) {
  if (variablename != NULL) return 0;
  variablename = (char *) safeCalloc(strlen(str)+1,sizeof(char));
  strcpy(variablename,str);
  return 1;
}

void initTool() {
  struct termios termAttr;
  yylex_init(&scanner);

  if (tcgetattr(0,&termAttr) == -1) {
    eliminatePromptBackup = 1;
  }
  
  pari_init(PARIMEMSIZE, 2);
  initSignalHandler();
  blockSignals();
  mp_set_memory_functions(safeMalloc,wrapSafeRealloc,NULL);
  ltop = avma;
  initToolDefaults();
}

void finishTool() {
  freeTool();
}

mp_prec_t getToolPrecision() {
  return tools_precision;
}

void setToolPrecision(mp_prec_t prec) {
  tools_precision = prec;
  defaultprecision = prec;
}

int getToolPoints() {
  return defaultpoints;
}

void setToolPoints(int p) {
  if (p < 12) defaultpoints = 12; else defaultpoints = p;
}

int getToolTaylorRecursions() {
  return taylorrecursions;
}

void setToolTaylorRecursions(int i) {
  if (i < 0) taylorrecursions = 0; else taylorrecursions = i;
}

int getToolHopitalRecursions() {
  return hopitalrecursions;
}

void setToolHopitalRecursions(int i) {
  if (i < 0) hopitalrecursions = 0; else hopitalrecursions = i;
}


int getToolDiameter(mpfr_t rop) {
  return mpfr_set(rop,statediam,GMP_RNDN);
}

void setToolDiameter(mpfr_t op) {
  mpfr_set_prec(statediam,mpfr_get_prec(op));
  mpfr_set(statediam,op,GMP_RNDN);
}

void setRecoverEnvironment(jmp_buf *env) {
  memmove(&recoverEnvironment,env,sizeof(recoverEnvironment));
  memmove(&recoverEnvironmentError,env,sizeof(recoverEnvironmentError));
  memmove(&(PARIENVIRONMENT),env,sizeof((PARIENVIRONMENT)));
  exitInsteadOfRecover = 0;
}

void invalidateRecoverEnvironment() {
  exitInsteadOfRecover = 1;
}


int general(int argc, char *argv[]) {
  struct termios termAttr;
  int parseAbort, executeAbort;

  yylex_init(&scanner);

  if (tcgetattr(0,&termAttr) == -1) {
    eliminatePromptBackup = 1;
  }
  
  pari_init(PARIMEMSIZE, 2);
  initSignalHandler();
  blockSignals();
  mp_set_memory_functions(safeMalloc,wrapSafeRealloc,NULL);
  ltop = avma;
  initToolDefaults();

  if (setjmp(PARIENVIRONMENT)) {
    fprintf(stderr,"Error: an error occurred in the PARI subsystem.\n");
    if (exitInsteadOfRecover) {
      fprintf(stderr,"Error: the recover environment has not been initialized. Exiting.\n");
      exit(1);
    }
    avma = ltop;
    longjmp(recoverEnvironment,1);
  }
 
  exitInsteadOfRecover = 0;
  printPrompt();
  while (1) {
    executeAbort = 0;
    parsedThing = NULL;
    parseAbort = yyparse(scanner);
    if (parsedThing != NULL) {
      
      handlingCtrlC = 0;
      if (!setjmp(recoverEnvironment)) {
	memmove(&recoverEnvironmentError,&recoverEnvironment,sizeof(recoverEnvironmentError));
	recoverEnvironmentReady = 1;
	initSignalHandler();
	numberBacktrace = 1;
	pushTimeCounter();
	executeAbort = executeCommand(parsedThing);
	popTimeCounter("full execution of the last parse chunk");
	blockSignals();
	recoverEnvironmentReady = 0;
      } else {
	blockSignals();
	if (handlingCtrlC) 
	  printMessage(1,"Warning: the last command has been interrupted. May leak memory.\n");
	else 
	  printMessage(1,"Warning: the last command could not be executed. May leak memory.\n");
      }

      freeThing(parsedThing);
    } 
    if (parseAbort || executeAbort) break;
    promptToBePrinted = 1;
  }
  
  freeTool();

  if (!eliminatePromptBackup) printf("\n");

  return 0;
}

