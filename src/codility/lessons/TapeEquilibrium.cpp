/**
 * Link: https://codility.com/programmers/lessons/3-time_complexity/tape_equilibrium/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a)
{
    int n = (int)a.size();
    vector<int> prefix_sum(n);
    for (int i = 0; i < n; ++i) prefix_sum[i] = (i > 0 ? prefix_sum[i-1] : 0) + a[i];

    int min_diff = abs(prefix_sum.back() - prefix_sum.front() * 2);
    for (int i = 1; i < n - 2; ++i) min_diff = min(min_diff, abs(prefix_sum.back() - prefix_sum[i] * 2));

    return min_diff;
}

int main()
{
    return 0;
}
