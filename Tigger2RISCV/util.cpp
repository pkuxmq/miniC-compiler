#include "globals.h"
#include "util.h"
#include <map>
using std::map;

extern FILE* RISCV_code;

static map<Var_Info, Var_Info> var_var;
static int func_stack_size;

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
		t->global = false;
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
		t->global = false;
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
		t->global = false;
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

Var_Info::Var_Info(char kind, int index) {
	this->kind = kind;
	this->index = index;
}

Var_Info::Var_Info() {}

bool operator<(Var_Info v1, Var_Info v2) {
	if (v1.kind < v2.kind)
		return true;
	else if (v1.kind > v2.kind)
		return false;
	else if (v1.index < v2.index)
		return true;
	else
		return false;
}

void set_var() {
	for (int i = 0; i < 12; i++) {
		if (i < 2)
			var_var[Var_Info('s', i)] = Var_Info('x', 8 + i);
		else
			var_var[Var_Info('s', i)] = Var_Info('x', 16 + i);
	}

	for (int i = 0; i < 7; i++) {
		if (i < 3)
			var_var[Var_Info('t', i)] = Var_Info('x', 5 + i);
		else
			var_var[Var_Info('t', i)] = Var_Info('x', 25 + i);
	}

	for (int i = 0; i < 8; i++)
		var_var[Var_Info('a', i)] = Var_Info('x', 10 + i);
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
				Var_Info x1 = var_var[t->child[0]->child[0]->attr.Var_info];
			    Var_Info x2 = var_var[t->child[0]->child[1]->attr.Var_info];
				Var_Info x3 = t->child[1]->attr.Var_info;
				switch (t->child[0]->attr.op) {
					case Lt:
						fprintf(RISCV_code, "	blt %c%d,%c%d,.%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
						break;
					case Gt:
						fprintf(RISCV_code, "	bgt %c%d,%c%d,.%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
						break;
					case Eq:
						fprintf(RISCV_code, "	beq %c%d,%c%d,.%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
						break;
					case Neq:
						fprintf(RISCV_code, "	bne %c%d,%c%d,.%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
						break;
					default: ;
				}
			}
			else if (t->kind.stmt == Assign_K) {
				if (t->global) {
					fprintf(RISCV_code, "	.global %c%d\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "	.section .sdata\n");
					fprintf(RISCV_code, "	.align 2\n");
					fprintf(RISCV_code, "	.type %c%d, @object\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "	.size %c%d, 4\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "%c%d:\n", t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "	.word 0\n");
					fprintf(RISCV_code, "\n\n");
				}
				else if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == Const_K) {
					fprintf(RISCV_code, "	li %c%d,%d\n", var_var[t->child[0]->attr.Var_info].kind, var_var[t->child[0]->attr.Var_info].index, t->child[1]->attr.val);
				}
				else if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == Var_K) {
					fprintf(RISCV_code, "	mv %c%d,%c%d\n", var_var[t->child[0]->attr.Var_info].kind, var_var[t->child[0]->attr.Var_info].index, var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index);
				}
				else if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == SOp_K) {
					Var_Info x1 = var_var[t->child[0]->attr.Var_info], x2 = var_var[t->child[1]->child[0]->attr.Var_info];
					if (t->child[1]->attr.op == Minus)
						fprintf(RISCV_code, "	sub %c%d,x0,%c%d\n", x1.kind, x1.index, x2.kind, x2.index);
					else if (t->child[1]->attr.op == Not) {
						fprintf(RISCV_code, "	xor %c%d,x0,%c%d\n", x1.kind, x1.index, x2.kind, x2.index);
						fprintf(RISCV_code, "	seqz %c%d,%c%d\n", x1.kind, x1.index, x1.kind, x1.index);
					}
				}
				else if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == DOp_K) {
					Var_Info x1 = var_var[t->child[0]->attr.Var_info], x2 = var_var[t->child[1]->child[0]->attr.Var_info];
					if (t->child[1]->child[1]->kind.exp == Var_K) {
						Var_Info x3 = var_var[t->child[1]->child[1]->attr.Var_info];
						switch (t->child[1]->attr.op) {
							case Plus:
								fprintf(RISCV_code, "	add %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Minus:
								fprintf(RISCV_code, "	sub %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Times:
								fprintf(RISCV_code, "	mul %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Over:
								fprintf(RISCV_code, "	div %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Mod:
								fprintf(RISCV_code, "	rem %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Lt:
								fprintf(RISCV_code, "	slt %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Gt:
								fprintf(RISCV_code, "	sgt %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								break;
							case Eq:
								fprintf(RISCV_code, "	xor %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								fprintf(RISCV_code, "	seqz %c%d,%c%d\n", x1.kind, x1.index, x1.kind, x1.index);
								break;
							case Neq:
								fprintf(RISCV_code, "	xor %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								fprintf(RISCV_code, "	snez %c%d,%c%d\n", x1.kind, x1.index, x1.kind, x1.index);
								break;
							case And:
								fprintf(RISCV_code, "	seqz %c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index);
								fprintf(RISCV_code, "	add %c%d,%c%d,-1\n", x1.kind, x1.index, x1.kind, x1.index);
								fprintf(RISCV_code, "	and %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								fprintf(RISCV_code, "	snez %c%d,%c%d\n", x1.kind, x1.index, x1.kind, x1.index);
								break;
							case Or:
								fprintf(RISCV_code, "	or %c%d,%c%d,%c%d\n", x1.kind, x1.index, x2.kind, x2.index, x3.kind, x3.index);
								fprintf(RISCV_code, "	snez %c%d,%c%d\n", x1.kind, x1.index, x1.kind, x1.index);
								break;
							default: ;
						}
					}
					else {
						int x3 = t->child[1]->child[1]->attr.val;
						switch (t->child[1]->attr.op) {
							case Plus:
								fprintf(RISCV_code, "	add %c%d,%c%d,%d\n", x1.kind, x1.index, x2.kind, x2.index, x3);
								break;
							case Lt:
								fprintf(RISCV_code, "	slti %c%d,%c%d,%d\n", x1.kind, x1.index, x2.kind, x2.index, x3);
								break; 
						}
					}
				}
				else if (t->child[0]->kind.exp == Var_K && t->child[1]->kind.exp == Array_K) {
					Var_Info x1 = var_var[t->child[0]->attr.Var_info], x2 = var_var[t->child[1]->child[0]->attr.Var_info];
					fprintf(RISCV_code, "	lw %c%d,%d(%c%d)\n", x1.kind, x1.index, t->child[1]->child[1]->attr.val, x2.kind, x2.index);
				}
				else if (t->child[0]->kind.exp == Array_K && t->child[1]->kind.exp == Var_K) {
					Var_Info x1 = var_var[t->child[0]->child[0]->attr.Var_info], x2 = var_var[t->child[1]->attr.Var_info];
					fprintf(RISCV_code, "	sw %c%d,%d(%c%d)\n", x2.kind, x2.index, t->child[0]->child[1]->attr.val, x1.kind, x1.index);
				}
			}
			else if (t->kind.stmt == Def_K) {
				Var_Info x1 = t->child[0]->attr.Var_info;
				fprintf(RISCV_code, "	.common %c%d,%d,4\n", x1.kind, x1.index, t->child[1]->attr.val);
				fprintf(RISCV_code, "\n\n");
			}
			else if (t->kind.stmt == Return_K) {
				fprintf(RISCV_code, "	lw ra,%d(sp)\n", func_stack_size - 4);
				fprintf(RISCV_code, "	add sp,sp,%d\n", func_stack_size);
				fprintf(RISCV_code, "	jr ra\n");
			}
			else if (t->kind.stmt == OFunc_K) {
				fprintf(RISCV_code, "	call %s\n", t->child[0]->attr.func_name + 2);
			}
			else if (t->kind.stmt == Label_K) {
				fprintf(RISCV_code, ".l%d:\n", t->child[0]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Goto_K) {
				fprintf(RISCV_code, "	j .l%d\n", t->child[0]->attr.Var_info.index);
			}
			else if (t->kind.stmt == Load_K) {
				if (t->child[0]->kind.exp == Var_K) {
					fprintf(RISCV_code, "	lui %c%d,%%hi(%c%d)\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "	lw %c%d,%%lo(%c%d)(%c%d)\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index, var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index);
				}
				else
					fprintf(RISCV_code, "	lw %c%d,%d(sp)\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, 4 * t->child[0]->attr.val);
			}
			else if (t->kind.stmt == Loadaddr_K) {
				if (t->child[0]->kind.exp == Var_K) {
					fprintf(RISCV_code, "	lui %c%d,%%hi(%c%d)\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
					fprintf(RISCV_code, "	add %c%d,%c%d,%%lo(%c%d)\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, t->child[0]->attr.Var_info.kind, t->child[0]->attr.Var_info.index);
				}
				else
					fprintf(RISCV_code, "	add %c%d,sp,%d\n", var_var[t->child[1]->attr.Var_info].kind, var_var[t->child[1]->attr.Var_info].index, 4 * t->child[0]->attr.val);
			}
			else if (t->kind.stmt == Store_K) {
				fprintf(RISCV_code, "	sw %c%d,%d(sp)\n", var_var[t->child[0]->attr.Var_info].kind, var_var[t->child[0]->attr.Var_info].index, 4 * t->child[1]->attr.val);
			}
		}
	}
	else if (t->nk == Func_K) {
		func_stack_size = (t->child[1]->attr.val / 4 + 1) * 16;
		fprintf(RISCV_code, "	.text\n");
		fprintf(RISCV_code, "	.align 2\n");
		fprintf(RISCV_code, "	.global %s\n", t->attr.func_name + 2);
		fprintf(RISCV_code, "	.type %s,@function\n", t->attr.func_name + 2);
		fprintf(RISCV_code, "%s:\n", t->attr.func_name + 2);
		fprintf(RISCV_code, "	add sp,sp,-%d\n", func_stack_size);
		fprintf(RISCV_code, "	sw ra,%d(sp)\n", func_stack_size - 4);
		printtree(t->child[2]);
		fprintf(RISCV_code, "\n");
		fprintf(RISCV_code, "	.size %s,.-%s\n", t->attr.func_name + 2, t->attr.func_name + 2);
		fprintf(RISCV_code, "	stk = %d\n", func_stack_size);
		fprintf(RISCV_code, "\n\n");
	}
}

void convert(TreeNode *t) {
	set_var();
	printtree(t);
}
