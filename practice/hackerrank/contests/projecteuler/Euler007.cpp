/**
 * Problem:
 *      10001st prime
 *
 * Links:
 *      https://projecteuler.net/problem=7
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler007
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAX = 120000;

int main()
{
    vector<bool> is_prime(MAX, true);
    vector<int> primes;
    for (ll i = 2; i < MAX; ++i)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (ll j = i*i; j < MAX; j += i) is_prime[j] = false;
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << primes[N-1] << endl;
    }

    return 0;
}
