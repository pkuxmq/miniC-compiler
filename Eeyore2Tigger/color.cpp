#include "color.h"
#include <algorithm>

using std::set_difference;
using std::set_union;
using std::set_intersection;
using std::inserter;
using std::swap;
using std::make_pair;

ConflictGraph *cgraph;

set<int> simplifyWorklist, freezeWorklist, spillWorklist, spilledNodes,
	coalescedNodes, coloredNodes, stack_set;
//stack<int> selectStack;
vector<int> selectStack;
set<Node *> coalescedMoves, constrainedMoves, frozenMoves, worklistMoves,
	activeMoves;

static const int REG_NUM = 27;

void GenCGraph(Graph *graph)
{
	spillWorklist.clear();
	freezeWorklist.clear();
	simplifyWorklist.clear();
	spilledNodes.clear();
	coalescedNodes.clear();
	coloredNodes.clear();
	stack_set.clear();
	selectStack.clear();
	//while (!selectStack.empty())
	//	selectStack.pop();
	coalescedMoves.clear();
	constrainedMoves.clear();
	frozenMoves.clear();
	worklistMoves.clear();
	activeMoves.clear();

	if (cgraph != NULL)
		delete cgraph;
	cgraph = new ConflictGraph(VAR_NUM);

	for (int i = 0; i < VAR_NUM; i++)
	{
		// printf("** %c%d %d\n", index_var[i].kind, index_var[i].index,
		// cgraph->precolored[i]);
		if (index_var[i].kind == 's')
		{
			cgraph->precolored[i] = true;
			cgraph->color[i] = index_var[i].index;
		}
		else if (index_var[i].kind == 'c')
		{
			cgraph->precolored[i] = true;
			cgraph->color[i] = 12 + index_var[i].index;
		}
		else if (index_var[i].kind == 'a')
		{
			cgraph->precolored[i] = true;
			cgraph->color[i] = 19 + index_var[i].index;
		}
	}

	for (int i = 0; i < graph->nodes.size(); i++)
	{
		if (graph->nodes[i]->isMove)
		{
			for (int a = 0; a < VAR_NUM; a++)
				if (graph->nodes[i]->def[a] || graph->nodes[i]->use[a])
					cgraph->moveList[a].insert(graph->nodes[i]);
			worklistMoves.insert(graph->nodes[i]);
		}
		for (int a = 0; a < VAR_NUM; a++)
			if (graph->nodes[i]->def[a])
				for (int j = 0; j < VAR_NUM; j++)
				{
					if (graph->nodes[i]->out[j])
						cgraph->addEdge(a, j);
				}
	}
}

bool MoveRelated(int n)
{
	set<Node *> s;
	set_intersection(cgraph->moveList[n].begin(), cgraph->moveList[n].end(),
			activeMoves.begin(), activeMoves.end(),
			inserter(s, s.begin()));
	if (!s.empty())
		return true;
	set_intersection(cgraph->moveList[n].begin(), cgraph->moveList[n].end(),
			worklistMoves.begin(), worklistMoves.end(),
			inserter(s, s.begin()));
	if (!s.empty())
		return true;
	return false;
}

void MakeWorklist()
{
	for (int i = 0; i < cgraph->n; i++)
	{
		if (cgraph->precolored[i])
		{
			continue;
		}
		if (cgraph->degree[i] >= REG_NUM)
		{
			spillWorklist.insert(i);
		}
		else if (MoveRelated(i))
		{
			freezeWorklist.insert(i);
		}
		else
		{
			simplifyWorklist.insert(i);
		}
	}
}

set<int> Adjacent(int n)
{
	// printf("Adjacent\n");
	// printf("%d %d\n", n, VAR_NUM);
	set<int> s1, s2;
	set_difference(cgraph->adj[n].begin(), cgraph->adj[n].end(),
			coalescedNodes.begin(), coalescedNodes.end(),
			inserter(s1, s1.begin()));
	set_difference(cgraph->adj[n].begin(), cgraph->adj[n].end(),
			stack_set.begin(), stack_set.end(),
			inserter(s2, s2.begin()));
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
			inserter(s1, s1.begin()));
	// printf("Adjacent\n");
	return s1;
}

set<Node *> NodeMoves(int n)
{
	set<Node *> s1, s2;
	set_intersection(cgraph->moveList[n].begin(), cgraph->moveList[n].end(),
			activeMoves.begin(), activeMoves.end(),
			inserter(s1, s1.begin()));
	set_intersection(cgraph->moveList[n].begin(), cgraph->moveList[n].end(),
			worklistMoves.begin(), worklistMoves.end(),
			inserter(s2, s2.begin()));
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
			inserter(s1, s1.begin()));
	return s1;
}

void EnableMoves(set<int> s)
{
	for (set<int>::iterator iter = s.begin(); iter != s.end(); iter++)
	{
		int n = *iter;
		set<Node *> sn;
		set_intersection(cgraph->moveList[n].begin(), cgraph->moveList[n].end(),
				activeMoves.begin(), activeMoves.end(),
				inserter(sn, sn.begin()));
		for (set<Node *>::iterator i = sn.begin(); i != sn.end(); i++)
		{
			set<Node *>::iterator j = activeMoves.find(*i);
			if (j != activeMoves.end())
				activeMoves.erase(j);
			worklistMoves.insert(*i);
		}
	}
}

void DecrementDegree(int n)
{
	int d = cgraph->degree[n];
	cgraph->degree[n]--;
	if (d == REG_NUM)
	{
		set<int> s = cgraph->adj[n];
		s.insert(n);
		EnableMoves(s);
		set<int>::iterator iter = spillWorklist.find(n);
		if (iter != spillWorklist.end())
			spillWorklist.erase(iter);
		if (MoveRelated(n))
			freezeWorklist.insert(n);
		else {
			simplifyWorklist.insert(n);
		}
	}
}

void push_stack(int n)
{
	//if (stack_set.find(n) != stack_set.end())
	//	printf("error %d %c%d\n", n, index_var[n].kind, index_var[n].index);
	//selectStack.push(n);
	selectStack.push_back(n);
	stack_set.insert(n);
}

void pop_stack()
{
	//int tmp = selectStack.top();
	//selectStack.pop();
	int tmp = *(selectStack.rbegin());
	selectStack.pop_back();
	bool flag = true;
	for (int i = 0; i < selectStack.size(); i++) {
		if (selectStack[i] == tmp) {
			flag = false;
			break;
		}
	}
	if (flag) {
		set<int>::iterator iter = stack_set.find(tmp);
		stack_set.erase(iter);
	}
}

void Simplify()
{
	// printf("Simplify\n");
	set<int>::iterator iter = simplifyWorklist.begin();
	int n = *iter;
	//printf("Simplify %d %c%d\n", n, index_var[n].kind, index_var[n].index);
	push_stack(n);
	// printf("Simplify %d\n", n);
	set<int> s = Adjacent(n);
	for (set<int>::iterator adj_iter = s.begin(); adj_iter != s.end();
			adj_iter++)
		DecrementDegree(*adj_iter);
	simplifyWorklist.erase(iter);
	// printf("Simplify finish\n");
}

void AddWorkList(int u)
{
	// printf("AddWorkList\n");
	if (!cgraph->precolored[u] && !MoveRelated(u) &&
			cgraph->degree[u] < REG_NUM)
	{
		set<int>::iterator iter = freezeWorklist.find(u);
		if (iter != freezeWorklist.end())
			freezeWorklist.erase(iter);
		simplifyWorklist.insert(u);
	}
	// printf("AddWorkList finish\n");
}

inline bool OK(int t, int r)
{
	return cgraph->degree[t] < REG_NUM || cgraph->precolored[t] ||
		cgraph->edge[make_pair(t, r)];
}

bool Conservative(set<int> s)
{
	int k = 0;
	for (set<int>::iterator iter = s.begin(); iter != s.end(); iter++)
		if (cgraph->degree[*iter] >= REG_NUM)
			k++;
	return k < REG_NUM;
}

int GetAlias(int x)
{
	set<int>::iterator iter = coalescedNodes.find(x);
	if (iter != coalescedNodes.end())
		return GetAlias(cgraph->alias[x]);
	else
		return x;
}

void Combine(int u, int v)
{
	set<int>::iterator iter = freezeWorklist.find(v);
	if (iter != freezeWorklist.end())
		freezeWorklist.erase(iter);
	else
	{
		iter = spillWorklist.find(v);
		if (iter != spillWorklist.end())
			spillWorklist.erase(iter);
	}

	coalescedNodes.insert(v);
	cgraph->alias[v] = u;
	set_union(cgraph->moveList[u].begin(), cgraph->moveList[u].end(),
			cgraph->moveList[v].begin(), cgraph->moveList[v].end(),
			inserter(cgraph->moveList[u], cgraph->moveList[u].begin()));
	set<int> tmp;
	tmp.insert(v);
	EnableMoves(tmp);

	set<int> s = Adjacent(v);
	for (iter = s.begin(); iter != s.end(); iter++)
	{
		cgraph->addEdge(*iter, u);
		DecrementDegree(*iter);
	}

	if (cgraph->degree[u] >= REG_NUM &&
			((iter = freezeWorklist.find(u)) != freezeWorklist.end()))
	{
		freezeWorklist.erase(iter);
		spillWorklist.insert(u);
	}
}

void Coalesce()
{
	// printf("Coalesce\n");
	set<Node *>::iterator iter = worklistMoves.begin();
	Node *m = *iter;
	int x = var_index[m->tn->child[0]->attr.Var_info];
	int y = var_index[m->tn->child[1]->attr.Var_info];
	x = GetAlias(x);
	y = GetAlias(y);
	if (cgraph->precolored[y])
		swap(x, y);
	worklistMoves.erase(iter);

	// printf("Coalesce\n");
	if (x == y)
	{
		coalescedMoves.insert(m);
		AddWorkList(x);
	}
	else if (cgraph->precolored[y] || cgraph->edge[make_pair(x, y)])
	{
		constrainedMoves.insert(m);
		AddWorkList(x);
		AddWorkList(y);
	}
	else if (cgraph->precolored[x])
	{
		bool flag = true;
		set<int> adj = Adjacent(y);
		for (set<int>::iterator iter = adj.begin(); iter != adj.end(); iter++)
			if (!OK(*iter, x))
			{
				flag = false;
				break;
			}
		if (flag)
		{
			coalescedMoves.insert(m);
			Combine(x, y);
			AddWorkList(y);
		}
		else
			activeMoves.insert(m);
	}
	else
	{
		set<int> s1 = Adjacent(x), s2 = Adjacent(y);
		set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
				inserter(s1, s1.begin()));
		if (Conservative(s1))
		{
			coalescedMoves.insert(m);
			Combine(x, y);
			AddWorkList(y);
		}
		else
			activeMoves.insert(m);
	}
	// printf("Coalesce\n");
}

void FreezeMoves(int u)
{
	set<Node *> s = NodeMoves(u);
	for (set<Node *>::iterator iter = s.begin(); iter != s.end(); iter++)
	{
		Node *m = *iter;
		int x = var_index[m->tn->child[0]->attr.Var_info];
		int y = var_index[m->tn->child[1]->attr.Var_info];
		int v = GetAlias(y);
		if (v == GetAlias(u))
			v = GetAlias(x);
		set<Node *>::iterator i = activeMoves.find(m);
		if (i != activeMoves.end())
			activeMoves.erase(i);
		frozenMoves.insert(m);

		if (!MoveRelated(v) && cgraph->degree[v] < REG_NUM)
		{
			set<int>::iterator j = freezeWorklist.find(v);
			if (j != freezeWorklist.end())
				freezeWorklist.erase(j);
			simplifyWorklist.insert(v);
		}
	}
}

void Freeze()
{
	// printf("Freeze\n");
	set<int>::iterator iter = freezeWorklist.begin();
	int n = *iter;
	simplifyWorklist.insert(n);
	freezeWorklist.erase(iter);
	FreezeMoves(n);
}

void Spill()
{
	// printf("Spill\n");
	set<int>::iterator iter = spillWorklist.begin();
	int m = *iter;
	spillWorklist.erase(iter);
	simplifyWorklist.insert(m);
	FreezeMoves(m);
}

void AssignColors()
{
	bool *remain_colors = new bool[REG_NUM];
	while (!selectStack.empty())
	{
		int n = *(selectStack.rbegin());
		pop_stack();
		for (int i = 0; i < REG_NUM; i++)
			remain_colors[i] = true;
		for (set<int>::iterator iter = cgraph->adj[n].begin();
				iter != cgraph->adj[n].end(); iter++)
		{
			int w = GetAlias(*iter);
			set<int>::iterator i;
			if (cgraph->precolored[w] ||
					((i = coloredNodes.find(w)) != coloredNodes.end()))
				remain_colors[cgraph->color[w]] = false;
		}
		bool flag = false;
		for (int i = 0; i < REG_NUM; i++)
		{
			if (remain_colors[i])
			{
				cgraph->color[n] = i;
				flag = true;
				coloredNodes.insert(n);
				break;
			}
		}
		if (!flag)
			spilledNodes.insert(n);
		// printf("%d %d\n", n, cgraph->color[n]);
	}

	for (set<int>::iterator iter = coalescedNodes.begin();
			iter != coalescedNodes.end(); iter++)
		cgraph->color[*iter] = cgraph->color[GetAlias(*iter)];

	delete[] remain_colors;
}

void RegAlloc(TreeNode *SyntaxTree)
{
	do
	{
		// printf("1\n");
		update_var_index(SyntaxTree);
		GenGraph(SyntaxTree);
		compute_liveness(graph);
		GenCGraph(graph);
		MakeWorklist();
		while (!simplifyWorklist.empty() || !worklistMoves.empty() ||
				!freezeWorklist.empty() || !spillWorklist.empty())
		{
			// printf("2\n");
			if (!simplifyWorklist.empty())
				Simplify();
			else if (!worklistMoves.empty())
				Coalesce();
			else if (!freezeWorklist.empty())
				Freeze();
			else if (!spillWorklist.empty())
				Spill();
		}
		// printf("3\n");
		AssignColors();
		// printf("4\n");

		if (!spilledNodes.empty())
		{
			//printf("rewrite %d\n", spilledNodes.size());
			/*for (int i : spilledNodes) {
				printf("%d %c%d\n", i, index_var[i].kind, index_var[i].index);
			}*/
			RewriteProgram(SyntaxTree);
			//printtree(SyntaxTree);
		}
	} while (!spilledNodes.empty());

	alloc(SyntaxTree);
	finalchange(SyntaxTree);

	save_regs(SyntaxTree);
}
