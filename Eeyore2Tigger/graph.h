#ifndef __GRAPH__
#define __GRAPH__
#include <map>
#include <vector>
#include <set>
#include "globals.h"
#include "Bit_set.h"

using std::map;
using std::pair;
using std::vector;
using std::set;

class Node {
public:
	vector<Node *> succ, prev;
	TreeNode *tn;

	//set<Var_Info> def, use;
	//set<Var_Info> in, out;

	Bit_set def, use, in, out;

	bool isMove;

	Node(TreeNode *tn);
};

class Graph {
public:
	vector<Node *> nodes;
	map<pair<Node *, Node *>, int> edge;

	Node *addNode(TreeNode *tn);
	void addEdge(Node *from, Node *to);
	void rmEdge(Node *from, Node *to);

	void printgraph();
};

class ConflictGraph {
public:
	map<pair<int, int>, bool> edge;
	set<int> *adj;
	int *degree;
	//bool *deleted;
	bool *precolored;
	//bool *MoveRelated;
	map<int, set<Node *> > moveList;
	map<int, int> alias;
	int *color;
	int n;

	ConflictGraph(int n);
	~ConflictGraph();
	void addEdge(int i, int j);
	//void rmEdge(int i, int j);
	//void deletenode(int i);
	//void addNode(int i);
};


#endif
