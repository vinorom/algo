/**
 * Problem:
 *      Largest prime factor
 *
 * Links:
 *      https://projecteuler.net/problem=3
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler003
 */

#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;

ll max_prime_factor(ll N)
{
    ll f = 2;
    while (f <= sqrt(N))
    {
        if (N % f == 0)
        {
            N /= f;
        }
        else
        {
            ++f;
        }
    }
    return max(N, f);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        ll factor = max_prime_factor(N);
        cout << factor << endl;
    }
    return 0;
}
