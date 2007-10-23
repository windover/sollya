%{

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "internparser.h"
#include "general.h"
#include "chain.h"

#define YY_NO_UNPUT 1

%}

%option noyywrap
%option always-interactive
%option prefix="internyy"
%option reentrant
%option bison-bridge
%option nounput

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
DOTCOLON        ".:"
COLONDOT        ":."

	       	
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

ONELINECOMMENT  ("//")([^\n])*"\n"

WRITE           "write"

ASCIIPLOT       "asciiplot"


ROUNDTOFORMAT   "round"
MINUSWORD       "RD"
PLUSWORD        "RU"
ZEROWORD        "RZ"
NEAREST         "RN"


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

READXML         "readxml"

MANTISSA        "mantissa"
EXPONENT        "exponent"
PRECISION       "precision"

REVERT          "revert"
SORT            "sort"

READFILE        "readfile"

ROUNDCORRECTLY  "roundcorrectly"

EXECUTE         "execute"

ISBOUND         "isbound"

%%

%{

%}




{COMMENTSTART}  {     BEGIN(commentstate); }

<commentstate>{COMMENTEND} { BEGIN(INITIAL); }

<commentstate>. { // Eat up comments 

                 }

<commentstate>[\n] { // Eat up newlines in comments

		}



{ONELINECOMMENT} {  // Eat up comments

                 }

<<EOF>>         {
                      yyterminate();
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
                                               return CONSTANTTOKEN; }        		       
{DYADICCONSTANT} 			    { 
                                              constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
                                               return DYADICCONSTANTTOKEN; } 	              
{HEXCONSTANT}     			    { constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
                                               return HEXCONSTANTTOKEN; }     		        
{BINARYCONSTANT}  			    { constBuffer = (char *) safeCalloc(yyleng-1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng-2);
					      yylval->value = constBuffer;
                                               return BINARYCONSTANTTOKEN; }  	  	      
					    											       
{PI}              			    {  return PITOKEN; }              					       
					    											       
{STRING}          			    { 
					      constBuffer = (char *) safeCalloc(yyleng-1,sizeof(char));
					      constBuffer2 = (char *) safeCalloc(yyleng-1,sizeof(char));
					      strncpy(constBuffer2,yytext+1,yyleng-2);
					      demaskString(constBuffer,constBuffer2);						
					      free(constBuffer2);
					      yylval->value = constBuffer;
                                               return STRINGTOKEN; }          					       
					    											       
{LPAR}            			    {  return LPARTOKEN; }            					       
{RPAR}            			    {  return RPARTOKEN; }            					       
{LBRACKET}        			    {  return LBRACKETTOKEN; }        					       
{RBRACKET}        			    {  return RBRACKETTOKEN; }        					   
{EXCLAMATIONEQUAL}			    {  return EXCLAMATIONEQUALTOKEN; }        				    
{COMPAREEQUAL}                              {  return COMPAREEQUALTOKEN; }        			           
{EQUAL}           			    {  return EQUALTOKEN; }           					       
{COMMA}           			    {  return COMMATOKEN; }           					       
{EXCLAMATION}				    {  return EXCLAMATIONTOKEN; }				    	       
{SEMICOLON}       			    {  return SEMICOLONTOKEN; }       					       
{LEFTANGLE}       			    {  return LEFTANGLETOKEN; }       					       
{STARLEFTANGLE}   			    {  return STARLEFTANGLETOKEN; }       				        
{RIGHTANGLEUNDERSCORE}			    {  return RIGHTANGLEUNDERSCORETOKEN; }			    	       
{RIGHTANGLEDOT} 			    {  return RIGHTANGLEDOTTOKEN; } 					 
{RIGHTANGLESTAR}			    {  return RIGHTANGLESTARTOKEN; } 					       
{RIGHTANGLE}      			    {  return RIGHTANGLETOKEN; }      					       
{DOTS}            			    {  return DOTSTOKEN; }            					       
{QUESTIONMARK}				    {  return QUESTIONMARKTOKEN; }				      	       
{AND}         				    {  return ANDTOKEN; }				      	       
{OR}         				    {  return ORTOKEN; }				      	       
{VERTBAR}				    {  return VERTBARTOKEN; }						       
{AT}					    {  return ATTOKEN; }					      	       
{DOUBLECOLON}				    {  return DOUBLECOLONTOKEN; }				      	       
{DOTCOLON}				    {  return DOTCOLONTOKEN; }				      	       
{COLONDOT}				    {  return COLONDOTTOKEN; }				      	       


{PLUS}            			    {  return PLUSTOKEN; }            					       
{MINUS}           			    {  return MINUSTOKEN; }           					       
{MUL}          				    {  return MULTOKEN; }          				      	       
{DIV}            			    {  return DIVTOKEN; }            					       
{POW}            			    {  return POWTOKEN; }            					       
					    											       
{SQRT}            			    {  return SQRTTOKEN; }            					       
{EXP}             			    {  return EXPTOKEN; }             					       
{LOG}             			    {  return LOGTOKEN; }             					       
{LOG2}            			    {  return LOG2TOKEN; }            					       
{LOG10}           			    {  return LOG10TOKEN; }           					       
{SIN}             			    {  return SINTOKEN; }             					       
{COS}             			    {  return COSTOKEN; }             					       
{TAN}             			    {  return TANTOKEN; }             					       
{ASIN}            			    {  return ASINTOKEN; }            					       
{ACOS}            			    {  return ACOSTOKEN; }            					       
{ATAN}            			    {  return ATANTOKEN; }            					       
{SINH}            			    {  return SINHTOKEN; }            					       
{COSH}            			    {  return COSHTOKEN; }            					       
{TANH}            			    {  return TANHTOKEN; }            					       
{ASINH}           			    {  return ASINHTOKEN; }           					       
{ACOSH}           			    {  return ACOSHTOKEN; }           					       
{ATANH}           			    {  return ATANHTOKEN; }           					       
{ABS}             			    {  return ABSTOKEN; }             					       
{ERF}             			    {  return ERFTOKEN; }             					       
{ERFC}            			    {  return ERFCTOKEN; }            					       
{LOG1P}           			    {  return LOG1PTOKEN; }           					       
{EXPM1}           			    {  return EXPM1TOKEN; }           					       
{DOUBLE}          			    {  return DOUBLETOKEN; }          					       
{DOUBLEDOUBLE}				    {  return DOUBLEDOUBLETOKEN; }				      	       
{TRIPLEDOUBLE}    			    {  return TRIPLEDOUBLETOKEN; }    					       
{DOUBLEEXTENDED}  			    {  return DOUBLEEXTENDEDTOKEN; }  					       
{CEIL}            			    {  return CEILTOKEN; }            					       
{FLOOR}           			    {  return FLOORTOKEN; }           					       
					    											       
{PREC}            			    {  return PRECTOKEN; }            					       
{POINTS}          			    {  return POINTSTOKEN; }          					       
{DIAM}            			    {  return DIAMTOKEN; }            					       
{DISPLAY}          			    {  return DISPLAYTOKEN; }          					       
{VERBOSITY}       			    {  return VERBOSITYTOKEN; }       					       
{CANONICAL}       			    {  return CANONICALTOKEN; }       					       
{AUTOSIMPLIFY}    			    {  return AUTOSIMPLIFYTOKEN; }    					       
{TAYLORRECURSIONS}			    {  return TAYLORRECURSIONSTOKEN; }					       
{TIMING}          			    {  return TIMINGTOKEN; }          					       
{FULLPARENTHESES} 			    {  return FULLPARENTHESESTOKEN; } 					       
{MIDPOINTMODE}    			    {  return MIDPOINTMODETOKEN; }    					       
{HOPITALRECURSIONS}			    {  return HOPITALRECURSIONSTOKEN; }					       
					    											       
{ON}              			    {  return ONTOKEN; }              					       
{OFF}             			    {  return OFFTOKEN; }             					       
{DYADIC}				    {  return DYADICTOKEN; }						       
{POWERS}          			    {  return POWERSTOKEN; }          					       
{BINARY}          			    {  return BINARYTOKEN; }          					       
{FILE}            			    {  return FILETOKEN; }            					       
{POSTSCRIPT}      			    {  return POSTSCRIPTTOKEN; }      					       
{POSTSCRIPTFILE}  			    {  return POSTSCRIPTFILETOKEN; }  					       
{PERTURB}         			    {  return PERTURBTOKEN; }         					       
{MINUSWORD}       			    {  return MINUSWORDTOKEN; }       					       
{PLUSWORD}        			    {  return PLUSWORDTOKEN; }        					       
{ZEROWORD}        			    {  return ZEROWORDTOKEN; }        					       
{NEAREST}         			    {  return NEARESTTOKEN; }         					       
{HONORCOEFFPREC} 			    {  return HONORCOEFFPRECTOKEN; } 					       
{TRUE}					    {  return TRUETOKEN; }					     	       
{FALSE}					    {  return FALSETOKEN; }					      	       
{DEFAULT}				    {  return DEFAULTTOKEN; }				 
{HEAD}   				    {  return HEADTOKEN; }				 
{ROUNDCORRECTLY}   		       	    {  return ROUNDCORRECTLYTOKEN; }				 
{REVERT}   				    {  return REVERTTOKEN; }				 
{SORT}   				    {  return SORTTOKEN; }				 
{MANTISSA}   				    {  return MANTISSATOKEN; }				 
{EXPONENT}   				    {  return EXPONENTTOKEN; }				 
{PRECISION}   				    {  return PRECISIONTOKEN; }				 
{TAIL}   				    {  return TAILTOKEN; }				 
{INF}   				    {  return INFTOKEN; }				 
{MID}   				    {  return MIDTOKEN; }				 
{SUP}   				    {  return SUPTOKEN; }				 
{READXML}   				    {  return READXMLTOKEN; }				 
{LENGTH}   				    {  return LENGTHTOKEN; }				 
{ABSOLUTE}   				    {  return ABSOLUTETOKEN; }				 
{RELATIVE}   				    {  return RELATIVETOKEN; }				 
{DECIMAL}   				    {  return DECIMALTOKEN; }				 
{ERROR}   				    {  return ERRORTOKEN; }				 	 
{READFILE}   				    {  return READFILETOKEN; }				 	       		  
{ISBOUND}   				    {  return ISBOUNDTOKEN; }				 	       

{QUIT}             			    {     
			                        return FALSEQUITTOKEN;
                                            }
{RESTART}         			    { return FALSERESTARTTOKEN; }         					       

{LIBRARY}         			    {  return LIBRARYTOKEN; }         					       
					    											       
{DIFF}            			    {  return DIFFTOKEN; }            					       
{SIMPLIFY}				    {  return SIMPLIFYTOKEN; }						       
{REMEZ}           			    {  return REMEZTOKEN; }           					       
{HORNER}          			    {  return HORNERTOKEN; }          					       
{EXPAND}          			    {  return EXPANDTOKEN; }          					       
{SIMPLIFYSAFE}				    {  return SIMPLIFYSAFETOKEN; }				      	       
{TAYLOR}         			    {  return TAYLORTOKEN; }         					       
{DEGREE}          			    {  return DEGREETOKEN; }          					       
{NUMERATOR}       			    {  return NUMERATORTOKEN; }       					       
{DENOMINATOR}     			    {  return DENOMINATORTOKEN; }     					       
{SUBSTITUTE}      			    {  return SUBSTITUTETOKEN; }      					       
{COEFF}           			    {  return COEFFTOKEN; }           					       
{SUBPOLY}         			    {  return SUBPOLYTOKEN; }         					       
{ROUNDCOEFFICIENTS} 			    {  return ROUNDCOEFFICIENTSTOKEN; } 			      	       
{RATIONALAPPROX}  			    {  return RATIONALAPPROXTOKEN; }  					       
{ACCURATEINFNORM}  			    {  return ACCURATEINFNORMTOKEN; }  					       
{ROUNDTOFORMAT}   			    {  return ROUNDTOFORMATTOKEN; }   					       
{EVALUATE}        			    {  return EVALUATETOKEN; }        					       
					    											       
{PARSE}           			    {  return PARSETOKEN; }           					       
					    											       
{PRINT}           			    {  return PRINTTOKEN; }           					       
{PRINTXML}           			    {  return PRINTXMLTOKEN; }           					       
{EXECUTE}           			    {  return EXECUTETOKEN; }           					       
{PLOT}            			    {  return PLOTTOKEN; }            					       
{PRINTHEXA}       			    {  return PRINTHEXATOKEN; }       					       
{PRINTBINARY}     			    {  return PRINTBINARYTOKEN; }     					       
{PRINTEXPANSION}  			    {  return PRINTEXPANSIONTOKEN; }  					       
{BASHEXECUTE}     			    {  return BASHEXECUTETOKEN; }     					       
{EXTERNALPLOT}    			    {  return EXTERNALPLOTTOKEN; }    					       
{WRITE}           			    {  return WRITETOKEN; }           					       
{ASCIIPLOT}       			    {  return ASCIIPLOTTOKEN; }       					       
{RENAME}         			    {  return RENAMETOKEN; }       				

					    											       
{INFNORM}         			    {  return INFNORMTOKEN; }         					       
{FINDZEROS}       			    {  return FINDZEROSTOKEN; }       					       
{FPFINDZEROS}     			    {  return FPFINDZEROSTOKEN; }     					       
{DIRTYINFNORM}    			    {  return DIRTYINFNORMTOKEN; }    					       
{INTEGRAL}        			    {  return INTEGRALTOKEN; }        					       
{DIRTYINTEGRAL}				    {  return DIRTYINTEGRALTOKEN; }				      	       
{WORSTCASE}       			    {  return WORSTCASETOKEN; }       					       
{IMPLEMENTPOLY}				    {  return IMPLEMENTPOLYTOKEN; }				      	       
{CHECKINFNORM}    			    {  return CHECKINFNORMTOKEN; }    					       
{ZERODENOMINATORS}			    {  return ZERODENOMINATORSTOKEN; }					       
{ISEVALUABLE}     			    {  return ISEVALUABLETOKEN; }     					       
{SEARCHGAL}       			    {  return SEARCHGALTOKEN; }       					       
{GUESSDEGREE}     			    {  return GUESSDEGREETOKEN; }     					       
{DIRTYFINDZEROS}  			    {  return DIRTYFINDZEROSTOKEN; }  					       
					    											       
{IF}					    {  return IFTOKEN; }					      	       
{THEN}					    {  return THENTOKEN; }					      	       
{ELSE}					    {  return ELSETOKEN; }					      	       
{FOR}					    {  return FORTOKEN; }					      	       
{IN}					    {  return INTOKEN; }					      	       
{FROM}					    {  return FROMTOKEN; }					      	       
{TO}					    {  return TOTOKEN; }					     	       
{BY}					    {  return BYTOKEN; }					      	       
{DO}					    {  return DOTOKEN; }					      	       
{BEGIN}					    {  return BEGINTOKEN; }					      	       
{END}					    {  return ENDTOKEN; }					      	       
{WHILEDEF}				    {  return WHILETOKEN; }					      	       
					    										             


[ \t]		{ /* Eat up spaces and tabulators */
		}

[\n]		{ 

		}

{IDENTIFIER}        			    { constBuffer = (char *) safeCalloc(yyleng+1,sizeof(char));
					      strncpy(constBuffer,yytext,yyleng);
					      yylval->value = constBuffer;
					       return IDENTIFIERTOKEN; }        			        

.		{ /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

%%

