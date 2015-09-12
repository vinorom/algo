/**
 * Problem:
 *       Double-base palindromes
 *
 * Links:
 *      https://projecteuler.net/problem=36
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler036
 */

#include <iostream>

using namespace std;

typedef unsigned long long ull; // enough to keep 20 digits, 2^20 > 10^6

ull reverse(ull a)
{
    ull rev = 0;
    while (a)
    {
        rev *= 10;
        rev += a % 10;
        a /= 10;
    }
    return rev;
}

bool is_palindromic(int a, int base)
{
    ull v = (ull)a;

    if (v % base == 0) return false;
    if (base == 10) return v == reverse(v);

    ull rev_base = 0;
    while (v)
    {
        rev_base *= 10;
        rev_base += v % base;
        v /= base;
    }

    return rev_base == reverse(rev_base);
}

int solve(int N, int K)
{
    int sum = 0;
    for (int i = 1; i < N; ++i)
    {
        if (is_palindromic(i, 10) && is_palindromic(i, K)) sum += i;
    }
    return sum;
}

int main()
{
    int N, K;
    cin >> N >> K;
    cout << solve(N, K) << endl;
    return 0;
}
