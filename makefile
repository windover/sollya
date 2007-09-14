LIB_XML2=`xml2-config --libs || echo "-L/usr/lib -lxml2 -lz -lpthread -lm"`
CPPFLAGS_XML2=`xml2-config --cflags || echo "-I/usr/include/libxml2"`

CPPFLAGS=-I/sw/include -I/home/njourd01/work-cvs/mpfi-1.3.4-RC3/src -rdynamic
LIB=-L/sw/lib -L/home/njourd01/work-cvs/mpfi-1.3.4-RC3/src
CFLAGS=-fPIC -Wall -g

all: tools libtools.so libtools.a

libtools.a: parser.tab.o lex.yy.o plot.o miniparser.tab.o lex.miniyy.o expression.o infnorm.o pari_utils.o remez.o general.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o 
	ar cru libtools.a lex.yy.o plot.o miniparser.tab.o lex.miniyy.o parser.tab.o expression.o infnorm.o pari_utils.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o
	ranlib libtools.a

libtools.so: parser.tab.o lex.yy.o plot.o miniparser.tab.o lex.miniyy.o expression.o infnorm.o pari_utils.o remez.o general.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o 
	gcc $(LIB) $(CFLAGS) -Wl,-export-dynamic -shared -o libtools.so lex.yy.o plot.o miniparser.tab.o lex.miniyy.o parser.tab.o expression.o infnorm.o pari_utils.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o -lfl -lmpfi -lpari -lmpfr -lgmp -ldl $(LIB_XML2)

tools: parser.tab.o lex.yy.o plot.o miniparser.tab.o lex.miniyy.o expression.o infnorm.o pari_utils.o remez.o general.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o main.o
	gcc $(LIB) $(CFLAGS) -Wl,-export-dynamic -o tools lex.yy.o plot.o miniparser.tab.o lex.miniyy.o parser.tab.o expression.o infnorm.o pari_utils.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o library.o execute.o xml.o general.o main.o -lfl -lmpfi -lpari -lmpfr -lgmp -ldl $(LIB_XML2)

parser.tab.o: parser.tab.h parser.tab.c expression.h general.h infnorm.h remez.h chain.h assignment.h taylor.h

lex.yy.o: lex.yy.c expression.h general.h

lex.yy.c: lexer.lex parser.tab.h general.h expression.h
	flex -I lexer.lex

parser.tab.c: parser.y expression.h infnorm.h remez.h general.h
	bison -d parser.y

parser.tab.h: parser.y expression.h infnorm.h remez.h general.h
	bison -d parser.y

plot.o: plot.h plot.c expression.h general.h

library.o: library.h library.c expression.h general.h chain.h 

expression.o: expression.h expression.c general.h miniparser.tab.h miniparser.tab.c library.h

general.o: plot.h expression.h infnorm.h remez.h general.h general.c assignment.h chain.h

main.o: main.h main.c general.h general.c

pari_utils.o : pari_utils.h pari_utils.c

remez.o: remez.h remez.c expression.h general.h pari_utils.h

fpminimax.o: fpminimax.h fpminimax.c expression.h general.h

infnorm.o: infnorm.h infnorm.c expression.h general.h chain.h proof.h

chain.o: chain.h chain.c

assignment.o: assignment.h assignment.c

taylor.o: taylor.h taylor.c

double.o: double.h double.c

external.o: external.h external.c expression.h expression.c general.h general.c

integral.o: integral.h integral.c expression.h

proof.o: proof.h proof.c expression.h infnorm.h 

worstcase.o: worstcase.h worstcase.c expression.h 

implement.o: implement.h implement.c expression.h general.h

execute.o: execute.h execute.c expression.h general.h

xml.o: xml.h xml.c expression.h general.h
	cc $(CFLAGS) $(CPPFLAGS) -c -o xml.o $(CPPFLAGS_XML2) xml.c


lex.miniyy.c: minilexer.lex miniparser.tab.h general.h expression.h
	flex -I -Pminiyy minilexer.lex

miniparser.tab.c: miniparser.y expression.h general.h double.h
	bison -d -p miniyy miniparser.y

miniparser.tab.h: miniparser.y expression.h general.h double.h
	bison -d -p miniyy miniparser.y

miniparser.tab.o: miniparser.tab.h miniparser.tab.c expression.h general.h double.h

lex.miniyy.o: lex.miniyy.c expression.h general.h



doc: Manuel_fr.tex
	latex Manuel_fr.tex
	latex Manuel_fr.tex
	dvips Manuel_fr.dvi -o Manuel_fr.ps

pdf: Manuel_fr.tex
	latex Manuel_fr.tex
	pdflatex Manuel_fr.tex


clean:
	rm -rf *~
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf parser.tab.c
	rm -rf parser.tab.h
	rm -rf miniparser.tab.h
	rm -rf miniparser.tab.c
	rm -rf lex.miniyy.c
	rm -rf tools
	rm -rf Manuel_fr.log Manuel_fr.aux Manuel_fr.dvi Manuel_fr.out Manuel_fr.toc Manuel_fr.pdf Manuel_fr.ps

