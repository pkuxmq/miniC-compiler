%{
#include <string.h>
#include "globals.h"
#include "util.h"
static TreeNode *savedTree;
int yydebug = 1;
int yyerror(char *);
extern int yylex(void);
%}

%token IF ELSE WHILE MAIN RETURN INT_TYPE
%token AND OR EQ NEQ
%token INT ID

%% 
root		: program
	  			{ SyntaxTree = $1; }
			;
program		: main_def
		 		{ $$ = $1; }
		 	| def_stmt ';' program
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| assign_stmt ';' program
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| func_def program
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
			| func_decl program
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
		 	;
func_decl	: type ID '(' def_para ')' ';'
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = FUNC;
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[2] = $4;
				}
		  	;
func_def 	: type ID '(' def_para ')' '{' def_body '}'
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = FUNC;
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[2] = $4;
				  $$->child[3] = $7;
				}
			;
def_body	: def_body func_decl
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
		 	| def_body one_stmt
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
			|	{ $$ = NULL; }
			;
def_para	: type ID
		 		{ $$ = newParaNode(Para_def);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
		 	| type ID ',' def_para
		 		{ $$ = newParaNode(Para_def);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[2] = $4;
				}
			|	{ $$ = NULL; }
			;
main_def	: INT_TYPE MAIN '(' ')' '{' def_body '}'
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = FUNC_MAIN;
				  $$->child[0] = $6;
				}
		 	;
stmt_seq 	: 	{ $$ = NULL; }
		  	| stmt_seq one_stmt
				{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
			;
one_stmt	: stmt
				{ $$ = $1; }
			;
stmt 		: open_stmt
				{ $$ = $1; }
	   		| match_stmt
				{ $$ = $1; }
			;
ifelse_stmt : IF '(' exp ')' match_stmt ELSE match_stmt
				{ $$ = newStmtNode(If_K);
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				  $$->child[2] = $7;
				  $$->attr.IfwithElse = TRUE;
				}
			;
open_stmt 	: if_open
		   		{ $$ = $1; }
			| while_open
				{ $$ = $1; }
			;
if_open 	: IF '(' exp ')' one_stmt
				{ $$ = newStmtNode(If_K);
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				  $$->attr.IfwithElse = FALSE;
				}
			| IF '(' exp ')' match_stmt ELSE open_stmt
				{ $$ = newStmtNode(If_K);
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				  $$->child[2] = $7;
				  $$->attr.IfwithElse = TRUE;
				}
			;
while_open	: WHILE '(' exp ')' open_stmt
				{ $$ = newStmtNode(While_K);
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				}
			;
match_stmt	: ifelse_stmt
		   		{ $$ = $1; }
			| '{' stmt_seq '}'
				{ $$ = $2; }
			| while_stmt
				{ $$ = $1; }
			| assign_stmt ';'
				{ $$ = $1; }
			| def_stmt ';'
				{ $$ = $1; }
			| return_stmt ';'
				{ $$ = $1; }
			| func ';'
				{ $$ = newStmtNode(OFunc_K);
				  $$->child[0] = $1->child[0];
				  $$->child[1] = $1->child[1];
				}
			;
while_stmt 	: WHILE '(' exp ')' match_stmt
				{ $$ = newStmtNode(While_K);
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				}
			;
assign_stmt	: ID '=' exp
				{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| ID '[' exp ']' '=' exp
				{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = newExpNode(Array_K);
				  $$->child[0]->child[0] = $1;
				  $$->child[0]->child[1] = $3;
				  $$->child[0]->type = Integer;
				  $$->child[1] = $6;
				}
			;
def_stmt	: type ID
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = NUM;
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
		 	| type ID '[' INT ']'
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = ARRAY;
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[2] = $4;
				}
			/*| type ID '=' exp*/
			;
return_stmt	: RETURN exp
				{ $$ = newStmtNode(Return_K);
				  $$->child[0] = $2;
				}
			;
exp			: exp OR comp_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Or;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
		  	| exp AND comp_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = And;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
			| comp_exp
				{ $$ = $1; }
			;
comp_exp 	: comp_exp EQ am_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Eq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
	  		| comp_exp NEQ am_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Neq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
			| comp_exp '<' am_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Lt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
			| comp_exp '>' am_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Gt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Boolean;
				}
			| am_exp
				{ $$ = $1; }
			;
am_exp		: am_exp '+' tom_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Plus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
		   	| am_exp '-' tom_exp
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
			| tom_exp
				{ $$ = $1; }
			;
tom_exp		: tom_exp '*' factor
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Times;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
	  		| tom_exp '/' factor
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Over;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
			| tom_exp '%' factor
				{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Mod;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
			| factor
				{ $$ = $1; }
			;
factor		: '(' exp ')'
				{ $$ = $2; }
			| INT
				{ $$ = $1; }
			| ID
				{ $$ = $1; }
			| ID '[' exp ']'
				{ $$ = newExpNode(Array_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->type = Integer;
				}
			| '(' exp ')' '[' exp ']'
				{ $$ = newExpNode(Array_K);
				  $$->child[0] = $2;
				  $$->child[1] = $5;
				  $$->type = Integer;
				}
			| func
				{ $$ = $1; }
			| '-' factor
				{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $2;
				  $$->type = Integer;
				}
			| '!' factor
				{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Not;
				  $$->child[0] = $2;
				  $$->type = Boolean;
				}
			;
func 		: ID '(' para ')'
				{ $$ = newExpNode(Func_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
	   		| ID '(' ')'
				{ $$ = newExpNode(Func_K);
				  $$->child[0] = $1;
				}
	   		;
para 		: exp
	   			{ $$ = newParaNode(Para);
				  $$->child[0] = $1;
				}
			| exp ',' para
	   			{ $$ = newParaNode(Para);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
			;
type 		: INT_TYPE
			   { $$ = newTypeNode(Int);}
	   		;

%% 

int yyerror(char *message)
{
	fprintf(stderr, "error in line %d: %s\n", lineno, message);
	return 0;
}

int myerror(int lineno, char *message)
{
	fprintf(stderr, "error in line %d: %s\n", lineno, message);
	return 0;
}
