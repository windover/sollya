#include <mpfr.h>
#include <mpfi.h>
#include <gmp.h>
#include "execute.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include "main.h"
#include "expression.h"
#include "infnorm.h"
#include "assignment.h"
#include "library.h"
#include "external.h"
#include "plot.h"
#include "remez.h"
#include "integral.h"
#include "double.h"
#include "worstcase.h"
#include "implement.h"
#include "taylor.h"
#include "xml.h"

node *copyThing(node *);
node *evaluateThingInner(node *);
node *evaluateThing(node *);

void *copyStringOnVoid(void *s) {
  char *copy;

  copy = (char *) safeCalloc(strlen((char *) s)+1,sizeof(char));
  strcpy(copy,(char *) s);
  
  return (void *) copy;
}

void *copyThingOnVoid(void *);

node *copyThing(node *tree) {
  node *copy;

  if (tree == NULL) return NULL;

  copy = (node *) safeMalloc(sizeof(node));
  copy->nodeType = tree->nodeType;

  switch (tree->nodeType) {
  case VARIABLE:
    break;
  case CONSTANT:
    copy->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(copy->value),mpfr_get_prec(*(tree->value)));
    mpfr_set(*(copy->value),*(tree->value),GMP_RNDN);
    break;
  case ADD:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;
  case SUB:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;
  case MUL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;
  case DIV:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;
  case SQRT:
    copy->child1 = copyThing(tree->child1);
    break;
  case EXP:
    copy->child1 = copyThing(tree->child1);
    break;
  case LOG:
    copy->child1 = copyThing(tree->child1);
    break;
  case LOG_2:
    copy->child1 = copyThing(tree->child1);
    break;
  case LOG_10:
    copy->child1 = copyThing(tree->child1);
    break;
  case SIN:
    copy->child1 = copyThing(tree->child1);
    break;
  case COS:
    copy->child1 = copyThing(tree->child1);
    break;
  case TAN:
    copy->child1 = copyThing(tree->child1);
    break;
  case ASIN:
    copy->child1 = copyThing(tree->child1);
    break;
  case ACOS:
    copy->child1 = copyThing(tree->child1);
    break;
  case ATAN:
    copy->child1 = copyThing(tree->child1);
    break;
  case SINH:
    copy->child1 = copyThing(tree->child1);
    break;
  case COSH:
    copy->child1 = copyThing(tree->child1);
    break;
  case TANH:
    copy->child1 = copyThing(tree->child1);
    break;
  case ASINH:
    copy->child1 = copyThing(tree->child1);
    break;
  case ACOSH:
    copy->child1 = copyThing(tree->child1);
    break;
  case ATANH:
    copy->child1 = copyThing(tree->child1);
    break;
  case POW:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;
  case NEG:
    copy->child1 = copyThing(tree->child1);
    break;
  case ABS:
    copy->child1 = copyThing(tree->child1);
    break;
  case DOUBLE:
    copy->child1 = copyThing(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy->child1 = copyThing(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy->child1 = copyThing(tree->child1);
    break;
  case ERF: 
    copy->child1 = copyThing(tree->child1);
    break;
  case ERFC:
    copy->child1 = copyThing(tree->child1);
    break;
  case LOG_1P:
    copy->child1 = copyThing(tree->child1);
    break;
  case EXP_M1:
    copy->child1 = copyThing(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy->child1 = copyThing(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = copyThing(tree->child1);
    break;
  case CEIL:
    copy->child1 = copyThing(tree->child1);
    break;
  case FLOOR:
    copy->child1 = copyThing(tree->child1);
    break;
  case PI_CONST:
    break;
  case COMMANDLIST:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break;			
  case WHILE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;				
  case IFELSE:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 				
  case IF:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 				
  case FOR:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 				
  case FORIN:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break;  				
  case QUIT:
    break;  				
  case FALSEQUIT:
    break; 			
  case RESTART:
    break;  			
  case PRINT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 				
  case NEWFILEPRINT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    copy->child1 = copyThing(tree->child1);
    break; 			
  case APPENDFILEPRINT:
    copy->child1 = copyThing(tree->child1);
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case PLOT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break;			
  case PRINTHEXA:
    copy->child1 = copyThing(tree->child1);
    break; 
  case PRINTBINARY:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case PRINTEXPANSION:
    copy->child1 = copyThing(tree->child1);
    break;
  case BASHEXECUTE:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case EXTERNALPLOT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 
  case WRITE:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case NEWFILEWRITE:
    copy->child1 = copyThing(tree->child1);
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break;
  case APPENDFILEWRITE:
    copy->child1 = copyThing(tree->child1);
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 
  case ASCIIPLOT:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;			
  case PRINTXML:
    copy->child1 = copyThing(tree->child1);
    break;			
  case PRINTXMLNEWFILE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;			
  case PRINTXMLAPPENDFILE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;			
  case WORSTCASE:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case RENAME:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyStringOnVoid);
    break; 				
  case AUTOPRINT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break;  			
  case ASSIGNMENT:
    copy->child1 = copyThing(tree->child1);
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			
  case LIBRARYBINDING:
    copy->child1 = copyThing(tree->child1);
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break;  			
  case PRECASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case POINTSASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case DIAMASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;			
  case DISPLAYASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case VERBOSITYASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  		
  case CANONICALASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case AUTOSIMPLIFYASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  		
  case TAYLORRECURSASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case TIMINGASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case FULLPARENASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  		
  case MIDPOINTASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case HOPITALRECURSASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case PRECSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case POINTSSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case DIAMSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case DISPLAYSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  		
  case VERBOSITYSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case CANONICALSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 	
  case TIMINGSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case FULLPARENSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  		
  case MIDPOINTSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    copy->child1 = copyThing(tree->child1);
    break;  	
  case AND:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 				
  case OR:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;				
  case NEGATION:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case INDEX:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 				
  case COMPAREEQUAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case COMPARELESS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case COMPAREGREATER:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case COMPARELESSEQUAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 		
  case COMPAREGREATEREQUAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;		
  case COMPARENOTEQUAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;		
  case CONCAT:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case ADDTOLIST:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case ON:
    break; 				
  case OFF:
    break; 				
  case DYADIC:
    break;  				
  case POWERS:
    break; 				
  case BINARY:
    break; 			 	
  case FILESYM:
    break; 			 	
  case POSTSCRIPT:
    break;  			
  case POSTSCRIPTFILE:
    break; 			
  case PERTURB:
    break; 			
  case ROUNDDOWN:
    break; 			
  case ROUNDUP:
    break; 			
  case ROUNDTOZERO:
    break;  			
  case ROUNDTONEAREST:
    break; 			
  case HONORCOEFF:
    break; 			
  case TRUE:
    break; 			 	
  case FALSE:
    break; 			 	
  case DEFAULT:
    break; 			
  case DECIMAL:
    break; 			
  case ABSOLUTESYM:
    break; 			
  case RELATIVESYM:
    break; 			
  case ERRORSPECIAL:
    break; 			
  case DOUBLESYMBOL:
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    break;  			
  case DOUBLEDOUBLESYMBOL:
    break; 		
  case TRIPLEDOUBLESYMBOL:
    break; 		
  case STRING:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			 	
  case TABLEACCESS:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    copy->child1 = copyThing(tree->child1);
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break;  	
  case DECIMALCONSTANT:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 		
  case DYADICCONSTANT:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			
  case HEXCONSTANT:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			
  case BINARYCONSTANT:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			
  case EMPTYLIST:
    break; 			
  case LIST:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			 	
  case FINALELLIPTICLIST:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 		
  case ELLIPTIC:
    break; 			
  case RANGE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			 	
  case DEBOUNDMAX:
    copy->child1 = copyThing(tree->child1);
    break;  			
  case DEBOUNDMIN:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case DEBOUNDMID:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case DIFF:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case SIMPLIFY:
    copy->child1 = copyThing(tree->child1);
    break;  			
  case SIMPLIFYSAFE:
    copy->child1 = copyThing(tree->child1);
    break;  			
  case REMEZ:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			 	
  case HORNER:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case CANONICAL:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case EXPAND:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case TAYLOR:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			 	
  case DEGREE:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case NUMERATOR:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case DENOMINATOR:
    copy->child1 = copyThing(tree->child1);
    break; 			
  case SUBSTITUTE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;			
  case COEFF:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			 	
  case SUBPOLY:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case ROUNDCOEFFICIENTS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 		
  case RATIONALAPPROX:    
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case ACCURATEINFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 		
  case ROUNDTOFORMAT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break;			
  case EVALUATE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case PARSE:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case READXML:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case INFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case FINDZEROS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case FPFINDZEROS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case DIRTYINFNORM:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case INTEGRAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case DIRTYINTEGRAL:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;  			
  case IMPLEMENTPOLY:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case CHECKINFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case ZERODENOMINATORS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break;  		
  case ISEVALUABLE:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case SEARCHGAL:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case GUESSDEGREE:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case ASSIGNMENTININDEXING:
    copy->arguments = copyChainWithoutReversal(tree->arguments, copyThingOnVoid);
    break; 			
  case DIRTYFINDZEROS:
    copy->child1 = copyThing(tree->child1);
    copy->child2 = copyThing(tree->child2);
    break; 			
  case HEAD:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case TAIL:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case LENGTH:
    copy->child1 = copyThing(tree->child1);
    break; 			 	
  case PRECDEREF:
    break; 			
  case POINTSDEREF:
    break; 			
  case DIAMDEREF:
    break; 			
  case DISPLAYDEREF:
    break; 			
  case VERBOSITYDEREF:
    break; 			
  case CANONICALDEREF:
    break; 			
  case AUTOSIMPLIFYDEREF:
    break; 		
  case TAYLORRECURSDEREF:
    break; 		
  case TIMINGDEREF:
    break; 			
  case FULLPARENDEREF:
    break; 			
  case MIDPOINTDEREF:
    break; 			
  case HOPITALRECURSDEREF:
    break;  	       
  default:
    fprintf(stderr,"Error: copyThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }

  return copy;
}



void *copyThingOnVoid(void *tree) {
  return (void *) copyThing((node *) tree);
}

char *getTimingStringForThing(node *tree) {
  char *constString, *newString;

  if (tree == NULL) return NULL;

  switch (tree->nodeType) {
  case VARIABLE:
    constString = NULL;
    break;
  case CONSTANT:
    constString = NULL;
    break;
  case ADD:
    constString = NULL;
    break;
  case SUB:
    constString = NULL;
    break;
  case MUL:
    constString = NULL;
    break;
  case DIV:
    constString = NULL;
    break;
  case SQRT:
    constString = NULL;
    break;
  case EXP:
    constString = NULL;
    break;
  case LOG:
    constString = NULL;
    break;
  case LOG_2:
    constString = NULL;
    break;
  case LOG_10:
    constString = NULL;
    break;
  case SIN:
    constString = NULL;
    break;
  case COS:
    constString = NULL;
    break;
  case TAN:
    constString = NULL;
    break;
  case ASIN:
    constString = NULL;
    break;
  case ACOS:
    constString = NULL;
    break;
  case ATAN:
    constString = NULL;
    break;
  case SINH:
    constString = NULL;
    break;
  case COSH:
    constString = NULL;
    break;
  case TANH:
    constString = NULL;
    break;
  case ASINH:
    constString = NULL;
    break;
  case ACOSH:
    constString = NULL;
    break;
  case ATANH:
    constString = NULL;
    break;
  case POW:
    constString = NULL;
    break;
  case NEG:
    constString = NULL;
    break;
  case ABS:
    constString = NULL;
    break;
  case DOUBLE:
    constString = NULL;
    break;
  case DOUBLEDOUBLE:
    constString = NULL;
    break;
  case TRIPLEDOUBLE:
    constString = NULL;
    break;
  case ERF: 
    constString = NULL;
    break;
  case ERFC:
    constString = NULL;
    break;
  case LOG_1P:
    constString = NULL;
    break;
  case EXP_M1:
    constString = NULL;
    break;
  case DOUBLEEXTENDED:
    constString = NULL;
    break;
  case LIBRARYFUNCTION:
    constString = NULL;
    break;
  case CEIL:
    constString = NULL;
    break;
  case FLOOR:
    constString = NULL;
    break;
  case PI_CONST:
    constString = NULL;
    break;
  case COMMANDLIST:
    constString = "begin-end statement";
    break;			
  case WHILE:
    constString = "while loop";
    break;				
  case IFELSE:
    constString = "if-then-else statement";
    break; 				
  case IF:
    constString = "if-then statement";
    break; 				
  case FOR:
    constString = "for loop";
    break; 				
  case FORIN:
    constString = "for-in loop";
    break;  				
  case QUIT:
    constString = NULL;
    break;  				
  case FALSEQUIT:
    constString = NULL;
    break; 			
  case RESTART:
    constString = NULL;
    break;  			
  case PRINT:
    constString = "print statement";
    break; 				
  case NEWFILEPRINT:
    constString = "print-into-new-file statement";
    break; 			
  case APPENDFILEPRINT:
    constString = "print-into-file statement";
    break; 			
  case PLOT:
    constString = "plot statement";
    break;			
  case PRINTHEXA:
    constString = "printhexa statement";
    break; 
  case PRINTBINARY:
    constString = "printbinary statement";
    break; 			
  case PRINTEXPANSION:
    constString = "printexpansion statement";
    break;
  case BASHEXECUTE:
    constString = "bashexecute statement";
    break; 			
  case EXTERNALPLOT:
    constString = "externalplot statement";
    break; 
  case WRITE:
    constString = "write statement";
    break; 			
  case NEWFILEWRITE:
    constString = "write-into-new-file statement";
    break;
  case APPENDFILEWRITE:
    constString = "write-into-file statement";
    break; 
  case ASCIIPLOT:
    constString = "asciiplot statement";
    break;			
  case PRINTXML:
    constString = "printing in xml mode";
    break;			
  case PRINTXMLNEWFILE:
    constString = "printing in xml mode into a new file";
    break;			
  case PRINTXMLAPPENDFILE:
    constString = "printing in xml mode into a file";
    break;			
  case WORSTCASE:
    constString = "worstcase statement";
    break; 			
  case RENAME:
    constString = "rename statement";
    break; 				
  case AUTOPRINT:
    constString = "automatic printing of expressions";
    break;  			
  case ASSIGNMENT:
    constString = "assignment";
    break; 			
  case LIBRARYBINDING:
    constString = "binding of a library";
    break;  			
  case PRECASSIGN:
    constString = "assigning the precision";
    break; 			
  case POINTSASSIGN:
    constString = "assigning the point number";
    break; 			
  case DIAMASSIGN:
    constString = "assigning the diameter";
    break;			
  case DISPLAYASSIGN:
    constString = "assigning the display mode";
    break; 			
  case VERBOSITYASSIGN:
    constString = "assigning the verbosity";
    break;  		
  case CANONICALASSIGN:
    constString = "assigning the canonical printing mode";
    break; 		
  case AUTOSIMPLIFYASSIGN:
    constString = "assigning the automatic simplification mode";
    break;  		
  case TAYLORRECURSASSIGN:
    constString = "assigning the number of recursions for Taylor";
    break; 		
  case TIMINGASSIGN:
    constString = "assigning the timing mode";
    break; 			
  case FULLPARENASSIGN:
    constString = "full parenthezation mode";
    break;  		
  case MIDPOINTASSIGN:
    constString = "assigning the midpoint printing mode";
    break; 			
  case HOPITALRECURSASSIGN:
    constString = "assigning the number of recursions for Hopital";
    break; 		
  case PRECSTILLASSIGN:
    constString = NULL;
    break; 		
  case POINTSSTILLASSIGN:
    constString = NULL;
    break; 		
  case DIAMSTILLASSIGN:
    constString = NULL;
    break; 		
  case DISPLAYSTILLASSIGN:
    constString = NULL;
    break;  		
  case VERBOSITYSTILLASSIGN:
    constString = NULL;
    break; 		
  case CANONICALSTILLASSIGN:
    constString = NULL;
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    constString = NULL;
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    constString = NULL;
    break; 	
  case TIMINGSTILLASSIGN:
    constString = NULL;
    break; 		
  case FULLPARENSTILLASSIGN:
    constString = NULL;
    break;  		
  case MIDPOINTSTILLASSIGN:
    constString = NULL;
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    constString = NULL;
    break;  	
  case AND:
    constString = NULL;
    break; 				
  case OR:
    constString = NULL;
    break;				
  case NEGATION:
    constString = NULL;
    break; 			
  case INDEX:
    constString = "indexing in a string or list";
    break; 				
  case COMPAREEQUAL:
    constString = "compare equal";
    break; 			
  case COMPARELESS:
    constString = "compare less";
    break; 			
  case COMPAREGREATER:
    constString = "compare greater";
    break; 			
  case COMPARELESSEQUAL:
    constString = "compare less or equal";
    break; 		
  case COMPAREGREATEREQUAL:
    constString = "compare greater or equal";
    break;		
  case COMPARENOTEQUAL:
    constString = "compare not equal";
    break;		
  case CONCAT:
    constString = "concatination of strings or lists";
    break; 			
  case ADDTOLIST:
    constString = "adding an element to a list";
    break; 			
  case ON:
    constString = NULL;
    break; 				
  case OFF:
    constString = NULL;
    break; 				
  case DYADIC:
    constString = NULL;
    break;  				
  case POWERS:
    constString = NULL;
    break; 				
  case BINARY:
    constString = NULL;
    break; 			 	
  case FILESYM:
    constString = NULL;
    break; 			 	
  case POSTSCRIPT:
    constString = NULL;
    break;  			
  case POSTSCRIPTFILE:
    constString = NULL;
    break; 			
  case PERTURB:
    constString = NULL;
    break; 			
  case ROUNDDOWN:
    constString = NULL;
    break; 			
  case ROUNDUP:
    constString = NULL;
    break; 			
  case ROUNDTOZERO:
    constString = NULL;
    break;  			
  case ROUNDTONEAREST:
    constString = NULL;
    break; 			
  case HONORCOEFF:
    constString = NULL;
    break; 			
  case TRUE:
    constString = NULL;
    break; 			 	
  case FALSE:
    constString = NULL;
    break; 			 	
  case DEFAULT:
    constString = NULL;
    break; 			
  case DECIMAL:
    constString = NULL;
    break; 			
  case ABSOLUTESYM:
    constString = NULL;
    break; 			
  case RELATIVESYM:
    constString = NULL;
    break; 			
  case ERRORSPECIAL:
    constString = NULL;
    break; 			
  case DOUBLESYMBOL:
    constString = NULL;
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    constString = NULL;
    break;  			
  case DOUBLEDOUBLESYMBOL:
    constString = NULL;
    break; 		
  case TRIPLEDOUBLESYMBOL:
    constString = NULL;
    break; 		
  case STRING:
    constString = NULL;
    break; 			 	
  case TABLEACCESS:
    constString = "dereferencing an identifier";
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    constString = "dereferencing an identifier and substituting";
    break;  	
  case DECIMALCONSTANT:
    constString = "reading a decimal constant";
    break; 		
  case DYADICCONSTANT:
    constString = "reading a dyadic constant";
    break; 			
  case HEXCONSTANT:
    constString = "reading a hexadecimal constant";
    break; 			
  case BINARYCONSTANT:
    constString = "reading a binary constant";
    break; 			
  case EMPTYLIST:
    constString = NULL;
    break; 			
  case LIST:
    constString = "handling a list";
    break; 			 	
  case FINALELLIPTICLIST:
    constString = "handling a finally elliptic list";
    break; 		
  case ELLIPTIC:
    constString = NULL;
    break; 			
  case RANGE:
    constString = "handling a range";
    break; 			 	
  case DEBOUNDMAX:
    constString = NULL;
    break;  			
  case DEBOUNDMIN:
    constString = NULL;
    break; 			
  case DEBOUNDMID:
    constString = NULL;
    break; 			
  case DIFF:
    constString = "differentiation";
    break; 			 	
  case SIMPLIFY:
    constString = "simplifying";
    break;  			
  case SIMPLIFYSAFE:
    constString = "simplifying without rounding";
    break;  			
  case REMEZ:
    constString = "computing a minimax approximation";
    break; 			 	
  case HORNER:
    constString = "convertion to horner notation";
    break; 			 	
  case CANONICAL:
    constString = "convertion to canonical notation";
    break; 			
  case EXPAND:
    constString = "expanding an expression";
    break; 			 	
  case TAYLOR:
    constString = "taylor";
    break; 			 	
  case DEGREE:
    constString = "getting the degree";
    break; 			 	
  case NUMERATOR:
    constString = "getting the numerator";
    break; 			
  case DENOMINATOR:
    constString = "getting the denominator";
    break; 			
  case SUBSTITUTE:
    constString = "substituting";
    break;			
  case COEFF:
    constString = "getting a coefficient";
    break; 			 	
  case SUBPOLY:
    constString = "getting a sub-polynomial";
    break; 			
  case ROUNDCOEFFICIENTS:
    constString = "rounding coefficients";
    break; 		
  case RATIONALAPPROX:    
    constString = "computing a rational approximation";
    break; 			
  case ACCURATEINFNORM:
    constString = "computing an accurate infinite norm";
    break; 		
  case ROUNDTOFORMAT:
    constString = "rounding to a format";
    break;			
  case EVALUATE:
    constString = "evaluating";
    break; 			
  case PARSE:
    constString = "parsing a mini-expression";
    break; 			 	
  case READXML:
    constString = "reading a XML-tree";
    break; 			 	
  case INFNORM:
    constString = "computing an infinite norm";
    break; 			
  case FINDZEROS:
    constString = "bounding zeros";
    break; 			
  case FPFINDZEROS:
    constString = "searching zeros";
    break; 			
  case DIRTYINFNORM:
    constString = "computing an infinite norm dirtily";
    break; 			
  case INTEGRAL:
    constString = "computing an integral";
    break; 			
  case DIRTYINTEGRAL:
    constString = "computing an integral dirtily";
    break;  			
  case IMPLEMENTPOLY:
    constString = "implementing a polynomial";
    break; 			
  case CHECKINFNORM:
    constString = "checking an infinite norm";
    break; 			
  case ZERODENOMINATORS:
    constString = "searching zeros of denominators";
    break;  		
  case ISEVALUABLE:
    constString = "testing if evaluable";
    break; 			
  case SEARCHGAL:
    constString = "searching a Gal value";
    break; 			
  case GUESSDEGREE:
    constString = "guessing a degree for Remez";
    break; 			
  case ASSIGNMENTININDEXING:
    constString = "assigning to an indexed element of a list";
    break; 			
  case DIRTYFINDZEROS:
    constString = "searching zeros dirtily";
    break; 			
  case HEAD:
    constString = NULL;
    break; 			 	
  case TAIL:
    constString = NULL;
    break; 			 	
  case LENGTH:
    constString = "computing the length of a list";
    break; 			 	
  case PRECDEREF:
    constString = "dereferencing the precision of the tool";
    break; 			
  case POINTSDEREF:
    constString = "dereferencing the number of points of the tool";
    break; 			
  case DIAMDEREF:
    constString = "dereferencing the diameter of the tool";
    break; 			
  case DISPLAYDEREF:
    constString = "dereferencing the display mode";
    break; 			
  case VERBOSITYDEREF:
    constString = "dereferencing the verbosity of the tool";
    break; 			
  case CANONICALDEREF:
    constString = "dereferencing the canonical mode state of the tool";
    break; 			
  case AUTOSIMPLIFYDEREF:
    constString = "dereferencing the automatic simplification mode state of the tool";
    break; 		
  case TAYLORRECURSDEREF:
    constString = "dereferencing the number of recursions for Taylor";
    break; 		
  case TIMINGDEREF:
    constString = "dereferencing the timing mode state of the tool";
    break; 			
  case FULLPARENDEREF:
    constString = "dereferencing the full parenthezation mode state of the tool";
    break; 			
  case MIDPOINTDEREF:
    constString = "dereferencing the midpoint mode state of the tool";
    break; 			
  case HOPITALRECURSDEREF:
    constString = "dereferencing the numbers of recursions for Hopital";
    break;  	       
  default:
    fprintf(stderr,"Error: getTimingStringForThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }

  if (constString == NULL) return NULL;

  newString = (char *) safeCalloc(strlen(constString) + 1,sizeof(char));
  strcpy(newString,constString);

  return newString;
}



int isPureTree(node *tree) {
  switch (tree->nodeType) {
  case VARIABLE:
    return 1;
    break;
  case CONSTANT:
    return 1;
    break;
  case ADD:
    return (isPureTree(tree->child1) && isPureTree(tree->child2));
    break;
  case SUB:
    return (isPureTree(tree->child1) && isPureTree(tree->child2));
    break;
  case MUL:
    return (isPureTree(tree->child1) && isPureTree(tree->child2));
    break;
  case DIV:
    return (isPureTree(tree->child1) && isPureTree(tree->child2));
    break;
  case SQRT:
    return isPureTree(tree->child1);
    break;
  case EXP:
    return isPureTree(tree->child1);
    break;
  case LOG:
    return isPureTree(tree->child1);
    break;
  case LOG_2:
    return isPureTree(tree->child1);
    break;
  case LOG_10:
    return isPureTree(tree->child1);
    break;
  case SIN:
    return isPureTree(tree->child1);
    break;
  case COS:
    return isPureTree(tree->child1);
    break;
  case TAN:
    return isPureTree(tree->child1);
    break;
  case ASIN:
    return isPureTree(tree->child1);
    break;
  case ACOS:
    return isPureTree(tree->child1);
    break;
  case ATAN:
    return isPureTree(tree->child1);
    break;
  case SINH:
    return isPureTree(tree->child1);
    break;
  case COSH:
    return isPureTree(tree->child1);
    break;
  case TANH:
    return isPureTree(tree->child1);
    break;
  case ASINH:
    return isPureTree(tree->child1);
    break;
  case ACOSH:
    return isPureTree(tree->child1);
    break;
  case ATANH:
    return isPureTree(tree->child1);
    break;
  case POW:
    return (isPureTree(tree->child1) && isPureTree(tree->child2));
    break;
  case NEG:
    return isPureTree(tree->child1);
    break;
  case ABS:
    return isPureTree(tree->child1);
    break;
  case DOUBLE:
    return isPureTree(tree->child1);
    break;
  case DOUBLEDOUBLE:
    return isPureTree(tree->child1);
    break;
  case TRIPLEDOUBLE:
    return isPureTree(tree->child1);
    break;
  case ERF: 
    return isPureTree(tree->child1);
    break;
  case ERFC:
    return isPureTree(tree->child1);
    break;
  case LOG_1P:
    return isPureTree(tree->child1);
    break;
  case EXP_M1:
    return isPureTree(tree->child1);
    break;
  case DOUBLEEXTENDED:
    return isPureTree(tree->child1);
    break;
  case LIBRARYFUNCTION:
    return isPureTree(tree->child1);
    break;
  case CEIL:
    return isPureTree(tree->child1);
    break;
  case FLOOR:
    return isPureTree(tree->child1);
    break;
  case PI_CONST:
    return 1;
    break;
  default:
    return 0;
  }
}

int isDefault(node *tree) {
  return (tree->nodeType == DEFAULT);
}

int isString(node *tree) {
  return (tree->nodeType == STRING);
}

int isList(node *tree) {
  return (tree->nodeType == LIST);
}

int isEmptyList(node *tree) {
  return (tree->nodeType == EMPTYLIST);
}

int isElliptic(node *tree) {
  return (tree->nodeType == ELLIPTIC);
}


int isPureList(node *tree) {
  chain *curr;

  if (!isList(tree)) return 0;

  curr = tree->arguments;
  while (curr != NULL) {
    if (isElliptic((node *) (curr->value))) return 0;
    curr = curr->next;
  }
  
  return 1;
}

int isFinalEllipticList(node *tree) {
  return (tree->nodeType == FINALELLIPTICLIST);
}

int isPureFinalEllipticList(node *tree) {
  chain *curr;

  if (!isFinalEllipticList(tree)) return 0;

  curr = tree->arguments;
  while (curr != NULL) {
    if (isElliptic((node *) (curr->value))) return 0;
    curr = curr->next;
  }
  
  return 1;
}




int isRange(node *tree) {
  if (tree->nodeType != RANGE) return 0;
  if (tree->child1->nodeType != CONSTANT) return 0;
  if (tree->child2->nodeType != CONSTANT) return 0;
  return 1;
}

int isError(node *tree) {
  if (tree->nodeType == ERRORSPECIAL) return 1;
  return 0;
}


int isBoolean(node *tree) {
  if (tree->nodeType == TRUE) return 1;
  if (tree->nodeType == FALSE) return 1;
  return 0;
}

int isHonorcoeffprec(node *tree) {
  if (tree->nodeType == HONORCOEFF) return 1;
  return 0;
}


int isOnOff(node *tree) {
  if (tree->nodeType == ON) return 1;
  if (tree->nodeType == OFF) return 1;
  return 0;
}

int isDisplayMode(node *tree) {
  if (tree->nodeType == DECIMAL) return 1;
  if (tree->nodeType == DYADIC) return 1;
  if (tree->nodeType == POWERS) return 1;
  if (tree->nodeType == BINARY) return 1;
  return 0;
}

int isRoundingSymbol(node *tree) {
  if (tree->nodeType == ROUNDTONEAREST) return 1;
  if (tree->nodeType == ROUNDDOWN) return 1;
  if (tree->nodeType == ROUNDUP) return 1;
  if (tree->nodeType == ROUNDTOZERO) return 1;
  return 0;
}

int isExpansionFormat(node *tree) {
  if (tree->nodeType == DOUBLESYMBOL) return 1;
  if (tree->nodeType == DOUBLEDOUBLESYMBOL) return 1;
  if (tree->nodeType == TRIPLEDOUBLESYMBOL) return 1;
  if (tree->nodeType == DOUBLEEXTENDEDSYMBOL) return 1;
  return 0;
}

int isRestrictedExpansionFormat(node *tree) {
  if (tree->nodeType == DOUBLESYMBOL) return 1;
  if (tree->nodeType == DOUBLEDOUBLESYMBOL) return 1;
  if (tree->nodeType == TRIPLEDOUBLESYMBOL) return 1;
  return 0;
}


int isFilePostscriptFile(node *tree) {
  if (tree->nodeType == FILESYM) return 1;
  if (tree->nodeType == POSTSCRIPT) return 1;
  if (tree->nodeType == POSTSCRIPTFILE) return 1;
  return 0;
}

int isExternalPlotMode(node *tree) {
  if (tree->nodeType == ABSOLUTESYM) return 1;
  if (tree->nodeType == RELATIVESYM) return 1;
  return 0;
}


int evaluateThingToPureTree(node **result, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isPureTree(evaluatedResult)) {
    *result = evaluatedResult;
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToConstant(mpfr_t result, node *tree, mpfr_t *defaultVal) {
  node *evaluatedResult, *simplified;
  mpfr_t tempMpfr, tempResult;
  int res;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && (isDefault(evaluatedResult))) {
    mpfr_set(result,*defaultVal,GMP_RNDN);
    freeThing(evaluatedResult);
    return 1;
  }

  if (isPureTree(evaluatedResult)) {
    
    simplified = simplifyTreeErrorfree(evaluatedResult);
    free_memory(evaluatedResult);

    mpfr_init2(tempMpfr,53);
    mpfr_set_d(tempMpfr,1.0,GMP_RNDN);

    mpfr_init2(tempResult,mpfr_get_prec(result));

    if (!isConstant(simplified)) {
      printMessage(1,"Warning: the given expression does not evaluate to a constant.\n");
      printMessage(1,"Setting %s to 1 when evaluating.\n",variablename);
    }

    res = evaluateFaithful(tempResult, simplified, tempMpfr, defaultprecision);

    if (!res) {
      printMessage(1,"Warning: the given expression is not a constant but an expression to evaluate.\n");
      printMessage(1,"A faithful evaluation is not possible. Will use a floating-point evaluation.\n");
      evaluate(tempResult, simplified, tempMpfr, defaultprecision * 256);
    } else {
      if (simplified->nodeType != CONSTANT) {
	printMessage(1,"Warning: the given expression is not a constant but an expression to evaluate.\n");
      }
    }

    free_memory(simplified);
    mpfr_set(result,tempResult,GMP_RNDN);
    
    mpfr_clear(tempMpfr);
    mpfr_clear(tempResult);

    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToInteger(int *result, node *tree, int *defaultVal) {
  mpfr_t *defaultValMpfr, resultMpfr;
  int res, tempResult;

  if (defaultVal != NULL) {
    defaultValMpfr = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*defaultValMpfr,sizeof(int)*8);
    mpfr_set_si(*defaultValMpfr,*defaultVal,GMP_RNDN);
  } else {
    defaultValMpfr = NULL;
  }

  mpfr_init2(resultMpfr,sizeof(int)*16);

  res = evaluateThingToConstant(resultMpfr, tree, defaultValMpfr);

  if (res) {
    tempResult = mpfr_get_si(resultMpfr, GMP_RNDN);
    
    mpfr_sub_si(resultMpfr, resultMpfr, tempResult, GMP_RNDN);

    if (!mpfr_zero_p(resultMpfr)) {
      printMessage(1,"Warning: the given expression does not evaluate to a machine integer.\n");
      printMessage(1,"Will round it to the nearest machine integer.\n");
    }

    *result = tempResult;
  }

  if (defaultValMpfr != NULL) {
    mpfr_clear(*defaultValMpfr);
    free(defaultValMpfr);
  }

  mpfr_clear(resultMpfr);
  
  return res;
}

int evaluateThingToString(char **result, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isString(evaluatedResult)) {
    *result = (char *) safeCalloc(strlen(evaluatedResult->string)+1,sizeof(char));
    strcpy(*result,evaluatedResult->string);
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToRange(mpfr_t a, mpfr_t b, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isRange(evaluatedResult)) {
    mpfr_set_prec(a,mpfr_get_prec(*((mpfr_t *) (evaluatedResult->child1->value))));
    mpfr_set_prec(b,mpfr_get_prec(*((mpfr_t *) (evaluatedResult->child2->value))));
    mpfr_set(a,*((mpfr_t *) (evaluatedResult->child1->value)),GMP_RNDN);
    mpfr_set(b,*((mpfr_t *) (evaluatedResult->child2->value)),GMP_RNDN);
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToBoolean(int *result, node *tree, int *defaultVal) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && isDefault(evaluatedResult)) {
    *result = *defaultVal;
    freeThing(evaluatedResult);
    return 1;
  }

  if (isBoolean(evaluatedResult)) {
    if (evaluatedResult->nodeType == TRUE) 
      *result = 1;
    else
      *result = 0;
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}


int evaluateThingToOnOff(int *result, node *tree, int *defaultVal) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && isDefault(evaluatedResult)) {
    *result = *defaultVal;
    freeThing(evaluatedResult);
    return 1;
  }

  if (isOnOff(evaluatedResult)) {
    if (evaluatedResult->nodeType == ON) 
      *result = 1;
    else
      *result = 0;
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToExternalPlotMode(int *result, node *tree, int *defaultVal) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && isDefault(evaluatedResult)) {
    *result = *defaultVal;
    freeThing(evaluatedResult);
    return 1;
  }

  if (isExternalPlotMode(evaluatedResult)) {
    switch (evaluatedResult->nodeType) {
    case ABSOLUTESYM:
      *result = ABSOLUTE;
      break;
    case RELATIVESYM:
      *result = RELATIVE;
      break;
    }
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToDisplayMode(int *result, node *tree, int *defaultVal) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && isDefault(evaluatedResult)) {
    *result = *defaultVal;
    freeThing(evaluatedResult);
    return 1;
  }

  if (isDisplayMode(evaluatedResult)) {
    switch (evaluatedResult->nodeType) {
    case DECIMAL:
      *result = 0;
      break;
    case DYADIC:
      *result = 1;
      break;
    case POWERS:
      *result = 2;
      break;
    case BINARY:
      *result = 3;
      break;
    }
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}


int evaluateThingToRoundingSymbol(int *result, node *tree, int *defaultVal) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if ((defaultVal != NULL) && isDefault(evaluatedResult)) {
    *result = *defaultVal;
    freeThing(evaluatedResult);
    return 1;
  }

  if (isRoundingSymbol(evaluatedResult)) {
    switch (evaluatedResult->nodeType) {
    case ROUNDTONEAREST:
      *result = GMP_RNDN;
      break;
    case ROUNDDOWN:
      *result = GMP_RNDD;
      break;
    case ROUNDUP:
      *result = GMP_RNDU;
      break;
    case ROUNDTOZERO:
      *result = GMP_RNDZ;
      break;
    }
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToExpansionFormat(int *result, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isExpansionFormat(evaluatedResult)) {
    switch (evaluatedResult->nodeType) {
    case DOUBLESYMBOL:
      *result = 1;
      break;
    case DOUBLEDOUBLESYMBOL:
      *result = 2;
      break;
    case TRIPLEDOUBLESYMBOL:
      *result = 3;
      break;
    case DOUBLEEXTENDEDSYMBOL:
      *result = 4;
      break;
    }
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToRestrictedExpansionFormat(int *result, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isRestrictedExpansionFormat(evaluatedResult)) {
    switch (evaluatedResult->nodeType) {
    case DOUBLESYMBOL:
      *result = 1;
      break;
    case DOUBLEDOUBLESYMBOL:
      *result = 2;
      break;
    case TRIPLEDOUBLESYMBOL:
      *result = 3;
      break;
    }
    freeThing(evaluatedResult);
    return 1;
  }
  
  freeThing(evaluatedResult);
  return 0;
}


int evaluateThingToPureListOfThings(chain **ch, node *tree) {
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  if (isPureList(evaluatedResult)) {
    *ch = evaluatedResult->arguments;
    free(evaluatedResult);
    return 1;
  }

  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToPureListOfPureTrees(chain **ch, node *tree) {
  node *evaluatedResult;
  chain *curr;

  evaluatedResult = evaluateThing(tree);

  if (isPureList(evaluatedResult)) {
    *ch = evaluatedResult->arguments;
    free(evaluatedResult);
    curr = *ch;
    while (curr != NULL) {
      if (!isPureTree((node *) (curr->value))) {
	freeChain(*ch,freeThingOnVoid);
	return 0;
      }
      curr = curr->next;
    }
    return 1;
  }

  freeThing(evaluatedResult);
  return 0;
}


int evaluateThingToIntegerList(chain **ch, int *finalelliptic, node *tree) {
  node *evaluatedResult;
  chain *curr;
  int *arrayRes, *resPtr;
  int i, resA;

  evaluatedResult = evaluateThing(tree);

  if (finalelliptic == NULL) {
    if (isPureList(evaluatedResult)) {
      curr = evaluatedResult->arguments;
      i = 0;
      while (curr != NULL) {
	if (!isPureTree((node *) (curr->value))) {
	  freeThing(evaluatedResult);
	  return 0;
	}
	i++;
	curr = curr->next;
      }
      arrayRes = (int *) safeCalloc(i,sizeof(int));
      curr = evaluatedResult->arguments; i = 0;
      while (curr != NULL) {
	if (!evaluateThingToInteger(&resA,(node *) (curr->value),NULL)) {
	  freeThing(evaluatedResult);
	  free(arrayRes);
	  return 0;
	} else {
	  arrayRes[i] = resA;
	}
	i++;
	curr = curr->next;
      }
      curr = NULL;
      for (i--;i>=0;i--) {
	resPtr = (int *) safeMalloc(sizeof(int));
	*resPtr = arrayRes[i];
	curr = addElement(curr, resPtr);
      }
      free(arrayRes);
      *ch = curr;
      freeThing(evaluatedResult);
      return 1;
    }
  } else {
    if (isPureList(evaluatedResult) || isPureFinalEllipticList(evaluatedResult)) {
      if (isList(evaluatedResult)) *finalelliptic = 0; else *finalelliptic = 1;
      curr = evaluatedResult->arguments;
      i = 0;
      while (curr != NULL) {
	if (!isPureTree((node *) (curr->value))) {
	  freeThing(evaluatedResult);
	  return 0;
	}
	i++;
	curr = curr->next;
      }
      arrayRes = (int *) safeCalloc(i,sizeof(int));
      curr = evaluatedResult->arguments; i = 0;
      while (curr != NULL) {
	if (!evaluateThingToInteger(&resA,(node *) (curr->value),NULL)) {
	  freeThing(evaluatedResult);
	  free(arrayRes);
	  return 0;
	} else {
	  arrayRes[i] = resA;
	}
	i++;
	curr = curr->next;
      }
      curr = NULL;
      for (i--;i>=0;i--) {
	resPtr = (int *) safeMalloc(sizeof(int));
	*resPtr = arrayRes[i];
	curr = addElement(curr, resPtr);
      }
      free(arrayRes);
      freeThing(evaluatedResult);
      *ch = curr;
      return 1;
    }
  }

  freeThing(evaluatedResult);
  return 0;
}

int evaluateThingToExpansionFormatList(chain **ch, node *tree) {
  node *evaluatedResult;
  chain *curr;
  int *arrayRes, *resPtr;
  int i, resA, k;
  int finalelliptic;

  evaluatedResult = evaluateThing(tree);

  if (isPureList(evaluatedResult) || isPureFinalEllipticList(evaluatedResult)) {
    if (isList(evaluatedResult)) finalelliptic = 0; else finalelliptic = 1;
    curr = evaluatedResult->arguments;
    i = 0;
    while (curr != NULL) {
      if (!isExpansionFormat((node *) (curr->value))) {
	freeThing(evaluatedResult);
	return 0;
      }
      i++;
      curr = curr->next;
    }
    arrayRes = (int *) safeCalloc(i,sizeof(int));
    curr = evaluatedResult->arguments; i = 0;
    while (curr != NULL) {
      if (!evaluateThingToExpansionFormat(&resA,(node *) (curr->value))) {
	freeThing(evaluatedResult);
	free(arrayRes);
	return 0;
      } else {
	arrayRes[i] = resA;
      }
      i++;
      curr = curr->next;
    }
    curr = NULL;
    for (k=0;k<i;k++) {
      resPtr = (int *) safeMalloc(sizeof(int));
      *resPtr = arrayRes[k];
      curr = addElement(curr, resPtr);
    }
    if (finalelliptic) {
      resPtr = (int *) safeMalloc(sizeof(int));
      *resPtr = -1;
      curr = addElement(curr, resPtr);
    }
    free(arrayRes);
    freeThing(evaluatedResult);
    *ch = curr;
    return 1;
  }
  

  freeThing(evaluatedResult);
  return 0;
}


void printThingWithFullStrings(node *thing) {
  char *temp;
  chain *curr;

  if (isPureTree(thing)) {
    printTree(thing);
  } else {
    if (isRange(thing)) {
      if (midpointMode) {
	temp = sprintMidpointMode(*(thing->child1->value), *(thing->child2->value));
	if (temp != NULL) {
	  printf("%s",temp);
	  free(temp);
	} else {
	  printf("[");
	  printValue(thing->child1->value,mpfr_get_prec(*(thing->child1->value)));
	  printf(";");
	  printValue(thing->child2->value,mpfr_get_prec(*(thing->child2->value)));
	  printf("]");
	}
      } else {
	printf("[");
	printValue(thing->child1->value,mpfr_get_prec(*(thing->child1->value)));
	printf(";");
	printValue(thing->child2->value,mpfr_get_prec(*(thing->child2->value)));
	printf("]");
      }
    } else {
      if (isList(thing)) {
	curr = thing->arguments;
	printf("[|");
	while (curr != NULL) {
	  printThingWithFullStrings((node *) (curr->value));
	  if (curr->next != NULL) printf(", ");
	  curr = curr->next;
	}
	printf("|]");
      } else {
	if (isFinalEllipticList(thing)) {
	  curr = thing->arguments;
	  printf("[|");
	  while (curr != NULL) {
	    printThingWithFullStrings((node *) (curr->value));
	    if (curr->next != NULL) printf(", ");
	    curr = curr->next;
	  }
	  printf("...|]");
	} else {
	  rawPrintThing(thing);
	}
      }
    }  
  }
}


void printThing(node *thing) {
  char *temp;
  chain *curr;

  if (isPureTree(thing)) {
    printTree(thing);
  } else {
    if (isRange(thing)) {
      if (midpointMode) {
	temp = sprintMidpointMode(*(thing->child1->value), *(thing->child2->value));
	if (temp != NULL) {
	  printf("%s",temp);
	  free(temp);
	} else {
	  printf("[");
	  printValue(thing->child1->value,mpfr_get_prec(*(thing->child1->value)));
	  printf(";");
	  printValue(thing->child2->value,mpfr_get_prec(*(thing->child2->value)));
	  printf("]");
	}
      } else {
	printf("[");
	printValue(thing->child1->value,mpfr_get_prec(*(thing->child1->value)));
	printf(";");
	printValue(thing->child2->value,mpfr_get_prec(*(thing->child2->value)));
	printf("]");
      }
    } else {
      if (isList(thing)) {
	curr = thing->arguments;
	printf("[|");
	while (curr != NULL) {
	  printThingWithFullStrings((node *) (curr->value));
	  if (curr->next != NULL) printf(", ");
	  curr = curr->next;
	}
	printf("|]");
      } else {
	if (isFinalEllipticList(thing)) {
	  curr = thing->arguments;
	  printf("[|");
	  while (curr != NULL) {
	    printThingWithFullStrings((node *) (curr->value));
	    if (curr->next != NULL) printf(", ");
	    curr = curr->next;
	  }
	  printf("...|]");
	} else {
	  if (isString(thing)) {
	    printf("%s",thing->string);
	  } else {
	    rawPrintThing(thing);
	  }
	}
      }
    }  
  }
}

void fRawPrintThing(FILE *fd, node *thing);

void fPrintThingWithFullStrings(FILE *fd, node *thing) {
  char *temp;
  chain *curr;

  if (isPureTree(thing)) {
    fprintTreeWithPrintMode(fd,thing);
  } else {
    if (isRange(thing)) {
      if (midpointMode) {
	temp = sprintMidpointMode(*(thing->child1->value), *(thing->child2->value));
	if (temp != NULL) {
	  fprintf(fd,"%s",temp);
	  free(temp);
	} else {
	  fprintf(fd,"[");
	  fprintValueWithPrintMode(fd,*(thing->child1->value));
	  fprintf(fd,";");
	  fprintValueWithPrintMode(fd,*(thing->child2->value));
	  fprintf(fd,"]");
	}
      } else {
	fprintf(fd,"[");
	fprintValueWithPrintMode(fd,*(thing->child1->value));
	fprintf(fd,";");
	fprintValueWithPrintMode(fd,*(thing->child2->value));
	fprintf(fd,"]");
      }
    } else {
      if (isList(thing)) {
	curr = thing->arguments;
	fprintf(fd,"[|");
	while (curr != NULL) {
	  fPrintThingWithFullStrings(fd,(node *) (curr->value));
	  if (curr->next != NULL) fprintf(fd,", ");
	  curr = curr->next;
	}
	fprintf(fd,"|]");
      } else {
	if (isFinalEllipticList(thing)) {
	  curr = thing->arguments;
	  fprintf(fd,"[|");
	  while (curr != NULL) {
	    fPrintThingWithFullStrings(fd,(node *) (curr->value));
	    if (curr->next != NULL) fprintf(fd,", ");
	    curr = curr->next;
	  }
	  fprintf(fd,"...|]");
	} else {
	  fRawPrintThing(fd,thing);
	}
      }
    }  
  }
}


void fPrintThing(FILE *fd, node *thing) {
  char *temp;
  chain *curr;

  if (isPureTree(thing)) {
    fprintTreeWithPrintMode(fd,thing);
  } else {
    if (isRange(thing)) {
      if (midpointMode) {
	temp = sprintMidpointMode(*(thing->child1->value), *(thing->child2->value));
	if (temp != NULL) {
	  fprintf(fd,"%s",temp);
	  free(temp);
	} else {
	  fprintf(fd,"[");
	  fprintValueWithPrintMode(fd,*(thing->child1->value));
	  fprintf(fd,";");
	  fprintValueWithPrintMode(fd,*(thing->child2->value));
	  fprintf(fd,"]");
	}
      } else {
	fprintf(fd,"[");
	fprintValueWithPrintMode(fd,*(thing->child1->value));
	fprintf(fd,";");
	fprintValueWithPrintMode(fd,*(thing->child2->value));
	fprintf(fd,"]");
      }
    } else {
      if (isList(thing)) {
	curr = thing->arguments;
	fprintf(fd,"[|");
	while (curr != NULL) {
	  fPrintThingWithFullStrings(fd,(node *) (curr->value));
	  if (curr->next != NULL) fprintf(fd,", ");
	  curr = curr->next;
	}
	fprintf(fd,"|]");
      } else {
	if (isFinalEllipticList(thing)) {
	  curr = thing->arguments;
	  fprintf(fd,"[|");
	  while (curr != NULL) {
	    fPrintThingWithFullStrings(fd,(node *) (curr->value));
	    if (curr->next != NULL) fprintf(fd,", ");
	    curr = curr->next;
	  }
	  fprintf(fd,"...|]");
	} else {
	  if (isString(thing)) {
	    fprintf(fd,"%s",thing->string);
	  } else {
	    fRawPrintThing(fd,thing);
	  }
	}
      }
    }  
  }
}


int assignThingToTable(char *identifier, node *thing) {

  if (((variablename != NULL) && (strcmp(variablename,identifier) == 0)) || 
      (getFunction(identifier) != NULL)) {
    printMessage(1,"Warning: the identifier \"%s\" is already bound to the free variable or to a library function\nThe command will have no effect.\n", identifier);
    return 0;
  }

  if (containsEntry(symbolTable, identifier)) {
    printMessage(2,"Information: the identifier \"%s\" has already been assigned to. This a reassignment.\n");
    symbolTable = removeEntry(symbolTable, identifier, freeThingOnVoid);
  }

  symbolTable = addEntry(symbolTable, identifier, thing, copyThingOnVoid);

  return 1;
}

node *getThingFromTable(char *identifier) {
  libraryFunction *tempLibraryFunction;
  node *temp_node;

  if ((variablename != NULL) && (strcmp(variablename,identifier) == 0)) {
    return makeVariable();
  }

  if ((tempLibraryFunction = getFunction(identifier)) != NULL) {
    if (variablename==NULL) {
      printMessage(1,"Warning: the current free variable is not bound to an identifier. Dereferencing library function \"%s\" requires this binding.\n",tempLibraryFunction->functionName);
      printMessage(1,"Will bind the current free variable to the identifier \"x\".\n");
      variablename = (char *) safeCalloc(2,sizeof(char));
      variablename[0] = 'x';
    }
    temp_node = (node *) safeMalloc(sizeof(node));
    temp_node->nodeType = LIBRARYFUNCTION;
    temp_node->libFun = tempLibraryFunction;
    temp_node->libFunDeriv = 0;
    temp_node->child1 = (node *) safeMalloc(sizeof(node));
    temp_node->child1->nodeType = VARIABLE;
    return temp_node;
  }

  if (!containsEntry(symbolTable, identifier)) return NULL;

  return (node *) getEntry(symbolTable, identifier, copyThingOnVoid);
}

void autoprint(node *thing) {
  mpfr_t a,b;
  node *temp_node, *tempNode2, *tempNode3;
  chain *curr;
  int freeThingAfterwards;

  if (isPureTree(thing)) {
    if (treeSize(thing) < CHEAPSIMPLIFYSIZE) {
      tempNode2 = simplifyTreeErrorfree(thing);
      freeThingAfterwards = 1;
    } else {
      tempNode2 = thing;
      freeThingAfterwards = 0;
    }
    if (isConstant(tempNode2)) {
      if (tempNode2->nodeType == CONSTANT) {
	printValue(tempNode2->value,mpfr_get_prec(*(tempNode2->value)));
      } else {
	mpfr_init2(a,tools_precision);
	mpfr_init2(b,tools_precision);
	mpfr_set_d(b,1.0,GMP_RNDN);
	if (evaluateFaithful(a,tempNode2,b,tools_precision)) {
	  printMessage(1,"Warning: rounding has happened. The value displayed is a faithful rounding of the true result.\n");
	  printValue(&a,tools_precision);
	} else {
	  evaluate(a,tempNode2,b,tools_precision * 256);
	  printMessage(1,"Warning: rounding has happened. The value displayed is not a faithful rounding of the true result.\n");
	  printValue(&a,tools_precision);
	}
	mpfr_clear(a);
      }
    } else {
      tempNode3 = simplifyTree(tempNode2);
      if (!isSyntacticallyEqual(tempNode3,tempNode2)) {
	printMessage(1,"Warning: rounding may have happened.\n");
      }
      freeThing(tempNode2);
      tempNode2 = tempNode3;
      if (treeSize(tempNode2) > MAXHORNERTREESIZE) {
	if (canonical) 
	  printMessage(1,"Warning: the expression is too big for being written in canonical form.\n");
	else 
	  printMessage(1,"Warning: the expression is too big for being written in Horner form.\n");
	temp_node = copyTree(tempNode2);
      } else {
	if (canonical) temp_node = makeCanonical(tempNode2,tools_precision); else temp_node = horner(tempNode2);
      }
      printTree(temp_node);
      free_memory(temp_node);
    }
    if (freeThingAfterwards) free_memory(tempNode2);
  } else {
    if (isList(thing)) {
      printf("[|");
      curr = thing->arguments;
      while (curr != NULL) {
	autoprint((node *) (curr->value));
	if (curr->next != NULL) printf(", ");
	curr = curr->next;
      }
      printf("|]");
    } else {
      if (isFinalEllipticList(thing)) {
	printf("[|");
	curr = thing->arguments;
	while (curr != NULL) {
	  autoprint((node *) (curr->value));
	  if (curr->next != NULL) printf(", ");
	  curr = curr->next;
	}
	printf("...|]");
      } else {
	printThing(thing);
      }
    }
  }
}

void evaluateThingListToThingArray(int *number, node ***array, chain *things) {
  chain *curr;
  int i;

  *number = lengthChain(things);
  *array = (node **) safeCalloc(*number,sizeof(node *));

  curr = things; i = 0;
  while (curr != NULL) {
    (*array)[i] = evaluateThing((node *) (curr->value));
    curr = curr->next;
    i++;
  }
}

int evaluateThingArrayToListOfPureTrees(chain **ch, int number, node **array) {
  chain *curr;
  int i, err;
  node *evaluated;

  err = 0;
  curr = NULL;
  for (i=number-1;i>=0;i--) {
    if (evaluateThingToPureTree(&evaluated, array[i])) {
      curr = addElement(curr,evaluated);
    } else {
      err = 1;
      break;
    }
  }

  if (err) {
    freeChain(curr,freeThingOnVoid);
    return 0;
  }

  *ch = curr;
  return 1;
}

int evaluateThingToConstantList(chain **ch, node *tree) {
  node **arrayTrees;
  chain *newChain;
  int i, number, k;
  node *evaluated;
  mpfr_t **arrayMpfr;

  evaluated = evaluateThing(tree);

  if (isPureList(evaluated)) {
    evaluateThingListToThingArray(&number, &arrayTrees, evaluated->arguments); 
    arrayMpfr = (mpfr_t **) safeCalloc(number,sizeof(mpfr_t *));
    for (i=0;i<number;i++) {
      arrayMpfr[i] = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
      mpfr_init2(*(arrayMpfr[i]),tools_precision);
    }
    for (i=0;i<number;i++) {
      if (!evaluateThingToConstant(*(arrayMpfr[i]),arrayTrees[i],NULL)) {
	for (k=0;k<=number;k++) {
	  freeThing(arrayTrees[k]);
	  mpfr_clear(*(arrayMpfr[k]));
	  free(arrayMpfr[k]);
	}
	free(arrayTrees);
	free(arrayMpfr);
	freeThing(evaluated);
	return 0;
      }
    }
    newChain = NULL;
    for (k=number-1;k>=0;k--) {
      newChain = addElement(newChain,arrayMpfr[k]);
    }
    free(arrayMpfr);
    *ch = newChain;
    for (i=0;i<number;i++) freeThing(arrayTrees[i]);
    free(arrayTrees);
    return 1;
  }

  freeThing(evaluated);
  return 0;
}



int evaluateThingToEmptyList(node *tree) {
  int res;
  node *evaluatedResult;

  evaluatedResult = evaluateThing(tree);

  res = isEmptyList(evaluatedResult);

  freeThing(evaluatedResult);

  return res;
}





int executeCommand(node *tree) {
  int result, res, intTemp, resA, resB, resC, resD, resE, defaultVal, i;  
  chain *curr, *tempList, *tempList2; 
  mpfr_t a, b, c, d, e;
  node *tempNode, *tempNode2, *tempNode3, *tempNode4;
  libraryFunction *tempLibraryFunction;
  char *tempString, *tempString2, *timingString;
  FILE *fd;
  node **array;
  rangetype tempRange;

  result = 0;

  timingString = NULL;
  if (timecounting) {
    timingString = getTimingStringForThing(tree);
    if (timingString != NULL) pushTimeCounter();
  }

  switch (tree->nodeType) {  
  case COMMANDLIST:
    curr = tree->arguments;
    result = 0;
    while (curr != NULL) {
      res = executeCommand((node *) (curr->value));
      if (res) {
	result = 1;
	break;
      }
      curr = curr->next;
    }
    break;			
  case WHILE:
    result = 0;
    do {
      if (!evaluateThingToBoolean(&intTemp, tree->child1, NULL)) {
	printMessage(1,"Warning: the given expression does not evaluate to a boolean.\n");
	printMessage(1,"The while loop will not be executed.\n");
	break;
      }
      if (!intTemp) 
	break;
      res = executeCommand(tree->child2);
      if (res) {
	result = 1;
	break;
      }
    } while (1);
    break;				
  case IFELSE:
    result = 0;
    curr = tree->arguments;
    if (!evaluateThingToBoolean(&intTemp, (node *) (curr->value), NULL)) {
      printMessage(1,"Warning: the given expression does not evaluate to a boolean.\n");
      printMessage(1,"Neither the if nor the else statement will be executed.\n");
    } else {
      if (intTemp) {
	curr = curr->next;
	result = executeCommand((node *) (curr->value));
      } else {
	curr = curr->next; curr = curr->next;
	result = executeCommand((node *) (curr->value));
      }
    }
    break; 				
  case IF:
    result = 0;
    if (!evaluateThingToBoolean(&intTemp, tree->child1, NULL)) {
      printMessage(1,"Warning: the given expression does not evaluate to a boolean.\n");
      printMessage(1,"The if statement will not be executed.\n");
    } else {
      if (intTemp) {
	result = executeCommand(tree->child2);
      } 
    }
    break; 				
  case FOR:
    result = 0;
    mpfr_init2(a,tools_precision);
    mpfr_init2(b,tools_precision);
    mpfr_init2(c,tools_precision);
    curr = tree->arguments;
    resA = evaluateThingToConstant(a, (node *) (curr->value), NULL);
    curr = curr->next;
    resB = evaluateThingToConstant(b, (node *) (curr->value), NULL);
    curr = curr->next;
    resC = evaluateThingToConstant(c, (node *) (curr->value), NULL);
    curr = curr->next;
    tempNode4 = (node *) (curr->value);
    if (resA && resB && resC) {
      tempNode = makeConstant(a);
      if (assignThingToTable(tree->string, tempNode)) {
	while (1) {
	  if (mpfr_sgn(c) > 0) {
	    if (mpfr_cmp(a,b) > 0) break;
	  } else {
	    if (mpfr_cmp(a,b) < 0) break;
	  }
	  res = executeCommand(tempNode4);
	  if (res) {
	    result = 1;
	    break;
	  }
	  tempNode2 = getThingFromTable(tree->string);
	  if (tempNode2 != NULL) {
	    tempNode3 = makeAdd(tempNode2,makeConstant(c));
	    resA = evaluateThingToConstant(a, tempNode3, NULL);
	    freeThing(tempNode3);
	    if (resA) {
	      tempNode3 = makeConstant(a);
	      if (!assignThingToTable(tree->string,tempNode3)) {
		printMessage(1,"Warning: at the end of a for loop, the loop variable \"%s\" cannot longer be assigned to.\n",tree->string);
		printMessage(1,"The for loop will no longer be executed.\n");
		break;
	      }
	    } else {
	      printMessage(1,"Warning: at the end of a for loop, the loop variable \"%s\" decreased by the loop step does no longer evaluate to a constant.\n",tree->string);
	      printMessage(1,"The for loop will no longer be executed.\n");
	      break;
	    }
	  } else {
	    printMessage(1,"Warning: the tool has been restarted inside a for loop.\n");
	    printMessage(1,"The for loop will no longer be executed.\n");
	    break;
	  }
	}
      } else {
	printMessage(1,"Warning: the identifier \"%s\" cannot be assigned to.\n",tree->string);
	printMessage(1,"The for loop will not be executed.\n");
      }
      freeThing(tempNode);
    } else {
      printMessage(1,"Warning: one of the arguments of the for loop does not evaluate to a constant.\n");
      printMessage(1,"The for loop will not be executed.\n");
    }
    mpfr_clear(a);
    mpfr_clear(b);
    mpfr_clear(c);
    break; 				
  case FORIN:
    if (evaluateThingToPureListOfThings(&tempList, tree->child1)) {
      curr = tempList;
      while (curr != NULL) {
	if (assignThingToTable(tree->string,(node *) (curr->value))) {
	  res = executeCommand(tree->child2);
	  if (res) {
	    result = 1;
	    break;
	  }
	} else {
	  printMessage(1,"Warning: the identifier \"%s\" can no longer be assigned to.\n",tree->string);
	  printMessage(1,"The execution of the for loop will be stopped.\n");
	  break;
	}
	curr = curr->next;
      }
      freeChain(tempList,freeThingOnVoid);
    } else {
      if (evaluateThingToEmptyList(tree->child1)) {
	printMessage(2,"Information: executing a for in statement on an empty list.\n");
      } else {
	printMessage(1,"Warning: the expression given does not evaluate to a non-elliptic list.\n");
	printMessage(1,"The loop will not be executed.\n");
      }
    }
    break;  				
  case QUIT:
    result = 1;
    break;  				
  case FALSEQUIT:
    printMessage(1,"Warning: a quit command has been used in a file read into another.\n");
    printMessage(1,"This quit command will be neglected.\n");
    result = 0;
    break; 			
  case RESTART:
    restartTool();
    printf("The tool has been restarted.\n");
    result = 0;
    break;  			
  case PRINT:
    curr = tree->arguments;
    while (curr != NULL) {
      tempNode = evaluateThing((node *) (curr->value));
      printThing(tempNode);
      freeThing(tempNode);
      if (curr->next != NULL) printf(" ");
      curr = curr->next;
    }
    printf("\n");
    break; 				
  case NEWFILEPRINT:
    if (evaluateThingToString(&tempString, tree->child1)) {
      fd = fopen(tempString,"w");
      if (fd != NULL) {
	curr = tree->arguments;
	while (curr != NULL) {
	  tempNode = evaluateThing((node *) (curr->value));
	  fPrintThing(fd,tempNode);
	  freeThing(tempNode);
	  if (curr->next != NULL) fprintf(fd," ");
	  curr = curr->next;
	}
	fprintf(fd,"\n");
	fclose(fd);
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",tempString);
	printMessage(1,"This command will have no effect.\n");
      }
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    } 
    break; 			
  case APPENDFILEPRINT:
    if (evaluateThingToString(&tempString, tree->child1)) {
      fd = fopen(tempString,"a");
      if (fd != NULL) {
	curr = tree->arguments;
	while (curr != NULL) {
	  tempNode = evaluateThing((node *) (curr->value));
	  fPrintThing(fd,tempNode);
	  freeThing(tempNode);
	  if (curr->next != NULL) fprintf(fd," ");
	  curr = curr->next;
	}
	fprintf(fd,"\n");
	fclose(fd);
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",tempString);
	printMessage(1,"This command will have no effect.\n");
      }
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    } 
    break; 			
  case PLOT:
    evaluateThingListToThingArray(&resA, &array, tree->arguments);
    resC = 0;
    if (isFilePostscriptFile(array[resA-2])) {
      if (evaluateThingToString(&tempString, array[resA-1])) {
	resB = resA - 2;
	resC = 1;
	switch ((array[resA-2])->nodeType) {
	case FILESYM:
	  resD = PLOTFILE;
	  break;
	case POSTSCRIPT:
	  resD = PLOTPOSTSCRIPT;
	  break;
	case POSTSCRIPTFILE:
	  resD = PLOTPOSTSCRIPTFILE;
	  break;
	default:
	  resC = 0;
	}
      } else {
	printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
	printMessage(1,"This command will have no effect.\n");
      }
    } else {
      resB = resA;
      resC = 1;
      tempString = NULL;
    }
    if (resC) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a, b, array[resB-1])) {
	if (evaluateThingArrayToListOfPureTrees(&tempList, resB-1, array)) {
	  plotTree(tempList, a, b, defaultpoints, tools_precision, tempString, resD);
	  freeChain(tempList,freeThingOnVoid);
	} else {
	  if (isPureList(array[0]) && (resB-1 == 1)) {
	    if (evaluateThingToPureListOfPureTrees(&tempList, array[0])) {
	      plotTree(tempList, a, b, defaultpoints, tools_precision, tempString, resD);
	      freeChain(tempList,freeThingOnVoid);
	    } else {
	      printMessage(1,"Warning: the first argument is not a list of pure functions.\n");
	      printMessage(1,"This command will have no effect.\n");
	    }
	  } else {
	    printMessage(1,"Warning: at least one of the given expressions does not evaluate to a pure function.\n");
	    printMessage(1,"Warning: the first argument is not a list of pure functions.\n");
	    printMessage(1,"This command will have no effect.\n");
	  }
	}
      } else {
	printMessage(1,"Warning: the expression given does not evaluate to a range.\n");
	printMessage(1,"This command will have no effect.\n");
      }
      mpfr_clear(a);
      mpfr_clear(b);
    }
    if (tempString != NULL) free(tempString);
    for (i=0;i<resA;i++)
      freeThing(array[i]);
    free(array);
    break;			
  case PRINTHEXA:
    mpfr_init2(a,tools_precision);
    if (evaluateThingToConstant(a, tree->child1, NULL)) {
      printDoubleInHexa(a);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a constant value.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    mpfr_clear(a);
    break; 
  case PRINTBINARY:
    mpfr_init2(a,tools_precision);
    if (evaluateThingToConstant(a, tree->child1, NULL)) {
      printBinary(a); printf("\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a constant value.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    mpfr_clear(a);
    break; 			
  case PRINTEXPANSION:
    if (evaluateThingToPureTree(&tempNode, tree->child1)) {
      if (printPolynomialAsDoubleExpansion(tempNode, tools_precision) == 1) {
	printMessage(1,"\nWarning: rounding occured while printing.");
      }
      printf("\n");
      freeThing(tempNode);
    } else {
      printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
      printMessage(1,"The command will not be executed.\n");
    }
    break;
  case BASHEXECUTE:
    if (evaluateThingToString(&tempString, tree->child1)) {
      intTemp = bashExecute(tempString);
      printMessage(2,"Information: the bash return value is %d.\n",intTemp);
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case EXTERNALPLOT:
    evaluateThingListToThingArray(&resA, &array, tree->arguments);
    if (evaluateThingToString(&tempString,array[0])) {
      resB = RELATIVE;
      if (evaluateThingToExternalPlotMode(&resA,array[1],&resB)) {
	if (evaluateThingToPureTree(&tempNode,array[2])) {
	  mpfr_init2(a,tools_precision);
	  mpfr_init2(b,tools_precision);
	  if (evaluateThingToRange(a,b,array[3])) {
	    if (evaluateThingToInteger(&resB, array[4], NULL)) {
	      resC = 0; resD = 0; tempString2 = NULL;
	      if (resA >= 6) {
		if ((array[5])->nodeType == PERTURB) {
		  resC = 1;
		  if (resA >= 8) {
		    if (isFilePostscriptFile(array[6])) {
		      if (evaluateThingToString(&tempString2,array[7])) {
			resD = 1;
			switch ((array[6])->nodeType) {
			case FILESYM:
			  resE = PLOTFILE;
			  break;
			case POSTSCRIPT:
			  resE = PLOTPOSTSCRIPT;
			  break;
			case POSTSCRIPTFILE:
			  resE = PLOTPOSTSCRIPTFILE;
			  break;
			default:
			  resD = 0;
			}
		      } else {
			printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
			printMessage(1,"This command will have no effect.\n");
		      }
		    }
		  } else {
		    resD = 1;
		  }
		} else {
		  if (resA >= 7) {
		    if (isFilePostscriptFile(array[5])) {
		      if (evaluateThingToString(&tempString2,array[6])) {
			resD = 1;
			switch ((array[5])->nodeType) {
			case FILESYM:
			  resE = PLOTFILE;
			  break;
			case POSTSCRIPT:
			  resE = PLOTPOSTSCRIPT;
			  break;
			case POSTSCRIPTFILE:
			  resE = PLOTPOSTSCRIPTFILE;
			  break;
			default:
			  resD = 0;
			}
		      } else {
			printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
			printMessage(1,"This command will have no effect.\n");
		      }
		    } 
		  }
		}
	      } 
	      if (resD) {
		externalPlot(tempString, a, b, (mp_prec_t) resB, resC, tempNode, resA, tools_precision, tempString2, resE);
	      }
	      if (tempString2 != NULL) free(tempString2);
	    } else {
	      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
	      printMessage(1,"This command will have no effect.\n");
	    }
	  } else {
	    printMessage(1,"Warning: the expression given does not evaluate to a constant range.\n");
	    printMessage(1,"This command will have no effect.\n");
	  }
	  mpfr_clear(a);
	  mpfr_clear(b);
	  freeThing(tempNode);
	} else {
	  printMessage(1,"Warning: the expression given does not evaluate to a function.\n");
	  printMessage(1,"This command will have no effect.\n");
	}
      } else {
	printMessage(1,"Warning: the expression given does not evaluate to one of absolute or relative.\n");
	printMessage(1,"This command will have no effect.\n");
      }
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    for (i=0;i<resA;i++)
      freeThing(array[i]);
    free(array);
    break; 
  case WRITE:
    curr = tree->arguments;
    while (curr != NULL) {
      tempNode = evaluateThing((node *) (curr->value));
      printThing(tempNode);
      freeThing(tempNode);
      curr = curr->next;
    }
    break; 			
  case NEWFILEWRITE:
    if (evaluateThingToString(&tempString, tree->child1)) {
      fd = fopen(tempString,"w");
      if (fd != NULL) {
	curr = tree->arguments;
	while (curr != NULL) {
	  tempNode = evaluateThing((node *) (curr->value));
	  fPrintThing(fd,tempNode);
	  freeThing(tempNode);
	  curr = curr->next;
	}
	fclose(fd);
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",tempString);
	printMessage(1,"This command will have no effect.\n");
      }
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    } 
    break;
  case APPENDFILEWRITE:
    if (evaluateThingToString(&tempString, tree->child1)) {
      fd = fopen(tempString,"a");
      if (fd != NULL) {
	curr = tree->arguments;
	while (curr != NULL) {
	  tempNode = evaluateThing((node *) (curr->value));
	  fPrintThing(fd,tempNode);
	  freeThing(tempNode);
	  curr = curr->next;
	}
	fclose(fd);
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be opened for appending.\n",tempString);
	printMessage(1,"This command will have no effect.\n");
      }
      free(tempString);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
      printMessage(1,"This command will have no effect.\n");
    } 
    break; 
  case ASCIIPLOT:
    if (evaluateThingToPureTree(&tempNode, tree->child1)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a, b, tree->child2)) {
	asciiPlotTree(tempNode, a, b, tools_precision);
      } else {
	printMessage(1,"Warning: the given expression does not evaluate to a constant range.\n");
	printMessage(1,"The command will not be executed.\n");
      }
      freeThing(tempNode);
      mpfr_clear(a);
      mpfr_clear(b);
    } else {
      printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
      printMessage(1,"The command will not be executed.\n");
    }
    break;			
  case PRINTXML:
    if (evaluateThingToPureTree(&tempNode, tree->child1)) {
      printf("\n");
      printXml(tempNode);
      freeThing(tempNode);
    } else {
      printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
      printMessage(1,"The command will not be executed.\n");
    }
    break;			
  case PRINTXMLNEWFILE:
    if (evaluateThingToPureTree(&tempNode, tree->child1)) {
      if (evaluateThingToString(&tempString, tree->child2)) {
	fd = fopen(tempString,"w");
	if (fd != NULL) {
	  fPrintXml(fd,tempNode);
	  fclose(fd);
	} else {
	  printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",tempString);
	  printMessage(1,"This command will have no effect.\n");
	}
      } else {
	printMessage(1,"Warning: the given expression does not evaluate to a string.\n");
	printMessage(1,"The command will not be executed.\n");
      }      
      freeThing(tempNode);
    } else {
      printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
      printMessage(1,"The command will not be executed.\n");
    }
    break;			
  case PRINTXMLAPPENDFILE:
    if (evaluateThingToPureTree(&tempNode, tree->child1)) {
      if (evaluateThingToString(&tempString, tree->child2)) {
	fd = fopen(tempString,"a");
	if (fd != NULL) {
	  fPrintXml(fd,tempNode);
	  fclose(fd);
	} else {
	  printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",tempString);
	  printMessage(1,"This command will have no effect.\n");
	}
      } else {
	printMessage(1,"Warning: the given expression does not evaluate to a string.\n");
	printMessage(1,"The command will not be executed.\n");
      }      
      freeThing(tempNode);
    } else {
      printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
      printMessage(1,"The command will not be executed.\n");
    }
    break;			
  case WORSTCASE:
    evaluateThingListToThingArray(&resA, &array, tree->arguments);
    resC = 0;
    if ((resA >= 6) && (isString(array[5]))) {
      fd = fopen((array[5])->string,"w");
      if (fd != NULL) {
	resC = 1;
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be opened for writing.\n",(array[5])->string);
	printMessage(1,"This command will have no effect.\n");
      }
    } else {
      resC = 1;
      fd = NULL;
    }
    if (resC) {
      if (evaluateThingToPureTree(&tempNode,array[0])) {
	mpfr_init2(a,tools_precision);
	if (evaluateThingToConstant(a,array[1],NULL)) {
	  mpfr_init2(b,tools_precision);
	  mpfr_init2(c,tools_precision);
	  if (evaluateThingToRange(b,c,array[2])) {
	    mpfr_init2(d,tools_precision);
	    if (evaluateThingToConstant(d,array[3],NULL)) {
	      mpfr_init2(e,tools_precision);
	      if (evaluateThingToConstant(e,array[4],NULL)) {
		tempRange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
		tempRange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
		mpfr_init2(*(tempRange.a),tools_precision);
		mpfr_init2(*(tempRange.b),tools_precision);
		mpfr_set(*(tempRange.a),b,GMP_RNDN);
		mpfr_set(*(tempRange.b),c,GMP_RNDN);
		printWorstCases(tempNode, a, tempRange, d, e, tools_precision, fd);
		mpfr_clear(*(tempRange.a));
		mpfr_clear(*(tempRange.b));
		free(tempRange.a);
		free(tempRange.b);
	      } else {
		printMessage(1,"Warning: the given expression does not evaluate to a constant.\n");
		printMessage(1,"The command will not be executed.\n");
	      }
	      mpfr_clear(e);			
	    } else {
	      printMessage(1,"Warning: the given expression does not evaluate to a constant.\n");
	      printMessage(1,"The command will not be executed.\n");
	    }
	    mpfr_clear(d);
	  } else {
	    printMessage(1,"Warning: the given expression does not evaluate to a constant range.\n");
	    printMessage(1,"The command will not be executed.\n");
	  }
	  mpfr_clear(b);
	  mpfr_clear(c);
	} else {
	  printMessage(1,"Warning: the given expression does not evaluate to a constant.\n");
	  printMessage(1,"The command will not be executed.\n");
	}
	mpfr_clear(a);
	freeThing(tempNode);
      } else {
	printMessage(1,"Warning: the given expression does not evaluate to a function.\n");
	printMessage(1,"The command will not be executed.\n");
      }
      if (fd != NULL) fclose(fd);
    }
    for (i=0;i<resA;i++)
      freeThing(array[i]);
    free(array);
    printf("\n");
    break; 			
  case RENAME:
    if (variablename == NULL) {
      variablename = (char *) safeCalloc(strlen((char *) (tree->arguments->value)) + 1,sizeof(char));
      strcpy(variablename,(char *) (tree->arguments->value));
    } else {
      if (strcmp(variablename,tree->string) == 0) {
	free(variablename);
	variablename = (char *) safeCalloc(strlen((char *) (tree->arguments->value)) + 1,sizeof(char));
	strcpy(variablename,(char *) (tree->arguments->value));
	printMessage(1,"Information: the free variable has been renamed from \"%s\" to \"%s\".\n",
		     tree->string,(char *) (tree->arguments->value));
      } else {
	printMessage(1,"Warning: the current free variable is named \"%s\" and not \"%s\". Can only rename the free variable.\n",
		     variablename,tree->string);
	printMessage(1,"The last command will have no effect.\n");
      }
    }
    break; 				
  case AUTOPRINT:
    curr = tree->arguments;
    while (curr != NULL) {
      tempNode = evaluateThing((node *) (curr->value));
      autoprint(tempNode);
      freeThing(tempNode);
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf("\n");
    break;  			
  case ASSIGNMENT:
    tempNode = evaluateThing(tree->child1);
    if (!assignThingToTable(tree->string, tempNode)) {
      printMessage(1,"Warning: the last assignment will have no effect.\n");
    }
    freeThing(tempNode);
    break; 	
  case ASSIGNMENTININDEXING:
    curr = tree->arguments;
    if (((node *) (curr->value))->nodeType == TABLEACCESS) {
      if ((tempNode = getThingFromTable(((node *) (curr->value))->string)) != NULL) {
	if (isPureList(tempNode)) {
	  curr = tree->arguments;
	  curr = curr->next;
	  if (evaluateThingToInteger(&resB, (node *) (curr->value), NULL)) {
	    if ((resB >= 0) && (resB <= lengthChain(tempNode->arguments))) {
	      curr = curr->next; 
	      tempNode2 = evaluateThing((node *) (curr->value));
	      if (resB == lengthChain(tempNode->arguments)) {
		tempList = addElement(copyChain(tempNode->arguments,copyThingOnVoid),copyThing(tempNode2));
		tempList2 = copyChain(tempList,copyThingOnVoid);
		freeChain(tempList,freeThingOnVoid);
		tempNode3 = makeList(tempList2);
	      } else {
		tempNode3 = makeList(copyChainAndReplaceNth(tempNode->arguments, resB, tempNode2, copyThingOnVoid));
	      }
	      curr = tree->arguments;
	      if (!assignThingToTable(((node *) (curr->value))->string, tempNode3)) {
		printMessage(1,"Warning: the last assignment will have no effect.\n");
	      }
	      freeThing(tempNode3);
	    } else {
	      printMessage(1,"Warning: assigning to indexed elements of lists is only allowed on indexes in the existing range.\n");
	      printMessage(1,"This command will have no effect.\n");
	    }
	  } else {
	    printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
	    printMessage(1,"This command will have no effect.\n");
	  }
	} else {
	  if (isEmptyList(tempNode)) {
	    curr = tree->arguments;
	    curr = curr->next;
	    if (evaluateThingToInteger(&resB, (node *) (curr->value), NULL)) {
	      if (resB == 0) {
		curr = curr->next; 
		tempNode2 = evaluateThing((node *) (curr->value));
		tempNode3 = makeList(addElement(NULL,tempNode2));
		curr = tree->arguments;
		if (!assignThingToTable(((node *) (curr->value))->string, tempNode3)) {
		  printMessage(1,"Warning: the last assignment will have no effect.\n");
		}
		freeThing(tempNode3);
	      } else {
		printMessage(1,"Warning: assigning to indexed elements of empty lists is only allowed on index 0.\n");
		printMessage(1,"This command will have no effect.\n");
	      }
	    } else {
	      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
	      printMessage(1,"This command will have no effect.\n");
	    }
	  } else {
	    if (isString(tempNode)) {
	      curr = tree->arguments;
	      curr = curr->next;
	      if (evaluateThingToInteger(&resB, (node *) (curr->value), NULL)) {
		if ((resB >= 0) && (resB <= strlen(tempNode->string))) {
		  curr = curr->next; 
		  if (evaluateThingToString(&tempString,(node *) (curr->value))) {
		    if (strlen(tempString) == 1) {
		      if (resB == strlen(tempNode->string)) {
			tempString2 = (char *) safeCalloc(resB + 2,sizeof(char));
			strcpy(tempString2,tempNode->string);
			tempString2[resB] = tempString[0];
			tempNode3 = makeString(tempString2);
			free(tempString2);
		      } else {
			tempNode3 = makeString(tempNode->string);
			(tempNode3->string)[resB] = tempString[0];
		      }
		      curr = tree->arguments;
		      if (!assignThingToTable(((node *) (curr->value))->string, tempNode3)) {
			printMessage(1,"Warning: the last assignment will have no effect.\n");
		      }
		      freeThing(tempNode3);
		    } else {
		      printMessage(1,"Warning: the string to be assigned is not of length 1.\n");
		      printMessage(1,"This command will have no effect.\n");		      
		    }
		    free(tempString);
		  } else {
		    printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
		    printMessage(1,"This command will have no effect.\n");
		  }
		} else {
		  printMessage(1,"Warning: assigning to indexed elements of strings is only allowed in the existing range.\n");
		  printMessage(1,"This command will have no effect.\n");
		}
	      } else {
		printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
		printMessage(1,"This command will have no effect.\n");
	      }	       
	    } else {
	      curr = tree->arguments;
	      printMessage(1,"Warning: the identifier \"%s\" is not assigned to a (empty) list or a string.\n",
			   ((node *) (curr->value))->string);
	      printMessage(1,"The command will not be executed.\n");
	    }
	  }
	}
	freeThing(tempNode);
      } else {
	curr = tree->arguments;
	printMessage(1,"Warning: the identifier \"%s\" is not assigned to.\n",((node *) (curr->value))->string);
	printMessage(1,"This command will have no effect.\n");
      }
    } else {
      printMessage(1,"Warning: the first element is not an identifier.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;
  case LIBRARYBINDING:
    if ((variablename != NULL) && (strcmp(variablename,tree->string) == 0)) {
      printMessage(1,"Warning: the identifier \"%s\" is already be bound as the current free variable.\n",variablename);
      printMessage(1,"It cannot be bound to a library function. This command will have no effect.\n");
    } else {
      if (containsEntry(symbolTable, tree->string)) {
	printMessage(1,"Warning: the identifier \"%s\" is already assign to.\n",variablename);
	printMessage(1,"It cannot be bound to a library function. This command will have no effect.\n");
      } else {
	if (evaluateThingToString(&tempString, tree->child1)) {
	  tempLibraryFunction = bindFunction(tempString, tree->string);
	  if(tempLibraryFunction == NULL) {
	    printMessage(1,"Warning: an error occured. The last command will have no effect.\n");
	  }
	} else {
	  printMessage(1,"Warning: the expression given does not evaluate to a string.\n");
	  printMessage(1,"This command will have no effect.\n");
	}
      }
    }
    break;  			
  case PRECASSIGN:
    defaultVal = DEFAULTPRECISION;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 12) {
	resA = 12;
	printMessage(1,"Warning: the precision of the tool must be at least 12 bits.\n");
      }
      defaultprecision = resA;
      tools_precision = resA;
      printf("The precision has been set to %d bits.\n",resA);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case POINTSASSIGN:
    defaultVal = DEFAULTPOINTS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 3) {
	resA = 3;
	printMessage(1,"Warning: the number of points must be at least 3 points.\n");
      }
      defaultpoints = resA;
      printf("The number of points has been set to %d.\n",resA);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case DIAMASSIGN:
    mpfr_init2(a,tools_precision);
    mpfr_init2(b,tools_precision);
    mpfr_set_d(b,DEFAULTDIAM,GMP_RNDN);
    if (evaluateThingToConstant(a, tree->child1, &b)) {
      mpfr_clear(statediam);
      mpfr_init2(statediam,tools_precision);
      mpfr_set(statediam,a,GMP_RNDN);
      printf("The diameter has been set to ");
      printMpfr(a);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    mpfr_clear(a);
    mpfr_clear(b);
    break;			
  case DISPLAYASSIGN:
    resB = 0;
    if (evaluateThingToDisplayMode(&resA, tree->child1, &resB)) {
      dyadic = resA;
      switch (dyadic) {	     
      case 0:
	printf("Display mode is decimal numbers.\n");
	break;
      case 1:
	printf("Display mode is dyadic numbers.\n");
	break;
      case 2:
	printf("Display mode is dyadic numbers in integer-power-of-2 notation.\n");
	break;
      case 3:
	printf("Display mode is binary numbers.\n");
	break;
      default:
	printf("Display mode in unknown state.\n");
      }
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to default, dyadic, powers or binary.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case VERBOSITYASSIGN:
    defaultVal = 1;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(1,"Warning: the verbosity of the tool must not be negative.\n");
      }
      verbosity = resA;
      printf("The verbosity level has been set to %d.\n",resA);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  		
  case CANONICALASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      canonical = resA;
      if (canonical) 
	printf("Canonical automatic printing output has been activated.\n");
      else 
	printf("Canonical automatic printing output has been deactivated.\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case AUTOSIMPLIFYASSIGN:
    defaultVal = 1;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      autosimplify = resA;
      if (autosimplify) 
	printf("Automatic pure tree simplification has been activated.\n");
      else 
	printf("Automatic pure tree simplification has been deactivated.\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  		
  case TAYLORRECURSASSIGN:
    defaultVal = DEFAULTTAYLORRECURSIONS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(1,"Warning: the number of recursions for Taylor evaluation must not be negative.\n");
      }
      verbosity = resA;
      taylorrecursions = resA;
      printf("The number of recursions for Taylor evaluation has been set to %d.\n",resA);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case TIMINGASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      timecounting = resA;
      if (timecounting) 
	printf("Timing has been activated.\n");
      else 
	printf("Timing has been deactivated.\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case FULLPARENASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      fullParentheses = resA;
      if (fullParentheses) 
	printf("Full parentheses mode has been activated.\n");
      else 
	printf("Full parentheses mode has been deactivated.\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  		
  case MIDPOINTASSIGN:
    defaultVal = 1;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      midpointMode = resA;
      if (midpointMode) 
	printf("Midpoint mode has been activated.\n");
      else 
	printf("Midpoint mode has been deactivated.\n");
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 			
  case HOPITALRECURSASSIGN:
    defaultVal = DEFAULTHOPITALRECURSIONS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(1,"Warning: the number of recursions for Hopital's rule must not be negative.\n");
      }
      hopitalrecursions = resA;
      printf("The number of recursions for Hopital's rule has been set to %d.\n",resA);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case PRECSTILLASSIGN:
    defaultVal = DEFAULTPRECISION;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 12) {
	resA = 12;
	printMessage(2,"Warning: the precision of the tool must be at least 12 bits.\n");
      }
      defaultprecision = resA;
      tools_precision = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case POINTSSTILLASSIGN:
    defaultVal = DEFAULTPOINTS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 3) {
	resA = 3;
	printMessage(2,"Warning: the number of points must be at least 3 points.\n");
      }
      defaultpoints = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case DIAMSTILLASSIGN:
    mpfr_init2(a,tools_precision);
    mpfr_init2(b,tools_precision);
    mpfr_set_d(b,DEFAULTDIAM,GMP_RNDN);
    if (evaluateThingToConstant(a, tree->child1, &b)) {
      mpfr_clear(statediam);
      mpfr_init2(statediam,tools_precision);
      mpfr_set(statediam,a,GMP_RNDN);
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    mpfr_clear(a);
    mpfr_clear(b);
    break; 		
  case DISPLAYSTILLASSIGN:
    resB = 0;
    if (evaluateThingToDisplayMode(&resA, tree->child1, &resB)) {
      dyadic = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to default, dyadic, powers or binary.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  		
  case VERBOSITYSTILLASSIGN:
    defaultVal = 1;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(2,"Warning: the verbosity of the tool must not be negative.\n");
      }
      verbosity = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case CANONICALSTILLASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      canonical = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    defaultVal = 1;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      autosimplify = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    defaultVal = DEFAULTTAYLORRECURSIONS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(2,"Warning: the number of recursions for Taylor evaluation must not be negative.\n");
      }
      taylorrecursions = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 	
  case TIMINGSTILLASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      timecounting = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case FULLPARENSTILLASSIGN:
    defaultVal = 0;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      fullParentheses = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  		
  case MIDPOINTSTILLASSIGN:
    defaultVal = 1;
    if (evaluateThingToOnOff(&resA, tree->child1, &defaultVal)) {
      midpointMode = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to on or off.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    defaultVal = DEFAULTHOPITALRECURSIONS;
    if (evaluateThingToInteger(&resA, tree->child1, &defaultVal)) {
      if (resA < 0) {
	resA = 0;
	printMessage(2,"Warning: the number of recursions for Hopital's rule must not be negative.\n");
      }
      hopitalrecursions = resA;
    } else {
      printMessage(1,"Warning: the expression given does not evaluate to a machine integer.\n");
      printMessage(1,"This command will have no effect.\n");
    }
    break;  	
  default:
    fprintf(stderr,"Error: executeCommand: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }
  
  if (timingString != NULL) {
    popTimeCounter(timingString);
    free(timingString);
  }

  return result;
}



node *makeCommandList(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMMANDLIST;
  res->arguments = thinglist;

  return res;

}

node *makeWhile(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = WHILE;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeIfElse(node *thing1, node *thing2, node *thing3) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = IFELSE;
  res->arguments = addElement(addElement(addElement(NULL, thing3), thing2), thing1);

  return res;

}

node *makeIf(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = IF;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeFor(char *string, node *thing1, node *thing2, node *thing3, node *thing4) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FOR;
  res->string = (char *) safeCalloc(strlen(string) + 1,sizeof(char));
  strcpy(res->string, string);
  res->arguments = addElement(addElement(addElement(addElement(NULL, thing4), thing3), thing2), thing1);

  return res;

}

node *makeConstantDouble(double d) {
  node *res;
  
  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CONSTANT;
  res->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
  mpfr_init2(*(res->value),53);
  mpfr_set_d(*(res->value),d,GMP_RNDN);

  return res;
}


node *makeForIn(char *string, node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FORIN;
  res->child1 = thing1;
  res->child2 = thing2;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeQuit() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = QUIT;

  return res;

}

node *makeFalseQuit() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FALSEQUIT;

  return res;

}

node *makeRestart() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = RESTART;

  return res;

}

node *makePrint(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINT;
  res->arguments = thinglist;

  return res;

}

node *makePrintXml(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTXML;
  res->child1 = thing;

  return res;

}

node *makePrintXmlNewFile(node *thing, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTXMLNEWFILE;
  res->child1 = thing;
  res->child2 = thing2;

  return res;

}

node *makePrintXmlAppendFile(node *thing, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTXMLAPPENDFILE;
  res->child1 = thing;
  res->child2 = thing2;

  return res;

}


node *makeNewFilePrint(node *thing, chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = NEWFILEPRINT;
  res->arguments = thinglist;
  res->child1 = thing;

  return res;

}

node *makeAppendFilePrint(node *thing, chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = APPENDFILEPRINT;
  res->arguments = thinglist;
  res->child1 = thing;
  

  return res;

}

node *makePlot(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PLOT;
  res->arguments = thinglist;

  return res;

}

node *makePrintHexa(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTHEXA;
  res->child1 = thing;

  return res;

}

node *makePrintBinary(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTBINARY;
  res->child1 = thing;

  return res;

}

node *makePrintExpansion(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRINTEXPANSION;
  res->child1 = thing;

  return res;

}

node *makeBashExecute(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = BASHEXECUTE;
  res->child1 = thing;

  return res;

}

node *makeExternalPlot(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = EXTERNALPLOT;
  res->arguments = thinglist;

  return res;

}

node *makeWrite(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = WRITE;
  res->arguments = thinglist;

  return res;

}

node *makeNewFileWrite(node *thing, chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = NEWFILEWRITE;
  res->child1 = thing;
  res->arguments = thinglist;

  return res;

}

node *makeAppendFileWrite(node *thing, chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = APPENDFILEWRITE;
  res->child1 = thing;
  res->arguments = thinglist;

  return res;

}

node *makeAsciiPlot(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ASCIIPLOT;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeWorstCase(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = WORSTCASE;
  res->arguments = thinglist;

  return res;

}

node *makeRename(char *string1, char *string2) {
  node *res;
  char *tempString;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = RENAME;
  res->string = (char *) safeCalloc(strlen(string1) + 1, sizeof(char));
  strcpy(res->string,string1);
  tempString = (char *) safeCalloc(strlen(string2) + 1, sizeof(char));
  strcpy(tempString,string2);
  res->arguments = addElement(NULL,tempString);

  return res;

}

node *makeAutoprint(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = AUTOPRINT;
  res->arguments = thinglist;

  return res;

}

node *makeAssignment(char *string, node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ASSIGNMENT;
  res->child1 = thing;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeLibraryBinding(char *string, node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = LIBRARYBINDING;
  res->child1 = thing;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makePrecAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRECASSIGN;
  res->child1 = thing;

  return res;

}

node *makePointsAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POINTSASSIGN;
  res->child1 = thing;

  return res;

}

node *makeDiamAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIAMASSIGN;
  res->child1 = thing;

  return res;

}

node *makeDisplayAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DISPLAYASSIGN;
  res->child1 = thing;

  return res;

}

node *makeVerbosityAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = VERBOSITYASSIGN;
  res->child1 = thing;

  return res;

}

node *makeCanonicalAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CANONICALASSIGN;
  res->child1 = thing;

  return res;

}

node *makeAutoSimplifyAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = AUTOSIMPLIFYASSIGN;
  res->child1 = thing;

  return res;

}

node *makeTaylorRecursAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TAYLORRECURSASSIGN;
  res->child1 = thing;

  return res;

}

node *makeTimingAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TIMINGASSIGN;
  res->child1 = thing;

  return res;

}

node *makeFullParenAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FULLPARENASSIGN;
  res->child1 = thing;

  return res;

}

node *makeMidpointAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = MIDPOINTASSIGN;
  res->child1 = thing;

  return res;

}

node *makeHopitalRecursAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HOPITALRECURSASSIGN;
  res->child1 = thing;

  return res;

}

node *makePrecStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRECSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makePointsStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POINTSSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeDiamStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIAMSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeDisplayStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DISPLAYSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeVerbosityStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = VERBOSITYSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeCanonicalStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CANONICALSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeAutoSimplifyStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = AUTOSIMPLIFYSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeTaylorRecursStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TAYLORRECURSSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeTimingStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TIMINGSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeFullParenStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FULLPARENSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeMidpointStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = MIDPOINTSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeHopitalRecursStillAssign(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HOPITALRECURSSTILLASSIGN;
  res->child1 = thing;

  return res;

}

node *makeAnd(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = AND;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeOr(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = OR;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeNegation(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = NEGATION;
  res->child1 = thing;

  return res;

}

node *makeIndex(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = INDEX;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareEqual(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPAREEQUAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareLess(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPARELESS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareGreater(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPAREGREATER;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareLessEqual(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPARELESSEQUAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareGreaterEqual(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPAREGREATEREQUAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCompareNotEqual(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COMPARENOTEQUAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeConcat(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CONCAT;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeAddToList(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ADDTOLIST;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeOn() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ON;

  return res;

}

node *makeOff() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = OFF;

  return res;

}

node *makeDyadic() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DYADIC;

  return res;

}

node *makePowers() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POWERS;

  return res;

}

node *makeBinaryThing() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = BINARY;

  return res;

}

node *makeFile() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FILESYM;

  return res;

}

node *makePostscript() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POSTSCRIPT;

  return res;

}

node *makePostscriptFile() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POSTSCRIPTFILE;

  return res;

}

node *makePerturb() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PERTURB;

  return res;

}

node *makeRoundDown() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDDOWN;

  return res;

}

node *makeRoundUp() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDUP;

  return res;

}

node *makeRoundToZero() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDTOZERO;

  return res;

}

node *makeRoundToNearest() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDTONEAREST;

  return res;

}

node *makeHonorCoeff() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HONORCOEFF;

  return res;

}

node *makeTrue() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TRUE;

  return res;

}

node *makeFalse() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FALSE;

  return res;

}

node *makeDefault() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DEFAULT;

  return res;

}

node *makeDecimal() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DECIMAL;

  return res;

}

node *makeAbsolute() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ABSOLUTESYM;

  return res;

}

node *makeRelative() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = RELATIVESYM;

  return res;

}

node *makeError() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ERRORSPECIAL;

  return res;

}


node *makeDoubleSymbol() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DOUBLESYMBOL;

  return res;

}

node *makeDoubleextendedSymbol() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DOUBLEEXTENDEDSYMBOL;

  return res;

}


node *makeDoubleDoubleSymbol() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DOUBLEDOUBLESYMBOL;

  return res;

}

node *makeTripleDoubleSymbol() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TRIPLEDOUBLESYMBOL;

  return res;

}

node *makeString(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = STRING;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeTableAccess(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TABLEACCESS;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeTableAccessWithSubstitute(char *string, node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TABLEACCESSWITHSUBSTITUTE;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);
  res->child1 = thing;

  return res;

}

node *makeDecimalConstant(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DECIMALCONSTANT;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeDyadicConstant(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DYADICCONSTANT;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeHexConstant(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HEXCONSTANT;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeBinaryConstant(char *string) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = BINARYCONSTANT;
  res->string = (char *) safeCalloc(strlen(string) + 1, sizeof(char));
  strcpy(res->string, string);

  return res;

}

node *makeEmptyList() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = EMPTYLIST;

  return res;

}

node *makeList(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = LIST;
  res->arguments = thinglist;

  return res;

}

node *makeFinalEllipticList(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FINALELLIPTICLIST;
  res->arguments = thinglist;

  return res;

}

node *makeElliptic() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ELLIPTIC;

  return res;

}

node *makeRange(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = RANGE;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}


node *makeDeboundMax(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DEBOUNDMAX;
  res->child1 = thing;

  return res;

}

node *makeDeboundMin(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DEBOUNDMIN;
  res->child1 = thing;

  return res;

}

node *makeDeboundMid(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DEBOUNDMID;
  res->child1 = thing;

  return res;

}

node *makeDiff(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIFF;
  res->child1 = thing;

  return res;

}

node *makeSimplify(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = SIMPLIFY;
  res->child1 = thing;

  return res;

}

node *makeRemez(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = REMEZ;
  res->arguments = thinglist;

  return res;

}

node *makeHorner(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HORNER;
  res->child1 = thing;

  return res;

}

node *makeCanonicalThing(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CANONICAL;
  res->child1 = thing;

  return res;

}

node *makeExpand(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = EXPAND;
  res->child1 = thing;

  return res;

}

node *makeSimplifySafe(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = SIMPLIFYSAFE;
  res->child1 = thing;

  return res;

}

node *makeTaylor(node *thing1, node *thing2, node *thing3) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TAYLOR;
  res->arguments = addElement(addElement(addElement(NULL, thing3), thing2), thing1);

  return res;

}

node *makeDegree(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DEGREE;
  res->child1 = thing;

  return res;

}

node *makeNumerator(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = NUMERATOR;
  res->child1 = thing;

  return res;

}

node *makeDenominator(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DENOMINATOR;
  res->child1 = thing;

  return res;

}

node *makeSubstitute(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = SUBSTITUTE;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeCoeff(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = COEFF;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeSubpoly(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = SUBPOLY;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeRoundcoefficients(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDCOEFFICIENTS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeRationalapprox(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = RATIONALAPPROX;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeAccurateInfnorm(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ACCURATEINFNORM;
  res->arguments = thinglist;

  return res;

}

node *makeRoundToFormat(node *thing1, node *thing2, node *thing3) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ROUNDTOFORMAT;
  res->arguments = addElement(addElement(addElement(NULL, thing3), thing2), thing1);

  return res;

}

node *makeEvaluate(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = EVALUATE;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeParse(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PARSE;
  res->child1 = thing;

  return res;

}

node *makeReadXml(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = READXML;
  res->child1 = thing;

  return res;

}


node *makeInfnorm(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = INFNORM;
  res->arguments = thinglist;

  return res;

}

node *makeFindZeros(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FINDZEROS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeFPFindZeros(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FPFINDZEROS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeDirtyInfnorm(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIRTYINFNORM;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeIntegral(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = INTEGRAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeDirtyIntegral(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIRTYINTEGRAL;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeImplementPoly(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = IMPLEMENTPOLY;
  res->arguments = thinglist;

  return res;

}

node *makeCheckInfnorm(node *thing1, node *thing2, node *thing3) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CHECKINFNORM;
  res->arguments = addElement(addElement(addElement(NULL, thing3), thing2), thing1);

  return res;

}

node *makeZeroDenominators(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ZERODENOMINATORS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeIsEvaluable(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ISEVALUABLE;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeSearchGal(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = SEARCHGAL;
  res->arguments = thinglist;

  return res;

}

node *makeGuessDegree(chain *thinglist) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = GUESSDEGREE;
  res->arguments = thinglist;

  return res;

}

node *makeDirtyFindZeros(node *thing1, node *thing2) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIRTYFINDZEROS;
  res->child1 = thing1;
  res->child2 = thing2;

  return res;

}

node *makeHead(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HEAD;
  res->child1 = thing;

  return res;

}

node *makeTail(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TAIL;
  res->child1 = thing;

  return res;

}

node *makeLength(node *thing) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = LENGTH;
  res->child1 = thing;

  return res;

}


node *makePrecDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = PRECDEREF;

  return res;

}

node *makePointsDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = POINTSDEREF;

  return res;

}


node *makeDiamDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DIAMDEREF;

  return res;

}


node *makeDisplayDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = DISPLAYDEREF;

  return res;

}


node *makeVerbosityDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = VERBOSITYDEREF;

  return res;

}


node *makeCanonicalDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = CANONICALDEREF;

  return res;

}


node *makeAutoSimplifyDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = AUTOSIMPLIFYDEREF;

  return res;

}


node *makeTaylorRecursDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TAYLORRECURSDEREF;

  return res;

}


node *makeTimingDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = TIMINGDEREF;

  return res;

}


node *makeFullParenDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = FULLPARENDEREF;

  return res;

}


node *makeMidpointDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = MIDPOINTDEREF;

  return res;

}


node *makeHopitalRecursDeref() {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = HOPITALRECURSDEREF;

  return res;

}

node *makeAssignmentInIndexing(node *thing1, node *thing2, node *thing3) {
  node *res;

  res = (node *) safeMalloc(sizeof(node));
  res->nodeType = ASSIGNMENTININDEXING;
  res->arguments = addElement(addElement(addElement(NULL,thing3),thing2),thing1);

  return res;
}

void freeThingOnVoid(void *tree) {
  freeThing((node *) tree);
}

void freeThing(node *tree) {
  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    free(tree);
    break;
  case CONSTANT:
    mpfr_clear(*(tree->value));
    free(tree->value);
    free(tree);
    break;
  case ADD:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;
  case SUB:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;
  case MUL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;
  case DIV:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;
  case SQRT:
    freeThing(tree->child1);
    free(tree);
    break;
  case EXP:
    freeThing(tree->child1);
    free(tree);
    break;
  case LOG:
    freeThing(tree->child1);
    free(tree);
    break;
  case LOG_2:
    freeThing(tree->child1);
    free(tree);
    break;
  case LOG_10:
    freeThing(tree->child1);
    free(tree);
    break;
  case SIN:
    freeThing(tree->child1);
    free(tree);
    break;
  case COS:
    freeThing(tree->child1);
    free(tree);
    break;
  case TAN:
    freeThing(tree->child1);
    free(tree);
    break;
  case ASIN:
    freeThing(tree->child1);
    free(tree);
    break;
  case ACOS:
    freeThing(tree->child1);
    free(tree);
    break;
  case ATAN:
    freeThing(tree->child1);
    free(tree);
    break;
  case SINH:
    freeThing(tree->child1);
    free(tree);
    break;
  case COSH:
    freeThing(tree->child1);
    free(tree);
    break;
  case TANH:
    freeThing(tree->child1);
    free(tree);
    break;
  case ASINH:
    freeThing(tree->child1);
    free(tree);
    break;
  case ACOSH:
    freeThing(tree->child1);
    free(tree);
    break;
  case ATANH:
    freeThing(tree->child1);
    free(tree);
    break;
  case POW:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;
  case NEG:
    freeThing(tree->child1);
    free(tree);
    break;
  case ABS:
    freeThing(tree->child1);
    free(tree);
    break;
  case DOUBLE:
    freeThing(tree->child1);
    free(tree);
    break;
  case DOUBLEDOUBLE:
    freeThing(tree->child1);
    free(tree);
    break;
  case TRIPLEDOUBLE:
    freeThing(tree->child1);
    free(tree);
    break;
  case ERF: 
    freeThing(tree->child1);
    free(tree);
    break;
  case ERFC:
    freeThing(tree->child1);
    free(tree);
    break;
  case LOG_1P:
    freeThing(tree->child1);
    free(tree);
    break;
  case EXP_M1:
    freeThing(tree->child1);
    free(tree);
    break;
  case DOUBLEEXTENDED:
    freeThing(tree->child1);
    free(tree);
    break;
  case LIBRARYFUNCTION:
    freeThing(tree->child1);
    free(tree);
    break;
  case CEIL:
    freeThing(tree->child1);
    free(tree);
    break;
  case FLOOR:
    freeThing(tree->child1);
    free(tree);
    break;
  case PI_CONST:
    free(tree);
    break;
  case COMMANDLIST:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break;			
  case WHILE:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;				
  case IFELSE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 				
  case IF:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 				
  case FOR:
    free(tree->string);
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 				
  case FORIN:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree->string);
    free(tree);
    break;  				
  case QUIT:
    free(tree);
    break;  				
  case FALSEQUIT:
    free(tree);
    break; 			
  case RESTART:
    free(tree);
    break;  			
  case PRINT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 				
  case NEWFILEPRINT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree->child1);
    free(tree);
    break; 			
  case APPENDFILEPRINT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree->child1);
    free(tree);
    break; 			
  case PLOT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break;			
  case PRINTHEXA:
    free(tree->child1);
    free(tree);
    break; 
  case PRINTBINARY:
    free(tree->child1);
    free(tree);
    break; 			
  case PRINTEXPANSION:
    free(tree->child1);
    free(tree);
    break;
  case BASHEXECUTE:
    free(tree->child1);
    free(tree);
    break; 			
  case EXTERNALPLOT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 
  case WRITE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case NEWFILEWRITE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree->child1);
    free(tree);
    break;
  case APPENDFILEWRITE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree->child1);
    free(tree);
    break; 
  case ASCIIPLOT:
    free(tree->child1);
    free(tree->child2);
    free(tree);
    break;			
  case PRINTXML:
    free(tree->child1);
    free(tree);
    break;			
  case PRINTXMLNEWFILE:
    free(tree->child1);
    free(tree->child2);
    free(tree);
    break;			
  case PRINTXMLAPPENDFILE:
    free(tree->child1);
    free(tree->child2);
    free(tree);
    break;			
  case WORSTCASE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case RENAME:
    free(tree->string);
    freeChain(tree->arguments, free);
    free(tree);
    break; 				
  case AUTOPRINT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break;  			
  case ASSIGNMENT:
    freeThing(tree->child1);
    free(tree->string);
    free(tree);
    break; 			
  case LIBRARYBINDING:
    freeThing(tree->child1);
    free(tree->string);
    free(tree);
    break;  			
  case PRECASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case POINTSASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case DIAMASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;			
  case DISPLAYASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case VERBOSITYASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  		
  case CANONICALASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case AUTOSIMPLIFYASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  		
  case TAYLORRECURSASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case TIMINGASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case FULLPARENASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  		
  case MIDPOINTASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case HOPITALRECURSASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case PRECSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case POINTSSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case DIAMSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case DISPLAYSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  		
  case VERBOSITYSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case CANONICALSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 	
  case TIMINGSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case FULLPARENSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  		
  case MIDPOINTSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    freeThing(tree->child1);
    free(tree);
    break;  	
  case AND:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 				
  case OR:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;				
  case NEGATION:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case INDEX:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 				
  case COMPAREEQUAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case COMPARELESS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case COMPAREGREATER:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case COMPARELESSEQUAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 		
  case COMPAREGREATEREQUAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;		
  case COMPARENOTEQUAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;		
  case CONCAT:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case ADDTOLIST:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case ON:
    free(tree);
    break; 				
  case OFF:
    free(tree);
    break; 				
  case DYADIC:
    free(tree);
    break;  				
  case POWERS:
    free(tree);
    break; 				
  case BINARY:
    free(tree);
    break; 			 	
  case FILESYM:
    free(tree);
    break; 			 	
  case POSTSCRIPT:
    free(tree);
    break;  			
  case POSTSCRIPTFILE:
    free(tree);
    break; 			
  case PERTURB:
    free(tree);
    break; 			
  case ROUNDDOWN:
    free(tree);
    break; 			
  case ROUNDUP:
    free(tree);
    break; 			
  case ROUNDTOZERO:
    free(tree);
    break;  			
  case ROUNDTONEAREST:
    free(tree);
    break; 			
  case HONORCOEFF:
    free(tree);
    break; 			
  case TRUE:
    free(tree);
    break; 			 	
  case FALSE:
    free(tree);
    break; 			 	
  case DEFAULT:
    free(tree);
    break; 			
  case DECIMAL:
    free(tree);
    break; 			
  case ABSOLUTESYM:
    free(tree);
    break; 			
  case RELATIVESYM:
    free(tree);
    break; 			
  case ERRORSPECIAL:
    free(tree);
    break; 			
  case DOUBLESYMBOL:
    free(tree);
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    free(tree);
    break;  			
  case DOUBLEDOUBLESYMBOL:
    free(tree);
    break; 		
  case TRIPLEDOUBLESYMBOL:
    free(tree);
    break; 		
  case STRING:
    free(tree->string);
    free(tree);
    break; 			 	
  case TABLEACCESS:
    free(tree->string);
    free(tree);
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    free(tree->string);
    freeThing(tree->child1);
    free(tree);
    break;  	
  case DECIMALCONSTANT:
    free(tree->string);
    free(tree);
    break; 		
  case DYADICCONSTANT:
    free(tree->string);
    free(tree);
    break; 			
  case HEXCONSTANT:
    free(tree->string);
    free(tree);
    break; 			
  case BINARYCONSTANT:
    free(tree->string);
    free(tree);
    break; 			
  case EMPTYLIST:
    free(tree);
    break; 			
  case LIST:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			 	
  case FINALELLIPTICLIST:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 		
  case ELLIPTIC:
    free(tree);
    break; 			
  case RANGE:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			 	
  case DEBOUNDMAX:
    freeThing(tree->child1);
    free(tree);
    break;  			
  case DEBOUNDMIN:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case DEBOUNDMID:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case DIFF:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case SIMPLIFY:
    freeThing(tree->child1);
    free(tree);
    break;  			
  case SIMPLIFYSAFE:
    freeThing(tree->child1);
    free(tree);
    break;  			
  case REMEZ:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			 	
  case HORNER:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case CANONICAL:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case EXPAND:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case TAYLOR:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			 	
  case DEGREE:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case NUMERATOR:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case DENOMINATOR:
    freeThing(tree->child1);
    free(tree);
    break; 			
  case SUBSTITUTE:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;			
  case COEFF:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			 	
  case SUBPOLY:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case ROUNDCOEFFICIENTS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 		
  case RATIONALAPPROX:    
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case ACCURATEINFNORM:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 		
  case ROUNDTOFORMAT:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break;			
  case EVALUATE:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case PARSE:
    freeThing(tree->child1);
    free(tree);
    break; 			 
  case READXML:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case INFNORM:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case FINDZEROS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case FPFINDZEROS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case DIRTYINFNORM:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case INTEGRAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case DIRTYINTEGRAL:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;  			
  case IMPLEMENTPOLY:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case CHECKINFNORM:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case ZERODENOMINATORS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break;  		
  case ISEVALUABLE:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case SEARCHGAL:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case GUESSDEGREE:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 	
  case ASSIGNMENTININDEXING:
    freeChain(tree->arguments, freeThingOnVoid);
    free(tree);
    break; 			
  case DIRTYFINDZEROS:
    freeThing(tree->child1);
    freeThing(tree->child2);
    free(tree);
    break; 			
  case HEAD:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case TAIL:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case LENGTH:
    freeThing(tree->child1);
    free(tree);
    break; 			 	
  case PRECDEREF:
    free(tree);
    break; 			
  case POINTSDEREF:
    free(tree);
    break; 			
  case DIAMDEREF:
    free(tree);
    break; 			
  case DISPLAYDEREF:
    free(tree);
    break; 			
  case VERBOSITYDEREF:
    free(tree);
    break; 			
  case CANONICALDEREF:
    free(tree);
    break; 			
  case AUTOSIMPLIFYDEREF:
    free(tree);
    break; 		
  case TAYLORRECURSDEREF:
    free(tree);
    break; 		
  case TIMINGDEREF:
    free(tree);
    break; 			
  case FULLPARENDEREF:
    free(tree);
    break; 			
  case MIDPOINTDEREF:
    free(tree);
    break; 			
  case HOPITALRECURSDEREF:
    free(tree);
    break;  	       
  default:
    fprintf(stderr,"Error: freeThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }
  return;
}


void rawPrintThing(node *tree) {
  int i;
  chain *curr;

  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename != NULL) 
      printf("%s",variablename);
    else 
      printf("undefined");
    break;
  case CONSTANT:
    printValue(tree->value,mpfr_get_prec(*(tree->value)));
    break;
  case ADD:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") + (");
    rawPrintThing(tree->child2);
    printf(")");
    break;
  case SUB:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") - (");
    rawPrintThing(tree->child2);
    printf(")");
    break;
  case MUL:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") * (");
    rawPrintThing(tree->child2);
    printf(")");
    break;
  case DIV:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") / (");
    rawPrintThing(tree->child2);
    printf(")");
    break;
  case SQRT:
    printf("sqrt(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case EXP:
    printf("exp(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case LOG:
    printf("log(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case LOG_2:
    printf("log2(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case LOG_10:
    printf("log2(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case SIN:
    printf("sin(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case COS:
    printf("cos(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case TAN:
    printf("tan(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ASIN:
    printf("asin(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ACOS:
    printf("acos(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ATAN:
    printf("atan(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case SINH:
    printf("sinh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case COSH:
    printf("cosh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case TANH:
    printf("tanh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ASINH:
    printf("asinh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ACOSH:
    printf("acosh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ATANH:
    printf("atanh(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case POW:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") ^ (");
    rawPrintThing(tree->child2);
    printf(")");
    break;
  case NEG:
    printf("-(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ABS:
    printf("abs(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case DOUBLE:
    printf("double(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case DOUBLEDOUBLE:
    printf("doubledouble(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case TRIPLEDOUBLE:
    printf("tripledouble(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ERF: 
    printf("erf(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case ERFC:
    printf("erfc(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case LOG_1P:
    printf("log1p(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case EXP_M1:
    printf("expm1(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case DOUBLEEXTENDED:
    printf("doubleextended(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	printf("diff(");
      }
      printf("%s(",tree->libFun->functionName);
      printTree(tree->child1);
      printf(")");
      for (i=1;i<=tree->libFunDeriv;i++) {
	printf(")");
      }
    }
    break;
  case CEIL:
    printf("ceil(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case FLOOR:
    printf("floor(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case PI_CONST:
    printf("pi");
    break;
  case COMMANDLIST:
    printf("begin\n");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      printf(";\n");
      curr = curr->next;
    }
    printf("end\n");
    break;			
  case WHILE:
    printf("while ");
    rawPrintThing(tree->child1);
    printf(" do ");
    rawPrintThing(tree->child2);
    break;				
  case IFELSE:
    printf("if ");
    curr = tree->arguments;
    rawPrintThing((node *) (curr->value));
    curr = curr->next;
    printf(" then\n");
    rawPrintThing((node *) (curr->value));
    printf("\nelse\n");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));
    break; 				
  case IF:
    printf("if ");
    rawPrintThing(tree->child1);
    printf(" then\n");
    rawPrintThing(tree->child2);
    break; 				
  case FOR:
    printf("for %s from ", tree->string);
    curr = tree->arguments;
    rawPrintThing((node *) (curr->value));
    printf(" to ");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));
    printf(" by ");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));
    printf(" do\n");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));
    break; 				
  case FORIN:
    printf("for %s in ",tree->string);
    rawPrintThing(tree->child1);
    printf(" do\n");
    rawPrintThing(tree->child2);
    break;  				
  case QUIT:
    printf("quit");
    break;  				
  case FALSEQUIT:
    printf("falsequit");
    break; 			
  case RESTART:
    printf("restart");
    break;  			
  case PRINT:
    printf("print(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 				
  case NEWFILEPRINT:
    printf("print(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(") > ");
    rawPrintThing(tree->child1);
    break; 			
  case APPENDFILEPRINT:
    printf("print(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(") >> ");
    rawPrintThing(tree->child1);
    break; 			
  case PLOT:
    printf("plot(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break;			
  case PRINTHEXA:
    printf("printhexa(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 
  case PRINTBINARY:
    printf("printbinary(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case PRINTEXPANSION:
    printf("printexpansion(");
    rawPrintThing(tree->child1);
    printf(")");
    break;
  case BASHEXECUTE:
    printf("bashexecute(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case EXTERNALPLOT:
    printf("externalplot(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 
  case WRITE:
    printf("write(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case NEWFILEWRITE:
    printf("write(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(") > ");
    rawPrintThing(tree->child1);
    break;
  case APPENDFILEWRITE:
    printf("write(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(") >> ");
    rawPrintThing(tree->child1);
    break; 
  case ASCIIPLOT:
    printf("asciiplot(");
    rawPrintThing(tree->child1);
    printf(",");
    rawPrintThing(tree->child2);
    printf(")");
    break;			
  case PRINTXML:
    printf("printxml(");
    rawPrintThing(tree->child1);
    printf(")");
    break;			
  case PRINTXMLNEWFILE:
    printf("printxml(");
    rawPrintThing(tree->child1);
    printf(") > ");
    rawPrintThing(tree->child2);
    break;			
  case PRINTXMLAPPENDFILE:
    printf("printxml(");
    rawPrintThing(tree->child1);
    printf(") >> ");
    rawPrintThing(tree->child2);
    break;			
  case WORSTCASE:
    printf("worstcase(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case RENAME:
    printf("rename(%s,%s)",tree->string,(char *) (tree->arguments->value));
    break; 				
  case AUTOPRINT:
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    break;  			
  case ASSIGNMENT:
    printf("%s = ",tree->string);
    rawPrintThing(tree->child1);
    break; 			
  case LIBRARYBINDING:
    printf("%s = library(",tree->string);
    rawPrintThing(tree->child1);
    printf(")");
    break;  			
  case PRECASSIGN:
    printf("prec = ");
    rawPrintThing(tree->child1);
    break; 			
  case POINTSASSIGN:
    printf("points = ");
    rawPrintThing(tree->child1);
    break; 			
  case DIAMASSIGN:
    printf("diam = ");
    rawPrintThing(tree->child1);
    break;			
  case DISPLAYASSIGN:
    printf("display = ");
    rawPrintThing(tree->child1);
    break; 			
  case VERBOSITYASSIGN:
    printf("verbosity = ");
    rawPrintThing(tree->child1);
    break;  		
  case CANONICALASSIGN:
    printf("canonical = ");
    rawPrintThing(tree->child1);
    break; 		
  case AUTOSIMPLIFYASSIGN:
    printf("autosimplify = ");
    rawPrintThing(tree->child1);
    break;  		
  case TAYLORRECURSASSIGN:
    printf("taylorrecursions = ");
    rawPrintThing(tree->child1);
    break; 		
  case TIMINGASSIGN:
    printf("timing = ");
    rawPrintThing(tree->child1);
    break; 			
  case FULLPARENASSIGN:
    printf("fullparentheses = ");
    rawPrintThing(tree->child1);
    break;  		
  case MIDPOINTASSIGN:
    printf("midpointmode = ");
    rawPrintThing(tree->child1);
    break; 			
  case HOPITALRECURSASSIGN:
    printf("hopitalrecursions = ");
    rawPrintThing(tree->child1);
    break; 		
  case PRECSTILLASSIGN:
    printf("prec = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case POINTSSTILLASSIGN:
    printf("points = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case DIAMSTILLASSIGN:
    printf("diam = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case DISPLAYSTILLASSIGN:
    printf("display = ");
    rawPrintThing(tree->child1);
    printf("!");
    break;  		
  case VERBOSITYSTILLASSIGN:
    printf("verbosity = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case CANONICALSTILLASSIGN:
    printf("canonical = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    printf("autosimplify = ");
    rawPrintThing(tree->child1);
    printf("!");
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    printf("taylorrecursions = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 	
  case TIMINGSTILLASSIGN:
    printf("timing = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case FULLPARENSTILLASSIGN:
    printf("fullparentheses = ");
    rawPrintThing(tree->child1);
    printf("!");
    break;  		
  case MIDPOINTSTILLASSIGN:
    printf("midpointmode = ");
    rawPrintThing(tree->child1);
    printf("!");
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    printf("hopitalrecursions = ");
    rawPrintThing(tree->child1);
    printf("!");
    break;  	
  case AND:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") && (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 				
  case OR:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") || (");
    rawPrintThing(tree->child2);
    printf(")");
    break;				
  case NEGATION:
    printf("!(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case INDEX:
    rawPrintThing(tree->child1);
    printf("[");
    rawPrintThing(tree->child2);
    printf("]");
    break; 				
  case COMPAREEQUAL:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") == (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case COMPARELESS:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") < (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case COMPAREGREATER:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") > (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case COMPARELESSEQUAL:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") <= (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 		
  case COMPAREGREATEREQUAL:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") >= (");
    rawPrintThing(tree->child2);
    printf(")");
    break;		
  case COMPARENOTEQUAL:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") != (");
    rawPrintThing(tree->child2);
    printf(")");
    break;		
  case CONCAT:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") @ (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case ADDTOLIST:
    printf("(");
    rawPrintThing(tree->child1);
    printf(") :: (");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case ON:
    printf("on");
    break; 				
  case OFF:
    printf("off");
    break; 				
  case DYADIC:
    printf("dyadic");
    break;  				
  case POWERS:
    printf("powers");
    break; 				
  case BINARY:
    printf("binary");
    break; 			 	
  case FILESYM:
    printf("file");
    break; 			 	
  case POSTSCRIPT:
    printf("postscript");
    break;  			
  case POSTSCRIPTFILE:
    printf("postscriptfile");
    break; 			
  case PERTURB:
    printf("perturb");
    break; 			
  case ROUNDDOWN:
    printf("RD");
    break; 			
  case ROUNDUP:
    printf("RU");
    break; 			
  case ROUNDTOZERO:
    printf("RZ");
    break;  			
  case ROUNDTONEAREST:
    printf("RN");
    break; 			
  case HONORCOEFF:
    printf("honorcoeff");
    break; 			
  case TRUE:
    printf("true");
    break; 			 	
  case FALSE:
    printf("false");
    break; 			 	
  case DEFAULT:
    printf("default");
    break; 			
  case DECIMAL:
    printf("decimal");
    break; 			
  case ABSOLUTESYM:
    printf("absolute");
    break; 			
  case RELATIVESYM:
    printf("relative");
    break; 			
  case ERRORSPECIAL:
    printf("error");
    break; 			
  case DOUBLESYMBOL:
    printf("double");
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    printf("doubleextended");
    break;  			
  case DOUBLEDOUBLESYMBOL:
    printf("doubledouble");
    break; 		
  case TRIPLEDOUBLESYMBOL:
    printf("tripledouble");
    break; 		
  case STRING:
    printf("\"%s\"",tree->string);
    break; 			 	
  case TABLEACCESS:
    printf("%s",tree->string);
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    printf("%s(",tree->string);
    rawPrintThing(tree->child1);
    printf(")");
    break;  	
  case DECIMALCONSTANT:
    printf("decimalconstant(\"%s\")",tree->string);
    break; 		
  case DYADICCONSTANT:
    printf("dyadicconstant(\"%s\")",tree->string);
    break; 			
  case HEXCONSTANT:
    printf("hexconstant(\"%s\")",tree->string);
    break; 			
  case BINARYCONSTANT:
    printf("binaryconstant(\"%s\")",tree->string);
    break; 			
  case EMPTYLIST:
    printf("[| |]");
    break; 			
  case LIST:
    printf("[|");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf("|]");
    break; 			 	
  case FINALELLIPTICLIST:
    printf("[|");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf("...|]");
    break; 		
  case ELLIPTIC:
    printf("...");
    break; 			
  case RANGE:
    printf("[");
    rawPrintThing(tree->child1);
    printf(";");
    rawPrintThing(tree->child2);
    printf("]");
    break; 			 	
  case DEBOUNDMAX:
    printf("sup(");
    rawPrintThing(tree->child1);
    printf(")");
    break;  			
  case DEBOUNDMIN:
    printf("inf(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case DEBOUNDMID:
    printf("mid(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case DIFF:
    printf("diff(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case SIMPLIFY:
    printf("simplify(");
    rawPrintThing(tree->child1);
    printf(")");
    break;  			
  case SIMPLIFYSAFE:
    printf("simplifysafe(");
    rawPrintThing(tree->child1);
    printf(")");
    break;  			
  case REMEZ:
    printf("remez(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			 	
  case HORNER:
    printf("horner(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case CANONICAL:
    printf("canonical(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case EXPAND:
    printf("expand(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case TAYLOR:
    printf("taylor(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			 	
  case DEGREE:
    printf("degree(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case NUMERATOR:
    printf("numerator(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case DENOMINATOR:
    printf("denominator(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			
  case SUBSTITUTE:
    printf("substitute(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break;			
  case COEFF:
    printf("coeff(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			 	
  case SUBPOLY:
    printf("subpoly(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case ROUNDCOEFFICIENTS:
    printf("roundcoefficients(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 		
  case RATIONALAPPROX:    
    printf("rationalapprox(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case ACCURATEINFNORM:
    printf("accurateinfnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 		
  case ROUNDTOFORMAT:
    printf("roundtoformat(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break;			
  case EVALUATE:
    printf("evaluate(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case PARSE:
    printf("parse(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case READXML:
    printf("readxml(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case INFNORM:
    printf("infnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case FINDZEROS:
    printf("findzeros(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case FPFINDZEROS:
    printf("fpfindzeros(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case DIRTYINFNORM:
    printf("dirtyinfnorm(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case INTEGRAL:
    printf("integral(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case DIRTYINTEGRAL:
    printf("dirtyintegral(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break;  			
  case IMPLEMENTPOLY:
    printf("implementpoly(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case CHECKINFNORM:
    printf("checkinfnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case ZERODENOMINATORS:
    printf("zerodenominators(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break;  		
  case ISEVALUABLE:
    printf("isevaluable(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case SEARCHGAL:
    printf("searchgal(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case GUESSDEGREE:
    printf("guessdegree(");
    curr = tree->arguments;
    while (curr != NULL) {
      rawPrintThing((node *) (curr->value));
      if (curr->next != NULL) printf(", ");
      curr = curr->next;
    }
    printf(")");
    break; 			
  case ASSIGNMENTININDEXING:
    curr = tree->arguments;
    rawPrintThing((node *) (curr->value));
    printf("[");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));
    printf("] = ");
    curr = curr->next;
    rawPrintThing((node *) (curr->value));    
    break; 			
  case DIRTYFINDZEROS:
    printf("dirtyfindzeros(");
    rawPrintThing(tree->child1);
    printf(", ");
    rawPrintThing(tree->child2);
    printf(")");
    break; 			
  case HEAD:
    printf("head(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case TAIL:
    printf("tail(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case LENGTH:
    printf("length(");
    rawPrintThing(tree->child1);
    printf(")");
    break; 			 	
  case PRECDEREF:
    printf("prec = ?");
    break; 			
  case POINTSDEREF:
    printf("points = ?");
    break; 			
  case DIAMDEREF:
    printf("diam = ?");
    break; 			
  case DISPLAYDEREF:
    printf("display = ?");
    break; 			
  case VERBOSITYDEREF:
    printf("verbosity = ?");
    break; 			
  case CANONICALDEREF:
    printf("canonical = ?");
    break; 			
  case AUTOSIMPLIFYDEREF:
    printf("autosimplify = ?");
    break; 		
  case TAYLORRECURSDEREF:
    printf("taylorrecursions = ?");
    break; 		
  case TIMINGDEREF:
    printf("timing = ?");
    break; 			
  case FULLPARENDEREF:
    printf("fullparentheses = ?");
    break; 			
  case MIDPOINTDEREF:
    printf("midpointmode = ?");
    break; 			
  case HOPITALRECURSDEREF:
    printf("hopitalrecursion = ?");
    break;  	       
  default:
    fprintf(stderr,"Error: rawPrintThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }
  return;
}

void fRawPrintThing(FILE *fd, node *tree) {
  int i;
  chain *curr;

  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename != NULL) 
      fprintf(fd,"%s",variablename);
    else 
      fprintf(fd,"undefined");
    break;
  case CONSTANT:
    fprintValueWithPrintMode(fd,*(tree->value));
    break;
  case ADD:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") + (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;
  case SUB:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") - (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;
  case MUL:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") * (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;
  case DIV:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") / (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;
  case SQRT:
    fprintf(fd,"sqrt(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP:
    fprintf(fd,"exp(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG:
    fprintf(fd,"log(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_2:
    fprintf(fd,"log2(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_10:
    fprintf(fd,"log2(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SIN:
    fprintf(fd,"sin(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COS:
    fprintf(fd,"cos(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TAN:
    fprintf(fd,"tan(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASIN:
    fprintf(fd,"asin(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOS:
    fprintf(fd,"acos(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATAN:
    fprintf(fd,"atan(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case SINH:
    fprintf(fd,"sinh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case COSH:
    fprintf(fd,"cosh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TANH:
    fprintf(fd,"tanh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ASINH:
    fprintf(fd,"asinh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ACOSH:
    fprintf(fd,"acosh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ATANH:
    fprintf(fd,"atanh(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case POW:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") ^ (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;
  case NEG:
    fprintf(fd,"-(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ABS:
    fprintf(fd,"abs(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLE:
    fprintf(fd,"double(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"doubledouble(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"tripledouble(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERF: 
    fprintf(fd,"erf(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case ERFC:
    fprintf(fd,"erfc(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LOG_1P:
    fprintf(fd,"log1p(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case EXP_M1:
    fprintf(fd,"expm1(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"doubleextended(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case LIBRARYFUNCTION:
    {
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,"diff(");
      }
      fprintf(fd,"%s(",tree->libFun->functionName);
      printTree(tree->child1);
      fprintf(fd,")");
      for (i=1;i<=tree->libFunDeriv;i++) {
	fprintf(fd,")");
      }
    }
    break;
  case CEIL:
    fprintf(fd,"ceil(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case FLOOR:
    fprintf(fd,"floor(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case PI_CONST:
    fprintf(fd,"pi");
    break;
  case COMMANDLIST:
    fprintf(fd,"begin\n");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      fprintf(fd,";\n");
      curr = curr->next;
    }
    fprintf(fd,"end\n");
    break;			
  case WHILE:
    fprintf(fd,"while ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd," do ");
    fRawPrintThing(fd,tree->child2);
    break;				
  case IFELSE:
    fprintf(fd,"if ");
    curr = tree->arguments;
    fRawPrintThing(fd,(node *) (curr->value));
    curr = curr->next;
    fprintf(fd," then\n");
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd,"\nelse\n");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));
    break; 				
  case IF:
    fprintf(fd,"if ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd," then\n");
    fRawPrintThing(fd,tree->child2);
    break; 				
  case FOR:
    fprintf(fd,"for %s from ", tree->string);
    curr = tree->arguments;
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd," to ");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd," by ");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd," do\n");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));
    break; 				
  case FORIN:
    fprintf(fd,"for %s in ",tree->string);
    fRawPrintThing(fd,tree->child1);
    fprintf(fd," do\n");
    fRawPrintThing(fd,tree->child2);
    break;  				
  case QUIT:
    fprintf(fd,"quit");
    break;  				
  case FALSEQUIT:
    fprintf(fd,"falsequit");
    break; 			
  case RESTART:
    fprintf(fd,"restart");
    break;  			
  case PRINT:
    fprintf(fd,"print(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 				
  case NEWFILEPRINT:
    fprintf(fd,"print(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,") > ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case APPENDFILEPRINT:
    fprintf(fd,"print(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,") >> ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case PLOT:
    fprintf(fd,"plot(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break;			
  case PRINTHEXA:
    fprintf(fd,"printhexa(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 
  case PRINTBINARY:
    fprintf(fd,"printbinary(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case PRINTEXPANSION:
    fprintf(fd,"printexpansion(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;
  case BASHEXECUTE:
    fprintf(fd,"bashexecute(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case EXTERNALPLOT:
    fprintf(fd,"externalplot(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 
  case WRITE:
    fprintf(fd,"write(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case NEWFILEWRITE:
    fprintf(fd,"write(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,") > ");
    fRawPrintThing(fd,tree->child1);
    break;
  case APPENDFILEWRITE:
    fprintf(fd,"write(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,") >> ");
    fRawPrintThing(fd,tree->child1);
    break; 
  case ASCIIPLOT:
    fprintf(fd,"asciiplot(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,",");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;			
  case PRINTXML:
    fprintf(fd,"printxml(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;			
  case PRINTXMLNEWFILE:
    fprintf(fd,"printxml(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") > ");
    fRawPrintThing(fd,tree->child2);
    break;			
  case PRINTXMLAPPENDFILE:
    fprintf(fd,"printxml(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") >> ");
    fRawPrintThing(fd,tree->child2);
    break;			
  case WORSTCASE:
    fprintf(fd,"worstcase(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case RENAME:
    fprintf(fd,"rename(%s,%s)",tree->string,(char *) (tree->arguments->value));
    break; 				
  case AUTOPRINT:
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    break;  			
  case ASSIGNMENT:
    fprintf(fd,"%s = ",tree->string);
    fRawPrintThing(fd,tree->child1);
    break; 			
  case LIBRARYBINDING:
    fprintf(fd,"%s = library(",tree->string);
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;  			
  case PRECASSIGN:
    fprintf(fd,"prec = ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case POINTSASSIGN:
    fprintf(fd,"points = ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case DIAMASSIGN:
    fprintf(fd,"diam = ");
    fRawPrintThing(fd,tree->child1);
    break;			
  case DISPLAYASSIGN:
    fprintf(fd,"display = ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case VERBOSITYASSIGN:
    fprintf(fd,"verbosity = ");
    fRawPrintThing(fd,tree->child1);
    break;  		
  case CANONICALASSIGN:
    fprintf(fd,"canonical = ");
    fRawPrintThing(fd,tree->child1);
    break; 		
  case AUTOSIMPLIFYASSIGN:
    fprintf(fd,"autosimplify = ");
    fRawPrintThing(fd,tree->child1);
    break;  		
  case TAYLORRECURSASSIGN:
    fprintf(fd,"taylorrecursions = ");
    fRawPrintThing(fd,tree->child1);
    break; 		
  case TIMINGASSIGN:
    fprintf(fd,"timing = ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case FULLPARENASSIGN:
    fprintf(fd,"fullparentheses = ");
    fRawPrintThing(fd,tree->child1);
    break;  		
  case MIDPOINTASSIGN:
    fprintf(fd,"midpointmode = ");
    fRawPrintThing(fd,tree->child1);
    break; 			
  case HOPITALRECURSASSIGN:
    fprintf(fd,"hopitalrecursions = ");
    fRawPrintThing(fd,tree->child1);
    break; 		
  case PRECSTILLASSIGN:
    fprintf(fd,"prec = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case POINTSSTILLASSIGN:
    fprintf(fd,"points = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case DIAMSTILLASSIGN:
    fprintf(fd,"diam = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case DISPLAYSTILLASSIGN:
    fprintf(fd,"display = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break;  		
  case VERBOSITYSTILLASSIGN:
    fprintf(fd,"verbosity = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case CANONICALSTILLASSIGN:
    fprintf(fd,"canonical = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    fprintf(fd,"autosimplify = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    fprintf(fd,"taylorrecursions = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 	
  case TIMINGSTILLASSIGN:
    fprintf(fd,"timing = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case FULLPARENSTILLASSIGN:
    fprintf(fd,"fullparentheses = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break;  		
  case MIDPOINTSTILLASSIGN:
    fprintf(fd,"midpointmode = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    fprintf(fd,"hopitalrecursions = ");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"!");
    break;  	
  case AND:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") && (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 				
  case OR:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") || (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;				
  case NEGATION:
    fprintf(fd,"!(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case INDEX:
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,"[");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,"]");
    break; 				
  case COMPAREEQUAL:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") == (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case COMPARELESS:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") < (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case COMPAREGREATER:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") > (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case COMPARELESSEQUAL:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") <= (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 		
  case COMPAREGREATEREQUAL:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") >= (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;		
  case COMPARENOTEQUAL:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") != (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;		
  case CONCAT:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") @ (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case ADDTOLIST:
    fprintf(fd,"(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,") :: (");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case ON:
    fprintf(fd,"on");
    break; 				
  case OFF:
    fprintf(fd,"off");
    break; 				
  case DYADIC:
    fprintf(fd,"dyadic");
    break;  				
  case POWERS:
    fprintf(fd,"powers");
    break; 				
  case BINARY:
    fprintf(fd,"binary");
    break; 			 	
  case FILESYM:
    fprintf(fd,"file");
    break; 			 	
  case POSTSCRIPT:
    fprintf(fd,"postscript");
    break;  			
  case POSTSCRIPTFILE:
    fprintf(fd,"postscriptfile");
    break; 			
  case PERTURB:
    fprintf(fd,"perturb");
    break; 			
  case ROUNDDOWN:
    fprintf(fd,"RD");
    break; 			
  case ROUNDUP:
    fprintf(fd,"RU");
    break; 			
  case ROUNDTOZERO:
    fprintf(fd,"RZ");
    break;  			
  case ROUNDTONEAREST:
    fprintf(fd,"RN");
    break; 			
  case HONORCOEFF:
    fprintf(fd,"honorcoeff");
    break; 			
  case TRUE:
    fprintf(fd,"true");
    break; 			 	
  case FALSE:
    fprintf(fd,"false");
    break; 			 	
  case DEFAULT:
    fprintf(fd,"default");
    break; 			
  case DECIMAL:
    fprintf(fd,"default");
    break; 			
  case ABSOLUTESYM:
    fprintf(fd,"absolute");
    break; 			
  case RELATIVESYM:
    fprintf(fd,"relative");
    break; 			
  case ERRORSPECIAL:
    fprintf(fd,"error");
    break; 			
  case DOUBLESYMBOL:
    fprintf(fd,"double");
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    fprintf(fd,"doubleextended");
    break;  			
  case DOUBLEDOUBLESYMBOL:
    fprintf(fd,"doubledouble");
    break; 		
  case TRIPLEDOUBLESYMBOL:
    fprintf(fd,"tripledouble");
    break; 		
  case STRING:
    fprintf(fd,"\"%s\"",tree->string);
    break; 			 	
  case TABLEACCESS:
    fprintf(fd,"%s",tree->string);
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    fprintf(fd,"%s(",tree->string);
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;  	
  case DECIMALCONSTANT:
    fprintf(fd,"decimalconstant(\"%s\")",tree->string);
    break; 		
  case DYADICCONSTANT:
    fprintf(fd,"dyadicconstant(\"%s\")",tree->string);
    break; 			
  case HEXCONSTANT:
    fprintf(fd,"hexconstant(\"%s\")",tree->string);
    break; 			
  case BINARYCONSTANT:
    fprintf(fd,"binaryconstant(\"%s\")",tree->string);
    break; 			
  case EMPTYLIST:
    fprintf(fd,"[| |]");
    break; 			
  case LIST:
    fprintf(fd,"[|");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,"|]");
    break; 			 	
  case FINALELLIPTICLIST:
    fprintf(fd,"[|");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,"...|]");
    break; 		
  case ELLIPTIC:
    fprintf(fd,"...");
    break; 			
  case RANGE:
    fprintf(fd,"[");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,";");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,"]");
    break; 			 	
  case DEBOUNDMAX:
    fprintf(fd,"*<");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,">*");
    break;  			
  case DEBOUNDMIN:
    fprintf(fd,"*<");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,">_");
    break; 			
  case DEBOUNDMID:
    fprintf(fd,"*<");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,">.");
    break; 			
  case DIFF:
    fprintf(fd,"diff(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case SIMPLIFY:
    fprintf(fd,"simplify(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;  			
  case SIMPLIFYSAFE:
    fprintf(fd,"simplifysafe(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break;  			
  case REMEZ:
    fprintf(fd,"remez(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			 	
  case HORNER:
    fprintf(fd,"horner(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case CANONICAL:
    fprintf(fd,"canonical(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case EXPAND:
    fprintf(fd,"expand(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case TAYLOR:
    fprintf(fd,"taylor(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			 	
  case DEGREE:
    fprintf(fd,"degree(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case NUMERATOR:
    fprintf(fd,"numerator(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case DENOMINATOR:
    fprintf(fd,"denominator(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			
  case SUBSTITUTE:
    fprintf(fd,"substitute(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;			
  case COEFF:
    fprintf(fd,"coeff(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			 	
  case SUBPOLY:
    fprintf(fd,"subpoly(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case ROUNDCOEFFICIENTS:
    fprintf(fd,"roundcoefficients(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 		
  case RATIONALAPPROX:    
    fprintf(fd,"rationalapprox(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case ACCURATEINFNORM:
    fprintf(fd,"accurateinfnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 		
  case ROUNDTOFORMAT:
    fprintf(fd,"roundtoformat(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break;			
  case EVALUATE:
    fprintf(fd,"evaluate(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case PARSE:
    fprintf(fd,"parse(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case READXML:
    fprintf(fd,"readxml(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case INFNORM:
    fprintf(fd,"infnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case FINDZEROS:
    fprintf(fd,"findzeros(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case FPFINDZEROS:
    fprintf(fd,"fpfindzeros(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case DIRTYINFNORM:
    fprintf(fd,"dirtyinfnorm(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case INTEGRAL:
    fprintf(fd,"integral(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case DIRTYINTEGRAL:
    fprintf(fd,"dirtyintegral(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;  			
  case IMPLEMENTPOLY:
    fprintf(fd,"implementpoly(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case CHECKINFNORM:
    fprintf(fd,"checkinfnorm(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case ZERODENOMINATORS:
    fprintf(fd,"zerodenominators(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break;  		
  case ISEVALUABLE:
    fprintf(fd,"isevaluable(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case SEARCHGAL:
    fprintf(fd,"searchgal(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 			
  case GUESSDEGREE:
    fprintf(fd,"guessdegree(");
    curr = tree->arguments;
    while (curr != NULL) {
      fRawPrintThing(fd,(node *) (curr->value));
      if (curr->next != NULL) fprintf(fd,", ");
      curr = curr->next;
    }
    fprintf(fd,")");
    break; 	
  case ASSIGNMENTININDEXING:
    curr = tree->arguments;
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd,"[");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));
    fprintf(fd,"] = ");
    curr = curr->next;
    fRawPrintThing(fd,(node *) (curr->value));    
    break; 					
  case DIRTYFINDZEROS:
    fprintf(fd,"dirtyfindzeros(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,", ");
    fRawPrintThing(fd,tree->child2);
    fprintf(fd,")");
    break; 			
  case HEAD:
    fprintf(fd,"head(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case TAIL:
    fprintf(fd,"tail(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case LENGTH:
    fprintf(fd,"length(");
    fRawPrintThing(fd,tree->child1);
    fprintf(fd,")");
    break; 			 	
  case PRECDEREF:
    fprintf(fd,"prec = ?");
    break; 			
  case POINTSDEREF:
    fprintf(fd,"points = ?");
    break; 			
  case DIAMDEREF:
    fprintf(fd,"diam = ?");
    break; 			
  case DISPLAYDEREF:
    fprintf(fd,"display = ?");
    break; 			
  case VERBOSITYDEREF:
    fprintf(fd,"verbosity = ?");
    break; 			
  case CANONICALDEREF:
    fprintf(fd,"canonical = ?");
    break; 			
  case AUTOSIMPLIFYDEREF:
    fprintf(fd,"autosimplify = ?");
    break; 		
  case TAYLORRECURSDEREF:
    fprintf(fd,"taylorrecursions = ?");
    break; 		
  case TIMINGDEREF:
    fprintf(fd,"timing = ?");
    break; 			
  case FULLPARENDEREF:
    fprintf(fd,"fullparentheses = ?");
    break; 			
  case MIDPOINTDEREF:
    fprintf(fd,"midpointmode = ?");
    break; 			
  case HOPITALRECURSDEREF:
    fprintf(fd,"hopitalrecursion = ?");
    break;  	       
  default:
    fprintf(stderr,"Error: rawPrintThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }
  return;
}

int isEqualStringOnVoid(void *s, void *s2) {
  if (strcmp((char *) s, (char *) s2)) return 1; else return 0;
}

int isEqualThing(node *tree, node *tree2);

int isEqualThingOnVoid(void *tree, void *tree2) {
  return isEqualThing((node *) tree, (node *) tree2);
}

int isEqualThing(node *tree, node *tree2) {
  
  if (tree == NULL) return 0;
  if (tree2 == NULL) return 0;

  if (tree->nodeType != tree2->nodeType) return 0;

  switch (tree->nodeType) {
  case VARIABLE:
    break;
  case CONSTANT:
    if (mpfr_cmp(*(tree->value),*(tree2->value)) != 0) return 0;
    break;
  case ADD:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;
  case SUB:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;
  case MUL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;
  case DIV:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;
  case SQRT:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case EXP:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case LOG:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case LOG_2:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case LOG_10:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case SIN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case COS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case TAN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ASIN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ACOS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ATAN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case SINH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case COSH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case TANH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ASINH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ACOSH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ATANH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case POW:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;
  case NEG:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ABS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case DOUBLE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case DOUBLEDOUBLE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case TRIPLEDOUBLE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ERF: 
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case ERFC:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case LOG_1P:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case EXP_M1:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case DOUBLEEXTENDED:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case LIBRARYFUNCTION:
    if (tree->libFun != tree2->libFun) return 0;
    if (tree->libFunDeriv != tree2->libFunDeriv) return 0;
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case CEIL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case FLOOR:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case PI_CONST:
    break;
  case COMMANDLIST:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break;			
  case WHILE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;				
  case IFELSE:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 				
  case IF:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 				
  case FOR:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 				
  case FORIN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break;  				
  case QUIT:
    break;  				
  case FALSEQUIT:
    break; 			
  case RESTART:
    break;  			
  case PRINT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 				
  case NEWFILEPRINT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case APPENDFILEPRINT:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case PLOT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break;			
  case PRINTHEXA:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 
  case PRINTBINARY:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case PRINTEXPANSION:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;
  case BASHEXECUTE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case EXTERNALPLOT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 
  case WRITE:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case NEWFILEWRITE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break;
  case APPENDFILEWRITE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 
  case ASCIIPLOT:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;			
  case PRINTXML:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;			
  case PRINTXMLNEWFILE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;			
  case PRINTXMLAPPENDFILE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;			
  case WORSTCASE:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case RENAME:
    if (strcmp(tree->string,tree2->string) != 0) return 0;
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualStringOnVoid)) return 0;
    break; 				
  case AUTOPRINT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break;  			
  case ASSIGNMENT:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 			
  case LIBRARYBINDING:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break;  			
  case PRECASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case POINTSASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case DIAMASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;			
  case DISPLAYASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case VERBOSITYASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  		
  case CANONICALASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case AUTOSIMPLIFYASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  		
  case TAYLORRECURSASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case TIMINGASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case FULLPARENASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  		
  case MIDPOINTASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case HOPITALRECURSASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case PRECSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case POINTSSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case DIAMSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case DISPLAYSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  		
  case VERBOSITYSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case CANONICALSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case AUTOSIMPLIFYSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  	
  case TAYLORRECURSSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 	
  case TIMINGSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case FULLPARENSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  		
  case MIDPOINTSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 		
  case HOPITALRECURSSTILLASSIGN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  	
  case AND:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 				
  case OR:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;				
  case NEGATION:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case INDEX:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 				
  case COMPAREEQUAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case COMPARELESS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case COMPAREGREATER:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case COMPARELESSEQUAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 		
  case COMPAREGREATEREQUAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;		
  case COMPARENOTEQUAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;		
  case CONCAT:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case ADDTOLIST:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case ON:
    break; 				
  case OFF:
    break; 				
  case DYADIC:
    break;  				
  case POWERS:
    break; 				
  case BINARY:
    break; 			 	
  case FILESYM:
    break; 			 	
  case POSTSCRIPT:
    break;  			
  case POSTSCRIPTFILE:
    break; 			
  case PERTURB:
    break; 			
  case ROUNDDOWN:
    break; 			
  case ROUNDUP:
    break; 			
  case ROUNDTOZERO:
    break;  			
  case ROUNDTONEAREST:
    break; 			
  case HONORCOEFF:
    break; 			
  case TRUE:
    break; 			 	
  case FALSE:
    break; 			 	
  case DEFAULT:
    break; 			
  case DECIMAL:
    break; 			
  case ABSOLUTESYM:
    break; 			
  case RELATIVESYM:
    break; 			
  case ERRORSPECIAL:
    break; 			
  case DOUBLESYMBOL:
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    break;  			
  case DOUBLEDOUBLESYMBOL:
    break; 		
  case TRIPLEDOUBLESYMBOL:
    break; 		
  case STRING:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 			 	
  case TABLEACCESS:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break;  	
  case DECIMALCONSTANT:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 		
  case DYADICCONSTANT:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 			
  case HEXCONSTANT:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 			
  case BINARYCONSTANT:
    if (strcmp(tree->string,tree2->string) != 0) return 0;    break; 			
  case EMPTYLIST:
    break; 			
  case LIST:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			 	
  case FINALELLIPTICLIST:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 		
  case ELLIPTIC:
    break; 			
  case RANGE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			 	
  case DEBOUNDMAX:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  			
  case DEBOUNDMIN:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case DEBOUNDMID:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case DIFF:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case SIMPLIFY:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  			
  case SIMPLIFYSAFE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break;  			
  case REMEZ:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			 	
  case HORNER:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case CANONICAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case EXPAND:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case TAYLOR:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			 	
  case DEGREE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case NUMERATOR:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case DENOMINATOR:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			
  case SUBSTITUTE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;			
  case COEFF:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			 	
  case SUBPOLY:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case ROUNDCOEFFICIENTS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 		
  case RATIONALAPPROX:    
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case ACCURATEINFNORM:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 		
  case ROUNDTOFORMAT:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break;			
  case EVALUATE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case PARSE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case READXML:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case INFNORM:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case FINDZEROS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case FPFINDZEROS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case DIRTYINFNORM:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case INTEGRAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case DIRTYINTEGRAL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;  			
  case IMPLEMENTPOLY:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case CHECKINFNORM:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case ZERODENOMINATORS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break;  		
  case ISEVALUABLE:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case SEARCHGAL:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case GUESSDEGREE:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case ASSIGNMENTININDEXING:
    if (!isEqualChain(tree->arguments,tree2->arguments,isEqualThingOnVoid)) return 0;
    break; 			
  case DIRTYFINDZEROS:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    if (!isEqualThing(tree->child2,tree2->child2)) return 0;
    break; 			
  case HEAD:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case TAIL:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case LENGTH:
    if (!isEqualThing(tree->child1,tree2->child1)) return 0;
    break; 			 	
  case PRECDEREF:
    break; 			
  case POINTSDEREF:
    break; 			
  case DIAMDEREF:
    break; 			
  case DISPLAYDEREF:
    break; 			
  case VERBOSITYDEREF:
    break; 			
  case CANONICALDEREF:
    break; 			
  case AUTOSIMPLIFYDEREF:
    break; 		
  case TAYLORRECURSDEREF:
    break; 		
  case TIMINGDEREF:
    break; 			
  case FULLPARENDEREF:
    break; 			
  case MIDPOINTDEREF:
    break; 			
  case HOPITALRECURSDEREF:
    break;  	       
  default:
    fprintf(stderr,"Error: isEqualThing: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }

  return 1;
}


int isCorrectlyTypedBaseSymbol(node *tree) {

  if (tree == NULL) return 0;

  switch (tree->nodeType) {
  case ON:
  case OFF:
  case DYADIC:
  case POWERS:
  case BINARY:
  case FILESYM:
  case POSTSCRIPT:
  case POSTSCRIPTFILE:
  case PERTURB:
  case ROUNDDOWN:
  case ROUNDUP:
  case ROUNDTOZERO:
  case ROUNDTONEAREST:
  case HONORCOEFF:
  case TRUE:
  case FALSE:
  case DEFAULT:
  case DECIMAL:
  case ABSOLUTESYM:
  case RELATIVESYM:
  case DOUBLESYMBOL:
  case DOUBLEEXTENDEDSYMBOL:
  case DOUBLEDOUBLESYMBOL:
  case TRIPLEDOUBLESYMBOL:
  case STRING:
  case EMPTYLIST:
    return 1;
  default:
    return 0;
  }

  return 0;
}


int isCorrectlyTyped(node *tree) {
  chain *curr;
  

  if (isPureTree(tree)) return 1;
  if (isCorrectlyTypedBaseSymbol(tree)) return 1;
  if (isRange(tree)) return 1;
  if (isPureList(tree)) {
    curr = tree->arguments;
    while (curr != NULL) {
      if (!isCorrectlyTyped((node *) (curr->value))) return 0;
      curr = curr->next;
    }
    return 1;
  }
  if (isPureFinalEllipticList(tree)) {
    curr = tree->arguments;
    while (curr != NULL) {
      if (!isCorrectlyTyped((node *) (curr->value))) return 0;
      curr = curr->next;
    }
    return 1;
  }

  return 0;
}



node *evaluateThing(node *tree) {
  node *evaluated, *tempNode;

  evaluated = evaluateThingInner(tree);

  if (!isCorrectlyTyped(evaluated)) {
    if (evaluated->nodeType == ERRORSPECIAL) {
      if (tree->nodeType != ERRORSPECIAL) 
	printMessage(1,"Warning: the given expression could not be handled.\n");
    } else {
      printMessage(1,"Warning: at least one of the given expressions or a subexpression is not correctly typed.\n");
      if (verbosity >= 2) {
	printMessage(2,"Information: the expression or a partial evaluation of it has been the following:\n");
	printThing(evaluated);
	printf("\n");     
      }
    }

    freeThing(evaluated);
    evaluated = makeError();
  }

  if (autosimplify && isPureTree(evaluated)) {
    if (treeSize(evaluated) < MAXAUTOSIMPLSIZE) {
      tempNode = simplifyTreeErrorfree(evaluated);
      freeThing(evaluated);
      evaluated = tempNode;
    } else {
      printMessage(1,"Warning: the given expression is too big to be treated by the automatic simplification.\n");
    }
  } 

  return evaluated;
}

void *evaluateThingInnerOnVoid(void *tree) {
  return (void *) evaluateThingInner((node *) tree);
}

node *evaluateThingInner(node *tree) {
  node *copy, *tempNode, *tempNode2;
  int resA, resB, i, resC, resD, resE;
  char *tempString, *tempString2, *timingString, *tempString3;
  mpfr_t a, b, c;
  chain *tempChain, *curr, *newChain, *tempChain2, *tempChain3;
  rangetype yrange, xrange;
  node *firstArg, *secondArg, *thirdArg, *fourthArg, *fifthArg, *sixthArg, *seventhArg, *eighthArg;
  rangetype *rangeTempPtr;
  FILE *fd, *fd2;
  mpfr_t *tempMpfrPtr;

  if (tree == NULL) return NULL;

  timingString = NULL;
  if (timecounting) {
    timingString = getTimingStringForThing(tree);
  }

  copy = (node *) safeMalloc(sizeof(node));
  copy->nodeType = tree->nodeType;

  switch (tree->nodeType) {
  case VARIABLE:
    break;
  case CONSTANT:
    copy->value = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
    mpfr_init2(*(copy->value),mpfr_get_prec(*(tree->value)));
    mpfr_set(*(copy->value),*(tree->value),GMP_RNDN);
    break;
  case ADD:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    break;
  case SUB:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    break;
  case MUL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    break;
  case DIV:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    break;
  case SQRT:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case EXP:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case LOG:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case LOG_2:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case LOG_10:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case SIN:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case COS:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case TAN:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ASIN:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ACOS:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ATAN:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case SINH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case COSH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case TANH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ASINH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ACOSH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ATANH:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case POW:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    break;
  case NEG:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ABS:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case DOUBLE:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case DOUBLEDOUBLE:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case TRIPLEDOUBLE:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ERF: 
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case ERFC:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case LOG_1P:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case EXP_M1:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case DOUBLEEXTENDED:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case LIBRARYFUNCTION:
    copy->libFun = tree->libFun;
    copy->libFunDeriv = tree->libFunDeriv;
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case CEIL:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case FLOOR:
    copy->child1 = evaluateThingInner(tree->child1);
    break;
  case PI_CONST:
    break;
  case AND:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isBoolean(copy->child1) && isBoolean(copy->child2)) {
      if ((copy->child1->nodeType == TRUE) && 
	  (copy->child2->nodeType == TRUE)) {
	copy->nodeType = TRUE;
      } else {
	copy->nodeType = FALSE;
      }
      freeThing(copy->child1);
      freeThing(copy->child2);
    }
    break; 				
  case OR:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isBoolean(copy->child1) && isBoolean(copy->child2)) {
      if ((copy->child1->nodeType == FALSE) && 
	  (copy->child2->nodeType == FALSE)) {
	copy->nodeType = FALSE;
      } else {
	copy->nodeType = TRUE;
      }
      freeThing(copy->child1);
      freeThing(copy->child2);
    }
    break;				
  case NEGATION:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isBoolean(copy->child1)) {
      if (copy->child1->nodeType == FALSE) {
	copy->nodeType = TRUE;
      } else {
	copy->nodeType = FALSE;
      }
      freeThing(copy->child1);
    }
    break; 			
  case INDEX:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isString(copy->child1) || isPureList(copy->child1)) {
      if (evaluateThingToInteger(&resA,copy->child2,NULL)) {
	if (isString(copy->child1)) {
	  if ((resA >= 0) && (resA < strlen(copy->child1->string))) {
	    if (timingString != NULL) pushTimeCounter();
	    tempString = (char *) safeCalloc(2,sizeof(char));
	    tempString[0] = (copy->child1->string)[resA];
	    copy->nodeType = STRING;
	    copy->string = tempString;
	    freeThing(copy->child1);
	    freeThing(copy->child2);
	    if (timingString != NULL) popTimeCounter(timingString);
	  }
	} else {
	  if (isPureList(copy->child1)) {
	    if ((resA >= 0) && (resA < lengthChain(copy->child1->arguments))) {
	      if (timingString != NULL) pushTimeCounter();
	      tempNode = copyThing((node *) accessInList(copy->child1->arguments, resA));
	      freeThing(copy);
	      copy = tempNode;
	      if (timingString != NULL) popTimeCounter(timingString);
	    }
	  }
	}
      }
    }
    break; 				
  case COMPAREEQUAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (timingString != NULL) pushTimeCounter();
    if (isEqualThing(copy->child1,copy->child2)) {
      if (!isError(copy->child1)) {
	freeThing(copy);
	copy = makeTrue();
      } else {
	freeThing(copy);
	copy = makeFalse();
      }
    } else {
      if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
	printMessage(2,"Information: equality test relies on floating-point result.\n");
	mpfr_init2(a,tools_precision);
	mpfr_init2(b,tools_precision);
	if (evaluateThingToConstant(a,copy->child1,NULL) && 
	    evaluateThingToConstant(b,copy->child2,NULL)) {
	  if (mpfr_cmp(a,b) == 0) {
	    freeThing(copy);
	    copy = makeTrue();		    
	  } else {
	    freeThing(copy);
	    copy = makeFalse();		    
	  }
	} else {
	  freeThing(copy);
	  copy = makeFalse();		    
	}
	mpfr_clear(a);
	mpfr_clear(b);
      } else {
	freeThing(copy);
	copy = makeFalse();
      }
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case COMPARELESS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL) && 
	  evaluateThingToConstant(b,copy->child2,NULL)) {
	printMessage(2,"Information: inequality test relies on floating-point result.\n");
	if (mpfr_cmp(a,b) < 0) {
	  freeThing(copy);
	  copy = makeTrue();		    
	} else {
	  freeThing(copy);
	  copy = makeFalse();		    
	}
      }
      mpfr_clear(a);
      mpfr_clear(b);
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			
  case COMPAREGREATER:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL) && 
	  evaluateThingToConstant(b,copy->child2,NULL)) {
	printMessage(2,"Information: inequality test relies on floating-point result.\n");
	if (mpfr_cmp(a,b) > 0) {
	  freeThing(copy);
	  copy = makeTrue();		    
	} else {
	  freeThing(copy);
	  copy = makeFalse();		    
	}
      }
      mpfr_clear(a);
      mpfr_clear(b);
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			
  case COMPARELESSEQUAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL) && 
	  evaluateThingToConstant(b,copy->child2,NULL)) {
	printMessage(2,"Information: inequality test relies on floating-point result.\n");
	if (mpfr_cmp(a,b) <= 0) {
	  freeThing(copy);
	  copy = makeTrue();		    
	} else {
	  freeThing(copy);
	  copy = makeFalse();		    
	}
      }
      mpfr_clear(a);
      mpfr_clear(b);
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 		
  case COMPAREGREATEREQUAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL) && 
	  evaluateThingToConstant(b,copy->child2,NULL)) {
	printMessage(2,"Information: inequality test relies on floating-point result.\n");
	if (mpfr_cmp(a,b) >= 0) {
	  freeThing(copy);
	  copy = makeTrue();		    
	} else {
	  freeThing(copy);
	  copy = makeFalse();		    
	}
      }
      mpfr_clear(a);
      mpfr_clear(b);
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break;		
  case COMPARENOTEQUAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (timingString != NULL) pushTimeCounter();
    if (isEqualThing(copy->child1,copy->child2)) {
      if (!isError(copy->child1)) {
	freeThing(copy);
	copy = makeFalse();
      } else {
	freeThing(copy);
	copy = makeFalse();
      }
    } else {
      if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
	printMessage(2,"Information: equality test relies on floating-point result.\n");
	mpfr_init2(a,tools_precision);
	mpfr_init2(b,tools_precision);
	if (evaluateThingToConstant(a,copy->child1,NULL) && 
	    evaluateThingToConstant(b,copy->child2,NULL)) {
	  if (mpfr_cmp(a,b) == 0) {
	    freeThing(copy);
	    copy = makeFalse();		    
	  } else {
	    freeThing(copy);
	    copy = makeTrue();		    
	  }
	} else {
	  freeThing(copy);
	  copy = makeTrue();		    
	}
	mpfr_clear(a);
	mpfr_clear(b);
      } else {
	freeThing(copy);
	copy = makeTrue();
      }
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break;		
  case CONCAT:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isString(copy->child1) && isString(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      tempString = (char *) safeCalloc(strlen(copy->child1->string) + strlen(copy->child2->string) + 1, sizeof(char));
      sprintf(tempString,"%s%s",copy->child1->string,copy->child2->string);
      freeThing(copy->child1);
      freeThing(copy->child2);
      copy->nodeType = STRING;
      copy->string = tempString;
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isString(copy->child1) && isPureTree(copy->child2)) {
	if (isConstant(copy->child2)) {
	  if (timingString != NULL) pushTimeCounter();
	  mpfr_init2(a,tools_precision);
	  if (evaluateThingToConstant(a, copy->child2, NULL)) {	  
	    tempString2 = sprintValue(&a, tools_precision);
	    tempString = (char *) safeCalloc(strlen(copy->child1->string) + strlen(tempString2) + 1, sizeof(char));
	    sprintf(tempString,"%s%s",copy->child1->string,tempString2);
	    freeThing(copy->child1);
	    freeThing(copy->child2);
	    copy->nodeType = STRING;
	    copy->string = tempString;
	    free(tempString2);
	  }
	  mpfr_clear(a);
	  if (timingString != NULL) popTimeCounter(timingString);
	} else {
	  if (timingString != NULL) pushTimeCounter();
	  tempString2 = sprintTree(copy->child2);
	  tempString = (char *) safeCalloc(strlen(copy->child1->string) + strlen(tempString2) + 1, sizeof(char));
	  sprintf(tempString,"%s%s",copy->child1->string,tempString2);
	  freeThing(copy->child1);
	  freeThing(copy->child2);
	  copy->nodeType = STRING;
	  copy->string = tempString;
	  free(tempString2);
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      } else {
	if (isString(copy->child2) && isPureTree(copy->child1)) {
	  if (isConstant(copy->child1)) {
	    if (timingString != NULL) pushTimeCounter();
	    mpfr_init2(a,tools_precision);
	    if (evaluateThingToConstant(a, copy->child1, NULL)) {	  
	      tempString2 = sprintValue(&a, tools_precision);
	      tempString = (char *) safeCalloc(strlen(copy->child2->string) + strlen(tempString2) + 1, sizeof(char));
	      sprintf(tempString,"%s%s",copy->child2->string,tempString2);
	      freeThing(copy->child1);
	      freeThing(copy->child2);
	      copy->nodeType = STRING;
	      copy->string = tempString;
	      free(tempString2);
	    }
	    mpfr_clear(a);
	    if (timingString != NULL) popTimeCounter(timingString);
	  } else {
	    if (timingString != NULL) pushTimeCounter();
	    tempString2 = sprintTree(copy->child1);
	    tempString = (char *) safeCalloc(strlen(copy->child2->string) + strlen(tempString2) + 1, sizeof(char));
	    sprintf(tempString,"%s%s",copy->child2->string,tempString2);
	    freeThing(copy->child1);
	    freeThing(copy->child2);
	    copy->nodeType = STRING;
	    copy->string = tempString;
	    free(tempString2);
	    if (timingString != NULL) popTimeCounter(timingString);
	  }
	} else {
	  if (isEmptyList(copy->child1) && isEmptyList(copy->child2)) {
	    freeThing(copy->child1);
	    freeThing(copy->child2);
	    copy->nodeType = EMPTYLIST;
	  } else {
	    if (isEmptyList(copy->child1) && (isList(copy->child2) || isFinalEllipticList(copy->child2))) {
	      copy->nodeType = copy->child2->nodeType;
	      copy->arguments = copy->child2->arguments;
	      freeThing(copy->child1);
	      free(copy->child2);
	    } else {
	      if (isEmptyList(copy->child2) && isList(copy->child1)) {
		if (timingString != NULL) pushTimeCounter();
		copy->nodeType = LIST;
		copy->arguments = copy->child1->arguments;
		freeThing(copy->child2);
		free(copy->child1);
		if (timingString != NULL) popTimeCounter(timingString);
	      } else {
		if (isList(copy->child1) && isList(copy->child2)) {
		  if (timingString != NULL) pushTimeCounter();
		  copy->nodeType = LIST;
		  copy->arguments = concatChains(copy->child1->arguments, copy->child2->arguments);
		  free(copy->child1);
		  free(copy->child2);
		  if (timingString != NULL) popTimeCounter(timingString);
		} else {
		  if (isList(copy->child1) && isFinalEllipticList(copy->child2)) {
		    if (timingString != NULL) pushTimeCounter();
		    copy->nodeType = FINALELLIPTICLIST;
		    copy->arguments = concatChains(copy->child1->arguments, copy->child2->arguments);
		    free(copy->child1);
		    free(copy->child2);
		    if (timingString != NULL) popTimeCounter(timingString);
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    break; 			
  case ADDTOLIST:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isList(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      copy->nodeType = LIST;
      copy->arguments = addElement(copy->child2->arguments,copy->child1);
      free(copy->child2);
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isEmptyList(copy->child2)) {
	if (timingString != NULL) pushTimeCounter();
	copy->nodeType = LIST;
	copy->arguments = addElement(NULL, copy->child1);
	freeThing(copy->child2);
	if (timingString != NULL) popTimeCounter(timingString);
      } else {
	if (isFinalEllipticList(copy->child2)) {
	  if (timingString != NULL) pushTimeCounter();
	  copy->nodeType = FINALELLIPTICLIST;
	  copy->arguments = addElement(copy->child2->arguments,copy->child1);
	  free(copy->child2);
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      }
    }
    break; 			
  case ON:
    break; 				
  case OFF:
    break; 				
  case DYADIC:
    break;  				
  case POWERS:
    break; 				
  case BINARY:
    break; 			 	
  case FILESYM:
    break; 			 	
  case POSTSCRIPT:
    break;  			
  case POSTSCRIPTFILE:
    break; 			
  case PERTURB:
    break; 			
  case ROUNDDOWN:
    break; 			
  case ROUNDUP:
    break; 			
  case ROUNDTOZERO:
    break;  			
  case ROUNDTONEAREST:
    break; 			
  case HONORCOEFF:
    break; 			
  case TRUE:
    break; 			 	
  case FALSE:
    break; 			 	
  case DEFAULT:
    break; 			
  case DECIMAL:
    break; 			
  case ABSOLUTESYM:
    break; 			
  case RELATIVESYM:
    break; 			
  case ERRORSPECIAL:
    break; 			
  case DOUBLESYMBOL:
    break;  			
  case DOUBLEEXTENDEDSYMBOL:
    break;  			
  case DOUBLEDOUBLESYMBOL:
    break; 		
  case TRIPLEDOUBLESYMBOL:
    break; 		
  case STRING:
    copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
    strcpy(copy->string,tree->string);
    break; 			 	
  case TABLEACCESS:
    if (timingString != NULL) pushTimeCounter();
    if ((tempNode = getThingFromTable(tree->string)) == NULL) {
      if (variablename == NULL) {
	variablename = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
	strcpy(variablename, tree->string);
      } else {
	printMessage(1,"Warning: the identifier \"%s\" is neither assigned to, nor bound to a library function nor equal to the current free variable.\n",tree->string);
	printMessage(1,"Will interpret \"%s\" as \"%s\".\n",tree->string,variablename);
      }
      tempNode = makeVariable();
    }
    free(copy);
    copy = tempNode;
    if (timingString != NULL) popTimeCounter(timingString);
    break;  			
  case TABLEACCESSWITHSUBSTITUTE:
    if (timingString != NULL) pushTimeCounter();
    if ((tempNode = getThingFromTable(tree->string)) == NULL) {
      if (variablename == NULL) {
	variablename = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
	strcpy(variablename, tree->string);
      } else {
	printMessage(1,"Warning: the identifier \"%s\" is neither assigned to, nor bound to a library function nor equal to the current free variable.\n",tree->string);
	printMessage(1,"Will interpret \"%s\" as \"%s\".\n",tree->string,variablename);
      }
      tempNode = makeVariable();
    }
    if (isPureTree(tempNode)) {
      if (evaluateThingToPureTree(&tempNode2,tree->child1)) {
	free(copy);
	if (tempNode->nodeType == VARIABLE) {
	  printMessage(1,"Warning: the identifier \"%s\" is bound to the current free variable. In a functional context it will be considered as the identity function.\n",
		       variablename);
	}
	copy = substitute(tempNode, tempNode2);
	freeThing(tempNode2);
      } else {
	copy->child1 = copyThing(tree->child1);
	copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
	strcpy(copy->string,tree->string);
      }
    } else {
      copy->child1 = copyThing(tree->child1);
      copy->string = (char *) safeCalloc(strlen(tree->string)+1,sizeof(char));
      strcpy(copy->string,tree->string);
    }
    freeThing(tempNode);
    if (timingString != NULL) popTimeCounter(timingString);
    break;  	
  case DECIMALCONSTANT:
    if (timingString != NULL) pushTimeCounter();
    mpfr_init2(a,tools_precision);
    mpfr_init2(b,tools_precision);
    mpfr_set_str(a,tree->string,10,GMP_RNDD);
    mpfr_set_str(b,tree->string,10,GMP_RNDU);    
    if (mpfr_cmp(a,b) != 0) {
      printMessage(1,
		   "Warning: Rounding occured when converting the constant \"%s\" to floating-point with %d bits.\n",
		   tree->string,(int) tools_precision);
      printMessage(1,"If safe computation is needed, try to increase the precision.\n");
      mpfr_set_str(a,tree->string,10,GMP_RNDN);
    }
    tempNode = makeConstant(a);
    mpfr_clear(b);
    mpfr_clear(a);
    free(copy);
    copy = tempNode;
    if (timingString != NULL) popTimeCounter(timingString);
    break; 		
  case DYADICCONSTANT:
    if (timingString != NULL) pushTimeCounter();
    mpfr_init2(a,tools_precision);
    if (!readDyadic(a,tree->string)) {
      printMessage(1,
		   "Warning: Rounding occured when converting the dyadic constant \"%s\" to floating-point with %d bits.\n",
		   tree->string,(int) tools_precision);
      printMessage(1,"If safe computation is needed, try to increase the precision.\n");
    }
    tempNode = makeConstant(a);
    mpfr_clear(a);
    free(copy);
    copy = tempNode;
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case HEXCONSTANT:
    if (timingString != NULL) pushTimeCounter();
    mpfr_init2(a,tools_precision);
    if (!readHexa(a,tree->string)) {
      printMessage(1,
		   "Warning: Rounding occured when converting the hexadecimal constant \"%s\" to floating-point with %d bits.\n",
		   tree->string,(int) tools_precision);
      printMessage(1,"If safe computation is needed, try to increase the precision.\n");
    }
    tempNode = makeConstant(a);
    mpfr_clear(a);
    free(copy);
    copy = tempNode;
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case BINARYCONSTANT:
    if (timingString != NULL) pushTimeCounter();
    mpfr_init2(a,tools_precision);
    mpfr_init2(b,tools_precision);
    mpfr_set_str(a,tree->string,2,GMP_RNDD);
    mpfr_set_str(b,tree->string,2,GMP_RNDU);    
    if (mpfr_cmp(a,b) != 0) {
      printMessage(1,
		   "Warning: Rounding occured when converting the binary constant \"%s_2\" to floating-point with %d bits.\n",
		   tree->string,(int) tools_precision);
      printMessage(1,"If safe computation is needed, try to increase the precision.\n");
      mpfr_set_str(a,tree->string,2,GMP_RNDN);
    }
    tempNode = makeConstant(a);
    mpfr_clear(b);
    mpfr_clear(a);
    free(copy);
    copy = tempNode;
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case EMPTYLIST:
    break; 			
  case LIST:
    tempChain = copyChain(tree->arguments, evaluateThingInnerOnVoid);
    if (timingString != NULL) pushTimeCounter();
    curr = tempChain; newChain = NULL; resC = 0;
    while (curr != NULL) {
      if ((curr->next != NULL) &&
	  (curr->next->next != NULL) &&
	  isElliptic((node *) (curr->next->value)) &&
	  isPureTree((node *) (curr->value)) &&
	  isPureTree((node *) (curr->next->next->value)) &&
	  isConstant((node *) (curr->value)) &&
	  isConstant((node *) (curr->next->next->value)) &&
	  evaluateThingToInteger(&resA,(node *) (curr->value), NULL) &&
	  evaluateThingToInteger(&resB,(node *) (curr->next->next->value),NULL) &&
	  (resA >= resB)) {
	mpfr_init2(a,sizeof(int) * 8);
	resC = 1;
	for (i=resA;i>=resB;i--) {
	  mpfr_set_si(a,i,GMP_RNDN);
	  newChain = addElement(newChain,makeConstant(a));
	}
	mpfr_clear(a);
	curr = curr->next->next;
      } else {
	newChain = addElement(newChain,copyThing((node *) (curr->value)));
      }
      curr = curr->next;
    }
    copy->arguments = newChain;
    if (resC && (!isPureList(copy))) {
      tempNode = evaluateThing(copy);
      freeThing(copy);
      copy = tempNode;
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			 	
  case FINALELLIPTICLIST:
    tempChain = copyChain(tree->arguments, evaluateThingInnerOnVoid);
    if (timingString != NULL) pushTimeCounter();
    curr = tempChain; newChain = NULL; resC = 0;
    while (curr != NULL) {
      if ((curr->next != NULL) &&
	  (curr->next->next != NULL) &&
	  isElliptic((node *) (curr->next->value)) &&
	  isPureTree((node *) (curr->value)) &&
	  isPureTree((node *) (curr->next->next->value)) &&
	  isConstant((node *) (curr->value)) &&
	  isConstant((node *) (curr->next->next->value)) &&
	  evaluateThingToInteger(&resA,(node *) (curr->value), NULL) &&
	  evaluateThingToInteger(&resB,(node *) (curr->next->next->value),NULL) &&
	  (resA >= resB)) {
	mpfr_init2(a,sizeof(int) * 8);
	resC = 1;
	for (i=resA;i>=resB;i--) {
	  mpfr_set_si(a,i,GMP_RNDN);
	  newChain = addElement(newChain,makeConstant(a));
	}
	mpfr_clear(a);
	curr = curr->next->next;
      } else {
	newChain = addElement(newChain,copyThing((node *) (curr->value)));
      }
      curr = curr->next;
    }
    copy->arguments = newChain;
    if (resC && (!isPureFinalEllipticList(copy))) {
      tempNode = evaluateThing(copy);
      freeThing(copy);
      copy = tempNode;
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 		
  case ELLIPTIC:
    break; 			
  case RANGE:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();
      mpfr_init2(a,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL)) {
	mpfr_init2(b,tools_precision);
	if (evaluateThingToConstant(b,copy->child2,NULL)) {
	  freeThing(copy->child1);
	  freeThing(copy->child2);
	  if (mpfr_cmp(a,b) > 0) {
	    printMessage(1,"Warning: the bounds of the given range are in wrong order. Will reverse them.\n");
	    copy->child1 = makeConstant(b);
	    copy->child2 = makeConstant(a);
	  } else {
	    copy->child1 = makeConstant(a);
	    copy->child2 = makeConstant(b);
	  }
	}      
	mpfr_clear(b);
      } 
      mpfr_clear(a);
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case DEBOUNDMAX:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isRange(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();
      tempNode = copyThing(copy->child1->child2);
      freeThing(copy);
      copy = tempNode;
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isPureTree(copy->child1)) {
	tempNode = copyThing(copy->child1);
	freeThing(copy);
	copy = tempNode;
      }
    }
    break;  			
  case DEBOUNDMIN:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isRange(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();
      tempNode = copyThing(copy->child1->child1);
      freeThing(copy);
      copy = tempNode;
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isPureTree(copy->child1)) {
	tempNode = copyThing(copy->child1);
	freeThing(copy);
	copy = tempNode;
      }
    }
    break; 			
  case DEBOUNDMID:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isRange(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();
      tempNode = makeDiv(makeAdd(copyThing(copy->child1->child1),copyThing(copy->child1->child2)),makeConstantDouble(2.0));
      freeThing(copy);
      copy = tempNode;
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isPureTree(copy->child1)) {
	tempNode = copyThing(copy->child1);
	freeThing(copy);
	copy = tempNode;
      }
    }
    break; 			
  case DIFF:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = differentiate(copy->child1);
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case SIMPLIFY:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (isConstant(copy->child1)) {
	mpfr_init2(a,tools_precision);
	mpfr_init2(b,tools_precision);
	mpfr_set_d(a,1.0,GMP_RNDN);
	if (timingString != NULL) pushTimeCounter();      
	if (evaluateFaithful(b, copy->child1, a, tools_precision)) {
	  tempNode = makeConstant(b);
	  freeThing(copy);
	  copy = tempNode;
	} else {
	  printMessage(2,"Information: the given tree is constant but cannot be evaluated faithfully.\n");
	  tempNode = simplifyTree(copy->child1);
	  freeThing(copy);
	  copy = tempNode; 
	}
	if (timingString != NULL) popTimeCounter(timingString);
	mpfr_clear(a);
	mpfr_clear(b);
      } else {
	if (timingString != NULL) pushTimeCounter();      
	tempNode = simplifyTree(copy->child1);
	freeThing(copy);
	copy = tempNode; 
	if (timingString != NULL) popTimeCounter(timingString);
      }
    }
    break;  			
  case SIMPLIFYSAFE:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = simplifyTreeErrorfree(copy->child1);
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break;  			
  case REMEZ:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = copyThing((node *) (curr->value));
    curr = curr->next;
    secondArg = copyThing((node *) (curr->value));
    curr = curr->next;
    thirdArg = copyThing((node *) (curr->value));
    curr = curr->next;
    fifthArg = NULL;
    if (curr != NULL) {
      fourthArg = copyThing((node *) (curr->value));
      curr = curr->next;
      if (curr != NULL) {
	fifthArg = copyThing((node *) (curr->value));
      } 
    } else {
      fourthArg = makeConstantDouble(1.0);
    }    
    if (isPureTree(firstArg) && isRange(thirdArg) && (isPureTree(fourthArg) || isDefault(fourthArg)) && ((fifthArg == NULL) || isPureTree(fifthArg))) {
      if (isPureTree(secondArg) || isPureList(secondArg)) {
	resB = 0;
	if (isPureTree(secondArg)) {
	  if (evaluateThingToInteger(&resA,secondArg,NULL)) {
	    resB = 1;
	    tempChain = makeIntPtrChainFromTo(0, resA);
	  }
	} else {
	  if (evaluateThingToIntegerList(&tempChain, NULL, secondArg)) {	  
	    resB = 1;
	  }
	}
	if (resB) {
	  if (isDefault(fourthArg)) {
	    freeThing(fourthArg);
	    fourthArg = makeConstantDouble(1.0);
	  }
	  mpfr_init2(a,tools_precision);
	  mpfr_init2(b,tools_precision);
	  if (evaluateThingToRange(a,b,thirdArg)) {
	    tempMpfrPtr = NULL;
	    if (fifthArg != NULL) {
	      tempMpfrPtr = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	      mpfr_init2(*tempMpfrPtr,tools_precision);
	      if (!evaluateThingToConstant(*tempMpfrPtr,fifthArg,NULL)) {
		printMessage(1,"Warning: the given argument cannot be evaluated to a constant. It will be ignored.\n");
		mpfr_clear(*tempMpfrPtr);
		free(tempMpfrPtr);
		tempMpfrPtr = NULL;
	      }
	    }
	    if (timingString != NULL) pushTimeCounter(); 
	    tempNode = remez(firstArg, fourthArg, tempChain, a, b, tempMpfrPtr, tools_precision);
	    if (timingString != NULL) popTimeCounter(timingString);
	    freeThing(copy);
	    copy = tempNode;
	    if (tempMpfrPtr != NULL) {
	      mpfr_clear(*tempMpfrPtr);
	      free(tempMpfrPtr);
	    }
	  }
	  mpfr_clear(a); 
	  mpfr_clear(b); 
	  freeChain(tempChain,freeIntPtr);
	}
      }
    }
    freeThing(firstArg);
    freeThing(secondArg);
    freeThing(thirdArg);
    freeThing(fourthArg);
    if (fifthArg != NULL) freeThing(fifthArg);
    break; 			 	
  case HORNER:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = horner(copy->child1);
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case CANONICAL:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = makeCanonical(copy->child1, tools_precision);
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			
  case EXPAND:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = expand(copy->child1);
      freeThing(copy);
      copy = tempNode;
      if (timingString != NULL) popTimeCounter(timingString); 
    }
    break; 			 	
  case TAYLOR:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    if (isPureTree((node *) (curr->value))) {
      curr = curr->next;
      if (isPureTree((node *) (curr->value)) &&
	  evaluateThingToInteger(&resA,(node *) (curr->value),NULL)) {
	curr = curr->next;
	mpfr_init2(a,tools_precision);
	if (isPureTree((node *) (curr->value)) &&
	    evaluateThingToConstant(a,(node *) (curr->value),NULL)) {
	  if (timingString != NULL) pushTimeCounter();      
	  tempNode = makeConstant(a);
	  curr = copy->arguments;
	  tempNode2 = taylor((node *) (curr->value), resA, tempNode, tools_precision);
	  freeThing(tempNode);
	  freeThing(copy);
	  copy = tempNode2;
	  if (timingString != NULL) popTimeCounter(timingString);
	} 
	mpfr_clear(a);
      }
    }
    break; 			 	
  case DEGREE:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      resA = getDegree(copy->child1);
      mpfr_init2(a,sizeof(int) * 8);
      mpfr_set_si(a,resA,GMP_RNDN);
      tempNode = makeConstant(a);
      mpfr_clear(a);
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case NUMERATOR:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      if (!getNumeratorDenominator(&tempNode,&tempNode2,copy->child1)) {
	printMessage(1,"Warning: the expression given is not a fraction. ");
	printMessage(1,"Will consider it as a fraction with denominator 1.\n");
      } else {
	freeThing(tempNode2);
      }
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			
  case DENOMINATOR:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isPureTree(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      if (!getNumeratorDenominator(&tempNode2,&tempNode,copy->child1)) {
	printMessage(1,"Warning: the expression given is not a fraction. ");
	printMessage(1,"Will consider it as a fraction with denominator 1.\n");
	tempNode = makeConstantDouble(1.0);
      } else {
	freeThing(tempNode2);
      }
      freeThing(copy);
      copy = tempNode; 
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			
  case SUBSTITUTE:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (timingString != NULL) pushTimeCounter();      
      tempNode = substitute(copy->child1,copy->child2);
      freeThing(copy);
      copy = tempNode;
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break;			
  case COEFF:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      if (evaluateThingToInteger(&resA,copy->child2,NULL)) {
	if (timingString != NULL) pushTimeCounter();      
	tempNode = getIthCoefficient(copy->child1, resA);
	freeThing(copy);
	copy = tempNode;
	if (timingString != NULL) popTimeCounter(timingString);
      }
    }
    break; 			 	
  case SUBPOLY:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && 
	(isPureList(copy->child2) || isPureFinalEllipticList(copy->child2))) {
      if (evaluateThingToIntegerList(&tempChain, &resA, copy->child2)) {
	if (timingString != NULL) pushTimeCounter();      
	tempNode = getSubpolynomial(copy->child1, tempChain, resA, tools_precision);
	freeThing(copy);
	copy = tempNode;
	freeChain(tempChain,freeIntPtr);
	if (timingString != NULL) popTimeCounter(timingString);
      }
    }
    break; 			
  case ROUNDCOEFFICIENTS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	(isPureList(copy->child2) || isPureFinalEllipticList(copy->child2))) {
      if (evaluateThingToExpansionFormatList(&tempChain, copy->child2)) {
	if (timingString != NULL) pushTimeCounter();      
	tempNode = roundPolynomialCoefficients(copy->child1, tempChain, tools_precision);
	freeThing(copy);
	copy = tempNode;
	freeChain(tempChain,freeIntPtr);
	if (timingString != NULL) popTimeCounter(timingString);
      }
    }
    break; 		
  case RATIONALAPPROX:    
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) && isPureTree(copy->child2)) {
      mpfr_init2(a,tools_precision);
      if (evaluateThingToConstant(a,copy->child1,NULL)) {
	if (evaluateThingToInteger(&resA,copy->child2,NULL)) {
	  if (timingString != NULL) pushTimeCounter();      
	  tempNode = rationalApprox(a,resA);
	  freeThing(copy);
	  copy = tempNode;
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      }
      mpfr_clear(a);
    }
    break; 			
  case ACCURATEINFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = (node *) (curr->value);
    curr = curr->next;
    secondArg = (node *) (curr->value);
    curr = curr->next;
    thirdArg = (node *) (curr->value);
    curr = curr->next;
    resA = 1;
    tempChain = NULL;
    if (curr != NULL) {
      if (isPureList((node *) (curr->value))) {
	tempChain = ((node *) (curr->value))->arguments;
	curr = tempChain;
	while (curr != NULL) {
	  if (!isRange((node *) (curr->value))) {
	    resA = 0;
	    break;
	  }
	  curr = curr->next;
	}
      } else {
	resA = 0;
      }
    }
    if (isPureTree(firstArg) &&
	isRange(secondArg) &&
	isPureTree(thirdArg) &&
	resA
	) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,secondArg)) {
	resB = tools_precision >> 1;
	if (evaluateThingToInteger(&resA,thirdArg,&resB)) {
	  if (resA > 2) {
	    mpfr_init2(c,(mp_prec_t) resA);
	    newChain = NULL;
	    if (tempChain != NULL) {
	      curr = tempChain;
	      while (curr != NULL) {
		rangeTempPtr = (rangetype *) safeMalloc(sizeof(rangetype));
		rangeTempPtr->a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
		rangeTempPtr->b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
		mpfr_init2(*(rangeTempPtr->a),tools_precision);
		mpfr_init2(*(rangeTempPtr->b),tools_precision);
		evaluateThingToRange(*(rangeTempPtr->a),*(rangeTempPtr->b),(node *) (curr->value));
		newChain = addElement(newChain, rangeTempPtr);
		curr = curr->next;
	      }
	    }
	    xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*(xrange.a),tools_precision);
	    mpfr_init2(*(xrange.b),tools_precision);
	    mpfr_set(*(xrange.a),a,GMP_RNDN);
	    mpfr_set(*(xrange.b),b,GMP_RNDN);
	    if (timingString != NULL) pushTimeCounter();      
	    resB = accurateInfnorm(c, firstArg, xrange, newChain, tools_precision);
	    if (timingString != NULL) popTimeCounter(timingString);     
	    if (!resB) {
	      mpfr_set_nan(c);
	    }
	    mpfr_clear(*(xrange.a));
	    mpfr_clear(*(xrange.b));
	    free(xrange.a);
	    free(xrange.b);
	    if (newChain != NULL) freeChain(newChain,freeRangetypePtr);
	    tempNode = makeConstant(c);
	    freeThing(copy);
	    copy = tempNode;
	    mpfr_clear(c);
	  }
	}
      }
      mpfr_clear(a);
      mpfr_clear(b);
    } 
    break; 		
  case ROUNDTOFORMAT:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    if (isPureTree((node *) (curr->value))) {
      curr = curr->next;
      if (isPureTree((node *) (curr->value)) || isDefault((node *) (curr->value))) {
	curr = curr->next;
	if (isRoundingSymbol((node *) (curr->value)) || isDefault((node *) (curr->value))) {
	  curr = copy->arguments;
	  mpfr_init2(a,tools_precision);
	  if (evaluateThingToConstant(a,(node *) (curr->value),NULL)) {
	    curr = curr->next;
	    resB = tools_precision;
	    if (evaluateThingToInteger(&resA,(node *) (curr->value),&resB) &&
		(resA > 0)) {
	      curr = curr->next;
	      resD = GMP_RNDN;
	      if (evaluateThingToRoundingSymbol(&resC,(node *) (curr->value),&resD)) {		
		if (timingString != NULL) pushTimeCounter();      
		mpfr_init2(b,tools_precision);
		resE = round_to_format(b, a, resA, resC);
		if (verbosity >= 2) {
		  if (resE == 0) {
		    printMessage(2,"Information: no rounding has happened.\n");
		  } else {
		    if (resE < 0) {
		      printMessage(2,"Information: rounding down has happened.\n");
		    } else {
		      printMessage(2,"Information: rounding up has happened.\n");
		    }
		  }
		}
		tempNode = makeConstant(b);
		mpfr_clear(b);
		freeThing(copy);
		copy = tempNode;
		if (timingString != NULL) popTimeCounter(timingString);
	      }
	    }
	  }
	  mpfr_clear(a);
	}
      }
    }
    break;			
  case EVALUATE:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1)) {
      if (isPureTree(copy->child2)) {
	mpfr_init2(a,tools_precision);
	if (evaluateThingToConstant(a,copy->child2,NULL)) {
	  mpfr_init2(b,tools_precision);
	  if (timingString != NULL) pushTimeCounter();      
	  if (evaluateFaithful(b, copy->child1, a, tools_precision)) {
	    freeThing(copy);
	    copy = makeConstant(b);
	  } else {
	    xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	    mpfr_init2(*(xrange.a),tools_precision);
	    mpfr_init2(*(xrange.b),tools_precision);
	    mpfr_init2(*(yrange.a),tools_precision);
	    mpfr_init2(*(yrange.b),tools_precision);
	    mpfr_set(*(xrange.a),a,GMP_RNDD);
	    mpfr_set(*(xrange.b),a,GMP_RNDU);
	    evaluateRangeFunction(yrange, copy->child1, xrange, tools_precision * 256);
	    freeThing(copy);
	    copy = makeRange(makeConstant(*(yrange.a)),makeConstant(*(yrange.b)));
	    mpfr_clear(*(xrange.a));
	    mpfr_clear(*(xrange.b));
	    mpfr_clear(*(yrange.a));
	    mpfr_clear(*(yrange.b));
	    free(xrange.a);
	    free(xrange.b);
	    free(yrange.a);
	    free(yrange.b);
	  }
	  if (timingString != NULL) popTimeCounter(timingString);
	  mpfr_clear(b);
	}
	mpfr_clear(a);
      } else {
	if (isRange(copy->child2)) {
	  if (timingString != NULL) pushTimeCounter();      
	  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  yrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  yrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(xrange.a),tools_precision);
	  mpfr_init2(*(xrange.b),tools_precision);
	  mpfr_init2(*(yrange.a),tools_precision);
	  mpfr_init2(*(yrange.b),tools_precision);
	  mpfr_set(*(xrange.a),*(copy->child2->child1->value),GMP_RNDD);
	  mpfr_set(*(xrange.b),*(copy->child2->child2->value),GMP_RNDU);
	  evaluateRangeFunction(yrange, copy->child1, xrange, tools_precision);
	  freeThing(copy);
	  copy = makeRange(makeConstant(*(yrange.a)),makeConstant(*(yrange.b)));
	  mpfr_clear(*(xrange.a));
	  mpfr_clear(*(xrange.b));
	  mpfr_clear(*(yrange.a));
	  mpfr_clear(*(yrange.b));
	  free(xrange.a);
	  free(xrange.b);
	  free(yrange.a);
	  free(yrange.b);
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      }
    }
    break; 			
  case PARSE:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isString(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      if ((tempNode = parseString(copy->child1->string)) != NULL) {
	freeThing(copy);
	copy = tempNode; 
      } else {
	printMessage(1,"Warning: the string \"%s\" could not be parsed by the miniparser.\n",copy->child1->string);
      }
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case READXML:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isString(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      if ((tempNode = readXml(copy->child1->string)) != NULL) {
	freeThing(copy);
	copy = tempNode; 
	if (variablename == NULL) {
	  printMessage(1,"Warning: the free varible is not bound to an identifier. Reading an XML file requires this binding.\n");
	  printMessage(1,"Will bind the free variable to the identifier \"x\"\n");
	  variablename = safeCalloc(2,sizeof(char));
	  variablename[0] = 'x';
	}
      } else {
	printMessage(1,"Warning: the file \"%s\" could not be read as an XML file.\n",copy->child1->string);
      }
      if (timingString != NULL) popTimeCounter(timingString);
    }
    break; 			 	
  case INFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = (node *) (curr->value);
    curr = curr->next;
    secondArg = (node *) (curr->value);
    curr = curr->next;
    fourthArg = NULL;
    if (curr != NULL) {
      if (isString((node *) (curr->value))) {
	fourthArg = (node *) (curr->value);
	curr = curr->next;
      }
    }
    resA = 1;
    tempChain = NULL;
    if (curr != NULL) {
      if (isPureList((node *) (curr->value))) {
	tempChain = ((node *) (curr->value))->arguments;
	curr = tempChain;
	while (curr != NULL) {
	  if (!isRange((node *) (curr->value))) {
	    resA = 0;
	    break;
	  }
	  curr = curr->next;
	}
      } else {
	resA = 0;
      }
    }
    if (isPureTree(firstArg) &&
	isRange(secondArg) &&
	resA
	) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,secondArg)) {
	resB = 0; fd = NULL;
	if (fourthArg == NULL) resB = 1; else {
	  if (evaluateThingToString(&tempString,fourthArg)) {
	    resB = 1;
	    if ((fd = fopen(tempString,"w")) == NULL) {
	      printMessage(1,"Warning: the file \"%s\" could not be opened for writing. The proof argument will be ignored.\n",tempString);
	    }
	    free(tempString);
	  }
	}
	if (resB) {
	  newChain = NULL;
	  if (tempChain != NULL) {
	    curr = tempChain;
	    while (curr != NULL) {
	      rangeTempPtr = (rangetype *) safeMalloc(sizeof(rangetype));
	      rangeTempPtr->a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	      rangeTempPtr->b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	      mpfr_init2(*(rangeTempPtr->a),tools_precision);
	      mpfr_init2(*(rangeTempPtr->b),tools_precision);
	      evaluateThingToRange(*(rangeTempPtr->a),*(rangeTempPtr->b),(node *) (curr->value));
	      newChain = addElement(newChain, rangeTempPtr);
	      curr = curr->next;
	    }
	  }
	  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(xrange.a),tools_precision);
	  mpfr_init2(*(xrange.b),tools_precision);
	  mpfr_set(*(xrange.a),a,GMP_RNDN);
	  mpfr_set(*(xrange.b),b,GMP_RNDN);
	  if (timingString != NULL) pushTimeCounter();      
	  yrange = infnorm(firstArg, xrange, newChain, tools_precision, statediam, fd);
	  if (timingString != NULL) popTimeCounter(timingString);     
	  if (fd != NULL) fclose(fd);
	  tempNode = makeRange(makeConstant(*(yrange.a)),makeConstant(*(yrange.b)));
	  mpfr_clear(*(yrange.a));
	  mpfr_clear(*(yrange.b));
	  free(yrange.a);
	  free(yrange.b);
	  mpfr_clear(*(xrange.a));
	  mpfr_clear(*(xrange.b));
	  free(xrange.a);
	  free(xrange.b);
	  if (newChain != NULL) freeChain(newChain,freeRangetypePtr);
	  freeThing(copy);
	  copy = tempNode;
	}
      }  
      mpfr_clear(a);
      mpfr_clear(b);
    } 
    break; 			
  case FINDZEROS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(xrange.a),tools_precision);
	mpfr_init2(*(xrange.b),tools_precision);
	mpfr_set(*(xrange.a),a,GMP_RNDN);
	mpfr_set(*(xrange.b),b,GMP_RNDN);
	if (timingString != NULL) pushTimeCounter(); 
	tempChain = findZerosFunction(copy->child1, xrange, tools_precision, statediam);
	if (timingString != NULL) popTimeCounter(timingString);
	if (tempChain == NULL) {
	  tempNode = makeEmptyList();
	} else {
	  newChain = NULL;
	  curr = tempChain;
	  while (curr != NULL) {
	    newChain = addElement(newChain,makeRange(makeConstant(*(((rangetype *) (curr->value))->a)),makeConstant(*(((rangetype *) (curr->value))->b))));
	    curr = curr->next;
	  }
	  curr = copyChain(newChain,copyThingOnVoid);
	  freeChain(newChain,freeThingOnVoid);
	  newChain = curr;
	  tempNode = makeList(newChain);
	}
	freeChain(tempChain,freeRangetypePtr);
	mpfr_clear(*(xrange.a));
	mpfr_clear(*(xrange.b));
	free(xrange.a);
	free(xrange.b);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case FPFINDZEROS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(xrange.a),tools_precision);
	mpfr_init2(*(xrange.b),tools_precision);
	mpfr_set(*(xrange.a),a,GMP_RNDN);
	mpfr_set(*(xrange.b),b,GMP_RNDN);
	if (timingString != NULL) pushTimeCounter(); 
	tempChain = fpFindZerosFunction(copy->child1, xrange, tools_precision);
	if (timingString != NULL) popTimeCounter(timingString);
	if (tempChain == NULL) {
	  tempNode = makeEmptyList();
	} else {
	  newChain = NULL;
	  curr = tempChain;
	  while (curr != NULL) {
	    newChain = addElement(newChain,makeConstant(*((mpfr_t *) (curr->value))));
	    curr = curr->next;
	  }
	  curr = copyChain(newChain,copyThingOnVoid);
	  freeChain(newChain,freeThingOnVoid);
	  newChain = curr;
	  tempNode = makeList(newChain);
	}
	freeChain(tempChain,freeMpfrPtr);
	mpfr_clear(*(xrange.a));
	mpfr_clear(*(xrange.b));
	free(xrange.a);
	free(xrange.b);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case DIRTYINFNORM:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	mpfr_init2(c,tools_precision);
	if (timingString != NULL) pushTimeCounter(); 
	uncertifiedInfnorm(c, copy->child1, a, b, defaultpoints, tools_precision);
	if (timingString != NULL) popTimeCounter(timingString);
	tempNode = makeConstant(c);
	mpfr_clear(c);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case INTEGRAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	mpfr_init2(*(xrange.a),tools_precision);
	mpfr_init2(*(xrange.b),tools_precision);
	mpfr_set(*(xrange.a),a,GMP_RNDN);
	mpfr_set(*(xrange.b),b,GMP_RNDN);
	if (timingString != NULL) pushTimeCounter(); 
	yrange = integral(copy->child1, xrange, tools_precision, statediam);
	if (timingString != NULL) popTimeCounter(timingString);
	tempNode = makeRange(makeConstant(*(yrange.a)),makeConstant(*(yrange.b)));
	mpfr_clear(*(yrange.a));
	mpfr_clear(*(yrange.b));
	free(yrange.a);
	free(yrange.b);
	mpfr_clear(*(xrange.a));
	mpfr_clear(*(xrange.b));
	free(xrange.a);
	free(xrange.b);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case DIRTYINTEGRAL:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	mpfr_init2(c,tools_precision);
	if (timingString != NULL) pushTimeCounter(); 
	uncertifiedIntegral(c, copy->child1, a, b, defaultpoints, tools_precision);
	if (timingString != NULL) popTimeCounter(timingString);
	tempNode = makeConstant(c);
	mpfr_clear(c);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break;  			
  case IMPLEMENTPOLY:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = (node *) (curr->value);
    curr = curr->next;
    secondArg = (node *) (curr->value);
    curr = curr->next;
    thirdArg = (node *) (curr->value);
    curr = curr->next;
    fourthArg = (node *) (curr->value);
    curr = curr->next;
    fifthArg = (node *) (curr->value);
    curr = curr->next;
    sixthArg = (node *) (curr->value);
    curr = curr->next;
    resA = 1; resB = 0; tempString = NULL;
    if (curr != NULL) {
      seventhArg = (node *) (curr->value);
      if (!(isHonorcoeffprec(seventhArg) || isString(seventhArg))) {
	resA = 0;
      } 
      if (resA) {
	if (isHonorcoeffprec(seventhArg)) {
	  resB = 1;
	} else {
	  if (!evaluateThingToString(&tempString,seventhArg)) {
	    resA = 0;
	  }
	}
      }
      curr = curr->next;
      if (curr != NULL) {
	eighthArg = (node *) (curr->value);
	if (!(isHonorcoeffprec(eighthArg) || isString(eighthArg))) {
	  resA = 0;
	} 
	if (resA) {
	  if (isHonorcoeffprec(eighthArg)) {
	    resB = 1;
	  } else {
	    if (tempString != NULL) {
	      resA = 0;
	    } else {
	      if (!evaluateThingToString(&tempString,eighthArg)) {
		resA = 0;
	      }
	    }
	  }
	}
      }
    }
    fd = NULL;
    if (tempString != NULL) {
      if ((fd = fopen(tempString,"w")) == NULL) {
	printMessage(1,"Warning: the file \"%s\" could not be opened for writing. The proof argument will be ignored.\n",tempString);
      }
      free(tempString);
    }
    if (isPureTree(firstArg) &&
	isRange(secondArg) &&
	isPureTree(thirdArg) &&
	isRestrictedExpansionFormat(fourthArg) &&
	isString(fifthArg) &&
	isString(sixthArg) &&
	resA) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      mpfr_init2(c,tools_precision);
      if (evaluateThingToRange(a,b,secondArg) &&
	  evaluateThingToConstant(c,thirdArg,NULL) &&
	  evaluateThingToRestrictedExpansionFormat(&resC,fourthArg) &&
	  evaluateThingToString(&tempString2, fifthArg) &&
	  evaluateThingToString(&tempString3, sixthArg)) {
	if ((fd2 = fopen(tempString3,"w")) != NULL) {
	  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(xrange.a),tools_precision);
	  mpfr_init2(*(xrange.b),tools_precision);
	  mpfr_set(*(xrange.a),a,GMP_RNDN);
	  mpfr_set(*(xrange.b),b,GMP_RNDN);
	  if (timingString != NULL) pushTimeCounter(); 
	  tempNode = implementpoly(firstArg, xrange, &c, resC, fd2, tempString2, resB, tools_precision, fd);
	  if (timingString != NULL) popTimeCounter(timingString);
	  mpfr_clear(*(xrange.a));
	  mpfr_clear(*(xrange.b));
	  free(xrange.a);
	  free(xrange.b);
	  if (tempNode == NULL) {
	    printMessage(1,"Warning: the implementation has not succeeded. The command could be executed.\n");
	    tempNode = makeError();
	  }
	  fclose(fd2);
	} else {
	  printMessage(1,"Warning: the file \"%s\" could not be opened for writing. The command cannot be executed.\n",tempString3);
	  tempNode = makeError();
	}
	free(tempString2);
	free(tempString3);
	freeThing(copy);
	copy = tempNode;
      }
      mpfr_clear(a);
      mpfr_clear(b);
      mpfr_clear(c);
    }
    if (fd != NULL) fclose(fd);
    break; 			
  case CHECKINFNORM:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = (node *) (curr->value);
    curr = curr->next;
    secondArg = (node *) (curr->value);
    curr = curr->next;
    thirdArg = (node *) (curr->value);
    if (isPureTree(firstArg) &&
	isRange(secondArg) &&
	isPureTree(thirdArg)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,secondArg)) {
	mpfr_init2(c,tools_precision);
	if (evaluateThingToConstant(c,thirdArg,NULL)) {
	  xrange.a = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  xrange.b = (mpfr_t *) safeMalloc(sizeof(mpfr_t));
	  mpfr_init2(*(xrange.a),tools_precision);
	  mpfr_init2(*(xrange.b),tools_precision);
	  mpfr_set(*(xrange.a),a,GMP_RNDN);
	  mpfr_set(*(xrange.b),b,GMP_RNDN);
	  if (timingString != NULL) pushTimeCounter(); 
	  resA = checkInfnorm(firstArg, xrange, c, statediam, tools_precision);
	  if (timingString != NULL) popTimeCounter(timingString);
	  mpfr_clear(*(xrange.a));
	  mpfr_clear(*(xrange.b));
	  free(xrange.a);
	  free(xrange.b);
	  freeThing(copy);
	  if (resA) 
	    copy = makeTrue();
	  else 
	    copy = makeFalse();
	}
	mpfr_clear(c);
      }
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case ZERODENOMINATORS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	if (timingString != NULL) pushTimeCounter(); 
	tempChain = uncertifiedZeroDenominators(copy->child1, a, b, tools_precision);
	if (timingString != NULL) popTimeCounter(timingString);
	if (tempChain == NULL) {
	  tempNode = makeEmptyList();
	} else {
	  newChain = NULL;
	  curr = tempChain;
	  while (curr != NULL) {
	    newChain = addElement(newChain,makeConstant(*((mpfr_t *) (curr->value))));
	    curr = curr->next;
	  }
	  curr = copyChain(newChain,copyThingOnVoid);
	  freeChain(newChain,freeThingOnVoid);
	  newChain = curr;
	  tempNode = makeList(newChain);
	}
	freeChain(tempChain,freeMpfrPtr);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break;  		
  case ISEVALUABLE:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isPureTree(copy->child2)) {
      mpfr_init2(a,tools_precision);
      if (evaluateThingToConstant(a,copy->child2,NULL)) {
	if (timingString != NULL) pushTimeCounter();      
	mpfr_init2(b,tools_precision);
	if (isEvaluable(copy->child1, a, &b, tools_precision) != ISNOTEVALUABLE) {
	  tempNode = makeTrue();
	} else { 
	  tempNode = makeFalse();
	}
	mpfr_clear(b);
	freeThing(copy);
	copy = tempNode;
	if (timingString != NULL) popTimeCounter(timingString);
      }
      mpfr_clear(a);
    }
    break; 			
  case SEARCHGAL:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    if (lengthChain(copy->arguments) >= 6) {
      curr = copy->arguments;
      firstArg = copyThing((node *) (curr->value));
      curr = curr->next;
      if (isPureTree(firstArg)) {
	firstArg = makeList(addElement(NULL,firstArg));
      }
      secondArg = copyThing((node *) (curr->value));
      curr = curr->next;
      thirdArg = copyThing((node *) (curr->value));
      curr = curr->next;
      fourthArg = copyThing((node *) (curr->value));
      curr = curr->next;
      fifthArg = copyThing((node *) (curr->value));
      curr = curr->next;
      if (isExpansionFormat(fifthArg)) {
	fifthArg = makeList(addElement(NULL,fifthArg));
      }
      sixthArg = copyThing((node *) (curr->value));
      if (isPureTree(sixthArg)) {
	sixthArg = makeList(addElement(NULL,sixthArg));
      }
      if (isPureList(firstArg) &&
	  isPureTree(secondArg) &&
	  isPureTree(thirdArg) &&
	  isPureTree(fourthArg) &&
	  isPureList(fifthArg) &&
	  isPureList(sixthArg) &&
	  (lengthChain(firstArg->arguments) == lengthChain(fifthArg->arguments)) &&
	  (lengthChain(fifthArg->arguments) == lengthChain(sixthArg->arguments))) {
	if (evaluateThingToPureListOfPureTrees(&tempChain, firstArg)) {
	  mpfr_init2(a,tools_precision);
	  if (evaluateThingToConstant(a,secondArg,NULL) &&
	      evaluateThingToInteger(&resA,thirdArg,NULL) &&
	      evaluateThingToInteger(&resB,fourthArg,NULL)) {
	    if (evaluateThingToExpansionFormatList(&tempChain2, fifthArg)) {
	      if (evaluateThingToConstantList(&tempChain3, sixthArg)) {
		mpfr_init2(c,tools_precision);
		if (timingString != NULL) pushTimeCounter(); 
		resC = searchGalValue(tempChain, c, a, (mp_prec_t) resA, resB, tempChain2, tempChain3, tools_precision);
		if (timingString != NULL) popTimeCounter(timingString);
		if (resC) {
		  tempNode = makeList(addElement(NULL,makeConstant(c)));
		} else {
		  tempNode = makeEmptyList();
		}
		freeThing(copy);
		copy = tempNode;
		mpfr_clear(c);
		freeChain(tempChain3, freeMpfrPtr);
	      }
	      freeChain(tempChain2, freeIntPtr);
	    }
	  }
	  mpfr_clear(a);
	  freeChain(tempChain,freeThingOnVoid);
	}
      }
      freeThing(firstArg);
      freeThing(secondArg);
      freeThing(thirdArg);
      freeThing(fourthArg);
      freeThing(fifthArg);
      freeThing(sixthArg);
    }
    break; 			
  case GUESSDEGREE:
    copy->arguments = copyChainWithoutReversal(tree->arguments, evaluateThingInnerOnVoid);
    curr = copy->arguments;
    firstArg = copyThing((node *) (curr->value));
    curr = curr->next;
    secondArg = copyThing((node *) (curr->value));
    curr = curr->next;
    thirdArg = copyThing((node *) (curr->value));
    curr = curr->next;
    if (curr != NULL) {
      fourthArg = copyThing((node *) (curr->value));
    } else {
      fourthArg = makeConstantDouble(1.0);
    }
    if (isPureTree(firstArg) &&
	isRange(secondArg) &&
	isPureTree(thirdArg) &&
	isPureTree(fourthArg)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      mpfr_init2(c,tools_precision);
      if (evaluateThingToRange(a,b,secondArg) &&
	  evaluateThingToConstant(c,thirdArg, NULL)) {
	if (timingString != NULL) pushTimeCounter(); 
	yrange = guessDegree(firstArg, fourthArg, a, b, c);
	if (timingString != NULL) popTimeCounter(timingString);
	tempNode = makeRange(makeConstant(*(yrange.a)),makeConstant(*(yrange.b)));
	freeThing(copy);
	copy = tempNode;
	mpfr_clear(*(yrange.a));
	mpfr_clear(*(yrange.b));
	free(yrange.a);
	free(yrange.b);
      }
      mpfr_clear(a);
      mpfr_clear(b);
      mpfr_clear(c);
    }
    freeThing(firstArg);
    freeThing(secondArg);
    freeThing(thirdArg);
    freeThing(fourthArg);
    break; 			
  case DIRTYFINDZEROS:
    copy->child1 = evaluateThingInner(tree->child1);
    copy->child2 = evaluateThingInner(tree->child2);
    if (isPureTree(copy->child1) &&
	isRange(copy->child2)) {
      mpfr_init2(a,tools_precision);
      mpfr_init2(b,tools_precision);
      if (evaluateThingToRange(a,b,copy->child2)) {
	if (timingString != NULL) pushTimeCounter(); 
	tempChain = uncertifiedFindZeros(copy->child1, a, b, defaultpoints, tools_precision);
	if (timingString != NULL) popTimeCounter(timingString);
	if (tempChain == NULL) {
	  tempNode = makeEmptyList();
	} else {
	  newChain = NULL;
	  curr = tempChain;
	  while (curr != NULL) {
	    newChain = addElement(newChain,makeConstant(*((mpfr_t *) (curr->value))));
	    curr = curr->next;
	  }
	  curr = copyChain(newChain,copyThingOnVoid);
	  freeChain(newChain,freeThingOnVoid);
	  newChain = curr;
	  tempNode = makeList(newChain);
	}
	freeChain(tempChain,freeMpfrPtr);
	freeThing(copy);
	copy = tempNode;
      } 
      mpfr_clear(a);
      mpfr_clear(b);
    }
    break; 			
  case HEAD:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isList(copy->child1)) {
      if (!isElliptic((node *) (copy->child1->arguments->value))) {
	if (timingString != NULL) pushTimeCounter();      
	tempNode = copyThing((node *) (copy->child1->arguments->value));
	freeThing(copy);
	copy = tempNode; 
	if (timingString != NULL) popTimeCounter(timingString);
      }
    } else {
      if (isFinalEllipticList(copy->child1)) {
	if (!isElliptic((node *) (copy->child1->arguments->value))) {
	  if (timingString != NULL) pushTimeCounter();      
	  tempNode = copyThing((node *) (copy->child1->arguments->value));
	  freeThing(copy);
	  copy = tempNode; 
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      } 
    }
    break; 			 	
  case TAIL:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isList(copy->child1)) {
      if (copy->child1->arguments->next == NULL) {
	if (timingString != NULL) pushTimeCounter();      
	freeThing(copy->child1);
	copy->nodeType = EMPTYLIST;
	if (timingString != NULL) popTimeCounter(timingString);
      } else {
	if (!isElliptic((node *) (copy->child1->arguments->next->value))) {
	  if (timingString != NULL) pushTimeCounter();      
	  copy->arguments = copyChainWithoutReversal(copy->child1->arguments->next,copyThingOnVoid);
	  freeThing(copy->child1);
	  copy->nodeType = LIST;
	  if (timingString != NULL) popTimeCounter(timingString);
	}
      }
    } else {
      if (isFinalEllipticList(copy->child1)) {
	if (copy->child1->arguments->next != NULL) {
	  if (!isElliptic((node *) (copy->child1->arguments->next->value))) {
	    if (timingString != NULL) pushTimeCounter();      
	    copy->arguments = copyChainWithoutReversal(copy->child1->arguments->next,copyThingOnVoid);
	    freeThing(copy->child1);
	    copy->nodeType = FINALELLIPTICLIST;
	    if (timingString != NULL) popTimeCounter(timingString);
	  }
	}
      }
    }
    break; 			 	
  case LENGTH:
    copy->child1 = evaluateThingInner(tree->child1);
    if (isEmptyList(copy->child1)) {
      if (timingString != NULL) pushTimeCounter();      
      freeThing(copy);
      copy = makeConstantDouble(0.0);
      if (timingString != NULL) popTimeCounter(timingString);
    } else {
      if (isPureList(copy->child1)) {
	if (timingString != NULL) pushTimeCounter();      
	resA = lengthChain(copy->child1->arguments);
	mpfr_init2(a,sizeof(int) * 8);
	mpfr_set_si(a,resA,GMP_RNDN);
	freeThing(copy);
	copy = makeConstant(a);
	mpfr_clear(a);
	if (timingString != NULL) popTimeCounter(timingString);
      } else {
	if (isFinalEllipticList(copy->child1)) {
	  if (timingString != NULL) pushTimeCounter();      
	  mpfr_init2(a,sizeof(int) * 8);
	  mpfr_set_inf(a,1);
	  freeThing(copy);
	  copy = makeConstant(a);
	  mpfr_clear(a);
	  if (timingString != NULL) popTimeCounter(timingString);
	} else {
	  if (isString(copy->child1)) {
	    if (timingString != NULL) pushTimeCounter();      
	    resA = strlen(copy->child1->string);
	    mpfr_init2(a,sizeof(int) * 8);
	    mpfr_set_si(a,resA,GMP_RNDN);
	    freeThing(copy);
	    copy = makeConstant(a);
	    mpfr_clear(a);
	    if (timingString != NULL) popTimeCounter(timingString);
	  }  
	}
      }
    }
    break; 			 	
  case PRECDEREF:
    if (timingString != NULL) pushTimeCounter();      
    mpfr_init2(a,sizeof(int) * 8);
    mpfr_set_si(a,tools_precision,GMP_RNDN);
    freeThing(copy);
    copy = makeConstant(a);
    mpfr_clear(a);
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case POINTSDEREF:
    if (timingString != NULL) pushTimeCounter();      
    mpfr_init2(a,sizeof(int) * 8);
    mpfr_set_si(a,defaultpoints,GMP_RNDN);
    freeThing(copy);
    copy = makeConstant(a);
    mpfr_clear(a);
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case DIAMDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    copy = makeConstant(statediam);
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case DISPLAYDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    switch (dyadic) {	     
    case 0:
      copy = makeDecimal();
      break;
    case 1:
      copy = makeDyadic();
      break;
    case 2:
      copy = makePowers();
      break;
    case 3:
      copy = makeBinaryThing();
      break;
    default:
      fprintf(stderr,"Error: display mode in unknown state.\n");
      exit(1);
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case VERBOSITYDEREF:
    if (timingString != NULL) pushTimeCounter();      
    mpfr_init2(a,sizeof(int) * 8);
    mpfr_set_si(a,verbosity,GMP_RNDN);
    freeThing(copy);
    copy = makeConstant(a);
    mpfr_clear(a);
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case CANONICALDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    if (canonical) {
      copy = makeOn();
    } else {
      copy = makeOff();
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case AUTOSIMPLIFYDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    if (autosimplify) {
      copy = makeOn();
    } else {
      copy = makeOff();
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 		
  case TAYLORRECURSDEREF:
    if (timingString != NULL) pushTimeCounter();      
    mpfr_init2(a,sizeof(int) * 8);
    mpfr_set_si(a,taylorrecursions,GMP_RNDN);
    freeThing(copy);
    copy = makeConstant(a);
    mpfr_clear(a);
    if (timingString != NULL) popTimeCounter(timingString);
    break; 		
  case TIMINGDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    if (timecounting) {
      copy = makeOn();
    } else {
      copy = makeOff();
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case FULLPARENDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    if (fullParentheses) {
      copy = makeOn();
    } else {
      copy = makeOff();
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case MIDPOINTDEREF:
    if (timingString != NULL) pushTimeCounter();      
    freeThing(copy);
    if (midpointMode) {
      copy = makeOn();
    } else {
      copy = makeOff();
    }
    if (timingString != NULL) popTimeCounter(timingString);
    break; 			
  case HOPITALRECURSDEREF:
    if (timingString != NULL) pushTimeCounter();      
    mpfr_init2(a,sizeof(int) * 8);
    mpfr_set_si(a,hopitalrecursions,GMP_RNDN);
    freeThing(copy);
    copy = makeConstant(a);
    mpfr_clear(a);
    if (timingString != NULL) popTimeCounter(timingString);
    break;  	       
  default:
    fprintf(stderr,"Error: evaluateThingInner: unknown identifier (%d) in the tree\n",tree->nodeType);
    exit(1);
  }

  if (timingString != NULL) free(timingString);

  return copy;
}
