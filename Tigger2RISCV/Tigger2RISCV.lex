
%{
#include "globals.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
%}

digit		[0-9]
int 		{digit}+
letter		[a-zA-Z_]
identifier	{letter}+{digit}*{letter}*{digit}*
newline		\n
whitespace	[  \t]+
v_var		"v"{int}
t_var		"t"{int}
s_var		"s"{int}
a_var		"a"{int}
label		"l"{int}

%%

{v_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 'v';
				 return VAR;}
{t_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 't';
				 return VAR;}
{s_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 's';
				 return VAR;}
{a_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 'a';
				 return VAR;}
{label}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 'l';
				 return LABEL;}
"f_"{identifier} {yylval = newFuncNode();
				 yylval->attr.func_name = copyString(yytext);
				 return FUNC;}
"end"			{return END;}
"call"			{return CALL;}
"if"			{return IF;}
"goto"			{return GOTO;}
"return"		{return RETURN;}
"store"			{return STORE;}
"load"			{return LOAD;}
"loadaddr"		{return LOADADDR;}
"malloc"		{return MALLOC;}
"=="			{return EQ;}
"!="			{return NEQ;}
"&&" 			{return AND;}
"||"			{return OR;}
"-"{int}		{yylval = newExpNode(Const_K);
				 yylval->attr.val = atoi(yytext);
				 return INT;}
{int}			{yylval = newExpNode(Const_K);
				 yylval->attr.val = atoi(yytext);
				 return INT;}
{newline}		{lineno++;}
{whitespace}	{}
"//"			{ char c;
				  do
				  {
					  c = getchar();
					  if (c == '\n') lineno++;
				  } while (c != '\n');
				}
[\+\-\*\/\=\!\%\>\<\(\)\[\]\{\}\:]	{return yytext[0];}

%%

int yywrap()
{
	return 1;
}
