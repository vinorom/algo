/**
 * Problem:
 *       Pandigital prime
 *
 * Links:
 *      https://projecteuler.net/problem=41
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler041
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

typedef long long ll;
typedef bitset<10> dmask;

vector<ll> pandigital_primes;

bool is_prime(ll v)
{
    if (v < 2) return false;
    for (ll f = 2; f * f <= v; ++f)
    {
        if (v % f == 0) return false;
    }
    return true;
}

void dfs(ll v, int dv, dmask& dm, int n)
{
    if (dv == 0)
    {
        if (is_prime(v)) pandigital_primes.push_back(v);
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (!dm[i])
        {
            dm[i] = true;
            dfs(v * 10 + i, dv - 1, dm, n);
            dm[i] = false;
        }
    }
}

void precompute_pandigital_primes()
{
    dmask dm;
    for (int i = 1; i <= 9; ++i) dfs(0, i, dm, i);
}

ll find_max_pandigital_prime(ll N)
{
    // sequence of pandigital primes is sorted by construction
    vector<ll>::iterator it = upper_bound(pandigital_primes.begin(), pandigital_primes.end(), N);
    return (it == pandigital_primes.begin()) ? -1 : *(--it);
}

int main()
{
    precompute_pandigital_primes();

    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        cout << find_max_pandigital_prime(N) << endl;
    }

    return 0;
}
