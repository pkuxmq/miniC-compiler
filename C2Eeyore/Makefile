all : Eeyore

Eeyore : lex yacc Egen.c symtab.c util.c Analyze.c main.c
	gcc -g -o ../eeyore lex.yy.c y.tab.c symtab.c util.c Analyze.c Egen.c main.c

lex : C2Eeyore.lex yacc
	lex C2Eeyore.lex

yacc : C2Eeyore.y
	yacc C2Eeyore.y -d

clean:
	rm y.tab.c y.tab.h lex.yy.c ../eeyore
