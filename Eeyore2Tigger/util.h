#ifndef _UTIL_H_
#define _UTIL_H_
#include "graph.h"

extern FILE *Tigger_code;

TreeNode *newFuncNode();

TreeNode *newStmtNode(StmtKind);

TreeNode *newExpNode(ExpKind);

char *copyString(char *);

void printtree(TreeNode *t);

#endif
