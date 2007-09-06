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
#include "xml.h"


void printXml(node *tree) {
  fPrintXml(stdout,tree);
}


void fPrintXmlInner(FILE *fd, node *tree) {
  if (tree == NULL) return;
  switch (tree->nodeType) {
  case VARIABLE:
    if (variablename == NULL) 
      fprintf(fd,"<ci> x </ci>\n");
    else 
      fprintf(fd,"<ci> %s </ci>\n",variablename);
    break;
  case CONSTANT:
    fprintValueForXml(fd, *(tree->value));
    break;
  case ADD:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<plus/>\n");
    fPrintXmlInner(fd, tree->child1);
    fPrintXmlInner(fd, tree->child2);
    fprintf(fd,"</apply>\n");
    break;
  case SUB:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<minus/>\n");
    fPrintXmlInner(fd, tree->child1);
    fPrintXmlInner(fd, tree->child2);
    fprintf(fd,"</apply>\n");
    break;
  case MUL:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<times/>\n");
    fPrintXmlInner(fd, tree->child1);
    fPrintXmlInner(fd, tree->child2);
    fprintf(fd,"</apply>\n");
    break;
  case DIV:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<divide/>\n");
    fPrintXmlInner(fd, tree->child1);
    fPrintXmlInner(fd, tree->child2);
    fprintf(fd,"</apply>\n");
    break;
  case SQRT:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<root/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case EXP:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<exp/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case LOG:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<ln/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case LOG_2:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<log/><logbase><cn>2</cn></logbase>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case LOG_10:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<log/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case SIN:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<sin/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case COS:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<cos/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case TAN:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<tan/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ASIN:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arcsin/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ACOS:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arccos/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ATAN:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arctan/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case SINH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<sinh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case COSH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<cosh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case TANH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<tanh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ASINH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arcsinh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ACOSH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arccosh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ATANH:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<arctanh/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case POW:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<power/>\n");
    fPrintXmlInner(fd, tree->child1);
    fPrintXmlInner(fd, tree->child2);
    fprintf(fd,"</apply>\n");
    break;
  case NEG:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<minus/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ABS:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<abs/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case DOUBLE:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">double</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case DOUBLEDOUBLE:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">doubledouble</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case TRIPLEDOUBLE:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">tripledouble</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ERF: 
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.openmath.org/CDs/errorFresnelInts.ocd\" encoding=\"OpenMath\">erf</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case ERFC:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.openmath.org/CDs/errorFresnelInts.ocd\" encoding=\"OpenMath\">erfc</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case LOG_1P:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<log/><apply><plus/><cn>1</cn>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply></apply>\n");
    break;
  case EXP_M1:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<apply><minus/><apply><exp>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply><cn>1</cn></apply>\n");
    break;
  case DOUBLEEXTENDED:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">doubleextended</csymbol>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case LIBRARYFUNCTION:
    if (tree->libFunDeriv == 0) {
      fprintf(fd,"<apply>\n");
      fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">%s</csymbol>\n",
	      tree->libFun->functionName);
      fPrintXmlInner(fd, tree->child1);
      fprintf(fd,"</apply>\n");	 
    } else {
      fprintf(fd,"<apply>\n");
      fprintf(fd,"<diff/>\n");
      fprintf(fd,"<bvar>\n");
      if (variablename == NULL) 
	fprintf(fd,"<ci> x </ci>\n");
      else 
	fprintf(fd,"<ci> %s </ci>\n",variablename);
      fprintf(fd,"<degree>\n");
      fprintf(fd,"<cn> %d </cn>\n",tree->libFunDeriv);
      fprintf(fd,"</degree>\n");
      fprintf(fd,"</bvar>\n");
      fprintf(fd,"<apply>\n");
      fprintf(fd,"<csymbol definitionURL=\"http://www.google.com/\" encoding=\"OpenMath\">%s</csymbol>\n",
	      tree->libFun->functionName);
      fPrintXmlInner(fd, tree->child1);
      fprintf(fd,"</apply>\n");	 
      fprintf(fd,"</apply>\n");
    }
    break;
  case CEIL:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<ceiling/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case FLOOR:
    fprintf(fd,"<apply>\n");
    fprintf(fd,"<floor/>\n");
    fPrintXmlInner(fd, tree->child1);
    fprintf(fd,"</apply>\n");
    break;
  case PI_CONST:
    fprintf(fd,"<pi/>");
    break;
  default:
   fprintf(stderr,"Error: fPrintXml: unknown identifier (%d) in the tree\n",tree->nodeType);
   exit(1);
  }
  return;  
}

void fPrintXml(FILE *fd, node *tree) {
  fprintf(fd,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(fd,"<!DOCTYPE math PUBLIC \"-//W3C//DTD MathML 2.0//EN\" \"http://www.w3.org/Math/DTD/mathml2/mathml2.dtd\" >\n");
  fprintf(fd,"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n");
  fprintf(fd,"<semantics>\n");
  fprintf(fd,"<annotation-xml encoding=\"MathML-Content\">\n");
  fprintf(fd,"<lambda>\n");
  if (variablename != NULL) 
    fprintf(fd,"<bvar><ci> %s </ci></bvar>\n",variablename);
  else 
    fprintf(fd,"<bvar><ci> x </ci></bvar>\n");
  fprintf(fd,"<apply>\n");
  fPrintXmlInner(fd,tree);
  fprintf(fd,"</apply>\n");
  fprintf(fd,"</lambda>\n");
  fprintf(fd,"</annotation-xml>\n");
  fprintf(fd,"<annotation encoding=\"arenaireplot/text\">");
  fprintTree(fd, tree);
  fprintf(fd,"</annotation>\n");
  fprintf(fd,"</semantics>\n");
  fprintf(fd,"</math>\n\n");
}


/* Reads the file filename containing a lambda construct
   into a node * 
   Return NULL if parsing the file is impossible

   Indication: use make... found in expression.h for building the nodes.
   Attention: do not forget do free incomplete trees if the 
   parsing fails. Use free_memory(node *) for this (found in expression.h).

   If warnings to the user shall be indicated, use printMessage(verbosity level, format string, ...)

*/
node *readXml(char *filename) {

  printf("We should now read the XML file \"%s\".\n",filename);

  return NULL;
}
