#ifndef __LIVENESS__
#define __LIVENESS__

#include "graph.h"
#include "globals.h"

extern Graph *graph;

void GenGraph(TreeNode *tree);

void compute_liveness(Graph *g);

#endif
