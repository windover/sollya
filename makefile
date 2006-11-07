CPPFLAGS=-I/sw/include
LIB=-L/sw/lib
CFLAGS=-O3 -Wall

tools: parser.tab.o lex.yy.o plot.o expression.o infnorm.o pari_utils.o remez.o main.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o
	gcc $(LIB) $(CFLAGS) -o tools lex.yy.o plot.o parser.tab.o expression.o infnorm.o pari_utils.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o external.o main.o -lfl -lmpfi -lpari -lmpfr -lgmp -ldl

parser.tab.o: parser.tab.h parser.tab.c expression.h main.h infnorm.h remez.h chain.h assignment.h taylor.h

lex.yy.o: lex.yy.c expression.h main.h

lex.yy.c: lexer.lex parser.tab.h main.h expression.h
	flex -I lexer.lex

parser.tab.c: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

parser.tab.h: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

plot.o: plot.h plot.c expression.h main.h

expression.o: expression.h expression.c main.h

main.o: plot.h expression.h infnorm.h remez.h main.h main.c assignment.h chain.h

pari_utils.o : pari_utils.h pari_utils.c

remez.o: remez.h remez.c expression.h main.h pari_utils.h

fpminimax.o: fpminimax.h fpminimax.c expression.h main.h

infnorm.o: infnorm.h infnorm.c expression.h main.h chain.h proof.h

chain.o: chain.h chain.c

assignment.o: assignment.h assignment.c

taylor.o: taylor.h taylor.c

double.o: double.h double.c

external.o: external.h external.c expression.h expression.c main.h main.c

integral.o: integral.h integral.c expression.h

proof.o: proof.h proof.c expression.h infnorm.h 

worstcase.o: worstcase.h worstcase.c expression.h 

implement.o: implement.h implement.c expression.h main.h

doc: Manuel_fr.tex
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
	rm -rf tools
	rm -rf Manuel_fr.log Manuel_fr.aux Manuel_fr.dvi Manuel_fr.out Manuel_fr.toc Manuel_fr.pdf 

