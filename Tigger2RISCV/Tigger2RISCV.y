%{
#include <string.h>
#include <stdio.h>
#include "globals.h"
#include "util.h"
int yyerror(const char []);
extern int yylex(void);
TreeNode *SyntaxTree;
%}

%token VAR LABEL IF GOTO STORE LOAD LOADADDR MALLOC
%token FUNC END CALL RETURN INT
%token AND OR EQ NEQ

%% 
root		: program
	  			{ SyntaxTree = $1; }

program 	: stmt program
		 		{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $1->global = true;
				}
			| func program
		 		{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				}
			| func
		 		{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				}
			;

func 		: FUNC '[' INT ']' '[' INT ']' stmt_seq END FUNC
		 		{ $$ = $1;
				  $$->child[0] = $3;
				  $$->child[1] = $6;
				  $$->child[2] = $8;
				}
			;

stmt_seq 	: stmt_seq stmt
		 		{
				  	$$ = newStmtNode(Seq_K);
				  	$$->child[0] = $1;
					$$->child[1] = $2;
				}
		  	|  { $$ = NULL; }
			;

stmt 		: LABEL ':'
		 		{ $$ = newStmtNode(Label_K);
				  $$->child[0] = $1;
				}
			| GOTO LABEL
		 		{ $$ = newStmtNode(Goto_K);
				  $$->child[0] = $2;
				}
			| IF LogicExp GOTO LABEL
		 		{ $$ = newStmtNode(If_K);
				  $$->child[0] = $2;
				  $$->child[1] = $4;
				}
			| VAR '=' exp
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| VAR '=' MALLOC INT
				{ $$ = newStmtNode(Def_K);
				  $$->child[0] = $1;
				  $$->child[1] = $4;
				}
			| VAR '[' val ']' '=' val
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = newExpNode(Array_K);
				  $$->child[0]->child[0] = $1;
				  $$->child[0]->child[1] = $3;
				  $$->child[1] = $6;
				}
			| VAR '=' VAR '[' val ']'
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = newExpNode(Array_K);
				  $$->child[1]->child[0] = $3;
				  $$->child[1]->child[1] = $5;
				}
			| CALL FUNC
		 		{ $$ = newStmtNode(OFunc_K);
				  $$->child[0] = $2;
				}
			| RETURN
		 		{ $$ = newStmtNode(Return_K); }
			| STORE VAR INT
				{ $$ = newStmtNode(Store_K);
				  $$->child[0] = $2;
				  $$->child[1] = $3;
				}
			| LOAD INT VAR
				{ $$ = newStmtNode(Load_K);
				  $$->child[0] = $2;
				  $$->child[1] = $3;
				}
			| LOADADDR INT VAR
				{ $$ = newStmtNode(Loadaddr_K);
				  $$->child[0] = $2;
				  $$->child[1] = $3;
				}
			| LOAD VAR VAR
				{ $$ = newStmtNode(Load_K);
				  $$->child[0] = $2;
				  $$->child[1] = $3;
				}
			| LOADADDR VAR VAR
				{ $$ = newStmtNode(Loadaddr_K);
				  $$->child[0] = $2;
				  $$->child[1] = $3;
				}
			;

exp			: val '+' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Plus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '-' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '*' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Times;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '/' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Over;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '%' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Mod;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| LogicExp
			| '-' val
		 		{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $2;
				}
			| val
				{ $$ = $1; }
			;

LogicExp 	: val AND val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = And;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
		  	| val OR val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Or;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '>' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Gt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val '<' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Lt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val EQ val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Eq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| val NEQ val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Neq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				}
			| '!' val
		 		{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Not;
				  $$->child[0] = $2;
				}
			;

val 		: VAR
				{ $$ = $1; }
	  		| INT
				{ $$ = $1; }
			;

%% 

int yyerror(const char message[])
{
	fprintf(stderr, "error in line %d: %s\n", lineno, message);
	return 0;
}
