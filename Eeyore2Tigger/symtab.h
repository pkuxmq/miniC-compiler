#ifndef __SYMTAB__
#define __SYMTEB__
#include "globals.h"
#include <map>

using std::map;

extern int func_num;

extern map<Var_Info, int> var_index;
extern map<int, Var_Info> index_var;
extern map<Var_Info, bool> global_var;
extern map<Var_Info, int> array_in_func;
extern int var_num[3], global_var_num;
extern int VAR_NUM;

void update_var_index(TreeNode *SyntaxTree);

#endif
