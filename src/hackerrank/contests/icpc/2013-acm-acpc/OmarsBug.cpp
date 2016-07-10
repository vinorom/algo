/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/omars-bug
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, X, Y;
        cin >> N >> X >> Y;

        int i = 0;
        int cur = 1;
        for (; i < N - 1; ++i, ++cur)
        {
            if (Y == 1 && cur == X) cur = X + 1;
            cout << cur << ' ';
        }

        if (Y == 1 && cur == X) cur = X + 1;
        else if (Y == 2 && cur < X) cur = X;
        cout << cur << ' ' << '\n';
    }

    return 0;
}
