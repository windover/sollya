#ifndef GENERAL_H
#define GENERAL_H


#include <mpfr.h>
#include "expression.h"
#include "chain.h"
#include "fpminimax.h"
#include "library.h"
#include <setjmp.h>
#include "config.h"

#define DEFAULTPOINTS 501
#define DEFAULTPRECISION 165
#define DEFAULTDIAM 1e-4
#define DEFAULTDIAM2 2e-3
#define DEFAULTTAYLORRECURSIONS 0
#define DEFAULTHOPITALRECURSIONS 2
#define MAXHORNERTREESIZE 5000
#define MAXAUTOSIMPLSIZE 5500
#define CHEAPSIMPLIFYSIZE 4000
#define PARIMEMSIZE 300000000


extern char *variablename;
extern mp_prec_t defaultprecision;
extern mp_prec_t tools_precision;
extern int defaultpoints;
extern int taylorrecursions;
extern int dyadic;
extern int verbosity;
extern int canonical;
extern int fileNumber;
extern int autosimplify;
extern int timecounting;
extern chain *timeStack;
extern int fullParentheses;
extern int midpointMode;
extern int hopitalrecursions;
extern int eliminatePromptBackup;
extern chain *readStack;
extern chain *readStackTemp;
extern chain *readStack2;
extern void *scanner;
extern char *newReadFilename;
extern char *newReadFilenameTemp;
extern FILE **tempFDPtr;
extern FILE *temp_fd;
extern node *temp_node;
extern mpfr_t *mpfr_temp;
extern mpfr_t *mpfr_temp2;
extern node *minitree;
extern char *constBuffer;
extern char *constBuffer2;
extern node* parsedThing;
extern int promptToBePrinted;
extern char *tempString;
extern char *tempString2;
extern chain *symbolTable;
extern mpfr_t statediam;
extern jmp_buf recoverEnvironmentError;
extern node *parsedThingIntern;
extern int *tempIntPtr;

extern void *rpl_malloc(size_t n);

int general(int argc, char *argv[]);
void printPrompt(void);
void recoverFromError(void);
void demaskString(char*, char*);
void *safeCalloc (size_t nmemb, size_t size);
void *safeMalloc (size_t size);
int printMessage(int verb, const char *format, ...);
int removeSpaces(char *outbuf, char *inbuf);
int removeMidpointMode(char *outbuf, char *inbuf);
void freeCounter(void);
void pushTimeCounter(void);
void popTimeCounter(char *s);
void newReadFileStarted();
void carriageReturnLexed();
void newTokenLexed();
void restartTool();

#endif /* ifdef GENERAL_H*/
