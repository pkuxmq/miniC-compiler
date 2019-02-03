#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 8

#define MAX_TOKEN_LEN 80

extern int lineno;

class Var_Info {
public:
	char kind;
	int index;

	Var_Info(char kind, int index);
	Var_Info();

	friend bool operator<(Var_Info v1, Var_Info v2);
};


/***** Syntax tree *****/

typedef enum {Func_K, Stmt_K, Exp_K} NodeKind;
typedef enum {If_K, Assign_K, Def_K, Return_K, Seq_K, OFunc_K, Label_K, Goto_K, Param_K, Load_K, Loadaddr_K, Store_K} StmtKind;
typedef enum {SOp_K, DOp_K, Const_K, Var_K, Array_K, CFunc_K} ExpKind;
typedef enum {Plus, Minus, Times, Over, Mod, Lt, Gt, Eq, Neq, Not, And, Or} OpType;

#define CHILDREN_NUM 4

class TreeNode
{
public:
	TreeNode *child[CHILDREN_NUM];
	int lineno;
	NodeKind nk;
	union {StmtKind stmt; ExpKind exp;} kind;
	union {OpType op; int val; Var_Info Var_info; char *func_name;} attr;
	TreeNode *parentnode;
	bool global;
};


#define YYSTYPE TreeNode *

extern TreeNode *SyntaxTree;

#endif
