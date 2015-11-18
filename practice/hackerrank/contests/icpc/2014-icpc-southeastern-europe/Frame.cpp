/**
 * https://www.hackerrank.com/contests/2014-icpc-southeastern-europe/challenges/frame
 */

#include <iostream>

using namespace std;

int main()
{
    int x, y;
    cin >> x >> y;

    int n;
    cin >> n;

    while (n--)
    {
        int a;
        cin >> a;

        bool x0 = x % a == 0;
        bool x1 = (x-1) % a == 0;
        bool x2 = (x-2) % a == 0;
        bool y0 = y % a == 0;
        bool y1 = (y-1) % a == 0;
        bool y2 = (y-2) % a == 0;

        bool answer = (x1 && y1) || (x1 && y0 && y2) || (y1 && x0 && x2) || (x0 && y2) || (y0 && x2);

        cout << (answer ? "YES" : "NO") << endl;
    }

    return 0;
}
