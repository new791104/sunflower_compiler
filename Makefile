sunflower: main.o sunflower.tab.o lex.yy.o 
	gcc -o parser main.o sunflower.tab.o lex.yy.o -lfl

main.o: main.c
	gcc -c main.c

lex.yy.o: lex.yy.c sunflower.tab.h
	gcc -c lex.yy.c

lex.yy.c: sunflower.l
	flex sunflower.l

sunflower.tab.o: sunflower.tab.c
	gcc -c sunflower.tab.c

sunflower.tab.c: sunflower.y
	bison sunflower.y




