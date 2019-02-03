
%{
#include "globals.h"
#include "util.h"
#include "y.tab.h"
	void yyecho() {
		fprintf(stderr, "%s", yytext);
	}
%}

digit		[0-9]
int 		{digit}+
letter		[a-zA-Z]
identifier	{letter}+{digit}*{letter}*{digit}*
newline		\n
whitespace	[  \t]+

%%

"if"			{yyecho();return IF;}
"else"			{yyecho();return ELSE;}
"while"			{yyecho();return WHILE;}
"main"			{yyecho();return MAIN;}
"return"		{yyecho();return RETURN;}
"int"			{yyecho();return INT_TYPE;}
"=="			{yyecho();return EQ;}
"!="			{yyecho();return NEQ;}
"&&" 			{yyecho();return AND;}
"||"			{yyecho();return OR;}
{int}			{yyecho();yylval = newExpNode(Const_K);
				 yylval->attr.val = atoi(yytext);
				 yylval->type = Integer;
				 return INT;}
{identifier}	{yyecho();yylval = newExpNode(Id_K);
				 yylval->attr.name = copyString(yytext);
				 return ID;}
{newline}		{yyecho();lineno++;}
{whitespace}	{yyecho();}
"//"			{ yyecho();char c;
				  do
				  {
					  c = input();
					  if (c == '\n') lineno++;
				  } while (c != '\n');
				}
[\+\-\*\/\=\!\%\>\<\(\)\[\]\{\}\;\,]	{yyecho();return yytext[0];}

%%

int yywrap()
{
	return 1;
}
