#include "rewrite.h"

static int stack_size;
static map<int, int> spillednode_index;
static map<int, int> regs_stackpos;

static Bit_set **func_regs;

void rewritefunc(TreeNode *t);
void rewriteseq(TreeNode *t);

void RewriteProgram(TreeNode *t)
{
	spillednode_index.clear();
	regs_stackpos.clear();
	while (t != NULL)
	{
		if (t->nk == Func_K)
		{
			rewritefunc(t);
			t = t->child[1];
		}
		else if (t->child[0]->nk != Func_K)
			t = t->child[1];
		else
		{
			rewritefunc(t->child[0]);
			t = t->child[1];
		}
	}
}

void rewritefunc(TreeNode *t)
{
	stack_size = t->child[2]->attr.val;
	rewriteseq(t->child[1]);
	t->child[2]->attr.val = stack_size;
}

void add_load_instr(TreeNode *t, Var_Info v, bool array)
{
	TreeNode *p = t->parentnode->parentnode;
	p->child[1] = newStmtNode(Seq_K);
	p->child[1]->parentnode = p;
	p->child[1]->child[1] = t->parentnode;
	t->parentnode->parentnode = p->child[1];

	TreeNode *prev_load;
	if (!array)
		prev_load = newStmtNode(Load_K);
	else
		prev_load = newStmtNode(Loadaddr_K);
	p->child[1]->child[0] = prev_load;
	prev_load->parentnode = p->child[1];

	if (spillednode_index.find(var_index[v]) == spillednode_index.end())
		spillednode_index[var_index[v]] = stack_size++;

	prev_load->child[0] = newExpNode(Const_K);
	prev_load->child[1] = newExpNode(Var_K);
	prev_load->child[0]->parentnode = prev_load;
	prev_load->child[1]->parentnode = prev_load;
	prev_load->child[0]->attr.val = spillednode_index[var_index[v]];
	prev_load->child[1]->attr.Var_info = v;
}

void add_store_instr(TreeNode *t, Var_Info v)
{
	TreeNode *p = t->parentnode, *n = p->child[1];
	p->child[1] = newStmtNode(Seq_K);
	p->child[1]->parentnode = p;
	p->child[1]->child[1] = n;
	n->parentnode = p->child[1];

	TreeNode *post_store = newStmtNode(Store_K);
	p->child[1]->child[0] = post_store;
	post_store->parentnode = p->child[1];

	if (spillednode_index.find(var_index[v]) == spillednode_index.end())
		spillednode_index[var_index[v]] = stack_size++;

	post_store->child[1] = newExpNode(Const_K);
	post_store->child[0] = newExpNode(Var_K);
	post_store->child[1]->parentnode = post_store;
	post_store->child[0]->parentnode = post_store;
	post_store->child[1]->attr.val = spillednode_index[var_index[v]];
	post_store->child[0]->attr.Var_info = v;
}

bool inspillset(int n)
{
	set<int>::iterator iter = spilledNodes.find(n);
	if (iter == spilledNodes.end())
		return false;
	else
		return true;
}

void rewriteseq(TreeNode *t)
{
	if (t == NULL)
		return;

	if (t->nk == Stmt_K)
	{
		if (t->kind.stmt == Seq_K)
		{
			rewriteseq(t->child[0]);
			rewriteseq(t->child[1]);
		}
		else if (t->kind.stmt == If_K)
		{
			rewriteseq(t->child[0]);
		}
		else if (t->kind.stmt == Assign_K)
		{
			if (t->child[1]->kind.exp == Array_K)
			{
				if (inspillset(var_index[t->child[1]->child[0]->attr.Var_info]))
					add_load_instr(t, t->child[1]->child[0]->attr.Var_info,
							true);
			}
			else if (t->child[1]->kind.exp == Var_K)
			{
				if (inspillset(var_index[t->child[1]->attr.Var_info]))
					add_load_instr(t, t->child[1]->attr.Var_info,
							false);
			}
			else if (t->child[1]->kind.exp == Const_K)
				;
			else
				rewriteseq(t->child[1]);

			if (t->child[0]->kind.exp == Var_K &&
					inspillset(var_index[t->child[0]->attr.Var_info]))
				add_store_instr(t, t->child[0]->attr.Var_info);
		}
	}
	else if (t->nk == Exp_K)
	{
		if (t->child[0]->kind.exp == Var_K &&
				inspillset(var_index[t->child[0]->attr.Var_info]))
			add_load_instr(t->parentnode, t->child[0]->attr.Var_info, false);
		if (t->child[1] != NULL && t->child[1]->kind.exp == Var_K &&
				inspillset(var_index[t->child[1]->attr.Var_info]))
			add_load_instr(t->parentnode, t->child[1]->attr.Var_info, false);
	}
}

void alloc(TreeNode *t)
{
	if (t == NULL)
		return;

	if (t->kind.exp == Var_K)
	{
		if (var_index.find(t->attr.Var_info) != var_index.end())
		{
			int index = var_index[t->attr.Var_info];
			if (!cgraph->precolored[index])
			{
				int reg = cgraph->color[index];
				if (reg <= 11)
				{
					t->attr.Var_info.kind = 's';
					t->attr.Var_info.index = reg;
				}
				else if (reg <= 18)
				{
					t->attr.Var_info.kind = 't';
					t->attr.Var_info.index = reg - 12;
				}
				else
				{
					t->attr.Var_info.kind = 'a';
					t->attr.Var_info.index = reg - 19;
				}
			}
		}
	}

	alloc(t->child[0]);
	alloc(t->child[1]);
}

void finalchange(TreeNode *t)
{
	if (t == NULL)
		return;
	/*
	   if (t->nk == Stmt_K && t->kind.stmt == Assign_K)
	   {
	   if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == Var_K &&
	   t->child[0]->attr.Var_info == t->child[1]->attr.Var_info)
	   {
	   t->parentnode->parentnode = t->parentnode->child[1];
	   if (t->parentnode->child[1] != NULL)
	   t->parentnode->child[1]->parentnode = t->parentnode->parentnode;
	   free(t->parentnode);
	   free(t);
	   }
	   else
	   {
	   finalchange(t->child[0]);
	   finalchange(t->child[1]);
	   }
	   }*/
	if (t->nk == Exp_K && t->kind.exp == Var_K)
	{
		if (t->attr.Var_info.kind == 'T')
			t->attr.Var_info.kind = 'v';
	}
	else
	{
		finalchange(t->child[0]);
		finalchange(t->child[1]);
	}
}

void get_regs(TreeNode *t, int index) {
	if (t == NULL)
		return;

	if (t->nk == Exp_K && t->kind.exp == Var_K) {
		char c = t->attr.Var_info.kind;
		int x = t->attr.Var_info.index;
		if (c == 's')
			func_regs[index]->set_bit(x, 1);
		else if (c == 't') {
			func_regs[index]->set_bit(x + 12, 1);
		}
		else if (c == 'a') {
			func_regs[index]->set_bit(x + 19, 1);
		}
	}
	else {
		get_regs(t->child[0], index);
		get_regs(t->child[1], index);
	}
}

void get_func_regs(TreeNode *t) {
	if (func_regs != NULL) {
		for (int i = 0; i < func_num; i++)
			delete func_regs[i];
	}
	else
		func_regs = new Bit_set *[func_num];
	for (int i = 0; i < func_num; i++) {
		func_regs[i] = new Bit_set(27);
	}

	int tmp = 0;
	while (t != NULL) {
		if (t->nk == Func_K) {
			get_regs(t, tmp++);
		}
		else if (t->child[0]->nk == Func_K) {
			get_regs(t->child[0], tmp++);
		}
		t = t->child[1];
	}
}


void add_func_reg_store(TreeNode *t, int pos, Var_Info var) {
	TreeNode *prev_seq = t->child[1];
	t->child[1] = newStmtNode(Seq_K);
	t->child[1]->parentnode = t;
	t->child[1]->child[1] = prev_seq;
	if (prev_seq != NULL)
	prev_seq->parentnode = t->child[1];

	TreeNode *store_instr = newStmtNode(Store_K);
	t->child[1]->child[0] = store_instr;
	store_instr->parentnode = t->child[1];

	store_instr->child[0] = newExpNode(Var_K);
	store_instr->child[1] = newExpNode(Const_K);
	store_instr->child[0]->parentnode = store_instr;
	store_instr->child[1]->parentnode = store_instr;

	store_instr->child[0]->attr.Var_info = var;
	store_instr->child[1]->attr.val = pos;
}

void add_func_reg_load(TreeNode *t, int pos, Var_Info var) {
	TreeNode *prev_seq = t->child[1];
	t->child[1] = newStmtNode(Seq_K);
	t->child[1]->parentnode = t;
	t->child[1]->child[1] = prev_seq;
	if (prev_seq != NULL)
	prev_seq->parentnode = t->child[1];

	TreeNode *load_instr = newStmtNode(Load_K);
	t->child[1]->child[0] = load_instr;
	load_instr->parentnode = t->child[1];

	load_instr->child[1] = newExpNode(Var_K);
	load_instr->child[0] = newExpNode(Const_K);
	load_instr->child[0]->parentnode = load_instr;
	load_instr->child[1]->parentnode = load_instr;

	load_instr->child[1]->attr.Var_info = var;
	load_instr->child[0]->attr.val = pos;
}

void save_regs_in_func(TreeNode *t, int index, int pos, int &stack) {
	if (t == NULL)
		return;

	int pos_tmp = pos;
	if (t->nk == Stmt_K && t->kind.stmt == Return_K) {
		for (int i = 0; i < 12; i++) {
			if ((*func_regs[index])[i]) {
				add_func_reg_load(t->parentnode->parentnode, pos_tmp++, Var_Info('s', i));
			}
		}
	}
	else if (t->nk == Stmt_K && t->kind.stmt == OFunc_K) {
		for (int i = 0; i < 7; i++) {
			if ((*func_regs[index])[i + 12]) {
				if (regs_stackpos.find(i + 12) == regs_stackpos.end())
					regs_stackpos[i + 12] = stack++;
				add_func_reg_store(t->parentnode->parentnode, regs_stackpos[i + 12], Var_Info('t', i));
				add_func_reg_load(t->parentnode->child[1], regs_stackpos[i + 12], Var_Info('t', i));
			}
		}
		for (int i = 1; i < 8; i++) {
			if ((*func_regs[index])[i + 19]) {
				if (regs_stackpos.find(i + 19) == regs_stackpos.end())
					regs_stackpos[i + 19] = stack++;
				add_func_reg_store(t->parentnode->parentnode, regs_stackpos[i + 19], Var_Info('a', i));
				add_func_reg_load(t->parentnode->child[1], regs_stackpos[i + 19], Var_Info('a', i));
			}
		}
	}
	else {
		save_regs_in_func(t->child[0], index, pos, stack);
		save_regs_in_func(t->child[1], index, pos, stack);
	}
}

void save_regs(TreeNode *t) {
	get_func_regs(t);
	int tmp = 0;
	while(t != NULL) {
		TreeNode *stmt;
		if (t->nk == Func_K)
			stmt = t;
		else
	   		stmt = t->child[0];
		if (stmt->nk == Func_K && tmp < func_num) {
			int regs_num = 0, pos = stmt->child[2]->attr.val;
			regs_stackpos.clear();
			for (int i = 0; i < 12; i++) {
				if ((*func_regs[tmp])[i]) {
					add_func_reg_store(stmt, pos++, Var_Info('s', i));
					regs_num++;
					regs_stackpos[i] = pos - 1;
				}
			}
			stmt->child[2]->attr.val += regs_num;

			save_regs_in_func(stmt->child[1], tmp, stmt->child[2]->attr.val - regs_num, stmt->child[2]->attr.val);
			tmp++;
		}
		t = t->child[1];
	}
}
