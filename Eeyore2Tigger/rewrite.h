#ifndef __REWRITE__
#define __REWRITE__
#include "symtab.h"
#include "globals.h"
#include "util.h"
#include "color.h"
#include "Bit_set.h"

extern int func_num;

void RewriteProgram(TreeNode *t);
void alloc(TreeNode *t);
void finalchange(TreeNode *t);
void save_regs(TreeNode *t);

#endif
