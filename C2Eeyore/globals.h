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

typedef union {
	int num;
	char name[MAX_TOKEN_LEN + 1];
} STYPE;

extern int lineno;


/***** Syntax tree *****/

typedef enum {Stmt_K, Exp_K, Type_K, Para_K} NodeKind;
typedef enum {If_K, While_K, Assign_K, Def_K, Return_K, Seq_K, OFunc_K} StmtKind;
typedef enum {SOp_K, DOp_K, Const_K, Id_K, Array_K, Func_K} ExpKind;
typedef enum {Int} TypeKind;
typedef enum {Para, Para_def} ParaKind;
typedef enum {NUM, ARRAY, FUNC, FUNC_MAIN} DefKind;
typedef enum {Void, Integer, Boolean} ExpType;
typedef enum {Plus, Minus, Times, Over, Mod, Lt, Gt, Eq, Neq, Not, And, Or} OpType;

#define CHILDREN_NUM 4

typedef struct treeNode
{
	struct treeNode *child[CHILDREN_NUM];
	struct treeNode *sibling;
	int lineno;
	NodeKind nk;
	union {StmtKind stmt; ExpKind exp; TypeKind type; ParaKind para;} kind;
	union {OpType op; int val; char *name; DefKind def; int IfwithElse;} attr;
	ExpType type;
} TreeNode;


#define YYSTYPE TreeNode *

TreeNode *SyntaxTree;
#endif
