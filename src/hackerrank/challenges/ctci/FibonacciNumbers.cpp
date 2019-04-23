/**
 * Problem:
 *      Cracking the Coding Interview: Recursion: Fibonacci Numbers
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-fibonacci-numbers
 */

#include <vector>
#include <iostream>

using namespace std;

static const int MAXN = 50;

int fibonacci(int n)
{
    if (n < 0) return -1;

    static vector<int> cache{0, 1};

    if (cache.size() > (size_t)n) return cache[n];

    auto res = fibonacci(n - 1) + fibonacci(n - 2);
    cache.resize(n + 1);
    cache[n] = res;

    return res;
}

int main()
{
    int n;
    cin >> n;
    cout << fibonacci(n);
    return 0;
}

