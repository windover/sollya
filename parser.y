%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pari/pari.h>
#include "expression.h"
#include "chain.h"
#include "main.h"
#include "execute.h"
#include "parser.tab.h"

#define YYERROR_VERBOSE 1
#define YYPARSE_PARAM scanner
#define YYLEX_PARAM   scanner

extern int yylex(YYSTYPE *lvalp, void *scanner);
extern FILE *yyget_in(void *scanner);


void yyerror(char *message) {
  if (!feof(yyget_in(scanner))) {
    fprintf(stderr,"Warning: %s.\nWill skip input until next semicolon after the unexpected token. May leak memory.\n",message);
    promptToBePrinted = 1;
  }
}

%}

%expect 1

%pure_parser

%union {
  doubleNode *dblnode;
  char *value;
  node *tree;
  chain *list;
  void *other;
};



%token  <value> CONSTANTTOKEN;          					       
%token  <value> DYADICCONSTANTTOKEN;   					       
%token  <value> HEXCONSTANTTOKEN;       					       
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
%token  TAILTOKEN;		       
											       
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

											       
%token  PARSETOKEN;             					       
											       
%token  PRINTTOKEN;             					       
%token  PRINTXMLTOKEN;             					       
%token  PLOTTOKEN;              					       
%token  PRINTHEXATOKEN;         					       
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
											       
%token  HELPTOKEN;                                                           

%type <other> startsymbol;
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


%%

startsymbol:            command SEMICOLONTOKEN 
                          {
			    parsedThing = $1;
			    $$ = NULL;
			    YYACCEPT;
			  }
                      | HELPTOKEN help SEMICOLONTOKEN
                          {
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


command:                simplecommand
                          {
			    $$ = $1;
			  }
                      | BEGINTOKEN commandlist ENDTOKEN
                          {
			    $$ = makeCommandList($2);
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
                      | indexing
                          {
			    $$ = makeIndex($1->a, $1->b);
			    free($1);
			  }
;

indexing:               thing LBRACKETTOKEN thing RBRACKETTOKEN 
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
			    demaskString(tempString, $1);
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
                      | IDENTIFIERTOKEN LPARTOKEN thing RPARTOKEN
                          {
			    $$ = makeTableAccessWithSubstitute($1, $3);
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
;



constant:               CONSTANTTOKEN          					       
                          {
			    $$ = makeDecimalConstant($1);
			    free($1);
			  }
                      | DYADICCONSTANTTOKEN   					       
                          {
			    $$ = makeDyadicConstant($1);
			  }
                      | HEXCONSTANTTOKEN       					       
                          {
			    $$ = makeHexConstant($1);
			  }
                      | BINARYCONSTANTTOKEN    					       
                          {
			    $$ = makeBinaryConstant($1);
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
			    printf("\"%s\" is recognized as a double precision constant.\n",$1);
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
			    printf("Here should be some help text.\n");
                          }                  					       
                      | RPARTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | LBRACKETTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | RBRACKETTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | EQUALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | COMPAREEQUALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | COMMATOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | EXCLAMATIONTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | SEMICOLONTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | STARLEFTANGLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | LEFTANGLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | RIGHTANGLEUNDERSCORETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      					       
                      | RIGHTANGLEDOTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }       					       
                      | RIGHTANGLESTARTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | RIGHTANGLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }            					       
                      | DOTSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | QUESTIONMARKTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | VERTBARTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | ATTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | DOUBLECOLONTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | EXCLAMATIONEQUALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | ANDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | ORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | PLUSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | MINUSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | MULTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                						       
                      | DIVTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | POWTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | SQRTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | EXPTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | LOGTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | LOG2TOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | LOG10TOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | SINTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | COSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | TANTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | ASINTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | ACOSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | ATANTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | SINHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | COSHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | TANHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | ASINHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | ACOSHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | ATANHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | ABSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | ERFTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | ERFCTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | LOG1PTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | EXPM1TOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | DOUBLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | DOUBLEDOUBLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | TRIPLEDOUBLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | DOUBLEEXTENDEDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | CEILTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | FLOORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 			
                      | HEADTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | TAILTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    		       
                      | PRECTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | POINTSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | DIAMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | DISPLAYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | VERBOSITYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | CANONICALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | AUTOSIMPLIFYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | TAYLORRECURSIONSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      					       
                      | TIMINGTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | FULLPARENTHESESTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }       					       
                      | MIDPOINTMODETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | HOPITALRECURSIONSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      					       
                      | ONTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                    					       
                      | OFFTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                   					       
                      | DYADICTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | POWERSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | BINARYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | FILETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | POSTSCRIPTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }            					       
                      | POSTSCRIPTFILETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | PERTURBTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | MINUSWORDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | PLUSWORDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | ZEROWORDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | NEARESTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | HONORCOEFFPRECTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }       					       
                      | TRUETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | FALSETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | DEFAULTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    											       
                      | ABSOLUTETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | DECIMALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | RELATIVETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | ERRORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    			
                      | QUITTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | FALSEQUITTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | RESTARTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | LIBRARYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | DIFFTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | SIMPLIFYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | REMEZTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | HORNERTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | EXPANDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | SIMPLIFYSAFETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | TAYLORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | DEGREETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                					       
                      | NUMERATORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | DENOMINATORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | SUBSTITUTETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }            					       
                      | COEFFTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | SUBPOLYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | ROUNDCOEFFICIENTSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }       					       
                      | RATIONALAPPROXTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | ACCURATEINFNORMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | ROUNDTOFORMATTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }         					       
                      | EVALUATETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | LENGTHTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | PARSETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | PRINTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | PRINTXMLTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | PLOTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                  					       
                      | PRINTHEXATOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | PRINTBINARYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | PRINTEXPANSIONTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | BASHEXECUTETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | EXTERNALPLOTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | WRITETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }                 					       
                      | ASCIIPLOTTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        
                      | RENAMETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        	       
                      | INFNORMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }               					       
                      | FINDZEROSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | FPFINDZEROSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | DIRTYINFNORMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | INTEGRALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }              					       
                      | DIRTYINTEGRALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | WORSTCASETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | IMPLEMENTPOLYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      						       
                      | CHECKINFNORMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }          					       
                      | ZERODENOMINATORSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      					       
                      | ISEVALUABLETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | SEARCHGALTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }             					       
                      | GUESSDEGREETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }           					       
                      | DIRTYFINDZEROSTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }        					       
                      | IFTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | THENTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | ELSETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | FORTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | INTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | FROMTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | TOTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | BYTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | DOTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | BEGINTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | ENDTOKEN
                          {
			    printf("Here should be some help text.\n");
                          }      							       
                      | WHILETOKEN
                          {
			    printf("Here should be some help text.\n");
                          }    
                      | HELPTOKEN
                          {
			    printf("Possible keywords in the arenaireplot tool are:\n");
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
			    printf("- !\n");
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
			    printf("- by\n");
			    printf("- canonical\n");
			    printf("- ceil\n");
			    printf("- checkinfnorm\n");
			    printf("- coeff\n");
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
			    printf("- exp\n");
			    printf("- expand\n");
			    printf("- expm1\n");
			    printf("- externalplot\n");
			    printf("- false\n");
			    printf("- file\n");
			    printf("- findzeros\n");
			    printf("- floor\n");
			    printf("- for\n");
			    printf("- fpfindzeros\n");
			    printf("- from\n");
			    printf("- fullparentheses\n");
			    printf("- guessdegree\n");
			    printf("- head\n");
			    printf("- help\n");
			    printf("- honorcoeffprec\n");
			    printf("- hopitalrecursions\n");
			    printf("- horner\n");
			    printf("- if\n");
			    printf("- implementpoly\n");
			    printf("- in\n");
			    printf("- infnorm\n");
			    printf("- integral\n");
			    printf("- isevaluable\n");
			    printf("- length\n");
			    printf("- library\n");
			    printf("- log\n");
			    printf("- log10\n");
			    printf("- log1p\n");
			    printf("- log2\n");
			    printf("- M\n");
			    printf("- midpointmode\n");
			    printf("- N\n");
			    printf("- numerator\n");
			    printf("- off\n");
			    printf("- on\n");
			    printf("- P\n");
			    printf("- parse\n");
			    printf("- perturb\n");
			    printf("- pi\n");
			    printf("- plot\n");
			    printf("- points\n");
			    printf("- postscript\n");
			    printf("- postscriptfile\n");
			    printf("- powers\n");
			    printf("- prec\n");
			    printf("- print\n");
			    printf("- printbinary\n");
			    printf("- printexpansion\n");
			    printf("- printhexa\n");
			    printf("- printxml\n");
			    printf("- quit\n");
			    printf("- rationalapprox\n");
			    printf("- read\n");
			    printf("- relative\n");
			    printf("- remez\n");
			    printf("- rename\n");
			    printf("- restart\n");
			    printf("- roundcoefficients\n");
			    printf("- roundtoformat\n");
			    printf("- searchgal\n");
			    printf("- simplify\n");
			    printf("- simplifysafe\n");
			    printf("- sin\n");
			    printf("- sinh\n");
			    printf("- sqrt\n");
			    printf("- subpoly\n");
			    printf("- substitute\n");
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
			    printf("- while\n");
			    printf("- worstcase\n");
			    printf("- write\n");
			    printf("- Z\n");
			    printf("- zerodenominators\n");
			    printf("\n");
                          }                                                           
;


