/**
 * https://www.hackerrank.com/contests/2014-icpc-central-europe-regional-contest-practice/challenges/the-imp
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 150001;
const int MAXK = 10;

struct item
{
    ll cost;
    ll value;
    item(): cost(0), value(0) {}
};

ll dp[MAXN][MAXK];

ll solve(const vector<item>& items, int k)
{
    int n = (int)items.size();

    item opt_item = items[n-1];
    dp[n-1][0] = opt_item.value - opt_item.cost;
    for (int i = n - 2; i >= 0; --i)
    {
        if (items[i].value - items[i].cost > opt_item.value - opt_item.cost) opt_item = items[i];
        dp[i][0] = opt_item.value - opt_item.cost;
    }
    for (int q = 0; q <= k; ++q) dp[n][q] = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        for (int q = 1; q <= k; ++q)
        {
            dp[i][q] = max(dp[i+1][q], min(items[i].value - items[i].cost, -items[i].cost + dp[i+1][q-1]));
        }
    }

    return dp[0][k];
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, k;
        cin >> n >> k;

        vector<item> items(n);
        for (int i = 0; i < n; ++i) cin >> items[i].value >> items[i].cost;

        sort(begin(items), end(items), [](item lhv, item rhv) { return lhv.value < rhv.value; });

        cout << solve(items, k) << endl;
    }

    return 0;
}
