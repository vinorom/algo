/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/nassas-robot
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string signals;
        cin >> signals;

        int x = 0, y = 0, d = 0;
        for (size_t i = 0; i < signals.size(); ++i)
        {
            if (signals[i] == '?')
            {
                ++d;
            }
            else
            {
                switch (signals[i])
                {
                    case 'U': ++y; break;
                    case 'D': --y; break;
                    case 'L': --x; break;
                    case 'R': ++x; break;
                }
            }
        }

        cout << (x-d) << ' ' << (y-d) << ' ' << (x+d) << ' ' << (y+d) << endl;
    }

    return 0;
}
