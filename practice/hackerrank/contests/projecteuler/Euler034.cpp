/**
 * Problem:
 *       Digit factorials
 *
 * Links:
 *      https://projecteuler.net/problem=34
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler034
 */

#include <iostream>

using namespace std;

int factorials[10];

void precompute()
{
    for (int i = 0, f = 1; i < 10; ++i, f *= i) factorials[i] = f;
}

int get_digit_factorial_sum(int n)
{
    int sum = 0;
    while (n)
    {
        sum += factorials[n % 10];
        n /= 10;
    }
    return sum;
}

//#define ORIGINAL_EULER_PROBLEM

int solve(int N)
{
    precompute();

    int sum = 0;
    for (int i = 10; i < N; ++i)
    {
#ifdef ORIGINAL_EULER_PROBLEM
        if (get_digit_factorial_sum(i) == i) // N=10^7
#else
        if (get_digit_factorial_sum(i) % i == 0)
#endif
        {
            sum += i;
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
