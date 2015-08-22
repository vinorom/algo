/**
 * Problem:
 *      Highly divisible triangular number
 *
 * Links:
 *      https://projecteuler.net/problem=12
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler012
 */

#include <iostream>

using namespace std;

const int MAXN = 1000;
int divisible_numbers[MAXN+1];

int count_divisors(int a)
{
    // number factorization: a = p1^k1 * p2^k2 * ... pn^kn
    // where pi are prime divisors
    // then number of divisors is (k1+1)*(k2+1)*...*(kn+1)

    int divisors = 1;
    for (int i = 2; i*i <= a; ++i)
    {
        int count = 0;
        for (; a % i == 0; a /= i, ++count);
        divisors *= count + 1;
    }
    if (a != 1) divisors *= 2;
    return divisors;
}

void precompute()
{
    int a = 0;
    for (int i = 1, n = 1; n <= MAXN; ++i)
    {
        a += i;
        int divisors = count_divisors(a);
        while (divisors > n && n <= MAXN) divisible_numbers[n++] = a;
    }
}

int main()
{
    precompute();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << divisible_numbers[N] << endl;
    }

    return 0;
}
