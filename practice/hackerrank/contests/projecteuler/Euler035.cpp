/**
 * Problem:
 *       Circular primes
 *
 * Links:
 *      https://projecteuler.net/problem=35
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler035
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 1000000;
bool is_prime[MAXN];
vector<int> primes;

void precompute_primes()
{
    std::fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i < MAXN; ++i)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (ll j = i*i; j < MAXN; j += i) is_prime[j] = false;
        }
    }
}

//#define ORIGINAL_EULER_PROBLEM

ll solve(int N)
{
    ll res = 0;
    int max_pow10 = 1;
    for (int i = 0; i < primes.size() && primes[i] < N; ++i)
    {
        int prime = primes[i];

        while (prime / max_pow10) max_pow10 *= 10;

        bool circular_prime = true;
        for (int pow10 = 10; pow10 < max_pow10 && circular_prime; pow10 *= 10)
        {
            int circular = (prime % pow10) * (max_pow10 / pow10) + prime / pow10;
            if (!is_prime[circular]) circular_prime = false;
        }

        if (circular_prime)
#ifdef ORIGINAL_EULER_PROBLEM
            ++res; // count
#else
            res += prime; // sum
#endif
    }
    return res;
}

int main()
{
    precompute_primes();

    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}
