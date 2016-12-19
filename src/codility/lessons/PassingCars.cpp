/**
 * Link: https://codility.com/programmers/lessons/5-prefix_sums/passing_cars/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a)
{
    int n = (int)a.size();

    vector<int> suffix_sum(n, 0);
    for (int i = n - 1; i >= 0; --i)
    {
        if (i < n - 1) suffix_sum[i] = suffix_sum[i+1];
        suffix_sum[i] += a[i];
    }

    int count = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (a[i] == 0) count += suffix_sum[i+1];
        if (count > 1000000000) return -1;
    }

    return count;
}

int main()
{
    return 0;
}
