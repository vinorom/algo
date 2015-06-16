/**
 * Problem:
 *      Summation of primes
 *
 * Links:
 *      https://projecteuler.net/problem=10
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler010
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAX = 2000001;
ll sum[MAX] = { 0 };

int main()
{
    // pre-compute
    vector<bool> is_prime(MAX, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i < MAX; ++i)
    {
        sum[i] = sum[i-1];
        if (is_prime[i])
        {
            sum[i] += i;
            for (ll j = 2*i; j < MAX; j += i) is_prime[j] = false;
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << sum[N] << endl;
    }

    return 0;
}
