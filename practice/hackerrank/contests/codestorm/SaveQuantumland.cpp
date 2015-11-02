/**
 * https://www.hackerrank.com/contests/codestorm/challenges/save-quantumland
 */

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        int extra_guards = 0;
        int last_guard = -1;
        for (int i = 0; i < n; ++i)
        {
            int guard;
            cin >> guard;

            if (guard)
            {
                last_guard = i;
            }
            else if (i - last_guard > 1)
            {
                ++extra_guards;
                last_guard = i;
            }
        }

        cout << extra_guards << endl;
    }

    return 0;
}
