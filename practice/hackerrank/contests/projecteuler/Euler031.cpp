/**
 * Problem:
 *       Coin sums
 *
 * Links:
 *      https://projecteuler.net/problem=31
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler031
 */

#include <iostream>

using namespace std;

const int MOD = 1000000007;
const int MAX = 100000;
const int DENOM_COUNT = 8;

int denoms[DENOM_COUNT] = { 1, 2, 5, 10, 20, 50, 100, 200 };
int change[MAX+1];

void precompute()
{
    std::fill(change, change + MAX + 1, 0);
    change[0] = 1;
    for (int i = 0; i < DENOM_COUNT; ++i)
    {
        for (int j = denoms[i]; j <= MAX; ++j)
        {
            change[j] += change[j - denoms[i]];
            change[j] %= MOD;
        }
    }
}

int main()
{
    precompute();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << change[N] << endl;
    }
    return 0;
}
