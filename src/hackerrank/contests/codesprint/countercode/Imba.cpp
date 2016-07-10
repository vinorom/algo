/**
 * https://www.hackerrank.com/contests/countercode/challenges/imba
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
        if (N % 2 == 1) cout << (N / 2 + 1) << ' ';
        for (int i = N / 2; i >= 1; --i) cout << i << ' ' << (N - i + 1) << ' ';
        cout << endl;
    }
    return 0;
}
