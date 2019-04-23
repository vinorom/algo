/**
 * Link: https://codility.com/programmers/lessons/17-dynamic_programming/number_solitaire/
 */

#include <vector>

using namespace std;

int solution(vector<int>& a)
{
    assert(!a.empty());

    int n = (int)a.size();
    vector<int> dp(n, 0);

    dp[0] = a[0];

    for (int i = 1; i < n; ++i)
    {
        dp[i] = dp[i-1] + a[i];
        for (int j = 2; j <= 6 && i - j >= 0; ++j) dp[i] = max(dp[i], dp[i-j] + a[i]);
    }

    return dp.back();
}

int main()
{
    return 0;
}
