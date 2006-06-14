%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "expression.h"
#include "chain.h"
#include "main.h"
#include "remez.h"
#include "infnorm.h"
#include "assignment.h"
#include "taylor.h"
#include "integral.h"
#include "worstcase.h"

int yylex();

extern FILE *yyin;
extern char *yytext;

void yyerror(char *message) {
  if ((!feof(yyin)) && (!handlingError)) {
    fprintf(stderr,"Warning: %s on token \"%s\". Will try to continue parsing (expecting \";\"). May leak memory.\n",message,yytext);
  }
}

%}



%union {
	char *value;
        node *tree;
        struct chainStruct *aChain;
        mp_prec_t  precisionval;
        int  pointsnum;
        rangetype rangeval;
        mpfr_t *constantval;
        int degreeval;
        int verbval;
        char *aString;
        FILE *aFile;
	void *other;
};

%token  <value> CONSTTOKEN
%token  <value> DYADICCONSTTOKEN
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
%token  TAYLORTOKEN
%token  FINDZEROSTOKEN
%token  DIRTYINFNORMTOKEN
%token  EVALUATETOKEN
%token  ATTOKEN
%token  NUMERATORTOKEN
%token  DENOMINATORTOKEN
%token  WITHOUTTOKEN
%token  DYADICTOKEN
%token  ONTOKEN
%token  OFFTOKEN
%token  INTEGRALTOKEN
%token  DIRTYINTEGRALTOKEN
%token  STRINGTOKEN
%token  PROOFTOKEN
%token  VERBOSITYTOKEN
%token  WORSTCASETOKEN
%token  WITHTOKEN
%token  INPUTPRECTOKEN
%token  OUTPUTPRECTOKEN
%token  INPUTEXPOTOKEN
%token  EPSILONTOKEN


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
%type <constantval> constantfunction
%type <tree> variable 
%type <tree> term
%type <tree> subterm
%type <tree> primary
%type <degreeval> degree
%type <rangeval> infnorm
%type <aString> lvariable
%type <other> assignment
%type <other> findzeros
%type <constantval> dirtyinfnorm
%type <constantval> dirtyintegral
%type <aString> variableWorkAround
%type <other> evaluate
%type <aChain> rangelist
%type <other> dyadic
%type <rangeval> integral
%type <aString> string
%type <aFile> writefile
%type <aChain> monomials
%type <aChain> degreelist
%type <verbval> verbosity
%type <other> verbosityset
%type <other> worstcase

%%

commands:    QUITTOKEN SEMICOLONTOKEN
                           {
			     $$ = NULL;
			     YYABORT;
                           }
           | command 
                           {
                             $$ = NULL;
			     YYACCEPT;
                           }
;

command:     plot
                           {
			     $$ = NULL;
			   }
           | print        
                           {
                             $$ = NULL;
                           }  
           | dirtyinfnorm  {
	                     printf("uncertified infnorm result: ");
			     printValue(($1),defaultprecision);
			     printf("\n");
			     mpfr_clear(*($1));
			     free(($1));
			     $$ = NULL;
	                   }
           | dirtyintegral {
	                     printf("uncertified integral result: ");
			     printValue(($1),defaultprecision);
			     printf("\n");
			     mpfr_clear(*($1));
			     free(($1));
			     $$ = NULL;
	                   }
           | infnorm       {
	                     printf("infnorm result: ");
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_abs(*($1.a),*($1.a),GMP_RNDN);
			     mpfr_abs(*($1.b),*($1.b),GMP_RNDN);
			     mpfr_max(*mpfr_temp,*($1.a),*($1.b),GMP_RNDU);
			     printValue(mpfr_temp,defaultprecision);
			     printf("\n");
			     mpfr_temp2 = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,defaultprecision);
			     mpfr_sub(*mpfr_temp2,*($1.a),*($1.b),GMP_RNDU);
			     mpfr_abs(*mpfr_temp2,*mpfr_temp2,GMP_RNDN);
			     if (mpfr_zero_p(*mpfr_temp)) {
			       printf("Absolute diameter of confidence interval: ");
			       printValue(mpfr_temp2,defaultprecision);
			       printf("\n");
			     } else {
			       mpfr_div(*mpfr_temp2,*mpfr_temp2,*mpfr_temp,GMP_RNDU);
			       if (mpfr_number_p(*mpfr_temp2)) {
				 printf("Relative diameter of confidence interval: ");
				 printValue(mpfr_temp2,defaultprecision);
				 mpfr_log2(*mpfr_temp2,*mpfr_temp2,GMP_RNDU);
				 double_temp = mpfr_get_d(*mpfr_temp2,GMP_RNDU);
				 printf(" (= 2^(%f))\n",double_temp);
			       }
			     }
			     mpfr_clear(*mpfr_temp);
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp);
			     free(mpfr_temp2);
			     mpfr_clear(*($1.a));
			     mpfr_clear(*($1.b));
			     free($1.a);
			     free($1.b);
	                     $$ = NULL;
	                   }
           | integral      {
	                     printf("integral result: ");
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_add(*mpfr_temp,*($1.a),*($1.b),GMP_RNDU);
			     mpfr_div_2ui(*mpfr_temp,*mpfr_temp,1,GMP_RNDU);
			     printValue(mpfr_temp,defaultprecision);
			     printf("\n");
			     mpfr_temp2 = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,defaultprecision);
			     mpfr_sub(*mpfr_temp2,*($1.a),*($1.b),GMP_RNDU);
			     mpfr_abs(*mpfr_temp2,*mpfr_temp2,GMP_RNDN);
			     mpfr_div_2ui(*mpfr_temp2,*mpfr_temp2,1,GMP_RNDN);
			     if (mpfr_zero_p(*mpfr_temp)) {
			       printf("Absolute diameter of confidence interval: ");
			       printValue(mpfr_temp2,defaultprecision);
			       printf("\n");
			     } else {
			       mpfr_div(*mpfr_temp2,*mpfr_temp2,*mpfr_temp,GMP_RNDU);
			       if (mpfr_number_p(*mpfr_temp2)) {
				 printf("Relative diameter of confidence interval: ");
				 mpfr_abs(*mpfr_temp2,*mpfr_temp2,GMP_RNDN);
				 printValue(mpfr_temp2,defaultprecision);
				 mpfr_log2(*mpfr_temp2,*mpfr_temp2,GMP_RNDU);
				 double_temp = mpfr_get_d(*mpfr_temp2,GMP_RNDU);
				 printf(" (= 2^(%f))\n",double_temp);
			       }
			     }
			     mpfr_clear(*mpfr_temp);
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp);
			     free(mpfr_temp2);
			     mpfr_clear(*($1.a));
			     mpfr_clear(*($1.b));
			     free($1.a);
			     free($1.b);
	                     $$ = NULL;
	                   }
           | evaluate      {
	                     $$ = NULL;
	                   }
           | worstcase     {
	                     $$ = NULL;
	                   }
           | dyadic SEMICOLONTOKEN  {
	                     $$ = NULL;
	                   }
           | verbosityset SEMICOLONTOKEN {
	                     $$ = NULL;
	                   }
           | findzeros     {
	                     $$ = NULL;
	                   }
	   | precision SEMICOLONTOKEN 
                           {
			     tools_precision = $1;
			     defaultprecision = $1;
			     printf("Default precision has been set to %d bits.\n",(int) defaultprecision);
                             $$ = NULL;
                           }
	   | points SEMICOLONTOKEN 
                           {
			     defaultpoints = $1;
			     printf("Default point number has been set to %d.\n",(int) defaultpoints);
                             $$ = NULL;
                           }
           | assignment SEMICOLONTOKEN
                           {
			     $$ = NULL;
			   }
           | error SEMICOLONTOKEN
                           {
			     handlingError = 0;
			     $$ = NULL;
                           }
;

dyadic:      DYADICTOKEN EQUALTOKEN ONTOKEN 
                           {
			     printf("Dyadic number output activated.\n");
			     dyadic = 1;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN OFFTOKEN
                           {
			     printf("Dyadic number output deactivated.\n");
			     dyadic = 0;
			     $$ = NULL;
                           }
;

verbosityset:  VERBOSITYTOKEN EQUALTOKEN verbosity
                           {
			     printf("Verbosity set to level %d.\n",($3));
			     verbosity = ($3);
			     $$ = NULL;
                           }
;


assignment:  lvariable EQUALTOKEN function 
                           {
			     if ((variablename != NULL) && (strcmp(variablename,($1)) == 0)) {
			       printMessage(1,"Warning: the identifer \"%s\" is already bound as the current variable. It cannot be assigned.\n",($1));
			       printMessage(1,"The last command will have no effect.\n");
			     } else {
			       if (containsEntry(symbolTable,($1))) {
				 printMessage(1,"Warning: the identifier \"%s\" is already assigned. It cannot be reassigned.\n",($1));
				 printMessage(1,"The last command will have no effect.\n");
			       } else {
				 symbolTable = addEntry(symbolTable,($1),($3));
			       }
			     }
			     free(($1));
			     free_memory(($3));
			     $$ = NULL;
                           }
;     

evaluate:    EVALUATETOKEN function INTOKEN range SEMICOLONTOKEN 
                           {
			     range_temp.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     range_temp.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*(range_temp.a),defaultprecision);
			     mpfr_init2(*(range_temp.b),defaultprecision);
			     evaluateRangeFunction(range_temp, ($2), ($4), defaultprecision);
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) == 0) {
			       printValue(range_temp.a,defaultprecision);
			       printf("\n");
			     } else {
			       printf("[");
			       printValue(range_temp.a,defaultprecision);
			       printf(";");
			       printValue(range_temp.b,defaultprecision);
			       printf("]\n");
			     }
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     mpfr_clear(*(range_temp.a));
			     mpfr_clear(*(range_temp.b));
			     free(range_temp.a);
			     free(range_temp.b);
			     $$ = NULL;
			   }
           | EVALUATETOKEN function ATTOKEN constantfunction SEMICOLONTOKEN 
                           {
			     range_temp.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     range_temp.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*(range_temp.a),defaultprecision);
			     mpfr_init2(*(range_temp.b),defaultprecision);
			     range_temp2.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     range_temp2.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*(range_temp2.a),defaultprecision);
			     mpfr_init2(*(range_temp2.b),defaultprecision);
			     mpfr_set(*(range_temp2.a),*($4),GMP_RNDD);
			     mpfr_set(*(range_temp2.b),*($4),GMP_RNDU);
			     evaluateRangeFunction(range_temp, ($2), range_temp2, defaultprecision);
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) == 0) {
			       printValue(range_temp.a,defaultprecision);
			       printf("\n");
			     } else {
			       printf("[");
			       printValue(range_temp.a,defaultprecision);
			       printf(";");
			       printValue(range_temp.b,defaultprecision);
			       printf("]\n");
			     }
			     mpfr_clear(*(range_temp.a));
			     mpfr_clear(*(range_temp.b));
			     free(range_temp.a);
			     free(range_temp.b);
			     mpfr_clear(*(range_temp2.a));
			     mpfr_clear(*(range_temp2.b));
			     free(range_temp2.a);
			     free(range_temp2.b);
			     mpfr_clear(*($4));
			     free(($4));
			     $$ = NULL;
			   }

;


worstcase:   WORSTCASETOKEN function WITHTOKEN INPUTPRECTOKEN EQUALTOKEN constantfunction COMMATOKEN INPUTEXPOTOKEN EQUALTOKEN range COMMATOKEN OUTPUTPRECTOKEN EQUALTOKEN constantfunction COMMATOKEN EPSILONTOKEN EQUALTOKEN constantfunction SEMICOLONTOKEN
                           {
			     /* function $2
                                inputprec $6
				outputprec $14
				inputexpo $10
				epsilon $18
			     */
			     printWorstCases(($2), *($6), ($10), *($14), *($18), tools_precision);
			     free_memory($2);
			     mpfr_clear(*($6));
			     mpfr_clear(*($14));
			     mpfr_clear(*($18));
			     free($6);
			     free($14);
			     free($18);
			     mpfr_clear(*(($10).a));
			     mpfr_clear(*(($10).b));
			     free(($10).a);
			     free(($10).b);
			     $$ = NULL;
			   }
;



findzeros:   FINDZEROSTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     chain_temp = findZerosFunction($2,$4,defaultprecision,*mpfr_temp);
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     if (chain_temp == NULL) {
			       printf("The function has no zeros in the interval.\n");
			     } else {
			       printf("All zeros of the given function are contained in:\n");
			       while (chain_temp != NULL) {
				 printf("[");
				 printValue(((rangetype *) (chain_temp->value))->a,defaultprecision);
				 printf(";");
				 printValue(((rangetype *) (chain_temp->value))->b,defaultprecision);
				 printf("]\n");
				 mpfr_clear(*(((rangetype *) (chain_temp->value))->a));
				 mpfr_clear(*(((rangetype *) (chain_temp->value))->b));
				 free(((rangetype *) (chain_temp->value))->a);
				 free(((rangetype *) (chain_temp->value))->b);
				 free(chain_temp->value);
				 chain_temp2 = chain_temp->next;
				 free(chain_temp);
				 chain_temp = chain_temp2;
			       }
			       printf("\n");
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = NULL;
                           }
                 | FINDZEROSTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant SEMICOLONTOKEN
                           {
			     chain_temp = findZerosFunction($2,$4,defaultprecision,*($8));
			     mpfr_clear(*($8));
			     free($8);
			     if (chain_temp == NULL) {
			       printf("The function has no zeros in the interval.\n");
			     } else {
			       printf("All zeros of the given function are contained in:\n");
			       while (chain_temp != NULL) {
				 printf("[");
				 printValue(((rangetype *) (chain_temp->value))->a,defaultprecision);
				 printf(";");
				 printValue(((rangetype *) (chain_temp->value))->b,defaultprecision);
				 printf("]\n");
				 mpfr_clear(*(((rangetype *) (chain_temp->value))->a));
				 mpfr_clear(*(((rangetype *) (chain_temp->value))->b));
				 free(((rangetype *) (chain_temp->value))->a);
				 free(((rangetype *) (chain_temp->value))->b);
				 free(chain_temp->value);
				 chain_temp2 = chain_temp->next;
				 free(chain_temp);
				 chain_temp = chain_temp2;
			       }
			       printf("\n");
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = NULL;
                           }
;


infnorm:     INFNORMTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = infnorm($2,$4,NULL,defaultprecision,*mpfr_temp,NULL);
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
			     range_temp = infnorm($2,$4,NULL,defaultprecision,*($8),NULL);
			     mpfr_clear(*($8));
			     free($8);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = infnorm($2,$4,$6,defaultprecision,*mpfr_temp,NULL);
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     chain_temp = $6;
			     while (chain_temp != NULL) {
			       mpfr_clear(*(((rangetype *) chain_temp->value)->a));
			       mpfr_clear(*(((rangetype *) chain_temp->value)->b));
			       free(((rangetype *) chain_temp->value)->a);
			       free(((rangetype *) chain_temp->value)->b);
			       free(chain_temp->value);
			       chain_temp2 = chain_temp->next; 
			       free(chain_temp);
			       chain_temp = chain_temp2;
			     }
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant SEMICOLONTOKEN
	                   {
			     range_temp = infnorm($2,$4,$6,defaultprecision,*($10),NULL);
			     mpfr_clear(*($10));
			     free($10);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     chain_temp = $6;
			     while (chain_temp != NULL) {
			       mpfr_clear(*(((rangetype *) chain_temp->value)->a));
			       mpfr_clear(*(((rangetype *) chain_temp->value)->b));
			       free(((rangetype *) chain_temp->value)->a);
			       free(((rangetype *) chain_temp->value)->b);
			       free(chain_temp->value);
			       chain_temp2 = chain_temp->next; 
			       free(chain_temp);
			       chain_temp = chain_temp2;
			     }
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range COMMATOKEN PROOFTOKEN EQUALTOKEN writefile SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = infnorm($2,$4,NULL,defaultprecision,*mpfr_temp,($8));
			     fclose(($8));
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant COMMATOKEN PROOFTOKEN EQUALTOKEN writefile SEMICOLONTOKEN
	                   {
			     range_temp = infnorm($2,$4,NULL,defaultprecision,*($8),($12));
			     mpfr_clear(*($8));
			     fclose(($12));
			     free($8);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN PROOFTOKEN EQUALTOKEN writefile SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = infnorm($2,$4,$6,defaultprecision,*mpfr_temp,($10));
			     fclose(($10));
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     chain_temp = $6;
			     while (chain_temp != NULL) {
			       mpfr_clear(*(((rangetype *) chain_temp->value)->a));
			       mpfr_clear(*(((rangetype *) chain_temp->value)->b));
			       free(((rangetype *) chain_temp->value)->a);
			       free(((rangetype *) chain_temp->value)->b);
			       free(chain_temp->value);
			       chain_temp2 = chain_temp->next; 
			       free(chain_temp);
			       chain_temp = chain_temp2;
			     }
			     $$ = range_temp;
                           }
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant COMMATOKEN PROOFTOKEN EQUALTOKEN writefile SEMICOLONTOKEN
	                   {
			     range_temp = infnorm($2,$4,$6,defaultprecision,*($10),($14));
			     fclose(($14));
			     mpfr_clear(*($10));
			     free($10);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     chain_temp = $6;
			     while (chain_temp != NULL) {
			       mpfr_clear(*(((rangetype *) chain_temp->value)->a));
			       mpfr_clear(*(((rangetype *) chain_temp->value)->b));
			       free(((rangetype *) chain_temp->value)->a);
			       free(((rangetype *) chain_temp->value)->b);
			       free(chain_temp->value);
			       chain_temp2 = chain_temp->next; 
			       free(chain_temp);
			       chain_temp = chain_temp2;
			     }
			     $$ = range_temp;
                           }
;


integral:     INTEGRALTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     range_temp = integral($2,$4,defaultprecision,*mpfr_temp);
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = range_temp;
                           }
           | INTEGRALTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant SEMICOLONTOKEN
	                   {
			     range_temp = integral($2,$4,defaultprecision,*($8));
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

dirtyinfnorm: DIRTYINFNORMTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     uncertifiedInfnorm(*mpfr_temp,($2),*(($4).a),*(($4).b),defaultpoints,defaultprecision);
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     $$ = mpfr_temp;
			   }
             | DIRTYINFNORMTOKEN function INTOKEN range COMMATOKEN points SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     uncertifiedInfnorm(*mpfr_temp,($2),*(($4).a),*(($4).b),($6),defaultprecision);
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     $$ = mpfr_temp;
			   }
;

dirtyintegral: DIRTYINTEGRALTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     uncertifiedIntegral(*mpfr_temp,($2),*(($4).a),*(($4).b),defaultpoints,defaultprecision);
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     $$ = mpfr_temp;
			   }
             | DIRTYINTEGRALTOKEN function INTOKEN range COMMATOKEN points SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     uncertifiedIntegral(*mpfr_temp,($2),*(($4).a),*(($4).b),($6),defaultprecision);
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     $$ = mpfr_temp;
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
			     $$ = NULL;
                           }
           | PRINTTOKEN string SEMICOLONTOKEN
                           {
			     printf("%s\n",($2));
			     free(($2));
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
			     $$ = NULL;
			   }
;

precision:  PRECTOKEN EQUALTOKEN CONSTTOKEN 
                           {
			     tools_precision = strtol($3,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: A precision must be integer. Will set precision to 12 bits.\n");
			       tools_precision = 12;
			     }
			     if (tools_precision < 12) {
			       printMessage(1,"Warning: The tools precision must be at least 12 bits.\nPrecision has been increased to 12.\n");
			       tools_precision = 12;
			     }
			     $$ = tools_precision;
                           }
;

points:  POINTSTOKEN EQUALTOKEN CONSTTOKEN
                           {
			     points = (unsigned long int) strtol($3,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: The number of points to be plotted must be integer. Will print 10 points.\n");
			       points = 10;
			     }
			     if (points < 3) {
			       printMessage(1,"Warning: at least 3 points must be considered. Will increase their number to 3.\n");
			       points = 3;
			     }
			     $$ = points;                           
                           }
;

degree:  CONSTTOKEN
                           {
			     int_temp = (int) strtol($1,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: the degree of a polynomial must be integer. Will do degree 3.\n");
			       int_temp = 3;
			     }
			     if (int_temp < 0) {
			       printMessage(1,"The degree of a polynomial must be a positive number. Will do degree 3.\n");
			       int_temp = 3;
			     }
			     $$ = int_temp;                           
                           }
;

verbosity:  CONSTTOKEN
                           {
			     int_temp = (int) strtol($1,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: the tool's verbosity must be an integer value. Will set verbosity 1.\n");
			       int_temp = 1;
			     }
			     if (int_temp < 0) {
			       printMessage(1,"Warning: The tool's verbosity must be a positive value. Will set verbosity 1.\n");
			       int_temp = 1;
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
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ADD;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }										
			|	function MINUSTOKEN term			
		           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SUB;
			     temp_node->child1 = $1;
			     temp_node->child2 = $3;
			     $$ = temp_node;
                           }				   			
			|	MINUSTOKEN term			
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
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
			      temp_node = (node*) safeMalloc(sizeof(node));
			      mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
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
			|       REMEZTOKEN LPARTOKEN function COMMATOKEN monomials COMMATOKEN range RPARTOKEN
                           {
			      temp_node = remez($3, $5, *($7.a), *($7.b), tools_precision);
			      free_memory($3);
			      mpfr_clear(*($7.a));
			      mpfr_clear(*($7.b));
			      free($7.a);
			      free($7.b);
			      freeChain($5,freeIntPtr);
			      $$ = temp_node;
                           }
                        |       TAYLORTOKEN LPARTOKEN function COMMATOKEN degree COMMATOKEN function RPARTOKEN
                           {
			      temp_node = taylor(($3),($5),($7),tools_precision);
			      free_memory(($3));
			      free_memory(($7));
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
                        |       NUMERATORTOKEN LPARTOKEN function RPARTOKEN 
                           {
			     if (!getNumeratorDenominator(&temp_node,&temp_node2,($3))) {
			       printMessage(1,"Warning: the expression given is not a fraction. ");
			       printMessage(1,"Will consider it as a fraction with denominator 1.\n");
			     } else {
			       free_memory(temp_node2);
			     }
			     $$ = temp_node;
			   }
                        |       DENOMINATORTOKEN LPARTOKEN function RPARTOKEN 
                           {
			     if (!getNumeratorDenominator(&temp_node2,&temp_node,($3))) {
			       printMessage(1,"Warning: the expression given is not a fraction. ");
			       printMessage(1,"Will consider it as a fraction with denominator 1.\n");
			       mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp,defaultprecision);
			       mpfr_set_d(*mpfr_temp,1.0,GMP_RNDN);
			       temp_node = (node *) safeMalloc(sizeof(node));
			       temp_node->nodeType = CONSTANT;
			       temp_node->value = mpfr_temp;
			     } 
			     free_memory(temp_node2);
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
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SQRT;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       EXPTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = EXP;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOGTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG2TOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_2;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG10TOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_10;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = COS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINTOKEN LPARTOKEN function RPARTOKEN
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ASIN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ACOS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ATAN;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       SINHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = SINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       COSHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = COSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TANHTOKEN LPARTOKEN function RPARTOKEN    
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ASINHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ASINH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ACOSHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ACOSH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ATANHTOKEN LPARTOKEN function RPARTOKEN   
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ATANH;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ABSTOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ABS;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLETOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       DOUBLEDOUBLETOKEN LPARTOKEN function RPARTOKEN     			  		
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       TRIPLEDOUBLETOKEN LPARTOKEN function RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = TRIPLEDOUBLE;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
;

monomials:                      degree
                           {
			     $$ = makeIntPtrChain(($1));
			   }
                        |       LBRACKETTOKEN degreelist RBRACKETTOKEN
                           {
			     $$ = $2;
			   }
;

degreelist:                     degree 
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = ($1);
			     chain_temp = addElement(NULL,intTempPtr);
			     $$ = chain_temp;
			   }
                         |      degreelist COMMATOKEN degree
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = ($3);
			     chain_temp = addElement(($1),intTempPtr);
			     $$ = chain_temp;
			   }
;



term:				subterm						
			   {
			     $$ = $1;
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
			|	LPARTOKEN function RPARTOKEN			
			   {
			     $$ = $2;
                           }	
                        |       prefixfunction
                           {
                             $$ = $1;
                           }
;

variableWorkAround: VARIABLETOKEN 
                           {
			     temp_string = (char *) safeCalloc(strlen(currentVariable)+1,sizeof(char));
			     strcpy(temp_string,currentVariable);
			     $$ = temp_string;
                           }
;


variable: VARIABLETOKEN
                           {
			     if (!containsEntry(symbolTable,currentVariable)) {
			       if (variablename==NULL) {
				 variablename = (char *) safeCalloc(strlen(currentVariable)+1,sizeof(char));
				 strcpy(variablename,currentVariable);
			       }
			       if (strcmp(variablename,currentVariable)!=0) {
				 printMessage(1,"Warning: the identifier \"%s\" is neither bound by assignment nor equal to the bound current variable.\n",currentVariable);
				 printMessage(1,"Will interpret \"%s\" as \"%s\".\n",currentVariable,variablename);
			       }
			       temp_node = (node*) safeMalloc(sizeof(node));
			       temp_node->nodeType = VARIABLE;
			     } else {
			       temp_node = getEntry(symbolTable,currentVariable);
			     }
			     $$ = temp_node;
                           }
                 | variableWorkAround LPARTOKEN function RPARTOKEN
                           {
			     if ((variablename != NULL) && (strcmp(variablename,($1)) == 0)) {
			       printMessage(1,"Warning: the identifier \"%s\" is equal to the already bound current variable.\n",
				      ($1));
			       printMessage(1,"Will interpret \"%s()\" as the identity function.\n",($1));
			       temp_node = ($3);
			     } else {
			       if (!containsEntry(symbolTable,($1))) {
				 printMessage(1,"Warning: the identifier \"%s\" is not bound by assignment.\n",($1));
				 printMessage(1,"Will interpret \"%s()\" as the identity function.\n",($1));
				 temp_node = ($3);
			       } else {
				 temp_node2 = getEntry(symbolTable,($1));
				 temp_node = substitute(temp_node2,($3));
				 free_memory(temp_node2);
				 free_memory(($3));
			       }
			     }
			     free(($1));
			     $$ = temp_node;
                           }
;

lvariable: VARIABLETOKEN
                           {
			     temp_string = (char *) safeCalloc(strlen(currentVariable)+1,sizeof(char));
			     strcpy(temp_string,currentVariable);
			     $$ = temp_string;
                           }
;

string: STRINGTOKEN
                           {
			     temp_string = (char *) safeCalloc(strlen(currentString)+1,sizeof(char));
			     demaskString(temp_string,currentString);
			     $$ = temp_string;
                           }
;

writefile: string     
                           {
			     temp_fd = fopen(($1),"w");
			     if (temp_fd == NULL) {
			       fprintf(stderr,"Error: the file \"%s\" could not be opened for writing: ",($1));
			       fprintf(stderr,"\"%s\".\n",strerror(errno));
			       free(($1));
			       recoverFromError();
			     }
			     free(($1));
			     $$ = temp_fd;
                           }
;


rangelist:         range                      {
                                                rangeTempPtr = (rangetype *) safeMalloc(sizeof(rangetype));
						rangeTempPtr->a = ($1).a;
						rangeTempPtr->b = ($1).b;
						$$ = addElement(NULL,(void *) rangeTempPtr);
                                              }
                 | rangelist COMMATOKEN range {
		                                rangeTempPtr = (rangetype *) safeMalloc(sizeof(rangetype));
						rangeTempPtr->a = ($3).a;
						rangeTempPtr->b = ($3).b;
						$$ = addElement(($1),(void *) rangeTempPtr);
		                              }
;

range:  LBRACKETTOKEN rangeconstant SEMICOLONTOKEN rangeconstant RBRACKETTOKEN
                           {
                             range_temp.a = $2;
			     range_temp.b = $4;
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) > 0) {
			       printMessage(1,"Warning: the range bounds are not correctly ordered. Will revert them.\n");
			       mpfr_swap(*(range_temp.a),*(range_temp.b));
		             }
			     $$ = range_temp;
                           }
      | LBRACKETTOKEN rangeconstant COMMATOKEN rangeconstant RBRACKETTOKEN
                           {
                             range_temp.a = $2;
			     range_temp.b = $4;
			     if (mpfr_cmp(*(range_temp.a),*(range_temp.b)) > 0) {
			       printMessage(1,"Warning: the range bounds are not correctly ordered. Will revert them.\n");
			       mpfr_swap(*(range_temp.a),*(range_temp.b));
		             }
			     $$ = range_temp;
                           }
;

constantfunction:  function
                           {
			     temp_node = simplifyTreeErrorfree($1);
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (temp_node->nodeType != CONSTANT) {
			       printMessage(1,
                      "Warning: the function given is not a floating-point constant but an expression to evaluate.\n");
			     }
			     if (!evaluateConstantExpression(*mpfr_temp,temp_node,tools_precision)) {
			       printMessage(1,"Warning: functions in this context must be expressions that evaluate to constants.\n");
			       printMessage(1,"Setting %s = 0 when evaluating the given variable expression.\n",variablename);
			       mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp2,tools_precision);
			       mpfr_set_d(*mpfr_temp2,1.0,GMP_RNDN);
			       evaluate(*mpfr_temp, ($1), *mpfr_temp2, tools_precision);
			       mpfr_clear(*mpfr_temp2);
			       free(mpfr_temp2);
			     }
			     free_memory(temp_node);
			     free_memory($1);
			     $$ = mpfr_temp;
                           }
;

rangeconstant:     function
                           {
			     temp_node = simplifyTreeErrorfree($1);
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (temp_node->nodeType != CONSTANT) {
			       printMessage(1,
                      "Warning: the range bound given is not a floating-point constant but an expression to evaluate.\n");
			     }
			     if (!evaluateConstantExpression(*mpfr_temp,temp_node,tools_precision)) {
			       printMessage(1,"Warning: range bounds must be expressions that evaluate to constants.\n");
			       printMessage(1,"Setting %s = 0 when evaluating the given variable expression.\n",variablename);
			       mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp2,tools_precision);
			       mpfr_set_d(*mpfr_temp2,1.0,GMP_RNDN);
			       evaluate(*mpfr_temp, ($1), *mpfr_temp2, tools_precision);
			       mpfr_clear(*mpfr_temp2);
			       free(mpfr_temp2);
			     }
			     free_memory(temp_node);
			     free_memory($1);
			     $$ = mpfr_temp;
                           }
;


diamconstant:     function
                           {
			     temp_node = simplifyTreeErrorfree($1);
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (temp_node->nodeType != CONSTANT) {
			       printMessage(1,
                      "Warning: the diameter given is not a floating-point constant but an expression to evaluate.\n");
			     }
			     if (!evaluateConstantExpression(*mpfr_temp,temp_node,tools_precision)) {
			       printMessage(1,"Warning: diameters must be expressions that evaluate to constants.\n");
			       printMessage(1,"Setting %s = 0 when evaluating the given variable expression.\n",variablename);
			       mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*mpfr_temp2,tools_precision);
			       mpfr_set_d(*mpfr_temp2,1.0,GMP_RNDN);
			       evaluate(*mpfr_temp, ($1), *mpfr_temp2, tools_precision);
			       mpfr_clear(*mpfr_temp2);
			       free(mpfr_temp2);
			     }
			     free_memory(temp_node);
			     free_memory($1);
			     $$ = mpfr_temp;
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
                            "Warning: Rounding occured when converting constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			       mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDN);
			     } 
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp2);
			     $$ = mpfr_temp;
			   }
        | DYADICCONSTTOKEN {
                             mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (!readDyadic(*mpfr_temp,$1)) {
			       printMessage(1,
                            "Warning: Rounding occured when converting the dyadic constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			     }
			     if (!mpfr_number_p(*mpfr_temp)) {
			       fprintf(stderr,
			  "Error: overflow occured during the conversion of the dyadic constant \"%s\". Will abort the computation.\n",$1);
			       recoverFromError();
			     }
			     $$ = mpfr_temp;
	                   }
        | PITOKEN 
                           {
			     printMessage(1,"Warning: The pi constant in the expression will be represented on %d bits\n",
				    (int) tools_precision);
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_const_pi(*mpfr_temp,GMP_RNDN);
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

