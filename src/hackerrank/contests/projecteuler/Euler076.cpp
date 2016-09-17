/**
 * Problem:
 *       Counting summations
 *
 * Links:
 *      https://projecteuler.net/problem=76
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler076
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

static const ll MOD = 1000000007;

int get_pentagonal_number(int k) { return k * (3 * k - 1) / 2; }

ll get_partition_count(int n)
{
    //https://en.wikipedia.org/wiki/Partition_(number_theory)

    static vector<ll> part_func;

    if (n < 0) return 0;
    if (n < part_func.size()) return part_func[n];

    ll pn = 0;
    if (n == 0)
    {
        pn = 1;
    }
    else
    {
        for (int k = 1, sign = 1; ; ++k, sign *= -1)
        {
            auto gk1 = get_pentagonal_number(k);
            auto pk1 = get_partition_count(n - gk1);
            pn += sign * pk1;

            auto gk2 = get_pentagonal_number(-k);
            auto pk2 = get_partition_count(n - gk2);
            pn += sign * pk2;

            while (pn < 0) pn += MOD;
            pn %= MOD;

            if (pk1 == 0 && pk2 == 0) break;
        }
    }

    part_func.resize((size_t)(n + 1));
    part_func[n] = pn;

    return pn;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << (get_partition_count(N) - 1) << '\n';
    }

    return 0;
}
