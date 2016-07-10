/**
 * Problem:
 *       Pandigital products
 *
 * Links:
 *      https://projecteuler.net/problem=32
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler032
 */

#include <iostream>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

typedef long long ll;
typedef bitset<10> dmask;

set<ll> products;

bool check_pandigital_part(ll v, dmask& dm)
{
    for (ll d = v % 10; d && !dm[d]; v /= 10, d = v % 10) dm[d] = true;
    return v == 0;
}

bool check_pandigital_product(ll a, ll b, int N)
{
    dmask dm;
    return
        check_pandigital_part(a, dm) &&
        check_pandigital_part(b, dm) &&
        check_pandigital_part(a * b, dm) &&
        dm.to_ullong() == ((1 << N) - 1) << 1;
}

void dfs(ll a, ll b, int db, dmask& dm, int N)
{
    if (db == 0)
    {
        if (check_pandigital_product(a, b, N)) products.insert(a * b);
        return;
    }

    for (int i = 1; i <= N; ++i)
    {
        if (!dm[i])
        {
            dm[i] = true;
            dfs(a, b * 10 + i, db - 1, dm, N);
            dm[i] = false;
        }
    }
}

void find_pandigital_products(ll a, int N)
{
    // A * B = C where ABC - pandigital 1 to N
    // => dA = 1,2 where dX - number of digits of X
    // => dA + dB = (N + 1) / 2

    dmask dm;
    if (!check_pandigital_part(a, dm)) return;

    int da = (int)dm.count();
    int db = (N + 1) / 2 - da;

    dfs(a, 0, db, dm, N);
}

ll sum_pandigital_products(int N)
{
    for (int a = 1; a < 100; ++a) find_pandigital_products(a, N);
    return accumulate(products.begin(), products.end(), 0);
}

int main()
{
    int N;
    cin >> N;
    cout << sum_pandigital_products(N) << endl;
    return 0;
}
