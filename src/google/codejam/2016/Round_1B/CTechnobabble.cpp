/**
 * http://code.google.com/codejam/contest/11254486/dashboard#s=p2
 */

#include <bits/stdc++.h>

using namespace std;

using adj_list = vector<int>;

class Graph
{
public:
    void AddEdge(int u, int v)
    {
        if (u >= (int)nodes.size()) nodes.resize(u + 1);
        if (v >= (int)nodes.size()) nodes.resize(v + 1);
        nodes[u].adj.push_back(v);
    }

    const int GetNumNodes() const { return (int)nodes.size(); }
    const adj_list GetAdjList(int u) const { return nodes[u].adj; }

private:
    struct Node
    {
        adj_list adj;
    };

    vector<Node> nodes;
};

bool bpm(const Graph& bpg, int u, unordered_map<int, int>& match, vector<bool>& seen)
{
    for (auto v : bpg.GetAdjList(u))
    {
        if (seen[v]) continue;

        seen[v] = true;

        if (match.count(v) == 0 || bpm(bpg, match[v], match, seen))
        {
            match[v] = u;
            return true;
        }
    }

    return false;
}

int max_bpm(const Graph& bpg)
{
    int flow = 0;

    unordered_map<int, int> match;
    vector<bool> seen(bpg.GetNumNodes());

    for (int u = 0; u < bpg.GetNumNodes(); ++u)
    {
        fill(seen.begin(), seen.end(), false);
        if (bpm(bpg, u, match, seen)) ++flow;
    }

    return flow;
}

int min_edge_cover(const Graph& bpg)
{
    int mbpm = max_bpm(bpg);
    return bpg.GetNumNodes() - mbpm;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        Graph bpg;
        unordered_map<string, int> left, right;

        for (int i = 0; i < N; ++i)
        {
            string l, r;
            cin >> l >> r;

            if (left.count(l) == 0)
            {
                int u = (int)left.size() + (int)right.size();
                left[l] = u;
            }
            if (right.count(r) == 0)
            {
                int v = (int)left.size() + (int)right.size();
                right[r] = v;
            }

            bpg.AddEdge(left[l], right[r]);
        }

        int mec = min_edge_cover(bpg);

        cout << "Case #" << t << ": " << (N - mec) << '\n';
    }

    return 0;
}
