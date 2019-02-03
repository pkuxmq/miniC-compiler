#include "globals.h"
#include "symtab.h"
#include "Analyze.h"
#include "y.tab.h"

static int cur_max_index[3];
static int max_goto_index;
static int Find_error;

extern int myerror(int lineno, char *message);

typedef struct return_info
{
	int kind; // 0 for const, 1 fot t, 2 for T, 3 for p
	int val;
} Return_Info;

int insert_and_get_para_num(TreeNode *node)
{
	int cnt;
	int var_index;
	cur_max_index[2] = 0;
	cnt = 0;
	st_Return st_ret;
	while(node != NULL)
	{
		cnt++;
		var_index = cur_max_index[2]++;
		st_ret = st_lookup(node->child[1]->attr.name);
		if (st_ret.memloc != -1)
		{
			myerror(node->lineno, "Variable name conflict!");
			Find_error = 1;
		}
		else 
			st_insert(node->child[1]->attr.name, lineno, var_index, 'p', 0);
		node = node->child[2];
	}
	return cnt;
}

void delete_para(TreeNode *node)
{
	while(node != NULL)
	{
		st_delete(node->child[1]->attr.name);
		node = node->child[2];
	}
}

void Type_check(TreeNode *node, char *kind)
{}

void Node_analyze(TreeNode *currentnode)
{
	st_Return st_ret;
	TreeNode *tmpnode;
	int var_index;
	int para_num;
	int i;

	if (currentnode == NULL)
	{
		return;
	}

	switch(currentnode->nk)
	{
		case Stmt_K:
			switch(currentnode->kind.stmt)
			{
				case If_K:
					if (currentnode->attr.IfwithElse)
					{
						Node_analyze(currentnode->child[1]);
						Node_analyze(currentnode->child[2]);
					}
					else
					{
						Node_analyze(currentnode->child[1]);
					}
					break;
				case While_K:
					Node_analyze(currentnode->child[1]);
					break;
				case Assign_K:
					Type_check(currentnode->child[0], "Assign");
					Node_analyze(currentnode->child[1]);
					TreeNode *tmpnode = currentnode->child[0];
					if (tmpnode->kind.exp == Array_K)
					{
						st_ret = st_lookup(tmpnode->child[0]->attr.name);
						if (st_ret.memloc == -1)
							myerror(currentnode->lineno, "Undefined variable!");
						Node_analyze(tmpnode->child[1]);
						break;
					}
					st_ret = st_lookup(currentnode->child[0]->attr.name);
					if(st_ret.memloc == -1)
					{
						myerror(currentnode->lineno, "Undefined variable!");
						Find_error = 1;
						//exit(1);
					}
					break;
				case Def_K:
					Type_check(currentnode, "Define");
					if (currentnode->attr.def == NUM)
					{
						st_ret = st_lookup(currentnode->child[1]->attr.name);
						if(st_ret.memloc != -1)
						{
							myerror(currentnode->lineno, "Redefine variable!");

							Find_error = 1;
							//exit(1);
						}
						var_index = cur_max_index[0]++;
						st_insert(currentnode->child[1]->attr.name, lineno, var_index, 'T', 0);
					}
					else if (currentnode->attr.def == ARRAY)
					{
						st_ret = st_lookup(currentnode->child[1]->attr.name);
						if(st_ret.memloc != -1)
						{
							myerror(currentnode->lineno, "Redefine variable!");
							Find_error = 1;
							//exit(1);	
						}
						var_index = cur_max_index[0]++;
						st_insert(currentnode->child[1]->attr.name, lineno, var_index, 'T', 0);
					}
					else if (currentnode->attr.def == FUNC)
					{
						st_ret = st_lookup(currentnode->child[1]->attr.name);
						if(st_ret.memloc != -1 && st_ret.type != 'u')
						{
							myerror(currentnode->lineno, "Function name conflict!");
							Find_error = 1;
							//exit(1);	
						}

						para_num = insert_and_get_para_num(currentnode->child[2]);
						if (st_ret.memloc != -1 && st_ret.paranum != para_num)
						{
							myerror(currentnode->lineno, "Function parameters unmatched!");
							Find_error = 1;
						}
						if (currentnode->child[3] != NULL && st_ret.memloc == -1)
						{
							st_insert(currentnode->child[1]->attr.name, lineno, 0, 'F', para_num);
							Node_analyze(currentnode->child[3]);
						}
						else
							st_insert(currentnode->child[1]->attr.name, lineno, 0, 'u', para_num);
						delete_para(currentnode->child[2]);
					}
					else if (currentnode->attr.def == FUNC_MAIN)
					{
						Node_analyze(currentnode->child[0]);
					}
					break;
				case Return_K:
					Node_analyze(currentnode->child[0]);
					break;
				case Seq_K:
					Node_analyze(currentnode->child[0]);
					Node_analyze(currentnode->child[1]);
					break;
				case OFunc_K:
					tmpnode = currentnode;
					st_ret = st_lookup(currentnode->child[0]->attr.name);
					if(st_ret.memloc == -1)
					{
						myerror(currentnode->lineno, "Undefined variable!");
						Find_error = 1;
						//exit(1);
					}
					para_num = 0;
					while(tmpnode->child[1] != NULL)
					{
						para_num++;
						Node_analyze(tmpnode->child[1]->child[0]);
						tmpnode = tmpnode->child[1];
					}
					if(para_num != st_ret.paranum)
					{
						myerror(currentnode->lineno, "Function parameters unmatched!");
						Find_error = 1;
					}
					break;
				default:	;
			}
			break;
		case Exp_K:
			switch(currentnode->kind.exp)
			{
				case SOp_K:
					break;
				case DOp_K:
					Node_analyze(currentnode->child[0]);
					Node_analyze(currentnode->child[1]);
					break;
				case Const_K:
					break;
				case Id_K:
					st_ret = st_lookup(currentnode->attr.name);
					if(st_ret.memloc == -1)
					{
						myerror(currentnode->lineno, "Undefined variable!");
						Find_error = 1;
						//exit(1);
					}
					break;
				case Array_K:
					Node_analyze(currentnode->child[0]);
					Node_analyze(currentnode->child[1]);
					break;
				case Func_K:
					tmpnode = currentnode;
					st_ret = st_lookup(currentnode->child[0]->attr.name);
					if(st_ret.memloc == -1)
					{
						myerror(currentnode->lineno, "Undefined variable!");
						Find_error = 1;
						//exit(1);
					}
					para_num = 0;
					while(tmpnode->child[1] != NULL)
					{
						para_num++;
						Node_analyze(currentnode->child[1]->child[0]);
						tmpnode = tmpnode->child[1];
					}
					if(para_num != st_ret.paranum)
					{
						myerror(currentnode->lineno, "Function parameters unmatched!");
						Find_error = 1;
					}
					break;
				default:	;
			}
			break;
		default:	;
	}

}

int analyze(TreeNode *SyntaxTree)
{
	Find_error = 0;
	Node_analyze(SyntaxTree);
	return Find_error;
}
