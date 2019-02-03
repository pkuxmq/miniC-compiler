all : RISCV

RISCV : lex yacc util.cpp main.cpp
	g++ -std=c++11 -g -o ../riscv64 lex.yy.c y.tab.c util.cpp main.cpp

lex : Tigger2RISCV.lex yacc
	lex Tigger2RISCV.lex

yacc : Tigger2RISCV.y
	yacc Tigger2RISCV.y -d

clean:
	rm y.tab.c y.tab.h lex.yy.c ../tigger
