/**
 * http://code.google.com/codejam/contest/6234486/dashboard#s=p0
 */

#include <bits/stdc++.h>

using namespace std;

const int MAXM = 100;

typedef vector<int> int_list;
typedef vector<int_list> adj_list;
adj_list adj(MAXM * 2);
int_list parities(MAXM * 2);

bool find_odd_cycle(int node, int parity)
{
    parities[node] = parity;
    for (auto a: adj[node])
    {
        if (parities[a] >= 0) // visited
        {
            if (parities[a] == parity) return true; // odd cycle
        }
        else
        {
            if (find_odd_cycle(a, parity ^ 1)) return true;
        }
    }
    return false;
}

bool find_odd_cycle_loop(int n)
{
    fill(parities.begin(), parities.end(), -1); // not visited

    for (int i = 0; i < n; ++i) // check all connected components
    {
        if (parities[i] < 0 && find_odd_cycle(i, 0)) return true;
    }
    return false;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int M;
        cin >> M;

        unordered_map<string, int> name2id;
        for (auto& l: adj) l.clear();

        string name1, name2;
        int n = 0;
        while (M--)
        {
            cin >> name1 >> name2;
            if (name2id.find(name1) == name2id.end()) name2id[name1] = n++;
            if (name2id.find(name2) == name2id.end()) name2id[name2] = n++;
            int id1 = name2id[name1];
            int id2 = name2id[name2];
            adj[id1].push_back(id2);
            adj[id2].push_back(id1);
        }

        cout << "Case #" << t << ": " << (find_odd_cycle_loop(n) ? "No" : "Yes") << '\n';
    }

    return 0;
}
