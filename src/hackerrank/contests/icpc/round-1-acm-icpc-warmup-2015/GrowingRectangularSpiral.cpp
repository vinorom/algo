/**
 * https://www.hackerrank.com/contests/round-1-acm-icpc-warmup-2015/challenges/growing-rectangular-spiral
 */

#include <iostream>

using namespace std;

int main()
{
    int P;
    cin >> P;

    while (P--)
    {
        int K, x, y;
        cin >> K >> x >> y;

        if (x == y)
        {
            cout << K << " NO PATH" << endl;
        }
        else if (x < y)
        {
            cout << K << ' ' << 2 << ' ' << x << ' ' << y << endl;
        }
        else // x > y
        {
            if (x > 1 && y > 3)
            {
                cout << K << " 6 1 2 3 " << (x-y+5) << ' ' << (x+2) << ' ' << (x+3) << endl;
            }
            else
            {
                cout << K << " NO PATH" << endl;
            }
        }
    }

    return 0;
}
