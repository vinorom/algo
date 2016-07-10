/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/the-stones-game
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, M, X;
        cin >> N >> M >> X;
        cout << ((N + M - X) % M == 0 ? "YES" : "NO") << endl;
    }

    return 0;
}
