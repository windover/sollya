%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pari/pari.h>
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
%token  ERRORTOKEN;			
								       
%token  QUITTOKEN;              					       
%token  FALSEQUITTOKEN;  						       
%token  RESTARTTOKEN;           					       
											       
%token  LIBRARYTOKEN;           					       
											       
%token  DIFFTOKEN;              					       
%token  SIMPLIFYTOKEN;  						       
%token  REMEZTOKEN;             					       
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
                            printf("This is %s.\nType 'help help;' for the list of available commands. Type 'help <command>;' for help on the specific command <command>.\nType 'quit;' for quitting the %s interpreter.\n\nYou can get moral support and help with bugs by writing to %s.\n\n",PACKAGE_NAME,PACKAGE_NAME,PACKAGE_BUGREPORT);
			    parsedThing = NULL;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | QUESTIONMARKTOKEN
                          {
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
			    printf("This is %s.\nSend bug reports to %s.\n",PACKAGE_STRING,PACKAGE_BUGREPORT);
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
		      |	term MULTOKEN subterm				
			  {
			    $$ = makeMul($1, $3);
                          }														
		      |	term DIVTOKEN subterm				
                          {
			    $$ = makeDiv($1, $3);
                          }					
;

subterm:                basicthing
                          {
			    $$ = $1;
                          }
                      | subterm POWTOKEN basicthing
                          {
			    $$ = makePow($1, $3);
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

statedereference:       PRECTOKEN EQUALTOKEN QUESTIONMARKTOKEN
                          {
			    $$ = makePrecDeref();
			  }
                      | POINTSTOKEN EQUALTOKEN QUESTIONMARKTOKEN            					       
                          {
			    $$ = makePointsDeref();
			  }
                      | DIAMTOKEN EQUALTOKEN QUESTIONMARKTOKEN              					       
                          {
			    $$ = makeDiamDeref();
			  }
                      | DISPLAYTOKEN EQUALTOKEN QUESTIONMARKTOKEN            					       
                          {
			    $$ = makeDisplayDeref();
			  }
                      | VERBOSITYTOKEN EQUALTOKEN QUESTIONMARKTOKEN         					       
                          {
			    $$ = makeVerbosityDeref();
			  }
                      | CANONICALTOKEN EQUALTOKEN QUESTIONMARKTOKEN         					       
                          {
			    $$ = makeCanonicalDeref();
			  }
                      | AUTOSIMPLIFYTOKEN EQUALTOKEN QUESTIONMARKTOKEN				       
                          {
			    $$ = makeAutoSimplifyDeref();
			  }
                      | TAYLORRECURSIONSTOKEN EQUALTOKEN QUESTIONMARKTOKEN				       
                          {
			    $$ = makeTaylorRecursDeref();
			  }
                      | TIMINGTOKEN EQUALTOKEN QUESTIONMARKTOKEN			       
                          {
			    $$ = makeTimingDeref();
			  }
                      | FULLPARENTHESESTOKEN EQUALTOKEN QUESTIONMARKTOKEN					       
                          {
			    $$ = makeFullParenDeref();
			  }
                      | MIDPOINTMODETOKEN EQUALTOKEN QUESTIONMARKTOKEN			       
                          {
			    $$ = makeMidpointDeref();
			  }
                      | HOPITALRECURSIONSTOKEN EQUALTOKEN QUESTIONMARKTOKEN				       
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
			    printf("\"%s\" is recognized as a base 10 constant.\n",$1);
			    free($1);
			  }          					       
                      | DYADICCONSTANTTOKEN
                          {
			    printf("\"%s\" is recognized as a dyadic number constant.\n",$1);
			    free($1);
                          }   					       
                      | HEXCONSTANTTOKEN
                          {
			    printf("\"%s\" is recognized as a double or single precision constant.\n",$1);
			    free($1);
                          }       					       
                      | HEXADECIMALCONSTANTTOKEN
                          {
			    printf("\"%s\" is recognized as a hexadecimal constant.\n",$1);
			    free($1);
                          }       					       
                      | BINARYCONSTANTTOKEN
                          {
			    printf("\"%s_2\" is recognized as a base 2 constant.\n",$1);
			    free($1);
                          }    					       
                      | PITOKEN
                          {
#ifdef HELP_PI_TEXT
			    printf(HELP_PI_TEXT);
#else
			    printf("Ratio circonference and diameter of a circle.\n");
#endif
                          }                					       
                      | IDENTIFIERTOKEN
                          {
			    printf("\"%s\" is an identifier.\n",$1);
			    free($1);
                          }          					       
                      | STRINGTOKEN
                          {
			    printf("\"%s\" is a string constant.\n",$1);
			    free($1);
                          }            					       
                      | LPARTOKEN
                          {
			    printf("Left parenthesis.\n");
                          }                  					       
                      | RPARTOKEN
                          {
			    printf("Right parenthesis.\n");
                          }                  					       
                      | LBRACKETTOKEN
                          {
			    printf("Left bracket - indicates a range or a list.\n");
                          }              					       
                      | RBRACKETTOKEN
                          {
			    printf("Right bracket - indicates a range or a list.\n");
                          }              					       
                      | EQUALTOKEN
                          {
#ifdef HELP_ASSIGNMENT_TEXT
			    printf(HELP_EQUAL_TEXT);
#else
			    printf("Assignment operator.\n");
#endif
                          }                 					       
                      | COMPAREEQUALTOKEN
                          {
#ifdef HELP_EQUAL_TEXT
			    printf(HELP_EQUAL_TEXT);
#else
			    printf("Equality test.\n");
#endif
                          }                 					       
                      | COMMATOKEN
                          {
			    printf("Separator in lists or ranges.\n");
                          }                 					       
                      | EXCLAMATIONTOKEN
                          {
			    printf("Suppresses output on assignments.\n");
                          }      						       
                      | STARLEFTANGLETOKEN
                          {
			    printf("Dereferences range bounds.\n");
                          }             					       
                      | LEFTANGLETOKEN
                          {
#ifdef HELP_LT_TEXT
			    printf(HELP_LT_TEXT);
#else
			    printf("Comparison less than.\n");
#endif
                          }             					       
                      | RIGHTANGLEUNDERSCORETOKEN
                          {
			    printf("Dereferences the lower range bound.\n");
                          }      					       
                      | RIGHTANGLEDOTTOKEN
                          {
			    printf("Dereferences the mid-point of a range.\n");
                          }       					       
                      | RIGHTANGLESTARTOKEN
                          {
			    printf("Dereferences the upper range bound.\n");
                          }             					       
                      | RIGHTANGLETOKEN
                          {
#ifdef HELP_GT_TEXT
			    printf(HELP_GT_TEXT);
#else
			    printf("Comparison greater than.\n");
#endif
                          }            					       
                      | DOTSTOKEN
                          {
			    printf("Ellipsis.\n");
                          }                  					       
                      | QUESTIONMARKTOKEN
                          {
			    printf("Dereferences global environment variables.\n");
                          }      						       
                      | VERTBARTOKEN
                          {
			    printf("Starts or ends a list.\n");
                          }      						       
                      | ATTOKEN
                          {
#ifdef HELP_CONCAT_TEXT
			    printf(HELP_CONCAT_TEXT);
#else
			    printf("Concatenation of lists or strings.\n");
#endif
                          }      							       
                      | DOUBLECOLONTOKEN
                          {
			    printf("a::b prepends a to list b or appends b to list a, preprending list a to list b if both are lists.\n");
                          }    
                      | DOTCOLONTOKEN
                          {
#ifdef HELP_PREPEND_TEXT
			    printf(HELP_PREPEND_TEXT);
#else
			    printf("a.:b prepends a to list b.\n");
#endif
                          }    
                      | COLONDOTTOKEN
                          {
#ifdef HELP_APPEND_TEXT
			    printf(HELP_APPEND_TEXT);
#else
			    printf("a:.b appends b to list a.\n");
#endif
                          }    
                      | EXCLAMATIONEQUALTOKEN
                          {
#ifdef HELP_NEQ_TEXT
			    printf(HELP_NEQ_TEXT);
#else
			    printf("Comparison not equal.\n");
#endif
                          }    
                      | ANDTOKEN
                          {
#ifdef HELP_AND_TEXT
			    printf(HELP_AND_TEXT);
#else
			    printf("Boolean and.\n");
#endif
                          }    
                      | ORTOKEN
                          {
#ifdef HELP_OR_TEXT
			    printf(HELP_OR_TEXT);
#else
			    printf("Boolean or.\n");
#endif
                          }    
                      | PLUSTOKEN
                          {
#ifdef HELP_PLUS_TEXT
			    printf(HELP_PLUS_TEXT);
#else
			    printf("Addition.\n");
#endif
                          }                  					       
                      | MINUSTOKEN
                          {
#ifdef HELP_MINUS_TEXT
			    printf(HELP_MINUS_TEXT);
#else
			    printf("Substraction.\n");
#endif
                          }                 					       
                      | MULTOKEN
                          {
#ifdef HELP_MULT_TEXT
			    printf(HELP_MULT_TEXT);
#else
			    printf("Multiplication.\n");
#endif
                          }                						       
                      | DIVTOKEN
                          {
#ifdef HELP_DIVIDE_TEXT
			    printf(HELP_DIVIDE_TEXT);
#else
			    printf("Division.\n");
#endif
                          }                  					       
                      | POWTOKEN
                          {
#ifdef HELP_POWER_TEXT
			    printf(HELP_POWER_TEXT);
#else
			    printf("Exponentiation.\n");
#endif
                          }                  					       
                      | SQRTTOKEN
                          {
#ifdef HELP_SQRT_TEXT
			    printf(HELP_SQRT_TEXT);
#else
			    printf("Square root.\n");
#endif
                          }                  					       
                      | EXPTOKEN
                          {
#ifdef HELP_EXP_TEXT
			    printf(HELP_EXP_TEXT);
#else
			    printf("Exponential.\n");
#endif
                          }                   					       
                      | LOGTOKEN
                          {
#ifdef HELP_LOG_TEXT
			    printf(HELP_LOG_TEXT);
#else
			    printf("Natural logarithm.\n");
#endif
                          }                   					       
                      | LOG2TOKEN
                          {
#ifdef HELP_LOG2_TEXT
			    printf(HELP_LOG2_TEXT);
#else
			    printf("Logarithm in base 2.\n");
#endif
                          }                  					       
                      | LOG10TOKEN
                          {
#ifdef HELP_LOG10_TEXT
			    printf(HELP_LOG10_TEXT);
#else
			    printf("Logarithm in base 10.\n");
#endif
                          }                 					       
                      | SINTOKEN
                          {
#ifdef HELP_SIN_TEXT
			    printf(HELP_SIN_TEXT);
#else
			    printf("Sine.\n");
#endif
                          }                   					       
                      | COSTOKEN
                          {
#ifdef HELP_COS_TEXT
			    printf(HELP_COS_TEXT);
#else
			    printf("Cosine.\n");
#endif
                          }                   					       
                      | TANTOKEN
                          {
#ifdef HELP_TAN_TEXT
			    printf(HELP_TAN_TEXT);
#else
			    printf("Tangent.\n");
#endif
                          }                   					       
                      | ASINTOKEN
                          {
#ifdef HELP_ASIN_TEXT
			    printf(HELP_ASIN_TEXT);
#else
			    printf("Arcsine.\n");
#endif
                          }                  					       
                      | ACOSTOKEN
                          {
#ifdef HELP_ACOS_TEXT
			    printf(HELP_ACOS_TEXT);
#else
			    printf("Arcosine.\n");
#endif
                          }                  					       
                      | ATANTOKEN
                          {
#ifdef HELP_ATAN_TEXT
			    printf(HELP_ATAN_TEXT);
#else
			    printf("Arctangent.\n");
#endif
                          }                  					       
                      | SINHTOKEN
                          {
#ifdef HELP_SINH_TEXT
			    printf(HELP_SINH_TEXT);
#else
			    printf("Hyperbolic sine.\n");
#endif
                          }                  					       
                      | COSHTOKEN
                          {
#ifdef HELP_COSH_TEXT
			    printf(HELP_COSH_TEXT);
#else
			    printf("Hyperbolic cosine.\n");
#endif
                          }                  					       
                      | TANHTOKEN
                          {
#ifdef HELP_TANH_TEXT
			    printf(HELP_TANH_TEXT);
#else
			    printf("Hyperbolic tangent.\n");
#endif
                          }                  					       
                      | ASINHTOKEN
                          {
#ifdef HELP_ASINH_TEXT
			    printf(HELP_ASINH_TEXT);
#else
			    printf("Area sine.\n");
#endif
                          }                 					       
                      | ACOSHTOKEN
                          {
#ifdef HELP_ACOSH_TEXT
			    printf(HELP_ACOSH_TEXT);
#else
			    printf("Area cosine.\n");
#endif
                          }                 					       
                      | ATANHTOKEN
                          {
#ifdef HELP_ATANH_TEXT
			    printf(HELP_ATANH_TEXT);
#else

			    printf("Area tangent.\n");
#endif
                          }                 					                        					       
                      | ABSTOKEN
                          {
#ifdef HELP_ABS_TEXT
			    printf(HELP_ABS_TEXT);
#else
			    printf("Absolute value.\n");
#endif
                          }                 					                          					       
                      | ERFTOKEN
                          {
#ifdef HELP_ERF_TEXT
			    printf(HELP_ERF_TEXT);
#else
			    printf("Error function.\n");
#endif
                          }                 					                          					       
                      | ERFCTOKEN
                          {
#ifdef HELP_ERFC_TEXT
			    printf(HELP_ERFC_TEXT);
#else
			    printf("Complementary error function.\n");
#endif
                          }                 					                         					       
                      | LOG1PTOKEN
                          {
#ifdef HELP_LOG1P_TEXT
			    printf(HELP_LOG1P_TEXT);
#else
			    printf("Natural logarithm of 1 plus argument.\n");
#endif
                          }                 					                        					       
                      | EXPM1TOKEN
                          {
#ifdef HELP_EXPM1_TEXT
			    printf(HELP_EXPM1_TEXT);
#else
			    printf("Exponential of argument minus 1.\n");
#endif
                          }                 					                        					       
                      | DOUBLETOKEN
                          {
#ifdef HELP_DOUBLE_TEXT
			    printf(HELP_DOUBLE_TEXT);
#else
			    printf("Double precision rounding operator.\n");
#endif
                          }                 					                       					       
                      | DOUBLEDOUBLETOKEN
                          {
#ifdef HELP_DOUBLEDOUBLE_TEXT
			    printf(HELP_DOUBLEDOUBLE_TEXT);
#else
			    printf("Double-double precision rounding operator.\n");
#endif
                          }                 					             						       
                      | TRIPLEDOUBLETOKEN
                          {
#ifdef HELP_TRIPLEDOUBLE_TEXT
			    printf(HELP_TRIPLEDOUBLE_TEXT);
#else
			    printf("Triple-double precision rounding operator.\n");
#endif
                          }                 					                 					       
                      | DOUBLEEXTENDEDTOKEN
                          {
#ifdef HELP_DOUBLEEXTENDED_TEXT
			    printf(HELP_DOUBLEEXTENDED_TEXT);
#else
			    printf("Double-extended precision rounding operator.\n");
#endif
                          }                 					               					       
                      | CEILTOKEN
                          {
#ifdef HELP_CEIL_TEXT
			    printf(HELP_CEIL_TEXT);
#else
			    printf("Ceiling.\n");
#endif
                          }                 					                         					       
                      | FLOORTOKEN
                          {
#ifdef HELP_FLOOR_TEXT
			    printf(HELP_FLOOR_TEXT);
#else
			    printf("Floor.\n");
#endif
                          }                 					                        			
                      | HEADTOKEN
                          {
#ifdef HELP_HEAD_TEXT
			    printf(HELP_HEAD_TEXT);
#else
			    printf("Head of a list.\n");
#endif
                          }                 					       
                      | ROUNDCORRECTLYTOKEN
                          {
#ifdef HELP_ROUNDCORRECTLY_TEXT
			    printf(HELP_ROUNDCORRECTLY_TEXT);
#else
			    printf("Round a bounding to the nearest floating-point value such that correct rounding is possible.\n");
#endif
                          }                 					       
                      | READFILETOKEN
                          {
#ifdef HELP_READFILE_TEXT
			    printf(HELP_READFILE_TEXT);
#else
			    printf("Reads a file into a string.\n");
#endif
                          }                 					           
                      | REVERTTOKEN
                          {
#ifdef HELP_REVERT_TEXT
			    printf(HELP_REVERT_TEXT);
#else
			    printf("Reverts a list that is not finally elliptic.\n");
#endif
                          }                 					       
                      | SORTTOKEN
                          {
#ifdef HELP_SORT_TEXT
			    printf(HELP_SORT_TEXT);
#else
			    printf("Sorts a list of constants in ascending order.\n");
#endif
                          }                 					       
                      | TAILTOKEN
                          {
#ifdef HELP_TAIL_TEXT
			    printf(HELP_TAIL_TEXT);
#else
			    printf("Tail of a list.\n");
#endif
                          }                 					       
                      | PRECTOKEN
                          {
#ifdef HELP_PREC_TEXT
			    printf(HELP_PREC_TEXT);
#else
			    printf("Global environment variable precision.\n");
#endif
                          }                 					       
                      | POINTSTOKEN
                          {
#ifdef HELP_POINTS_TEXT
			    printf(HELP_POINTS_TEXT);
#else
			    printf("Global environment variable number of points.\n");
#endif
                          }                 					                       					       
                      | DIAMTOKEN
                          {
#ifdef HELP_DIAM_TEXT
			    printf(HELP_DIAM_TEXT);
#else
			    printf("Global environment variable diameter.\n");
#endif
                          }                 					                         					       
                      | DISPLAYTOKEN
                          {
#ifdef HELP_DISPLAY_TEXT
			    printf(HELP_DISPLAY_TEXT);
#else
			    printf("Global environment variable display mode.\n");
#endif
                          }                 					                       					       
                      | VERBOSITYTOKEN
                          {
#ifdef HELP_VERBOSITY_TEXT
			    printf(HELP_VERBOSITY_TEXT);
#else
			    printf("Global environment variable verbosity.\n");
#endif
                          }                 					                    					       
                      | CANONICALTOKEN
                          {
#ifdef HELP_CANONICAL_TEXT
			    printf(HELP_CANONICAL_TEXT);
#else
			    printf("Global environment variable canonical output.\n");
#endif
                          }                 					                    					       
                      | AUTOSIMPLIFYTOKEN
                          {
#ifdef HELP_AUTOSIMPLIFY_TEXT
			    printf(HELP_AUTOSIMPLIFY_TEXT);
#else
			    printf("Global environment variable automatic simplification.\n");
#endif
                          }                 					                 					       
                      | TAYLORRECURSIONSTOKEN
                          {
#ifdef HELP_TAYLORRECURSIONS_TEXT
			    printf(HELP_TAYLORRECURSIONS_TEXT);
#else
			    printf("Global environement variable recursions of Taylor evaluation.\n");
#endif
                          }                 					             					       
                      | TIMINGTOKEN
                          {
#ifdef HELP_TIMING_TEXT
			    printf(HELP_TIMING_TEXT);
#else
			    printf("Global environement variable timing of computations.\n");
#endif
                          }                 					                       					       
                      | FULLPARENTHESESTOKEN
                          {
#ifdef HELP_FULLPARENTHESES_TEXT
			    printf(HELP_FULLPARENTHESES_TEXT);
#else
			    printf("Global environement variable fully parenthized mode.\n");
#endif
                          }                 					              					       
                      | MIDPOINTMODETOKEN
                          {
#ifdef HELP_MIDPOINTMODE_TEXT
			    printf(HELP_MIDPOINTMODE_TEXT);
#else
			    printf("Global environement variable midpoint mode.\n");
#endif
                          }                 					                 					       
                      | HOPITALRECURSIONSTOKEN
                          {
#ifdef HELP_HOPITALRECURSIONS_TEXT
			    printf(HELP_HOPITALRECURSIONS_TEXT);
#else
			    printf("Global environement variable recursions of Hopital evaluation.\n");
#endif
                          }                 					             					       
                      | ONTOKEN
                          {
#ifdef HELP_ON_TEXT
			    printf(HELP_ON_TEXT);
#else
			    printf("Something is switched on.\n");
#endif
                          }                 					                           					       
                      | OFFTOKEN
                          {
#ifdef HELP_OFF_TEXT
			    printf(HELP_OFF_TEXT);
#else
			    printf("Something is switched off.\n");
#endif
                          }                 					                          					       
                      | DYADICTOKEN
                          {
#ifdef HELP_DYADIC_TEXT
			    printf(HELP_DYADIC_TEXT);
#else
			    printf("Display mode is dyadic output.\n");
#endif
                          }                 					             						       
                      | POWERSTOKEN
                          {
#ifdef HELP_POWERS_TEXT
			    printf(HELP_POWERS_TEXT);
#else
			    printf("Display mode is dyadic output with powers.\n");
#endif
                          }                 					                       					       
                      | BINARYTOKEN
                          {
#ifdef HELP_BINARY_TEXT
			    printf(HELP_BINARY_TEXT);
#else
			    printf("Display mode is binary.\n");
#endif
                          }                 					                       					       
                      | HEXADECIMALTOKEN
                          {
#ifdef HELP_HEXADECIMAL_TEXT
			    printf(HELP_HEXADECIMAL_TEXT);
#else
			    printf("Display mode is hexadecimal.\n");
#endif
                          }                 					                       					       
                      | FILETOKEN
                          {
#ifdef HELP_FILE_TEXT
			    printf(HELP_FILE_TEXT);
#else
			    printf("A file will be specified.\n");
#endif
                          }                 					                         					       
                      | POSTSCRIPTTOKEN
                          {
#ifdef HELP_POSTSCRIPT_TEXT
			    printf(HELP_POSTSCRIPT_TEXT);
#else
			    printf("A postscript file will be specified.\n");
#endif
                          }                 					                   					       
                      | POSTSCRIPTFILETOKEN
                          {
#ifdef HELP_POSTSCRIPTFILE_TEXT
			    printf(HELP_POSTSCRIPTFILE_TEXT);
#else
			    printf("A postscript file and a file will be specified.\n");
#endif
                          }                 					               					       
                      | PERTURBTOKEN
                          {
#ifdef HELP_PERTURB_TEXT
			    printf(HELP_PERTURB_TEXT);
#else
			    printf("Perturbation is demanded.\n");
#endif
                          }                 					                      					       
                      | MINUSWORDTOKEN
                          {
#ifdef HELP_RD_TEXT
			    printf(HELP_RD_TEXT);
#else
			    printf("Round towards minus infinity.\n");
#endif
                          }                 					                    					       
                      | PLUSWORDTOKEN
                          {
#ifdef HELP_RU_TEXT
			    printf(HELP_RU_TEXT);
#else
			    printf("Round towards plus infinity.\n");
#endif
                          }                 					                     					       
                      | ZEROWORDTOKEN
                          {
#ifdef HELP_RZ_TEXT
			    printf(HELP_RZ_TEXT);
#else
			    printf("Round towards zero.\n");
#endif
                          }                 					                     					       
                      | NEARESTTOKEN
                          {
#ifdef HELP_RN_TEXT
			    printf(HELP_RN_TEXT);
#else
			    printf("Round to nearest.\n");
#endif
                          }                 					                      					       
                      | HONORCOEFFPRECTOKEN
                          {
#ifdef HELP_HONORCOEFFPREC_TEXT
			    printf(HELP_HONORCOEFFPREC_TEXT);
#else
			    printf("Honorate the precision of the coefficients.\n");
#endif
                          }                 					              					       
                      | TRUETOKEN
                          {
#ifdef HELP_TRUE_TEXT
			    printf(HELP_TRUE_TEXT);
#else
			    printf("Boolean constant true.\n");
#endif
                          }                 					             							       
                      | FALSETOKEN
                          {
#ifdef HELP_FALSE_TEXT
			    printf(HELP_FALSE_TEXT);
#else
			    printf("Boolean constant false.\n");
#endif
                          }                 					             							       
                      | DEFAULTTOKEN
                          {
#ifdef HELP_DEFAULT_TEXT
			    printf(HELP_DEFAULT_TEXT);
#else
			    printf("Default value.\n");
#endif
                          }                        											       
                      | ABSOLUTETOKEN
                          {
#ifdef HELP_ABSOLUTE_TEXT
			    printf(HELP_ABSOLUTE_TEXT);
#else
			    printf("Consider an absolute error.\n");
#endif
                          }                 					       
                      | DECIMALTOKEN
                          {
#ifdef HELP_DECIMAL_TEXT
			    printf(HELP_DECIMAL_TEXT);
#else
			    printf("Display mode is decimal.\n");
#endif
                          }                 					       
                      | RELATIVETOKEN
                          {
#ifdef HELP_RELATIVE_TEXT
			    printf(HELP_RELATIVE_TEXT);
#else
			    printf("Consider a relative error.\n");
#endif
                          }                 					       
                      | ERRORTOKEN
                          {
#ifdef HELP_ERROR_TEXT
			    printf(HELP_ERROR_TEXT);
#else
			    printf("Type error meta-value.\n");
#endif
                          }                 					       
                      | QUITTOKEN
                          {
#ifdef HELP_QUIT_TEXT
			    printf(HELP_QUIT_TEXT);
#else
			    printf("Exit from the tool.\n");
#endif
                          }                 					                         					       
                      | FALSEQUITTOKEN
                          {
#ifdef HELP_QUIT_TEXT
			    printf(HELP_QUIT_TEXT);
#else
			    printf("Exit from the tool - help is called inside a read macro.\n");
#endif
                          }                 					             						       
                      | RESTARTTOKEN
                          {
#ifdef HELP_RESTART_TEXT
			    printf(HELP_RESTART_TEXT);
#else
			    printf("Restart the tool.\n");
#endif
                          }                 					                      					       
                      | LIBRARYTOKEN
                          {
#ifdef HELP_LIBRARY_TEXT
			    printf(HELP_LIBRARY_TEXT);
#else
			    printf("Library binding dereferencer.\n");
#endif
                          }                 					                      					       
                      | DIFFTOKEN
                          {
#ifdef HELP_DIFF_TEXT
			    printf(HELP_DIFF_TEXT);
#else
			    printf("Differentiation: diff(func).\n");
#endif
                          }                 					                         					       
                      | SIMPLIFYTOKEN
                          {
#ifdef HELP_SIMPLIFY_TEXT
			    printf(HELP_SIMPLIFY_TEXT);
#else
			    printf("Simplify: simplify(func).\n");
#endif
                          }                 					             						       
                      | REMEZTOKEN
                          {
#ifdef HELP_REMEZ_TEXT
			    printf(HELP_REMEZ_TEXT);
#else
			    printf("Remez: remez(func,degree|monoms,range[,weight[,quality]]).\n");
#endif
                          }                 					                        					       
                      | HORNERTOKEN
                          {
#ifdef HELP_HORNER_TEXT
			    printf(HELP_HORNER_TEXT);
#else
			    printf("Horner: horner(func)\n");
#endif
                          }                 					                       					       
                      | EXPANDTOKEN
                          {
#ifdef HELP_EXPAND_TEXT
			    printf(HELP_EXPAND_TEXT);
#else
			    printf("Expand: expand(func).\n");
#endif
                          }                 					                       					       
                      | SIMPLIFYSAFETOKEN
                          {
#ifdef HELP_SIMPLIFYSAFE_TEXT
			    printf(HELP_SIMPLIFYSAFE_TEXT);
#else
			    printf("Safe simplification: simplifysafe(func).\n");
#endif
                          }                 					             						       
                      | TAYLORTOKEN
                          {
#ifdef HELP_TAYLOR_TEXT
			    printf(HELP_TAYLOR_TEXT);
#else
			    printf("Taylor expansion: taylor(func,degree,point).\n");
#endif
                          }                 					                      					       
                      | DEGREETOKEN
                          {
#ifdef HELP_DEGREE_TEXT
			    printf(HELP_DEGREE_TEXT);
#else
			    printf("Degree of a polynomial: degree(func).\n");
#endif
                          }                 					                       					       
                      | NUMERATORTOKEN
                          {
#ifdef HELP_NUMERATOR_TEXT
			    printf(HELP_NUMERATOR_TEXT);
#else
			    printf("Numerator of an expression: numerator(func).\n");
#endif
                          }                 					                    					       
                      | DENOMINATORTOKEN
                          {
#ifdef HELP_DENOMINATOR_TEXT
			    printf(HELP_DENOMINATOR_TEXT);
#else
			    printf("Denominator of an expression: denominator(func).\n");
#endif
                          }                 					                  					       
                      | SUBSTITUTETOKEN
                          {
#ifdef HELP_SUBSTITUTE_TEXT
			    printf(HELP_SUBSTITUTE_TEXT);
#else
			    printf("Substitute func2 for free variable in func: substitute(func,func2).\n");
#endif
                          }                 					                   					       
                      | COEFFTOKEN
                          {
#ifdef HELP_COEFF_TEXT
			    printf(HELP_COEFF_TEXT);
#else
			    printf("i-th coefficient of a polynomial: coeff(func,degree).\n");
#endif
                          }                 					                        					       
                      | SUBPOLYTOKEN
                          {
#ifdef HELP_SUBPOLY_TEXT
			    printf(HELP_SUBPOLY_TEXT);
#else
			    printf("Subpolynomial consisting in monomials: subpoly(func,list of degrees).\n");
#endif
                          }                 					                      					       
                      | ROUNDCOEFFICIENTSTOKEN
                          {
#ifdef HELP_ROUNDCOEFFICIENTS_TEXT
			    printf(HELP_ROUNDCOEFFICIENTS_TEXT);
#else
			    printf("Round coefficients of a polynomial to format: roundcoefficients(func,list of formats).\n");
#endif
                          }                 					              					       
                      | RATIONALAPPROXTOKEN
                          {
#ifdef HELP_RATIONALAPPROX_TEXT
			    printf(HELP_RATIONALAPPROX_TEXT);
#else
			    printf("Rational approximation: rationalapprox(constant).\n");
#endif
                          }                 					               					       
                      | ACCURATEINFNORMTOKEN
                          {
#ifdef HELP_ACCURATEINFNORM_TEXT
			    printf(HELP_ACCURATEINFNORM_TEXT);
#else
			    printf("Faithful rounded infinite norm: accurateinfnorm(func,bits,range,domains to exclude).\n");
#endif
                          }                 					               					       
                      | ROUNDTOFORMATTOKEN
                          {
#ifdef HELP_ROUND_TEXT
			    printf(HELP_ROUND_TEXT);
#else
			    printf("Round to a given format: round(constant,precision,rounding mode).\n");
#endif
                          }                 					                					       
                      | EVALUATETOKEN
                          {
#ifdef HELP_EVALUATE_TEXT
			    printf(HELP_EVALUATE_TEXT);
#else
			    printf("Evaluate a function in a point or interval: round(func,constant|range).\n");
#endif
                          }                 					                     					       
                      | LENGTHTOKEN
                          {
#ifdef HELP_LENGTH_TEXT
			    printf(HELP_LENGTH_TEXT);
#else
			    printf("Length of a list: length(list).\n");
#endif
                          }                 					           
                      | PARSETOKEN
                          {
#ifdef HELP_PARSE_TEXT
			    printf(HELP_PARSE_TEXT);
#else
			    printf("Parse a string to function: parse(string).\n");
#endif
                          }                 					                        					       
                      | PRINTTOKEN
                          {
#ifdef HELP_PRINT_TEXT
			    printf(HELP_PRINT_TEXT);
#else
			    printf("Print something: print(thing1, thing2, ...).\n");
#endif
                          }                 					                        					       
                      | PRINTXMLTOKEN
                          {
#ifdef HELP_PRINTXML_TEXT
			    printf(HELP_PRINTXML_TEXT);
#else
			    printf("Print a function in XML: printxml(func).\n");
#endif
                          }                 					                        					       
                      | READXMLTOKEN
                          {
#ifdef HELP_READXML_TEXT
			    printf(HELP_READXML_TEXT);
#else
			    printf("Reads a function in XML: readxml(filename).\n");
#endif
                          }                 					                        					       
                      | PLOTTOKEN
                          {
#ifdef HELP_PLOT_TEXT
			    printf(HELP_PLOT_TEXT);
#else
			    printf("Plot (a) function(s) in a range: plot(func,func2,...,range).\n");
			    printf("There are further options.\n");
#endif
                          }                 					                         					       
                      | PRINTHEXATOKEN
                          {
#ifdef HELP_PRINTHEXA_TEXT
			    printf(HELP_PRINTHEXA_TEXT);
#else
			    printf("Print a constant in hexadecimal: printhexa(constant).\n");
#endif
                          }                 					       
                      | PRINTFLOATTOKEN
                          {
#ifdef HELP_PRINTFLOAT_TEXT
			    printf(HELP_PRINTFLOAT_TEXT);
#else
			    printf("Print a constant in hexadecimal simple precision: printfloat(constant).\n");
#endif
                          }                 					                    					       
                      | PRINTBINARYTOKEN
                          {
#ifdef HELP_PRINTBINARY_TEXT
			    printf(HELP_PRINTBINARY_TEXT);
#else
			    printf("Print a constant in binary: printbinary(constant).\n");
#endif
                          }                 					                  					       
                      | PRINTEXPANSIONTOKEN
                          {
#ifdef HELP_PRINTEXPANSION_TEXT
			    printf(HELP_PRINTEXPANSION_TEXT);
#else
			    printf("Print a polynomial as an expansion of double precision numbers: printexpansion(func).\n");
#endif
                          }                 					               					       
                      | BASHEXECUTETOKEN
                          {
#ifdef HELP_BASHEXECUTE_TEXT
			    printf(HELP_BASHEXECUTE_TEXT);
#else
			    printf("Execute a command in a shell: bashexecute(string).\n");
#endif
                          }                 					                  					       
                      | EXTERNALPLOTTOKEN
                          {
#ifdef HELP_EXTERNALPLOT_TEXT
			    printf(HELP_EXTERNALPLOT_TEXT);
#else
			    printf("Here should be some help text.\n");
#endif
                          }                 					                 					       
                      | WRITETOKEN
                          {
#ifdef HELP_WRITE_TEXT
			    printf(HELP_WRITE_TEXT);
#else
			    printf("Write something without adding spaces and newlines: write(thing1, thing2, ...).\n");
#endif
                          }                 					                        					       
                      | ASCIIPLOTTOKEN
                          {
#ifdef HELP_ASCIIPLOT_TEXT
			    printf(HELP_ASCIIPLOT_TEXT);
#else
			    printf("Plot a function in a range using an ASCII terminal: asciiplot(func,range).\n");
#endif
                          }                 					               
                      | RENAMETOKEN
                          {
#ifdef HELP_RENAME_TEXT
			    printf(HELP_RENAME_TEXT);
#else
			    printf("Rename free variable string1 to string2: rename(string1, string2).\n");
#endif
                          }                 					       
                      | INFNORMTOKEN
                          {
#ifdef HELP_INFNORM_TEXT
			    printf(HELP_INFNORM_TEXT);
#else
			    printf("Certified infinite norm: infnorm(func,range[,prooffile[,list of funcs]]).\n");
#endif
                          }                 					                      					       
                      | FINDZEROSTOKEN
                          {
#ifdef HELP_FINDZEROS_TEXT
			    printf(HELP_FINDZEROS_TEXT);
#else
			    printf("Certified bounding of zeros: findzeros(func,range).\n");
#endif
                          }                 					                    					       
                      | FPFINDZEROSTOKEN
                          {
#ifdef HELP_FPFINDZEROS_TEXT
			    printf(HELP_FPFINDZEROS_TEXT);
#else
			    printf("Approximate zeros of a function: fpfindzeros(func,range).\n");
#endif
                          }                 					                  					       
                      | DIRTYINFNORMTOKEN
                          {
#ifdef HELP_DIRTYINFNORM_TEXT
			    printf(HELP_DIRTYINFNORM_TEXT);
#else
			    printf("Floating-point infinite norm: dirtyinfnorm(func,range).\n");
#endif
                          }                 					                 					       
                      | INTEGRALTOKEN
                          {
#ifdef HELP_INTEGRAL_TEXT
			    printf(HELP_INTEGRAL_TEXT);
#else
			    printf("Certified integral: integral(func,range).\n");
#endif
                          }                 					                     					       
                      | DIRTYINTEGRALTOKEN
                          {
#ifdef HELP_DIRTYINTEGRAL_TEXT
			    printf(HELP_DIRTYINTEGRAL_TEXT);
#else
			    printf("Floating-point integral: dirtyintegral(func,range).\n");
#endif
                          }                 					             						       
                      | WORSTCASETOKEN
                          {
#ifdef HELP_WORSTCASE_TEXT
			    printf(HELP_WORSTCASE_TEXT);
#else
			    printf("Print all worst-cases under a certain bound: worstcase(func,constant,range,constant,constant[,file]).\n");
#endif
                          }                 					                    					       
                      | IMPLEMENTPOLYTOKEN
                          {
#ifdef HELP_IMPLEMENTPOLY_TEXT
			    printf(HELP_IMPLEMENTPOLY_TEXT);
#else
			    printf("Implement a polynomial in C: implementpoly(func,range,constant,format,string,string2[,honorcoeffprec[,string3]]).\n");
			    printf("Implements func in range with error constant with entering format named in function\nstring writing to file string2 honoring the precision of the coefficients or not with a proof in file string3.\n");
#endif
                          }                 					             						       
                      | CHECKINFNORMTOKEN
                          {
#ifdef HELP_CHECKINFNORM_TEXT
			    printf(HELP_CHECKINFNORM_TEXT);
#else
			    printf("Checks whether an infinite norm is bounded: checkinfnorm(func,range,constant).\n");
#endif
                          }                 					                 					       
                      | ZERODENOMINATORSTOKEN
                          {
#ifdef HELP_ZERODENOMINATORS_TEXT
			    printf(HELP_ZERODENOMINATORS_TEXT);
#else
			    printf("Searches floating-point approximations to zeros of denominators: zerodenominators(func,range).\n");
#endif
                          }                 					             					       
                      | ISEVALUABLETOKEN
                          {
#ifdef HELP_ISEVALUABLE_TEXT
			    printf(HELP_ISEVALUABLE_TEXT);
#else
			    printf("Tests if func is evaluable on range: isevaluable(func,range).\n");
#endif
                          }                 					                  					       
                      | SEARCHGALTOKEN
                          {
#ifdef HELP_SEARCHGAL_TEXT
			    printf(HELP_SEARCHGAL_TEXT);
#else
			    printf("Searches Gal values for func (or list of func): searchgal(func|list of func, constant, integer, integer, format|list of formats, constant|list of constants).\n");
#endif
                          }                 					                    					       
                      | GUESSDEGREETOKEN
                          {
#ifdef HELP_GUESSDEGREE_TEXT
			    printf(HELP_GUESSDEGREE_TEXT);
#else
			    printf("Guesses the degree needed for approximating func: guessdegree(func,range,constant[,weight]).\n");
#endif
                          }                 					                  					       
                      | DIRTYFINDZEROSTOKEN
                          {
#ifdef HELP_DIRTYFINDZEROS_TEXT
			    printf(HELP_DIRTYFINDZEROS_TEXT);
#else
			    printf("Finds zeros of a function dirtily: dirtyfindzeros(func,range).\n");
#endif
                          }                 					               					       
                      | IFTOKEN
                          {
			    printf("If construct: if condition then command or if condition then command else command.\n");
                          }                 					             							       
                      | THENTOKEN
                          {
			    printf("If construct: if condition then command or if condition then command else command.\n");
                          }                 					             							       
                      | ELSETOKEN
                          {
			    printf("If construct: if condition then command else command\n");
                          }                 					             							       
                      | FORTOKEN
                          {
			    printf("For construct: for i from const to const2 [by const3] do command\nor for i in list do command.\n");
                          }                 					             							       
                      | INTOKEN
                          {
			    printf("For construct: for i in list do command.\n");
                          }                 					             							       
                      | FROMTOKEN
                          {
			    printf("For construct: for i from const to const2 [by const3] do command.\n");
                          }                 					             							       
                      | TOTOKEN
                          {
			    printf("For construct: for i from const to const2 [by const3] do command.\n");
                          }                 					             							       
                      | BYTOKEN
                          {
			    printf("For construct: for i from const to const2 by const3 do command.\n");
                          }                 					             							       
                      | DOTOKEN
                          {
			    printf("For construct: for i from const to const2 [by const3] do command.\n");
			    printf("While construct: while condition do command.\n");
                          }                 					             							       
                      | BEGINTOKEN
                          {
			    printf("Begin-end construct: begin command; command; ... end.\n");
                          }                 					             							       
                      | ENDTOKEN
                          {
			    printf("Begin-end construct: begin command; command; ... end.\n");
                          }                 					             							       
                      | WHILETOKEN
                          {
			    printf("While construct: while condition do command.\n");
                          }                 					       
                      | INFTOKEN
                          {
#ifdef HELP_INF_TEXT
			    printf(HELP_INF_TEXT);
#else
			    printf("Dereferencing the infimum of a range: inf(range).\n");
#endif
                          }                 					       
                      | MIDTOKEN
                          {
#ifdef HELP_MID_TEXT
			    printf(HELP_MID_TEXT);
#else
			    printf("Dereferencing the midpoint of a range: mid(range).\n");
#endif
                          }                 					       
                      | SUPTOKEN
                          {
#ifdef HELP_SUP_TEXT
			    printf(HELP_SUP_TEXT);
#else
			    printf("Dereferencing the supremum of a range: sup(range).\n");
#endif
                          }                 					       
                      | EXPONENTTOKEN
                          {
#ifdef HELP_EXPONENT_TEXT
			    printf(HELP_EXPONENT_TEXT);
#else
			    printf("exponent(constant): returns an integer such that constant scaled by the power of 2\nof this integer is an odd or zero integer.\n");
#endif
                          }                 					       
                      | MANTISSATOKEN
                          {
#ifdef HELP_MANTISSA_TEXT
			    printf(HELP_MANTISSA_TEXT);
#else
			    printf("mantissa(constant): returns an odd or zero integer equal to constant scaled by an integer power of 2.\n");
#endif
                          }                 					       
                      | PRECISIONTOKEN
                          {
#ifdef HELP_PRECISION_TEXT
			    printf(HELP_PRECISION_TEXT);
#else
			    printf("precision(constant): returns the least number of bits constant can be written on.\n");
#endif
                          }                 					       
                      | EXECUTETOKEN
                          {
#ifdef HELP_EXECUTE_TEXT
			    printf(HELP_EXECUTE_TEXT);
#else
			    printf("execute(string): executes an %s script contained in a file named string.\n",PACKAGE_NAME);
#endif
                          }                 					       
                      | ISBOUNDTOKEN
                          {
#ifdef HELP_ISBOUND_TEXT
			    printf(HELP_ISBOUND_TEXT);
#else
			    printf("isbound(identifier): returns a boolean indicating if identifier is bound.\n");
#endif
                          }                 					       
                      | VERSIONTOKEN 
                          {
			    printf("Prints the version of the software.\n");
                          }                 					       
                      | EXTERNALPROCTOKEN                          {
#ifdef HELP_EXTERNALPROC_TEXT
			    printf(HELP_EXTERNALPROC_TEXT);
#else
			    printf("externalplot(identifier, file, argumentypes -> resulttype): binds identifier to an external procedure with signature argumenttypes -> resulttype in file.\n");
#endif
                          }                 					           
                      | VOIDTOKEN                          {
#ifdef HELP_VOID_TEXT
			    printf(HELP_VOID_TEXT);
#else
			    printf("Represents the void type for externalproc.\n");
#endif
                          }                 					       
                      | CONSTANTTYPETOKEN                          {
#ifdef HELP_CONSTANT_TEXT
			    printf(HELP_CONSTANT_TEXT);
#else
			    printf("Represents the constant type for externalproc.\n");
#endif
                          }                 					       
                      | FUNCTIONTOKEN                          {
#ifdef HELP_FUNCTION_TEXT
			    printf(HELP_FUNCTION_TEXT);
#else
			    printf("Represents the function type for externalproc.\n");
#endif
                          }                 					       
                      | RANGETOKEN                          {
#ifdef HELP_RANGE_TEXT
			    printf(HELP_RANGE_TEXT);
#else
			    printf("Represents the range type for externalproc.\n");
#endif
                          }                 					       
                      | INTEGERTOKEN                          {
#ifdef HELP_INTEGER_TEXT
			    printf(HELP_INTEGER_TEXT);
#else
			    printf("Represents the integer type for externalproc.\n");
#endif
                          }                 					       
                      | STRINGTYPETOKEN                          {
#ifdef HELP_STRING_TEXT
			    printf(HELP_STRING_TEXT);
#else
			    printf("Represents the string type for externalproc.\n");
#endif
                          }                 					       
                      | BOOLEANTOKEN                          {
#ifdef HELP_BOOLEAN_TEXT
			    printf(HELP_BOOLEAN_TEXT);
#else
			    printf("Represents the boolean type for externalproc.\n");
#endif
                          }                 					       
                      | LISTTOKEN                          {
#ifdef HELP_LISTOF_TEXT
			    printf(HELP_LISTOF_TEXT);
#else
			    printf("Represents the list type for externalproc.\n");
#endif
                          }                 					       
                      | OFTOKEN                          {
#ifdef HELP_LISTOF_TEXT
			    printf(HELP_LISTOF_TEXT);
#else
			    printf("Used in list of type for externalproc.\n");
#endif
                          }                 					       
                      | VARTOKEN                          {
#ifdef HELP_VAR_TEXT
			    printf(HELP_VAR_TEXT);
#else
			    printf("Declares a local variable.\n");
#endif
                          }                 					       
                      | NOPTOKEN                          {
#ifdef HELP_NOP_TEXT
			    printf(HELP_NOP_TEXT);
#else
			    printf("Does nothing.\n");
#endif
                          }                 		
                      | PROCTOKEN                          {
#ifdef HELP_PROC_TEXT
			    printf(HELP_PROC_TEXT);
#else
			    printf("Defines a nameless procedure.\n");
#endif
                          }                 					       			       
                      | PROCEDURETOKEN                     {
#ifdef HELP_PROCEDURE_TEXT
			    printf(HELP_PROCEDURE_TEXT);
#else
			    printf("Defines a named procedure.\n");
#endif
                          }                 					       			       
                      | HELPTOKEN
                          {
			    printf("Possible keywords in %s are:\n",PACKAGE_NAME);
			    printf("- ^\n");
			    printf("- <\n");
			    printf("- =\n");
			    printf("- ==\n");
			    printf("- >\n");
			    printf("- >_\n");
			    printf("- >.\n");
			    printf("- >*\n");
			    printf("- |\n");
			    printf("- ||\n");
			    printf("- -\n");
			    printf("- ,\n");
			    printf("- ;\n");
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
			    printf("- ]\n");
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
			    printf("- floor\n");
			    printf("- for\n");
			    printf("- fpfindzeros\n");
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


