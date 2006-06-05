tools: parser.tab.o lex.yy.o plot.o expression.o infnorm.o remez.o main.o chain.o double.o assignment.o taylor.o integral.o proof.o
	gcc -Wall -g -o tools lex.yy.o plot.o parser.tab.o expression.o infnorm.o remez.o chain.o double.o assignment.o taylor.o integral.o proof.o main.o -lfl -lmpfi -lpari -lmpfr -lgmp

parser.tab.o: parser.tab.h parser.tab.c expression.h main.h infnorm.h remez.h chain.h assignment.h taylor.h
	gcc -Wall -g -c parser.tab.c

lex.yy.o: lex.yy.c expression.h main.h
	gcc -Wall -g -c lex.yy.c

lex.yy.c: lexer.lex parser.tab.h main.h expression.h
	flex -I lexer.lex

parser.tab.c: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

parser.tab.h: parser.y expression.h infnorm.h remez.h main.h
	bison -d parser.y

plot.o: plot.h plot.c expression.h main.h
	gcc -g -Wall -c plot.c

expression.o: expression.h expression.c main.h
	gcc -g -Wall -c expression.c

main.o: plot.h expression.h infnorm.h remez.h main.h main.c assignment.h chain.h
	gcc -g -Wall -c main.c

remez.o: remez.h remez.c expression.h main.h
	gcc -g -Wall -c remez.c

infnorm.o: infnorm.h infnorm.c expression.h main.h chain.h proof.h
	gcc -g -Wall -c infnorm.c

chain.o: chain.h chain.c
	gcc -g -Wall -c chain.c

assignment.o: assignment.h assignment.c
	gcc -g -Wall -c assignment.c

taylor.o: taylor.h taylor.c
	gcc -g -Wall -c taylor.c


double.o: double.h double.c
	gcc -g -Wall -c double.c

integral.o: integral.h integral.c expression.h
	gcc -g -Wall -c integral.c

proof.o: proof.h proof.c expression.h infnorm.h 
	gcc -g -Wall -c proof.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf parser.tab.c
	rm -rf parser.tab.h
	rm -rf tools
