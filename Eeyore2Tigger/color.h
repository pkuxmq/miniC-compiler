#ifndef __COLOR__
#define __COLOR__
#include "globals.h"
#include "graph.h"
#include "symtab.h"
#include "liveness.h"
#include "rewrite.h"
#include <stack>
using std::stack;

extern ConflictGraph *cgraph;

extern set<Var_Info> precolored, initial;
extern set<int> simplifyWorklist, freezeWorklist, spillWorklist, spilledNodes, coalescedNodes, coloredNodes;
//extern stack<int> selectStack;
extern vector<int> selectStack;
extern set<Node *> coalescedMoves, constrainedMoves, frozenMoves, worklistMoves, activeMoves;

void RegAlloc(TreeNode *SyntaxTree);

#endif
