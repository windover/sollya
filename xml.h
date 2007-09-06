#ifndef XML_H
#define XML_H


#include <mpfr.h>
#include <stdio.h>
#include "main.h"
#include "expression.h"

void printXml(node *);
void fPrintXml(FILE *, node *);

node *readXml(char *);


#endif /* ifdef XML_H*/
