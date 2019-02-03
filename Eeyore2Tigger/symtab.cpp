#include "symtab.h"

map<Var_Info, bool> global_var;
map<Var_Info, int> array_in_func;
map<Var_Info, int> var_index;
map<int, Var_Info> index_var;
int var_num[3] = {0}, global_var_num = 0;
int VAR_NUM;
int func_num = 0;

static int index_num;

Var_Info::Var_Info(char kind, int index)
{
    this->kind = kind;
    this->index = index;
}

Var_Info::Var_Info() {}

bool operator<(Var_Info v1, Var_Info v2)
{
    if (v1.kind == v2.kind)
        return v1.index < v2.index;
    return v1.kind < v2.kind;
}

bool operator==(Var_Info v1, Var_Info v2)
{
    return v1.kind == v2.kind && v1.index == v2.index;
}

bool operator!=(Var_Info v1, Var_Info v2)
{
    return v1.kind != v2.kind || v1.index != v2.index;
}

void update(TreeNode *t);
void update_var_index(TreeNode *SyntaxTree)
{
    var_index.clear();
	index_var.clear();
    VAR_NUM = 0;
    index_num = 0;
    update(SyntaxTree);
}

void update(TreeNode *t)
{
    if (t == NULL)
        return;

    if (t->nk == Exp_K && t->kind.exp == Var_K)
    {
		//printf("updating: %c%d\n", t->attr.Var_info.kind, t->attr.Var_info.index);
		if (t->attr.Var_info.kind == 'l')
			return;
        Var_Info tmp = t->attr.Var_info;
		//if (t->parentnode->nk == Stmt_K && t->parentnode->kind.stmt == Def_K)
		if (global_var[tmp])
			return;
        map<Var_Info, int>::iterator iter = var_index.find(tmp);
        if (iter == var_index.end())
        {
            var_index[tmp] = index_num++;
			index_var[var_index[tmp]] = tmp;
            VAR_NUM++;
        }
    }
    else
    {
        update(t->child[0]);
        update(t->child[1]);
    }
}
