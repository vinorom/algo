/**
 * Problem:
 *      Multiples of 3 and 5
 *
 * Links:
 *      https://projecteuler.net/problem=1
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler001
 */

#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        ll k = (N - 1) / 3;
        ll sum = 3 * (1 + k) * k / 2;
        k = (N - 1) / 5;
        sum += 5 * (1 + k) * k / 2;
        k = (N - 1) / 15;
        sum -= 15 * (1 + k) * k / 2;
        cout << sum << endl;
    }
    return 0;
}
