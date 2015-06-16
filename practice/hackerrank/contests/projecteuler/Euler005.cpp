/**
 * Problem:
 *      Smallest multiple
 *
 * Links:
 *      https://projecteuler.net/problem=5
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler005
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
    if (a > b) swap(a, b);
    if (a == 0) return b;
    return gcd(a, b % a);
}

ll lcm(int N)
{
    ll l = 1;
    for (int i = 2; i <= N; ++i)
    {
        l = l * i / gcd(l, i);
    }
    return l;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << lcm(N) << endl;
    }
    return 0;
}
