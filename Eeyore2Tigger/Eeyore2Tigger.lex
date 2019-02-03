
%{
#include "globals.h"
#include "util.h"
#include "symtab.h"
#include "y.tab.h"
#include <stdio.h>
%}

digit		[0-9]
int 		{digit}+
letter		[a-zA-Z_]
identifier	{letter}+{digit}*{letter}*{digit}*
newline		\n
whitespace	[  \t]+
T_var		"T"{int}
t_var		"t"{int}
p_var		"p"{int}
label		"l"{int}

%%

"var"			{return VAR_DEF;}
{T_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 'T';
				 var_num[0] = var_num[0] > yylval->attr.Var_info.index ? var_num[0] : yylval->attr.Var_info.index;
				 return VAR;}
{t_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 't';
				 var_num[1] = var_num[1] > yylval->attr.Var_info.index ? var_num[1] : yylval->attr.Var_info.index;
				 return VAR;}
{p_var}			{yylval = newExpNode(Var_K);
				 yylval->attr.Var_info.index = atoi(yytext + 1);
				 yylval->attr.Var_info.kind = 'p';
				 var_num[2] = var_num[2] > yylval->attr.Var_info.index ? var_num[2] : yylval->attr.Var_info.index;
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
"param"			{return PARAM;}
"if"			{return IF;}
"goto"			{return GOTO;}
"return"		{return RETURN;}
"=="			{return EQ;}
"!="			{return NEQ;}
"&&" 			{return AND;}
"||"			{return OR;}
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
