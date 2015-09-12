/**
 * Problem:
 *      Sum square difference
 *
 * Links:
 *      https://projecteuler.net/problem=6
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler006
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
        ll N;
        cin >> N;

        ll sum_sqr = 0;
        for (ll i = 1; i <= N; ++i) sum_sqr += i * i;
        ll sqr_sum = (1 + N) * N / 2;
        sqr_sum *= sqr_sum;
        cout << (sqr_sum - sum_sqr) << endl;
    }
    return 0;
}
