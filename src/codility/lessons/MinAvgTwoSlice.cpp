/**
 * Link: https://codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(const vector<int>& a)
{
    int n = (int)a.size();

#define UPDATE_MIN_AVG(avg, pos) if (min_avg > avg) min_avg = avg, p = pos;

    int p = 0;
    auto min_avg = numeric_limits<double>::max();
    for (int i = 1; i < n; ++i)
    {
        UPDATE_MIN_AVG((a[i-1]+a[i]) / 2.0, i - 1);
        if (i > 1) UPDATE_MIN_AVG((a[i-2]+a[i-1]+a[i]) / 3.0, i - 2);
    }
    return p;

#undef UPDATE_MIN_AVG
}

int main()
{
    return 0;
}
