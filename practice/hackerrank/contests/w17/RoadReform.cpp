/**
 * https://www.hackerrank.com/contests/w17/challenges/roads-building
 */

#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef map<int /*node*/, ll /*weight > 0*/> adj_map;

struct node
{
    int n;
    adj_map edges;
    node(): n(-1) {}
};

struct hnode: public node
{
    ll key;
    int pos;

    hnode() { renew(); }
    void renew() { key = std::numeric_limits<int>::max(); pos = -1; }
};

typedef vector<hnode> graph;
typedef vector<hnode*> heap;

void heap_bubble_up(heap& h, hnode* n)
{
    while (n->pos > 0 && h[n->pos]->key < h[(n->pos - 1) / 2]->key)
    {
        swap(h[n->pos], h[(n->pos - 1) / 2]);
        swap(h[n->pos]->pos, h[(n->pos - 1) / 2]->pos);
    }
}

void heap_bubble_down(heap& h, hnode* n)
{
    while ((2 * n->pos + 1 < h.size() && n->key > h[2 * n->pos + 1]->key) ||
           (2 * n->pos + 2 < h.size() && n->key > h[2 * n->pos + 2]->key))
    {
        hnode* oth = h[2 * n->pos + 1];
        if (2 * n->pos + 2 < h.size() && oth->key > h[2 * n->pos + 2]->key) oth = h[2 * n->pos + 2];

        swap(h[n->pos], h[oth->pos]);
        swap(h[n->pos]->pos, h[oth->pos]->pos);
    }
}

void heap_insert(heap& h, hnode* n)
{
    h.push_back(n);
    n->pos = (int)h.size() - 1;
    heap_bubble_up(h, n);
}

hnode* heap_extract_top(heap& h)
{
    if (h.empty()) return 0;

    hnode* min = h[0];

    h[0] = h[h.size() - 1];
    h.resize(h.size() - 1);
    h[0]->pos = 0;

    if (h.size() > 1)
        heap_bubble_down(h, h[0]);

    min->pos = -1;

    return min;
}

bool heap_extract(heap& h, hnode* n)
{
    if (h.empty()) return false;
    if (n->pos == -1) return false;

    h[n->pos] = h[h.size() - 1];
    h.resize(h.size() - 1);
    h[n->pos]->pos = n->pos;

    if (!h.empty())
    {
        if (h[n->pos]->key < h[(n->pos - 1) / 2]->key)
            heap_bubble_up(h, h[n->pos]);
        else if (h.size() > 1)
            heap_bubble_down(h, h[n->pos]);
    }

    n->pos = -1;

    return true;
}

void dijkstra(graph& g, int source)
{
    heap h;
    for (int i = 0; i < (int)g.size(); ++i)
    {
        if (i != source) heap_insert(h, &g[i]);
    }

    g[source].key = 0;
    for (adj_map::iterator it = g[source].edges.begin(); it != g[source].edges.end(); ++it)
    {
        int v = (*it).first;
        ll w = (*it).second;

        if (g[v].pos != -1) // in heap
        {
            heap_extract(h, &g[v]);
            g[v].key = g[source].key + w;
            heap_insert(h, &g[v]);
        }
    }

    while (!h.empty())
    {
        hnode* min = heap_extract_top(h);

        for (adj_map::iterator it = g[min->n].edges.begin(); it != g[min->n].edges.end(); ++it)
        {
            int v = (*it).first;
            ll w = (*it).second;

            if (g[v].pos != -1) // in heap
            {
                heap_extract(h, &g[v]);
                g[v].key = std::min(g[min->n].key + w, g[v].key);
                heap_insert(h, &g[v]);
            }
        }
    }
}

ll solve(graph& g)
{
    int i, j;
    int N = (int)g.size();

    graph g_rev = g;

    vector<int> idx(N);
    vector<int> idx_rev(N);
    i = 0, generate(idx.begin(), idx.end(), [&i]() { return i++; });
    i = 0, generate(idx_rev.begin(), idx_rev.end(), [&i]() { return i++; });

    dijkstra(g, 0);
    sort(idx.begin(), idx.end(), [&g](int lhv, int rhv) { return g[lhv].key < g[rhv].key; });
    ll min_len = g[N-1].key;

    dijkstra(g_rev, N-1);
    sort(idx_rev.begin(), idx_rev.end(), [&g_rev](int lhv, int rhv) { return g_rev[lhv].key < g_rev[rhv].key; });

    ll rev_prefix_sum[N+1] = {0};
    for (i = 0; i < N; ++i) rev_prefix_sum[i+1] = rev_prefix_sum[i] + g_rev[idx_rev[i]].key;

    ll count = 0;
    for (i = 0, j = N-1; min_len - 1 - g[idx[i]].key > 0; ++i)
    {
        ll right_len = min_len - 1 - g[idx[i]].key;
        while (idx[i] == idx_rev[j] || right_len - g_rev[idx_rev[j]].key <= 0) --j;
        count += right_len * (j + 1) - rev_prefix_sum[j+1];
    }

    return count;
}

int main()
{
    int N, M;
    cin >> N >> M;

    graph g(N);
    for (int i = 0; i < N; ++i) g[i].n = i;

    for (int i = 0; i < M; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].edges[v] = g[u].edges[v] == 0 ? w : min(g[u].edges[v], w);
        g[v].edges[u] = g[v].edges[u] == 0 ? w : min(g[v].edges[u], w);
    }

    cout << solve(g) << endl;

    return 0;
}
