/**
 * Problem:
 *      Goldbach's other conjecture
 *
 * Links:
 *      https://projecteuler.net/problem=46
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler046
 */

#include <iostream>

using namespace std;

const int MAXN = 500000;
bool is_prime[MAXN];

void precompute_primes()
{
    std::fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i < MAXN; ++i)
    {
        if (is_prime[i])
        {
            for (int j = i*i; j < MAXN; j += i) is_prime[j] = false;
        }
    }
}

bool is_composite(int a)
{
    return a > 1 && !is_prime[a];
}

int count_goldbach_forms(int N)
{
    int count = 0;
    for (int i = 1; i*i*2 < N; ++i)
    {
        if (is_prime[N-i*i*2]) ++count;
    }
    return count;
}

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    precompute_primes();

#ifdef ORIGINAL_EULER_PROBLEM
    for (int i = 1; i < MAXN; i += 2)
    {
        if (is_composite(i) && count_goldbach_forms(i) == 0)
        {
            cout << i << endl;
            break;
        }
    }
#else
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << count_goldbach_forms(N) << endl;
    }
#endif

    return 0;
}
