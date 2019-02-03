#include "liveness.h"
#include "symtab.h"
#include <algorithm>

using std::set_intersection;
using std::set_difference;
using std::inserter;

Graph *graph;

static map<int, vector<Node *> > goto_label_node;
static set<int> goto_label_index;
static map<int, Node *> label_node;

Node *genGraph(TreeNode *tn, Node *prev);
void add_def(TreeNode *tn, Node *n);
void add_use(TreeNode *tn, Node *n);

void GenGraph(TreeNode *tree) {
	if (graph != NULL)
		delete graph;
	graph = new Graph();
	genGraph(tree, NULL);

	for (set<int>::iterator i = goto_label_index.begin(); i != goto_label_index.end(); i++) {
		for (int n = 0; n < goto_label_node[*i].size(); n++) {
			graph->addEdge(goto_label_node[*i][n], label_node[*i]);
		}
	}
}

Node *genGraph(TreeNode *tn, Node *prev) {
	//printf("%p %p\n", tn, prev);
	if (tn == NULL)
		return NULL;
	if (tn->nk == Func_K) {
		return genGraph(tn->child[1], prev);
		//return NULL;
	}
	if (tn->nk != Stmt_K)
		return NULL;

	if (tn->kind.stmt == Seq_K) {
		//printf("SEQ\n");
		if (tn->child[0]->kind.stmt == Label_K) {
			TreeNode *label_next = tn->child[1];
			while (label_next->child[0]->kind.stmt == Label_K)
				label_next = label_next->child[1];
			Node *n = genGraph(label_next->child[0], prev);
			label_node[tn->child[0]->child[0]->attr.Var_info.index] = n;
			label_next = tn->child[1];
			while(label_next->child[0]->kind.stmt == Label_K) {
				label_node[label_next->child[0]->child[0]->attr.Var_info.index] = n;
				label_next = label_next->child[1];
			}
			genGraph(label_next->child[1], n);
			return n;
		}
		Node *n = genGraph(tn->child[0], prev);
		if (n == NULL)
			n = prev;
		if (tn->child[1] != NULL)
			genGraph(tn->child[1], n);
		//printf("SEQ finish %p\n", tn);
		return n;
	}
	else if (tn->kind.stmt == If_K) {
		//printf("IF\n");
		Node *n = graph->addNode(tn);
		add_use(tn->child[0], n);
		if (prev != NULL)
			graph->addEdge(prev, n);
		int label_index = tn->child[1]->attr.Var_info.index;
		goto_label_node[label_index].push_back(n);
		goto_label_index.insert(label_index);
		return n;
	}
	else if (tn->kind.stmt == Assign_K) {
		//printf("ASSIGN\n");
		Node *n = graph->addNode(tn);
		if (tn->child[0]->kind.exp == Var_K && tn->child[1]->kind.exp == Var_K)
			n->isMove = true;
		if (tn->child[0]->kind.exp == Var_K)
			add_def(tn->child[0], n);
		else
			add_use(tn->child[0], n);
		add_use(tn->child[1], n);
		if (prev != NULL)
			graph->addEdge(prev, n);
		return n;
	}
	else if (tn->kind.stmt == Def_K) {
		//printf("DEF\n");
		return NULL;
	}
	else if (tn->kind.stmt == Return_K) {
		//printf("RETURN\n");
		return NULL;
	}
	else if (tn->kind.stmt == OFunc_K) {
		//printf("OFUNC\n");
		return prev;
	}
	else if (tn->kind.stmt == Goto_K) {
		//printf("GOTO\n");
		int label_index = tn->child[0]->attr.Var_info.index;
		goto_label_node[label_index].push_back(prev);
		goto_label_index.insert(label_index);
		return NULL;
	}
	else if (tn->kind.stmt == Param_K) {
		//printf("PARAM\n");
		Node *n = graph->addNode(tn);
		add_use(tn->child[0], n);
		if (prev != NULL)
			graph->addEdge(prev, n);
		return n;
	}
	else if (tn->kind.stmt == Load_K || tn->kind.stmt == Loadaddr_K) {
		Node *n = graph->addNode(tn);
		add_def(tn->child[1], n);
		if (prev != NULL)
			graph->addEdge(prev, n);
		return n;
	}
	else if (tn->kind.stmt == Store_K) {
		Node *n = graph->addNode(tn);
		add_use(tn->child[0], n);
		if (prev != NULL)
			graph->addEdge(prev, n);
		return n;
	}

	return NULL;
}

void add_def(TreeNode *tn, Node *n) {
	n->def.set_bit(var_index[tn->attr.Var_info], 1);
}

void add_use(TreeNode *tn, Node *n) {
	//printf("ADD_USE %p %p\n", tn, n);
	if (tn->kind.exp == SOp_K) {
		add_use(tn->child[0], n);
	}
	else if (tn->kind.exp == DOp_K) {
		add_use(tn->child[0], n);
		add_use(tn->child[1], n);
	}
	else if (tn->kind.exp == Var_K) {
		n->use.set_bit(var_index[tn->attr.Var_info], 1);
		//printf("add use %c%d %d: %d %d\n", tn->attr.Var_info.kind, tn->attr.Var_info.index, var_index[tn->attr.Var_info], n->use.bits[0], n->use.bits[1]);
	}
	else if (tn->kind.exp == Array_K) {
		add_use(tn->child[0], n);
		add_use(tn->child[1], n);
	}
	//printf("ADD_USE finish %p %p\n", tn, n);
}

void compute_liveness(Graph *g) {
	for (int i = 0; i < g->nodes.size(); i++) {
		g->nodes[i]->in.clear();
		g->nodes[i]->out.clear();
	}

	bool all_eq = false;
	while(!all_eq) {
		//printf("one\n");
		all_eq = true;

		// inverse order
		for (int i = (int)g->nodes.size() - 1; i >= 0; i--) {
		//for (int i = 0; i < (int)g->nodes.size(); i++) {
			Node *n = g->nodes[i];
			Bit_set in_ = n->in, out_ = n->out;

			//printf("prev____in:%d %d, out:%d %d, use:%d %d, def:%d %d\n", n->in.bits[0], n->in.bits[1], n->out.bits[0], n->out.bits[1], n->use.bits[0], n->use.bits[1], n->def.bits[0], n->def.bits[1]);
			
			n->out.clear();
			for (int j = 0; j < n->succ.size(); j++) {
				n->out = n->out | n->succ[j]->in;
			}

			n->in = n->use | (n->out ^ (n->out & n->def));
			/*
			n->out.clear();
			for (int j = 0; j < n->succ.size(); j++) {
				n->out = n->out | n->succ[j]->in;
			}
			*/

			//printf("in:%d %d, out:%d %d, use:%d %d, def:%d %d\n", n->in.bits[0], n->in.bits[1], n->out.bits[0], n->out.bits[1], n->use.bits[0], n->use.bits[1], n->def.bits[0], n->def.bits[1]);

			if (all_eq) {
				if (in_ == n->in && out_ == n->out);
				else
					all_eq = false;
			}
		}
	}
}

