/**
 * Problem:
 *       Champernowne's constant
 *
 * Links:
 *      https://projecteuler.net/problem=40
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler040
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll get_digit(ll idx)
{
    ll count = 0;
    ll d = 1;
    ll scale = 1;
    for (; idx >= (d * scale + count) * 9; count = d * scale + count, ++d, scale *= 10);

    ll rem = idx - count * 9;
    ll num_idx = rem / d;
    ll digit_idx = rem % d;

    ll num = scale + num_idx;
    for (; digit_idx < d - 1; ++digit_idx, num /= 10);

    return num % 10;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N = 7;
        ll answer = 1;

        for (int i = 0; i < N; ++i)
        {
            ll idx;
            cin >> idx;

            answer *= get_digit(idx - 1);
        }

        cout << answer << '\n';
    }

    return 0;
}
