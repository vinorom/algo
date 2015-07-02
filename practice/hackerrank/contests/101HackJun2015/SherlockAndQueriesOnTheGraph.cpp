/**
 * https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-queries-on-the-graph
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

////////////////////////////////////////
// Graph
////////////////////////////////////////

typedef pair<int, int> PI;
typedef vector<int> VI;

const int MAXN = 100001;
const int MAXM = 100001;
const int MAXLOGN = 17; // log(MAXN)

VI graph[MAXN]; // [u] - list of adjacent edges for vertex u
PI edges[MAXM]; // [i] = (u, v) - edge
int N = MAXN;   // number of vertices (to be adjusted)
int M = MAXM;   // number of edges (to be adjusted)

int adj(int u, int e)
{
    return edges[e].first == u ? edges[e].second : edges[e].first;
}

////////////////////////////////////////
// Bridge Tree
////////////////////////////////////////

// http://threads-iiith.quora.com/The-Bridge-Tree-of-a-graph
// http://www.geeksforgeeks.org/bridge-in-a-graph/

VI bridge_tree[MAXN];   // [i] - list of adjacent vertices
int BTN = 0;            // number of vertices in bridge tree (calculated)

bool bt_is_bridge[MAXM];    // [e] - whether edge e is bridge or not
int bt_comp[MAXN];          // [u] - component that vertex u was merged into
int bt_disc[MAXN];          // [u] - time when vertex u was discovered
bool bt_visited[MAXN];
queue<int> bt_queue[MAXN];

int dfs_find_bridges(int u, int edge) // returns earliest visited vertex reachable from u
{
    static int tm = 0;

    bt_visited[u] = true;
    bt_disc[u] = tm++;
    int low = bt_disc[u];

    for (int i = 0; i < (int)graph[u].size(); ++i)
    {
        int e = graph[u][i];
        int v = adj(u, e);

        if (!bt_visited[v])
        {
            low = min(low, dfs_find_bridges(v, e));
        }
        else if (e != edge)
        {
            low = min(low, bt_disc[v]);
        }
    }

    if (low == bt_disc[u] && edge != -1)
    {
        bt_is_bridge[edge] = true;
    }

    return low;
}

void dfs_build_bridge_tree(int u)
{
    int comp = BTN;
    bt_visited[u] = true;
    bt_queue[u].push(u);

    while (!bt_queue[u].empty())
    {
        int v = bt_queue[u].front();
        bt_queue[u].pop();

        bt_comp[v] = comp;

        for (int i = 0; i < (int)graph[v].size(); ++i)
        {
            int e = graph[v][i];
            int w = adj(v, e);
            if (bt_visited[w]) continue;

            if (bt_is_bridge[e])
            {
                // create new component, connect with current one, discover new component
                ++BTN;
                bridge_tree[comp].push_back(BTN);
                bridge_tree[BTN].push_back(comp);
                dfs_build_bridge_tree(w);
            }
            else
            {
                bt_visited[w] = true;
                bt_queue[u].push(w);
            }
        }
    }
}

void build_bridge_tree()
{
    // find all bridges
    std::fill(bt_is_bridge, bt_is_bridge + M, false);
    std::fill(bt_visited, bt_visited + N, false);
    for (int u = 0; u < N; ++u)
    {
        if (!bt_visited[u]) dfs_find_bridges(u, -1);
    }

    // build a bridge tree
    std::fill(bt_visited, bt_visited + N, false);
    BTN = 0;
    for (int u = 0; u < N; ++u)
    {
        if (!bt_visited[u]) dfs_build_bridge_tree(u);
    }
    ++BTN;
}

void dump_bridge_tree()
{
    for (int i = 0; i < BTN; ++i)
    {
        cout << "BT[" << i << "]:";
        for (int j = 0; j < (int)bridge_tree[i].size(); ++j) cout << bridge_tree[i][j] << ",";
        cout << endl;
    }
    for (int i = 0; i < N; ++i)
    {
        cout << "BT comp[" << i << "]:" << bt_comp[i] << endl;
    }
}

////////////////////////////////////////
// Tree/LCA
////////////////////////////////////////

// https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/

namespace lca
{

VI* tree = bridge_tree;

int P[MAXN][MAXLOGN];
int L[MAXN];
int start[MAXN], finish[MAXN], now = 0;

void dfs_lca(int u, int p) // dp
{
    L[u] = p != -1 ? L[p] + 1 : 0;
    P[u][0] = p;
    start[u] = ++now;
    for (int i = 1; i < MAXLOGN; ++i)
    {
        int x = P[u][i - 1];
        if (x < 0) break;
        P[u][i] = P[x][i - 1];
    }
    for (int i = 0; i < (int)tree[u].size(); ++i)
    {
        int v = tree[u][i];
        if (v == p) continue;
        dfs_lca(v, u);
    }
    finish[u] = ++now;
}

void build_lca()
{
    now = 0;
    for (int i = 0; i < BTN; ++i) P[i][0] = -1;

    dfs_lca(0, -1);
}

void dump_lca()
{
    for (int i = 0; i < BTN; ++i)
    {
        cout << "[" << i << "]: L=" << L[i] << " start=" << start[i] << " finish=" << finish[i] << endl;
    }
    for (int i = 0; i < BTN; ++i)
    {
        cout << "P[" << i << "]:";
        for (int j = 0; j < MAXLOGN; ++j) cout << ' ' << P[i][j];
        cout << endl;
    }
}

int lca(int p, int q)
{
    if (L[p] < L[q]) swap(p, q);

    int log = 1;
    for (; (1 << log) <= L[p]; ++log);
    --log;

    for (int i = log; i >= 0; --i)
    {
        if (L[p] - (1 << i) >= L[q]) p = P[p][i];
    }

    if (p == q) return p;

    for (int i = log; i >= 0; --i)
    {
        if (P[p][i] != -1 && P[p][i] != P[q][i])
        {
            p = P[p][i];
            q = P[q][i];
        }
    }

    return P[p][0];
}

bool is_ancestor(int u, int a)
{
    return start[u] <= start[a] && finish[u] >= finish[a];
}

PI intersect_paths(int a, int u /*ancestor of a*/, int b, int v /*ancestor of b*/)
{
    if (!is_ancestor(v, a)) return make_pair(0, 0);
    int x = lca(a, b);
    if (L[u] < L[v])
    {
        if (is_ancestor(v, x)) return make_pair(x, v);
    }
    else
    {
        if (is_ancestor(u, x)) return make_pair(x, u);
    }
    return make_pair(0, 0);
}

int distance(int a, int b)
{
    return L[a] + L[b] - 2 * L[lca(a, b)];
}

int distance(PI path)
{
    return distance(path.first, path.second);
}

} // namespace lca

int solve(int a, int b, int c, int d)
{
    int res = lca::distance(c, d);
    int u = lca::lca(a, b);
    int v = lca::lca(c, d);
    res -= lca::distance(lca::intersect_paths(a, u, c, v));
    res -= lca::distance(lca::intersect_paths(a, u, d, v));
    res -= lca::distance(lca::intersect_paths(b, u, c, v));
    res -= lca::distance(lca::intersect_paths(b, u, d, v));
    return res;
}

int main()
{
    int Q;
    cin >> N >> M >> Q;
    for (int i = 0; i < M; ++i)
    {
        int A, B;
        cin >> A >> B;
        --A, --B;
        edges[i] = make_pair(A, B);
        graph[A].push_back(i);
        graph[B].push_back(i);
    }
    build_bridge_tree();
    //dump_bridge_tree();
    lca::build_lca();
    //lca::dump_lca();
    while (Q--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d;
        cout << solve(bt_comp[a], bt_comp[b], bt_comp[c], bt_comp[d]) << endl;
    }

    return 0;
}
