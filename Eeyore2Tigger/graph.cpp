#include "graph.h"
#include "symtab.h"
using std::make_pair;

Node::Node(TreeNode *tn) : def(VAR_NUM), use(VAR_NUM), in(VAR_NUM), out(VAR_NUM)
{
    this->tn = tn;
    isMove = false;
}

Node *Graph::addNode(TreeNode *tn)
{
    Node *n = new Node(tn);
    nodes.push_back(n);
    return n;
}

void Graph::addEdge(Node *from, Node *to)
{
    from->succ.push_back(to);
    to->prev.push_back(from);

    edge[make_pair(from, to)] = 1;
}

void Graph::rmEdge(Node *from, Node *to)
{
    edge[make_pair(from, to)] = 0;

    for (vector<Node *>::iterator i = from->succ.begin(); i < from->succ.end();
         i++)
    {
        if (*i == to)
        {
            from->succ.erase(i);
            break;
        }
    }

    for (vector<Node *>::iterator i = to->prev.begin(); i < to->prev.end(); i++)
    {
        if (*i == from)
        {
            to->prev.erase(i);
            break;
        }
    }
}

void Graph::printgraph()
{
    printf("print graph:\nnode number: %d\n", (int)nodes.size());
    for (int i = 0; i < nodes.size(); i++)
    {

        printf("Node %p:\n", nodes[i]);
        printf("prev: ");
        for (int j = 0; j < nodes[i]->prev.size(); j++)
        {
            printf("%p ", nodes[i]->prev[j]);
        }
        printf("\n");

        printf("succ: ");
        for (int j = 0; j < nodes[i]->succ.size(); j++)
        {
            printf("%p ", nodes[i]->succ[j]);
        }
        printf("\n");

        printf("in: ");
        print(nodes[i]->in);
        printf("\n");

        printf("out: ");
        print(nodes[i]->out);
        printf("\n");

        printf("use: ");
        print(nodes[i]->use);
        printf("\n");

        printf("def: ");
        print(nodes[i]->def);
        printf("\n");
    }
}

ConflictGraph::ConflictGraph(int n)
{
    this->n = n;
    adj = new set<int>[n];
    degree = new int[n];
    // deleted = new bool[n];
    precolored = new bool[n];
    // MoveRelated = new bool[n];
    color = new int[n];

	for (int i = 0; i < n; i++) {
		degree[i] = 0;
		precolored[i] = false;
		color[i] = 0;
	}
}

ConflictGraph::~ConflictGraph()
{
    delete[] adj;
    delete[] degree;
    // delete[] deleted;
    delete[] precolored;
    // delete[] MoveRelated;
    delete[] color;
}

void ConflictGraph::addEdge(int i, int j)
{
	if (i == j)
		return;
    edge[make_pair(i, j)] = true;
    edge[make_pair(j, i)] = true;
    if (!precolored[i])
    {
        adj[i].insert(j);
        degree[i]++;
    }
    if (!precolored[j])
    {
        adj[j].insert(i);
        degree[j]++;
    }
}
/*
void ConflictGraph::rmEdge(int i, int j)
{
    edge[make_pair(i, j)] = false;
    edge[make_pair(j, i)] = false;
    set<int>::iterator iter = adj[i].find(j);
    if (iter != adj[i].end())
        adj[i].erase(iter);
    iter = adj[j].find(i);
    if (iter != adj[j].end())
        adj[j].erase(iter);
    degree[i]--;
    degree[j]--;
}

void ConflictGraph::deletenode(int i)
{
    if (deleted[i])
        return;
    deleted[i] = true;
    for (set<int>::iterator iter = adj[i].begin(); iter != adj[i].end(); iter++)
    {
        rmEdge(i, *iter);
    }
}

void ConflictGraph::addNode(int i)
{
    if (!deleted[i])
        return;
    deleted[i] = false;
    for (set<int>::iterator iter = adj[i].begin(); iter != adj[i].end(); iter++)
    {
        addEdge(i, *iter);
    }
}
*/
