/*

Copyright 2008 by 

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

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "chain.h"
#include "general.h"
#include "execute.h"
#include "parser.h"
#include "library.h"
#include "help.h"
#include "config.h"

#define YYERROR_VERBOSE 1
#define YYPARSE_PARAM scanner
#define YYLEX_PARAM   scanner

extern int yylex(YYSTYPE *lvalp, void *scanner);
extern FILE *yyget_in(void *scanner);
extern char *getCurrentLexSymbol();

void yyerror(char *message) {
  char *str;
  if (!feof(yyget_in(scanner))) {
    str = getCurrentLexSymbol();
    printMessage(1,"Warning: %s.\nThe last symbol read has been \"%s\".\nWill skip input until next semicolon after the unexpected token. May leak memory.\n",message,str);
    free(str);
    promptToBePrinted = 1;
  } 
}

%}

%defines

%expect 1

%pure_parser

%union {
  doubleNode *dblnode;
  char *value;
  node *tree;
  chain *list;
  int *integerval;
  void *other;
};



%token  <value> CONSTANTTOKEN;          					       
%token  <value> MIDPOINTCONSTANTTOKEN;          					       
%token  <value> DYADICCONSTANTTOKEN;   					       
%token  <value> HEXCONSTANTTOKEN;       					       
%token  <value> HEXADECIMALCONSTANTTOKEN;       					       
%token  <value> BINARYCONSTANTTOKEN;    					       
											       
%token  PITOKEN;                					       
											       
%token  <value> IDENTIFIERTOKEN;          					       
											       
%token  <value> STRINGTOKEN;            					       
											       
%token  LPARTOKEN;              					       
%token  RPARTOKEN;              					       
%token  LBRACKETTOKEN;          					       
%token  RBRACKETTOKEN;          					       
%token  EQUALTOKEN;             					       
%token  ASSIGNEQUALTOKEN;
%token  COMPAREEQUALTOKEN;             					       
%token  COMMATOKEN;             					       
%token  EXCLAMATIONTOKEN;  						       
%token  SEMICOLONTOKEN;         					       
%token  STARLEFTANGLETOKEN;         					       
%token  LEFTANGLETOKEN;         					       
%token  RIGHTANGLEUNDERSCORETOKEN;  					       
%token  RIGHTANGLEDOTTOKEN;   					       
%token  RIGHTANGLESTARTOKEN;         					       
%token  RIGHTANGLETOKEN;        					       
%token  DOTSTOKEN;              					       
%token  QUESTIONMARKTOKEN;  						       
%token  VERTBARTOKEN;  						       
%token  ATTOKEN;  							       
%token  DOUBLECOLONTOKEN;
%token  DOTCOLONTOKEN;
%token  COLONDOTTOKEN;
%token  EXCLAMATIONEQUALTOKEN;
%token  APPROXTOKEN;
%token  ANDTOKEN;
%token  ORTOKEN;
	       										       
%token  PLUSTOKEN;              					       
%token  MINUSTOKEN;             					       
%token  MULTOKEN;            						       
%token  DIVTOKEN;              					       
%token  POWTOKEN;              					       
											       
%token  SQRTTOKEN;              					       
%token  EXPTOKEN;               					       
%token  LOGTOKEN;               					       
%token  LOG2TOKEN;              					       
%token  LOG10TOKEN;             					       
%token  SINTOKEN;               					       
%token  COSTOKEN;               					       
%token  TANTOKEN;               					       
%token  ASINTOKEN;              					       
%token  ACOSTOKEN;              					       
%token  ATANTOKEN;              					       
%token  SINHTOKEN;              					       
%token  COSHTOKEN;              					       
%token  TANHTOKEN;              					       
%token  ASINHTOKEN;             					       
%token  ACOSHTOKEN;             					       
%token  ATANHTOKEN;             					       
%token  ABSTOKEN;               					       
%token  ERFTOKEN;               					       
%token  ERFCTOKEN;              					       
%token  LOG1PTOKEN;             					       
%token  EXPM1TOKEN;             					       
%token  DOUBLETOKEN;            					       
%token  DOUBLEDOUBLETOKEN;  						       
%token  TRIPLEDOUBLETOKEN;      					       
%token  DOUBLEEXTENDEDTOKEN;    					       
%token  CEILTOKEN;              					       
%token  FLOORTOKEN;             			

%token  HEADTOKEN;
%token  REVERTTOKEN;
%token  SORTTOKEN;
%token  TAILTOKEN;		       
%token  MANTISSATOKEN;
%token  EXPONENTTOKEN;
%token  PRECISIONTOKEN;
%token  ROUNDCORRECTLYTOKEN;
											       
%token  PRECTOKEN;              					       
%token  POINTSTOKEN;            					       
%token  DIAMTOKEN;              					       
%token  DISPLAYTOKEN;            					       
%token  VERBOSITYTOKEN;         					       
%token  CANONICALTOKEN;         					       
%token  AUTOSIMPLIFYTOKEN;      					       
%token  TAYLORRECURSIONSTOKEN;  					       
%token  TIMINGTOKEN;            					       
%token  FULLPARENTHESESTOKEN;   					       
%token  MIDPOINTMODETOKEN;      					       
%token  SUPPRESSWARNINGSTOKEN;    					       
%token  HOPITALRECURSIONSTOKEN;  					       
											       
%token  ONTOKEN;                					       
%token  OFFTOKEN;               					       
%token  DYADICTOKEN;  						       
%token  POWERSTOKEN;            					       
%token  BINARYTOKEN;            					       
%token  HEXADECIMALTOKEN;            					       
%token  FILETOKEN;              					       
%token  POSTSCRIPTTOKEN;        					       
%token  POSTSCRIPTFILETOKEN;    					       
%token  PERTURBTOKEN;           					       
%token  MINUSWORDTOKEN;         					       
%token  PLUSWORDTOKEN;          					       
%token  ZEROWORDTOKEN;          					       
%token  NEARESTTOKEN;           					       
%token  HONORCOEFFPRECTOKEN;   					       
%token  TRUETOKEN;  							       
%token  FALSETOKEN;  							       
%token  DEFAULTTOKEN;											       
%token  ABSOLUTETOKEN;
%token  DECIMALTOKEN;
%token  RELATIVETOKEN;
%token  FIXEDTOKEN;
%token  FLOATINGTOKEN;

%token  ERRORTOKEN;			
								       
%token  QUITTOKEN;              					       
%token  FALSEQUITTOKEN;  						       
%token  RESTARTTOKEN;           					       
											       
%token  LIBRARYTOKEN;           					       
											       
%token  DIFFTOKEN;              					       
%token  SIMPLIFYTOKEN;  						       
%token  REMEZTOKEN;             					       
%token  FPMINIMAXTOKEN;             					       
%token  HORNERTOKEN;            					       
%token  EXPANDTOKEN;            					       
%token  SIMPLIFYSAFETOKEN;  						       
%token  TAYLORTOKEN;           					       
%token  DEGREETOKEN;            					       
%token  NUMERATORTOKEN;         					       
%token  DENOMINATORTOKEN;       					       
%token  SUBSTITUTETOKEN;        					       
%token  COEFFTOKEN;             					       
%token  SUBPOLYTOKEN;           					       
%token  ROUNDCOEFFICIENTSTOKEN;   					       
%token  RATIONALAPPROXTOKEN;    					       
%token  ACCURATEINFNORMTOKEN;    					       
%token  ROUNDTOFORMATTOKEN;     					       
%token  EVALUATETOKEN;          					       
%token  LENGTHTOKEN;
%token  INFTOKEN;
%token  MIDTOKEN;
%token  SUPTOKEN;

%token  READXMLTOKEN;											       
%token  PARSETOKEN;             					       
											       
%token  PRINTTOKEN;             					       
%token  PRINTXMLTOKEN;             					       
%token  PLOTTOKEN;              					       
%token  PRINTHEXATOKEN;         					       
%token  PRINTFLOATTOKEN;
%token  PRINTBINARYTOKEN;       					       
%token  PRINTEXPANSIONTOKEN;    					       
%token  BASHEXECUTETOKEN;       					       
%token  EXTERNALPLOTTOKEN;      					       
%token  WRITETOKEN;             					       
%token  ASCIIPLOTTOKEN;    
%token  RENAMETOKEN;    	       
											       
											       
%token  INFNORMTOKEN;           					       
%token  FINDZEROSTOKEN;         					       
%token  FPFINDZEROSTOKEN;       					       
%token  DIRTYINFNORMTOKEN;      					       
%token  INTEGRALTOKEN;          					       
%token  DIRTYINTEGRALTOKEN;  						       
%token  WORSTCASETOKEN;         					       
%token  IMPLEMENTPOLYTOKEN;  						       
%token  CHECKINFNORMTOKEN;      					       
%token  ZERODENOMINATORSTOKEN;  					       
%token  ISEVALUABLETOKEN;       					       
%token  SEARCHGALTOKEN;         					       
%token  GUESSDEGREETOKEN;       					       
%token  DIRTYFINDZEROSTOKEN;    					       
											       
%token  IFTOKEN;  							       
%token  THENTOKEN;  							       
%token  ELSETOKEN;  							       
%token  FORTOKEN;  							       
%token  INTOKEN;  							       
%token  FROMTOKEN;  							       
%token  TOTOKEN;  							       
%token  BYTOKEN;  							       
%token  DOTOKEN;  							       
%token  BEGINTOKEN;  							       
%token  ENDTOKEN;  							       
%token  WHILETOKEN;  							       

%token  READFILETOKEN;

%token  ISBOUNDTOKEN;

%token  EXECUTETOKEN;

%token  EXTERNALPROCTOKEN; 
%token  VOIDTOKEN;    
%token  CONSTANTTYPETOKEN; 
%token  FUNCTIONTOKEN;  
%token  RANGETOKEN;  
%token  INTEGERTOKEN;   
%token  STRINGTYPETOKEN;    
%token  BOOLEANTOKEN;    
%token  LISTTOKEN;    
%token  OFTOKEN;    

%token  VARTOKEN;    
%token  PROCTOKEN;
%token  PROCEDURETOKEN;
%token  RETURNTOKEN;
%token  NOPTOKEN;
									       
%token  HELPTOKEN;      
%token  VERSIONTOKEN;
                                                     

%type <other> startsymbol;
%type <other> help;
%type <other> helpmeta;
%type <other> egalquestionmark;
%type <tree>  command;
%type <tree>  procbody;
%type <tree>  variabledeclaration;
%type <tree>  simplecommand;
%type <list>  commandlist;
%type <list>  variabledeclarationlist;
%type <list>  identifierlist;
%type <tree>  thing;
%type <list>  thinglist;
%type <tree>  ifcommand;
%type <tree>  forcommand;
%type <tree>  assignment;
%type <tree>  simpleassignment;
%type <tree>  stateassignment;
%type <tree>  stillstateassignment;
%type <tree>  basicthing;
%type <tree>  list;
%type <tree>  constant;
%type <list>  simplelist;
%type <tree>  range;
%type <tree>  debound;
%type <tree>  headfunction;
%type <tree>  term;
%type <tree>  hyperterm;
%type <tree>  subterm;
%type <tree>  megaterm;
%type <tree>  statedereference;
%type <dblnode>  indexing;
%type <integerval> externalproctype;
%type <integerval> extendedexternalproctype;
%type <list>  externalproctypesimplelist;
%type <list>  externalproctypelist;

%%

startsymbol:            command SEMICOLONTOKEN 
                          {
			    parsedThing = $1;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | helpmeta SEMICOLONTOKEN		      
                          {
			    outputMode();
                            printf("This is %s.\nType 'help help;' for the list of available commands. Type 'help <command>;' for help on the specific command <command>.\nType 'quit;' for quitting the %s interpreter.\n\nYou can get moral support and help with bugs by writing to %s.\n\n",PACKAGE_NAME,PACKAGE_NAME,PACKAGE_BUGREPORT);
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | QUESTIONMARKTOKEN
                          {
			    outputMode();
                            printf("This is %s.\nType 'help help;' for the list of available commands. Type 'help <command>;' for help on the specific command <command>.\nType 'quit;' for quitting the %s interpreter.\n\nYou can get moral support and help with bugs by writing to %s.\n\n",PACKAGE_NAME,PACKAGE_NAME,PACKAGE_BUGREPORT);
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | helpmeta help SEMICOLONTOKEN
                          {
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | VERSIONTOKEN SEMICOLONTOKEN
                          {
			    outputMode();
			    printf("This is\n\n\t%s.\n\nCopyright 2008 by Laboratoire de l'Informatique du Parallelisme,\nUMR CNRS - ENS Lyon - UCB Lyon 1 - INRIA 5668\n\nContributors are Ch. Lauter, S. Chevillard, N. Jourdan and M. Joldes.\n\nThis software is governed by the CeCILL-C license under French law and\nabiding by the rules of distribution of free software.  You can  use,\nmodify and/ or redistribute the software under the terms of the CeCILL-C\nlicense as circulated by CEA, CNRS and INRIA at the following URL\n\"http://www.cecill.info\".\n\nPlease send bug reports to %s.\n",PACKAGE_STRING,PACKAGE_BUGREPORT);
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | error SEMICOLONTOKEN
                          {
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
;

helpmeta:               HELPTOKEN
                          {
			    helpNotFinished = 1;
			    $$ = NULL;
			  }
;

command:                simplecommand
                          {
			    $$ = $1;
			  }
                      | BEGINTOKEN commandlist ENDTOKEN
                          {
			    $$ = makeCommandList($2);
                          }
                      | BEGINTOKEN variabledeclarationlist commandlist ENDTOKEN
                          {			    
			    $$ = makeCommandList(concatChains($2, $3));
                          }
                      | BEGINTOKEN variabledeclarationlist ENDTOKEN
                          {
			    $$ = makeCommandList($2);
                          }
                      | BEGINTOKEN ENDTOKEN
                          {
			    $$ = makeNop();
                          }
                      | IFTOKEN ifcommand
                          {
			    $$ = $2;
			  }
                      | WHILETOKEN thing DOTOKEN command
                          {
			    $$ = makeWhile($2, $4);
			  }
                      | FORTOKEN forcommand
                          {
			    $$ = $2;
			  }
;

ifcommand:              thing THENTOKEN command 
                          {
			    $$ = makeIf($1, $3);
                          }
                      | thing THENTOKEN command ELSETOKEN command 
                          {
			    $$ = makeIfElse($1,$3,$5);
                          }
;



forcommand:             IDENTIFIERTOKEN FROMTOKEN thing TOTOKEN thing DOTOKEN command
                          {
			    $$ = makeFor($1, $3, $5, makeConstantDouble(1.0), $7);
			    free($1);
                          }
                      | IDENTIFIERTOKEN FROMTOKEN thing TOTOKEN thing BYTOKEN thing DOTOKEN command
                          {
			    $$ = makeFor($1, $3, $5, $7, $9);
			    free($1);
                          }
                      | IDENTIFIERTOKEN INTOKEN thing DOTOKEN command
                          {
			    $$ = makeForIn($1, $3, $5);
			    free($1);
                          }
;


commandlist:            command SEMICOLONTOKEN
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | command SEMICOLONTOKEN commandlist
                          {
			    $$ = addElement($3, $1);
			  }
;

variabledeclarationlist: variabledeclaration SEMICOLONTOKEN
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | variabledeclaration SEMICOLONTOKEN variabledeclarationlist
                          {
			    $$ = addElement($3, $1);
			  }
;

variabledeclaration:    VARTOKEN identifierlist
                          {
			    $$ = makeVariableDeclaration($2);
			  }
;


identifierlist:         IDENTIFIERTOKEN
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | IDENTIFIERTOKEN COMMATOKEN identifierlist
                          {
			    $$ = addElement($3, $1);
			  }
;

procbody:               LPARTOKEN RPARTOKEN BEGINTOKEN commandlist ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList($4), makeUnit());
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN variabledeclarationlist commandlist ENDTOKEN
                          {			    
			    $$ = makeProc(NULL, makeCommandList(concatChains($4, $5)), makeUnit());
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN variabledeclarationlist ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList($4), makeUnit());
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList(addElement(NULL,makeNop())), makeUnit());
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN commandlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList($4), $6);
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN variabledeclarationlist commandlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {			    
			    $$ = makeProc(NULL, makeCommandList(concatChains($4, $5)), $7);
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN variabledeclarationlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList($4), $6);
                          }
                      | LPARTOKEN RPARTOKEN BEGINTOKEN RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc(NULL, makeCommandList(addElement(NULL,makeNop())), $5);
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN commandlist ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList($5), makeUnit());
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN variabledeclarationlist commandlist ENDTOKEN
                          {			    
			    $$ = makeProc($2, makeCommandList(concatChains($5, $6)), makeUnit());
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN variabledeclarationlist ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList($5), makeUnit());
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList(addElement(NULL,makeNop())), makeUnit());
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN commandlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList($5), $7);
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN variabledeclarationlist commandlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {			    
			    $$ = makeProc($2, makeCommandList(concatChains($5, $6)), $8);
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN variabledeclarationlist RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList($5), $7);
                          }
                      | LPARTOKEN identifierlist RPARTOKEN BEGINTOKEN RETURNTOKEN thing SEMICOLONTOKEN ENDTOKEN
                          {
			    $$ = makeProc($2, makeCommandList(addElement(NULL, makeNop())), $6);
                          }
;


simplecommand:          QUITTOKEN
                          {
			    $$ = makeQuit();
			  }
                      | FALSEQUITTOKEN
                          {
			    $$ = makeFalseQuit();
			  }
                      | NOPTOKEN
                          {
			    $$ = makeNop();
			  }
                      | RESTARTTOKEN
                          {
			    $$ = makeRestart();
			  }
                      | PRINTTOKEN LPARTOKEN thinglist RPARTOKEN            					       
                          {
			    $$ = makePrint($3);
			  }
                      | PRINTTOKEN LPARTOKEN thinglist RPARTOKEN RIGHTANGLETOKEN thing           	
                          {
			    $$ = makeNewFilePrint($6, $3);
			  }				       
                      | PRINTTOKEN LPARTOKEN thinglist RPARTOKEN RIGHTANGLETOKEN RIGHTANGLETOKEN thing           	
                          {
			    $$ = makeAppendFilePrint($7, $3);
			  }				       
                      | PLOTTOKEN LPARTOKEN thing COMMATOKEN thinglist RPARTOKEN               	
                          {
			    $$ = makePlot(addElement($5, $3));
			  }				       
                      | PRINTHEXATOKEN LPARTOKEN thing RPARTOKEN         	
                          {
			    $$ = makePrintHexa($3);
			  }				       
                      | PRINTFLOATTOKEN LPARTOKEN thing RPARTOKEN         	
                          {
			    $$ = makePrintFloat($3);
			  }				       
                      | PRINTBINARYTOKEN LPARTOKEN thing RPARTOKEN      	
                          {
			    $$ = makePrintBinary($3);
			  }				       
                      | PRINTEXPANSIONTOKEN LPARTOKEN thing RPARTOKEN   	
                          {
			    $$ = makePrintExpansion($3);
			  }				       
                      | BASHEXECUTETOKEN LPARTOKEN thing RPARTOKEN      	
                          {
			    $$ = makeBashExecute($3);
			  }				       
                      | EXTERNALPLOTTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN     	
                          {
			    $$ = makeExternalPlot(addElement(addElement(addElement(addElement($11,$9),$7),$5),$3));
			  }				       
                      | WRITETOKEN LPARTOKEN thinglist RPARTOKEN            	
                          {
			    $$ = makeWrite($3);
			  }				       
                      | WRITETOKEN LPARTOKEN thinglist RPARTOKEN RIGHTANGLETOKEN thing           	
                          {
			    $$ = makeNewFileWrite($6, $3);
			  }				       
                      | WRITETOKEN LPARTOKEN thinglist RPARTOKEN RIGHTANGLETOKEN RIGHTANGLETOKEN thing           	
                          {
			    $$ = makeAppendFileWrite($7, $3);
			  }				       
                      | ASCIIPLOTTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeAsciiPlot($3, $5);
			  }				       
                      | PRINTXMLTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makePrintXml($3);
			  }	
                      | EXECUTETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeExecute($3);
			  }				       
                      | PRINTXMLTOKEN LPARTOKEN thing RPARTOKEN RIGHTANGLETOKEN thing
                          {
			    $$ = makePrintXmlNewFile($3,$6);
			  }				       
                      | PRINTXMLTOKEN LPARTOKEN thing RPARTOKEN RIGHTANGLETOKEN RIGHTANGLETOKEN thing
                          {
			    $$ = makePrintXmlAppendFile($3,$7);
			  }				       
                      | WORSTCASETOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeWorstCase(addElement(addElement(addElement(addElement($11, $9), $7), $5), $3));
			  }         					       
                      | RENAMETOKEN LPARTOKEN IDENTIFIERTOKEN COMMATOKEN IDENTIFIERTOKEN RPARTOKEN        	
                          {
			    $$ = makeRename($3, $5);
			    free($3);
			    free($5);
			  }	
                      | EXTERNALPROCTOKEN LPARTOKEN IDENTIFIERTOKEN COMMATOKEN thing COMMATOKEN externalproctypelist MINUSTOKEN RIGHTANGLETOKEN extendedexternalproctype RPARTOKEN        	
                          {
			    $$ = makeExternalProc($3, $5, addElement($7, $10));
			    free($3);
			  }				       
                      | assignment
                          {
			    $$ = $1;
			  }
                      | thinglist
                          {
			    $$ = makeAutoprint($1);
			  }
                      | PROCEDURETOKEN IDENTIFIERTOKEN procbody
                          {
			    $$ = makeAssignment($2, $3);
			    free($2);
			  }  
;

assignment:             stateassignment 
                          {
			    $$ = $1;
			  }
                      | stillstateassignment EXCLAMATIONTOKEN
                          {
			    $$ = $1;
			  }
                      | simpleassignment
                          {
			    $$ = $1;
			  }
                      | simpleassignment EXCLAMATIONTOKEN
                          {
			    $$ = $1;
			  }
;

simpleassignment:       IDENTIFIERTOKEN EQUALTOKEN thing 
                          {
			    $$ = makeAssignment($1, $3);
			    free($1);
			  }
                      | IDENTIFIERTOKEN ASSIGNEQUALTOKEN thing 
                          {
			    $$ = makeFloatAssignment($1, $3);
			    free($1);
			  }
                      | IDENTIFIERTOKEN EQUALTOKEN LIBRARYTOKEN LPARTOKEN thing RPARTOKEN 
                          {
			    $$ = makeLibraryBinding($1, $5);
			    free($1);
			  }
                      | indexing EQUALTOKEN thing 
                          {
			    $$ = makeAssignmentInIndexing($1->a,$1->b,$3);
			    free($1);
			  }
                      | indexing ASSIGNEQUALTOKEN thing 
                          {
			    $$ = makeFloatAssignmentInIndexing($1->a,$1->b,$3);
			    free($1);
			  }
;

stateassignment:        PRECTOKEN EQUALTOKEN thing              					       
                          {
			    $$ = makePrecAssign($3);
			  }
                      | POINTSTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makePointsAssign($3);
			  }
                      | DIAMTOKEN EQUALTOKEN thing              					       
                          {
			    $$ = makeDiamAssign($3);
			  }
                      | DISPLAYTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makeDisplayAssign($3);
			  }
                      | VERBOSITYTOKEN EQUALTOKEN thing         					       
                          {
			    $$ = makeVerbosityAssign($3);
			  }
                      | CANONICALTOKEN EQUALTOKEN thing         					       
                          {
			    $$ = makeCanonicalAssign($3);
			  }
                      | AUTOSIMPLIFYTOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeAutoSimplifyAssign($3);
			  }
                      | TAYLORRECURSIONSTOKEN EQUALTOKEN thing  					       
                          {
			    $$ = makeTaylorRecursAssign($3);
			  }
                      | TIMINGTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makeTimingAssign($3);
			  }
                      | FULLPARENTHESESTOKEN EQUALTOKEN thing   					       
                          {
			    $$ = makeFullParenAssign($3);
			  }
                      | MIDPOINTMODETOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeMidpointAssign($3);
			  }
                      | SUPPRESSWARNINGSTOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeSuppressWarningsAssign($3);
			  }
                      | HOPITALRECURSIONSTOKEN EQUALTOKEN thing  					       
                          {
			    $$ = makeHopitalRecursAssign($3);
			  }
;

stillstateassignment:   PRECTOKEN EQUALTOKEN thing              					       
                          {
			    $$ = makePrecStillAssign($3);
			  }
                      | POINTSTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makePointsStillAssign($3);
			  }
                      | DIAMTOKEN EQUALTOKEN thing              					       
                          {
			    $$ = makeDiamStillAssign($3);
			  }
                      | DISPLAYTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makeDisplayStillAssign($3);
			  }
                      | VERBOSITYTOKEN EQUALTOKEN thing         					       
                          {
			    $$ = makeVerbosityStillAssign($3);
			  }
                      | CANONICALTOKEN EQUALTOKEN thing         					       
                          {
			    $$ = makeCanonicalStillAssign($3);
			  }
                      | AUTOSIMPLIFYTOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeAutoSimplifyStillAssign($3);
			  }
                      | TAYLORRECURSIONSTOKEN EQUALTOKEN thing  					       
                          {
			    $$ = makeTaylorRecursStillAssign($3);
			  }
                      | TIMINGTOKEN EQUALTOKEN thing            					       
                          {
			    $$ = makeTimingStillAssign($3);
			  }
                      | FULLPARENTHESESTOKEN EQUALTOKEN thing   					       
                          {
			    $$ = makeFullParenStillAssign($3);
			  }
                      | MIDPOINTMODETOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeMidpointStillAssign($3);
			  }
                      | SUPPRESSWARNINGSTOKEN EQUALTOKEN thing      					       
                          {
			    $$ = makeSuppressWarningsStillAssign($3);
			  }
                      | HOPITALRECURSIONSTOKEN EQUALTOKEN thing  					       
                          {
			    $$ = makeHopitalRecursStillAssign($3);
			  }
;

thinglist:              thing
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | thing COMMATOKEN thinglist
                          {
			    $$ = addElement($3, $1);
			  }
;

thing:                  megaterm
                          {
			    $$ = $1;
			  }
                      | thing ANDTOKEN megaterm
                          {
			    $$ = makeAnd($1, $3);
			  }
                      | thing ORTOKEN megaterm
                          {
			    $$ = makeOr($1, $3);
			  }
                      | EXCLAMATIONTOKEN megaterm
                          {
			    $$ = makeNegation($2);
			  }
;

indexing:               basicthing LBRACKETTOKEN thing RBRACKETTOKEN 
                          {
			    $$ = (doubleNode *) safeMalloc(sizeof(doubleNode));
			    $$->a = $1;
			    $$->b = $3;
			  }
;


megaterm:               hyperterm
                          {
			    $$ = $1;
			  }
                      | megaterm COMPAREEQUALTOKEN hyperterm
                          {
			    $$ = makeCompareEqual($1, $3);
			  }
                      | megaterm LEFTANGLETOKEN hyperterm
                          {
			    $$ = makeCompareLess($1, $3);
			  }
                      | megaterm RIGHTANGLETOKEN hyperterm
                          {
			    $$ = makeCompareGreater($1, $3);
			  }
                      | megaterm LEFTANGLETOKEN EQUALTOKEN hyperterm
                          {
			    $$ = makeCompareLessEqual($1, $4);
			  }
                      | megaterm RIGHTANGLETOKEN EQUALTOKEN hyperterm
                          {
			    $$ = makeCompareGreaterEqual($1, $4);
			  }
                      | megaterm EXCLAMATIONEQUALTOKEN hyperterm
                          {
			    $$ = makeCompareNotEqual($1, $3);
			  }
;

hyperterm:                term
                          {
			    $$ = $1;
			  }
                      | hyperterm PLUSTOKEN term
                          {
			    $$ = makeAdd($1, $3);
			  }
                      | hyperterm MINUSTOKEN term
                          {
			    $$ = makeSub($1, $3);
			  }
                      | hyperterm ATTOKEN term
                          {
			    $$ = makeConcat($1, $3);
			  }
                      | hyperterm DOUBLECOLONTOKEN term
                          {
			    $$ = makeAddToList($1, $3);
			  }
                      | hyperterm DOTCOLONTOKEN term
                          {
			    $$ = makePrepend($1, $3);
			  }
                      | hyperterm COLONDOTTOKEN term
                          {
			    $$ = makeAppend($1, $3);
			  }
;

                           
term:                   subterm						
			  {
			    $$ = $1;
                          }			
		      |	MINUSTOKEN subterm			
                          {
			    $$ = makeNeg($2);
                          }				
		      |	APPROXTOKEN subterm			
                          {
			    $$ = makeEvalConst($2);
                          }				
		      |	PLUSTOKEN subterm			
                          {
			    $$ = $2;
                          }				
		      |	term MULTOKEN subterm				
			  {
			    $$ = makeMul($1, $3);
                          }														
		      |	term DIVTOKEN subterm				
                          {
			    $$ = makeDiv($1, $3);
                          }					
		      |	term MULTOKEN MINUSTOKEN subterm				
			  {
			    $$ = makeMul($1, makeNeg($4));
                          }														
		      |	term DIVTOKEN MINUSTOKEN subterm				
                          {
			    $$ = makeDiv($1, makeNeg($4));
                          }					
		      |	term MULTOKEN PLUSTOKEN subterm				
			  {
			    $$ = makeMul($1, $4);
                          }														
		      |	term DIVTOKEN PLUSTOKEN subterm				
                          {
			    $$ = makeDiv($1, $4);
                          }					
;

subterm:                basicthing
                          {
			    $$ = $1;
                          }
                      | basicthing POWTOKEN subterm
                          {
			    $$ = makePow($1, $3);
                          }
                      | basicthing POWTOKEN MINUSTOKEN subterm
                          {
			    $$ = makePow($1, makeNeg($4));
                          }
                      | basicthing POWTOKEN PLUSTOKEN subterm
                          {
			    $$ = makePow($1, $4);
                          }
;


basicthing:             ONTOKEN                 					       
                          {
			    $$ = makeOn();
			  }
                      | OFFTOKEN                					       
                          {
			    $$ = makeOff();
			  }
                      | DYADICTOKEN   						       
                          {
			    $$ = makeDyadic();
			  }
                      | POWERSTOKEN             					                                
                          {
			    $$ = makePowers();
			  }
                      | BINARYTOKEN             					       
                          {
			    $$ = makeBinaryThing();
			  }
                      | HEXADECIMALTOKEN             					       
                          {
			    $$ = makeHexadecimalThing();
			  }
                      | FILETOKEN               					       
                          {
			    $$ = makeFile();
			  }
                      | POSTSCRIPTTOKEN         					       
                          {
			    $$ = makePostscript();
			  }
                      | POSTSCRIPTFILETOKEN     					       
                          {
			    $$ = makePostscriptFile();
			  }
                      | PERTURBTOKEN            					       
                          {
			    $$ = makePerturb();
			  }
                      | MINUSWORDTOKEN          					       
                          {
			    $$ = makeRoundDown();
			  }
                      | PLUSWORDTOKEN           					       
                          {
			    $$ = makeRoundUp();
			  }
                      | ZEROWORDTOKEN           					       
                          {
			    $$ = makeRoundToZero();
			  }
                      | NEARESTTOKEN            					       
                          {
			    $$ = makeRoundToNearest();
			  }
                      | HONORCOEFFPRECTOKEN    					       
                          {
			    $$ = makeHonorCoeff();
			  }
                      | TRUETOKEN   							       
                          {
			    $$ = makeTrue();
			  }
                      | VOIDTOKEN   							       
                          {
			    $$ = makeUnit();
			  }
                      | FALSETOKEN   							       
                          {
			    $$ = makeFalse();
			  }
                      | DEFAULTTOKEN   							       
                          {
			    $$ = makeDefault();
			  }
                      | DECIMALTOKEN   							       
                          {
			    $$ = makeDecimal();
			  }
                      | ABSOLUTETOKEN   							       
                          {
			    $$ = makeAbsolute();
			  }
                      | RELATIVETOKEN   							       
                          {
			    $$ = makeRelative();
			  }
                      | FIXEDTOKEN   							       
                          {
			    $$ = makeFixed();
			  }
                      | FLOATINGTOKEN   							       
                          {
			    $$ = makeFloating();
			  }
                      | ERRORTOKEN   							       
                          {
			    $$ = makeError();
			  }
                      | DOUBLETOKEN             					       
                          {
			    $$ = makeDoubleSymbol();
			  }
                      | DOUBLEEXTENDEDTOKEN             					       
                          {
			    $$ = makeDoubleextendedSymbol();
			  }
                      | DOUBLEDOUBLETOKEN   						       
                          {
			    $$ = makeDoubleDoubleSymbol();
			  }
                      | TRIPLEDOUBLETOKEN       					       
                          {
			    $$ = makeTripleDoubleSymbol();
			  }
                      | STRINGTOKEN
                          {
			    tempString = safeCalloc(strlen($1) + 1, sizeof(char));
			    strcpy(tempString, $1);
			    free($1);
			    tempString2 = safeCalloc(strlen(tempString) + 1, sizeof(char));
			    strcpy(tempString2, tempString);
			    free(tempString);
			    $$ = makeString(tempString2);
			    free(tempString2);
			  }
                      | constant
                          {
			    $$ = $1;
			  }
                      | IDENTIFIERTOKEN
                          {
			    $$ = makeTableAccess($1);
			    free($1);
			  }
                      | ISBOUNDTOKEN LPARTOKEN IDENTIFIERTOKEN RPARTOKEN
                          {
			    $$ = makeIsBound($3);
			    free($3);
			  }
                      | IDENTIFIERTOKEN LPARTOKEN thinglist RPARTOKEN
                          {
			    $$ = makeTableAccessWithSubstitute($1, $3);
			    free($1);
			  }
                      | IDENTIFIERTOKEN LPARTOKEN RPARTOKEN
                          {
			    $$ = makeTableAccessWithSubstitute($1, NULL);
			    free($1);
			  }
                      | list 
                          {
			    $$ = $1;
			  }
                      | range 
                          {
			    $$ = $1;
			  }
                      | debound 
                          {
			    $$ = $1;
			  }
                      | headfunction 
                          {
			    $$ = $1;
			  }
                      | LPARTOKEN thing RPARTOKEN
                          {
			    $$ = $2;
			  }
                      | statedereference
                          {
			    $$ = $1;
			  }
                      | indexing
                          {
			    $$ = makeIndex($1->a, $1->b);
			    free($1);
			  }
                      | LPARTOKEN thing RPARTOKEN LPARTOKEN thinglist RPARTOKEN
                          {
			    $$ = makeApply($2,$5);
			  }
                      | PROCTOKEN procbody
                          {
			    $$ = $2;
			  }
;


constant:               CONSTANTTOKEN          					       
                          {
			    $$ = makeDecimalConstant($1);
			    free($1);
			  }
                      | MIDPOINTCONSTANTTOKEN   					       
                          {
			    $$ = makeMidpointConstant($1);
			    free($1);
			  }
                      | DYADICCONSTANTTOKEN   					       
                          {
			    $$ = makeDyadicConstant($1);
			    free($1);
			  }
                      | HEXCONSTANTTOKEN       					       
                          {
			    $$ = makeHexConstant($1);
			    free($1);
			  }
                      | HEXADECIMALCONSTANTTOKEN       					       
                          {
			    $$ = makeHexadecimalConstant($1);
			    free($1);
			  }
                      | BINARYCONSTANTTOKEN    					       
                          {
			    $$ = makeBinaryConstant($1);
			    free($1);
			  }
                      | PITOKEN
                          {
			    $$ = makePi();
			  }
;



list:                   LBRACKETTOKEN VERTBARTOKEN VERTBARTOKEN RBRACKETTOKEN  
                          {
			    $$ = makeEmptyList();
			  }
                      | LBRACKETTOKEN ORTOKEN RBRACKETTOKEN  
                          {
			    $$ = makeEmptyList();
			  }
		      | LBRACKETTOKEN VERTBARTOKEN simplelist VERTBARTOKEN RBRACKETTOKEN
                          {
			    $$ = makeList($3);
			  }
                      | LBRACKETTOKEN VERTBARTOKEN simplelist DOTSTOKEN VERTBARTOKEN RBRACKETTOKEN
                          {
			    $$ = makeFinalEllipticList($3);
			  }
;

simplelist:             thing
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | thing COMMATOKEN simplelist
                          {
			    $$ = addElement($3, $1);
			  }
                      | thing COMMATOKEN DOTSTOKEN COMMATOKEN simplelist
                          {
			    $$ = addElement(addElement($5, makeElliptic()), $1);
			  }
;


range:                  LBRACKETTOKEN thing COMMATOKEN thing RBRACKETTOKEN
                          {
			    $$ = makeRange($2, $4);
			  }
                      | LBRACKETTOKEN thing SEMICOLONTOKEN thing RBRACKETTOKEN
                          {
			    $$ = makeRange($2, $4);
			  }
;

debound:                STARLEFTANGLETOKEN thing RIGHTANGLESTARTOKEN
                          {
			    $$ = makeDeboundMax($2);
			  }
                      | STARLEFTANGLETOKEN thing RIGHTANGLEDOTTOKEN
                          {
			    $$ = makeDeboundMid($2);
			  }
                      | STARLEFTANGLETOKEN thing RIGHTANGLEUNDERSCORETOKEN
                          {
			    $$ = makeDeboundMin($2);
			  }
                      | SUPTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDeboundMax($3);
			  }
                      | MIDTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDeboundMid($3);
			  }
                      | INFTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDeboundMin($3);
			  }
;

headfunction:           DIFFTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDiff($3);
			  }              					       
                      | SIMPLIFYTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSimplify($3);
			  }  						       
                      | REMEZTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeRemez(addElement(addElement($7, $5), $3));
			  }             					       
                      | FPMINIMAXTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeFPminimax(addElement(addElement(addElement($9, $7), $5), $3));
			  }
                      | HORNERTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeHorner($3);
			  }   
                      | CANONICALTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeCanonicalThing($3);
			  }            					       
                      | EXPANDTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeExpand($3);
			  }            					       
                      | SIMPLIFYSAFETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSimplifySafe($3);
			  }  						       
                      | TAYLORTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeTaylor($3, $5, $7);
			  }           					       
                      | DEGREETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDegree($3);
			  }            					       
                      | NUMERATORTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeNumerator($3);
			  }         					       
                      | DENOMINATORTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDenominator($3);
			  }       					       
                      | SUBSTITUTETOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeSubstitute($3, $5);
			  }        					       
                      | COEFFTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeCoeff($3, $5);
			  }             					       
                      | SUBPOLYTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeSubpoly($3, $5);
			  }           					       
                      | ROUNDCOEFFICIENTSTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeRoundcoefficients($3, $5);
			  }   					       
                      | RATIONALAPPROXTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeRationalapprox($3, $5);
			  }    					       
                      | ACCURATEINFNORMTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeAccurateInfnorm(addElement(addElement($7, $5), $3));
			  }    					       
                      | ROUNDTOFORMATTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeRoundToFormat($3, $5, $7);
			  }     					       
                      | EVALUATETOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeEvaluate($3, $5);
			  }          					       
                      | PARSETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeParse($3);
			  }             					       
                      | READXMLTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeReadXml($3);
			  }             					       
                      | INFNORMTOKEN LPARTOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeInfnorm(addElement($5, $3));
			  }           					       
                      | FINDZEROSTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeFindZeros($3, $5);
			  }         					       
                      | FPFINDZEROSTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeFPFindZeros($3, $5);
			  }       					       
                      | DIRTYINFNORMTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeDirtyInfnorm($3, $5);
			  }      					       
                      | INTEGRALTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeIntegral($3, $5);
			  }          					       
                      | DIRTYINTEGRALTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeDirtyIntegral($3, $5);
			  }  						       
                      | IMPLEMENTPOLYTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeImplementPoly(addElement(addElement(addElement(addElement(addElement($13, $11), $9), $7), $5), $3));
			  }  						       
                      | CHECKINFNORMTOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeCheckInfnorm($3, $5, $7);
			  }      					       
                      | ZERODENOMINATORSTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeZeroDenominators($3, $5);
			  }  					       
                      | ISEVALUABLETOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeIsEvaluable($3, $5);
			  }       					       
                      | SEARCHGALTOKEN LPARTOKEN thinglist RPARTOKEN
                          {
			    $$ = makeSearchGal($3);
			  }         					       
                      | GUESSDEGREETOKEN LPARTOKEN thing COMMATOKEN thing COMMATOKEN thinglist RPARTOKEN
                          {
			    $$ = makeGuessDegree(addElement(addElement($7, $5), $3));
			  }       					       
                      | DIRTYFINDZEROSTOKEN LPARTOKEN thing COMMATOKEN thing RPARTOKEN
                          {
			    $$ = makeDirtyFindZeros($3, $5);
			  }    					       
                      | HEADTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeHead($3);
			  }              					       
                      | ROUNDCORRECTLYTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeRoundCorrectly($3);
			  }              					       
                      | READFILETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeReadFile($3);
			  }              					       
                      | REVERTTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeRevert($3);
			  }              					       
                      | SORTTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSort($3);
			  }              					       
                      | MANTISSATOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeMantissa($3);
			  }              					       
                      | EXPONENTTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeExponent($3);
			  }              					       
                      | PRECISIONTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makePrecision($3);
			  }              					       
                      | TAILTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeTail($3);
			  }              					       
                      | SQRTTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSqrt($3);
			  }              					       
                      | EXPTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeExp($3);
			  }               					       
                      | LOGTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeLog($3);
			  }               					       
                      | LOG2TOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeLog2($3);
			  }              					       
                      | LOG10TOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeLog10($3);
			  }             					       
                      | SINTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSin($3);
			  }               					       
                      | COSTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeCos($3);
			  }               					       
                      | TANTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeTan($3);
			  }               					       
                      | ASINTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAsin($3);
			  }              					       
                      | ACOSTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAcos($3);
			  }              					       
                      | ATANTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAtan($3);
			  }              					       
                      | SINHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeSinh($3);
			  }              					       
                      | COSHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeCosh($3);
			  }              					       
                      | TANHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeTanh($3);
			  }              					       
                      | ASINHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAsinh($3);
			  }             					       
                      | ACOSHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAcosh($3);
			  }             					       
                      | ATANHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAtanh($3);
			  }             					       
                      | ABSTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeAbs($3);
			  }               					       
                      | ERFTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeErf($3);
			  }               					       
                      | ERFCTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeErfc($3);
			  }              					       
                      | LOG1PTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeLog1p($3);
			  }             					       
                      | EXPM1TOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeExpm1($3);
			  }             					       
                      | DOUBLETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDouble($3);
			  }            					       
                      | DOUBLEDOUBLETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDoubledouble($3);
			  }  						       
                      | TRIPLEDOUBLETOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeTripledouble($3);
			  }      					       
                      | DOUBLEEXTENDEDTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeDoubleextended($3);
			  }    					       
                      | CEILTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeCeil($3);
			  }              					       
                      | FLOORTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeFloor($3);
			  }             					       
                      | LENGTHTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeLength($3);
			  }
;

egalquestionmark:       EQUALTOKEN QUESTIONMARKTOKEN
                          {
			    $$ = NULL;
			  }
                      | 
                          {
			    $$ = NULL;
			  }
;

statedereference:       PRECTOKEN egalquestionmark
                          {
			    $$ = makePrecDeref();
			  }
                      | POINTSTOKEN egalquestionmark            					       
                          {
			    $$ = makePointsDeref();
			  }
                      | DIAMTOKEN egalquestionmark              					       
                          {
			    $$ = makeDiamDeref();
			  }
                      | DISPLAYTOKEN egalquestionmark            					       
                          {
			    $$ = makeDisplayDeref();
			  }
                      | VERBOSITYTOKEN egalquestionmark         					       
                          {
			    $$ = makeVerbosityDeref();
			  }
                      | CANONICALTOKEN egalquestionmark         					       
                          {
			    $$ = makeCanonicalDeref();
			  }
                      | AUTOSIMPLIFYTOKEN egalquestionmark				       
                          {
			    $$ = makeAutoSimplifyDeref();
			  }
                      | TAYLORRECURSIONSTOKEN egalquestionmark				       
                          {
			    $$ = makeTaylorRecursDeref();
			  }
                      | TIMINGTOKEN egalquestionmark			       
                          {
			    $$ = makeTimingDeref();
			  }
                      | FULLPARENTHESESTOKEN egalquestionmark					       
                          {
			    $$ = makeFullParenDeref();
			  }
                      | MIDPOINTMODETOKEN egalquestionmark			       
                          {
			    $$ = makeMidpointDeref();
			  }
                      | SUPPRESSWARNINGSTOKEN egalquestionmark			       
                          {
			    $$ = makeSuppressWarningsDeref();
			  }
                      | HOPITALRECURSIONSTOKEN egalquestionmark				       
                          {
			    $$ = makeHopitalRecursDeref();
			  }
;

externalproctype:       CONSTANTTYPETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = CONSTANT_TYPE;
			    $$ = tempIntPtr;
			  }
                      | FUNCTIONTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = FUNCTION_TYPE;
			    $$ = tempIntPtr;
			  }
                      | RANGETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = RANGE_TYPE;
			    $$ = tempIntPtr;
			  }
                      | INTEGERTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = INTEGER_TYPE;
			    $$ = tempIntPtr;
			  }
                      | STRINGTYPETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = STRING_TYPE;
			    $$ = tempIntPtr;
			  }
                      | BOOLEANTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = BOOLEAN_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN CONSTANTTYPETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = CONSTANT_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN FUNCTIONTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = FUNCTION_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN RANGETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = RANGE_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN INTEGERTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = INTEGER_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN STRINGTYPETOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = STRING_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
                      | LISTTOKEN OFTOKEN BOOLEANTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = BOOLEAN_LIST_TYPE;
			    $$ = tempIntPtr;
			  }
;

extendedexternalproctype: VOIDTOKEN
                          {
			    tempIntPtr = (int *) safeMalloc(sizeof(int));
			    *tempIntPtr = VOID_TYPE;
			    $$ = tempIntPtr;
			  }
                      | externalproctype
		          {
			    $$ = $1;
		          }
;


externalproctypesimplelist:   externalproctype
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | externalproctype COMMATOKEN externalproctypesimplelist
                          {
			    $$ = addElement($3, $1);
			  }
;

externalproctypelist:       extendedexternalproctype
                          {
			    $$ = addElement(NULL, $1);
			  }
                      | LPARTOKEN externalproctypesimplelist RPARTOKEN 
                          {
			    $$ = $2;
			  }
;


help:                   CONSTANTTOKEN
                          {
			    outputMode(); printf("\"%s\" is recognized as a base 10 constant.\n",$1);
			    free($1);
			  }          					       
                      | DYADICCONSTANTTOKEN
                          {
			    outputMode(); printf("\"%s\" is recognized as a dyadic number constant.\n",$1);
			    free($1);
                          }   					       
                      | HEXCONSTANTTOKEN
                          {
			    outputMode(); printf("\"%s\" is recognized as a double or single precision constant.\n",$1);
			    free($1);
                          }       					       
                      | HEXADECIMALCONSTANTTOKEN
                          {
			    outputMode(); printf("\"%s\" is recognized as a hexadecimal constant.\n",$1);
			    free($1);
                          }       					       
                      | BINARYCONSTANTTOKEN
                          {
			    outputMode(); printf("\"%s_2\" is recognized as a base 2 constant.\n",$1);
			    free($1);
                          }    					       
                      | PITOKEN
                          {
#ifdef HELP_PI_TEXT
			    outputMode(); printf(HELP_PI_TEXT);
#else
			    outputMode(); printf("Ratio circonference and diameter of a circle.\n");
#endif
                          }                					       
                      | IDENTIFIERTOKEN
                          {
			    outputMode(); printf("\"%s\" is an identifier.\n",$1);
			    free($1);
                          }          					       
                      | STRINGTOKEN
                          {
			    outputMode(); printf("\"%s\" is a string constant.\n",$1);
			    free($1);
                          }            					       
                      | LPARTOKEN
                          {
			    outputMode(); printf("Left parenthesis.\n");
                          }                  					       
                      | RPARTOKEN
                          {
			    outputMode(); printf("Right parenthesis.\n");
                          }                  					       
                      | LBRACKETTOKEN
                          {
			    outputMode(); printf("Left bracket - indicates a range.\n");
                          }              					       
                      | RBRACKETTOKEN
                          {
			    outputMode(); printf("Right bracket - indicates a range.\n");
                          }
                      | LBRACKETTOKEN VERTBARTOKEN
                          {
			    outputMode(); printf("Left bracket-bar - indicates a list.\n");
                          }              					       
                      | VERTBARTOKEN RBRACKETTOKEN 
                          {
			    outputMode(); printf("Bar-right bracket - indicates a list.\n");
                          }              					       
                      | EQUALTOKEN
                          {
#ifdef HELP_ASSIGNMENT_TEXT
			    outputMode(); printf(HELP_ASSIGNMENT_TEXT);
#else
			    outputMode(); printf("Assignment operator.\n");
#endif
                          }       
                      | ASSIGNEQUALTOKEN
                          {
#ifdef HELP_FLOATASSIGNMENT_TEXT
			    outputMode(); printf(HELP_FLOATASSIGNMENT_TEXT);
#else
			    outputMode(); printf("Evaluating assignment operator.\n");
#endif
                          }                 					       
                      | COMPAREEQUALTOKEN
                          {
#ifdef HELP_EQUAL_TEXT
			    outputMode(); printf(HELP_EQUAL_TEXT);
#else
			    outputMode(); printf("Equality test.\n");
#endif
                          }                 					       
                      | COMMATOKEN
                          {
			    outputMode(); printf("Separator in lists or ranges.\n");
                          }                 					       
                      | EXCLAMATIONTOKEN
                          {
#ifdef HELP_NOT_TEXT
			    outputMode(); printf(HELP_NOT_TEXT);
#else
			    outputMode(); printf("Suppresses output on assignments or boolean negation.\n");
#endif
                          }      						       
                      | STARLEFTANGLETOKEN
                          {
			    outputMode(); printf("Dereferences range bounds.\n");
                          }             					       
                      | LEFTANGLETOKEN
                          {
#ifdef HELP_LT_TEXT
			    outputMode(); printf(HELP_LT_TEXT);
#else
			    outputMode(); printf("Comparison less than.\n");
#endif
                          }            
                      | LEFTANGLETOKEN EQUALTOKEN
                          {
#ifdef HELP_LE_TEXT
			    outputMode(); printf(HELP_LE_TEXT);
#else
			    outputMode(); printf("Comparison less than or equal to.\n");
#endif
                          }             					       
                      | RIGHTANGLEUNDERSCORETOKEN
                          {
			    outputMode(); printf("Dereferences the lower range bound.\n");
                          }      					       
                      | RIGHTANGLEDOTTOKEN
                          {
			    outputMode(); printf("Dereferences the mid-point of a range.\n");
                          }       					       
                      | RIGHTANGLETOKEN EQUALTOKEN
                          {
#ifdef HELP_GE_TEXT
			    outputMode(); printf(HELP_GE_TEXT);
#else
			    outputMode(); printf("Comparison greater than or equal to.\n");
#endif
			  }
                      | RIGHTANGLESTARTOKEN
                          {
			    outputMode(); printf("Dereferences the upper range bound.\n");
                          }             					       
                      | RIGHTANGLETOKEN
                          {
#ifdef HELP_GT_TEXT
			    outputMode(); printf(HELP_GT_TEXT);
#else
			    outputMode(); printf("Comparison greater than.\n");
#endif
                          }            					       
                      | DOTSTOKEN
                          {
			    outputMode(); printf("Ellipsis.\n");
                          }                  					       
                      | QUESTIONMARKTOKEN
                          {
			    outputMode(); printf("Dereferences global environment variables.\n");
                          }      						       
                      | VERTBARTOKEN
                          {
			    outputMode(); printf("Starts or ends a list.\n");
                          }      						       
                      | ATTOKEN
                          {
#ifdef HELP_CONCAT_TEXT
			    outputMode(); printf(HELP_CONCAT_TEXT);
#else
			    outputMode(); printf("Concatenation of lists or strings.\n");
#endif
                          }      							       
                      | DOUBLECOLONTOKEN
                          {
			    outputMode(); printf("a::b prepends a to list b or appends b to list a, preprending list a to list b if both are lists.\n");
                          }    
                      | DOTCOLONTOKEN
                          {
#ifdef HELP_PREPEND_TEXT
			    outputMode(); printf(HELP_PREPEND_TEXT);
#else
			    outputMode(); printf("a.:b prepends a to list b.\n");
#endif
                          }    
                      | COLONDOTTOKEN
                          {
#ifdef HELP_APPEND_TEXT
			    outputMode(); printf(HELP_APPEND_TEXT);
#else
			    outputMode(); printf("a:.b appends b to list a.\n");
#endif
                          }    
                      | EXCLAMATIONEQUALTOKEN
                          {
#ifdef HELP_NEQ_TEXT
			    outputMode(); printf(HELP_NEQ_TEXT);
#else
			    outputMode(); printf("Comparison not equal.\n");
#endif
                          }    
                      | ANDTOKEN
                          {
#ifdef HELP_AND_TEXT
			    outputMode(); printf(HELP_AND_TEXT);
#else
			    outputMode(); printf("Boolean and.\n");
#endif
                          }    
                      | ORTOKEN
                          {
#ifdef HELP_OR_TEXT
			    outputMode(); printf(HELP_OR_TEXT);
#else
			    outputMode(); printf("Boolean or.\n");
#endif
                          }    
                      | PLUSTOKEN
                          {
#ifdef HELP_PLUS_TEXT
			    outputMode(); printf(HELP_PLUS_TEXT);
#else
			    outputMode(); printf("Addition.\n");
#endif
                          }                  					       
                      | MINUSTOKEN
                          {
#ifdef HELP_MINUS_TEXT
			    outputMode(); printf(HELP_MINUS_TEXT);
#else
			    outputMode(); printf("Substraction.\n");
#endif
                          }                 					       
                      | APPROXTOKEN
                          {
#ifdef HELP_APPROX_TEXT
			    outputMode(); printf(HELP_APPROX_TEXT);
#else
			    outputMode(); printf("Floating-point approximation of a constant expression.\n");
#endif
                          }                 					       
                      | MULTOKEN
                          {
#ifdef HELP_MULT_TEXT
			    outputMode(); printf(HELP_MULT_TEXT);
#else
			    outputMode(); printf("Multiplication.\n");
#endif
                          }                						       
                      | DIVTOKEN
                          {
#ifdef HELP_DIVIDE_TEXT
			    outputMode(); printf(HELP_DIVIDE_TEXT);
#else
			    outputMode(); printf("Division.\n");
#endif
                          }                  					       
                      | POWTOKEN
                          {
#ifdef HELP_POWER_TEXT
			    outputMode(); printf(HELP_POWER_TEXT);
#else
			    outputMode(); printf("Exponentiation.\n");
#endif
                          }                  					       
                      | SQRTTOKEN
                          {
#ifdef HELP_SQRT_TEXT
			    outputMode(); printf(HELP_SQRT_TEXT);
#else
			    outputMode(); printf("Square root.\n");
#endif
                          }                  					       
                      | EXPTOKEN
                          {
#ifdef HELP_EXP_TEXT
			    outputMode(); printf(HELP_EXP_TEXT);
#else
			    outputMode(); printf("Exponential.\n");
#endif
                          }                   					       
                      | LOGTOKEN
                          {
#ifdef HELP_LOG_TEXT
			    outputMode(); printf(HELP_LOG_TEXT);
#else
			    outputMode(); printf("Natural logarithm.\n");
#endif
                          }                   					       
                      | LOG2TOKEN
                          {
#ifdef HELP_LOG2_TEXT
			    outputMode(); printf(HELP_LOG2_TEXT);
#else
			    outputMode(); printf("Logarithm in base 2.\n");
#endif
                          }                  					       
                      | LOG10TOKEN
                          {
#ifdef HELP_LOG10_TEXT
			    outputMode(); printf(HELP_LOG10_TEXT);
#else
			    outputMode(); printf("Logarithm in base 10.\n");
#endif
                          }                 					       
                      | SINTOKEN
                          {
#ifdef HELP_SIN_TEXT
			    outputMode(); printf(HELP_SIN_TEXT);
#else
			    outputMode(); printf("Sine.\n");
#endif
                          }                   					       
                      | COSTOKEN
                          {
#ifdef HELP_COS_TEXT
			    outputMode(); printf(HELP_COS_TEXT);
#else
			    outputMode(); printf("Cosine.\n");
#endif
                          }                   					       
                      | TANTOKEN
                          {
#ifdef HELP_TAN_TEXT
			    outputMode(); printf(HELP_TAN_TEXT);
#else
			    outputMode(); printf("Tangent.\n");
#endif
                          }                   					       
                      | ASINTOKEN
                          {
#ifdef HELP_ASIN_TEXT
			    outputMode(); printf(HELP_ASIN_TEXT);
#else
			    outputMode(); printf("Arcsine.\n");
#endif
                          }                  					       
                      | ACOSTOKEN
                          {
#ifdef HELP_ACOS_TEXT
			    outputMode(); printf(HELP_ACOS_TEXT);
#else
			    outputMode(); printf("Arcosine.\n");
#endif
                          }                  					       
                      | ATANTOKEN
                          {
#ifdef HELP_ATAN_TEXT
			    outputMode(); printf(HELP_ATAN_TEXT);
#else
			    outputMode(); printf("Arctangent.\n");
#endif
                          }                  					       
                      | SINHTOKEN
                          {
#ifdef HELP_SINH_TEXT
			    outputMode(); printf(HELP_SINH_TEXT);
#else
			    outputMode(); printf("Hyperbolic sine.\n");
#endif
                          }                  					       
                      | COSHTOKEN
                          {
#ifdef HELP_COSH_TEXT
			    outputMode(); printf(HELP_COSH_TEXT);
#else
			    outputMode(); printf("Hyperbolic cosine.\n");
#endif
                          }                  					       
                      | TANHTOKEN
                          {
#ifdef HELP_TANH_TEXT
			    outputMode(); printf(HELP_TANH_TEXT);
#else
			    outputMode(); printf("Hyperbolic tangent.\n");
#endif
                          }                  					       
                      | ASINHTOKEN
                          {
#ifdef HELP_ASINH_TEXT
			    outputMode(); printf(HELP_ASINH_TEXT);
#else
			    outputMode(); printf("Area sine.\n");
#endif
                          }                 					       
                      | ACOSHTOKEN
                          {
#ifdef HELP_ACOSH_TEXT
			    outputMode(); printf(HELP_ACOSH_TEXT);
#else
			    outputMode(); printf("Area cosine.\n");
#endif
                          }                 					       
                      | ATANHTOKEN
                          {
#ifdef HELP_ATANH_TEXT
			    outputMode(); printf(HELP_ATANH_TEXT);
#else

			    outputMode(); printf("Area tangent.\n");
#endif
                          }                 					                        					       
                      | ABSTOKEN
                          {
#ifdef HELP_ABS_TEXT
			    outputMode(); printf(HELP_ABS_TEXT);
#else
			    outputMode(); printf("Absolute value.\n");
#endif
                          }                 					                          					       
                      | ERFTOKEN
                          {
#ifdef HELP_ERF_TEXT
			    outputMode(); printf(HELP_ERF_TEXT);
#else
			    outputMode(); printf("Error function.\n");
#endif
                          }                 					                          					       
                      | ERFCTOKEN
                          {
#ifdef HELP_ERFC_TEXT
			    outputMode(); printf(HELP_ERFC_TEXT);
#else
			    outputMode(); printf("Complementary error function.\n");
#endif
                          }                 					                         					       
                      | LOG1PTOKEN
                          {
#ifdef HELP_LOG1P_TEXT
			    outputMode(); printf(HELP_LOG1P_TEXT);
#else
			    outputMode(); printf("Natural logarithm of 1 plus argument.\n");
#endif
                          }                 					                        					       
                      | EXPM1TOKEN
                          {
#ifdef HELP_EXPM1_TEXT
			    outputMode(); printf(HELP_EXPM1_TEXT);
#else
			    outputMode(); printf("Exponential of argument minus 1.\n");
#endif
                          }                 					                        					       
                      | DOUBLETOKEN
                          {
#ifdef HELP_DOUBLE_TEXT
			    outputMode(); printf(HELP_DOUBLE_TEXT);
#else
			    outputMode(); printf("Double precision rounding operator.\n");
#endif
                          }                 					                       					       
                      | DOUBLEDOUBLETOKEN
                          {
#ifdef HELP_DOUBLEDOUBLE_TEXT
			    outputMode(); printf(HELP_DOUBLEDOUBLE_TEXT);
#else
			    outputMode(); printf("Double-double precision rounding operator.\n");
#endif
                          }                 					             						       
                      | TRIPLEDOUBLETOKEN
                          {
#ifdef HELP_TRIPLEDOUBLE_TEXT
			    outputMode(); printf(HELP_TRIPLEDOUBLE_TEXT);
#else
			    outputMode(); printf("Triple-double precision rounding operator.\n");
#endif
                          }                 					                 					       
                      | DOUBLEEXTENDEDTOKEN
                          {
#ifdef HELP_DOUBLEEXTENDED_TEXT
			    outputMode(); printf(HELP_DOUBLEEXTENDED_TEXT);
#else
			    outputMode(); printf("Double-extended precision rounding operator.\n");
#endif
                          }                 					               					       
                      | CEILTOKEN
                          {
#ifdef HELP_CEIL_TEXT
			    outputMode(); printf(HELP_CEIL_TEXT);
#else
			    outputMode(); printf("Ceiling.\n");
#endif
                          }                 					                         					       
                      | FLOORTOKEN
                          {
#ifdef HELP_FLOOR_TEXT
			    outputMode(); printf(HELP_FLOOR_TEXT);
#else
			    outputMode(); printf("Floor.\n");
#endif
                          }                 					                        			
                      | HEADTOKEN
                          {
#ifdef HELP_HEAD_TEXT
			    outputMode(); printf(HELP_HEAD_TEXT);
#else
			    outputMode(); printf("Head of a list.\n");
#endif
                          }                 					       
                      | ROUNDCORRECTLYTOKEN
                          {
#ifdef HELP_ROUNDCORRECTLY_TEXT
			    outputMode(); printf(HELP_ROUNDCORRECTLY_TEXT);
#else
			    outputMode(); printf("Round a bounding to the nearest floating-point value such that correct rounding is possible.\n");
#endif
                          }                 					       
                      | READFILETOKEN
                          {
#ifdef HELP_READFILE_TEXT
			    outputMode(); printf(HELP_READFILE_TEXT);
#else
			    outputMode(); printf("Reads a file into a string.\n");
#endif
                          }                 					           
                      | REVERTTOKEN
                          {
#ifdef HELP_REVERT_TEXT
			    outputMode(); printf(HELP_REVERT_TEXT);
#else
			    outputMode(); printf("Reverts a list that is not finally elliptic.\n");
#endif
                          }                 					       
                      | SORTTOKEN
                          {
#ifdef HELP_SORT_TEXT
			    outputMode(); printf(HELP_SORT_TEXT);
#else
			    outputMode(); printf("Sorts a list of constants in ascending order.\n");
#endif
                          }                 					       
                      | TAILTOKEN
                          {
#ifdef HELP_TAIL_TEXT
			    outputMode(); printf(HELP_TAIL_TEXT);
#else
			    outputMode(); printf("Tail of a list.\n");
#endif
                          }                 					       
                      | PRECTOKEN
                          {
#ifdef HELP_PREC_TEXT
			    outputMode(); printf(HELP_PREC_TEXT);
#else
			    outputMode(); printf("Global environment variable precision.\n");
#endif
                          }                 					       
                      | POINTSTOKEN
                          {
#ifdef HELP_POINTS_TEXT
			    outputMode(); printf(HELP_POINTS_TEXT);
#else
			    outputMode(); printf("Global environment variable number of points.\n");
#endif
                          }                 					                       					       
                      | DIAMTOKEN
                          {
#ifdef HELP_DIAM_TEXT
			    outputMode(); printf(HELP_DIAM_TEXT);
#else
			    outputMode(); printf("Global environment variable diameter.\n");
#endif
                          }                 					                         					       
                      | DISPLAYTOKEN
                          {
#ifdef HELP_DISPLAY_TEXT
			    outputMode(); printf(HELP_DISPLAY_TEXT);
#else
			    outputMode(); printf("Global environment variable display mode.\n");
#endif
                          }                 					                       					       
                      | VERBOSITYTOKEN
                          {
#ifdef HELP_VERBOSITY_TEXT
			    outputMode(); printf(HELP_VERBOSITY_TEXT);
#else
			    outputMode(); printf("Global environment variable verbosity.\n");
#endif
                          }                 					                    					       
                      | CANONICALTOKEN
                          {
#ifdef HELP_CANONICAL_TEXT
			    outputMode(); printf(HELP_CANONICAL_TEXT);
#else
			    outputMode(); printf("Global environment variable canonical output.\n");
#endif
                          }                 					                    					       
                      | AUTOSIMPLIFYTOKEN
                          {
#ifdef HELP_AUTOSIMPLIFY_TEXT
			    outputMode(); printf(HELP_AUTOSIMPLIFY_TEXT);
#else
			    outputMode(); printf("Global environment variable automatic simplification.\n");
#endif
                          }                 					                 					       
                      | TAYLORRECURSIONSTOKEN
                          {
#ifdef HELP_TAYLORRECURSIONS_TEXT
			    outputMode(); printf(HELP_TAYLORRECURSIONS_TEXT);
#else
			    outputMode(); printf("Global environment variable recursions of Taylor evaluation.\n");
#endif
                          }                 					             					       
                      | TIMINGTOKEN
                          {
#ifdef HELP_TIMING_TEXT
			    outputMode(); printf(HELP_TIMING_TEXT);
#else
			    outputMode(); printf("Global environment variable timing of computations.\n");
#endif
                          }                 					                       					       
                      | FULLPARENTHESESTOKEN
                          {
#ifdef HELP_FULLPARENTHESES_TEXT
			    outputMode(); printf(HELP_FULLPARENTHESES_TEXT);
#else
			    outputMode(); printf("Global environment variable fully parenthized mode.\n");
#endif
                          }                 					              					       
                      | MIDPOINTMODETOKEN
                          {
#ifdef HELP_MIDPOINTMODE_TEXT
			    outputMode(); printf(HELP_MIDPOINTMODE_TEXT);
#else
			    outputMode(); printf("Global environment variable midpoint mode.\n");
#endif
                          }                 	
                      | SUPPRESSWARNINGSTOKEN
                          {
#ifdef HELP_ROUNDINGWARNINGS_TEXT
			    outputMode(); printf(HELP_ROUNDINGWARNINGS_TEXT);
#else
			    outputMode(); printf("Global environment variable activating warnings about rounding.\n");
#endif
                          }                 						                 					       
                      | HOPITALRECURSIONSTOKEN
                          {
#ifdef HELP_HOPITALRECURSIONS_TEXT
			    outputMode(); printf(HELP_HOPITALRECURSIONS_TEXT);
#else
			    outputMode(); printf("Global environment variable recursions of Hopital evaluation.\n");
#endif
                          }                 					             					       
                      | ONTOKEN
                          {
#ifdef HELP_ON_TEXT
			    outputMode(); printf(HELP_ON_TEXT);
#else
			    outputMode(); printf("Something is switched on.\n");
#endif
                          }                 					                           					       
                      | OFFTOKEN
                          {
#ifdef HELP_OFF_TEXT
			    outputMode(); printf(HELP_OFF_TEXT);
#else
			    outputMode(); printf("Something is switched off.\n");
#endif
                          }                 					                          					       
                      | DYADICTOKEN
                          {
#ifdef HELP_DYADIC_TEXT
			    outputMode(); printf(HELP_DYADIC_TEXT);
#else
			    outputMode(); printf("Display mode is dyadic output.\n");
#endif
                          }                 					             						       
                      | POWERSTOKEN
                          {
#ifdef HELP_POWERS_TEXT
			    outputMode(); printf(HELP_POWERS_TEXT);
#else
			    outputMode(); printf("Display mode is dyadic output with powers.\n");
#endif
                          }                 					                       					       
                      | BINARYTOKEN
                          {
#ifdef HELP_BINARY_TEXT
			    outputMode(); printf(HELP_BINARY_TEXT);
#else
			    outputMode(); printf("Display mode is binary.\n");
#endif
                          }                 					                       					       
                      | HEXADECIMALTOKEN
                          {
#ifdef HELP_HEXADECIMAL_TEXT
			    outputMode(); printf(HELP_HEXADECIMAL_TEXT);
#else
			    outputMode(); printf("Display mode is hexadecimal.\n");
#endif
                          }                 					                       					       
                      | FILETOKEN
                          {
#ifdef HELP_FILE_TEXT
			    outputMode(); printf(HELP_FILE_TEXT);
#else
			    outputMode(); printf("A file will be specified.\n");
#endif
                          }                 					                         					       
                      | POSTSCRIPTTOKEN
                          {
#ifdef HELP_POSTSCRIPT_TEXT
			    outputMode(); printf(HELP_POSTSCRIPT_TEXT);
#else
			    outputMode(); printf("A postscript file will be specified.\n");
#endif
                          }                 					                   					       
                      | POSTSCRIPTFILETOKEN
                          {
#ifdef HELP_POSTSCRIPTFILE_TEXT
			    outputMode(); printf(HELP_POSTSCRIPTFILE_TEXT);
#else
			    outputMode(); printf("A postscript file and a file will be specified.\n");
#endif
                          }                 					               					       
                      | PERTURBTOKEN
                          {
#ifdef HELP_PERTURB_TEXT
			    outputMode(); printf(HELP_PERTURB_TEXT);
#else
			    outputMode(); printf("Perturbation is demanded.\n");
#endif
                          }                 					                      					       
                      | MINUSWORDTOKEN
                          {
#ifdef HELP_RD_TEXT
			    outputMode(); printf(HELP_RD_TEXT);
#else
			    outputMode(); printf("Round towards minus infinity.\n");
#endif
                          }                 					                    					       
                      | PLUSWORDTOKEN
                          {
#ifdef HELP_RU_TEXT
			    outputMode(); printf(HELP_RU_TEXT);
#else
			    outputMode(); printf("Round towards plus infinity.\n");
#endif
                          }                 					                     					       
                      | ZEROWORDTOKEN
                          {
#ifdef HELP_RZ_TEXT
			    outputMode(); printf(HELP_RZ_TEXT);
#else
			    outputMode(); printf("Round towards zero.\n");
#endif
                          }                 					                     					       
                      | NEARESTTOKEN
                          {
#ifdef HELP_RN_TEXT
			    outputMode(); printf(HELP_RN_TEXT);
#else
			    outputMode(); printf("Round to nearest.\n");
#endif
                          }                 					                      					       
                      | HONORCOEFFPRECTOKEN
                          {
#ifdef HELP_HONORCOEFFPREC_TEXT
			    outputMode(); printf(HELP_HONORCOEFFPREC_TEXT);
#else
			    outputMode(); printf("Honorate the precision of the coefficients.\n");
#endif
                          }                 					              					       
                      | TRUETOKEN
                          {
#ifdef HELP_TRUE_TEXT
			    outputMode(); printf(HELP_TRUE_TEXT);
#else
			    outputMode(); printf("Boolean constant true.\n");
#endif
                          }                 					             							       
                      | FALSETOKEN
                          {
#ifdef HELP_FALSE_TEXT
			    outputMode(); printf(HELP_FALSE_TEXT);
#else
			    outputMode(); printf("Boolean constant false.\n");
#endif
                          }                 					             							       
                      | DEFAULTTOKEN
                          {
#ifdef HELP_DEFAULT_TEXT
			    outputMode(); printf(HELP_DEFAULT_TEXT);
#else
			    outputMode(); printf("Default value.\n");
#endif
                          }                        											       
                      | ABSOLUTETOKEN
                          {
#ifdef HELP_ABSOLUTE_TEXT
			    outputMode(); printf(HELP_ABSOLUTE_TEXT);
#else
			    outputMode(); printf("Consider an absolute error.\n");
#endif
                          }                 					       
                      | DECIMALTOKEN
                          {
#ifdef HELP_DECIMAL_TEXT
			    outputMode(); printf(HELP_DECIMAL_TEXT);
#else
			    outputMode(); printf("Display mode is decimal.\n");
#endif
                          }                 					       
                      | RELATIVETOKEN
                          {
#ifdef HELP_RELATIVE_TEXT
			    outputMode(); printf(HELP_RELATIVE_TEXT);
#else
			    outputMode(); printf("Consider a relative error.\n");
#endif
                          }
                      | FIXEDTOKEN
                          {
#ifdef HELP_FIXED_TEXT
			    outputMode(); printf(HELP_FIXED_TEXT);
#else
			    outputMode(); printf("Consider fixed-point numbers.\n");
#endif
                          }
                      | FLOATINGTOKEN
                          {
#ifdef HELP_FLOATING_TEXT
			    outputMode(); printf(HELP_FLOATING_TEXT);
#else
			    outputMode(); printf("Consider floating-point numbers.\n");
#endif
                          }                 					       
                      | ERRORTOKEN
                          {
#ifdef HELP_ERROR_TEXT
			    outputMode(); printf(HELP_ERROR_TEXT);
#else
			    outputMode(); printf("Type error meta-value.\n");
#endif
                          }                 					       
                      | QUITTOKEN
                          {
#ifdef HELP_QUIT_TEXT
			    outputMode(); printf(HELP_QUIT_TEXT);
#else
			    outputMode(); printf("Exit from the tool.\n");
#endif
                          }                 					                         					       
                      | FALSEQUITTOKEN
                          {
#ifdef HELP_QUIT_TEXT
			    outputMode(); printf(HELP_QUIT_TEXT);
#else
			    outputMode(); printf("Exit from the tool - help is called inside a read macro.\n");
#endif
                          }                 					             						       
                      | RESTARTTOKEN
                          {
#ifdef HELP_RESTART_TEXT
			    outputMode(); printf(HELP_RESTART_TEXT);
#else
			    outputMode(); printf("Restart the tool.\n");
#endif
                          }                 					                      					       
                      | LIBRARYTOKEN
                          {
#ifdef HELP_LIBRARY_TEXT
			    outputMode(); printf(HELP_LIBRARY_TEXT);
#else
			    outputMode(); printf("Library binding dereferencer.\n");
#endif
                          }                 					                      					       
                      | DIFFTOKEN
                          {
#ifdef HELP_DIFF_TEXT
			    outputMode(); printf(HELP_DIFF_TEXT);
#else
			    outputMode(); printf("Differentiation: diff(func).\n");
#endif
                          }                 					                         					       
                      | SIMPLIFYTOKEN
                          {
#ifdef HELP_SIMPLIFY_TEXT
			    outputMode(); printf(HELP_SIMPLIFY_TEXT);
#else
			    outputMode(); printf("Simplify: simplify(func).\n");
#endif
                          }                 					             						       
                      | REMEZTOKEN
                          {
#ifdef HELP_REMEZ_TEXT
			    outputMode(); printf(HELP_REMEZ_TEXT);
#else
			    outputMode(); printf("Remez: remez(func,degree|monoms,range[,weight[,quality]]).\n");
#endif
                          }                 					                        					       
                      | FPMINIMAXTOKEN
                          {
#ifdef HELP_FPMINIMAX_TEXT
			    outputMode(); printf(HELP_FPMINIMAX_TEXT);
#else
			    outputMode(); printf("Fpminimax: fpminimax(func,degree|monoms,formats,range|pointslist[,absolute|relative[,fixed|floating[,constrainedPart[, minimaxpoly]]]]).\n");
#endif
                          }                 					                        					       
                      | HORNERTOKEN
                          {
#ifdef HELP_HORNER_TEXT
			    outputMode(); printf(HELP_HORNER_TEXT);
#else
			    outputMode(); printf("Horner: horner(func)\n");
#endif
                          }                 					                       					       
                      | EXPANDTOKEN
                          {
#ifdef HELP_EXPAND_TEXT
			    outputMode(); printf(HELP_EXPAND_TEXT);
#else
			    outputMode(); printf("Expand: expand(func).\n");
#endif
                          }                 					                       					       
                      | SIMPLIFYSAFETOKEN
                          {
#ifdef HELP_SIMPLIFYSAFE_TEXT
			    outputMode(); printf(HELP_SIMPLIFYSAFE_TEXT);
#else
			    outputMode(); printf("Safe simplification: simplifysafe(func).\n");
#endif
                          }                 					             						       
                      | TAYLORTOKEN
                          {
#ifdef HELP_TAYLOR_TEXT
			    outputMode(); printf(HELP_TAYLOR_TEXT);
#else
			    outputMode(); printf("Taylor expansion: taylor(func,degree,point).\n");
#endif
                          }                 					                      					       
                      | DEGREETOKEN
                          {
#ifdef HELP_DEGREE_TEXT
			    outputMode(); printf(HELP_DEGREE_TEXT);
#else
			    outputMode(); printf("Degree of a polynomial: degree(func).\n");
#endif
                          }                 					                       					       
                      | NUMERATORTOKEN
                          {
#ifdef HELP_NUMERATOR_TEXT
			    outputMode(); printf(HELP_NUMERATOR_TEXT);
#else
			    outputMode(); printf("Numerator of an expression: numerator(func).\n");
#endif
                          }                 					                    					       
                      | DENOMINATORTOKEN
                          {
#ifdef HELP_DENOMINATOR_TEXT
			    outputMode(); printf(HELP_DENOMINATOR_TEXT);
#else
			    outputMode(); printf("Denominator of an expression: denominator(func).\n");
#endif
                          }                 					                  					       
                      | SUBSTITUTETOKEN
                          {
#ifdef HELP_SUBSTITUTE_TEXT
			    outputMode(); printf(HELP_SUBSTITUTE_TEXT);
#else
			    outputMode(); printf("Substitute func2 for free variable in func: substitute(func,func2).\n");
#endif
                          }                 					                   					       
                      | COEFFTOKEN
                          {
#ifdef HELP_COEFF_TEXT
			    outputMode(); printf(HELP_COEFF_TEXT);
#else
			    outputMode(); printf("i-th coefficient of a polynomial: coeff(func,degree).\n");
#endif
                          }                 					                        					       
                      | SUBPOLYTOKEN
                          {
#ifdef HELP_SUBPOLY_TEXT
			    outputMode(); printf(HELP_SUBPOLY_TEXT);
#else
			    outputMode(); printf("Subpolynomial consisting in monomials: subpoly(func,list of degrees).\n");
#endif
                          }                 					                      					       
                      | ROUNDCOEFFICIENTSTOKEN
                          {
#ifdef HELP_ROUNDCOEFFICIENTS_TEXT
			    outputMode(); printf(HELP_ROUNDCOEFFICIENTS_TEXT);
#else
			    outputMode(); printf("Round coefficients of a polynomial to format: roundcoefficients(func,list of formats).\n");
#endif
                          }                 					              					       
                      | RATIONALAPPROXTOKEN
                          {
#ifdef HELP_RATIONALAPPROX_TEXT
			    outputMode(); printf(HELP_RATIONALAPPROX_TEXT);
#else
			    outputMode(); printf("Rational approximation: rationalapprox(constant).\n");
#endif
                          }                 					               					       
                      | ACCURATEINFNORMTOKEN
                          {
#ifdef HELP_ACCURATEINFNORM_TEXT
			    outputMode(); printf(HELP_ACCURATEINFNORM_TEXT);
#else
			    outputMode(); printf("Faithful rounded infinite norm: accurateinfnorm(func,bits,range,domains to exclude).\n");
#endif
                          }                 					               					       
                      | ROUNDTOFORMATTOKEN
                          {
#ifdef HELP_ROUND_TEXT
			    outputMode(); printf(HELP_ROUND_TEXT);
#else
			    outputMode(); printf("Round to a given format: round(constant,precision,rounding mode).\n");
#endif
                          }                 					                					       
                      | EVALUATETOKEN
                          {
#ifdef HELP_EVALUATE_TEXT
			    outputMode(); printf(HELP_EVALUATE_TEXT);
#else
			    outputMode(); printf("Evaluate a function in a point or interval: round(func,constant|range).\n");
#endif
                          }                 					                     					       
                      | LENGTHTOKEN
                          {
#ifdef HELP_LENGTH_TEXT
			    outputMode(); printf(HELP_LENGTH_TEXT);
#else
			    outputMode(); printf("Length of a list: length(list).\n");
#endif
                          }                 					           
                      | PARSETOKEN
                          {
#ifdef HELP_PARSE_TEXT
			    outputMode(); printf(HELP_PARSE_TEXT);
#else
			    outputMode(); printf("Parse a string to function: parse(string).\n");
#endif
                          }                 					                        					       
                      | PRINTTOKEN
                          {
#ifdef HELP_PRINT_TEXT
			    outputMode(); printf(HELP_PRINT_TEXT);
#else
			    outputMode(); printf("Print something: print(thing1, thing2, ...).\n");
#endif
                          }                 					                        					       
                      | PRINTXMLTOKEN
                          {
#ifdef HELP_PRINTXML_TEXT
			    outputMode(); printf(HELP_PRINTXML_TEXT);
#else
			    outputMode(); printf("Print a function in XML: printxml(func).\n");
#endif
                          }                 					                        					       
                      | READXMLTOKEN
                          {
#ifdef HELP_READXML_TEXT
			    outputMode(); printf(HELP_READXML_TEXT);
#else
			    outputMode(); printf("Reads a function in XML: readxml(filename).\n");
#endif
                          }                 					                        					       
                      | PLOTTOKEN
                          {
#ifdef HELP_PLOT_TEXT
			    outputMode(); printf(HELP_PLOT_TEXT);
#else
			    outputMode(); printf("Plot (a) function(s) in a range: plot(func,func2,...,range).\n");
			    outputMode(); printf("There are further options.\n");
#endif
                          }                 					                         					       
                      | PRINTHEXATOKEN
                          {
#ifdef HELP_PRINTHEXA_TEXT
			    outputMode(); printf(HELP_PRINTHEXA_TEXT);
#else
			    outputMode(); printf("Print a constant in hexadecimal: printhexa(constant).\n");
#endif
                          }                 					       
                      | PRINTFLOATTOKEN
                          {
#ifdef HELP_PRINTFLOAT_TEXT
			    outputMode(); printf(HELP_PRINTFLOAT_TEXT);
#else
			    outputMode(); printf("Print a constant in hexadecimal simple precision: printfloat(constant).\n");
#endif
                          }                 					                    					       
                      | PRINTBINARYTOKEN
                          {
#ifdef HELP_PRINTBINARY_TEXT
			    outputMode(); printf(HELP_PRINTBINARY_TEXT);
#else
			    outputMode(); printf("Print a constant in binary: printbinary(constant).\n");
#endif
                          }                 					                  					       
                      | PRINTEXPANSIONTOKEN
                          {
#ifdef HELP_PRINTEXPANSION_TEXT
			    outputMode(); printf(HELP_PRINTEXPANSION_TEXT);
#else
			    outputMode(); printf("Print a polynomial as an expansion of double precision numbers: printexpansion(func).\n");
#endif
                          }                 					               					       
                      | BASHEXECUTETOKEN
                          {
#ifdef HELP_BASHEXECUTE_TEXT
			    outputMode(); printf(HELP_BASHEXECUTE_TEXT);
#else
			    outputMode(); printf("Execute a command in a shell: bashexecute(string).\n");
#endif
                          }                 					                  					       
                      | EXTERNALPLOTTOKEN
                          {
#ifdef HELP_EXTERNALPLOT_TEXT
			    outputMode(); printf(HELP_EXTERNALPLOT_TEXT);
#else
			    outputMode(); printf("Here should be some help text.\n");
#endif
                          }                 					                 					       
                      | WRITETOKEN
                          {
#ifdef HELP_WRITE_TEXT
			    outputMode(); printf(HELP_WRITE_TEXT);
#else
			    outputMode(); printf("Write something without adding spaces and newlines: write(thing1, thing2, ...).\n");
#endif
                          }                 					                        					       
                      | ASCIIPLOTTOKEN
                          {
#ifdef HELP_ASCIIPLOT_TEXT
			    outputMode(); printf(HELP_ASCIIPLOT_TEXT);
#else
			    outputMode(); printf("Plot a function in a range using an ASCII terminal: asciiplot(func,range).\n");
#endif
                          }                 					               
                      | RENAMETOKEN
                          {
#ifdef HELP_RENAME_TEXT
			    outputMode(); printf(HELP_RENAME_TEXT);
#else
			    outputMode(); printf("Rename free variable string1 to string2: rename(string1, string2).\n");
#endif
                          }                 					       
                      | INFNORMTOKEN
                          {
#ifdef HELP_INFNORM_TEXT
			    outputMode(); printf(HELP_INFNORM_TEXT);
#else
			    outputMode(); printf("Certified infinite norm: infnorm(func,range[,prooffile[,list of funcs]]).\n");
#endif
                          }                 					                      					       
                      | FINDZEROSTOKEN
                          {
#ifdef HELP_FINDZEROS_TEXT
			    outputMode(); printf(HELP_FINDZEROS_TEXT);
#else
			    outputMode(); printf("Certified bounding of zeros: findzeros(func,range).\n");
#endif
                          }                 					                    					       
                      | FPFINDZEROSTOKEN
                          {
#ifdef HELP_FPFINDZEROS_TEXT
			    outputMode(); printf(HELP_FPFINDZEROS_TEXT);
#else
			    outputMode(); printf("Approximate zeros of a function: fpfindzeros(func,range).\n");
#endif
                          }                 					                  					       
                      | DIRTYINFNORMTOKEN
                          {
#ifdef HELP_DIRTYINFNORM_TEXT
			    outputMode(); printf(HELP_DIRTYINFNORM_TEXT);
#else
			    outputMode(); printf("Floating-point infinite norm: dirtyinfnorm(func,range).\n");
#endif
                          }                 					                 					       
                      | INTEGRALTOKEN
                          {
#ifdef HELP_INTEGRAL_TEXT
			    outputMode(); printf(HELP_INTEGRAL_TEXT);
#else
			    outputMode(); printf("Certified integral: integral(func,range).\n");
#endif
                          }                 					                     					       
                      | DIRTYINTEGRALTOKEN
                          {
#ifdef HELP_DIRTYINTEGRAL_TEXT
			    outputMode(); printf(HELP_DIRTYINTEGRAL_TEXT);
#else
			    outputMode(); printf("Floating-point integral: dirtyintegral(func,range).\n");
#endif
                          }                 					             						       
                      | WORSTCASETOKEN
                          {
#ifdef HELP_WORSTCASE_TEXT
			    outputMode(); printf(HELP_WORSTCASE_TEXT);
#else
			    outputMode(); printf("Print all worst-cases under a certain bound: worstcase(func,constant,range,constant,constant[,file]).\n");
#endif
                          }                 					                    					       
                      | IMPLEMENTPOLYTOKEN
                          {
#ifdef HELP_IMPLEMENTPOLY_TEXT
			    outputMode(); printf(HELP_IMPLEMENTPOLY_TEXT);
#else
			    outputMode(); printf("Implement a polynomial in C: implementpoly(func,range,constant,format,string,string2[,honorcoeffprec[,string3]]).\n");
			    outputMode(); printf("Implements func in range with error constant with entering format named in function\nstring writing to file string2 honoring the precision of the coefficients or not with a proof in file string3.\n");
#endif
                          }                 					             						       
                      | CHECKINFNORMTOKEN
                          {
#ifdef HELP_CHECKINFNORM_TEXT
			    outputMode(); printf(HELP_CHECKINFNORM_TEXT);
#else
			    outputMode(); printf("Checks whether an infinite norm is bounded: checkinfnorm(func,range,constant).\n");
#endif
                          }                 					                 					       
                      | ZERODENOMINATORSTOKEN
                          {
#ifdef HELP_ZERODENOMINATORS_TEXT
			    outputMode(); printf(HELP_ZERODENOMINATORS_TEXT);
#else
			    outputMode(); printf("Searches floating-point approximations to zeros of denominators: zerodenominators(func,range).\n");
#endif
                          }                 					             					       
                      | ISEVALUABLETOKEN
                          {
#ifdef HELP_ISEVALUABLE_TEXT
			    outputMode(); printf(HELP_ISEVALUABLE_TEXT);
#else
			    outputMode(); printf("Tests if func is evaluable on range: isevaluable(func,range).\n");
#endif
                          }                 					                  					       
                      | SEARCHGALTOKEN
                          {
#ifdef HELP_SEARCHGAL_TEXT
			    outputMode(); printf(HELP_SEARCHGAL_TEXT);
#else
			    outputMode(); printf("Searches Gal values for func (or list of func): searchgal(func|list of func, constant, integer, integer, format|list of formats, constant|list of constants).\n");
#endif
                          }                 					                    					       
                      | GUESSDEGREETOKEN
                          {
#ifdef HELP_GUESSDEGREE_TEXT
			    outputMode(); printf(HELP_GUESSDEGREE_TEXT);
#else
			    outputMode(); printf("Guesses the degree needed for approximating func: guessdegree(func,range,constant[,weight]).\n");
#endif
                          }                 					                  					       
                      | DIRTYFINDZEROSTOKEN
                          {
#ifdef HELP_DIRTYFINDZEROS_TEXT
			    outputMode(); printf(HELP_DIRTYFINDZEROS_TEXT);
#else
			    outputMode(); printf("Finds zeros of a function dirtily: dirtyfindzeros(func,range).\n");
#endif
                          }                 					               					       
                      | IFTOKEN
                          {
			    outputMode(); printf("If construct: if condition then command or if condition then command else command.\n");
                          }                 					             							       
                      | THENTOKEN
                          {
			    outputMode(); printf("If construct: if condition then command or if condition then command else command.\n");
                          }                 					             							       
                      | ELSETOKEN
                          {
			    outputMode(); printf("If construct: if condition then command else command\n");
                          }                 					             							       
                      | FORTOKEN
                          {
			    outputMode(); printf("For construct: for i from const to const2 [by const3] do command\nor for i in list do command.\n");
                          }                 					             							       
                      | INTOKEN
                          {
			    outputMode(); printf("For construct: for i in list do command.\n");
                          }                 					             							       
                      | FROMTOKEN
                          {
			    outputMode(); printf("For construct: for i from const to const2 [by const3] do command.\n");
                          }                 					             							       
                      | TOTOKEN
                          {
			    outputMode(); printf("For construct: for i from const to const2 [by const3] do command.\n");
                          }                 					             							       
                      | BYTOKEN
                          {
			    outputMode(); printf("For construct: for i from const to const2 by const3 do command.\n");
                          }                 					             							       
                      | DOTOKEN
                          {
			    outputMode(); printf("For construct: for i from const to const2 [by const3] do command.\n");
			    outputMode(); printf("While construct: while condition do command.\n");
                          }                 					             							       
                      | BEGINTOKEN
                          {
			    outputMode(); printf("Begin-end construct: begin command; command; ... end.\n");
                          }                 					             							       
                      | ENDTOKEN
                          {
			    outputMode(); printf("Begin-end construct: begin command; command; ... end.\n");
                          }                 					             							       
                      | WHILETOKEN
                          {
			    outputMode(); printf("While construct: while condition do command.\n");
                          }                 					       
                      | INFTOKEN
                          {
#ifdef HELP_INF_TEXT
			    outputMode(); printf(HELP_INF_TEXT);
#else
			    outputMode(); printf("Dereferencing the infimum of a range: inf(range).\n");
#endif
                          }                 					       
                      | MIDTOKEN
                          {
#ifdef HELP_MID_TEXT
			    outputMode(); printf(HELP_MID_TEXT);
#else
			    outputMode(); printf("Dereferencing the midpoint of a range: mid(range).\n");
#endif
                          }                 					       
                      | SUPTOKEN
                          {
#ifdef HELP_SUP_TEXT
			    outputMode(); printf(HELP_SUP_TEXT);
#else
			    outputMode(); printf("Dereferencing the supremum of a range: sup(range).\n");
#endif
                          }                 					       
                      | EXPONENTTOKEN
                          {
#ifdef HELP_EXPONENT_TEXT
			    outputMode(); printf(HELP_EXPONENT_TEXT);
#else
			    outputMode(); printf("exponent(constant): returns an integer such that constant scaled by the power of 2\nof this integer is an odd or zero integer.\n");
#endif
                          }                 					       
                      | MANTISSATOKEN
                          {
#ifdef HELP_MANTISSA_TEXT
			    outputMode(); printf(HELP_MANTISSA_TEXT);
#else
			    outputMode(); printf("mantissa(constant): returns an odd or zero integer equal to constant scaled by an integer power of 2.\n");
#endif
                          }                 					       
                      | PRECISIONTOKEN
                          {
#ifdef HELP_PRECISION_TEXT
			    outputMode(); printf(HELP_PRECISION_TEXT);
#else
			    outputMode(); printf("precision(constant): returns the least number of bits constant can be written on.\n");
#endif
                          }                 					       
                      | EXECUTETOKEN
                          {
#ifdef HELP_EXECUTE_TEXT
			    outputMode(); printf(HELP_EXECUTE_TEXT);
#else
			    outputMode(); printf("execute(string): executes an %s script contained in a file named string.\n",PACKAGE_NAME);
#endif
                          }                 					       
                      | ISBOUNDTOKEN
                          {
#ifdef HELP_ISBOUND_TEXT
			    outputMode(); printf(HELP_ISBOUND_TEXT);
#else
			    outputMode(); printf("isbound(identifier): returns a boolean indicating if identifier is bound.\n");
#endif
                          }                 					       
                      | VERSIONTOKEN 
                          {
			    outputMode(); printf("Prints the version of the software.\n");
                          }                 					       
                      | EXTERNALPROCTOKEN                          {
#ifdef HELP_EXTERNALPROC_TEXT
			    outputMode(); printf(HELP_EXTERNALPROC_TEXT);
#else
			    outputMode(); printf("externalplot(identifier, file, argumentypes -> resulttype): binds identifier to an external procedure with signature argumenttypes -> resulttype in file.\n");
#endif
                          }                 					           
                      | VOIDTOKEN                          {
#ifdef HELP_VOID_TEXT
			    outputMode(); printf(HELP_VOID_TEXT);
#else
			    outputMode(); printf("Represents the void type for externalproc.\n");
#endif
                          }                 					       
                      | CONSTANTTYPETOKEN                          {
#ifdef HELP_CONSTANT_TEXT
			    outputMode(); printf(HELP_CONSTANT_TEXT);
#else
			    outputMode(); printf("Represents the constant type for externalproc.\n");
#endif
                          }                 					       
                      | FUNCTIONTOKEN                          {
#ifdef HELP_FUNCTION_TEXT
			    outputMode(); printf(HELP_FUNCTION_TEXT);
#else
			    outputMode(); printf("Represents the function type for externalproc.\n");
#endif
                          }                 					       
                      | RANGETOKEN                          {
#ifdef HELP_RANGE_TEXT
			    outputMode(); printf(HELP_RANGE_TEXT);
#else
			    outputMode(); printf("Represents the range type for externalproc.\n");
#endif
                          }                 					       
                      | INTEGERTOKEN                          {
#ifdef HELP_INTEGER_TEXT
			    outputMode(); printf(HELP_INTEGER_TEXT);
#else
			    outputMode(); printf("Represents the integer type for externalproc.\n");
#endif
                          }                 					       
                      | STRINGTYPETOKEN                          {
#ifdef HELP_STRING_TEXT
			    outputMode(); printf(HELP_STRING_TEXT);
#else
			    outputMode(); printf("Represents the string type for externalproc.\n");
#endif
                          }                 					       
                      | BOOLEANTOKEN                          {
#ifdef HELP_BOOLEAN_TEXT
			    outputMode(); printf(HELP_BOOLEAN_TEXT);
#else
			    outputMode(); printf("Represents the boolean type for externalproc.\n");
#endif
                          }                 					       
                      | LISTTOKEN                          {
#ifdef HELP_LISTOF_TEXT
			    outputMode(); printf(HELP_LISTOF_TEXT);
#else
			    outputMode(); printf("Represents the list type for externalproc.\n");
#endif
                          }                 					       
                      | OFTOKEN                          {
#ifdef HELP_LISTOF_TEXT
			    outputMode(); printf(HELP_LISTOF_TEXT);
#else
			    outputMode(); printf("Used in list of type for externalproc.\n");
#endif
                          }                 					       
                      | VARTOKEN                          {
#ifdef HELP_VAR_TEXT
			    outputMode(); printf(HELP_VAR_TEXT);
#else
			    outputMode(); printf("Declares a local variable.\n");
#endif
                          }                 					       
                      | NOPTOKEN                          {
#ifdef HELP_NOP_TEXT
			    outputMode(); printf(HELP_NOP_TEXT);
#else
			    outputMode(); printf("Does nothing.\n");
#endif
                          }                 		
                      | PROCTOKEN                          {
#ifdef HELP_PROC_TEXT
			    outputMode(); printf(HELP_PROC_TEXT);
#else
			    outputMode(); printf("Defines a nameless procedure.\n");
#endif
                          }                 					       			       
                      | PROCEDURETOKEN                     {
#ifdef HELP_PROCEDURE_TEXT
			    outputMode(); printf(HELP_PROCEDURE_TEXT);
#else
			    outputMode(); printf("Defines a named procedure.\n");
#endif
                          }                 	
                      | RETURNTOKEN                     {
#ifdef HELP_RETURN_TEXT
			    outputMode(); printf(HELP_RETURN_TEXT);
#else
			    outputMode(); printf("Returns an expression in a procedure.\n");
#endif
                          }                 					       			       
                      | HELPTOKEN
                          {
			    outputMode(); printf("Type \"help <keyword>;\" for help on the keyword <keyword>.\nFor example type \"help implementpoly;\" for help on the command \"implementpoly\".\n\n");
			    printf("Possible keywords in %s are:\n",PACKAGE_NAME);
			    printf("- ^\n");
			    printf("- <\n");
			    printf("- <=\n");
			    printf("- =\n");
			    printf("- ==\n");
			    printf("- >\n");
			    printf("- >=\n");
			    printf("- >_\n");
			    printf("- >.\n");
			    printf("- >*\n");
			    printf("- |\n");
			    printf("- ||\n");
			    printf("- -\n");
			    printf("- ,\n");
			    printf("- ;\n");
			    printf("- :=\n");
			    printf("- ::\n");
			    printf("- :.\n");
			    printf("- .:\n");
			    printf("- !\n");
			    printf("- ?\n");
			    printf("- /\n");
			    printf("- ...\n");
			    printf("- (\n");
			    printf("- )\n");
			    printf("- [\n");
			    printf("- [|\n");
			    printf("- ]\n");
			    printf("- |]\n");
			    printf("- @\n");
			    printf("- *\n");
			    printf("- *<\n");
			    printf("- &&\n");
			    printf("- +\n");
			    printf("- abs\n");
			    printf("- absolute\n");
			    printf("- accurateinfnorm\n");
			    printf("- acos\n");
			    printf("- acosh\n");
			    printf("- asciiplot\n");
			    printf("- asin\n");
			    printf("- asinh\n");
			    printf("- atan\n");
			    printf("- atanh\n");
			    printf("- autosimplify\n");
			    printf("- bashexecute\n");
			    printf("- begin\n");
			    printf("- binary\n");
			    printf("- boolean\n");
			    printf("- by\n");
			    printf("- canonical\n");
			    printf("- ceil\n");
			    printf("- checkinfnorm\n");
			    printf("- coeff\n");
			    printf("- constant\n");
			    printf("- cos\n");
			    printf("- cosh\n");
			    printf("- D\n");
			    printf("- DD\n");
			    printf("- DE\n");
			    printf("- decimal\n");
			    printf("- default\n");
			    printf("- degree\n");
			    printf("- denominator\n");
			    printf("- diam\n");
			    printf("- diff\n");
			    printf("- dirtyinfnorm\n");
			    printf("- dirtyfindzeros\n");
			    printf("- dirtyintegral\n");
			    printf("- display\n");
			    printf("- do\n");
			    printf("- double\n");
			    printf("- doubledouble\n");
			    printf("- doubleextended\n");
			    printf("- dyadic\n");
			    printf("- else\n");
			    printf("- end\n");
			    printf("- erf\n");
			    printf("- erfc\n");
			    printf("- error\n");
			    printf("- evaluate\n");
			    printf("- execute\n");
			    printf("- exp\n");
			    printf("- expand\n");
			    printf("- expm1\n");
			    printf("- exponent\n");
			    printf("- externalplot\n");
			    printf("- externalproc\n");
			    printf("- false\n");
			    printf("- file\n");
			    printf("- findzeros\n");
			    printf("- fixed\n");
			    printf("- floating\n");
			    printf("- floor\n");
			    printf("- for\n");
			    printf("- fpfindzeros\n");
			    printf("- fpminimax\n");
			    printf("- from\n");
			    printf("- fullparentheses\n");
			    printf("- function\n");
			    printf("- guessdegree\n");
			    printf("- head\n");
			    printf("- help\n");
			    printf("- honorcoeffprec\n");
			    printf("- hopitalrecursions\n");
			    printf("- horner\n");
			    printf("- if\n");
			    printf("- implementpoly\n");
			    printf("- in\n");
			    printf("- inf\n");
			    printf("- infnorm\n");
			    printf("- integer\n");
			    printf("- integral\n");
			    printf("- isbound\n");
			    printf("- isevaluable\n");
			    printf("- length\n");
			    printf("- library\n");
			    printf("- list\n");
			    printf("- log\n");
			    printf("- log10\n");
			    printf("- log1p\n");
			    printf("- log2\n");
			    printf("- mantissa\n");
			    printf("- mid\n");
			    printf("- midpointmode\n");
			    printf("- nop\n");
			    printf("- numerator\n");
			    printf("- of\n");
			    printf("- off\n");
			    printf("- on\n");
			    printf("- parse\n");
			    printf("- perturb\n");
			    printf("- pi\n");
			    printf("- plot\n");
			    printf("- points\n");
			    printf("- postscript\n");
			    printf("- postscriptfile\n");
			    printf("- powers\n");
			    printf("- prec\n");
			    printf("- precision\n");
			    printf("- print\n");
			    printf("- printbinary\n");
			    printf("- printexpansion\n");
			    printf("- printfloat\n");
			    printf("- printhexa\n");
			    printf("- printxml\n");
			    printf("- proc\n");
			    printf("- procedure\n");
			    printf("- quit\n");
			    printf("- RD\n");
			    printf("- RN\n");
			    printf("- RU\n");
			    printf("- RZ\n");
			    printf("- range\n");
			    printf("- rationalapprox\n");
			    printf("- read\n");
			    printf("- readfile\n");
			    printf("- readxml\n");
			    printf("- relative\n");
			    printf("- remez\n");
			    printf("- rename\n");
			    printf("- restart\n");
			    printf("- revert\n");
			    printf("- round\n");
			    printf("- roundcoefficients\n");
			    printf("- roundcorrectly\n");
			    printf("- roundingwarnings\n");
			    printf("- searchgal\n");
			    printf("- simplify\n");
			    printf("- simplifysafe\n");
			    printf("- sin\n");
			    printf("- sinh\n");
			    printf("- sort\n");
			    printf("- sqrt\n");
			    printf("- string\n");
			    printf("- subpoly\n");
			    printf("- substitute\n");
			    printf("- sup\n");
			    printf("- tail\n");
			    printf("- tan\n");
			    printf("- tanh\n");
			    printf("- taylor\n");
			    printf("- taylorrecursions\n");
			    printf("- TD\n");
			    printf("- then\n");
			    printf("- timing\n");
			    printf("- to\n");
			    printf("- tripledouble\n");
			    printf("- true\n");
			    printf("- var\n");
			    printf("- verbosity\n");
			    printf("- version\n");
			    printf("- void\n");
			    printf("- while\n");
			    printf("- worstcase\n");
			    printf("- write\n");
			    printf("- zerodenominators\n");
			    printf("\n");
                          }                                                           
;


