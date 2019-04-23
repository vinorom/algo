/**
 * Problem:
 *      Permuted multiples
 *
 * Links:
 *      https://projecteuler.net/problem=52
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler052
 */

#include <iostream>

using namespace std;

bool check_mult(int n, int K)
{
    int n1 = n;
    int digits1[10];
    fill(digits1, digits1 + 10, 0);
    while (n1) digits1[n1 % 10]++, n1 /= 10;

    int digitsk[10];
    for (int k = 2; k <= K; ++k)
    {
        int n2 = k * n;
        fill(digitsk, digitsk + 10, 0);
        while (n2) digitsk[n2 % 10]++, n2 /= 10;

        for (int i = 0; i < 10; ++i)
        {
            if (digits1[i] != digitsk[i]) return false;
        }
    }

    return true;
}

int main()
{
    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; ++i)
    {
        if (check_mult(i, K))
        {
            for (int k = 1; k <= K; ++k) cout << (k * i) << ' ';
            cout << '\n';
        }
    }

    return 0;
}
