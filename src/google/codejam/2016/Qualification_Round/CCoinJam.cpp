/**
 * http://code.google.com/codejam/contest/6254486/dashboard#s=p2
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXM = 100000000;
const int MAXBASE = 10;

bitset<MAXM> not_prime;
vector<ll> primes;

void precompute()
{
    not_prime[0] = not_prime[1] = 1;
    for (int i = 2; i * i < MAXM; ++i)
    {
        if (!not_prime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j < MAXM; j += i) not_prime[j] = 1;
        }
    }
}

bool check_jamcoin(int n, ll v, int base, ll mod)
{
    ll rem = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        rem = (rem * base + ((v >> i) & 1)) % mod;
    }
    rem = (rem * base + 1) % mod;
    return rem == 0;
}

int main()
{
    precompute();

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n, j;
        cin >> n >> j;
        n -= 2;

        cout << "Case #" << t << ":\n";

        ll divisors[MAXBASE+1];
        for (ll i = 0; i < (1 << n) && j > 0; ++i)
        {
            divisors[MAXBASE] = 0;
            for (int base = 2; base <= MAXBASE; ++base)
            {
                divisors[base] = 0;
                for (auto p : primes)
                {
                    if (check_jamcoin(n, i, base, p))
                    {
                        divisors[base] = p;
                        break;
                    }
                }
                if (!divisors[base]) break;
            }
            if (divisors[MAXBASE])
            {
                --j;
                cout << '1';
                for (int k = n - 1; k >= 0; --k) cout << ((i >> k) & 1);
                cout << '1';
                for (int base = 2; base <= MAXBASE; ++base) cout << ' ' << divisors[base];
                cout << '\n';
            }
        }
        assert(j == 0);
    }

    return 0;
}
