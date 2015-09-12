/**
 * Problem:
 *      Sub-string divisibility
 *
 * Links:
 *      https://projecteuler.net/problem=43
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler043
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int DIVISORS[] = { 1, 1, 1, 1, 2, 3, 5, 7, 11, 13, 17 };

void check_pandigital(ll val, int mask, int digits, int N, ll& sum)
{
    if (digits > 3 && (val % 1000) % DIVISORS[digits]) return;

    if (mask == (1 << (N + 1)) - 1) sum += val;

    for (int i = 0; i <= N; ++i)
    {
        if ((mask & (1 << i)) == 0)
        {
            check_pandigital(val * 10 + i, mask | (1 << i), digits + 1, N, sum);
        }
    }
}

int main()
{
    int N;
    cin >> N;
    ll sum = 0;
    check_pandigital(0, 0, 0, N, sum);
    cout << sum << endl;
    return 0;
}
