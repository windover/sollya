%{

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "parser.tab.h"
#include "main.h"
#include "chain.h"

#define YY_NO_UNPUT 1

%}

%option noyywrap
%option always-interactive
%option reentrant
%option bison-bridge
%option nounput

%x readstate
%x readstate2
%x commentstate

CHAR		[a-zA-Z]
NUMBER		[0-9]
HEXNUMBER       (([0-9])|([ABCDEFabcdef]))

CONSTANT        ({NUMBER}+|({NUMBER}*"."{NUMBER}+))(("~"{NUMBER}"/"{NUMBER}"~")?)(((((" ")*)(([eE]))([+-])?{NUMBER}+)?))
DYADICCONSTANT  ({NUMBER}+)([bB])([+-]?)({NUMBER}+)
HEXCONSTANT     ("0x"){HEXNUMBER}{16}

BINARYCONSTANT  (([0-1])+|(([0-1])*"."([0-1])+))"_2"


IDENTIFIER        {CHAR}({CHAR}|{NUMBER})*

LPAR            "("
RPAR            ")"

LBRACKET        "["
RBRACKET        "]"
	       	
PI              ("pi")|("Pi")

PLUS            "+"
MINUS           "-"
MUL             "*"
DIV             "/"
POW             "^"
SQRT            "sqrt"
EXP             "exp"
LOG             "log"
LOG2            "log2"
LOG10           "log10"
SIN             "sin"
COS             "cos"
TAN             "tan"
ASIN            "asin"
ACOS            "acos"
ATAN            "atan"
SINH            "sinh"
COSH            "cosh"
TANH            "tanh"
ASINH           "asinh"
ACOSH           "acosh"
ATANH           "atanh"
ABS             "abs"
ERF             "erf"
ERFC            "erfc"
LOG1P           "log1p"
EXPM1           "expm1"

EQUAL           "="
COMMA           ","
PREC            "prec"
POINTS          "points"
EXCLAMATION     "!"
DOUBLECOLON     "::"
	       	
SEMICOLON       ";"
QUIT            "quit"
PRINT           "print"
DIFF            "diff"
SIMPLIFY        "simplify"
CANONICAL       "canonical"
PLOT            "plot"
REMEZ           "remez"
INFNORM         "infnorm"
DIAM            "diam"

DOUBLELONG       "double"
DOUBLEDOUBLELONG "doubledouble"
TRIPLEDOUBLELONG "tripledouble"
DOUBLEEXTENDEDLONG "doubleextended"


DOUBLESHORT      "D"
DOUBLEDOUBLESHORT "DD"
TRIPLEDOUBLESHORT "TD"
DOUBLEEXTENDEDSHORT "DE"


DOUBLE          ({DOUBLELONG}|{DOUBLESHORT})
DOUBLEDOUBLE    ({DOUBLEDOUBLELONG}|{DOUBLEDOUBLESHORT})
TRIPLEDOUBLE    ({TRIPLEDOUBLELONG}|{TRIPLEDOUBLESHORT})
DOUBLEEXTENDED  ({DOUBLEEXTENDEDLONG}|{DOUBLEEXTENDEDSHORT})

HORNER          "horner"
DEGREE          "degree"
EXPAND          "expand"

SIMPLIFYSAFE1   "safesimplify"
SIMPLIFYSAFE2   "simplifysafe"

SIMPLIFYSAFE    ({SIMPLIFYSAFE1}|{SIMPLIFYSAFE2})

TAYLOR          "taylor"

FINDZEROS       "findzeros"
FPFINDZEROS     "fpfindzeros"
DIRTYINFNORM    "dirtyinfnorm"

EVALUATE        "evaluate"


NUMERATOR       "numerator"
DENOMINATOR     "denominator"

DYADIC          "dyadic"
DISPLAY         "display"
ON              "on"
OFF             "off"
POWERS          "powers"
BINARY          "binary"

INTEGRAL        "integral"
DIRTYINTEGRAL   "dirtyintegral"

STRINGDELIMITER [\"]
OCTALCHAR       [01234567]
OCTAL           ({OCTALCHAR})(({OCTALCHAR})?)(({OCTALCHAR})?)
HEXACHAR        [0123456789ABCDEFabcdef]
HEXA            ({HEXACHAR})(({HEXACHAR})?)
STRING          ({STRINGDELIMITER})((("\\\\")|(("\\")[\"\'\?ntabfrv])|(("\\")({OCTAL}))|(("\\x")({HEXA}))|([^\"\\]))*)({STRINGDELIMITER})


VERBOSITY       "verbosity"

WORSTCASE       "worstcase"

LEFTANGLE       "<"
RIGHTANGLEUNDERSCORE ">_"
RIGHTANGLEDOT ">."
RIGHTANGLE      ">"
STARLEFTANGLE   "*<"
RIGHTANGLESTAR  ">*"

COMPAREEQUAL    "=="
EXCLAMATIONEQUAL "!="

AND             "&&"
OR              "||"

SUBSTITUTE      "substitute"

DOTS            "..."

IMPLEMENTPOLY   "implementpoly"

CHECKINFNORM    "checkinfnorm"

TAYLORRECURSIONS "taylorrecursions"

PRINTHEXA       "printhexa"
PRINTBINARY     "printbinary"

ROUNDCOEFFICIENTS "roundcoefficients"


RESTART         "restart"


ZERODENOMINATORS "zerodenominators"
ISEVALUABLE     "isevaluable"
HONORCOEFFPREC  "honorcoeffprec"

ACCURATEINFNORM  "accurateinfnorm"


FILE            "file"
POSTSCRIPT      "postscript"
POSTSCRIPTFILE  "postscriptfile"

PRINTEXPANSION  "printexpansion"

BASHEXECUTE     "bashexecute"
EXTERNALPLOT    "externalplot"
PERTURB         "perturb"

COEFF           "coeff"
SUBPOLY         "subpoly"

QUESTIONMARK    "?"

SEARCHGAL       "searchgal"


RATIONALAPPROX  "rationalapprox"

READ            "read"

COMMENTSTART    "/*"
COMMENTEND      "*/"

ONELINECOMMENT  ("//"|"#")([^\n])*"\n"

WRITE           "write"

ASCIIPLOT       "asciiplot"


ROUNDTOFORMAT   "round"
MINUSWORD       "M"
PLUSWORD        "P"
ZEROWORD        "Z"
NEAREST         "N"


GUESSDEGREE     "guessdegree"

PARSE           "parse"

AUTOSIMPLIFY    "autosimplify"

TIMING          "timing"
FULLPARENTHESES "fullparentheses"
MIDPOINTMODE    "midpointmode"

LIBRARY         "library"

HOPITALRECURSIONS "hopitalrecursions"

HELP            "help"

DIRTYFINDZEROS  "dirtyfindzeros"

CEIL            "ceil"
FLOOR           "floor"

HEAD            "head"
TAIL            "tail"

VERTBAR         "|"
AT              "@"

IF              "if"
THEN            "then"
ELSE            "else"
FOR             "for"
IN              "in"
FROM            "from"
TO              "to"
BY              "by"
DO              "do"
BEGINLONG       "begin"
ENDLONG         "end"
BEGINSHORT      "{"
ENDSHORT        "}"
BEGIN           ({BEGINSHORT}|{BEGINLONG})
END             ({ENDSHORT}|{ENDLONG})

WHILEDEF        "while"

TRUE            "true"
FALSE           "false"
DEFAULT         "default"

RENAME          "rename"

LENGTH          "length"

ABSOLUTE        "absolute"
RELATIVE        "relative"
DECIMAL         "decimal"

ERROR           "error"

PRINTXML        "printxml"

INF             "inf"
MID             "mid"
SUP             "sup"


%%

%{
  YY_BUFFER_STATE *currStatePtr;
%}




{COMMENTSTART}  {     BEGIN(commentstate); }

<commentstate>{COMMENTEND} { BEGIN(INITIAL); }

<commentstate>. { // Eat up comments 

                 }

<commentstate>[\n] { // Eat up newlines in comments

		}



{ONELINECOMMENT} {  // Eat up comments

                 }


{READ}          {
                      BEGIN(readstate);
                }

<readstate>{STRING}  {
                       if (newReadFilename != NULL) free(newReadFilename);
		       newReadFilename = NULL;
		       newReadFilename = (char*) safeCalloc(yyleng - 1,sizeof(char));
		       strncpy(newReadFilename,yytext+1,yyleng-2);
		       BEGIN(readstate2);
                }

<readstate>[ \t]     { /* Eat up spaces and tabulators */
		}

<readstate>.         { /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

<readstate2>{SEMICOLON} {
                      newReadFilenameTemp = (char *) safeCalloc(strlen(newReadFilename)+1,sizeof(char));
		      demaskString(newReadFilenameTemp,newReadFilename);
		      temp_fd = fopen(newReadFilenameTemp,"r");
		      if (temp_fd == NULL) {
			printMessage(1,"Warning: the file \"%s\" could not be opened for reading: ",newReadFilenameTemp);
			printMessage(1,"\"%s\".\n",strerror(errno));
			printMessage(1,"The last command will have no effect. No memory will be lost.\n");
		      } else {
			newReadFileStarted();
			currStatePtr = (YY_BUFFER_STATE *) safeMalloc(sizeof(YY_BUFFER_STATE));
			*currStatePtr = YY_CURRENT_BUFFER;
			readStack = addElement(readStack, (void *) currStatePtr);
			tempFDPtr = (FILE **) safeMalloc(sizeof(FILE *));
			*tempFDPtr = yyin;
			readStack2 = addElement(readStack2, (void *) tempFDPtr);
			yyin = temp_fd;
			yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE, scanner), scanner);
		      }
		      free(newReadFilenameTemp);
		      BEGIN(INITIAL);
                }

<readstate2>[ \t]     { /* Eat up spaces and tabulators */
		}

<readstate2>.         { /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

<<EOF>>         {
                      if (readStack == NULL) {
			printf("\n");
			yyterminate();
		      } else {
			fclose(yyin);
			yyin = *((FILE **) (readStack2->value));
			free(readStack2->value);
			readStackTemp = readStack2->next;
			free(readStack2);
			readStack2 = readStackTemp;
			yy_delete_buffer(YY_CURRENT_BUFFER, scanner);
			yy_switch_to_buffer(*((YY_BUFFER_STATE *) (readStack->value)),scanner);
			free(readStack->value);
			readStackTemp = readStack->next;
			free(readStack);
			readStack = readStackTemp;
		      }
                }

{CONSTANT}                                  { 
					      constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      constBuffer2 = (char *) safeCalloc(yyleng+1,sizeof(char));
					      if (removeSpaces(constBuffer2,yytext)) {
						printMessage(2,"Information: removed spaces in scientific notation constant \"%s\", it will be considered as \"%s\"\n",yytext,constBuffer2);
					      }
					      if (removeMidpointMode(constBuffer,constBuffer2)) {
						printMessage(2,"Information: removed midpoint information in scientific notation constant \"%s\", it will be considered as \"%s\"\n",constBuffer2,constBuffer);
					      }
					      free(constBuffer2);
					      yylval->value = constBuffer;
                                              newTokenLexed(); return CONSTANTTOKEN; }        		       
{DYADICCONSTANT} 			    { 
                                              constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
                                              newTokenLexed(); return DYADICCONSTANTTOKEN; } 	              
{HEXCONSTANT}     			    { constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
                                              newTokenLexed(); return HEXCONSTANTTOKEN; }     		        
{BINARYCONSTANT}  			    { constBuffer = (char *) safeCalloc(yyleng-1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng-2);
					      yylval->value = constBuffer;
                                              newTokenLexed(); return BINARYCONSTANTTOKEN; }  	  	      
					    											       
{PI}              			    { newTokenLexed(); return PITOKEN; }              					       
					    											       
{STRING}          			    { 
					      constBuffer = (char *) safeCalloc(yyleng-1,sizeof(char));
					      constBuffer2 = (char *) safeCalloc(yyleng-1,sizeof(char));
					      strncpy(constBuffer2,yytext+1,yyleng-2);
					      demaskString(constBuffer,constBuffer2);						
					      free(constBuffer2);
					      yylval->value = constBuffer;
                                              newTokenLexed(); return STRINGTOKEN; }          					       
					    											       
{LPAR}            			    { newTokenLexed(); return LPARTOKEN; }            					       
{RPAR}            			    { newTokenLexed(); return RPARTOKEN; }            					       
{LBRACKET}        			    { newTokenLexed(); return LBRACKETTOKEN; }        					       
{RBRACKET}        			    { newTokenLexed(); return RBRACKETTOKEN; }        					   
{EXCLAMATIONEQUAL}			    { newTokenLexed(); return EXCLAMATIONEQUALTOKEN; }        				    
{COMPAREEQUAL}                              { newTokenLexed(); return COMPAREEQUALTOKEN; }        			           
{EQUAL}           			    { newTokenLexed(); return EQUALTOKEN; }           					       
{COMMA}           			    { newTokenLexed(); return COMMATOKEN; }           					       
{EXCLAMATION}				    { newTokenLexed(); return EXCLAMATIONTOKEN; }				    	       
{SEMICOLON}       			    { newTokenLexed(); return SEMICOLONTOKEN; }       					       
{LEFTANGLE}       			    { newTokenLexed(); return LEFTANGLETOKEN; }       					       
{STARLEFTANGLE}   			    { newTokenLexed(); return STARLEFTANGLETOKEN; }       				        
{RIGHTANGLEUNDERSCORE}			    { newTokenLexed(); return RIGHTANGLEUNDERSCORETOKEN; }			    	       
{RIGHTANGLEDOT} 			    { newTokenLexed(); return RIGHTANGLEDOTTOKEN; } 					 
{RIGHTANGLESTAR}			    { newTokenLexed(); return RIGHTANGLESTARTOKEN; } 					       
{RIGHTANGLE}      			    { newTokenLexed(); return RIGHTANGLETOKEN; }      					       
{DOTS}            			    { newTokenLexed(); return DOTSTOKEN; }            					       
{QUESTIONMARK}				    { newTokenLexed(); return QUESTIONMARKTOKEN; }				      	       
{AND}         				    { newTokenLexed(); return ANDTOKEN; }				      	       
{OR}         				    { newTokenLexed(); return ORTOKEN; }				      	       
{VERTBAR}				    { newTokenLexed(); return VERTBARTOKEN; }						       
{AT}					    { newTokenLexed(); return ATTOKEN; }					      	       
{DOUBLECOLON}				    { newTokenLexed(); return DOUBLECOLONTOKEN; }				      	       


{PLUS}            			    { newTokenLexed(); return PLUSTOKEN; }            					       
{MINUS}           			    { newTokenLexed(); return MINUSTOKEN; }           					       
{MUL}          				    { newTokenLexed(); return MULTOKEN; }          				      	       
{DIV}            			    { newTokenLexed(); return DIVTOKEN; }            					       
{POW}            			    { newTokenLexed(); return POWTOKEN; }            					       
					    											       
{SQRT}            			    { newTokenLexed(); return SQRTTOKEN; }            					       
{EXP}             			    { newTokenLexed(); return EXPTOKEN; }             					       
{LOG}             			    { newTokenLexed(); return LOGTOKEN; }             					       
{LOG2}            			    { newTokenLexed(); return LOG2TOKEN; }            					       
{LOG10}           			    { newTokenLexed(); return LOG10TOKEN; }           					       
{SIN}             			    { newTokenLexed(); return SINTOKEN; }             					       
{COS}             			    { newTokenLexed(); return COSTOKEN; }             					       
{TAN}             			    { newTokenLexed(); return TANTOKEN; }             					       
{ASIN}            			    { newTokenLexed(); return ASINTOKEN; }            					       
{ACOS}            			    { newTokenLexed(); return ACOSTOKEN; }            					       
{ATAN}            			    { newTokenLexed(); return ATANTOKEN; }            					       
{SINH}            			    { newTokenLexed(); return SINHTOKEN; }            					       
{COSH}            			    { newTokenLexed(); return COSHTOKEN; }            					       
{TANH}            			    { newTokenLexed(); return TANHTOKEN; }            					       
{ASINH}           			    { newTokenLexed(); return ASINHTOKEN; }           					       
{ACOSH}           			    { newTokenLexed(); return ACOSHTOKEN; }           					       
{ATANH}           			    { newTokenLexed(); return ATANHTOKEN; }           					       
{ABS}             			    { newTokenLexed(); return ABSTOKEN; }             					       
{ERF}             			    { newTokenLexed(); return ERFTOKEN; }             					       
{ERFC}            			    { newTokenLexed(); return ERFCTOKEN; }            					       
{LOG1P}           			    { newTokenLexed(); return LOG1PTOKEN; }           					       
{EXPM1}           			    { newTokenLexed(); return EXPM1TOKEN; }           					       
{DOUBLE}          			    { newTokenLexed(); return DOUBLETOKEN; }          					       
{DOUBLEDOUBLE}				    { newTokenLexed(); return DOUBLEDOUBLETOKEN; }				      	       
{TRIPLEDOUBLE}    			    { newTokenLexed(); return TRIPLEDOUBLETOKEN; }    					       
{DOUBLEEXTENDED}  			    { newTokenLexed(); return DOUBLEEXTENDEDTOKEN; }  					       
{CEIL}            			    { newTokenLexed(); return CEILTOKEN; }            					       
{FLOOR}           			    { newTokenLexed(); return FLOORTOKEN; }           					       
					    											       
{PREC}            			    { newTokenLexed(); return PRECTOKEN; }            					       
{POINTS}          			    { newTokenLexed(); return POINTSTOKEN; }          					       
{DIAM}            			    { newTokenLexed(); return DIAMTOKEN; }            					       
{DISPLAY}          			    { newTokenLexed(); return DISPLAYTOKEN; }          					       
{VERBOSITY}       			    { newTokenLexed(); return VERBOSITYTOKEN; }       					       
{CANONICAL}       			    { newTokenLexed(); return CANONICALTOKEN; }       					       
{AUTOSIMPLIFY}    			    { newTokenLexed(); return AUTOSIMPLIFYTOKEN; }    					       
{TAYLORRECURSIONS}			    { newTokenLexed(); return TAYLORRECURSIONSTOKEN; }					       
{TIMING}          			    { newTokenLexed(); return TIMINGTOKEN; }          					       
{FULLPARENTHESES} 			    { newTokenLexed(); return FULLPARENTHESESTOKEN; } 					       
{MIDPOINTMODE}    			    { newTokenLexed(); return MIDPOINTMODETOKEN; }    					       
{HOPITALRECURSIONS}			    { newTokenLexed(); return HOPITALRECURSIONSTOKEN; }					       
					    											       
{ON}              			    { newTokenLexed(); return ONTOKEN; }              					       
{OFF}             			    { newTokenLexed(); return OFFTOKEN; }             					       
{DYADIC}				    { newTokenLexed(); return DYADICTOKEN; }						       
{POWERS}          			    { newTokenLexed(); return POWERSTOKEN; }          					       
{BINARY}          			    { newTokenLexed(); return BINARYTOKEN; }          					       
{FILE}            			    { newTokenLexed(); return FILETOKEN; }            					       
{POSTSCRIPT}      			    { newTokenLexed(); return POSTSCRIPTTOKEN; }      					       
{POSTSCRIPTFILE}  			    { newTokenLexed(); return POSTSCRIPTFILETOKEN; }  					       
{PERTURB}         			    { newTokenLexed(); return PERTURBTOKEN; }         					       
{MINUSWORD}       			    { newTokenLexed(); return MINUSWORDTOKEN; }       					       
{PLUSWORD}        			    { newTokenLexed(); return PLUSWORDTOKEN; }        					       
{ZEROWORD}        			    { newTokenLexed(); return ZEROWORDTOKEN; }        					       
{NEAREST}         			    { newTokenLexed(); return NEARESTTOKEN; }         					       
{HONORCOEFFPREC} 			    { newTokenLexed(); return HONORCOEFFPRECTOKEN; } 					       
{TRUE}					    { newTokenLexed(); return TRUETOKEN; }					     	       
{FALSE}					    { newTokenLexed(); return FALSETOKEN; }					      	       
{DEFAULT}				    { newTokenLexed(); return DEFAULTTOKEN; }				 
{HEAD}   				    { newTokenLexed(); return HEADTOKEN; }				 
{TAIL}   				    { newTokenLexed(); return TAILTOKEN; }				 
{INF}   				    { newTokenLexed(); return INFTOKEN; }				 
{MID}   				    { newTokenLexed(); return MIDTOKEN; }				 
{SUP}   				    { newTokenLexed(); return SUPTOKEN; }				 
{LENGTH}   				    { newTokenLexed(); return LENGTHTOKEN; }				 
{ABSOLUTE}   				    { newTokenLexed(); return ABSOLUTETOKEN; }				 
{RELATIVE}   				    { newTokenLexed(); return RELATIVETOKEN; }				 
{DECIMAL}   				    { newTokenLexed(); return DECIMALTOKEN; }				 
{ERROR}   				    { newTokenLexed(); return ERRORTOKEN; }				 	       

{QUIT}            			    {     
                                              newTokenLexed(); 
                                              if (readStack != NULL) {
			                        return FALSEQUITTOKEN;
                                              }
                                              return QUITTOKEN;         
                                            }
{RESTART}         			    { newTokenLexed(); return RESTARTTOKEN; }         					       
					    											       
{LIBRARY}         			    { newTokenLexed(); return LIBRARYTOKEN; }         					       
					    											       
{DIFF}            			    { newTokenLexed(); return DIFFTOKEN; }            					       
{SIMPLIFY}				    { newTokenLexed(); return SIMPLIFYTOKEN; }						       
{REMEZ}           			    { newTokenLexed(); return REMEZTOKEN; }           					       
{HORNER}          			    { newTokenLexed(); return HORNERTOKEN; }          					       
{EXPAND}          			    { newTokenLexed(); return EXPANDTOKEN; }          					       
{SIMPLIFYSAFE}				    { newTokenLexed(); return SIMPLIFYSAFETOKEN; }				      	       
{TAYLOR}         			    { newTokenLexed(); return TAYLORTOKEN; }         					       
{DEGREE}          			    { newTokenLexed(); return DEGREETOKEN; }          					       
{NUMERATOR}       			    { newTokenLexed(); return NUMERATORTOKEN; }       					       
{DENOMINATOR}     			    { newTokenLexed(); return DENOMINATORTOKEN; }     					       
{SUBSTITUTE}      			    { newTokenLexed(); return SUBSTITUTETOKEN; }      					       
{COEFF}           			    { newTokenLexed(); return COEFFTOKEN; }           					       
{SUBPOLY}         			    { newTokenLexed(); return SUBPOLYTOKEN; }         					       
{ROUNDCOEFFICIENTS} 			    { newTokenLexed(); return ROUNDCOEFFICIENTSTOKEN; } 			      	       
{RATIONALAPPROX}  			    { newTokenLexed(); return RATIONALAPPROXTOKEN; }  					       
{ACCURATEINFNORM}  			    { newTokenLexed(); return ACCURATEINFNORMTOKEN; }  					       
{ROUNDTOFORMAT}   			    { newTokenLexed(); return ROUNDTOFORMATTOKEN; }   					       
{EVALUATE}        			    { newTokenLexed(); return EVALUATETOKEN; }        					       
					    											       
{PARSE}           			    { newTokenLexed(); return PARSETOKEN; }           					       
					    											       
{PRINT}           			    { newTokenLexed(); return PRINTTOKEN; }           					       
{PRINTXML}           			    { newTokenLexed(); return PRINTXMLTOKEN; }           					       
{PLOT}            			    { newTokenLexed(); return PLOTTOKEN; }            					       
{PRINTHEXA}       			    { newTokenLexed(); return PRINTHEXATOKEN; }       					       
{PRINTBINARY}     			    { newTokenLexed(); return PRINTBINARYTOKEN; }     					       
{PRINTEXPANSION}  			    { newTokenLexed(); return PRINTEXPANSIONTOKEN; }  					       
{BASHEXECUTE}     			    { newTokenLexed(); return BASHEXECUTETOKEN; }     					       
{EXTERNALPLOT}    			    { newTokenLexed(); return EXTERNALPLOTTOKEN; }    					       
{WRITE}           			    { newTokenLexed(); return WRITETOKEN; }           					       
{ASCIIPLOT}       			    { newTokenLexed(); return ASCIIPLOTTOKEN; }       					       
{RENAME}         			    { newTokenLexed(); return RENAMETOKEN; }       				

					    											       
{INFNORM}         			    { newTokenLexed(); return INFNORMTOKEN; }         					       
{FINDZEROS}       			    { newTokenLexed(); return FINDZEROSTOKEN; }       					       
{FPFINDZEROS}     			    { newTokenLexed(); return FPFINDZEROSTOKEN; }     					       
{DIRTYINFNORM}    			    { newTokenLexed(); return DIRTYINFNORMTOKEN; }    					       
{INTEGRAL}        			    { newTokenLexed(); return INTEGRALTOKEN; }        					       
{DIRTYINTEGRAL}				    { newTokenLexed(); return DIRTYINTEGRALTOKEN; }				      	       
{WORSTCASE}       			    { newTokenLexed(); return WORSTCASETOKEN; }       					       
{IMPLEMENTPOLY}				    { newTokenLexed(); return IMPLEMENTPOLYTOKEN; }				      	       
{CHECKINFNORM}    			    { newTokenLexed(); return CHECKINFNORMTOKEN; }    					       
{ZERODENOMINATORS}			    { newTokenLexed(); return ZERODENOMINATORSTOKEN; }					       
{ISEVALUABLE}     			    { newTokenLexed(); return ISEVALUABLETOKEN; }     					       
{SEARCHGAL}       			    { newTokenLexed(); return SEARCHGALTOKEN; }       					       
{GUESSDEGREE}     			    { newTokenLexed(); return GUESSDEGREETOKEN; }     					       
{DIRTYFINDZEROS}  			    { newTokenLexed(); return DIRTYFINDZEROSTOKEN; }  					       
					    											       
{IF}					    { newTokenLexed(); return IFTOKEN; }					      	       
{THEN}					    { newTokenLexed(); return THENTOKEN; }					      	       
{ELSE}					    { newTokenLexed(); return ELSETOKEN; }					      	       
{FOR}					    { newTokenLexed(); return FORTOKEN; }					      	       
{IN}					    { newTokenLexed(); return INTOKEN; }					      	       
{FROM}					    { newTokenLexed(); return FROMTOKEN; }					      	       
{TO}					    { newTokenLexed(); return TOTOKEN; }					     	       
{BY}					    { newTokenLexed(); return BYTOKEN; }					      	       
{DO}					    { newTokenLexed(); return DOTOKEN; }					      	       
{BEGIN}					    { newTokenLexed(); return BEGINTOKEN; }					      	       
{END}					    { newTokenLexed(); return ENDTOKEN; }					      	       
{WHILEDEF}				    { newTokenLexed(); return WHILETOKEN; }					      	       
					    										             
{HELP}            			    { newTokenLexed(); return HELPTOKEN; }                                                       


[ \t]		{ /* Eat up spaces and tabulators */
		}

[\n]		{ 
                     carriageReturnLexed();
		}

{IDENTIFIER}        			    { constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
					      newTokenLexed(); return IDENTIFIERTOKEN; }        			        

.		{ /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

%%


