/**
 * Problem:
 *      Distinct primes factors
 *
 * Links:
 *      https://projecteuler.net/problem=47
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler047
 */

#include <iostream>

using namespace std;

int count_prime_factors(int a)
{
    int count = 0;
    for (int i = 2; i * i < a; ++i)
    {
        if (a % i == 0)
        {
            ++count;
            while (a % i == 0) a /= i;
        }
    }
    return a == 1 ? count : ++count;
}

int main()
{
    int N, K;
    cin >> N >> K;

    int count = 0;
    for (int i = 1; i < N + K; ++i)
    {
        if (count_prime_factors(i) == K)
        {
            ++count;
            if (count >= K) cout << (i - K + 1) << endl;
        }
        else
        {
            count = 0;
        }
    }

    return 0;
}
