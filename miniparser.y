/*

Copyright 2007 by 

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
#include "general.h"
#include "miniparser.h"
#include "double.h"

#define YYERROR_VERBOSE 1

extern int miniyylex();

void miniyyerror(char *message) {
    printMessage(1,"Warning: %s. Will try to continue parsing (expecting \";\"). May leak memory.\n",message);
}


%}

%defines
%name-prefix="miniyy" 

%union {
	char *value;
        node *tree;
        mpfr_t *constantval;
  	void *other;
};


%token  <value> CONSTTOKEN
%token  <value> DYADICCONSTTOKEN
%token  <value> BINARYCONSTTOKEN
%token  <value> HEXCONSTTOKEN
%token  PITOKEN
%token  ETOKEN
%token  <value> VARIABLETOKEN
%token	LPARTOKEN        
%token	RPARTOKEN        
%token	PLUSTOKEN        
%token	MINUSTOKEN       
%token	MULTOKEN             
%token	DIVTOKEN         
%token	POWTOKEN         
%token	SQRTTOKEN        
%token	EXPTOKEN         
%token	LOGTOKEN         
%token	LOG2TOKEN        
%token	LOG10TOKEN       
%token	SINTOKEN             
%token	COSTOKEN         
%token	TANTOKEN         
%token	ASINTOKEN        
%token	ACOSTOKEN        
%token	ATANTOKEN        
%token	SINHTOKEN        
%token	COSHTOKEN        
%token	TANHTOKEN        
%token	ASINHTOKEN       
%token	ACOSHTOKEN       
%token	ATANHTOKEN       
%token	ABSTOKEN         
%token	ERFTOKEN         
%token	ERFCTOKEN         
%token	LOG1PTOKEN         
%token	EXPM1TOKEN         
%token  DOUBLETOKEN
%token  DOUBLEDOUBLETOKEN
%token  TRIPLEDOUBLETOKEN
%token  DOUBLEEXTENDEDTOKEN
%token  CEILTOKEN
%token  FLOORTOKEN

%type <other> start
%type <tree> fun
%type <tree> prefixfunction
%type <constantval> constant
%type <tree> variable 
%type <tree> term
%type <tree> subterm
%type <tree> primary

%%


start:                          fun
                           {
			     minitree = $1;   
			     $$ = NULL;
			   }
;



fun:     			term						
                           {
			     $$ = $1;
                           }   									
      			|	fun PLUSTOKEN term			
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ADD;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }										
			|	fun MINUSTOKEN term			
		           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SUB;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }				   			
;

		
prefixfunction:                 SQRTTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SQRT;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       EXPTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = EXP;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOGTOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG2TOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_2;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG10TOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_10;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINTOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSTOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = COS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANTOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINTOKEN LPARTOKEN fun RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ASIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ACOS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ATAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINHTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSHTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = COSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANHTOKEN LPARTOKEN fun RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINHTOKEN LPARTOKEN fun RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ASINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSHTOKEN LPARTOKEN fun RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ACOSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANHTOKEN LPARTOKEN fun RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ATANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ABSTOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ABS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ERFTOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ERF;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ERFCTOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ERFC;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG1PTOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_1P;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       EXPM1TOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = EXP_M1;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLETOKEN LPARTOKEN fun RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLEDOUBLETOKEN LPARTOKEN fun RPARTOKEN     			  		
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TRIPLEDOUBLETOKEN LPARTOKEN fun RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TRIPLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLEEXTENDEDTOKEN LPARTOKEN fun RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLEEXTENDED;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }
                        |       CEILTOKEN LPARTOKEN fun RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = CEIL;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }
                        |       FLOORTOKEN LPARTOKEN fun RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = FLOOR;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }
;




term:				subterm						
			   {
			     $$ = $1;
                           }			
			|	MINUSTOKEN subterm			
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = NEG;
			     temp_node->child1 = $2;
			     $$ = temp_node;
                           }									
			|	term MULTOKEN subterm				
			   {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = MUL;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }							
										
			|	term DIVTOKEN subterm				
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DIV;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }					
;

subterm:                        primary
                           {
			     $$ = $1;
                           }
                        |       subterm POWTOKEN primary
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = POW;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }
;

primary:			variable					
			   {
			     $$ = $1;
                           }	  									
			|       constant  
			   {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = CONSTANT;
			     temp_node->value = $1;
			     $$ = temp_node;
                           }									
                        |       PITOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = PI_CONST;
			     $$ = temp_node;
			   }
			|	LPARTOKEN fun RPARTOKEN			
			   {
			     $$ = $2;
                           }	
                        |       prefixfunction
                           {
                             $$ = $1;
                           }
;


variable: VARIABLETOKEN
                           {
			     if (variablename == NULL) {
			       variablename = (char *) safeCalloc(strlen($1) + 1,sizeof(char));
			       strcpy(variablename,$1);
			     }
			     if (strcmp(variablename,$1) != 0) {
				 printMessage(1,"Warning: the identifier \"%s\" is not equal to the bound current variable.\n",$1);
				 printMessage(1,"Will interpret \"%s\" as \"%s\".\n",$1,variablename);
			     }
			     temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = VARIABLE;
			     free($1);
			     $$ = temp_node;
			   }
;


constant: CONSTTOKEN 
                           {
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,tools_precision);
			     mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDD);
			     mpfr_set_str(*mpfr_temp2,$1,10,GMP_RNDU);
			     if (mpfr_cmp(*mpfr_temp,*mpfr_temp2) != 0) {
			       printMessage(1,
                            "Warning: Rounding occurred when converting constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			       mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDN);
			     } 
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp2);
			     free($1);
			     $$ = mpfr_temp;
			   }
        | DYADICCONSTTOKEN {
                             mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (!readDyadic(*mpfr_temp,$1)) {
			       printMessage(1,
                            "Warning: Rounding occurred when converting the dyadic constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			     }
			     if (!mpfr_number_p(*mpfr_temp)) {
			       printMessage(1,
			  "Error: overflow occurred during the conversion of the dyadic constant \"%s\". Will abort the computation.\n",$1);
			       recoverFromError();
			     }
			     $$ = mpfr_temp;
	                   }
        | BINARYCONSTTOKEN {
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,tools_precision);
			     mpfr_set_str(*mpfr_temp,$1,2,GMP_RNDD);
			     mpfr_set_str(*mpfr_temp2,$1,2,GMP_RNDU);
			     if (mpfr_cmp(*mpfr_temp,*mpfr_temp2) != 0) {
			       printMessage(1,
                            "Warning: Rounding occurred when converting constant \"%s_2\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			       mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDN);
			     } 
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp2);
			     free($1);
			     $$ = mpfr_temp;
	                   }
        | HEXCONSTTOKEN    {
	                     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (!readHexa(*mpfr_temp,$1)) {
			       printMessage(1,
                            "Warning: Rounding occurred when converting the hexadecimal constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			     }
			     if (!mpfr_number_p(*mpfr_temp)) {
			       printMessage(1,
			  "Error: overflow occurred during the conversion of the hexadecimal constant \"%s\". Will abort the computation.\n",$1);
			       recoverFromError();
			     }
	                     $$ = mpfr_temp;
	                   }
        | ETOKEN 
                           {
			     printMessage(1,"Warning: The e constant in the expression will be represented on %d bits\n",
				    (int) tools_precision);
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
			     mpfr_exp(*mpfr_temp,*mpfr_temp,GMP_RNDN);
			     $$ = mpfr_temp;
			   }
;


