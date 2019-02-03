all : Tigger

Tigger : lex yacc util.cpp Bit_set.cpp symtab.cpp graph.cpp convert.cpp liveness.cpp color.cpp rewrite.cpp main.cpp
	g++ -std=c++11 -g -o ../tigger lex.yy.c y.tab.c util.cpp Bit_set.cpp symtab.cpp graph.cpp convert.cpp liveness.cpp color.cpp rewrite.cpp main.cpp

lex : Eeyore2Tigger.lex yacc
	lex Eeyore2Tigger.lex

yacc : Eeyore2Tigger.y
	yacc Eeyore2Tigger.y -d

clean:
	rm y.tab.c y.tab.h lex.yy.c ../tigger
