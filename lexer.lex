%{

#include <stdio.h>
#include <string.h>
#include "expression.h"
#include "parser.tab.h"
#include "main.h"


#define YY_NO_UNPUT


%}

%option noyywrap


CHAR		[a-zA-Z]
NUMBER		[0-9]

CONSTANT        ({NUMBER}+|({NUMBER}+"."{NUMBER}*)|({NUMBER}*"."{NUMBER}+))((([eE]([+-])?{NUMBER}+)?))
DYADICCONSTANT  ({NUMBER}+)([bB])([+-]?)({NUMBER}+)
VARIABLE        {CHAR}({CHAR}|{NUMBER})*

LPAR            "("
RPAR            ")"

LBRACKET        "["
RBRACKET        "]"

IN              "in"
	       	
PI              "pi"
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
	       	
COLON           ":"
EQUAL           "="
COMMA           ","
PREC            "prec"
POINTS          "points"
	       	
SEMICOLON       ";"
QUIT            "quit"
PRINT           "print"
DIFF            "diff"
SIMPLIFY        "simplify"
PLOT            "plot"
REMEZ           "remez"
INFNORM         "infnorm"
DIAM            "diam"

DOUBLELONG       "double"
DOUBLEDOUBLELONG "doubledouble"
TRIPLEDOUBLELONG "tripledouble"

DOUBLESHORT      "D"
DOUBLEDOUBLESHORT "DD"
TRIPLEDOUBLESHORT "TD"


DOUBLE          ({DOUBLELONG}|{DOUBLESHORT})
DOUBLEDOUBLE    ({DOUBLEDOUBLELONG}|{DOUBLEDOUBLESHORT})
TRIPLEDOUBLE    ({TRIPLEDOUBLELONG}|{TRIPLEDOUBLESHORT})

HORNER          "horner"
DEGREE          "degree"
EXPAND          "expand"

SIMPLIFYSAFE1   "safesimplify"
SIMPLIFYSAFE2   "simplifysafe"

SIMPLIFYSAFE    ({SIMPLIFYSAFE1}|{SIMPLIFYSAFE2})

TAYLOR          "taylor"

FINDZEROS       "findzeros"
DIRTYINFNORM    "dirtyinfnorm"

EVALUATE        "evaluate"
AT              "at"

NUMERATOR       "numerator"
DENOMINATOR     "denominator"

WITHOUT         "without"

DYADIC          "dyadic"
ON              "on"
OFF             "off"

%%

%{

%}



{CONSTANT}      {     
                      yylval.value = yytext;
                      promptToBePrinted = 0; return CONSTTOKEN;
                }
{DYADICCONSTANT} {     
                      yylval.value = yytext;
                      promptToBePrinted = 0; return DYADICCONSTTOKEN;
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
{COLON}         {     promptToBePrinted = 0; return COLONTOKEN    ;    }          
{EQUAL}         {     promptToBePrinted = 0; return EQUALTOKEN    ;    }          
{COMMA}         {     promptToBePrinted = 0; return COMMATOKEN    ;    }          
{PREC}          {     promptToBePrinted = 0; return PRECTOKEN     ;    }           
{POINTS}        {     promptToBePrinted = 0; return POINTSTOKEN   ;    }         
{SEMICOLON}     {     promptToBePrinted = 0; return SEMICOLONTOKEN;    }      
{QUIT}          {     promptToBePrinted = 0; return QUITTOKEN;         }
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
{HORNER}        {     promptToBePrinted = 0; return HORNERTOKEN;       }
{DEGREE}        {     promptToBePrinted = 0; return DEGREETOKEN;       }
{EXPAND}        {     promptToBePrinted = 0; return EXPANDTOKEN;       }
{SIMPLIFYSAFE}  {     promptToBePrinted = 0; return SIMPLIFYSAFETOKEN; }
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


{VARIABLE}      {     			     
                      if (currentVariable != NULL) free(currentVariable);
		      currentVariable = NULL;
		      currentVariable = (char*) calloc(yyleng + 1,sizeof(char));
		      strncpy(currentVariable,yytext,yyleng);
                      promptToBePrinted = 0; return VARIABLETOKEN;    
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



