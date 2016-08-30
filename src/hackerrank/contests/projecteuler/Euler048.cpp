/**
 * Problem:
 *      Self powers
 *
 * Links:
 *      https://projecteuler.net/problem=48
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler048
 */

#include <iostream>

using namespace std;

typedef long long ll;

static const ll MOD = 10000000000ll;

ll mult_mod(ll a, ll b, ll M) // (a * b) mod M
{
    if (b == 0) return 0;
    ll res = mult_mod(a, b / 1000, M);
    res *= 1000;
    if (b % 1000) res += a * (b % 1000);
    return res % M;
}

ll pow_mod(ll a, ll b, ll M) // (a ^ b) mod M
{
    if (b == 0) return 1;
    ll res = pow_mod(a, b / 2, M);
    res = mult_mod(res, res, M);
    if (b & 1) res = mult_mod(res, a, M);
    return res;
}

ll solve(ll N)
{
    ll res = 0;
    for (ll i = 1; i <= N; ++i)
    {
        res += pow_mod(i, i, MOD);
        res %= MOD;
    }
    return res;
}

int main()
{
    int N;
    cin >> N;

    cout << solve(N) << endl;

    return 0;
}
