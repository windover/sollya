/*

Copyright 2007 by 

Laboratoire de l'Informatique du Parallélisme, 
UMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668

Contributors Ch. Lauter, S. Chevillard, N. Jourdan

christoph.lauter@ens-lyon.fr
sylvain.chevillard@ens-lyon.fr
nicolas.jourdan@ens-lyon.fr

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinite norm, an automatic polynomial
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
extern int helpNotFinished;
extern char *tempString;
extern char *tempString2;
extern chain *symbolTable;
extern chain *declaredSymbolTable;
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
