/**
 * Problem:
 *      Cracking the Coding Interview: DP: Coin Change
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-coin-change
 */

#include <iostream>

using namespace std;

long long solve(int n, int c[], int m)
{
    long long dp[n+1];
    std::fill(dp, dp + n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < m; ++i)
    {
        for (int j = c[i]; j <= n; ++j) dp[j] += dp[j-c[i]];
    }
    return dp[n];
}

int main()
{
    int n, m;
    cin >> n >> m;
    int c[m];
    for (int i = 0; i < m; ++i) cin >> c[i];
    cout << solve(n, c, m) << '\n';
    return 0;
}
