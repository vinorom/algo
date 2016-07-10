/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/server
 */

#include <iostream>

using namespace std;

int main()
{
    int n, T, tc = 1;
    while (cin >> n)
    {
        cin >> T;

        int answer = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int v;
            cin >> v;
            sum += v;
            if (sum <= T) answer = i + 1;
        }

        cout << "Case " << tc++ << ": " << answer << endl;
    }

    return 0;
}
