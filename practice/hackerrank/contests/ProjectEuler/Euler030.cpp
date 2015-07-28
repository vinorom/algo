/**
 * Problem:
 *       Digit Nth powers
 *
 * Links:
 *      https://projecteuler.net/problem=30
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler030
 */

#include <iostream>

using namespace std;

const int MAX = 9999999;

int pow(int a, int b)
{
    if (b == 0) return 1;
    int res = pow(a, b/2);
    return res * res * (b & 1 ? a : 1);
}

int solve(int N)
{
    int pows[10];
    for (int i = 0; i < 10; ++i) pows[i] = pow(i, N);

    int sum_total = 0;
    for (int i = 10; i <= MAX; ++i)
    {
        int sum_pow_digits = 0;
        for (int n = i; n; n /= 10) sum_pow_digits += pows[n % 10];
        if (sum_pow_digits == i) sum_total += i;
    }

    return sum_total;
}

int main()
{
    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}
