#include "globals.h"
#include "util.h"

TreeNode *newStmtNode(StmtKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
		//fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nk = Stmt_K;
		t->kind.stmt = kind;
		t->lineno = lineno;
	}
	return t;
}

TreeNode *newExpNode(ExpKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
		//fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nk = Exp_K;
		t->kind.exp = kind;
		t->lineno = lineno;
		t->type = Void;
	}
	return t;
}

TreeNode *newTypeNode(TypeKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
		//fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nk = Type_K;
		t->kind.type = kind;
		t->lineno = lineno;
		t->type = Void;
	}
	return t;
}

TreeNode *newParaNode(ParaKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
		//fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nk = Para_K;
		t->kind.para = kind;
		t->lineno = lineno;
		t->type = Void;
	}
	return t;
}

char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL) return NULL;
	n = strlen(s) + 1;
	t = malloc(n);
	if (t == NULL);
		//fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
		strcpy(t, s);
	return t;
}

void printTree(TreeNode *tree)
{
	int i;
	while(tree != NULL)
	{
		if (tree->nk == Stmt_K)
		{
			switch (tree->kind.stmt)
			{
				case If_K:
					printf("If\n");
					break;
				case While_K:
					printf("While\n");
					break;
				case Assign_K:
					printf("Assign\n");
					break;
				case Def_K:
					printf("Define\n");

					break;
				case Return_K:
					printf("Return\n");
					break;
				case Seq_K:
					printf("Seq\n");
					break;
				default:
					printf("Unknown ExpNode kind\n");
					break;
			}
		}
		for(i = 0; i < CHILDREN_NUM; i++)
			printTree(tree->child[i]);
		tree = tree->sibling;
	}
}
