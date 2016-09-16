/**
 * Problem:
 *       Prime summations
 *
 * Links:
 *      https://projecteuler.net/problem=77
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler077
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

static const int MAXN = 1000;

vector<int> primes;
bool is_prime[MAXN];

void precompute_primes()
{
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < MAXN; ++i)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j < MAXN; j += i) is_prime[j] = false;
        }
    }
}

ll solve(int N)
{
    vector<ll> dp(N+1);
    dp[0] = 1;

    for (size_t i = 0; i < primes.size(); ++i)
    {
        for (int j = primes[i]; j <= N; ++j)
        {
            dp[j] += dp[j-primes[i]];
        }
    }

    return dp[N];
}

int main()
{
    precompute_primes();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << solve(N) << '\n';
    }

    return 0;
}
