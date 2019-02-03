#include "globals.h"
#include "graph.h"
#include "util.h"
#include "symtab.h"
using std::max;

TreeNode *newFuncNode()
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->nk = Func_K;
		t->lineno = lineno;
		t->parentnode = NULL;
	}
	return t;
}

TreeNode *newStmtNode(StmtKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->nk = Stmt_K;
		t->kind.stmt = kind;
		t->lineno = lineno;
		t->parentnode = NULL;
	}
	return t;
}

TreeNode *newExpNode(ExpKind kind)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if (t == NULL);
	else
	{
		for (i = 0; i < CHILDREN_NUM; i++)
			t->child[i] = NULL;
		t->nk = Exp_K;
		t->kind.exp = kind;
		t->lineno = lineno;
		t->parentnode = NULL;
	}
	return t;
}

char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL) return NULL;
	n = strlen(s) + 1;
	t = new char[n];
	if (t == NULL);
	else
		strcpy(t, s);
	return t;
}

void TreeNode::set_global_var()
{
	if (kind.stmt == Def_K) {
		global_var[child[0]->attr.Var_info] = true;
		global_var_num = max(global_var_num, child[0]->attr.Var_info.index);
	}
}

void printtree(TreeNode *t)
{
	if (t == NULL)
		return;
	if (t->nk == Stmt_K) {
		if (t->kind.stmt == Seq_K) {
			printtree(t->child[0]);
			printtree(t->child[1]);
		}
		else {
			if (t->kind.stmt == If_K) {
				fprintf(Tigger_code, "if ");
				printtree(t->child[0]);
				fprintf(Tigger_code, "goto ");
				printtree(t->child[1]);
				fprintf(Tigger_code, "\n");
			}
			else if (t->kind.stmt == Assign_K) {
				if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == Var_K && t->child[0]->attr.Var_info == t->child[1]->attr.Var_info)
					return;
				printtree(t->child[0]);
				fprintf(Tigger_code, "= ");
				printtree(t->child[1]);
				fprintf(Tigger_code, "\n");
			}
			else if (t->kind.stmt == Def_K) {
				printtree(t->child[0]);
				if (t->attr.def == ARRAY)
					fprintf(Tigger_code, "= malloc %d\n", t->child[1]->attr.val);
				else
					fprintf(Tigger_code, "= 0\n");
			}
			else if (t->kind.stmt == Return_K) {
				fprintf(Tigger_code, "return ");
				printtree(t->child[0]);
				fprintf(Tigger_code, "\n");
			}
			else if (t->kind.stmt == OFunc_K) {
				fprintf(Tigger_code, "call %s\n", t->child[0]->attr.func_name);
			}
			else if (t->kind.stmt == Label_K) {
				fprintf(Tigger_code, "l%d:\n", t->child[0]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Goto_K) {
				fprintf(Tigger_code, "goto l%d\n", t->child[0]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Param_K) {
				fprintf(Tigger_code, "param %c%d\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Load_K) {
				if (t->child[0]->kind.exp == Var_K)
					fprintf(Tigger_code, "load %c%d %c%d\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, t->child[1]->attr.Var_info.kind, t->child[1]->attr.Var_info.index);
				else
					fprintf(Tigger_code, "load %d %c%d\n", t->child[0]->attr.val, t->child[1]->attr.Var_info.kind, t->child[1]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Loadaddr_K) {
				if (t->child[0]->kind.exp == Var_K)
					fprintf(Tigger_code, "loadaddr %c%d %c%d\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, t->child[1]->attr.Var_info.kind, t->child[1]->attr.Var_info.index);
				else
					fprintf(Tigger_code, "loadaddr %d %c%d\n", t->child[0]->attr.val, t->child[1]->attr.Var_info.kind, t->child[1]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Store_K) {
				fprintf(Tigger_code, "store %c%d %d\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, t->child[1]->attr.val);
			}
		}
	}
	else if (t->nk == Exp_K) {
		if (t->kind.exp == SOp_K) {
			if (t->attr.op == Minus)
				fprintf(Tigger_code, "-");
			else if (t->attr.op == Not)
				fprintf(Tigger_code, "!");
			printtree(t->child[0]);
		}
		else if (t->kind.exp == DOp_K) {
			printtree(t->child[0]);
			switch(t->attr.op) {
				case Plus:
					fprintf(Tigger_code, "+ ");
					break;
				case Minus:
					fprintf(Tigger_code, "- ");
					break;
				case Times:
					fprintf(Tigger_code, "* ");
					break;
				case Over:
					fprintf(Tigger_code, "/ ");
					break;
				case Mod:
					fprintf(Tigger_code, "%% ");
					break;
				case Lt:
					fprintf(Tigger_code, "< ");
					break;
				case Gt:
					fprintf(Tigger_code, "> ");
					break;
				case Eq:
					fprintf(Tigger_code, "== ");
					break;
				case Neq:
					fprintf(Tigger_code, "!= ");
					break;
				case And:
					fprintf(Tigger_code, "&& ");
					break;
				case Or:
					fprintf(Tigger_code, "|| ");
					break;
			}
			printtree(t->child[1]);
		}
		else if (t->kind.exp == Const_K) {
			fprintf(Tigger_code, "%d ", t->attr.val);
		}
		else if (t->kind.exp == Var_K) {
			//if (t->attr.Var_info.kind == 'c')
			//	t->attr.Var_info.kind = 't';
			fprintf(Tigger_code, "%c%d ", t->attr.Var_info.kind, t->attr.Var_info.index);
		}
		else if (t->kind.exp == Array_K) {
			if (t->child[1]->kind.exp == Var_K) {
			//	if (t->child[1]->attr.Var_info.kind == 'c')
			//		t->child[1]->attr.Var_info.index = 't';
				fprintf(Tigger_code, "%c%d [%c%d] ", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, t->child[1]->attr.Var_info.kind, t->child[1]->attr.Var_info.index);
			}
			else
				fprintf(Tigger_code, "%c%d [%d] ", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, t->child[1]->attr.val);

		}
		else if (t->kind.exp == CFunc_K) {
			fprintf(Tigger_code, "call %s ", t->child[0]->attr.func_name);
		}
	}
	else if (t->nk == Func_K) {
		fprintf(Tigger_code, "%s [%d]", t->attr.func_name, t->child[0]->attr.val);
		if (t->child[2] != NULL)
			fprintf(Tigger_code, " [%d]", t->child[2]->attr.val);
		fprintf(Tigger_code, "\n");
		printtree(t->child[1]);
		fprintf(Tigger_code, "end %s\n", t->attr.func_name);
	}
}
