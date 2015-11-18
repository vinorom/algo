/**
 * https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-weird-sum
 */

#include <iostream>

using namespace std;

int to_digit(char c) { return c - '0'; }
char from_digit(int digit) { return char('0' + digit); }

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string N, M;
        cin >> N >> M;

        size_t size = max(N.size(), M.size());
        N = string(size - N.size(), '0') + N;
        M = string(size - M.size(), '0') + M;

        string weird_sum(size, '0');
        bool overhead = false;
        for (size_t i = 0; i < size; ++i)
        {
            int s = to_digit(N[i]) + to_digit(M[i]);
            if (s > 9 || overhead)
            {
                s = 9;
                overhead = true;
            }
            weird_sum[i] = from_digit(s);
        }

        cout << weird_sum << endl;
    }
    return 0;
}
