/**
 * Problem:
 *       Truncatable primes
 *
 * Links:
 *      https://projecteuler.net/problem=37
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler037
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll solve(int N)
{
    bool is_prime[N];
    std::fill(is_prime, is_prime + N, true);
    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i < N; ++i)
    {
        if (is_prime[i])
        {
            for (ll j = i*i; j < N; j += i) is_prime[j] = false;
        }
    }

    ll sum = 0;
    for (int i = 8; i < N; ++i)
    {
        if (is_prime[i])
        {
            bool trunc_prime = true;
            for (int pow10 = 10; i / pow10 != 0 && trunc_prime; pow10 *= 10)
            {
                if (!is_prime[i / pow10] || !is_prime[i % pow10]) trunc_prime = false;
            }

            if (trunc_prime) sum += i;
        }
    }

    return sum;
}

int main()
{
    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}
