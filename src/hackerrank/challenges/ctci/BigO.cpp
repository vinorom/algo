/**
 * Problem:
 *      Cracking the Coding Interview: Time Complexity: Primality
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-big-o
 */

#include <iostream>

using namespace std;

bool is_prime(int n)
{
    assert(n >= 1);

    if (n == 1) return false;

    for (int i = 2; i*i <= n; ++i)
    {
        if (n % i == 0) return false;
    }

    return true;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int p;
        cin >> p;
        cout << (is_prime(p) ? "Prime" : "Not prime") << '\n';
    }
    return 0;
}
