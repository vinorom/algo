/**
 * Problem:
 *      Largest product in a series
 *
 * Links:
 *      https://projecteuler.net/problem=8
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler008
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, K;
        cin >> N >> K;
        string n;
        cin >> n;

        int max_product = 0;
        for (int i = 0; i < N - 7; ++i)
        {
            int p = 1;
            for (int j = i; j < i + K; ++j) p *= int(n[j] - '0');
            max_product = max(max_product, p);
        }

        cout << max_product << endl;
    }
    return 0;
}
