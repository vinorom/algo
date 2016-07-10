/**
 * Problem:
 *       Quadratic primes
 *
 * Links:
 *      https://projecteuler.net/problem=27
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler027
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAX = 7000000;
vector<bool> primes(MAX, true);

void precompute_primes()
{
    for (ll i = 2; i < MAX; i += (i & 1) ? 2 : 1)
    {
        if (primes[i])
        {
            for (ll j = i * i; j < MAX; j += i) primes[j] = false;
        }
    }
}

int count_primes(int a, int b)
{
    // n^2 + a*n + b
    int n = 0;
    for (; n*n+a*n+b > 0 && primes[n*n+a*n+b]; ++n);
    return n;
}

pair<int, int> solve(int N)
{
    int max_count_primes = 0;
    int max_a = 0;
    int max_b = 0;
    for (int a = -N; a < N; ++a)
    {
        for (int b = 1; b < N; ++b) // b > 0
        {
            int count = count_primes(a, b);
            if (max_count_primes < count)
            {
                max_count_primes = count;
                max_a = a;
                max_b = b;
            }
        }
    }
    return make_pair(max_a, max_b);
}

int main()
{
    precompute_primes();

    int N;
    cin >> N;
    pair<int, int> coef = solve(N);
    cout << coef.first << " " << coef.second << endl;

    return 0;
}
