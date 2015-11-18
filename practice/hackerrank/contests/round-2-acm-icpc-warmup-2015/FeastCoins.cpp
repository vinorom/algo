/**
 * https://www.hackerrank.com/contests/round-2-acm-icpc-warmup-2015/challenges/feast-coins
 */

#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int MAXS = 5001;
const int MAXN = 51;

ll dp[MAXS][MAXN];

ll subset_sum_count(PII coins[], int N, int S, int k /*required number of coins of each value*/)
{
    for (int i = 0; i <= N; ++i) dp[0][i] = 1;
    for (int j = 1; j <= S; ++j) dp[j][0] = 0;

    for (int i = 1; i <= S; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            PII coin = coins[j-1];
            dp[i][j] = dp[i][j-1];
            if (coin.first <= i && coin.second >= k)
            {
                dp[i][j] += dp[i-coin.first][j-1];
            }
        }
    }

    return dp[S][N];
}

ll solve(PII coins[], int N, int S)
{
    ll count = 0;
    for (int k = 1; k * k <= S; ++k)
    {
        if (S % k == 0)
        {
            count += subset_sum_count(coins, N, S / k, k);
            if (k * k != S) count += subset_sum_count(coins, N, k, S / k);
        }
    }
    return count;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int S, N;
        cin >> S >> N;

        PII coins[N];
        for (int i = 0; i < N; ++i) cin >> coins[i].first >> coins[i].second;

        cout << "Case " << t << ": " << solve(coins, N, S) << endl;
    }

    return 0;
}
