#ifndef _UTIL_H_
#define _UTIL_H_

TreeNode *newStmtNode(StmtKind);

TreeNode *newExpNode(ExpKind);

TreeNode *newTypeNode(TypeKind);

TreeNode *newParaNode(ParaKind);

char *copyString(char *);

void printTree(TreeNode *);

#endif
