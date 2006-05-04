%{

#include <stdio.h>
#include "expression.h"
#include "parser.tab.h"
#include "main.h"

#define YY_NO_UNPUT


%}

%option noyywrap


CHAR		[a-zA-Z]
NUMBER		[0-9]

CONSTANT        ({NUMBER}+|({NUMBER}+"."{NUMBER}*)|({NUMBER}*"."{NUMBER}+))((([eE]([+-])?{NUMBER}+)?))
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


%%

%{

%}



{CONSTANT}      {     
                      yylval.value = yytext;
                      return CONSTTOKEN;
                }
{IN}            {     return INTOKEN; }
{LBRACKET}      {     return LBRACKETTOKEN; }
{RBRACKET}      {     return RBRACKETTOKEN; }

{PI}            {     return PITOKEN;    }             
{E}             {     return ETOKEN;     }              
{LPAR}          {     return LPARTOKEN     ;    }           
{RPAR}          {     return RPARTOKEN     ;    }           
{PLUS}          {     return PLUSTOKEN     ;    }           
{MINUS}         {     return MINUSTOKEN    ;    }          
{MUL}           {     return MULTOKEN      ;    }            
{DIV}           {     return DIVTOKEN      ;    }            
{POW}           {     return POWTOKEN      ;    }            
{SQRT}          {     return SQRTTOKEN     ;    }           
{EXP}           {     return EXPTOKEN      ;    }            
{LOG}           {     return LOGTOKEN      ;    }            
{LOG2}          {     return LOG2TOKEN     ;    }           
{LOG10}         {     return LOG10TOKEN    ;    }          
{SIN}           {     return SINTOKEN      ;    }            
{COS}           {     return COSTOKEN      ;    }            
{TAN}           {     return TANTOKEN      ;    }            
{ASIN}          {     return ASINTOKEN     ;    }           
{ACOS}          {     return ACOSTOKEN     ;    }           
{ATAN}          {     return ATANTOKEN     ;    }           
{SINH}          {     return SINHTOKEN     ;    }           
{COSH}          {     return COSHTOKEN     ;    }           
{TANH}          {     return TANHTOKEN     ;    }           
{ASINH}         {     return ASINHTOKEN    ;    }          
{ACOSH}         {     return ACOSHTOKEN    ;    }          
{ATANH}         {     return ATANHTOKEN    ;    }          
{ABS}           {     return ABSTOKEN      ;    }            
{COLON}         {     return COLONTOKEN    ;    }          
{EQUAL}         {     return EQUALTOKEN    ;    }          
{COMMA}         {     return COMMATOKEN    ;    }          
{PREC}          {     return PRECTOKEN     ;    }           
{POINTS}        {     return POINTSTOKEN   ;    }         
{SEMICOLON}     {     return SEMICOLONTOKEN;    }      
{QUIT}          {     return QUITTOKEN;         }
{PRINT}         {     return PRINTTOKEN;        }
{DIFF}          {     return DIFFTOKEN;         }
{SIMPLIFY}      {     return SIMPLIFYTOKEN;     }    
{PLOT}          {     return PLOTTOKEN;         }
{INFNORM}       {     return INFNORMTOKEN;      }
{REMEZ}         {     return REMEZTOKEN;        } 
{DIAM}          {     return DIAMTOKEN;         }
{DOUBLE}        {     return DOUBLETOKEN;       }
{DOUBLEDOUBLE}  {     return DOUBLEDOUBLETOKEN; }
{TRIPLEDOUBLE}  {     return TRIPLEDOUBLETOKEN; }
{HORNER}        {     return HORNERTOKEN;       }
{DEGREE}        {     return DEGREETOKEN;       }
{EXPAND}        {     return EXPANDTOKEN;       }
{SIMPLIFYSAFE}  {     return SIMPLIFYSAFETOKEN; }


{VARIABLE}      {     			     
                      if (variablename == NULL) { 
                         variablename = (char*) calloc(yyleng + 1,sizeof(char));
			 strncpy(variablename,yytext,yyleng);
                      } else {
			if (strncmp(variablename,yytext,yyleng) != 0) {
			  printf("Warning: only one variable name is allowed in the expression, ");
			  printf("will interpret \"%s\" as \"%s\".\n",
				 yytext, variablename);
			}
                      }
                      return VARIABLETOKEN;    
                }

[ \t]		{ /* Eat up spaces and tabulators */
		}

[\n]		{ /* Eat up carriage returns and count them */
		}

.		{ /* otherwise */
			fprintf(stderr,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				yytext);
		}

%%



