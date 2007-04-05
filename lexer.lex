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

CONSTANT        ({NUMBER}+|({NUMBER}*"."{NUMBER}+))(((((" ")*)[eE]([+-])?{NUMBER}+)?))
DYADICCONSTANT  ({NUMBER}+)([bB])([+-]?)({NUMBER}+)
HEXCONSTANT     ("0x"){HEXNUMBER}{16}

BINARYCONSTANT  (([0-1])+|(([0-1])*"."([0-1])+))"_2"


VARIABLE        {CHAR}({CHAR}|{NUMBER})*

LPAR            "("
RPAR            ")"

LBRACKET        "["
RBRACKET        "]"

IN              "in"
	       	
PI              ("pi")|("Pi")
E               "e"
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

	       	
COLON           ":"
EQUAL           "="
COMMA           ","
PREC            "prec"
POINTS          "points"
EXCLAMATION     "!"
	       	
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
AT              "at"

NUMERATOR       "numerator"
DENOMINATOR     "denominator"

WITHOUT         "without"

DYADIC          "dyadic"
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

PROOF           "proof"

VERBOSITY       "verbosity"

WORSTCASE       "worstcase"
WITH            "with"
INPUTPREC       "inputprec"
OUTPUTPREC      "outputprec"
INPUTEXPO       "inputexpo"
EPSILON         "epsilon"
OUTPUT          "output"

LEFTANGLE       "<"
RIGHTANGLEUNDERSCORE ">_"
RIGHTANGLEDOT ">."
RIGHTANGLE      ">"

SUBSTITUTE      "substitute"

FPMINIMAX       "fpminimax"
MI              "mi"
TI              "ti"
ABSOLUTE        "absolute"
RELATIVE        "relative"
WEIGHT          "weight"
EQUI            "equi"
CHEB            "cheb"


DOTS            "..."

IMPLEMENTPOLY   "implementpoly"
NAME            "name"
VARIABLEMETA    "variable"
AS              "as"

CHECKINFNORM    "checkinfnorm"
BOUNDED         "bounded"
BY              "by"

TAYLORRECURSIONS "taylorrecursions"

PRINTHEXA       "printhexa"
PRINTBINARY     "printbinary"

ROUNDCOEFFICIENTS "roundcoefficients"

HONORCOEFFPREC  "honorcoeffprec"

RESTART         "restart"

TESTPARI        "testpari"

ZERODENOMINATORS "zerodenominators"
ISEVALUABLE     "isevaluable"

EVALUATEACCURATE "evaluateaccurate"

ACCURATEINFNORM  "accurateinfnorm"

BITS            "bits"

FILE            "file"
POSTSCRIPT      "postscript"
POSTSCRIPTFILE  "postscriptfile"

PRINTEXPANSION  "printexpansion"

BASHEXECUTE     "bashexecute"
EXTERNALPLOT    "externalplot"
PERTURB         "perturb"
TO              "to"

COEFF           "coeff"
SUBPOLY         "subpoly"

QUESTIONMARK    "?"

SEARCHGAL       "searchgal"

STEPS           "steps"

RATIONALAPPROX  "rationalapprox"

READ            "read"

COMMENTSTART    "/*"
COMMENTEND      "*/"

ONELINECOMMENT  ("//"|"#")([^\n])*"\n"

WRITE           "write"

ASCIIPLOT       "asciiplot"

DOLLAR           "$"

ROUNDTOFORMAT   "round"
MINUSWORD       "M"
PLUSWORD        "P"
ZEROWORD        "Z"
NEAREST         "N"

FINISH          "&"

GUESSDEGREE     "guessdegree"

PARSE           "parse"

AUTOSIMPLIFY    "autosimplify"

TIMING          "timing"

%%

%{
  YY_BUFFER_STATE *currStatePtr;
%}


{COMMENTSTART}  {     BEGIN(commentstate); }

<commentstate>{COMMENTEND} { printPrompt(); BEGIN(INITIAL); }

<commentstate>. { // Eat up comments 
                 }

<commentstate>[\n] { // Eat up newlines in comments
		}



{ONELINECOMMENT} {  // Eat up comments
                      printPrompt();
                 }

{DOTS}          {     promptToBePrinted = 0; return DOTSTOKEN;              }     

{BINARYCONSTANT} {
                      if (constBuffer != NULL) free(constBuffer);
		      constBuffer = (char *) safeCalloc(strlen(yytext)-1,sizeof(char));
		      strncpy(constBuffer,yytext,strlen(yytext)-2);
                      yylval->value = constBuffer;
                      promptToBePrinted = 0; return BINARYCONSTTOKEN;
                 }


{CONSTANT}      {     
                      if (constBuffer != NULL) free(constBuffer);
		      constBuffer = (char *) safeCalloc(strlen(yytext)+1,sizeof(char));
		      if (removeSpaces(constBuffer,yytext)) {
			printMessage(2,"Information: removed spaces in scientific notation constant \"%s\", it will be considered as \"%s\"\n",yytext,constBuffer);
		      }
                      yylval->value = constBuffer;
                      promptToBePrinted = 0; return CONSTTOKEN;
                }
{DYADICCONSTANT} {     
                      yylval->value = yytext;
                      promptToBePrinted = 0; return DYADICCONSTTOKEN;
                }
{HEXCONSTANT}   {     
                      yylval->value = yytext;
                      promptToBePrinted = 0; return HEXCONSTTOKEN;
                }
{IN}            {     promptToBePrinted = 0; return INTOKEN; }
{LBRACKET}      {     promptToBePrinted = 0; return LBRACKETTOKEN; }
{RBRACKET}      {     promptToBePrinted = 0; return RBRACKETTOKEN; }

{PI}            {     promptToBePrinted = 0; return PITOKEN;    }             
{E}             {     promptToBePrinted = 0; return ETOKEN;     }              
{LPAR}          {     promptToBePrinted = 0; return LPARTOKEN     ;    }           
{RPAR}          {     promptToBePrinted = 0; return RPARTOKEN     ;    }           
{PLUS}          {     promptToBePrinted = 0; return PLUSTOKEN     ;    }           
{MINUS}         {     promptToBePrinted = 0; return MINUSTOKEN    ;    }          
{MUL}           {     promptToBePrinted = 0; return MULTOKEN      ;    }            
{DIV}           {     promptToBePrinted = 0; return DIVTOKEN      ;    }            
{POW}           {     promptToBePrinted = 0; return POWTOKEN      ;    }            
{SQRT}          {     promptToBePrinted = 0; return SQRTTOKEN     ;    }           
{EXP}           {     promptToBePrinted = 0; return EXPTOKEN      ;    }            
{LOG}           {     promptToBePrinted = 0; return LOGTOKEN      ;    }            
{LOG2}          {     promptToBePrinted = 0; return LOG2TOKEN     ;    }           
{LOG10}         {     promptToBePrinted = 0; return LOG10TOKEN    ;    }          
{SIN}           {     promptToBePrinted = 0; return SINTOKEN      ;    }            
{COS}           {     promptToBePrinted = 0; return COSTOKEN      ;    }            
{TAN}           {     promptToBePrinted = 0; return TANTOKEN      ;    }            
{ASIN}          {     promptToBePrinted = 0; return ASINTOKEN     ;    }           
{ACOS}          {     promptToBePrinted = 0; return ACOSTOKEN     ;    }           
{ATAN}          {     promptToBePrinted = 0; return ATANTOKEN     ;    }           
{SINH}          {     promptToBePrinted = 0; return SINHTOKEN     ;    }           
{COSH}          {     promptToBePrinted = 0; return COSHTOKEN     ;    }           
{TANH}          {     promptToBePrinted = 0; return TANHTOKEN     ;    }           
{ASINH}         {     promptToBePrinted = 0; return ASINHTOKEN    ;    }          
{ACOSH}         {     promptToBePrinted = 0; return ACOSHTOKEN    ;    }          
{ATANH}         {     promptToBePrinted = 0; return ATANHTOKEN    ;    }          
{ABS}           {     promptToBePrinted = 0; return ABSTOKEN      ;    }            
{ERF}           {     promptToBePrinted = 0; return ERFTOKEN      ;    }            
{ERFC}          {     promptToBePrinted = 0; return ERFCTOKEN     ;    }            
{LOG1P}         {     promptToBePrinted = 0; return LOG1PTOKEN    ;    }            
{EXPM1}         {     promptToBePrinted = 0; return EXPM1TOKEN    ;    }            
{COLON}         {     promptToBePrinted = 0; return COLONTOKEN    ;    }          
{EQUAL}         {     promptToBePrinted = 0; return EQUALTOKEN    ;    }          
{COMMA}         {     promptToBePrinted = 0; return COMMATOKEN    ;    }          
{PREC}          {     promptToBePrinted = 0; return PRECTOKEN     ;    }           
{POINTS}        {     promptToBePrinted = 0; return POINTSTOKEN   ;    }         
{SEMICOLON}     {     promptToBePrinted = 0; return SEMICOLONTOKEN;    }      
{QUIT}          {     
                      promptToBePrinted = 0; 
                      if (readStack != NULL) {
			return FALSEQUITTOKEN;
                      }
                      return QUITTOKEN;         
                }
{PRINT}         {     promptToBePrinted = 0; return PRINTTOKEN;        }
{DIFF}          {     promptToBePrinted = 0; return DIFFTOKEN;         }
{SIMPLIFY}      {     promptToBePrinted = 0; return SIMPLIFYTOKEN;     }    
{PLOT}          {     promptToBePrinted = 0; return PLOTTOKEN;         }
{INFNORM}       {     promptToBePrinted = 0; return INFNORMTOKEN;      }
{REMEZ}         {     promptToBePrinted = 0; return REMEZTOKEN;        } 
{DIAM}          {     promptToBePrinted = 0; return DIAMTOKEN;         }
{DOUBLE}        {     promptToBePrinted = 0; return DOUBLETOKEN;       }
{DOUBLEDOUBLE}  {     promptToBePrinted = 0; return DOUBLEDOUBLETOKEN; }
{TRIPLEDOUBLE}  {     promptToBePrinted = 0; return TRIPLEDOUBLETOKEN; }
{DOUBLEEXTENDED} {     promptToBePrinted = 0; return DOUBLEEXTENDEDTOKEN; }
{HORNER}        {     promptToBePrinted = 0; return HORNERTOKEN;       }
{DEGREE}        {     promptToBePrinted = 0; return DEGREETOKEN;       }
{EXPAND}        {     promptToBePrinted = 0; return EXPANDTOKEN;       }
{SIMPLIFYSAFE}  {     promptToBePrinted = 0; return SIMPLIFYSAFETOKEN; }
{CANONICAL}     {     promptToBePrinted = 0; return CANONICALTOKEN; }
{TAYLOR}        {     promptToBePrinted = 0; return TAYLORTOKEN; }
{FINDZEROS}     {     promptToBePrinted = 0; return FINDZEROSTOKEN; }
{DIRTYINFNORM}  {     promptToBePrinted = 0; return DIRTYINFNORMTOKEN; }
{EVALUATE}      {     promptToBePrinted = 0; return EVALUATETOKEN; }
{AT}            {     promptToBePrinted = 0; return ATTOKEN; }
{NUMERATOR}     {     promptToBePrinted = 0; return NUMERATORTOKEN; }
{DENOMINATOR}   {     promptToBePrinted = 0; return DENOMINATORTOKEN; }
{WITHOUT}       {     promptToBePrinted = 0; return WITHOUTTOKEN; }
{DYADIC}        {     promptToBePrinted = 0; return DYADICTOKEN; }
{ON}            {     promptToBePrinted = 0; return ONTOKEN; }
{OFF}           {     promptToBePrinted = 0; return OFFTOKEN; }
{POWERS}        {     promptToBePrinted = 0; return POWERSTOKEN; }
{BINARY}        {     promptToBePrinted = 0; return BINARYTOKEN; }
{INTEGRAL}      {     promptToBePrinted = 0; return INTEGRALTOKEN; }
{DIRTYINTEGRAL} {     promptToBePrinted = 0; return DIRTYINTEGRALTOKEN; }
{PROOF}         {     promptToBePrinted = 0; return PROOFTOKEN; }
{VERBOSITY}     {     promptToBePrinted = 0; return VERBOSITYTOKEN; }
{WORSTCASE}     {     promptToBePrinted = 0; return WORSTCASETOKEN; }	
{WITH}          {     promptToBePrinted = 0; return WITHTOKEN; }	
{INPUTPREC}     {     promptToBePrinted = 0; return INPUTPRECTOKEN; }	
{OUTPUTPREC}    {     promptToBePrinted = 0; return OUTPUTPRECTOKEN; }	
{INPUTEXPO}     {     promptToBePrinted = 0; return INPUTEXPOTOKEN; }	
{EPSILON}       {     promptToBePrinted = 0; return EPSILONTOKEN; }     
{OUTPUT}        {     promptToBePrinted = 0; return OUTPUTTOKEN; }     
{LEFTANGLE}              {     promptToBePrinted = 0; return LEFTANGLETOKEN; }     
{RIGHTANGLEUNDERSCORE}   {     promptToBePrinted = 0; return RIGHTANGLEUNDERSCORETOKEN; }     
{RIGHTANGLEDOT}          {     promptToBePrinted = 0; return RIGHTANGLEDOTTOKEN; }     
{RIGHTANGLE}             {     promptToBePrinted = 0; return RIGHTANGLETOKEN; }     
{SUBSTITUTE}             {     promptToBePrinted = 0; return SUBSTITUTETOKEN; }     
{FPMINIMAX}              {     promptToBePrinted = 0; return FPMINIMAXTOKEN;        }     
{MI}                     {     promptToBePrinted = 0; return MITOKEN;               }     
{TI}                     {     promptToBePrinted = 0; return TITOKEN;               }     
{ABSOLUTE}               {     promptToBePrinted = 0; return ABSOLUTETOKEN;         }     
{RELATIVE}               {     promptToBePrinted = 0; return RELATIVETOKEN;         }     
{WEIGHT}                 {     promptToBePrinted = 0; return WEIGHTTOKEN;           }     
{EQUI}                   {     promptToBePrinted = 0; return EQUITOKEN;             }     
{CHEB}                   {     promptToBePrinted = 0; return CHEBTOKEN;             }     
{IMPLEMENTPOLY}          {     promptToBePrinted = 0; return IMPLEMENTPOLYTOKEN;    }     
{NAME}                   {     promptToBePrinted = 0; return NAMETOKEN;             }     
{VARIABLEMETA}           {     promptToBePrinted = 0; return VARIABLEMETATOKEN;     }
{AS}                     {     promptToBePrinted = 0; return ASTOKEN;               }          
{CHECKINFNORM}           {     promptToBePrinted = 0; return CHECKINFNORMTOKEN;     }          
{BOUNDED}                {     promptToBePrinted = 0; return BOUNDEDTOKEN;          }
{BY}                     {     promptToBePrinted = 0; return BYTOKEN;               }                    
{TAYLORRECURSIONS}       {     promptToBePrinted = 0; return TAYLORRECURSIONSTOKEN; }                    
{PRINTHEXA}              {     promptToBePrinted = 0; return PRINTHEXATOKEN; }                    
{PRINTBINARY}            {     promptToBePrinted = 0; return PRINTBINARYTOKEN; }                    
{ROUNDCOEFFICIENTS}      {     promptToBePrinted = 0; return ROUNDCOEFFICIENTSTOKEN; }                    
{HONORCOEFFPREC}         {     promptToBePrinted = 0; return HONORCOEFFPRECTOKEN; }                    
{RESTART}                {     promptToBePrinted = 0; return RESTARTTOKEN; }                    
{TESTPARI}               {     promptToBePrinted = 0; return TESTPARITOKEN; }                    
{FPFINDZEROS}            {     promptToBePrinted = 0; return FPFINDZEROSTOKEN; }                    
{ZERODENOMINATORS}       {     promptToBePrinted = 0; return ZERODENOMINATORSTOKEN; }                    
{ISEVALUABLE}            {     promptToBePrinted = 0; return ISEVALUABLETOKEN; }                    
{EVALUATEACCURATE}       {     promptToBePrinted = 0; return EVALUATEACCURATETOKEN; }                    
{EXCLAMATION}            {     promptToBePrinted = 0; return EXCLAMATIONTOKEN; }                    
{ACCURATEINFNORM}        {     promptToBePrinted = 0; return ACCURATEINFNORMTOKEN; }                    
{BITS}                   {     promptToBePrinted = 0; return BITSTOKEN; }                    
{FILE}                   {     promptToBePrinted = 0; return FILETOKEN;           }                    
{POSTSCRIPT}             {     promptToBePrinted = 0; return POSTSCRIPTTOKEN;     }                    
{POSTSCRIPTFILE}         {     promptToBePrinted = 0; return POSTSCRIPTFILETOKEN; }                    
{PRINTEXPANSION}         {     promptToBePrinted = 0; return PRINTEXPANSIONTOKEN; }                    
{BASHEXECUTE}            {     promptToBePrinted = 0; return BASHEXECUTETOKEN; }                    
{EXTERNALPLOT}           {     promptToBePrinted = 0; return EXTERNALPLOTTOKEN; }                    
{PERTURB}                {     promptToBePrinted = 0; return PERTURBTOKEN; }                    
{TO}                     {     promptToBePrinted = 0; return TOTOKEN; }                    
{COEFF}                  {     promptToBePrinted = 0; return COEFFTOKEN; }                    
{SUBPOLY}                {     promptToBePrinted = 0; return SUBPOLYTOKEN; }                    
{QUESTIONMARK}           {     promptToBePrinted = 0; return QUESTIONMARKTOKEN; }                    
{SEARCHGAL}              {     promptToBePrinted = 0; return SEARCHGALTOKEN; }                    
{STEPS}                  {     promptToBePrinted = 0; return STEPSTOKEN; }                    
{RATIONALAPPROX}         {     promptToBePrinted = 0; return RATIONALAPPROXTOKEN; }                    
{WRITE}                  {     promptToBePrinted = 0; return WRITETOKEN; }                    
{ASCIIPLOT}              {     promptToBePrinted = 0; return ASCIIPLOTTOKEN; }                    
{DOLLAR}                 {     promptToBePrinted = 0; return DOLLARTOKEN; }                    
{ROUNDTOFORMAT}          {     promptToBePrinted = 0; return ROUNDTOFORMATTOKEN; }                    
{MINUSWORD}              {     promptToBePrinted = 0; return MINUSWORDTOKEN; }                    	
{PLUSWORD}               {     promptToBePrinted = 0; return PLUSWORDTOKEN; }                    	
{ZEROWORD}               {     promptToBePrinted = 0; return ZEROWORDTOKEN; }                    	
{NEAREST}                {     promptToBePrinted = 0; return NEARESTTOKEN; }                    
{GUESSDEGREE}            {     promptToBePrinted = 0; return GUESSDEGREETOKEN; }                    
{PARSE}                  {     promptToBePrinted = 0; return PARSETOKEN; }                    
{AUTOSIMPLIFY}           {     promptToBePrinted = 0; return AUTOSIMPLIFYTOKEN; }                    
{TIMING}                 {     promptToBePrinted = 0; return TIMINGTOKEN; }                    

{READ}          {
                      BEGIN(readstate);
                }

{VARIABLE}      {     			     
                      if (currentVariable != NULL) free(currentVariable);
		      currentVariable = NULL;
		      currentVariable = (char*) safeCalloc(yyleng + 1,sizeof(char));
		      strncpy(currentVariable,yytext,yyleng);
                      promptToBePrinted = 0; return VARIABLETOKEN;    
                }

{STRING}        {     			     
                      if (currentString != NULL) free(currentString);
		      currentString = NULL;
		      currentString = (char*) safeCalloc(yyleng - 1,sizeof(char));
		      strncpy(currentString,yytext+1,yyleng-2);
                      promptToBePrinted = 0; return STRINGTOKEN;    
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
			promptToBePrinted = 1;
		      } else {
			eliminatePrompt = 1;
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
			if (readStack == NULL) {
			  eliminatePrompt = eliminatePromptBackup;
			}
		      }
                }

{FINISH}        {
                      if (readStack == NULL) {
			fprintf(stderr,"Error: unallowed character in this context.\n");
		      } else {
			printMessage(1,"Warning: closing file included using the read macro.\n");
			fclose(yyin);
			yyin = *((FILE **) (readStack2->value));
			free(readStack2->value);
			readStackTemp = readStack2->next;
			free(readStack2);
			readStack2 = readStackTemp;
			yy_delete_buffer(YY_CURRENT_BUFFER,scanner);
			yy_switch_to_buffer(*((YY_BUFFER_STATE *) (readStack->value)),scanner);
			free(readStack->value);
			readStackTemp = readStack->next;
			free(readStack);
			readStack = readStackTemp;
			if (readStack == NULL) {
			  eliminatePrompt = eliminatePromptBackup;
			}
		      }
                }



[ \t]		{ /* Eat up spaces and tabulators */
		}

[\n]		{ 
                      if (promptToBePrinted) printPrompt();
		}

.		{ /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

%%


