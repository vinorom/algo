/**
 * Problem: http://code.google.com/codejam/contest/2984486/dashboard#s=p1
 */

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> Adj;
typedef vector<Adj> Graph;

int subtree_nodes[1000]; // number of nodes in a subtree with given root node

void DFS(const Graph& g, int s, int parent)
{
    subtree_nodes[s] = 1;

    int children = 0;
    for (int i = 0; i < g[s].size(); ++i)
    {
        if (g[s][i] != parent) ++children;
    }

    if (children <= 1) return; // don't count nodes below

    int max_subtree_nodes1 = 0;
    int max_subtree_nodes2 = 0;
    for (int i = 0; i < g[s].size(); ++i)
    {
        int child_node = g[s][i];
        if (child_node != parent)
        {
            DFS(g, child_node, s);

            if (max_subtree_nodes1 < subtree_nodes[child_node])
            {
                max_subtree_nodes2 = max_subtree_nodes1;
                max_subtree_nodes1 = subtree_nodes[child_node];
            }
            else if (max_subtree_nodes2 < subtree_nodes[child_node])
            {
                max_subtree_nodes2 = subtree_nodes[child_node];
            }
        }
    }

    subtree_nodes[s] = 1 + max_subtree_nodes1 + max_subtree_nodes2; // itself and two max subtrees
}

int DFS_loop(const Graph& g)
{
    int max_tree_nodes = 0;
    for (int i = 0; i < g.size(); ++i)
    {
        DFS(g, i, -1);
        max_tree_nodes = max(max_tree_nodes, subtree_nodes[i]);
    }
    return g.size() - max_tree_nodes;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;
        Graph graph(N);
        for (int i = 0; i < N - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
            graph[u-1].push_back(v-1);
            graph[v-1].push_back(u-1);
        }

        int min_nodes_to_remove = DFS_loop(graph);

        cout << "Case #" << t << ": " << min_nodes_to_remove << endl;
    }

    return 0;
}
