/**
 * Problem:
 *       Maximum path sum I
 *
 * Links:
 *      https://projecteuler.net/problem=18
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler018
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;

        int row[N];
        int totals[N];
        for (int i = 0; i < N; ++i)
        {
            row[i] = 0;
            totals[i] = 0;

            int total_prev = 0;
            for (int j = 0; j <= i; ++j)
            {
                cin >> row[j];

                int total_new = max(total_prev, totals[j]) + row[j];
                total_prev = totals[j];
                totals[j] = total_new;
            }
        }

        int total_max = *std::max_element(totals, totals + N);
        cout << total_max << endl;
    }

    return 0;
}
