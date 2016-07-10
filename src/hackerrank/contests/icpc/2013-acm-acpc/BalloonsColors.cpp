/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/balloons-colors
 */

#include <iostream>

using namespace std;

const string ANSWERS[] = { "OKAY", "EASY", "HARD", "BOTH" };

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, X, Y;
        cin >> N >> X >> Y;

        int answer = 0;
        for (int i = 0; i < N; ++i)
        {
            int color;
            cin >> color;
            if (i == 0 && color == X) answer += 1;
            if (i == N - 1 && color == Y) answer += 2;
        }

        cout << ANSWERS[answer] << endl;
    }

    return 0;
}
