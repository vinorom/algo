/**
 * https://www.hackerrank.com/contests/w17/challenges/find-the-robot
 */

#include <iostream>

using namespace std;

typedef pair<int, int> point;

point solve(int N)
{
    int cycles = N / 4;
    int rest = N % 4;
    int x = -2 * cycles;
    int y = -2 * cycles;
    switch (rest)
    {
        case 1: x += N; break;
        case 2: x += N - 1; y += N; break;
        case 3: x -= 2; y += N - 1; break;
    }
    return point(x, y);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        point p = solve(N);
        cout << p.first << ' ' << p.second << endl;
    }
    return 0;
}
