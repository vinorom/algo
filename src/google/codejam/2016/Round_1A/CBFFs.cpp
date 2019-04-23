/**
 * http://code.google.com/codejam/contest/4304486/dashboard#s=p2
 */

#include <vector>
#include <iostream>

using namespace std;

int solve(int F[], int N)
{
    int max_cycle_len = 0;
    int max_chain_len_sum = 0;

    // inverse graph
    vector<int> F_inv[N];
    for (int i = 0; i < N; ++i) F_inv[F[i]].push_back(i);

    bool visited[N];
    std::fill(visited, visited + N, false);

    std::function<int(int,int)> dfs_get_tree_height = [&](int node, int prev_node) -> int
    {
        visited[node] = true;

        int max_height = 0;
        for (size_t i = 0; i < F_inv[node].size(); ++i)
        {
            auto child = F_inv[node][i];
            if (child != prev_node) max_height = max(max_height, dfs_get_tree_height(child, node) + 1);
        }
        return max_height;
    };

    int distance[N];
    std::fill(distance, distance + N, -1);

    std::function<void(int,int)> dfs_find_cycle = [&](int node, int dist)
    {
        if (distance[node] >= 0) // found cycle
        {
            auto cycle_len = dist - distance[node];

            // visit connected component
            // and find two longest chains that come to the cycle in F_inv
            int max_chain_len1 = 0;
            int max_chain_len2 = 0;

            auto prev_node = node;
            auto cur_node = F[prev_node];
            for (int i = 0; i < cycle_len; ++i, prev_node = cur_node, cur_node = F[prev_node])
            {
                auto height = dfs_get_tree_height(cur_node, prev_node);
                if (height > max_chain_len1) max_chain_len2 = max_chain_len1, max_chain_len1 = height;
                else if (height > max_chain_len2) max_chain_len2 = height;
            }

            if (cycle_len == 2)
            {
                max_chain_len_sum += max_chain_len1 + max_chain_len2 + 2;
            }
            else
            {
                max_cycle_len = max(max_cycle_len, cycle_len);
            }
        }
        else
        {
            distance[node] = dist;
            dfs_find_cycle(F[node], dist + 1);
        }
    };

    // find cycle in each connected component
    for (int node = 0; node < N; ++node)
    {
        if (!visited[node]) dfs_find_cycle(node, 0);
    }

    return max(max_cycle_len, max_chain_len_sum);
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        int F[N];
        for (int i = 0; i < N; ++i)
        {
            cin >> F[i];
            --F[i];
        }

        cout << "Case #" << t << ": " << solve(F, N) << '\n';
    }

    return 0;
}
