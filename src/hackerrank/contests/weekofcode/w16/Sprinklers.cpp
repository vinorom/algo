/**
 * https://www.hackerrank.com/contests/w16/challenges/sprinklers
 */

#include <iostream>
#include <vector>

using namespace std;

int count_sprinklers(int N, const vector<int>& p, int e, vector<int>* pout = 0)
{
    int i = 0;
    for (; i + 1 < p.size() && p[i+1] - e <= 1; ++i);
    int count = 1;
    if (pout) pout->push_back(p[i]);
    for (; p[i] + e < N; )
    {
        int tmp = i;
        for (; i + 1 < p.size() && p[i+1] - p[tmp] <= 2 * e + 1; ++i);
        count++;
        if (pout) pout->push_back(p[i]);
    }
    return count;
}

void solve(int N, const vector<int>& p, int S, int Q, int& E, vector<int>& pout)
{
    // find minimal possible E
    E = max(p[0] - 1, N - p.back());
    for (int i = 1; i < p.size(); ++i) E = max(E, (p[i] - p[i - 1]) / 2);
    int opt_cost = (int)p.size() * S + E * Q;

    for (int e = E; e < N; )
    {
        int count = count_sprinklers(N, p, e);
        int cost = count * S + e * Q;
        if (cost < opt_cost)
        {
            E = e;
            opt_cost = cost;
        }

        // find next e that gives different number of sprinklers
        int l = e;
        int r = N;
        while (l + 1 < r)
        {
            int mid = (l + r) / 2;
            if (count_sprinklers(N, p, mid) != count)
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
        e = r;
    }

    // E is optimal here, find positions to set up sprinklers
    count_sprinklers(N, p, E, &pout);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, M, S, Q;
        cin >> N >> M >> S >> Q;
        vector<int> p(M), pout;
        for (int i = 0; i < M; ++i) cin >> p[i];

        int E;
        solve(N, p, S, Q, E, pout);
        cout << pout.size() << " " << E << endl;
        for (int i = 0; i < pout.size(); ++i) cout << (i > 0 ? " " : "") << pout[i];
        cout << endl;
    }

    return 0;
}
