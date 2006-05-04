%{
#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "main.h"
#include "remez.h"
#include "infnorm.h"

int yylex();

extern FILE *yyin;
extern char *yytext;

void yyerror(char *message) {
  printf("Warning: %s on token \"%s\". Will try to continue parsing (expecting \";\"). May leak memory.\n",
	 message,yytext);
}

%}


%locations

%defines

%union {
	char *value;
        node *tree;
        mp_prec_t  precisionval;
        int  pointsnum;
        rangetype rangeval;
        mpfr_t *constantval;
        int degreeval;
	void *other;
}


%token  <value> CONSTTOKEN
%token  INTOKEN
%token  LBRACKETTOKEN
%token  RBRACKETTOKEN
%token  PITOKEN
%token  ETOKEN
%token  VARIABLETOKEN
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
%token	COLONTOKEN       
%token	EQUALTOKEN       
%token	COMMATOKEN       
%token	PRECTOKEN        
%token	POINTSTOKEN      		
%token  SEMICOLONTOKEN   
%token  QUITTOKEN
%token  PRINTTOKEN
%token  DIFFTOKEN
%token  SIMPLIFYTOKEN
%token  PLOTTOKEN
%token  INFNORMTOKEN
%token  REMEZTOKEN
%token  DIAMTOKEN
%token  DOUBLETOKEN
%token  DOUBLEDOUBLETOKEN
%token  TRIPLEDOUBLETOKEN
%token  HORNERTOKEN
%token  DEGREETOKEN
%token  EXPANDTOKEN
%token  SIMPLIFYSAFETOKEN


%type <other> commands
%type <other> command
%type <other> plot
%type <other> print
%type <precisionval> precision
%type <pointsnum> points
%type <tree> function
%type <tree> prefixfunction
%type <rangeval> range
%type <constantval> constant
%type <constantval> rangeconstant
%type <constantval> diamconstant
%type <tree> variable 
%type <tree> term
%type <tree> subterm
%type <tree> primary
%type <degreeval> degree
%type <rangeval> infnorm

%%

commands:    QUITTOKEN SEMICOLONTOKEN
                           {
                             exit(0);
			     $$ = NULL;
                           }
           | command commands 
                           {
                             $$ = NULL;
                           }
;

command:     plot
                           {
			     printPrompt();
			     $$ = NULL;
			   }
           | print        
                           {
			     printPrompt();
                             $$ = NULL;
                           } 
           | infnorm       {
	                     printf("infnorm result: ");
			     mpfr_temp = (mpfr_t *) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_abs(*($1.a),*($1.a),GMP_RNDN);
			     mpfr_abs(*($1.b),*($1.b),GMP_RNDN);
			     mpfr_max(*mpfr_temp,*($1.a),*($1.b),GMP_RNDU);
			     printValue(mpfr_temp,defaultprecision);
			     printf("\n");
			     mpfr_temp2 = (mpfr_t *) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,defaultprecision);
			     mpfr_sub(*mpfr_temp2,*($1.a),*($1.b),GMP_RNDU);
			     mpfr_abs(*mpfr_temp2,*mpfr_temp2,GMP_RNDN);
			     if (mpfr_zero_p(*mpfr_temp)) {
			       printf("Absolute diameter of confidence interval: ");
			       printValue(mpfr_temp2,defaultprecision);
			       printf("\n");
			     } else {
			       mpfr_div(*mpfr_temp2,*mpfr_temp2,*mpfr_temp,GMP_RNDU);
			       printf("Relative diameter of confidence interval: ");
			       printValue(mpfr_temp2,defaultprecision);
			       mpfr_log2(*mpfr_temp2,*mpfr_temp2,GMP_RNDU);
			       double_temp = mpfr_get_d(*mpfr_temp2,GMP_RNDU);
			       printf(" (= 2^(%f))\n",double_temp);
			     }
			     mpfr_clear(*mpfr_temp);
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp);
			     free(mpfr_temp2);
			     mpfr_clear(*($1.a));
			     mpfr_clear(*($1.b));
			     free($1.a);
			     free($1.b);
			     free(variablename);
			     variablename = NULL;
			     printPrompt();
	                     $$ = NULL;
	                   }
	   | precision SEMICOLONTOKEN 
                           {
			     tools_precision = $1;
			     defaultprecision = $1;
			     printf("Default precision has been set to %d bits.\n",(int) defaultprecision);
			     printPrompt();
                             $$ = NULL;
                           }
	   | points SEMICOLONTOKEN 
                           {
			     defaultpoints = $1;
			     printf("Default point number has been set to %d.\n",(int) defaultpoints);
			     printPrompt();
                             $$ = NULL;
                           }
           | error SEMICOLONTOKEN
                           {
			     free(variablename);
			     variablename = NULL;
			     printPrompt();
			     $$ = NULL;
                           }
;


infnorm:     INFNORMTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = infnorm($2,$4,defaultprecision,*mpfr_temp);
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant SEMICOLONTOKEN
	                   {
			     range_temp = infnorm($2,$4,defaultprecision,*($8));
			     mpfr_clear(*($8));
			     free($8);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
;


print:       PRINTTOKEN function SEMICOLONTOKEN
                           {
			     prec_temp = tools_precision;
			     tools_precision = defaultprecision;
                             printTree($2);
			     tools_precision = prec_temp;
			     printf("\n");
			     free_memory($2);
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;
                           }
;

plot:        PLOTTOKEN precision COMMATOKEN points COLONTOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($6, *($8.a), *($8.b), $4, $2);
			     free_memory($6);
			     mpfr_clear(*($8.a));
			     mpfr_clear(*($8.b));
			     free($8.a);
			     free($8.b);
			     tools_precision = defaultprecision;
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;
                           }
           | PLOTTOKEN points COMMATOKEN precision COLONTOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($6, *($8.a), *($8.b), $2, $4);
			     free_memory($6);
			     mpfr_clear(*($8.a));
			     mpfr_clear(*($8.b));
			     free($8.a);
			     free($8.b);
			     tools_precision = defaultprecision;
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;
                           }
           | PLOTTOKEN precision COLONTOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($4, *($6.a), *($6.b), defaultpoints, $2);
			     free_memory($4);
			     mpfr_clear(*($6.a));
			     mpfr_clear(*($6.b));
			     free($6.a);
			     free($6.b);
			     tools_precision = defaultprecision;
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;										 
			   }
           | PLOTTOKEN points COLONTOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($4, *($6.a), *($6.b), $2, tools_precision);
			     free_memory($4);
			     mpfr_clear(*($6.a));
			     mpfr_clear(*($6.b));
			     free($6.a);
			     free($6.b);
			     tools_precision = defaultprecision;
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;
			   }
           | PLOTTOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), defaultpoints, tools_precision);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     free(variablename);
			     variablename = NULL;
			     $$ = NULL;
			   }
;

precision:  PRECTOKEN EQUALTOKEN CONSTTOKEN 
                           {
			     tools_precision = strtol($3,endptr,10);
                             if (**endptr != '\0') {
			       printf("A precision must be integer\n");
			       exit(1);
			     }
			     if (tools_precision < 12) {
			       printf("Precision has been increased to 12.\n");
			       tools_precision = 12;
			     }
			     $$ = tools_precision;
                           }
;

points:  POINTSTOKEN EQUALTOKEN CONSTTOKEN
                           {
			     points = (unsigned long int) strtol($3,endptr,10);
                             if (**endptr != '\0') {
			       printf("Number of points must be integer\n");
			       exit(1);
			     }
			     if (points < 3) {
			       printf("You must print at least 3 points. Increasing number to 3.\n");
			       points = 3;
			     }
			     $$ = points;                           
                           }
;

degree:  CONSTTOKEN
                           {
			     int_temp = (int) strtol($1,endptr,10);
                             if (**endptr != '\0') {
			       printf("The degree of a polynomial must be integer. Will do degree 3.\n");
			       int_temp = 3;
			     }
			     if (int_temp < 0) {
			       printf("The degree of a polynomial must be a positive number. Will do degree 3.\n");
			       int_temp = 3;
			     }
			     $$ = int_temp;                           
                           }
;


function:			term						
                           {
			     $$ = $1;
                           }   									
      			|	function PLUSTOKEN term			
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ADD;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }										
			|	function MINUSTOKEN term			
		           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = SUB;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }				   			
			|	MINUSTOKEN term			
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = NEG;
			     temp_node->child1 = $2;
			     $$ = temp_node;
                           }
;

		
prefixfunction:                EXPANDTOKEN LPARTOKEN function RPARTOKEN
                           {
			      temp_node = expand($3);
			      free_memory($3);
			      $$ = temp_node;
                           } 
			|      DEGREETOKEN LPARTOKEN function RPARTOKEN
                           {
			      temp_node = (node*) malloc(sizeof(node));
			      mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			      mpfr_init2(*(mpfr_temp),(mp_prec_t) tools_precision);
			      mpfr_set_si(*(mpfr_temp),getDegree($3),GMP_RNDN);
                              temp_node->nodeType = CONSTANT;
                              temp_node->value = mpfr_temp;
			      free_memory($3);
			      $$ = temp_node;
                           }
                        |       HORNERTOKEN LPARTOKEN function RPARTOKEN
                           {
			      temp_node = horner($3);
			      free_memory($3);
			      $$ = temp_node;
                           }
			|       REMEZTOKEN LPARTOKEN function COMMATOKEN degree COMMATOKEN range RPARTOKEN
                           {
			      temp_node = remez($3, $5, *($7.a), *($7.b), tools_precision);
			      free_memory($3);
			      mpfr_clear(*($7.a));
			      mpfr_clear(*($7.b));
			      free($7.a);
			      free($7.b);
			      $$ = temp_node;
                           }
                        |       SIMPLIFYTOKEN LPARTOKEN function RPARTOKEN
                           {
			     temp_node = simplifyTree($3);
			     free_memory($3);
			     $$ = temp_node;
			   }
                        |       SIMPLIFYSAFETOKEN LPARTOKEN function RPARTOKEN
                           {
			     temp_node = simplifyTreeErrorfree($3);
			     free_memory($3);
			     $$ = temp_node;
			   }
			|       DIFFTOKEN LPARTOKEN function RPARTOKEN
                           {
			     temp_node = differentiate($3);
			     free_memory($3);
			     $$ = temp_node;
			   }
			|       SQRTTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = SQRT;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       EXPTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = EXP;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOGTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = LOG;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG2TOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = LOG_2;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG10TOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = LOG_10;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = SIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = COS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = TAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ASIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ACOS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ATAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = SINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = COSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = TANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ASINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ACOSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ATANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ABSTOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = ABS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLETOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = DOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLEDOUBLETOKEN LPARTOKEN function RPARTOKEN     			  		
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = DOUBLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TRIPLEDOUBLETOKEN LPARTOKEN function RPARTOKEN     			   	
                           {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = TRIPLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
;

term:				subterm						
			   {
			     $$ = $1;
                           }												
			|	term MULTOKEN subterm				
			   {
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = MUL;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }							
										
			|	term DIVTOKEN subterm				
                           {
                             temp_node = (node*) malloc(sizeof(node));
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
                             temp_node = (node*) malloc(sizeof(node));
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
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = CONSTANT;
			     temp_node->value = $1;
			     $$ = temp_node;
                           }									
			|	LPARTOKEN function RPARTOKEN			
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
                             temp_node = (node*) malloc(sizeof(node));
			     temp_node->nodeType = VARIABLE;
			     $$ = temp_node;
                           }
;

range:  LBRACKETTOKEN rangeconstant SEMICOLONTOKEN rangeconstant RBRACKETTOKEN
                           {
                             range_temp.a = $2;
			     range_temp.b = $4;
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) > 0) {
			       printf("Warning: the range bounds are not correctly ordered. Will revert them.\n");
			       mpfr_swap(*(range_temp.a),*(range_temp.b));
		             }
			     $$ = range_temp;
                           }
      | LBRACKETTOKEN rangeconstant COMMATOKEN rangeconstant RBRACKETTOKEN
                           {
                             range_temp.a = $2;
			     range_temp.b = $4;
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) > 0) {
			       printf("Warning: the range bounds are not correctly ordered. Will revert them.\n");
			       mpfr_swap(*(range_temp.a),*(range_temp.b));
		             }
			     $$ = range_temp;
                           }
;


rangeconstant:     function
                           {
			     mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if ($1->nodeType != CONSTANT) {
			       printf(
                      "Warning: the range bound given is not a floating-point constant but an expression to evaluate.\n");
			     }
			     if (!evaluateConstantExpression(*mpfr_temp,($1),tools_precision)) {
			       printf("Warning: range bounds must be expressions that evaluate to constants.\n");
			       printf("Setting %s = 0 when evaluating the given variable expression.\n",variablename);
			       mpfr_temp2 = (mpfr_t*) malloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp2,tools_precision);
			       mpfr_set_d(*mpfr_temp2,1.0,GMP_RNDN);
			       evaluate(*mpfr_temp, ($1), *mpfr_temp2, tools_precision);
			       mpfr_clear(*mpfr_temp2);
			       free(mpfr_temp2);
			     }
			     $$ = mpfr_temp;
                           }
;


diamconstant:     function
                           {
			     mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if ($1->nodeType != CONSTANT) {
			       printf(
                      "Warning: the diameter given is not a floating-point constant but an expression to evaluate.\n");
			     }
			     if (!evaluateConstantExpression(*mpfr_temp,($1),tools_precision)) {
			       printf("Warning: the diameter must be an expression that evaluates to a constant.\n");
			       printf("Setting %s = 0 when evaluating the given variable expression.\n",variablename);
			       mpfr_temp2 = (mpfr_t*) malloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp2,tools_precision);
			       mpfr_set_d(*mpfr_temp2,1.0,GMP_RNDN);
			       evaluate(*mpfr_temp, ($1), *mpfr_temp2, tools_precision);
			       mpfr_clear(*mpfr_temp2);
			       free(mpfr_temp2);
			     }
			     $$ = mpfr_temp;
                           }
;




constant: CONSTTOKEN 
                           {
			     mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_temp2 = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,tools_precision);
			     mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDD);
			     mpfr_set_str(*mpfr_temp2,$1,10,GMP_RNDU);
			     if (mpfr_cmp(*mpfr_temp,*mpfr_temp2) != 0) {
			       printf(
                            "Warning: Rounding occured when converting constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printf("If safe computation is needed, try to increase the precision.\n");
			       mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDN);
			     } 
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp2);
			     $$ = mpfr_temp;
			   }
        | PITOKEN 
                           {
			     printf("Warning: The pi constant in the expression will be represented on %d bits\n",
				    (int) tools_precision);
			     mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_const_pi(*mpfr_temp,GMP_RNDN);
			     $$ = mpfr_temp;
                           }
        | ETOKEN 
                           {
			     printf("Warning: The e constant in the expression will be represented on %d bits\n",
				    (int) tools_precision);
			     mpfr_temp = (mpfr_t*) malloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
			     mpfr_exp(*mpfr_temp,*mpfr_temp,GMP_RNDN);
			     $$ = mpfr_temp;
			   }
;

