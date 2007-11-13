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
									       
%token  HELPTOKEN;      
%token  VERSIONTOKEN;
                                                     

%type <other> startsymbol;
%type <other> help;
%type <other> helpmeta;
%type <tree>  command;
%type <tree>  simplecommand;
%type <list>  commandlist;
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

simplecommand:          QUITTOKEN
                          {
			    $$ = makeQuit();
			  }
                      | FALSEQUITTOKEN
                          {
			    $$ = makeFalseQuit();
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
			    printf("Here should be some help text.\n");
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
			    printf("Right bracker - indicates a range or a list.\n");
                          }              					       
                      | EQUALTOKEN
                          {
			    printf("Assignment operator.\n");
                          }                 					       
                      | COMPAREEQUALTOKEN
                          {
			    printf("Equality test.\n");
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
			    printf("Comparison less than.\n");
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
			    printf("Comparison greater than.\n");
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
			    printf("Concatenation of lists or strings.\n");
                          }      							       
                      | DOUBLECOLONTOKEN
                          {
			    printf("a::b prepends a to list b or appends b to list a, preprending list a to list b if both are lists.\n");
                          }    
                      | DOTCOLONTOKEN
                          {
			    printf("a.:b prepends a to list b.\n");
                          }    
                      | COLONDOTTOKEN
                          {
			    printf("a:.b appends b to list a.\n");
                          }    
                      | EXCLAMATIONEQUALTOKEN
                          {
			    printf("Comparison not equal.\n");
                          }    
                      | ANDTOKEN
                          {
			    printf("Boolean and.\n");
                          }    
                      | ORTOKEN
                          {
			    printf("Boolean or.\n");
                          }    
                      | PLUSTOKEN
                          {
			    printf("Addition.\n");
                          }                  					       
                      | MINUSTOKEN
                          {
			    printf("Substraction.\n");
                          }                 					       
                      | MULTOKEN
                          {
			    printf("Multiplication.\n");
                          }                						       
                      | DIVTOKEN
                          {
			    printf("Division.\n");
                          }                  					       
                      | POWTOKEN
                          {
			    printf("Exponentiation.\n");
                          }                  					       
                      | SQRTTOKEN
                          {
			    printf("Square root.\n");
                          }                  					       
                      | EXPTOKEN
                          {
			    printf("Exponential.\n");
                          }                   					       
                      | LOGTOKEN
                          {
			    printf("Natural logarithm.\n");
                          }                   					       
                      | LOG2TOKEN
                          {
			    printf("Logarithm in base 2.\n");
                          }                  					       
                      | LOG10TOKEN
                          {
			    printf("Logarithm in base 10.\n");
                          }                 					       
                      | SINTOKEN
                          {
			    printf("Sine.\n");
                          }                   					       
                      | COSTOKEN
                          {
			    printf("Cosine.\n");
                          }                   					       
                      | TANTOKEN
                          {
			    printf("Tangent.\n");
                          }                   					       
                      | ASINTOKEN
                          {
			    printf("Arcsine.\n");
                          }                  					       
                      | ACOSTOKEN
                          {
			    printf("Arcosine.\n");
                          }                  					       
                      | ATANTOKEN
                          {
			    printf("Arctangent.\n");
                          }                  					       
                      | SINHTOKEN
                          {
			    printf("Hyperbolic sine.\n");
                          }                  					       
                      | COSHTOKEN
                          {
			    printf("Hyperbolic cosine.\n");
                          }                  					       
                      | TANHTOKEN
                          {
			    printf("Hyperbolic tangent.\n");
                          }                  					       
                      | ASINHTOKEN
                          {
			    printf("Area sine.\n");
                          }                 					       
                      | ACOSHTOKEN
                          {
			    printf("Area cosine.\n");
                          }                 					       
                      | ATANHTOKEN
                          {
			    printf("Area tangent.\n");
                          }                 					       
                      | ABSTOKEN
                          {
			    printf("Absolute value.\n");
                          }                   					       
                      | ERFTOKEN
                          {
			    printf("Error function.\n");
                          }                   					       
                      | ERFCTOKEN
                          {
			    printf("Complementary error function.\n");
                          }                  					       
                      | LOG1PTOKEN
                          {
			    printf("Natural logarithm of 1 plus argument.\n");
                          }                 					       
                      | EXPM1TOKEN
                          {
			    printf("Exponential of argument minus 1.\n");
                          }                 					       
                      | DOUBLETOKEN
                          {
			    printf("Double precision rounding operator.\n");
                          }                					       
                      | DOUBLEDOUBLETOKEN
                          {
			    printf("Double-double precision rounding operator.\n");
                          }      						       
                      | TRIPLEDOUBLETOKEN
                          {
			    printf("Triple-double precision rounding operator.\n");
                          }          					       
                      | DOUBLEEXTENDEDTOKEN
                          {
			    printf("Double-extended precision rounding operator.\n");
                          }        					       
                      | CEILTOKEN
                          {
			    printf("Ceiling.\n");
                          }                  					       
                      | FLOORTOKEN
                          {
			    printf("Floor.\n");
                          }                 			
                      | HEADTOKEN
                          {
			    printf("Head of a list.\n");
                          }   
                      | ROUNDCORRECTLYTOKEN
                          {
			    printf("Round a bounding to the nearest floating-point value such that correct rounding is possible.\n");
                          }   
                      | READFILETOKEN
                          {
			    printf("Reads a file into a string.\n");
                          }    
                      | REVERTTOKEN
                          {
			    printf("Reverts a list that is not finally elliptic.\n");
                          }    
                      | SORTTOKEN
                          {
			    printf("Sorts a list of constants in ascending order.\n");
                          }    
                      | TAILTOKEN
                          {
			    printf("Tail of a list.\n");
                          }    		       
                      | PRECTOKEN
                          {
			    printf("Global environment variable precision.\n");
                          }                  					       
                      | POINTSTOKEN
                          {
			    printf("Global environment variable number of points.\n");
                          }                					       
                      | DIAMTOKEN
                          {
			    printf("Global environment variable diameter.\n");
                          }                  					       
                      | DISPLAYTOKEN
                          {
			    printf("Global environment variable display mode.\n");
                          }                					       
                      | VERBOSITYTOKEN
                          {
			    printf("Global environment variable verbosity.\n");
                          }             					       
                      | CANONICALTOKEN
                          {
			    printf("Global environment variable canonical output.\n");
                          }             					       
                      | AUTOSIMPLIFYTOKEN
                          {
			    printf("Global environment variable automatic simplification.\n");
                          }          					       
                      | TAYLORRECURSIONSTOKEN
                          {
			    printf("Global environement variable recursions of Taylor evaluation.\n");
                          }      					       
                      | TIMINGTOKEN
                          {
			    printf("Global environement variable timing of computations.\n");
                          }                					       
                      | FULLPARENTHESESTOKEN
                          {
			    printf("Global environement variable fully parenthized mode.\n");
                          }       					       
                      | MIDPOINTMODETOKEN
                          {
			    printf("Global environement variable midpoint mode.\n");
                          }          					       
                      | HOPITALRECURSIONSTOKEN
                          {
			    printf("Global environement variable recursions of Hopital evaluation.\n");
                          }      					       
                      | ONTOKEN
                          {
			    printf("Something is switched on.\n");
                          }                    					       
                      | OFFTOKEN
                          {
			    printf("Something is switched off.\n");
                          }                   					       
                      | DYADICTOKEN
                          {
			    printf("Display mode is dyadic output.\n");
                          }      						       
                      | POWERSTOKEN
                          {
			    printf("Display mode is dyadic output with powers.\n");
                          }                					       
                      | BINARYTOKEN
                          {
			    printf("Display mode is binary.\n");
                          }                					       
                      | HEXADECIMALTOKEN
                          {
			    printf("Display mode is hexadecimal.\n");
                          }                					       
                      | FILETOKEN
                          {
			    printf("A file will be specified.\n");
                          }                  					       
                      | POSTSCRIPTTOKEN
                          {
			    printf("A postscript file will be specified.\n");
                          }            					       
                      | POSTSCRIPTFILETOKEN
                          {
			    printf("A postscript file and a file will be specified.\n");
                          }        					       
                      | PERTURBTOKEN
                          {
			    printf("Perturbation is demanded.\n");
                          }               					       
                      | MINUSWORDTOKEN
                          {
			    printf("Round towards minus infinity.\n");
                          }             					       
                      | PLUSWORDTOKEN
                          {
			    printf("Round towards plus infinity.\n");
                          }              					       
                      | ZEROWORDTOKEN
                          {
			    printf("Round towards zero.\n");
                          }              					       
                      | NEARESTTOKEN
                          {
			    printf("Round to nearest.\n");
                          }               					       
                      | HONORCOEFFPRECTOKEN
                          {
			    printf("Honorate the precision of the coefficients.\n");
                          }       					       
                      | TRUETOKEN
                          {
			    printf("Boolean constant true.\n");
                          }      							       
                      | FALSETOKEN
                          {
			    printf("Boolean constant false.\n");
                          }      							       
                      | DEFAULTTOKEN
                          {
			    printf("Default value.\n");
                          }    											       
                      | ABSOLUTETOKEN
                          {
			    printf("Consider an absolute error.\n");
                          }    
                      | DECIMALTOKEN
                          {
			    printf("Display mode is decimal.\n");
                          }    
                      | RELATIVETOKEN
                          {
			    printf("Consider a relative error.\n");
                          }    
                      | ERRORTOKEN
                          {
			    printf("Type error meta-value.\n");
                          }    			
                      | QUITTOKEN
                          {
			    printf("Exit from the tool.\n");
                          }                  					       
                      | FALSEQUITTOKEN
                          {
			    printf("Exit from the tool - help is called inside a read macro.\n");
                          }      						       
                      | RESTARTTOKEN
                          {
			    printf("Restart the tool.\n");
                          }               					       
                      | LIBRARYTOKEN
                          {
			    printf("Library binding dereferencer.\n");
                          }               					       
                      | DIFFTOKEN
                          {
			    printf("Differentiation: diff(func).\n");
                          }                  					       
                      | SIMPLIFYTOKEN
                          {
			    printf("Simplify: simplify(func).\n");
                          }      						       
                      | REMEZTOKEN
                          {
			    printf("Remez: remez(func,degree|monoms,range[,weight[,quality]]).\n");
                          }                 					       
                      | HORNERTOKEN
                          {
			    printf("Horner: horner(func)\n");
                          }                					       
                      | EXPANDTOKEN
                          {
			    printf("Expand: expand(func).\n");
                          }                					       
                      | SIMPLIFYSAFETOKEN
                          {
			    printf("Safe simplification: simplifysafe(func).\n");
                          }      						       
                      | TAYLORTOKEN
                          {
			    printf("Taylor expansion: taylor(func,degree,point).\n");
                          }               					       
                      | DEGREETOKEN
                          {
			    printf("Degree of a polynomial: degree(func).\n");
                          }                					       
                      | NUMERATORTOKEN
                          {
			    printf("Numerator of an expression: numerator(func).\n");
                          }             					       
                      | DENOMINATORTOKEN
                          {
			    printf("Denominator of an expression: denominator(func).\n");
                          }           					       
                      | SUBSTITUTETOKEN
                          {
			    printf("Substitute func2 for free variable in func: substitute(func,func2).\n");
                          }            					       
                      | COEFFTOKEN
                          {
			    printf("i-th coefficient of a polynomial: coeff(func,degree).\n");
                          }                 					       
                      | SUBPOLYTOKEN
                          {
			    printf("Subpolynomial consisting in monomials: subpoly(func,list of degrees).\n");
                          }               					       
                      | ROUNDCOEFFICIENTSTOKEN
                          {
			    printf("Round coefficients of a polynomial to format: roundcoefficients(func,list of formats).\n");
                          }       					       
                      | RATIONALAPPROXTOKEN
                          {
			    printf("Rational approximation: rationalapprox(constant).\n");
                          }        					       
                      | ACCURATEINFNORMTOKEN
                          {
			    printf("Faithful rounded infinite norm: accurateinfnorm(func,bits,range,domains to exclude).\n");
                          }        					       
                      | ROUNDTOFORMATTOKEN
                          {
			    printf("Round to a given format: round(constant,precision,rounding mode).\n");
                          }         					       
                      | EVALUATETOKEN
                          {
			    printf("Evaluate a function in a point or interval: round(func,constant|range).\n");
                          }              					       
                      | LENGTHTOKEN
                          {
			    printf("Length of a list: length(list).\n");
                          }    
                      | PARSETOKEN
                          {
			    printf("Parse a string to function: parse(string).\n");
                          }                 					       
                      | PRINTTOKEN
                          {
			    printf("Print something: print(thing1, thing2, ...).\n");
                          }                 					       
                      | PRINTXMLTOKEN
                          {
			    printf("Print a function in XML: printxml(func).\n");
                          }                 					       
                      | READXMLTOKEN
                          {
			    printf("Reads a function in XML: readxml(filename).\n");
                          }                 					       
                      | PLOTTOKEN
                          {
			    printf("Plot (a) function(s) in a range: plot(func,func2,...,range).\n");
			    printf("There are further options.\n");
                          }                  					       
                      | PRINTHEXATOKEN
                          {
			    printf("Print a constant in hexadecimal: printhexa(constant).\n");
                          }      
                      | PRINTFLOATTOKEN
                          {
			    printf("Print a constant in hexadecimal simple precision: printfloat(constant).\n");
                          }             					       
                      | PRINTBINARYTOKEN
                          {
			    printf("Print a constant in binary: printbinary(constant).\n");
                          }           					       
                      | PRINTEXPANSIONTOKEN
                          {
			    printf("Print a polynomial as an expansion of double precision numbers: printexpansion(func).\n");
                          }        					       
                      | BASHEXECUTETOKEN
                          {
			    printf("Execute a command in a shell: bashexecute(string).\n");
                          }           					       
                      | EXTERNALPLOTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | WRITETOKEN
                          {
			    printf("Write something without adding spaces and newlines: write(thing1, thing2, ...).\n");
                          }                 					       
                      | ASCIIPLOTTOKEN
                          {
			    printf("Plot a function in a range using an ASCII terminal: asciiplot(func,range).\n");
                          }        
                      | RENAMETOKEN
                          {
			    printf("Rename free variable string1 to string2: rename(string1, string2).\n");
                          }        	       
                      | INFNORMTOKEN
                          {
			    printf("Certified infinite norm: infnorm(func,range[,prooffile[,list of funcs]]).\n");
                          }               					       
                      | FINDZEROSTOKEN
                          {
			    printf("Certified bounding of zeros: findzeros(func,range).\n");
                          }             					       
                      | FPFINDZEROSTOKEN
                          {
			    printf("Approximate zeros of a function: fpfindzeros(func,range).\n");
                          }           					       
                      | DIRTYINFNORMTOKEN
                          {
			    printf("Floating-point infinite norm: dirtyinfnorm(func,range).\n");
                          }          					       
                      | INTEGRALTOKEN
                          {
			    printf("Certified integral: integral(func,range).\n");
                          }              					       
                      | DIRTYINTEGRALTOKEN
                          {
			    printf("Floating-point integral: dirtyintegral(func,range).\n");
                          }      						       
                      | WORSTCASETOKEN
                          {
			    printf("Print all worst-cases under a certain bound: worstcase(func,constant,range,constant,constant[,file]).\n");
                          }             					       
                      | IMPLEMENTPOLYTOKEN
                          {
			    printf("Implement a polynomial in C: implementpoly(func,range,constant,format,string,string2[,honorcoeffprec[,string3]]).\n");
			    printf("Implements func in range with error constant with entering format named in function\nstring writing to file string2 honoring the precision of the coefficients or not with a proof in file string3.\n");
                          }      						       
                      | CHECKINFNORMTOKEN
                          {
			    printf("Checks whether an infinite norm is bounded: checkinfnorm(func,range,constant).\n");
                          }          					       
                      | ZERODENOMINATORSTOKEN
                          {
			    printf("Searches floating-point approximations to zeros of denominators: zerodenominators(func,range).\n");
                          }      					       
                      | ISEVALUABLETOKEN
                          {
			    printf("Tests if func is evaluable on range: isevaluable(func,range).\n");
                          }           					       
                      | SEARCHGALTOKEN
                          {
			    printf("Searches Gal values for func (or list of func): searchgal(func|list of func, constant, integer, integer, format|list of formats, constant|list of constants).\n");
                          }             					       
                      | GUESSDEGREETOKEN
                          {
			    printf("Guesses the degree needed for approximating func: guessdegree(func,range,constant[,weight]).\n");
                          }           					       
                      | DIRTYFINDZEROSTOKEN
                          {
			    printf("Finds zeros of a function dirtily: dirtyfindzeros(func,range).\n");
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
			    printf("Dereferencing the infimum of a range: inf(range).\n");
                          }    
                      | MIDTOKEN
                          {
			    printf("Dereferencing the midpoint of a range: mid(range).\n");
                          }    
                      | SUPTOKEN
                          {
			    printf("Dereferencing the supremum of a range: sup(range).\n");
                          }    
                      | EXPONENTTOKEN
                          {
			    printf("exponent(constant): returns an integer such that constant scaled by the power of 2\nof this integer is an odd or zero integer.\n");
                          }    
                      | MANTISSATOKEN
                          {
			    printf("mantissa(constant): returns an odd or zero integer equal to constant scaled by an integer power of 2.\n");
                          }    
                      | PRECISIONTOKEN
                          {
			    printf("precision(constant): returns the least number of bits constant can be written on.\n");
                          }    
                      | EXECUTETOKEN
                          {
			    printf("execute(string): executes an %s script contained in a file named string.\n",PACKAGE_NAME);
                          }    
                      | ISBOUNDTOKEN
                          {
			    printf("isbound(identifier): returns a boolean indicating if identifier is bound.\n");
                          }   
                      | VERSIONTOKEN 
                          {
			    printf("Prints the version of the software.\n");
                          }    
                      | EXTERNALPROCTOKEN                          {
			    printf("externalplot(identifier, file, argumentypes -> resulttype): binds identifier to an external procedure with signature argumenttypes -> resulttype in file.\n");
                          }    
                      | VOIDTOKEN                          {
			    printf("Represents the void type for externalproc.\n");
                          }    
                      | CONSTANTTYPETOKEN                          {
			    printf("Represents the constant type for externalproc.\n");
                          }    
                      | FUNCTIONTOKEN                          {
			    printf("Represents the function type for externalproc.\n");
                          }    
                      | RANGETOKEN                          {
			    printf("Represents the range type for externalproc.\n");
                          }    
                      | INTEGERTOKEN                          {
			    printf("Represents the integer type for externalproc.\n");
                          }    
                      | STRINGTYPETOKEN                          {
			    printf("Represents the string type for externalproc.\n");
                          }    
                      | BOOLEANTOKEN                          {
			    printf("Represents the boolean type for externalproc.\n");
                          }    
                      | LISTTOKEN                          {
			    printf("Represents the list type for externalproc.\n");
                          }    
                      | OFTOKEN                          {
			    printf("Used in list of type for externalproc.\n");
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
			    printf("- autosymplify\n");
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
			    printf("- dirtinfnorm\n");
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


