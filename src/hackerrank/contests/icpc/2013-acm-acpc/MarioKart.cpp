/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/mario-kart
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct coin
{
    int cost, power;
    coin(): cost(), power() {}
};

int get_min_moves(int stations[], int N, coin coins[], int M, int L)
{
    sort(stations, stations + N);

    int D = stations[N-1] - stations[0];

    // DP: find all possible subsets of coins, i.e. all possible moves
    // O(M*D)
    typedef pair<bool, int /*min cost*/> PBI;
    PBI dp[D+1][M+1];

    for (int j = 0; j <= M; ++j) dp[0][j] = PBI(true, 0);
    for (int i = 1; i <= D; ++i) fill(dp[i], dp[i] + M + 1, PBI(false, L + 1));

    for (int i = 1; i <= D; ++i)
    {
        for (int j = 1; j <= M; ++j)
        {
            coin c = coins[j-1];
            dp[i][j] = dp[i][j-1];
            if (c.power <= i && dp[i-c.power][j-1].first && dp[i-c.power][j-1].second + c.cost <= L)
            {
                dp[i][j] = PBI(true, min(dp[i][j].second, dp[i-c.power][j-1].second + c.cost));
            }
        }
    }

    // make up a graph where two nodes are connected by edge iff it is possible to move between them
    // O(N^2)
    vector<int> adj[N];
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            int d = stations[j] - stations[i];
            if (dp[d][M].first)
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // BFS: find the path between first and last stations
    int distance[N];
    fill(distance, distance + N, -1);

    queue<int> q;
    distance[0] = 0;
    q.push(0);

    while (!q.empty() && q.front() != N - 1)
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (distance[v] == -1)
            {
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }

    return distance[N-1];
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, M, L;
        cin >> N >> M >> L;

        int stations[N];
        for (int i = 0; i < N; ++i) cin >> stations[i];

        coin coins[M];
        for (int i = 0; i < M; ++i) cin >> coins[i].cost >> coins[i].power;

        cout << get_min_moves(stations, N, coins, M, L) << endl;
    }

    return 0;
}
