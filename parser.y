%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pari/pari.h>
#include "expression.h"
#include "chain.h"
#include "main.h"
#include "remez.h"
#include "infnorm.h"
#include "assignment.h"
#include "taylor.h"
#include "integral.h"
#include "worstcase.h"
#include "fpminimax.h"
#include "implement.h"
#include "double.h"
#include "pari_utils.h"
#include "plot.h"
#include "external.h"

int yylex();

extern FILE *yyin;
extern char *yytext;
extern ulong ltop;

void yyerror(char *message) {
  if ((!feof(yyin)) && (!handlingError)) {
    fprintf(stderr,"Warning: %s on token \"%s\". Will try to continue parsing (expecting \";\"). May leak memory.\n",message,yytext);
  }
}

%}

%expect 1

%union {
	char *value;
        node *tree;
        struct chainStruct *aChain;
        struct doubleChainStruct *aDoubleChain;
        struct formatStruct *aFormat;
        struct errorStruct *anError;
        struct pointsStruct *aPoint;
        mp_prec_t  precisionval;
        int  pointsnum;
        rangetype rangeval;
        mpfr_t *constantval;
        int degreeval;
        int verbval;
        int anInteger;
        char *aString;
        FILE *aFile;
	void *other;
};

%token  <value> CONSTTOKEN
%token  <value> DYADICCONSTTOKEN
%token  <value> BINARYCONSTTOKEN
%token  <value> HEXCONSTTOKEN
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
%token	ERFTOKEN         
%token	ERFCTOKEN         
%token	LOG1PTOKEN         
%token	EXPM1TOKEN         
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
%token  CANONICALTOKEN
%token  PLOTTOKEN
%token  INFNORMTOKEN
%token  REMEZTOKEN
%token  DIAMTOKEN
%token  DOUBLETOKEN
%token  DOUBLEDOUBLETOKEN
%token  TRIPLEDOUBLETOKEN
%token  DOUBLEEXTENDEDTOKEN
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
%token  POWERSTOKEN
%token  BINARYTOKEN
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
%token  OUTPUTTOKEN
%token  LEFTANGLETOKEN
%token  RIGHTANGLEUNDERSCORETOKEN
%token  RIGHTANGLEDOTTOKEN
%token  RIGHTANGLETOKEN
%token  SUBSTITUTETOKEN
%token  FPMINIMAXTOKEN
%token  MITOKEN        
%token  TITOKEN        
%token  ABSOLUTETOKEN
%token  RELATIVETOKEN  
%token  WEIGHTTOKEN    
%token  EQUITOKEN      
%token  CHEBTOKEN      
%token  DOTSTOKEN      
%token  IMPLEMENTPOLYTOKEN      
%token  NAMETOKEN
%token  VARIABLEMETATOKEN      
%token  ASTOKEN
%token  CHECKINFNORMTOKEN
%token	BOUNDEDTOKEN     
%token	BYTOKEN          
%token  TAYLORRECURSIONSTOKEN
%token  PRINTHEXATOKEN
%token  PRINTBINARYTOKEN
%token  ROUNDCOEFFICIENTSTOKEN
%token  HONORCOEFFPRECTOKEN
%token  RESTARTTOKEN
%token  TESTPARITOKEN
%token  FPFINDZEROSTOKEN
%token  ZERODENOMINATORSTOKEN
%token  ISEVALUABLETOKEN
%token  EVALUATEACCURATETOKEN                   
%token  EXCLAMATIONTOKEN
%token  ACCURATEINFNORMTOKEN
%token  BITSTOKEN
%token  FILETOKEN
%token  POSTSCRIPTTOKEN
%token  PDFTOKEN     
%token  POSTSCRIPTFILETOKEN
%token  PDFFILETOKEN       
%token  PRINTEXPANSIONTOKEN
%token  BASHEXECUTETOKEN
%token  EXTERNALPLOTTOKEN
%token  PERTURBTOKEN
%token  TOTOKEN
%token  COEFFTOKEN
%token  SUBPOLYTOKEN
%token  QUESTIONMARKTOKEN
%token  SEARCHGALTOKEN
%token  STEPSTOKEN
%token  RATIONALAPPROXTOKEN
%token  FALSEQUITTOKEN
%token  WRITETOKEN
%token  ASCIIPLOTTOKEN
%token  DOLLARTOKEN

%type <other> commands
%type <other> command
%type <other> plot
%type <other> asciiplot
%type <other> print
%type <other> write
%type <precisionval> precision
%type <pointsnum> points
%type <tree> function
%type <tree> prefixfunction
%type <rangeval> range
%type <rangeval> directrange
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
%type <other> fpfindzeros
%type <other> zerodenominators
%type <constantval> dirtyinfnorm
%type <constantval> dirtyintegral
%type <aString> variableWorkAround
%type <rangeval> evaluate
%type <aChain> rangelist
%type <other> dyadic
%type <other> canonical
%type <rangeval> integral
%type <aString> string
%type <aFile> writefile
%type <aFile> appendfile
%type <aChain> monomials
%type <aChain> degreelist
%type <verbval> verbosity
%type <anInteger> taylorrecursionsvalue
%type <other> verbosityset
%type <other> worstcase
%type <rangeval> commandfunction
%type <aDoubleChain> monomialsAndPrecision
%type <aFormat> format
%type <aChain> formatlist
%type <anError> errordefinition
%type <aPoint> pointsdefinition
%type <aChain> pointslist
%type <anInteger> integer
%type <tree> fpminimax
%type <tree> implementpoly
%type <anInteger> variableformat
%type <anInteger> checkinfnorm
%type <other> taylorrecursions
%type <other> printHexa
%type <other> printBinary
%type <tree> roundcoefficients
%type <aChain> expansionFormats
%type <anInteger> expansionFormat
%type <aChain> expansionFormatList
%type <other> restart
%type <other> testpari
%type <other> autoprint
%type <other> printlist
%type <other> printelem
%type <other> writelist
%type <other> writeelem
%type <aString> fwritelist
%type <aString> fwriteelem
%type <other> isevaluable
%type <other> evaluateaccurate
%type <constantval> accurateinfnorm
%type <constantval> evaluateaccuratecommandfunction
%type <aChain> functionlist
%type <anInteger> plottype
%type <other> printexpansion
%type <anInteger> bashexecute
%type <other> externalplot
%type <anInteger> externalplotmode
%type <aChain> integerlist
%type <rangeval> printableRange
%type <rangeval> symbolRange
%type <constantval> searchGal
%type <aString> directString


%%

commands:    QUITTOKEN SEMICOLONTOKEN
                           {
			     $$ = NULL;
			     YYABORT;
                           }
           | FALSEQUITTOKEN SEMICOLONTOKEN
                           {
			     $$ = NULL;
			     YYACCEPT;
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
           | asciiplot
                           {
			     $$ = NULL;
			   }
           | print        
                           {
                             $$ = NULL;
                           }  
           | write        
                           {
                             $$ = NULL;
                           }  
           | autoprint   
                           {
			     $$ = NULL;
			   }
           | printHexa 
                           {
			     $$ = NULL;
			   }
           | printBinary 
                           {
			     $$ = NULL;
			   }
           | printexpansion 
                           {
			     $$ = NULL;
			   }
           | dirtyinfnorm  SEMICOLONTOKEN {
	                     printf("uncertified infnorm result: ");
			     printValue(($1),defaultprecision);
			     printf("\n");
			     mpfr_clear(*($1));
			     free(($1));
			     $$ = NULL;
	                   }
           | dirtyintegral SEMICOLONTOKEN {
	                     printf("uncertified integral result: ");
			     printValue(($1),defaultprecision);
			     printf("\n");
			     mpfr_clear(*($1));
			     free(($1));
			     $$ = NULL;
	                   }
           | accurateinfnorm  SEMICOLONTOKEN {
	                     if (!mpfr_number_p(*($1))) {
			       printf("The infnorm value could not be computed exactly enough.\n");
	                     } else {
	                       printf("Faithful rounded-up infnorm result on %d bits:\n",(int) mpfr_get_prec(*($1)));
			       printMpfr(*($1));
			     } 
			     mpfr_clear(*($1));
			     free(($1));
			     $$ = NULL;
	                   }
           | infnorm SEMICOLONTOKEN {
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
           | integral SEMICOLONTOKEN {
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
           | searchGal SEMICOLONTOKEN {
	                     if (!mpfr_number_p(*($1))) {
			       printf("The Gal good approximation search has given no result.\n");
			     } else { 
			       printf("Found the following appropriate well approximating point:\n");
			       printMpfr(*($1));
			     }
			     mpfr_clear(*($1));
			     free($1);
	                     $$ = NULL;
	                   }
           | evaluate SEMICOLONTOKEN      
                            {
			      if ((mpfr_cmp(*($1.a),*($1.b)) == 0) && (mpfr_number_p(*($1.a)))) {
				printValue($1.a,defaultprecision);
				printf("\n");
			      } else {
				printf("[");
				printValue($1.a,defaultprecision);
				printf(";");
				printValue($1.b,defaultprecision);
				printf("]\n");
			      }
			      mpfr_clear(*($1.a));
			      mpfr_clear(*($1.b));
			      free($1.a);
			      free($1.b);
			      $$ = NULL;
	                   }
           | evaluateaccurate SEMICOLONTOKEN {
	                      $$ = NULL;
	                   }
           | isevaluable SEMICOLONTOKEN 
                           {
			     $$ = NULL;
			   }
           | worstcase     {
	                     $$ = NULL;
	                   }
           | dyadic SEMICOLONTOKEN  {
	                     $$ = NULL;
	                   }
           | DYADICTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN  {
	                     switch (dyadic) {	     
			     case 0:
			       printf("Dyadic number output is deactivated.\n");
			       break;
			     case 1:
			       printf("Dyadic number output is activated.\n");
			       break;
			     case 2:
			       printf("Dyadic number output is activated with power of 2 notation.\n");
			       break;
			     case 3:
			       printf("Dyadic number output is activated with binary notation.\n");
			       break;
			     default:
			       printf("Dyadic number output in unknown state.\n");
			     }
	                     $$ = NULL;	                   
	                   }
           | canonical SEMICOLONTOKEN  {
	                     $$ = NULL;
	                   }
           | CANONICALTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN  {
	                     if (canonical) {
			       printf("Canonical autoprint output is activated.\n");
			     } else {
			       printf("Canonical autoprint output is deactivated.\n");
			     }
	                     $$ = NULL;	                   
	                   }
           | taylorrecursions SEMICOLONTOKEN {
	                     $$ = NULL;
	                   }
           | TAYLORRECURSIONSTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN {
			     printf("The number of recursions for the Taylor evaluation is set to %d.\n",taylorrecursions);	                     
	                     $$ = NULL;
	                   }
           | verbosityset SEMICOLONTOKEN {
	                     $$ = NULL;
	                   }
           | VERBOSITYTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN
                           {
			     printf("Verbosity set to level %d.\n",verbosity);
			     $$ = NULL;
                           }
           | findzeros     {
	                     $$ = NULL;
	                   }
           | fpfindzeros   {
	                     $$ = NULL;
	                   }
           | zerodenominators {
	                     $$ = NULL;
	                   }
	   | precision SEMICOLONTOKEN 
                           {
			     tools_precision = $1;
			     defaultprecision = $1;
			     printf("Default precision has been set to %d bits.\n",(int) defaultprecision);
                             $$ = NULL;
                           }
	   | precision EXCLAMATIONTOKEN SEMICOLONTOKEN 
                           {
			     tools_precision = $1;
			     defaultprecision = $1;
                             $$ = NULL;
                           }
	   | PRECTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN 
                           {
			     printf("Default precision is set to %d bits.\n",(int) defaultprecision);
                             $$ = NULL;
                           }
	   | points SEMICOLONTOKEN 
                           {
			     defaultpoints = $1;
			     printf("Default point number has been set to %d.\n",(int) defaultpoints);
                             $$ = NULL;
                           }
	   | points EXCLAMATIONTOKEN SEMICOLONTOKEN 
                           {
			     defaultpoints = $1;
                             $$ = NULL;
                           }
	   | POINTSTOKEN EQUALTOKEN QUESTIONMARKTOKEN SEMICOLONTOKEN 
                           {
			     printf("Default point number is set to %d points.\n",(int) defaultpoints);
                             $$ = NULL;
                           }
           | assignment SEMICOLONTOKEN
                           {
			     $$ = NULL;
			   }
           | implementpoly SEMICOLONTOKEN
                           {
			     free_memory($1);
			     $$ = NULL;
			   }
           | checkinfnorm SEMICOLONTOKEN
	                   {
			     if ($1) {
			       printf("The given bound for the infinite norm of the given function is satisfied.\n");
			     } else {
			       printf("The given bound for the infinite norm of the given function could not be verified.\n");
			       printMessage(2,"Information: Try to decrease the diameter for the test dichotomy.\n");
			     }
			     $$ = NULL;
			   }
           | restart SEMICOLONTOKEN
                           {
			     $$ = NULL;
			   }
           | testpari SEMICOLONTOKEN
                           {
			     $$ = NULL;
			   }
           | bashexecute SEMICOLONTOKEN
                           {
			     int_temp = $1;
			     printMessage(2,"Information: the returned value is %d.\n",int_temp);
			     $$ = NULL;
			   }
           | externalplot SEMICOLONTOKEN 
	                   {
			     $$ = NULL;
	                   }
           | error SEMICOLONTOKEN
                           {
			     handlingError = 0;
			     $$ = NULL;
                           }
;


restart:     RESTARTTOKEN
                           {
			     freeSymbolTable(symbolTable,freeMemoryOnVoid);
			     freeSymbolTable(symbolTable2,freeRangetypePtr);
			     if(currentVariable != NULL) free(currentVariable);
			     if(variablename != NULL) free(variablename);
			     symbolTable = NULL;
			     symbolTable2 = NULL;
			     currentVariable = NULL;
			     variablename = NULL;
			     defaultprecision = DEFAULTPRECISION;
			     defaultpoints = DEFAULTPOINTS;
			     tools_precision = DEFAULTPRECISION;
			     taylorrecursions = DEFAULTTAYLORRECURSIONS;
			     verbosity = 1;
			     dyadic = 0;
			     avma = ltop;
			     printf("System restarted.\n");
			     $$ = NULL;
			   }
;

testpari:     TESTPARITOKEN
                           {
			     printf("Will now test the PARI subsystem.\n");
			     testPari();
			     printf("PARI test completed. We did not crash. Will now restart the system.\n");
			     freeSymbolTable(symbolTable,freeMemoryOnVoid);
			     freeSymbolTable(symbolTable2,freeRangetypePtr);
			     if(currentVariable != NULL) free(currentVariable);
			     if(variablename != NULL) free(variablename);
			     symbolTable = NULL;
			     symbolTable2 = NULL;
			     currentVariable = NULL;
			     variablename = NULL;
			     defaultprecision = DEFAULTPRECISION;
			     defaultpoints = DEFAULTPOINTS;
			     tools_precision = DEFAULTPRECISION;
			     taylorrecursions = DEFAULTTAYLORRECURSIONS;
			     verbosity = 1;
			     dyadic = 0;
			     avma = ltop;
			     printf("System restarted.\n");
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
           | DYADICTOKEN EQUALTOKEN POWERSTOKEN
                           {
			     printf("Dyadic number output activated with power of 2 notation.\n");
			     dyadic = 2;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN BINARYTOKEN
                           {
			     printf("Dyadic number output activated with binary notation.\n");
			     dyadic = 3;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN ONTOKEN EXCLAMATIONTOKEN
                           {
			     dyadic = 1;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN OFFTOKEN EXCLAMATIONTOKEN
                           {
			     dyadic = 0;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN POWERSTOKEN EXCLAMATIONTOKEN
                           {
			     dyadic = 2;
			     $$ = NULL;
                           }
           | DYADICTOKEN EQUALTOKEN BINARYTOKEN EXCLAMATIONTOKEN
                           {
			     dyadic = 3;
			     $$ = NULL;
                           }
;

canonical:   CANONICALTOKEN EQUALTOKEN ONTOKEN 
                           {
			     printf("Canonical autoprint output activated.\n");
			     canonical = 1;
			     $$ = NULL;
                           }
           | CANONICALTOKEN EQUALTOKEN OFFTOKEN
                           {
			     printf("Canonical autoprint output deactivated.\n");
			     canonical = 0;
			     $$ = NULL;
                           }
           | CANONICALTOKEN EQUALTOKEN ONTOKEN EXCLAMATIONTOKEN
                           {
			     canonical = 1;
			     $$ = NULL;
                           }
           | CANONICALTOKEN EQUALTOKEN OFFTOKEN EXCLAMATIONTOKEN
                           {
			     canonical = 0;
			     $$ = NULL;
                           }
;


verbosityset:  VERBOSITYTOKEN EQUALTOKEN verbosity
                           {
			     printf("Verbosity set to level %d.\n",($3));
			     verbosity = ($3);
			     $$ = NULL;
                           }
             | VERBOSITYTOKEN EQUALTOKEN verbosity EXCLAMATIONTOKEN
                           {
			     verbosity = ($3);
			     $$ = NULL;
                           }
;

taylorrecursions: TAYLORRECURSIONSTOKEN EQUALTOKEN taylorrecursionsvalue
                           {
			     printf("The number of recursions for the Taylor evaluation is set to %d.\n",($3));
			     taylorrecursions = ($3);
			     $$ = NULL;
			   }
                | TAYLORRECURSIONSTOKEN EQUALTOKEN taylorrecursionsvalue EXCLAMATIONTOKEN
                           {
			     taylorrecursions = ($3);
			     $$ = NULL;
			   }
;

assignment:  lvariable EQUALTOKEN variableWorkAround EXCLAMATIONTOKEN {
			     if ((variablename != NULL) && (strcmp(variablename,($1)) == 0)) {
			       if (containsEntry(symbolTable,($3))) {
				 printMessage(1,"Warning: the identifier \"%s\" is already assigned. The free variable cannot be named like an assigned identifier.\n",($3));
				 printMessage(1,"The last command will have no effect.\n");
			       } else {
				 printMessage(1,"Warning: the identifier \"%s\" is bound as the current variable. It will be renamed as \"%s\" as forced.\n",($1),($3));
				 free(variablename);
				 variablename = (char *) safeCalloc(strlen(($3))+1,sizeof(char));
				 strcpy(variablename,($3));
			       }
			     } else {
			       if (containsEntry(symbolTable,($1))) {
				 printMessage(2,"Information: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
				 symbolTable = removeEntry(symbolTable, ($1), freeMemoryOnVoid);
				 if (!containsEntry(symbolTable,$3)) {
				   if (variablename==NULL) {
				     variablename = (char *) safeCalloc(strlen($3)+1,sizeof(char));
				     strcpy(variablename,$3);
				   }
				   if (strcmp(variablename,$3)!=0) {
				     printMessage(1,"Warning: the identifier \"%s\" is neither bound by assignment nor equal to the bound current variable.\n",$3);
				     printMessage(1,"Will interpret \"%s\" as \"%s\".\n",$3,variablename);
				   }
				   temp_node = (node*) safeMalloc(sizeof(node));
				   temp_node->nodeType = VARIABLE;
				 } else {
				   temp_node = getEntry(symbolTable,$3,copyTreeOnVoid);
				 }
				 symbolTable = addEntry(symbolTable, ($1), temp_node, copyTreeOnVoid);
			       } else {
				 if (!containsEntry(symbolTable,$3)) {
				   if (variablename==NULL) {
				     variablename = (char *) safeCalloc(strlen($3)+1,sizeof(char));
				     strcpy(variablename,$3);
				   }
				   if (strcmp(variablename,$3)!=0) {
				     printMessage(1,"Warning: the identifier \"%s\" is neither bound by assignment nor equal to the bound current variable.\n",$3);
				     printMessage(1,"Will interpret \"%s\" as \"%s\".\n",$3,variablename);
				   }
				   temp_node = (node*) safeMalloc(sizeof(node));
				   temp_node->nodeType = VARIABLE;
				 } else {
				   temp_node = getEntry(symbolTable,$3,copyTreeOnVoid);
				 }
				 symbolTable = addEntry(symbolTable,($1),temp_node,copyTreeOnVoid);
			       }
			     }
			     free(($1));
			     free(($3));
			     $$ = NULL;
                           }
           | lvariable EQUALTOKEN function 
                           {
			     if ((variablename != NULL) && (strcmp(variablename,($1)) == 0)) {
			       printMessage(1,"Warning: the identifer \"%s\" is already bound as the current variable. It cannot be assigned.\n",($1));
			       printMessage(1,"The last command will have no effect.\n");
			     } else {
			       if (containsEntry(symbolTable,($1))) {
				 printMessage(1,"Warning: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
				 symbolTable = removeEntry(symbolTable, ($1), freeMemoryOnVoid);
				 symbolTable = addEntry(symbolTable, ($1), ($3), copyTreeOnVoid);
			       } else {
				 symbolTable = addEntry(symbolTable,($1),($3),copyTreeOnVoid);
			       }
			     }
			     free(($1));
			     free_memory(($3));
			     $$ = NULL;
                           }
           | lvariable EQUALTOKEN directrange
                           {
			     if (containsEntry(symbolTable2,($1))) {
			       printMessage(1,"Warning: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
			       symbolTable2 = removeEntry(symbolTable2, ($1), freeRangetypePtr);
			       symbolTable2 = addEntry(symbolTable2, ($1), &($3), copyRangetypePtr);

			     } else {
			       symbolTable2 = addEntry(symbolTable2,($1),&($3),copyRangetypePtr);
			     }
			     free($1);
			     mpfr_clear(*(($3).a));
			     mpfr_clear(*(($3).b));			     
			     free(($3).a);
			     free(($3).b);
			     $$ = NULL;
			   }
           | lvariable EQUALTOKEN directString
                           {
			     if (containsEntry(symbolTable3,($1))) {
			       printMessage(1,"Warning: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
			       symbolTable3 = removeEntry(symbolTable3, ($1), freeStringPtr);
			       symbolTable3 = addEntry(symbolTable3, ($1), $3, copyString);

			     } else {
			       symbolTable3 = addEntry(symbolTable3,($1),$3,copyString);
			     }
			     free($1);
			     free($3);
			     $$ = NULL;
			   }
           | lvariable EQUALTOKEN function EXCLAMATIONTOKEN
                           {
			     if ((variablename != NULL) && (strcmp(variablename,($1)) == 0)) {
			       printMessage(1,"Warning: the identifer \"%s\" is already bound as the current variable. It cannot be assigned.\n",($1));
			       printMessage(1,"The last command will have no effect.\n");
			     } else {
			       if (containsEntry(symbolTable,($1))) {
				 printMessage(2,"Information: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
				 symbolTable = removeEntry(symbolTable, ($1), freeMemoryOnVoid);
				 symbolTable = addEntry(symbolTable, ($1), ($3), copyTreeOnVoid);
			       } else {
				 symbolTable = addEntry(symbolTable,($1),($3),copyTreeOnVoid);
			       }
			     }
			     free(($1));
			     free_memory(($3));
			     $$ = NULL;
                           }
           | lvariable EQUALTOKEN directrange EXCLAMATIONTOKEN
                           {
			     if (containsEntry(symbolTable2,($1))) {
			       printMessage(2,"Information: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
			       symbolTable2 = removeEntry(symbolTable2, ($1), freeRangetypePtr);
			       symbolTable2 = addEntry(symbolTable2, ($1), &($3), copyRangetypePtr);

			     } else {
			       symbolTable2 = addEntry(symbolTable2,($1),&($3),copyRangetypePtr);
			     }
			     free($1);
			     mpfr_clear(*(($3).a));
			     mpfr_clear(*(($3).b));			     
			     free(($3).a);
			     free(($3).b);
			     $$ = NULL;
			   }
           | lvariable EQUALTOKEN directString EXCLAMATIONTOKEN
                           {
			     if (containsEntry(symbolTable3,($1))) {
			       printMessage(2,"Information: the identifier \"%s\" is already assigned. This is a reassignment.\n",($1));
			       symbolTable3 = removeEntry(symbolTable3, ($1), freeStringPtr);
			       symbolTable3 = addEntry(symbolTable3, ($1), $3, copyString);

			     } else {
			       symbolTable3 = addEntry(symbolTable3,($1),$3,copyString);
			     }
			     free($1);
			     free($3);
			     $$ = NULL;
			   }
;     


evaluateaccurate: EVALUATEACCURATETOKEN function ATTOKEN constantfunction 
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     int_temp = evaluateFaithfulOrFail($2, *($4), *mpfr_temp, 256, &tempPrec);
			     if (int_temp) {
			       printMpfr(*mpfr_temp);
			       printMessage(2,"Information: intermediate precision of %d bits.\n",tempPrec);
			     } else {
			       printf("Could not evaluate the function sufficiently exactly.\n");
			     }
			     mpfr_clear(*mpfr_temp);
			     mpfr_clear(*($4));
			     free(mpfr_temp);
			     free($4);
			     free_memory($2);
			     $$ = NULL;
                           }
;

evaluate:    EVALUATETOKEN function INTOKEN range 
                           {
			     range_temp.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     range_temp.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*(range_temp.a),defaultprecision);
			     mpfr_init2(*(range_temp.b),defaultprecision);
			     evaluateRangeFunction(range_temp, ($2), ($4), defaultprecision);
			     mpfr_clear(*(($4).a));
			     mpfr_clear(*(($4).b));
			     free(($4).a);
			     free(($4).b);
			     free_memory($2);
			     $$ = range_temp;
			   }
           | EVALUATETOKEN function ATTOKEN constantfunction 
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
			     mpfr_clear(*(range_temp2.a));
			     mpfr_clear(*(range_temp2.b));
			     free(range_temp2.a);
			     free(range_temp2.b);
			     mpfr_clear(*($4));
			     free(($4));
			     free_memory($2);
			     $$ = range_temp;
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
			     printWorstCases(($2), *($6), ($10), *($14), *($18), tools_precision, NULL);
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
           | WORSTCASETOKEN function WITHTOKEN INPUTPRECTOKEN EQUALTOKEN constantfunction COMMATOKEN INPUTEXPOTOKEN EQUALTOKEN range COMMATOKEN OUTPUTPRECTOKEN EQUALTOKEN constantfunction COMMATOKEN EPSILONTOKEN EQUALTOKEN constantfunction COMMATOKEN OUTPUTTOKEN EQUALTOKEN writefile SEMICOLONTOKEN 
                           {
			     /* function $2
                                inputprec $6
				outputprec $14
				inputexpo $10
				epsilon $18
				file $22
			     */
			     printWorstCases(($2), *($6), ($10), *($14), *($18), tools_precision, ($22));
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
			     fclose($22);
			     $$ = NULL;
			   }
;


isevaluable: ISEVALUABLETOKEN function ATTOKEN constantfunction
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     switch (isEvaluable($2, *($4), mpfr_temp, defaultprecision)) {
			     case ISFLOATINGPOINTEVALUABLE:
			       printf("The given function can be evaluated in floating-point at the given point.\n");
			       printf("An approximate value is: ");
			       printValue(mpfr_temp,defaultprecision);
			       printf("\n");
			       break;
			     case ISHOPITALEVALUABLE:
			       printf("The given function can be evaluated in interval arithmetic with Hopital's rule at the given point.\n");
			       printf("An approximate value is: ");
			       printValue(mpfr_temp,defaultprecision);
			       printf("\n");
			       break;
			     case ISNOTEVALUABLE:
			       printf("The given function cannot be evaluated at the given point by this tool.\n");
			       break;
			     default:
			       fprintf(stderr,"On processing parser input. A function returned an unspecified value.\n");
			       exit(1);
			     }
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4));
			     free($4);
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

fpfindzeros:   FPFINDZEROSTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     chain_temp = fpFindZerosFunction($2,$4,defaultprecision);
			     if (chain_temp == NULL) {
			       printf("The function seems to have no zeros in the interval.\n");
			     } else {
			       printf("The %d approximated zeros of the function (and their images) are:\n",
				      lengthChain(chain_temp));
			       while (chain_temp != NULL) {
				 evaluateFaithful(*mpfr_temp, $2, *((mpfr_t *) (chain_temp->value)), defaultprecision);
				 printValue(((mpfr_t *) (chain_temp->value)),defaultprecision);
				 printf(" \t( ");
				 printValue(mpfr_temp,defaultprecision);
				 printf(" )\n");
				 mpfr_clear(*((mpfr_t *) (chain_temp->value)));
				 free(chain_temp->value);
				 chain_temp2 = chain_temp->next;
				 free(chain_temp);
				 chain_temp = chain_temp2;
			       }

			     }
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = NULL;
                           }
;

zerodenominators:   ZERODENOMINATORSTOKEN function INTOKEN range SEMICOLONTOKEN
                           {
			     chain_temp = uncertifiedZeroDenominators($2,*($4.a),*($4.b),defaultprecision);
			     if (chain_temp == NULL) {
			       printf("The function seems to have no denominator vanishing in the interval.\n");
			     } else {
			       printf("The function has denominators vanishing at:\n");
			       while (chain_temp != NULL) {
				 printMpfr(*((mpfr_t *) (chain_temp->value)));
				 mpfr_clear(*((mpfr_t *) (chain_temp->value)));
				 free(chain_temp->value);
				 chain_temp2 = chain_temp->next;
				 free(chain_temp);
				 chain_temp = chain_temp2;
			       }

			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = NULL;
                           }
;



infnorm:     INFNORMTOKEN function INTOKEN range 
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
           | INFNORMTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant 
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
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist 
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
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant 
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
           | INFNORMTOKEN function INTOKEN range COMMATOKEN PROOFTOKEN EQUALTOKEN writefile 
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
           | INFNORMTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant COMMATOKEN PROOFTOKEN EQUALTOKEN writefile 
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
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN PROOFTOKEN EQUALTOKEN writefile 
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
           | INFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant COMMATOKEN PROOFTOKEN EQUALTOKEN writefile
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


integral:     INTEGRALTOKEN function INTOKEN range
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
           | INTEGRALTOKEN function INTOKEN range COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant 
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

accurateinfnorm: ACCURATEINFNORMTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN 
                           {
			     int_temp = $6;
			     if (int_temp < 12) {
			       printMessage(1,"Warning: the demanded precision must be at least 12 bits.\nIncreased the precision to 12 bits.\n");
			       int_temp = 12;
			     }
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,int_temp);

			     int_temp = accurateInfnorm(*mpfr_temp, $2, $4, NULL, defaultprecision);
			     if (!int_temp) {
			       mpfr_set_nan(*mpfr_temp);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = mpfr_temp;
			   }
               | ACCURATEINFNORMTOKEN function INTOKEN range WITHOUTTOKEN rangelist WITHTOKEN integer BITSTOKEN 
                           {
			     int_temp = $8;
			     if (int_temp < 12) {
			       printMessage(1,"Warning: the demanded precision must be at least 12 bits.\nIncreased the precision to 12 bits.\n");
			       int_temp = 12;
			     }
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,int_temp);

			     int_temp = accurateInfnorm(*mpfr_temp, $2, $4, $6, defaultprecision);
			     if (!int_temp) {
			       mpfr_set_nan(*mpfr_temp);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     $$ = mpfr_temp;
			   }
;


searchGal:    SEARCHGALTOKEN function ATTOKEN constantfunction WITHTOKEN integer BITSTOKEN INTOKEN integer STEPSTOKEN INTOKEN expansionFormat WITHTOKEN EPSILONTOKEN EQUALTOKEN constantfunction 
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     int_temp = searchGalValue($2, *mpfr_temp, *($4), $6, $9, $12, *($16), tools_precision);
			     if (!int_temp) {
			       mpfr_set_nan(*mpfr_temp);
			     }
			     $$ = mpfr_temp;
			   }
;


dirtyinfnorm: DIRTYINFNORMTOKEN function INTOKEN range 
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
             | DIRTYINFNORMTOKEN function INTOKEN range COMMATOKEN points 
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

dirtyintegral: DIRTYINTEGRALTOKEN function INTOKEN range 
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
             | DIRTYINTEGRALTOKEN function INTOKEN range COMMATOKEN points 
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

autoprint:   function SEMICOLONTOKEN
                           {
			     temp_node = horner($1);
			     if (isConstant(temp_node)) {
			       if (temp_node->nodeType == CONSTANT) {
				 prec_temp = tools_precision;
				 tools_precision = defaultprecision;
				 printTree(temp_node);
				 tools_precision = prec_temp;
				 printf("\n");
			       } else {
				 mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
				 mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
				 mpfr_temp3 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
				 mpfr_init2(*mpfr_temp,defaultprecision);
				 mpfr_init2(*mpfr_temp2,defaultprecision);
				 mpfr_init2(*mpfr_temp3,defaultprecision);
				 mpfr_set_d(*mpfr_temp3,0.0,GMP_RNDN);
				 evaluateConstantWithErrorEstimate(*mpfr_temp, 
								   *mpfr_temp2, temp_node, *mpfr_temp3, defaultprecision);
				 mpfr_log2(*mpfr_temp3,*mpfr_temp2,GMP_RNDD);
				 double_temp = mpfr_get_d(*mpfr_temp3,GMP_RNDD);
				 if (mpfr_number_p(*mpfr_temp)) {
				   if (!mpfr_zero_p(*mpfr_temp2)) {
				     printMessage(1,
						  "Warning: the displayed value is affected by a relative error of approximately 2^(%f).\n",
						  double_temp);
				   } else {
				     printMessage(1,"Warning: rounding has happened.\n");
				   }
				 } else {
				   printMessage(1,"Warning: the expression is mathematically undefined or numerically unstable.\n");
				 }
				 printValue(mpfr_temp, defaultprecision);
				 printf("\n");
				 mpfr_clear(*mpfr_temp);
				 mpfr_clear(*mpfr_temp2);
				 mpfr_clear(*mpfr_temp3);
				 free(mpfr_temp);
				 free(mpfr_temp2);
				 free(mpfr_temp3);
			       }
			     } else {
			       temp_node2 = simplifyTree(temp_node);
			       if (!isSyntacticallyEqual(temp_node,temp_node2)) {
				 printMessage(1,"Warning: the displayed function is affected by rounding error.\n");
			       }
			       free_memory(temp_node);
			       if (canonical) temp_node = makeCanonical(temp_node2,tools_precision); else temp_node = horner(temp_node2);
			       prec_temp = tools_precision;
			       tools_precision = defaultprecision;
			       printTree(temp_node);
			       tools_precision = prec_temp;
			       printf("\n");
			       free_memory(temp_node2);
			     }
			     free_memory($1);
			     free_memory(temp_node);
			     $$ = NULL;
			   }
           | printableRange SEMICOLONTOKEN {
                             printf("[");
                             printValue(($1).a,tools_precision);
			     printf(";");
			     printValue(($1).b,tools_precision);
			     printf("]\n");
			     mpfr_clear(*(($1).a));
			     mpfr_clear(*(($1).b));
			     free($1.a);
			     free($1.b);
                             $$ = NULL;
	                    }
           | directString SEMICOLONTOKEN {
	                     printf("%s\n",$1);
			     free($1);
	                     $$ = NULL;
	                    }
;

write:       WRITETOKEN writelist SEMICOLONTOKEN
                           {
			     $$ = NULL;
			   }
           | WRITETOKEN RIGHTANGLETOKEN writefile fwritelist SEMICOLONTOKEN
                           {
			     int_temp = fprintf($3,"%s",$4);
			     printMessage(2,"Information: wrote %d byte(s) to the newly created file.\n",int_temp);
			     free($4);
			     fclose($3);
			     $$ = NULL;
			   }
           | WRITETOKEN RIGHTANGLETOKEN RIGHTANGLETOKEN appendfile fwritelist SEMICOLONTOKEN
                           {
			     int_temp = fprintf($4,"%s",$5);
			     printMessage(2,"Information: wrote %d byte(s) to the file opened for appending.\n",int_temp);
			     free($5);
			     fclose($4);
			     $$ = NULL;
			   }
;


writelist:   writeelem     {
                             $$ = NULL;
                           }
           | writeelem COMMATOKEN writelist
                           {
			     $$ = NULL;
			   }
;



writeelem:   function
                           {
			     prec_temp = tools_precision;
			     tools_precision = defaultprecision;
                             printTree($1);
			     tools_precision = prec_temp;
			     free_memory($1);
			     $$ = NULL;
                           }
           | directString 
                           {
			     printf("%s",($1));
			     free(($1));
                             $$ = NULL;
			   }
           | printableRange {
                             printf("[");
                             printValue(($1).a,tools_precision);
			     printf(";");
			     printValue(($1).b,tools_precision);
			     printf("]");
			     mpfr_clear(*(($1).a));
			     mpfr_clear(*(($1).b));
			     free($1.a);
			     free($1.b);
                             $$ = NULL;
	                    }
;

fwritelist:   fwriteelem     {
                             $$ = $1;
                           }
           | fwriteelem COMMATOKEN fwritelist
                           {
			     temp_string = (char *) safeCalloc(strlen($1) + strlen($3) + 1,sizeof(char));
			     sprintf(temp_string,"%s%s",$1,$3);
			     free($1);
			     free($3);
			     $$ = temp_string;
			   }
;



fwriteelem:   function
                           {
			     prec_temp = tools_precision;
			     tools_precision = defaultprecision;
                             temp_string = sprintTree($1);
			     tools_precision = prec_temp;
			     free_memory($1);
			     $$ = temp_string;
                           }
           | directString 
                           {
                             $$ = $1;
			   }
           | printableRange {
	                     temp_string = sprintValue(($1).a,tools_precision);
	                     temp_string2 = sprintValue(($1).a,tools_precision);
	                     temp_string3 = (char *) safeCalloc(strlen(temp_string) + strlen(temp_string2) + 4,sizeof(char));
			     sprintf(temp_string3,"[%s;%s]",temp_string,temp_string2);
			     free(temp_string);
			     free(temp_string2);
			     mpfr_clear(*(($1).a));
			     mpfr_clear(*(($1).b));
			     free($1.a);
			     free($1.b);
                             $$ = temp_string3;
	                    }
;



print:       PRINTTOKEN printlist SEMICOLONTOKEN
                           {
			     printf("\n");
			     $$ = NULL;
			   }
;


printlist:   printelem     {
                             $$ = NULL;
                           }
           | printelem COMMATOKEN printlist
                           {
			     $$ = NULL;
			   }
;



printelem:   function
                           {
			     prec_temp = tools_precision;
			     tools_precision = defaultprecision;
                             printTree($1);
			     printf(" ");
			     tools_precision = prec_temp;
			     free_memory($1);
			     $$ = NULL;
                           }
           | directString 
                           {
			     printf("%s ",($1));
			     free(($1));
                             $$ = NULL;
			   }
           | printableRange {
                             printf("[");
                             printValue(($1).a,tools_precision);
			     printf(";");
			     printValue(($1).b,tools_precision);
			     printf("] ");
			     mpfr_clear(*(($1).a));
			     mpfr_clear(*(($1).b));
			     free($1.a);
			     free($1.b);
                             $$ = NULL;
	                    }
;

printHexa:  PRINTHEXATOKEN constantfunction SEMICOLONTOKEN 
                           {
			     printDoubleInHexa(*($2));
			     mpfr_clear(*($2));
			     free($2);
			     $$ = NULL;
			   }
;

printBinary:  PRINTBINARYTOKEN constantfunction SEMICOLONTOKEN 
                           {
			     printBinary(*($2));
			     printf("\n");
			     mpfr_clear(*($2));
			     free($2);
			     $$ = NULL;
			   }
;


printexpansion: PRINTEXPANSIONTOKEN function SEMICOLONTOKEN
                           {
			     if (isConstant($2)) {
			       temp_node = simplifyTreeErrorfree($2);
			       if (temp_node->nodeType == CONSTANT) {			       
				 if (printDoubleExpansion(*(temp_node->value)) != 0) {
				   printMessage(1,"\nWarning: rounding occured while printing.");
				 }
			       } else {
				 printMessage(1,"Warning: the constant expression is not a constant but must be evaluated.\n");
				 mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
				 mpfr_init2(*mpfr_temp,defaultprecision);
				 evaluateConstantExpression(*mpfr_temp, temp_node, defaultprecision);
				 if (printDoubleExpansion(*mpfr_temp) != 0) {
				   printMessage(1,"\nWarning: rounding occured while printing.");
				 }
				 mpfr_clear(*mpfr_temp);
				 free(mpfr_temp);
			       }
			       free_memory(temp_node);
			     } else {
			       if (printPolynomialAsDoubleExpansion($2, defaultprecision) == 1) {
				 printMessage(1,"\nWarning: rounding occured while printing.");
			       }
			     }
			     printf("\n");
			     free_memory($2);
			     $$ = NULL;
			   }
;

asciiplot:   ASCIIPLOTTOKEN function INTOKEN range SEMICOLONTOKEN {
                             asciiPlotTree($2, *($4.a), *($4.b), tools_precision);
                             free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
                             $$ = NULL;
                           }
;

plot:        PLOTTOKEN functionlist INTOKEN range SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), defaultpoints, tools_precision, NULL, -1);
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN precision SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), defaultpoints, ($6), NULL, -1);
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN points SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($6), tools_precision, NULL, -1);
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN precision COMMATOKEN points SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($8), ($6), NULL, -1);
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN points COMMATOKEN precision SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($6), ($8), NULL, -1);
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN plottype EQUALTOKEN string SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), defaultpoints, tools_precision, ($8), ($6));
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN precision COMMATOKEN plottype EQUALTOKEN string SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), defaultpoints, ($6), ($10), ($8));
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN points COMMATOKEN plottype EQUALTOKEN string SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($6), tools_precision, ($10), ($8));
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN precision COMMATOKEN points COMMATOKEN plottype EQUALTOKEN string SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($8), ($6), ($12), ($10));
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
           | PLOTTOKEN functionlist INTOKEN range COMMATOKEN points COMMATOKEN precision COMMATOKEN plottype EQUALTOKEN string SEMICOLONTOKEN 
                           {
			     plotTree($2, *($4.a), *($4.b), ($6), ($8), ($12), ($10));
			     freeChain($2,freeMemoryOnVoid);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     tools_precision = defaultprecision;
			     $$ = NULL;
			   }
;

plottype:           FILETOKEN {
                                $$ = PLOTFILE;
                              }
                  | POSTSCRIPTTOKEN {
                                $$ = PLOTPOSTSCRIPT;
                              }
                  | POSTSCRIPTFILETOKEN {
                                $$ = PLOTPOSTSCRIPTFILE;
                              }
;


functionlist:       function {
	                       chain_temp = addElement(NULL,$1);
			       $$ = chain_temp;
                             }
                  | function COMMATOKEN functionlist {
		               chain_temp = addElement($3,$1);
			       $$ = chain_temp;
		             }
                  | LBRACKETTOKEN functionlist RBRACKETTOKEN 
                             {
			       $$ = $2;
			     }
;


variableformat:     DOUBLETOKEN 
                           {
			     $$ = 1;
                           }
                  | DOUBLEDOUBLETOKEN 
                           {
			     $$ = 2;
			   }
                  | TRIPLEDOUBLETOKEN 
                           {
			     $$ = 3;
			   }
;

implementpoly:        IMPLEMENTPOLYTOKEN function INTOKEN range WITHTOKEN EPSILONTOKEN EQUALTOKEN constantfunction WITHTOKEN VARIABLEMETATOKEN ASTOKEN variableformat INTOKEN writefile WITHTOKEN NAMETOKEN EQUALTOKEN string 
                           {
			     temp_node = implementpoly($2,$4,$8,$12,$14,$18,0,tools_precision,NULL);
			     if (temp_node != NULL) {
			       printMessage(2,"Information: the implementation has succeeded.\n"); 
			     } else {
			       printMessage(1,"Warning: the implementation has not succeeded. The code may be incomplete.\n"); 
			       temp_node = copyTree($2);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($8));
			     free($8);
			     fclose($14);
			     free($18);
			     $$ = temp_node;
			   }
                    | IMPLEMENTPOLYTOKEN function INTOKEN range WITHTOKEN EPSILONTOKEN EQUALTOKEN constantfunction WITHTOKEN VARIABLEMETATOKEN ASTOKEN variableformat INTOKEN writefile WITHTOKEN NAMETOKEN EQUALTOKEN string COMMATOKEN HONORCOEFFPRECTOKEN
                           {
			     temp_node = implementpoly($2,$4,$8,$12,$14,$18,1,tools_precision,NULL);
			     if (temp_node != NULL) {
			       printMessage(2,"Information: the implementation has succeeded.\n"); 
			     } else {
			       printMessage(1,"Warning: the implementation has not succeeded. The code may be incomplete.\n"); 
			       temp_node = copyTree($2);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($8));
			     free($8);
			     fclose($14);
			     free($18);
			     $$ = temp_node;
			   }
                    | IMPLEMENTPOLYTOKEN function INTOKEN range WITHTOKEN EPSILONTOKEN EQUALTOKEN constantfunction WITHTOKEN VARIABLEMETATOKEN ASTOKEN variableformat INTOKEN writefile WITHTOKEN NAMETOKEN EQUALTOKEN string COMMATOKEN PROOFTOKEN EQUALTOKEN writefile
                           {
			     temp_node = implementpoly($2,$4,$8,$12,$14,$18,0,tools_precision,$22);
			     if (temp_node != NULL) {
			       printMessage(2,"Information: the implementation has succeeded.\n"); 
			     } else {
			       printMessage(1,"Warning: the implementation has not succeeded. The code may be incomplete.\n"); 
			       temp_node = copyTree($2);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($8));
			     free($8);
			     fclose($14);
			     fclose($22);
			     free($18);
			     $$ = temp_node;
			   }
                    | IMPLEMENTPOLYTOKEN function INTOKEN range WITHTOKEN EPSILONTOKEN EQUALTOKEN constantfunction WITHTOKEN VARIABLEMETATOKEN ASTOKEN variableformat INTOKEN writefile WITHTOKEN NAMETOKEN EQUALTOKEN string COMMATOKEN HONORCOEFFPRECTOKEN COMMATOKEN PROOFTOKEN EQUALTOKEN writefile
                           {
			     temp_node = implementpoly($2,$4,$8,$12,$14,$18,1,tools_precision,$24);
			     if (temp_node != NULL) {
			       printMessage(2,"Information: the implementation has succeeded.\n"); 
			     } else {
			       printMessage(1,"Warning: the implementation has not succeeded. The code may be incomplete.\n"); 
			       temp_node = copyTree($2);
			     }
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($8));
			     free($8);
			     fclose($14);
			     fclose($24);
			     free($18);
			     $$ = temp_node;
			   }
;

checkinfnorm:        CHECKINFNORMTOKEN function INTOKEN range BOUNDEDTOKEN BYTOKEN constantfunction 
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     mpfr_set_d(*mpfr_temp,DEFAULTDIAM,GMP_RNDN);
			     if (mpfr_sgn(*($7)) < 0) {
			       printMessage(1,"Warning: the given bound evaluates to a negative value. Infinite norms are by definition positive.\nWill take the opposite of the given bound.\n");
			       mpfr_neg(*($7),*($7),GMP_RNDN);
			     } 
			     int_temp = checkInfnorm($2, $4, *($7), *mpfr_temp, defaultprecision);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($7));
			     free($7);
			     mpfr_clear(*mpfr_temp);
			     free(mpfr_temp);
			     $$ = int_temp;
			   }
                   | CHECKINFNORMTOKEN function INTOKEN range BOUNDEDTOKEN BYTOKEN constantfunction COMMATOKEN DIAMTOKEN EQUALTOKEN diamconstant 
                           {
			     if (mpfr_sgn(*($7)) < 0) {
			       printMessage(1,"Warning: the given bound evaluates to a negative value. Infinite norms are by definition positive.\nWill take the opposite of the given bound.\n");
			       mpfr_neg(*($7),*($7),GMP_RNDN);
			     } 
			     int_temp = checkInfnorm($2, $4, *($7), *($11), defaultprecision);
			     free_memory($2);
			     mpfr_clear(*($4.a));
			     mpfr_clear(*($4.b));
			     free($4.a);
			     free($4.b);
			     mpfr_clear(*($7));
			     free($7);
			     mpfr_clear(*($11));
			     free($11);
			     $$ = int_temp;
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

taylorrecursionsvalue:  CONSTTOKEN
                           {
			     int_temp = (int) strtol($1,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: the number of recursions for Taylor evaluation must be an integer. Will set the value to 0.\n");
			       int_temp = 0;
			     }
			     if (int_temp < 0) {
			       printMessage(1,"Warning: the number of recursions for Taylor evaluation must be positive or zero. Will set the value to 0.\n");
			       int_temp = 0;
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
                        |       roundcoefficients
                           {
			      $$ = $1;
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
                        |       RATIONALAPPROXTOKEN LPARTOKEN constantfunction COMMATOKEN integer RPARTOKEN
                           {
			      temp_node = rationalApprox(*($3), $5);
			      mpfr_clear(*($3));
			      free($3);
			      $$ = temp_node;
                           }
                        |       COEFFTOKEN LPARTOKEN function COMMATOKEN integer RPARTOKEN
                           {
			      temp_node = getIthCoefficient(($3), ($5));
			      free_memory(($3));
			      $$ = temp_node;
			   }

                        |       SUBPOLYTOKEN LPARTOKEN function COMMATOKEN LBRACKETTOKEN integerlist RBRACKETTOKEN RPARTOKEN
                           {
			      temp_node = getSubpolynomial(($3), ($6), 0, tools_precision);
			      free_memory(($3));
			      freeChain(($6),freeIntPtr);
			      $$ = temp_node;
			   }
                        |       SUBPOLYTOKEN LPARTOKEN function COMMATOKEN LBRACKETTOKEN integerlist COMMATOKEN DOTSTOKEN RBRACKETTOKEN RPARTOKEN
                           {
			      temp_node = getSubpolynomial(($3), ($6), 1, tools_precision);
			      free_memory(($3));
			      freeChain(($6),freeIntPtr);
			      $$ = temp_node;
			   }
			|       fpminimax
                           {
			      temp_node = $1;
			      $$ = temp_node;
                           }
                        |       TAYLORTOKEN LPARTOKEN function COMMATOKEN degree COMMATOKEN function RPARTOKEN
                           {
			      temp_node = taylor(($3),($5),($7),tools_precision);
			      free_memory(($3));
			      free_memory(($7));
			      $$ = temp_node;
                           }
                        |       SUBSTITUTETOKEN LPARTOKEN function COMMATOKEN function RPARTOKEN
                           {
			      temp_node = substitute(($3),($5));
			      free_memory(($3));
			      free_memory(($5));
			      $$ = temp_node;
                           }

                        |       SIMPLIFYTOKEN LPARTOKEN function RPARTOKEN
                           {
			     temp_node = simplifyTree($3);
			     free_memory($3);
			     $$ = temp_node;
			   }
                        |       CANONICALTOKEN LPARTOKEN function RPARTOKEN
                           {
			     temp_node = makeCanonical($3,tools_precision);
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
                        |       ERFTOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ERF;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       ERFCTOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = ERFC;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       LOG1PTOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = LOG_1P;
			     temp_node->child1 = $3;
			     $$ = temp_node;
                           }		
                        |       EXPM1TOKEN LPARTOKEN function RPARTOKEN     						
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = EXP_M1;
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
                        |       DOUBLEEXTENDEDTOKEN LPARTOKEN function RPARTOKEN     			   	
                           {
                             temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = DOUBLEEXTENDED;
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
                         |      degree COMMATOKEN degreelist
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = ($1);
			     chain_temp = addElement(($3),intTempPtr);
			     $$ = chain_temp;
			   }
                         |      degree DOTSTOKEN degree
                           {
			     if (($1) > ($3)) {
			       printMessage(1,"Warning: the bounds given for a elliptic degree list are not in ascending order.\nThis list or sublist will not be taken into account.\n");
			     }
			     chain_temp = makeIntPtrChainFromTo(($1),($3));
			     $$ = chain_temp;
			   }
                         |      degree DOTSTOKEN degree COMMATOKEN degreelist
                           {
			     if (($1) > ($3)) {
			       printMessage(1,"Warning: the bounds given for a elliptic degree list are not in ascending order.\nThis list or sublist will not be taken into account.\n");
			     }
			     chain_temp = makeIntPtrChainFromTo(($1),($3));
			     chain_temp = concatChains(chain_temp,($5));
			     $$ = chain_temp;
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
			|	LPARTOKEN function RPARTOKEN			
			   {
			     $$ = $2;
                           }	
                        |       prefixfunction
                           {
                             $$ = $1;
                           }
                        |       LEFTANGLETOKEN commandfunction RIGHTANGLETOKEN
                           {
			     temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = CONSTANT;
			     temp_node->value = $2.b;
			     mpfr_clear(*($2.a));
			     free($2.a);
			     $$ = temp_node;
			   }
                        |       LEFTANGLETOKEN commandfunction RIGHTANGLEUNDERSCORETOKEN
                           {
			     temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = CONSTANT;
			     temp_node->value = $2.a;
			     mpfr_clear(*($2.b));
			     free($2.b);
			     $$ = temp_node;
			   }
                        |       LEFTANGLETOKEN commandfunction RIGHTANGLEDOTTOKEN
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_add(*mpfr_temp,*($2.a),*($2.b),GMP_RNDN);
			     mpfr_div_2ui(*mpfr_temp,*mpfr_temp,1,GMP_RNDN);
			     temp_node = (node*) safeMalloc(sizeof(node));
			     temp_node->nodeType = CONSTANT;
			     temp_node->value = mpfr_temp;
			     mpfr_clear(*($2.a));
			     mpfr_clear(*($2.b));
			     free($2.a);
			     free($2.b);
			     $$ = temp_node;
			   }
                        |       LEFTANGLETOKEN implementpoly RIGHTANGLETOKEN
                           {
			     $$ = $2;
			   }
;


evaluateaccuratecommandfunction: EVALUATEACCURATETOKEN function ATTOKEN constantfunction 
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,defaultprecision);
			     int_temp = evaluateFaithfulOrFail($2, *($4), *mpfr_temp, 256, NULL);
			     if (!int_temp) {
			       mpfr_set_nan(*(mpfr_temp));
			     }
			     mpfr_clear(*($4));
			     free($4);
			     free_memory($2);
			     $$ = mpfr_temp;
                           }


commandfunction:          infnorm
                           {
			     $$ = $1;
			   }
                        | integral
                           {
			     $$ = $1;
			   }
                        | evaluate 
                           {
			     $$ = $1;
                           }
                        | range
                           {
			     $$ = $1;
                           }
                        | dirtyinfnorm
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,mpfr_get_prec(*($1)));
			     mpfr_set(*mpfr_temp,*($1),GMP_RNDN);
			     range_temp.a = $1;
			     range_temp.b = mpfr_temp;
			     $$ = range_temp;
			   }
                        | searchGal
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,mpfr_get_prec(*($1)));
			     mpfr_set(*mpfr_temp,*($1),GMP_RNDN);
			     range_temp.a = $1;
			     range_temp.b = mpfr_temp;
			     $$ = range_temp;
			   }
                        | dirtyintegral
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,mpfr_get_prec(*($1)));
			     mpfr_set(*mpfr_temp,*($1),GMP_RNDN);
			     range_temp.a = $1;
			     range_temp.b = mpfr_temp;
			     $$ = range_temp;
			   }
                        | accurateinfnorm
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,mpfr_get_prec(*($1)));
			     mpfr_set(*mpfr_temp,*($1),GMP_RNDN);
			     range_temp.a = $1;
			     range_temp.b = mpfr_temp;
			     $$ = range_temp;
			   }
                        | evaluateaccuratecommandfunction
                           {
			     mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,mpfr_get_prec(*($1)));
			     mpfr_set(*mpfr_temp,*($1),GMP_RNDN);
			     range_temp.a = $1;
			     range_temp.b = mpfr_temp;
			     $$ = range_temp;
			   }

;

variableWorkAround: VARIABLETOKEN 
                           {
			     temp_string = (char *) safeCalloc(strlen(currentVariable)+1,sizeof(char));
			     strcpy(temp_string,currentVariable);
			     $$ = temp_string;
                           }
;


variable: variableWorkAround
                           {
			     if (!containsEntry(symbolTable,$1)) {
			       if (variablename==NULL) {
				 variablename = (char *) safeCalloc(strlen($1)+1,sizeof(char));
				 strcpy(variablename,$1);
			       }
			       if (strcmp(variablename,$1)!=0) {
				 printMessage(1,"Warning: the identifier \"%s\" is neither bound by assignment nor equal to the bound current variable.\n",$1);
				 printMessage(1,"Will interpret \"%s\" as \"%s\".\n",$1,variablename);
			       }
			       temp_node = (node*) safeMalloc(sizeof(node));
			       temp_node->nodeType = VARIABLE;
			     } else {
			       temp_node = getEntry(symbolTable,$1,copyTreeOnVoid);
			     }
			     free($1);
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
				 temp_node2 = getEntry(symbolTable,($1),copyTreeOnVoid);
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

string:     directString   {
                             $$ = $1;
                           }
          | variableWorkAround {
  			     if (!containsEntry(symbolTable3,$1)) {
			       printMessage(1,"Warning: the identifier \"%s\" is not bound by assignment.\n",$1);
			       printMessage(1,"Will take \"$%s\" as content of \"%s\".\n",$1,$1);
			       temp_string = (char *) safeCalloc(strlen($1) + 2,sizeof(char));
			       sprintf(temp_string,"$%s",$1);
			     } else {
			       temp_string = getEntry(symbolTable3,$1,copyString);
			     }
			     free($1);
			     $$ = temp_string;
	                   }
;


directString: STRINGTOKEN
                           {
			     temp_string = (char *) safeCalloc(strlen(currentString)+1,sizeof(char));
			     demaskString(temp_string,currentString);
			     $$ = temp_string;
                           } 
          | DOLLARTOKEN variableWorkAround {
  			     if (!containsEntry(symbolTable3,$2)) {
			       printMessage(1,"Warning: the identifier \"%s\" is not bound by assignment.\n",$2);
			       printMessage(1,"Will take \"$%s\" as content of \"%s\".\n",$2,$2);
			       temp_string = (char *) safeCalloc(strlen($2) + 2,sizeof(char));
			       sprintf(temp_string,"$%s",$2);
			     } else {
			       temp_string = getEntry(symbolTable3,$2,copyString);
			     }
			     free($2);
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

appendfile: string     
                           {
			     temp_fd = fopen(($1),"a");
			     if (temp_fd == NULL) {
			       fprintf(stderr,"Error: the file \"%s\" could not be opened for appending: ",($1));
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

range:        directrange 
                           {
			     $$ = $1;
                           }
            | variableWorkAround 
                           {
			     if (!containsEntry(symbolTable2,$1)) {
			       printMessage(1,"Warning: the identifier \"%s\" is not bound by assignment.\n",$1);
			       printMessage(1,"Will take [-1;1] for \"%s\".\n",$1);
			       range_temp.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			       range_temp.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*(range_temp.a),defaultprecision);
			       mpfr_init2(*(range_temp.b),defaultprecision);
			       mpfr_set_d(*(range_temp.a),-1.0,GMP_RNDN);
			       mpfr_set_d(*(range_temp.b),1.0,GMP_RNDN);
			     } else {
			       rangeTempPtr = getEntry(symbolTable2,$1,copyRangetypePtr);
			       range_temp.a = rangeTempPtr->a;
			       range_temp.b = rangeTempPtr->b;
			       free(rangeTempPtr);
			     }
			     free($1);
			     $$ = range_temp;
	                   }
;

printableRange: directrange {
	                     $$ = $1;
                           }
              | symbolRange {
                             $$ = $1;
	                   }
;


symbolRange: LBRACKETTOKEN variableWorkAround RBRACKETTOKEN
                           {
			     if (!containsEntry(symbolTable2,$2)) {
			       printMessage(1,"Warning: the identifier \"%s\" is not bound by assignment.\n",$2);
			       printMessage(1,"Will take [-1;1] for \"%s\".\n",$2);
			       range_temp.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			       range_temp.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
			       mpfr_init2(*(range_temp.a),defaultprecision);
			       mpfr_init2(*(range_temp.b),defaultprecision);
			       mpfr_set_d(*(range_temp.a),-1.0,GMP_RNDN);
			       mpfr_set_d(*(range_temp.b),1.0,GMP_RNDN);
			     } else {
			       rangeTempPtr = getEntry(symbolTable2,$2,copyRangetypePtr);
			       range_temp.a = rangeTempPtr->a;
			       range_temp.b = rangeTempPtr->b;
			       free(rangeTempPtr);
			     }
			     free($2);
			     $$ = range_temp;
	                   }
;


directrange:  LBRACKETTOKEN rangeconstant SEMICOLONTOKEN rangeconstant RBRACKETTOKEN
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
      | LEFTANGLETOKEN LBRACKETTOKEN commandfunction RBRACKETTOKEN RIGHTANGLETOKEN
                           {
			     $$ = $3;
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
        | BINARYCONSTTOKEN {
			     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     mpfr_temp2 = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp2,tools_precision);
			     mpfr_set_str(*mpfr_temp,$1,2,GMP_RNDD);
			     mpfr_set_str(*mpfr_temp2,$1,2,GMP_RNDU);
			     if (mpfr_cmp(*mpfr_temp,*mpfr_temp2) != 0) {
			       printMessage(1,
                            "Warning: Rounding occured when converting constant \"%s_2\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			       mpfr_set_str(*mpfr_temp,$1,10,GMP_RNDN);
			     } 
			     mpfr_clear(*mpfr_temp2);
			     free(mpfr_temp2);
			     $$ = mpfr_temp;
	                   }
        | HEXCONSTTOKEN    {
	                     mpfr_temp = (mpfr_t*) safeMalloc(sizeof(mpfr_t));
			     mpfr_init2(*mpfr_temp,tools_precision);
			     if (!readHexa(*mpfr_temp,$1)) {
			       printMessage(1,
                            "Warning: Rounding occured when converting the hexadecimal constant \"%s\" to floating-point with %d bits.\n",
				      $1,(int) tools_precision);
			       printMessage(1,"If safe computation is needed, try to increase the precision.\n");
			     }
			     if (!mpfr_number_p(*mpfr_temp)) {
			       fprintf(stderr,
			  "Error: overflow occured during the conversion of the hexadecimal constant \"%s\". Will abort the computation.\n",$1);
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


integer:                   CONSTTOKEN 
                           {  
			     int_temp = (unsigned long int) strtol($1,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: The number given in this context must be integer. Will interpret the constant as 0.\n");
			       int_temp = 0;
			     }
			     $$ = int_temp;                           
			   }
                         | MINUSTOKEN CONSTTOKEN 
                           {  
			     int_temp = (unsigned long int) strtol($2,endptr,10);
                             if (**endptr != '\0') {
			       printMessage(1,"Warning: The number given in this context must be integer. Will interpret the constant as 0.\n");
			       int_temp = 0;
			     }
			     $$ = -int_temp;                           
			   }
;

monomialsAndPrecision:     monomials COMMATOKEN format
                           {
			     chain_temp = NULL;
			     int_temp = lengthChain($1);
			     for (int_temp2=0;int_temp2<int_temp;int_temp2++) {
			       formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			       formatTypeTemp->formatType = ($3)->formatType;
			       formatTypeTemp->prec = ($3)->prec;
			       if (formatTypeTemp->formatType == TI_FORMAT) {
				 mpfr_temp = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
				 mpfr_init2(*mpfr_temp,mpfr_get_prec(*(($3)->tiValue)));
				 mpfr_set(*mpfr_temp,*(($3)->tiValue),GMP_RNDN);
				 formatTypeTemp->tiValue = mpfr_temp;
			       }
			       chain_temp = addElement(chain_temp,(void *) formatTypeTemp);
			     }
			     doubleChainTemp = (doubleChain *) safeMalloc(sizeof(doubleChain));
			     doubleChainTemp->a = $1;
			     doubleChainTemp->b = chain_temp;
			     freeFormatTypePtr($3);
			     $$ = doubleChainTemp;
			   }
                         | monomials COMMATOKEN LBRACKETTOKEN formatlist RBRACKETTOKEN
                           {
			     if (lengthChain($1) != lengthChain($4)) {
			       printMessage(1,"Warning: the number of the coefficients to be present in the polynomial asked for and the number of their precisions do not correspond.\n");
			       printMessage(1,"The last command will be aborted and have no effect.\n");
			       recoverFromError();
			     }
			     doubleChainTemp = (doubleChain *) safeMalloc(sizeof(doubleChain));
			     doubleChainTemp->a = $1;
			     doubleChainTemp->b = $4;
			     $$ = doubleChainTemp;
			   }
;


format:                    DOUBLETOKEN
                           {
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = DOUBLE_FORMAT;
			     $$ = formatTypeTemp;
			   }
                         | DOUBLEDOUBLETOKEN
                           {
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = DOUBLEDOUBLE_FORMAT;
			     $$ = formatTypeTemp;
			   }
                         | TRIPLEDOUBLETOKEN
                           {
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = TRIPLEDOUBLE_FORMAT;
			     $$ = formatTypeTemp;
			   }
                         | integer
                           {
			     int_temp = $1;
			     if (int_temp < 0) {
			       printMessage(1,"Precisions must be positive integers. Will do precision 0 here.\n");
			       int_temp = 0;
			     }
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = PRECISION_FORMAT;
			     formatTypeTemp->prec = int_temp;
			     $$ = formatTypeTemp;
			   }
                         | MITOKEN EQUALTOKEN integer
                           {
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = MI_FORMAT;
			     formatTypeTemp->prec = $3;
			     $$ = formatTypeTemp;			     
			   }
                         | TITOKEN EQUALTOKEN constantfunction
                           {
			     formatTypeTemp = (formatType *) safeMalloc(sizeof(formatType));
			     formatTypeTemp->formatType = TI_FORMAT;
			     formatTypeTemp->tiValue = $3;
			     $$ = formatTypeTemp;			     
			   }
;

formatlist:                format
                           {
			     $$ = addElement(NULL,(void *) $1);
			   }
                         | format COMMATOKEN formatlist
                           {
			     $$ = addElement($3,(void *) $1);
			   }
;




errordefinition:           ABSOLUTETOKEN
                           {
			     errorTypeTemp = (errorType *) safeMalloc(sizeof(errorType));
			     errorTypeTemp->errorType = ABSOLUTE_ERROR;
			     $$ = errorTypeTemp;
			   }
                         | RELATIVETOKEN
                           {
			     errorTypeTemp = (errorType *) safeMalloc(sizeof(errorType));
			     errorTypeTemp->errorType = RELATIVE_ERROR;
			     $$ = errorTypeTemp;
			   }
                         | WEIGHTTOKEN EQUALTOKEN function
                           {
			     errorTypeTemp = (errorType *) safeMalloc(sizeof(errorType));
			     errorTypeTemp->errorType = WEIGHTFUNCTION_ERROR;
			     errorTypeTemp->weightFunction = $3;
			     $$ = errorTypeTemp;
			   }
;


pointsdefinition:          EQUITOKEN
                           {
			     pointsTypeTemp = (pointsType *) safeMalloc(sizeof(pointsType));
			     pointsTypeTemp->pointsType = EQUI_POINTS;
			     $$ = pointsTypeTemp;
			   }
                         | CHEBTOKEN
                           {
			     pointsTypeTemp = (pointsType *) safeMalloc(sizeof(pointsType));
			     pointsTypeTemp->pointsType = CHEB_POINTS;
			     $$ = pointsTypeTemp;
			   }
                         | REMEZTOKEN
                           {
			     pointsTypeTemp = (pointsType *) safeMalloc(sizeof(pointsType));
			     pointsTypeTemp->pointsType = REMEZ_POINTS;
			     $$ = pointsTypeTemp;
			   }
                         | LBRACKETTOKEN pointslist RBRACKETTOKEN
                           {
			     pointsTypeTemp = (pointsType *) safeMalloc(sizeof(pointsType));
			     pointsTypeTemp->pointsType = USER_POINTS;
			     pointsTypeTemp->pointsList = $2;
			     $$ = pointsTypeTemp;
			   }
;

pointslist:                constantfunction
                           {
			     $$ = addElement(NULL,(void *) $1);
			   }
                         | pointslist COMMATOKEN constantfunction
                           {
			     $$ = addElement($1,(void *) $3);
			   }
;


fpminimax:                 FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range RPARTOKEN
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, NULL, -1, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, NULL, -1, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN pointsdefinition RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, $9, -1, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freePointsTypePtr($9);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN integer RPARTOKEN 
                           {
			     int_temp = $9;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, NULL, int_temp, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN writefile RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, NULL, -1, $9);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     fclose($9);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN pointsdefinition RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, $11, -1, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     freePointsTypePtr($11);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN integer RPARTOKEN 
                           {
			     int_temp = $11;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, NULL, int_temp, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN writefile RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, NULL, -1, $11);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     fclose($11);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN pointsdefinition COMMATOKEN integer RPARTOKEN 
                           {
			     int_temp = $11;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, $9, int_temp, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freePointsTypePtr($9);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN pointsdefinition COMMATOKEN writefile RPARTOKEN 
                           {
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, $9, -1, $11);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freePointsTypePtr($9);
			     fclose($11);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN integer COMMATOKEN writefile RPARTOKEN 
                           {
			     int_temp = $9;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, NULL, int_temp, $11);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     fclose($11);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN pointsdefinition COMMATOKEN integer RPARTOKEN 
                           {
			     int_temp = $13;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, $11, int_temp, NULL);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     freePointsTypePtr($11);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN integer COMMATOKEN writefile RPARTOKEN 
                           {
			     int_temp = $11;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, NULL, int_temp, $13);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     fclose($13);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN pointsdefinition COMMATOKEN integer COMMATOKEN writefile RPARTOKEN 
                           {
			     int_temp = $11;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), NULL, $9, int_temp, $13);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freePointsTypePtr($9);
			     fclose($13);
			     $$ = temp_node;
			   }
                         | FPMINIMAXTOKEN LPARTOKEN function COMMATOKEN monomialsAndPrecision COMMATOKEN range COMMATOKEN errordefinition COMMATOKEN pointsdefinition COMMATOKEN integer COMMATOKEN writefile RPARTOKEN 
                           {
			     int_temp = $13;
			     if (int_temp < 1) {
			       printMessage(1,"The quality parameter must be a non-zero positive integer. Will do default quality.\n");
			       int_temp = -1;
			     } 
			     temp_node = fpminimax($3, $5->a, $5->b, *($7.a), *($7.b), $9, $11, int_temp, $15);
			     free_memory($3);
			     freeChain($5->a,freeIntPtr);
			     freeChain($5->b,freeFormatTypePtr);
			     free($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);
			     free($7.b);
			     freeErrorTypePtr($9);
			     freePointsTypePtr($11);
			     fclose($15);
			     $$ = temp_node;
			   }
;



expansionFormat:           DOUBLETOKEN
                           {
			     $$ = 1;
			   }
                         | DOUBLEDOUBLETOKEN
                           {
			     $$ = 2;
			   }
                         | TRIPLEDOUBLETOKEN
                           {
			     $$ = 3;
			   }
                         | DOUBLEEXTENDEDTOKEN
                           {
			     $$ = 4;
			   }
;

expansionFormatList:       expansionFormat
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = $1;
			     $$ = addElement(NULL,(void *) intTempPtr);
                           }
                         | expansionFormatList COMMATOKEN expansionFormat
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = $3;
			     $$ = addElement($1,(void *) intTempPtr);
			   }
;

expansionFormats:          LBRACKETTOKEN expansionFormatList RBRACKETTOKEN
                           {
			     $$ = $2;
			   }
                         | LBRACKETTOKEN expansionFormatList COMMATOKEN DOTSTOKEN RBRACKETTOKEN
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = -1;
			     $$ = addElement($2,(void *) intTempPtr);
			   }
;

roundcoefficients:         ROUNDCOEFFICIENTSTOKEN LPARTOKEN function COMMATOKEN expansionFormats RPARTOKEN
                           {
			     temp_node = roundPolynomialCoefficients($3, $5, defaultprecision);
			     free_memory($3);
			     freeChain($5,freeIntPtr);
			     $$ = temp_node;
			   }
;

bashexecute:               BASHEXECUTETOKEN string 
                           {
			     int_temp = bashExecute($2);
			     free($2);
			     $$ = int_temp;
			   }
;

externalplotmode:          ABSOLUTETOKEN
                           {
			     $$ = ABSOLUTE;
                           }
                         | RELATIVETOKEN
                           {
			     $$ = RELATIVE;
			   }
;


externalplot:              EXTERNALPLOTTOKEN string externalplotmode TOTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN 
                           {
			     externalPlot($2, *($7.a), *($7.b), (mp_prec_t) $9, 0, $5, $3, defaultprecision, NULL, -1);
			     free($2);
			     free_memory($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);			    
			     free($7.b);
			     $$ = NULL;
                           }
                         | EXTERNALPLOTTOKEN string externalplotmode TOTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN COMMATOKEN PERTURBTOKEN
                           {
			     externalPlot($2, *($7.a), *($7.b), (mp_prec_t) $9, 1, $5, $3, defaultprecision, NULL, -1);
			     free($2);
			     free_memory($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);			    
			     free($7.b);
			     $$ = NULL;
                           }
                         | EXTERNALPLOTTOKEN string externalplotmode TOTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN COMMATOKEN PERTURBTOKEN COMMATOKEN plottype EQUALTOKEN string
                           {
			     externalPlot($2, *($7.a), *($7.b), (mp_prec_t) $9, 1, $5, $3, defaultprecision, $16, $14);
			     free($2);
			     free_memory($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);			    
			     free($7.b);
			     free($16);
			     $$ = NULL;
                           }
                         | EXTERNALPLOTTOKEN string externalplotmode TOTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN COMMATOKEN plottype EQUALTOKEN string
                           {
			     externalPlot($2, *($7.a), *($7.b), (mp_prec_t) $9, 0, $5, $3, defaultprecision, $14, $12);
			     free($2);
			     free_memory($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);			    
			     free($7.b);
			     free($14);
			     $$ = NULL;
                           }
                         | EXTERNALPLOTTOKEN string externalplotmode TOTOKEN function INTOKEN range WITHTOKEN integer BITSTOKEN COMMATOKEN plottype EQUALTOKEN string COMMATOKEN PERTURBTOKEN 
                           {
			     externalPlot($2, *($7.a), *($7.b), (mp_prec_t) $9, 1, $5, $3, defaultprecision, $14, $12);
			     free($2);
			     free_memory($5);
			     mpfr_clear(*($7.a));
			     mpfr_clear(*($7.b));
			     free($7.a);			    
			     free($7.b);
			     free($14);
			     $$ = NULL;
                           }
;


integerlist:               integer 
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = $1;
			     $$ = addElement(NULL,(void *) intTempPtr);
                           }
                         | integerlist COMMATOKEN integer
                           {
			     intTempPtr = (int *) safeMalloc(sizeof(int));
			     *intTempPtr = $3;
			     $$ = addElement($1,(void *) intTempPtr);
			   }
                         |     integer DOTSTOKEN integer
                           {
			     if (($1) > ($3)) {
			       printMessage(1,"Warning: the bounds given for a elliptic list are not in ascending order.\nThis list or sublist will not be taken into account.\n");
			     }
			     chain_temp = makeIntPtrChainFromTo(($1),($3));
			     $$ = chain_temp;
			   }
                         |     integerlist COMMATOKEN integer DOTSTOKEN integer 
                           {
			     if (($3) > ($5)) {
			       printMessage(1,"Warning: the bounds given for a elliptic list are not in ascending order.\nThis list or sublist will not be taken into account.\n");
			     }
			     chain_temp = makeIntPtrChainFromTo(($3),($5));
			     chain_temp = concatChains(($1),chain_temp);
			     $$ = chain_temp;
			   }
;

