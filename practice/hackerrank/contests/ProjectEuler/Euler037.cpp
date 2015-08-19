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
    ll sum = 0;

    bool is_prime[N];
    std::fill(is_prime, is_prime + N, true);
    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i < N; ++i)
    {
        if (is_prime[i])
        {
            for (ll j = i*i; j < N; j += i) is_prime[j] = false;

            int pow10 = 1;
            ll v = i;
            while (v / pow10 != 0 && is_prime[v / pow10] && (pow10 == 1 || is_prime[v % pow10])) pow10 *= 10;

            if (i > 7 && v / pow10 == 0) sum += i;
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
