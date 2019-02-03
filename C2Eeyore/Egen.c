#include "globals.h"
#include "symtab.h"
#include "Egen.h"
#include "Analyze.h"
#include "y.tab.h"

extern FILE *Eeyore_code;
extern int insert_and_get_para_num(TreeNode *);
extern void delete_para(TreeNode *);

static int cur_max_index[3];
static int max_goto_index;

typedef struct return_info
{
	int kind; // 0 for const, 1 fot t, 2 for T, 3 for p
	int val;
} Return_Info;

char get_kind(Return_Info ri)
{
	switch(ri.kind)
	{
		case 0:
			return ' ';
		case 1:
			return 't';
		case 2:
			return 'T';
		case 3:
			return 'p';
		default:	;
	}
}

Return_Info E_code_gen(TreeNode *currentnode)
{
	Return_Info tmp;
	Return_Info tmp2;
	Return_Info new_tmp;
	Return_Info tmp_tmp;
	st_Return st_ret;
	TreeNode *tmpnode;
	char output_kind;
	char output_kind2;
	char *output_name;
	int var_index;
	int para_index;
	int goto_index;
	int goto_index_next;
	int array_size;
	int para_num;
	int i;

	if (currentnode == NULL)
	{
		new_tmp.kind = -1;
		new_tmp.val = 0;
		return new_tmp;
	}

	switch(currentnode->nk)
	{
		case Stmt_K:
			switch(currentnode->kind.stmt)
			{
				case If_K:
					if (currentnode->attr.IfwithElse)
					{
						tmp = E_code_gen(currentnode->child[0]);
						goto_index = max_goto_index++;
						output_kind = get_kind(tmp);
						fprintf(Eeyore_code, "if %c%d == 0 goto l%d\n", output_kind, tmp.val, goto_index);
						E_code_gen(currentnode->child[1]);
						fprintf(Eeyore_code, "l%d:\n", goto_index);
						E_code_gen(currentnode->child[2]);
					}
					else
					{
						tmp = E_code_gen(currentnode->child[0]);
						goto_index = max_goto_index++;
						output_kind = get_kind(tmp);
						fprintf(Eeyore_code, "if %c%d == 0 goto l%d\n", output_kind, tmp.val, goto_index);
						E_code_gen(currentnode->child[1]);
						fprintf(Eeyore_code, "l%d:\n", goto_index);
					}
					break;
				case While_K:
					goto_index = max_goto_index++;
					goto_index_next = max_goto_index++;
					fprintf(Eeyore_code, "l%d:\n", goto_index);
					tmp = E_code_gen(currentnode->child[0]);
					output_kind = get_kind(tmp);
					fprintf(Eeyore_code, "if %c%d == 0 goto l%d\n", output_kind, tmp.val, goto_index_next);
					E_code_gen(currentnode->child[1]);
					fprintf(Eeyore_code, "goto l%d\n", goto_index);
					fprintf(Eeyore_code, "l%d:\n", goto_index_next);
					break;
				case Assign_K:
					tmp = E_code_gen(currentnode->child[1]);
					output_kind = get_kind(tmp);
					TreeNode *tmpnode = currentnode->child[0];
					if (tmpnode->kind.exp == Array_K)
					{
						st_ret = st_lookup(tmpnode->child[0]->attr.name);
						tmp2 = E_code_gen(tmpnode->child[1]);
						output_kind2 = get_kind(tmp2);
						if (tmp2.kind == 0)
							tmp2.val *= 4;
						else if (tmp2.kind == 1)
							fprintf(Eeyore_code, "t%d = 4 * t%d\n", tmp2.val, tmp2.val);
						else
						{
							tmp_tmp.kind = 1;
							tmp_tmp.val = cur_max_index[1]++;
							fprintf(Eeyore_code, "var t%d\n", tmp_tmp.val);
							fprintf(Eeyore_code, "t%d = 4 * T%d\n", tmp_tmp.val, tmp2.val);
							tmp2 = tmp_tmp;
							output_kind2 = get_kind(tmp2);
						}
						fprintf(Eeyore_code, "%c%d [%c%d] = %c%d\n", st_ret.type, st_ret.memloc, output_kind2, tmp2.val, output_kind, tmp.val);
						break;
					}
					st_ret = st_lookup(currentnode->child[0]->attr.name);
					fprintf(Eeyore_code, "%c%d = %c%d\n", st_ret.type, st_ret.memloc, output_kind, tmp.val);
					break;
				case Def_K:
					if (currentnode->attr.def == NUM)
					{
						var_index = cur_max_index[0]++;
						fprintf(Eeyore_code, "var T%d\n", var_index);
					}
					else if (currentnode->attr.def == ARRAY)
					{
						var_index = cur_max_index[0]++;
						array_size = 4 * currentnode->child[2]->attr.val;
						fprintf(Eeyore_code, "var %d T%d\n", array_size, var_index);
					}
					else if (currentnode->attr.def == FUNC)
					{
						if (currentnode->child[3] == NULL)
							break;
						cur_max_index[2] = 0;
						para_num = insert_and_get_para_num(currentnode->child[2]);
						output_name = currentnode->child[1]->attr.name;
						fprintf(Eeyore_code, "f_%s [%d]\n", output_name, para_num);
						E_code_gen(currentnode->child[3]);
						fprintf(Eeyore_code, "end f_%s\n", output_name);
						delete_para(currentnode->child[2]);
					}
					else if (currentnode->attr.def == FUNC_MAIN)
					{
						fprintf(Eeyore_code, "f_main [0]\n");
						E_code_gen(currentnode->child[0]);
						fprintf(Eeyore_code, "end f_main\n");
					}
					break;
				case Return_K:
					tmp = E_code_gen(currentnode->child[0]);
					output_kind = get_kind(tmp);
					fprintf(Eeyore_code, "return %c%d\n", output_kind, tmp.val);
					break;
				case Seq_K:
					E_code_gen(currentnode->child[0]);
					E_code_gen(currentnode->child[1]);
					break;
				case OFunc_K:
					tmpnode = currentnode;
					while(tmpnode->child[1] != NULL)
					{
						tmp = E_code_gen(currentnode->child[1]->child[0]);
						output_kind = get_kind(tmp);
						fprintf(Eeyore_code, "param %c%d\n", output_kind, tmp.val);
						tmpnode = tmpnode->child[1];
					}
					output_name = currentnode->child[0]->attr.name;
					fprintf(Eeyore_code, "call f_%s\n", output_name);
					break;
				default:	;
			}
			break;
		case Exp_K:
			switch(currentnode->kind.exp)
			{
				case SOp_K:
					tmp = E_code_gen(currentnode->child[0]);
					output_kind = get_kind(tmp);
					new_tmp.kind = 1;
					new_tmp.val = cur_max_index[1]++;
					fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
					switch(currentnode->attr.op)
					{
						case Minus:
							fprintf(Eeyore_code, "t%d = -%c%d\n", new_tmp.val, output_kind, tmp.val);
							break;
						case Not:
							fprintf(Eeyore_code, "t%d = !%c%d\n", new_tmp.val, output_kind, tmp.val);
							break;
						default:	;
					}
					return new_tmp;
				case DOp_K:
					tmp = E_code_gen(currentnode->child[0]);
					tmp2 = E_code_gen(currentnode->child[1]);
					output_kind = get_kind(tmp);
					output_kind2 = get_kind(tmp2);
					new_tmp.kind = 1;
					new_tmp.val = cur_max_index[1]++;
					fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
					switch(currentnode->attr.op)
					{
						case Plus:
							fprintf(Eeyore_code, "t%d = %c%d + %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Minus:
							fprintf(Eeyore_code, "t%d = %c%d - %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Times:
							fprintf(Eeyore_code, "t%d = %c%d * %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Over:
							fprintf(Eeyore_code, "t%d = %c%d / %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Mod:
							fprintf(Eeyore_code, "t%d = %c%d %% %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Lt:
							fprintf(Eeyore_code, "t%d = %c%d < %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Gt:
							fprintf(Eeyore_code, "t%d = %c%d > %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Eq:
							fprintf(Eeyore_code, "t%d = %c%d == %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Neq:
							fprintf(Eeyore_code, "t%d = %c%d != %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case And:
							fprintf(Eeyore_code, "t%d = %c%d && %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						case Or:
							fprintf(Eeyore_code, "t%d = %c%d || %c%d\n", new_tmp.val, output_kind, tmp.val, output_kind2, tmp2.val);
							break;
						default:	;
					}
					return new_tmp;
				case Const_K:
					new_tmp.kind = 0;
					new_tmp.val = currentnode->attr.val;
					return new_tmp;
				case Id_K:
					new_tmp.kind = 2;
					st_ret = st_lookup(currentnode->attr.name);
					new_tmp.val = st_ret.memloc;
					if (st_ret.type == 'p')
						new_tmp.kind = 3;
					return new_tmp;
				case Array_K:
					tmp = E_code_gen(currentnode->child[0]);
					tmp2 = E_code_gen(currentnode->child[1]);
					output_kind = get_kind(tmp);
					output_kind2 = get_kind(tmp2);
					new_tmp.kind = 1;
					new_tmp.val = cur_max_index[1]++;
					if (output_kind2 == ' ')
					{
						fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
						fprintf(Eeyore_code, "t%d = %c%d [%d]\n", new_tmp.val, output_kind, tmp.val, 4 * tmp2.val);
					}
					else
					{
						fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
						fprintf(Eeyore_code, "t%d = 4 * %c%d\n", new_tmp.val, output_kind2, tmp2.val);
						new_tmp.val = cur_max_index[1]++;
						fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
						fprintf(Eeyore_code, "t%d = %c%d [t%d]\n", new_tmp.val, output_kind, tmp.val, new_tmp.val - 1);
					}
					return new_tmp;
				case Func_K:
					tmpnode = currentnode;
					while(tmpnode->child[1] != NULL)
					{
						tmp = E_code_gen(currentnode->child[1]->child[0]);
						output_kind = get_kind(tmp);
						fprintf(Eeyore_code, "param %c%d\n", output_kind, tmp.val);
						tmpnode = tmpnode->child[1];
					}
					new_tmp.kind = 1;
					new_tmp.val = cur_max_index[1]++;
					fprintf(Eeyore_code, "var t%d\n", new_tmp.val);
					output_name = currentnode->child[0]->attr.name;
					fprintf(Eeyore_code, "t%d = call f_%s\n", new_tmp.val, output_name);
					return new_tmp;
				default:	;
			}
			break;
		default:	;
	}

	new_tmp.kind = -1;
	new_tmp.val = 0;
	return new_tmp;
}

void generator(TreeNode *SyntaxTree)
{
	E_code_gen(SyntaxTree);
}
