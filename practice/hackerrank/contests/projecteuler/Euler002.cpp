/**
 * Problem:
 *      Even Fibonacci numbers
 *
 * Links:
 *      https://projecteuler.net/problem=2
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler002
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll even_fib_sum(ll N)
{
    ll f[3] = { 1, 2, 0 };
    ll sum = f[1];
    for (int i = 2; ; ++i)
    {
        f[i%3] = f[(i+1)%3] + f[(i+2)%3];
        if (f[i%3] > N) break;
        if (f[i%3] % 2 == 0) sum += f[i%3];
    }
    return sum;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        cout << even_fib_sum(N) << endl;
    }
    return 0;
}
