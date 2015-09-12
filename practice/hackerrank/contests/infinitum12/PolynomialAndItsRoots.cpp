/**
 * https://www.hackerrank.com/contests/infinitum12/challenges/polynomial-and-its-roots
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

typedef long long ll;

ll compute_polynomial_value(ll* a /*ai*/, int n /*degree*/, ll x)
{
    ll res = 0;
    for (ll i = 0, xn = 1; i <= n; ++i, xn *= x) res += a[i] * xn;
    return res;
}

bool check_polynomial_root(ll* a, int n, ll x, vector<ll>& roots)
{
    if (x * compute_polynomial_value(a + 1, n - 1, x) != -a[0]) return false;

    roots.push_back(x);

    // update coefficients
    for (ll i = 1, d = -a[0]; i < n; ++i)
    {
        ll ai = a[i];
        a[i] = d / x;
        d = a[i] - ai;
    }

    return true;
}

void find_polynomial_roots(ll* a /*ai*/, int n /*degree*/, vector<ll>& roots)
{
    if (n < 1) return;

    ll& a0 = a[0];
    ll& a1 = a[1];
    ll abs_a0 = std::abs(a0);

    if (n == 1) // linear function
    {
        // a0 + a1*x = 0
        assert(a1 != 0); // a1 != 0, otherwise there is no root
        assert(abs_a0 % a1 == 0);
        roots.push_back(a0 == 0 ? 0 : -a0 / a1);
        return;
    }

    if (a0 == 0)
    {
        roots.push_back(0);
    }
    else
    {
        for (ll x = 1; x <= sqrt(abs_a0) + 1; ++x) // root should be among factors of a0 (consider negative factors too)
        {
            if (abs_a0 % x != 0) continue;

            if (check_polynomial_root(a, n, x, roots) ||
                check_polynomial_root(a, n, -x, roots) ||
                check_polynomial_root(a, n, a0 / x, roots) ||
                check_polynomial_root(a, n, -a0 / x, roots))
                break;
        }
    }

    find_polynomial_roots(a + 1, n - 1, roots);
}

int main()
{
    int N;
    cin >> N;
    ll a[N + 1];
    for (int i = 0; i <= N; ++i) cin >> a[i];

    vector<ll> roots;
    find_polynomial_roots(a, N, roots);
    ll sum = std::accumulate(roots.begin(), roots.end(), 0);
    ll product = std::accumulate(roots.begin(), roots.end(), 1, std::multiplies<ll>());
    cout << sum << ' ' << product << endl;

    return 0;
}
