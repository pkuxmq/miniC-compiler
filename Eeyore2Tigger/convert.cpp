#include "convert.h"
#include "symtab.h"
#include "util.h"
#include <map>
using std::swap;
using std::map;

static int param_num = 0;
static int func_stack_size = 0;
static map<TreeNode *, bool> added_prev_loadaddr;
static int func_saved_reg[12];
static map<TreeNode *, bool> return_regs;
static bool InMainFunc = false;
static map<TreeNode *, bool> call_func_saved_regs;

int add_load_var_instr(TreeNode *t, Var_Info *var, bool array)
{
    // printf("add\n");
    TreeNode *p = t->parentnode, *s = p->child[1];

    if (!array)
        p->child[0] = newStmtNode(Load_K);
    else
        p->child[0] = newStmtNode(Loadaddr_K);
    p->child[0]->parentnode = p;

    p->child[0]->child[0] = newExpNode(Var_K);
    p->child[0]->child[0]->parentnode = p->child[0];
    p->child[0]->child[1] = newExpNode(Var_K);
    p->child[0]->child[1]->parentnode = p->child[0];

    p->child[0]->child[0]->attr.Var_info.kind = var->kind;
    p->child[0]->child[0]->attr.Var_info.index = var->index;
    p->child[0]->child[1]->attr.Var_info.kind = 't';
    p->child[0]->child[1]->attr.Var_info.index = ++var_num[1];

    p->child[1] = newStmtNode(Seq_K);
    p->child[1]->parentnode = p;
    p->child[1]->child[0] = t;
    p->child[1]->child[1] = s;
    t->parentnode = p->child[1];
    if (s != NULL)
        s->parentnode = p->child[1];

    // printf("add finish\n");
    return var_num[1];
}

void add_loadaddr_array_instr(TreeNode *t, Var_Info *var, int stack_pos)
{
    TreeNode *p = t->parentnode, *s = p->child[1];

    p->child[0] = newStmtNode(Loadaddr_K);
    p->child[0]->parentnode = p;

    p->child[0]->child[0] = newExpNode(Const_K);
    p->child[0]->child[0]->parentnode = p->child[0];
    p->child[0]->child[1] = newExpNode(Var_K);
    p->child[0]->child[1]->parentnode = p->child[0];

    p->child[0]->child[0]->attr.val = stack_pos;
    p->child[0]->child[1]->attr.Var_info.kind = var->kind;
    p->child[0]->child[1]->attr.Var_info.index = var->index;

    p->child[1] = newStmtNode(Seq_K);
    p->child[1]->parentnode = p;
    p->child[1]->child[0] = t;
    p->child[1]->child[1] = s;
    t->parentnode = p->child[1];
    if (s != NULL)
        s->parentnode = p->child[1];
}

void add_store_var_instr(TreeNode *t, Var_Info *var, int index, TreeNode *idx)
{
    TreeNode *p = t->parentnode, *s = p->child[1];

    TreeNode *seq1 = newStmtNode(Seq_K);
    p->child[1] = seq1;
    seq1->parentnode = p;

    TreeNode *ldaddr = newStmtNode(Loadaddr_K);
    seq1->child[0] = ldaddr;
    ldaddr->parentnode = seq1;

    ldaddr->child[0] = newExpNode(Var_K);
    ldaddr->child[0]->parentnode = ldaddr;
    ldaddr->child[1] = newExpNode(Var_K);
    ldaddr->child[1]->parentnode = ldaddr;
    ldaddr->child[0]->attr.Var_info.kind = var->kind;
    ldaddr->child[0]->attr.Var_info.index = var->index;
    ldaddr->child[1]->attr.Var_info.kind = 't';
    ldaddr->child[1]->attr.Var_info.index = ++var_num[1];

    TreeNode *seq2 = newStmtNode(Seq_K);
    seq1->child[1] = seq2;
    seq2->parentnode = seq1;

    TreeNode *st = newStmtNode(Assign_K);
    seq2->child[0] = st;
    st->parentnode = seq2;
    seq2->child[1] = s;
    if (s != NULL)
        s->parentnode = seq2;

    st->child[0] = newExpNode(Array_K);
    st->child[0]->parentnode = st;
    st->child[1] = newExpNode(Var_K);
    st->child[1]->parentnode = st;
    added_prev_loadaddr[st->child[0]] = true;

    st->child[0]->child[0] = newExpNode(Var_K);
    st->child[0]->child[0]->parentnode = st->child[0];
    st->child[0]->child[0]->attr.Var_info.kind = 't';
    st->child[0]->child[0]->attr.Var_info.index =
        ldaddr->child[1]->attr.Var_info.index;
    if (idx == NULL)
    {
        st->child[0]->child[1] = newExpNode(Const_K);
        st->child[0]->child[1]->parentnode = st->child[0];
        st->child[0]->child[1]->attr.val = 0;
    }
    else
    {
        st->child[0]->child[1] = newExpNode(idx->kind.exp);
        st->child[0]->child[1]->parentnode = st->child[0];
        st->child[0]->child[1]->attr = idx->attr;
    }

    st->child[1]->attr.Var_info.kind = 't';
    st->child[1]->attr.Var_info.index = index;
}

int add_prev_assign(TreeNode *t, int val)
{
    TreeNode *p = t->parentnode->parentnode;
    p->child[1] = newStmtNode(Seq_K);
    p->child[1]->parentnode = p;
    t->parentnode->parentnode = p->child[1];
    p->child[1]->child[1] = t->parentnode;
    TreeNode *prev_assign = newStmtNode(Assign_K);
    p->child[1]->child[0] = prev_assign;
    prev_assign->parentnode = p->child[1];

    prev_assign->child[0] = newExpNode(Var_K);
    prev_assign->child[1] = newExpNode(Const_K);
    prev_assign->child[0]->parentnode = prev_assign;
    prev_assign->child[1]->parentnode = prev_assign;

    prev_assign->child[0]->attr.Var_info = Var_Info('t', ++var_num[1]);
    prev_assign->child[1]->attr.val = val;

    return var_num[1];
}

void checkexp(TreeNode *cexp, TreeNode *t)
{
    if (cexp->child[0]->kind.exp == Const_K)
    {
        if (cexp->child[1] != NULL)
        {
            if (cexp->child[1]->kind.exp == Var_K)
            {
                if (cexp->attr.op == Plus)
                    swap(cexp->child[0], cexp->child[1]);
                else if (cexp->attr.op == Gt)
                {
                    swap(cexp->child[0], cexp->child[1]);
                    cexp->attr.op = Lt;
                }
                else
                {
                    int new_index =
                        add_prev_assign(t, cexp->child[0]->attr.val);
                    cexp->child[0]->kind.exp = Var_K;
                    cexp->child[0]->attr.Var_info.kind = 't';
                    cexp->child[0]->attr.Var_info.index = new_index;
                }
            }
            else
            {
                int new_index1 = add_prev_assign(t, cexp->child[0]->attr.val);
                int new_index2 = add_prev_assign(t, cexp->child[1]->attr.val);

                cexp->child[0]->kind.exp = Var_K;
                cexp->child[0]->attr.Var_info.kind = 't';
                cexp->child[0]->attr.Var_info.index = new_index1;

                cexp->child[1]->kind.exp = Var_K;
                cexp->child[1]->attr.Var_info.kind = 't';
                cexp->child[1]->attr.Var_info.index = new_index2;
            }
        }
    }
    else if (cexp->child[1] != NULL)
    {
        if (cexp->child[1]->kind.exp == Const_K &&
            !(cexp->attr.op == Plus || cexp->attr.op == Lt))
        {
            int new_index = add_prev_assign(t, cexp->child[1]->attr.val);
            cexp->child[1]->kind.exp = Var_K;
            cexp->child[1]->attr.Var_info.kind = 't';
            cexp->child[1]->attr.Var_info.index = new_index;
        }
    }
}

void add_prev_assign_var(TreeNode *t, Var_Info var1, Var_Info var2)
{
    t->parentnode->child[1] = newStmtNode(Seq_K);
    t->parentnode->child[1]->parentnode = t->parentnode;
    t->parentnode = t->parentnode->child[1];
    t->parentnode->child[1] = t;
    TreeNode *prev_assign = newStmtNode(Assign_K);
    t->parentnode->child[0] = prev_assign;
    prev_assign->parentnode = t->parentnode;
    prev_assign->child[0] = newExpNode(Var_K);
    prev_assign->child[1] = newExpNode(Var_K);
    prev_assign->child[0]->parentnode = prev_assign;
    prev_assign->child[1]->parentnode = prev_assign;
    prev_assign->child[0]->attr.Var_info = var1;
    prev_assign->child[1]->attr.Var_info = var2;
}

void convert_without_array(TreeNode *t)
{
    if (t == NULL)
        return;
    // printf("%p\n", t);
    if (t->nk == Stmt_K)
    {
        if (t->kind.stmt == If_K)
        {
            // printf("If\n");
            TreeNode *cexp = t->child[0];
            if (cexp->child[0] == NULL)
                return;
            if (cexp->child[0]->kind.exp == Var_K &&
                global_var[cexp->child[0]->attr.Var_info])
            {
                int new_index = add_load_var_instr(
                    t, &cexp->child[0]->attr.Var_info, false);

                cexp->child[0]->attr.Var_info.kind = 't';
                cexp->child[0]->attr.Var_info.index = new_index;
            }
            if (cexp->child[1] != NULL && cexp->child[1]->kind.exp == Var_K &&
                global_var[cexp->child[1]->attr.Var_info])
            {
                if (cexp->child[0]->attr.Var_info ==
                    cexp->child[1]->attr.Var_info)
                    ;
                else
                {
                    int new_index = add_load_var_instr(
                        t, &cexp->child[1]->attr.Var_info, false);

                    cexp->child[1]->attr.Var_info.kind = 't';
                    cexp->child[1]->attr.Var_info.index = new_index;
                }
            }

            checkexp(cexp, t);
        }
        else if (t->kind.stmt == Assign_K)
        {
            // printf("Assign\n");

            if (t->child[1]->kind.exp == CFunc_K)
            {
                t->parentnode->child[0] = t->child[1];
                t->child[1]->parentnode = t->parentnode;
                t->parentnode->child[0]->nk = Stmt_K;
                t->parentnode->child[0]->kind.stmt = OFunc_K;

                TreeNode *s = t->parentnode->child[1];
                t->parentnode->child[1] = newStmtNode(Seq_K);
                t->parentnode->child[1]->parentnode = t->parentnode;
                t->parentnode->child[1]->child[0] = t;
                t->parentnode->child[1]->child[1] = s;
                s->parentnode = t->parentnode->child[1];
                t->parentnode = t->parentnode->child[1];

                t->child[1] = newExpNode(Var_K);
                t->child[1]->parentnode = t;
                t->child[1]->attr.Var_info.kind = 'a';
                t->child[1]->attr.Var_info.index = 0;

                convert_without_array(t->parentnode->parentnode);
            }

            TreeNode *cexp = t->child[1];
            if (cexp->child[0] != NULL)
            {
                if (cexp->child[0]->kind.exp == Var_K &&
                    global_var[cexp->child[0]->attr.Var_info])
                {
                    int new_index =
                        add_load_var_instr(t, &cexp->child[0]->attr.Var_info,
                                           cexp->kind.exp == Array_K);

                    cexp->child[0]->attr.Var_info.kind = 't';
                    cexp->child[0]->attr.Var_info.index = new_index;

                    if (cexp->kind.exp == Array_K)
                        added_prev_loadaddr[cexp] = true;
                }
                if (cexp->child[1] != NULL &&
                    cexp->child[1]->kind.exp == Var_K &&
                    global_var[cexp->child[1]->attr.Var_info])
                {
                    if (cexp->child[0]->attr.Var_info ==
                        cexp->child[1]->attr.Var_info)
                        ;
                    else
                    {
                        int new_index = add_load_var_instr(
                            t, &cexp->child[1]->attr.Var_info, false);

                        cexp->child[1]->attr.Var_info.kind = 't';
                        cexp->child[1]->attr.Var_info.index = new_index;
                    }
                }
                checkexp(cexp, t);
            }
            else if (cexp->kind.exp == Var_K && global_var[cexp->attr.Var_info])
            {
                int new_index =
                    add_load_var_instr(t, &cexp->attr.Var_info, false);
                cexp->attr.Var_info.kind = 't';
                cexp->attr.Var_info.index = new_index;
            }

            cexp = t->child[0]->child[1];
            if (cexp != NULL && cexp->child[0] != NULL)
            {
                if (cexp->child[0]->kind.exp == Var_K &&
                    global_var[cexp->child[0]->attr.Var_info])
                {
                    int new_index = add_load_var_instr(
                        t, &cexp->child[0]->attr.Var_info, true);

                    cexp->child[0]->attr.Var_info.kind = 't';
                    cexp->child[0]->attr.Var_info.index = new_index;
                    added_prev_loadaddr[cexp] = true;
                }
            }

            TreeNode *tmp = t->child[0];
            if (t->child[0]->kind.exp == Array_K)
            {
                if (tmp->child[0]->kind.exp == Var_K &&
                    global_var[tmp->child[0]->attr.Var_info])
                {
                    Var_Info var_tmp = tmp->child[0]->attr.Var_info;
                    TreeNode *idx = tmp->child[1];

                    t->child[0] = newExpNode(Var_K);
                    t->child[0]->attr.Var_info.kind = 't';
                    t->child[0]->attr.Var_info.index = ++var_num[1];

                    add_store_var_instr(t, &var_tmp,
                                        t->child[0]->attr.Var_info.index, idx);
                }
                if (t->child[1]->kind.exp == Const_K)
                {
                    int new_index = add_prev_assign(t, t->child[1]->attr.val);
                    t->child[1]->kind.exp = Var_K;
                    t->child[1]->attr.Var_info.kind = 't';
                    t->child[1]->attr.Var_info.index = new_index;
                }
            }
            else if (tmp->kind.exp == Var_K && global_var[tmp->attr.Var_info])
            {
                Var_Info var_tmp = tmp->attr.Var_info;
                tmp->attr.Var_info.kind = 't';
                tmp->attr.Var_info.index = ++var_num[1];

                add_store_var_instr(t, &var_tmp, tmp->attr.Var_info.index,
                                    NULL);
            }
        }
        else if (t->kind.stmt == Return_K)
        {
            // printf("Return %p\n", t);

            if (t->child[0] != NULL)
            {
                TreeNode *prev_assign = newStmtNode(Assign_K);
                t->parentnode->child[0] = prev_assign;
                prev_assign->parentnode = t->parentnode;
                prev_assign->child[0] = newExpNode(Var_K);
                prev_assign->child[0]->parentnode = prev_assign;
                prev_assign->child[0]->attr.Var_info.kind = 'a';
                prev_assign->child[0]->attr.Var_info.index = 0;
                prev_assign->child[1] = t->child[0];
                t->child[0]->parentnode = prev_assign;

                TreeNode *s = t->parentnode->child[1],
                         *new_seq = newStmtNode(Seq_K);
                t->parentnode->child[1] = new_seq;
                new_seq->parentnode = t->parentnode;
                new_seq->child[0] = t;
                new_seq->child[1] = s;
                t->parentnode = new_seq;
                if (s != NULL)
                    s->parentnode = new_seq;

                t->child[0] = NULL;

                convert_without_array(t->parentnode->parentnode);
            }
/*            if (!InMainFunc && !return_regs[t])
            {
                for (int i = 0; i < 12; i++)
                    add_prev_assign_var(t->parentnode, Var_Info('s', i),
                                        Var_Info('t', func_saved_reg[i]));
                return_regs[t] = true;
            }*/
        }
        else if (t->kind.stmt == Seq_K)
        {
            // printf("Seq\n");
            convert_without_array(t->child[0]);
            convert_without_array(t->child[1]);
        }
        else if (t->kind.stmt == Param_K)
        {
            // printf("Param\n");

            TreeNode *cexp = t;
            if (cexp->child[0]->kind.exp == Var_K &&
                global_var[cexp->child[0]->attr.Var_info])
            {
                int new_index = add_load_var_instr(
                    t, &cexp->child[0]->attr.Var_info, false);

                cexp->child[0]->attr.Var_info.kind = 't';
                cexp->child[0]->attr.Var_info.index = new_index;
            }

            TreeNode *p = t->parentnode;
            p->child[0] = newStmtNode(Assign_K);
            p->child[0]->parentnode = p;
            p->child[0]->child[1] = t->child[0];
            p->child[0]->child[0] = newExpNode(Var_K);
            p->child[0]->child[0]->attr.Var_info.kind = 'a';
            p->child[0]->child[0]->attr.Var_info.index = param_num++;

            free(t);
        }
        else if (t->kind.stmt == Def_K &&
                 !global_var[t->child[0]->attr.Var_info])
        {
            if (t->attr.def == ARRAY)
            {
                array_in_func[t->child[0]->attr.Var_info] = func_stack_size;
                func_stack_size += t->child[1]->attr.val / 4;
                free(t->child[1]);
            }
            free(t->child[0]);
            t->parentnode->parentnode->child[1] = t->parentnode->child[1];
            t->parentnode->child[1]->parentnode = t->parentnode->parentnode;
            free(t->parentnode);
            free(t);
        }
        else if (t->kind.stmt == OFunc_K)
        {
            param_num = 0;
           /* if (!call_func_saved_regs[t])
            {
                int saved_reg[7];
                for (int i = 0; i < 7; i++)
                    saved_reg[i] = ++var_num[1];
                for (int i = 0; i < 7; i++)
                {
                    add_prev_assign_var(t->parentnode,
                                        Var_Info('t', saved_reg[i]),
                                        Var_Info('c', i));
                }
                for (int i = 0; i < 7; i++)
                {
                    add_prev_assign_var(t->parentnode->child[1],
                                        Var_Info('c', i),
                                        Var_Info('t', saved_reg[i]));
                }
				call_func_saved_regs[t] = true;
            }*/
        }
    }
    else if (t->nk == Func_K)
    {
        // printf("Func\n");
        func_stack_size = 0;
        TreeNode *next = t->child[1];

        /*if (strcmp(t->attr.func_name, "f_main"))
        {
            for (int i = 0; i < 12; i++)
                func_saved_reg[i] = ++var_num[1];

            for (int i = 0; i < 12; i++)
                add_prev_assign_var(next, Var_Info('t', func_saved_reg[i]),
                                    Var_Info('s', i));
        }
        else
            InMainFunc = true;*/

        for (int i = 0; i < t->child[0]->attr.val; i++)
        {
            add_prev_assign_var(next, Var_Info('p', i), Var_Info('a', i));
        }

        convert_without_array(next);

        t->child[2] = newExpNode(Const_K);
        t->child[2]->parentnode = t;
        t->child[2]->attr.val = func_stack_size;
    }
}

void add_prev_op(TreeNode *t, Var_Info s1, Var_Info s2, char op, Var_Info d)
{
    t->parentnode->child[1] = newStmtNode(Seq_K);
    t->parentnode->child[1]->parentnode = t->parentnode;
    t->parentnode = t->parentnode->child[1];
    t->parentnode->child[1] = t;
    TreeNode *prev_assign = newStmtNode(Assign_K);
    t->parentnode->child[0] = prev_assign;
    prev_assign->parentnode = t->parentnode;

    prev_assign->child[0] = newExpNode(Var_K);
    prev_assign->child[0]->parentnode = prev_assign;
    prev_assign->child[0]->attr.Var_info = d;

    TreeNode *prev_op = newExpNode(DOp_K);
    prev_assign->child[1] = prev_op;
    prev_op->parentnode = prev_assign;

    if (op == '+')
        prev_op->attr.op = Plus;
    else if (op == '*')
        prev_op->attr.op = Times;

    prev_op->child[0] = newExpNode(Var_K);
    prev_op->child[1] = newExpNode(Var_K);
    prev_op->child[0]->parentnode = prev_op;
    prev_op->child[1]->parentnode = prev_op;

    prev_op->child[0]->attr.Var_info = s1;
    prev_op->child[1]->attr.Var_info = s2;
}

void convert_array(TreeNode *t)
{
    if (t == NULL)
        return;

    if (t->nk == Exp_K && t->kind.exp == Array_K)
    {
        if (!global_var[t->child[0]->attr.Var_info] && !added_prev_loadaddr[t])
        {
            add_loadaddr_array_instr(t->parentnode,
                                     &(t->child[0]->attr.Var_info),
                                     array_in_func[t->child[0]->attr.Var_info]);
            added_prev_loadaddr[t] = true;
        }
        if (t->child[1]->kind.exp == Var_K)
        {
            // int index1 = add_prev_assign(t->parentnode, 4);
            // add_prev_op(t->parentnode->parentnode, Var_Info('t', index1),
            // t->child[1]->attr.Var_info, '*', Var_Info('t', ++var_num[1]));
            add_prev_op(t->parentnode->parentnode, t->child[0]->attr.Var_info,
                        t->child[1]->attr.Var_info, '+',
                        t->child[0]->attr.Var_info);
            t->child[1]->kind.exp = Const_K;
            t->child[1]->attr.val = 0;
        }
    }
    else
    {
        convert_array(t->child[0]);
        convert_array(t->child[1]);
    }
}

void rotate_seq(TreeNode *t) {
	TreeNode *p = t->parentnode, *s = t, *prev;
	while(s->child[0] != NULL)
		s = s->child[0];
	if (p->nk == Func_K)
		p->child[1] = s;
	else
		p->child[0] = s;
	prev = p;
	while(t != s) {
		s->child[0] = s->child[1];
		s->child[1] = s->parentnode;
		s->parentnode = prev;
		prev = s;
		s = s->child[1];
	}
	t->child[0] = t->child[1];
	t->child[1] = NULL;
}

void rotate(TreeNode *t) {
	do {
		if (t->nk == Func_K) {
			rotate_seq(t->child[1]);
			break;
		}
		if (t->child[0]->nk == Func_K)
			rotate_seq(t->child[0]->child[1]);
		t = t->child[1];
	} while(t != NULL);
}

void convert_tree(TreeNode *t)
{
	rotate(t);
    convert_without_array(t);
    convert_array(t);
}
