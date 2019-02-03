%{
#include <string.h>
#include <stdio.h>
#include "globals.h"
#include "util.h"
#include "symtab.h"
#include "graph.h"
int yyerror(const char []);
extern int yylex(void);
TreeNode *SyntaxTree;
extern int func_num;
%}

%token VAR_DEF VAR LABEL IF GOTO
%token FUNC END CALL PARAM RETURN INT
%token AND OR EQ NEQ

%% 
root		: program
	  			{ SyntaxTree = $1; }

program 	: stmt program
		 		{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				  $$->child[0]->set_global_var();
				}
			| func program
		 		{ $$ = newStmtNode(Seq_K);
				  $$->child[0] = $1;
				  $$->child[1] = $2;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				  func_num++;
				}
			| func
		 		{ $$ = $1;
				  func_num++;  
				}
			;

func 		: FUNC '[' INT ']' stmt_seq END FUNC
		 		{ $$ = $1;
				  $$->child[0] = $3;
				  $$->child[1] = $5;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			;

stmt_seq 	: stmt_seq stmt
		 		{
				  	$$ = newStmtNode(Seq_K);
				  	$$->child[0] = $1;
					if ($$->child[0] != NULL)
				  		$$->child[0]->parentnode = $$;
					$$->child[1] = $2;
					$$->child[1]->parentnode = $$;
				}
		  	|  { $$ = NULL; }
			;

stmt 		: VAR_DEF VAR
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = NUM;
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
	   		| VAR_DEF INT VAR
		 		{ $$ = newStmtNode(Def_K);
				  $$->attr.def = ARRAY;
				  $$->child[0] = $3;
				  $$->child[1] = $2;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| LABEL ':'
		 		{ $$ = newStmtNode(Label_K);
				  $$->child[0] = $1;
				  $$->child[0]->parentnode = $$;
				}
			| GOTO LABEL
		 		{ $$ = newStmtNode(Goto_K);
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
			| IF LogicExp GOTO LABEL
		 		{ $$ = newStmtNode(If_K);
				  $$->child[0] = $2;
				  $$->child[1] = $4;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| VAR '=' exp
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| VAR '[' val ']' '=' val
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = newExpNode(Array_K);
				  $$->child[0]->child[0] = $1;
				  $$->child[0]->child[1] = $3;
				  $$->child[0]->child[0]->parentnode = $$->child[0];
				  $$->child[0]->child[1]->parentnode = $$->child[0];
				  $$->child[1] = $6;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| VAR '=' VAR '[' val ']'
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = newExpNode(Array_K);
				  $$->child[1]->child[0] = $3;
				  $$->child[1]->child[1] = $5;
				  $$->child[1]->child[0]->parentnode = $$->child[1];
				  $$->child[1]->child[1]->parentnode = $$->child[1];
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| VAR '=' CALL FUNC
		 		{ $$ = newStmtNode(Assign_K);
				  $$->child[0] = $1;
				  $$->child[1] = newExpNode(CFunc_K);
				  $$->child[1]->child[0] = $4;
				  $$->child[1]->child[0]->parentnode = $$->child[1];
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| CALL FUNC
		 		{ $$ = newStmtNode(OFunc_K);
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
			| PARAM val
		 		{ $$ = newStmtNode(Param_K);
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
			| RETURN val
		 		{ $$ = newStmtNode(Return_K);
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
			;

exp			: val '+' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Plus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '-' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '*' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Times;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '/' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Over;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '%' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Mod;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| LogicExp
			| '-' val
		 		{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Minus;
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
				}
			| val
				{ $$ = $1; }
			;

LogicExp 	: val AND val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = And;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
		  	| val OR val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Or;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '>' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Gt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val '<' val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Lt;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val EQ val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Eq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| val NEQ val
		 		{ $$ = newExpNode(DOp_K);
				  $$->attr.op = Neq;
				  $$->child[0] = $1;
				  $$->child[1] = $3;
				  $$->child[0]->parentnode = $$;
				  $$->child[1]->parentnode = $$;
				}
			| '!' val
		 		{ $$ = newExpNode(SOp_K);
				  $$->attr.op = Not;
				  $$->child[0] = $2;
				  $$->child[0]->parentnode = $$;
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
