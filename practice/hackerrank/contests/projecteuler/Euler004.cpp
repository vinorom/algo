/**
 * Problem:
 *      Largest palindrome product
 *
 * Links:
 *      https://projecteuler.net/problem=4
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler004
 */

#include <iostream>

using namespace std;

bool is_product(int p)
{
    for (int i = 999; i >= 100; --i)
    {
        if (p % i == 0 && p / i <= i && p / i >= 100) return true;
    }
    return false;
}

int max_palindrome_product(int N)
{
    for (int a = 9; a >= 1; --a)
    {
        int p = 100001 * a;
        if (p >= N) continue;
        for (int b = 9; b >= 0; --b)
        {
            if (p + 10010 * b >= N) continue;
            for (int c = 9; c >= 0; --c)
            {
                int p1 = p + 10010 * b + 1100 * c;
                if (p1 < N && is_product(p1)) return p1;
            }
        }
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << max_palindrome_product(N) << endl;
    }
    return 0;
}
