INCLUDE=-I/sw/include
LIB=-L/sw/lib

tools: parser.tab.o lex.yy.o plot.o expression.o infnorm.o pari_utils.o remez.o main.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o
	gcc $(LIB) -Wall -g -o tools lex.yy.o plot.o parser.tab.o expression.o infnorm.o pari_utils.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o worstcase.o fpminimax.o implement.o main.o -lfl -lmpfi -lpari -lmpfr -lgmp

parser.tab.o: parser.tab.h parser.tab.c expression.h main.h infnorm.h remez.h chain.h assignment.h taylor.h
	gcc $(INCLUDE) -Wall -g -c parser.tab.c

lex.yy.o: lex.yy.c expression.h main.h
	gcc $(INCLUDE) -Wall -g -c lex.yy.c

lex.yy.c: lexer.lex parser.tab.h main.h expression.h
	flex -I lexer.lex

parser.tab.c: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

parser.tab.h: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

plot.o: plot.h plot.c expression.h main.h
	gcc $(INCLUDE) -g -Wall -c plot.c

expression.o: expression.h expression.c main.h
	gcc $(INCLUDE) -g -Wall -c expression.c

main.o: plot.h expression.h infnorm.h remez.h main.h main.c assignment.h chain.h
	gcc $(INCLUDE) -g -Wall -c main.c

pari_utils.o : pari_utils.h pari_utils.c
	gcc $(INCLUDE) -g -Wall -c pari_utils.c

remez.o: remez.h remez.c expression.h main.h pari_utils.h
	gcc $(INCLUDE) -g -Wall -c remez.c

fpminimax.o: fpminimax.h fpminimax.c expression.h main.h
	gcc $(INCLUDE) -g -Wall -c fpminimax.c


infnorm.o: infnorm.h infnorm.c expression.h main.h chain.h proof.h
	gcc $(INCLUDE) -g -Wall -c infnorm.c

chain.o: chain.h chain.c
	gcc $(INCLUDE) -g -Wall -c chain.c

assignment.o: assignment.h assignment.c
	gcc $(INCLUDE) -g -Wall -c assignment.c

taylor.o: taylor.h taylor.c
	gcc $(INCLUDE) -g -Wall -c taylor.c


double.o: double.h double.c
	gcc $(INCLUDE) -g -Wall -c double.c

integral.o: integral.h integral.c expression.h
	gcc $(INCLUDE) -g -Wall -c integral.c

proof.o: proof.h proof.c expression.h infnorm.h 
	gcc $(INCLUDE) -g -Wall -c proof.c

worstcase.o: worstcase.h worstcase.c expression.h 
	gcc $(INCLUDE) -g -Wall -c worstcase.c

implement.o: implement.h implement.c expression.h main.h
	gcc $(INCLUDE) -g -Wall -c implement.c


doc: Manuel_fr.tex
	latex Manuel_fr.tex
	dvips Manuel_fr.dvi -o Manuel_fr.ps

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf parser.tab.c
	rm -rf parser.tab.h
	rm -rf tools
	rm -rf Manuel_fr.log Manuel_fr.aux Manuel_fr.dvi Manuel_fr.out Manuel_fr.toc