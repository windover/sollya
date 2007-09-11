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

// Nico:
// From: libxml2-2.6.30 and reader1.c example
// http://xmlsoft.org/examples/index.html#reader1.c

/** 
 * section: xmlReader
 * synopsis: Parse an XML file with an xmlReader
 * purpose: Demonstrate the use of xmlReaderForFile() to parse an XML file
 *          and dump the informations about the nodes found in the process.
 *          (Note that the XMLReader functions require libxml2 version later
 *          than 2.6.)
 * usage: reader1 <filename>
 * test: reader1 test2.xml > reader1.tmp ; diff reader1.tmp reader1.res ; rm reader1.tmp
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libxml/xmlreader.h>

#ifdef LIBXML_READER_ENABLED

// PARSER MATHML - return: 0 (not found) -1 (sync lost) 1 (found)
int search_mathml		 (xmlTextReaderPtr reader);
int search_semantics  (xmlTextReaderPtr reader);
int search_annotations(xmlTextReaderPtr reader);
int process_annotation(xmlTextReaderPtr reader);
int process_content   (xmlTextReaderPtr reader);

static int (*next_xmlparser)(xmlTextReaderPtr reader)=search_mathml;

static int				current_depth;
static const xmlChar *xml_name, *xml_value;
static node				*result_node;

#define change_xmlparser(new_parser) do { \
	printMessage(3,"%p => ",next_xmlparser); \
	printMessage(3,"%p\n",next_xmlparser=new_parser); } while(0)

int process_annotation(xmlTextReaderPtr reader)
{
// using external node *parseString(char *)
// Depth: 03 Type: 03 Name: #text (HasValue) ((x^(1b1)) + (1b2 * x)) - sin(x)
// on_error 
if (current_depth+2>=xmlTextReaderDepth(reader))
	{ change_xmlparser(search_annotations); return -1; }
// on_search
if (xmlTextReaderIsEmptyElement(reader) ||
    xmlTextReaderNodeType(reader)!=3 ||
    current_depth+3!=xmlTextReaderDepth(reader)
    ) return 0;
result_node=parseString((char*)xml_value);
change_xmlparser(search_annotations);
return 1;
}

int process_content(xmlTextReaderPtr reader)
{
// node *parseString(char *)
return 0;
}

int search_annotations(xmlTextReaderPtr reader)
{
// on_error 
if (current_depth+1>=xmlTextReaderDepth(reader))
	{ change_xmlparser(search_semantics); return -1; }
// on_search
if (xmlTextReaderIsEmptyElement(reader) ||
    xmlTextReaderNodeType(reader)!=1 ||
    current_depth+2!=xmlTextReaderDepth(reader)
    ) return 0;
if (!strcmp(xml_name,"annotation") &&
    xmlTextReaderHasAttributes(reader) &&
    !strcmp(xmlTextReaderGetAttribute(reader,"encoding"),"arenaireplot/text") )
	{ change_xmlparser(process_annotation); return 1;}
if (0 && !strcmp(xml_name,"annotation-xml") &&
    xmlTextReaderHasAttributes(reader) &&
    !strcmp(xmlTextReaderGetAttribute(reader,"encoding"),"MathML-Content") )
	{ change_xmlparser(process_content); return 1;}
// on_not_found
return 1;
}

int search_semantics (xmlTextReaderPtr reader)
{
// on_error 
if (current_depth>=xmlTextReaderDepth(reader)) { change_xmlparser(search_mathml); return -1; }
// on_cannot_find
if (xmlTextReaderIsEmptyElement(reader) ||
    strcmp(xml_name,"semantics") ||
    xmlTextReaderNodeType(reader)!=1 ||
    current_depth+1!=xmlTextReaderDepth(reader)
    ) return 0;
// on_found
change_xmlparser(search_annotations);
return 1;
}

int search_mathml (xmlTextReaderPtr reader)
{
// on_error => nothing to do
// on_cannot_find =>
if (xmlTextReaderIsEmptyElement(reader) ||
    strcmp(xml_name,"math") ||
    xmlTextReaderNodeType(reader)!=1
    ) return 0;
// on_found =>
current_depth=xmlTextReaderDepth(reader);
change_xmlparser(search_semantics);
return 1;
}

/**
 * processNode:
 * @reader: the xmlReader
 *
 * Dump information about the current node
 */
static int
processNode(xmlTextReaderPtr reader) {
// doc/info: http://xmlsoft.planetmirror.com/html/libxml-xmlreader.html
    int				ret;

    ret = xmlTextReaderRead(reader);
    if (ret!=1) { // EOF or ERROR
      if (ret) printf("Failed to parse, return code %i\n",ret);
      return ret;
      }
    xml_name = xmlTextReaderConstName(reader);
    if (xml_name == NULL)
	 xml_name = BAD_CAST "--";

    xml_value = xmlTextReaderConstValue(reader);

    printMessage(3,"Depth: %02d Type: %02d Name: %s", 
	    xmlTextReaderDepth(reader),
	    xmlTextReaderNodeType(reader),
	    xml_name);
	 if (xmlTextReaderIsEmptyElement(reader)) printMessage(3," (EmptyElt)");
	 if (xmlTextReaderHasValue(reader))       printMessage(3," (HasValue)");
	 if (xmlTextReaderHasAttributes(reader))  printMessage(3," (HasAttrb)");
    if (xml_value == NULL || // XmlNodeType.SignificantWhitespace
    	  xmlTextReaderNodeType(reader)==14)  	printMessage(3,"\n");
    else {
        if (xmlStrlen(xml_value) > 40)       printMessage(3," %.40s...\n", xml_value);
        else                                 printMessage(3," %s\n", xml_value);  }
while((*next_xmlparser)(reader)<0) printMessage(2,"Lost Sync! Try resync...\n");
return ret;
}





/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 */
static node*
streamXmlFile(const char *filename) {
    xmlTextReaderPtr reader;

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader == NULL) { printf("Unable to open %s\n", filename); return NULL; }
    for(result_node=NULL,current_depth=0;processNode(reader)==1 && !result_node;);
    xmlFreeTextReader(reader);
    return result_node;
}

/* Reads the file filename containing a lambda construct
   into a node * 
   Return NULL if parsing the file is impossible

   Indication: use make... found in expression.h for building the nodes.
   Attention: do not forget do free incomplete trees if the 
   parsing fails. Use free_memory(node *) for this (found in expression.h).

   If warnings to the user shall be indicated, use printMessage(verbosity level, format string, ...)
   verbosity level=0 nothing 1 important 2 information 3 internal/debug...
*/
node *readXml(char *filename) {
	node* result=NULL;
	
  printf("We should now read the XML file \"%s\".\n",filename);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    result=streamXmlFile(filename);

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();

  return result;
}

#else
node *readXml(char *filename) {
  printf("We should now read the XML file \"%s\".\n",filename);
  printf("XInclude support not compiled in, cannot parse XML file.\n");
    return NULL;
}
#endif

