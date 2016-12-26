/**
 * Link: https://codility.com/programmers/lessons/14-binary_search_algorithm/min_max_division/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(int k, int m, vector<int>& a)
{
    assert(!a.empty());

    int n = (int)a.size();

    auto min_sum = *max_element(a.begin(), a.end());
    if (k >= n) return min_sum;

    auto max_sum = accumulate(a.begin(), a.end(), 0);
    if (k == 1) return max_sum;

    while (min_sum < max_sum)
    {
        auto mid_sum = (min_sum + max_sum) / 2;

        int sum = 0;
        int count = 0;
        for (auto ai : a)
        {
            sum += ai;
            if (sum > mid_sum)
            {
                sum = ai;
                ++count;
            }
            if (count == k) break;
        }

        if (count == k)
        {
            min_sum = mid_sum + 1;
        }
        else
        {
            max_sum = mid_sum;
        }
    }

    return min_sum;
}

int main()
{
    vector<int> a{2, 1, 5, 1, 2, 2, 2};
    cout << solution(3, 5, a) << endl;
    return 0;
}
