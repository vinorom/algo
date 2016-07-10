/**
 * https://www.hackerrank.com/contests/2014-icpc-central-europe-regional-contest-practice/challenges/sums
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        bool found = false;
        for (int len = 2; N > (len - 1) * len / 2; ++len)
        {
            int diff = N - (len - 1) * len / 2;
            if (diff % len == 0)
            {
                int start = diff / len;

                cout << N << " = " << start;
                for (int j = start + 1; j < start + len; ++j) cout << " + " << j;
                cout << '\n';

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}