/**
 * Problem:
 *       Number spiral diagonals
 *
 * Links:
 *      https://projecteuler.net/problem=28
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler028
 */

#include <iostream>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll mul_mod(ll a, ll b, ll m) // = a*b (mod m)
{
    if (b == 0) return 0;
    ll res = mul_mod(a, b / 2, m);
    res += res;
    if (b & 1) res += a;
    return ll(res % m);
}

ll sum_diag(ll N)
{
    ll s1 = 0;
    switch (N % 3)
    {
        case 0: s1 = mul_mod(N/3*2, mul_mod(N+1, N+2, MOD), MOD); break;
        case 1: s1 = mul_mod((N+2)/3*2, mul_mod(N, N+1, MOD), MOD); break;
        case 2: s1 = mul_mod((N+1)/3*2, mul_mod(N, N+2, MOD), MOD); break;
    }
    ll s2 = mul_mod(3, mul_mod(N+3, (N-1)/2, MOD), MOD) + 3;
    ll s3 = mul_mod(3, N-1, MOD);

    ll res = (s1 + s3) % MOD;
    res = (res + MOD - s2) % MOD;
    return res;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        cout << sum_diag(N) << endl;
    }
    return 0;
}
