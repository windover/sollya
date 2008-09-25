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
it offers a certified infinity norm, an automatic polynomial
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
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "miniparser.h"
#include "general.h"


#define YY_NO_UNPUT 1

%}

%option noyywrap
%option prefix="miniyy"
%option always-interactive
%option nounput


CHAR		[a-zA-Z]
NUMBER		[0-9]
HEXNUMBER       (([0-9])|([ABCDEFabcdef]))


CONSTANT        ((({NUMBER}+|({NUMBER}*"."{NUMBER}+))(((((" ")*)[eE]([+-])?{NUMBER}+)?)))|("infty"|"nan"|"NAN"|"NaN"|"@Inf@"|"@NaN@"))
DYADICCONSTANT  ({NUMBER}+)([bB])([+-]?)({NUMBER}+)
HEXCONSTANT     ("0x"){HEXNUMBER}{16}

BINARYCONSTANT  (([0-1])+|(([0-1])*"."([0-1])+))"_2"


VARIABLE        {CHAR}({CHAR}|{NUMBER})*

LPAR            "("
RPAR            ")"
	       	
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

CEIL            "ceil"
FLOOR           "floor"

%%


{BINARYCONSTANT} {
		      constBuffer = (char *) safeCalloc(strlen(miniyytext)-1,sizeof(char));
		      strncpy(constBuffer,miniyytext,strlen(miniyytext)-2);
                      miniyylval.value = constBuffer;
                       return BINARYCONSTTOKEN;
                 }


{CONSTANT}      {     
		      constBuffer = (char *) safeCalloc(strlen(miniyytext)+1,sizeof(char));
		      removeSpaces(constBuffer,miniyytext);
                      miniyylval.value = constBuffer;
                       return CONSTTOKEN;
                }
{DYADICCONSTANT} {     
                      miniyylval.value = miniyytext;
                       return DYADICCONSTTOKEN;
                }
{HEXCONSTANT}   {     
                      miniyylval.value = miniyytext;
                       return HEXCONSTTOKEN;
                }
{PI}            {      return PITOKEN;    }             
{E}             {      return ETOKEN;     }              
{LPAR}          {      return LPARTOKEN     ;    }           
{RPAR}          {      return RPARTOKEN     ;    }           
{PLUS}          {      return PLUSTOKEN     ;    }           
{MINUS}         {      return MINUSTOKEN    ;    }          
{MUL}           {      return MULTOKEN      ;    }            
{DIV}           {      return DIVTOKEN      ;    }            
{POW}           {      return POWTOKEN      ;    }            
{SQRT}          {      return SQRTTOKEN     ;    }           
{EXP}           {      return EXPTOKEN      ;    }            
{LOG}           {      return LOGTOKEN      ;    }            
{LOG2}          {      return LOG2TOKEN     ;    }           
{LOG10}         {      return LOG10TOKEN    ;    }          
{SIN}           {      return SINTOKEN      ;    }            
{COS}           {      return COSTOKEN      ;    }            
{TAN}           {      return TANTOKEN      ;    }            
{ASIN}          {      return ASINTOKEN     ;    }           
{ACOS}          {      return ACOSTOKEN     ;    }           
{ATAN}          {      return ATANTOKEN     ;    }           
{SINH}          {      return SINHTOKEN     ;    }           
{COSH}          {      return COSHTOKEN     ;    }           
{TANH}          {      return TANHTOKEN     ;    }           
{ASINH}         {      return ASINHTOKEN    ;    }          
{ACOSH}         {      return ACOSHTOKEN    ;    }          
{ATANH}         {      return ATANHTOKEN    ;    }          
{ABS}           {      return ABSTOKEN      ;    }            
{ERF}           {      return ERFTOKEN      ;    }            
{ERFC}          {      return ERFCTOKEN     ;    }            
{LOG1P}         {      return LOG1PTOKEN    ;    }            
{EXPM1}         {      return EXPM1TOKEN    ;    }            
{DOUBLE}        {      return DOUBLETOKEN;       }
{DOUBLEDOUBLE}  {      return DOUBLEDOUBLETOKEN; }
{TRIPLEDOUBLE}  {      return TRIPLEDOUBLETOKEN; }
{DOUBLEEXTENDED} {      return DOUBLEEXTENDEDTOKEN; }
{CEIL}          {      return CEILTOKEN; }
{FLOOR}         {      return FLOORTOKEN; }
{VARIABLE}      {     			     
		      constBuffer = (char*) safeCalloc(miniyyleng + 1,sizeof(char));
		      strncpy(constBuffer,miniyytext,miniyyleng);
		      miniyylval.value = constBuffer;
                       return VARIABLETOKEN;    
                }

[ \t]		{ /* Eat up spaces and tabulators */
		}

[\n]		{ 
		}

.		{ /* otherwise */
			printMessage(1,"The character \"%s\" cannot be recognized. Will ignore it.\n",
				miniyytext);
		}

%%



void startBuffer(char *str) {
  miniyy_switch_to_buffer(miniyy_scan_string(str));
}

void endBuffer(void) {
  miniyy_delete_buffer(YY_CURRENT_BUFFER);
}
