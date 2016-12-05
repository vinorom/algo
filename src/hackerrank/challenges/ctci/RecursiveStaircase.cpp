/**
 * Problem:
 *      Cracking the Coding Interview: Recursion: Davis' Staircase
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-recursive-staircase
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 37;
ll count_ways[MAXN];

ll calc_num_ways_to_climb(int n)
{
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (count_ways[n] > 0) return count_ways[n];
    count_ways[n] = calc_num_ways_to_climb(n - 3) + calc_num_ways_to_climb(n - 2) + calc_num_ways_to_climb(n - 1);
    return count_ways[n];
}

int main()
{
    fill(count_ways, count_ways + MAXN, 0);
    calc_num_ways_to_climb(MAXN - 1);

    int s;
    cin >> s;
    while (s--)
    {
        int n;
        cin >> n;
        cout << calc_num_ways_to_climb(n) << '\n';
    }
    return 0;
}
