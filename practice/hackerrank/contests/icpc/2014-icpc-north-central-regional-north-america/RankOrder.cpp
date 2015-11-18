/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/rank-order
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1000000;

PII scores[2][MAXN];

int main()
{
    int N, t = 1;
    while (cin >> N)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> scores[i][j].first;
                scores[i][j].second = j;
            }
            sort(scores[i], scores[i] + N, greater<PII>());
        }

        int j;
        for (j = 0; j < N && scores[0][j].second == scores[1][j].second; ++j);

        cout << "Case " << t++ << ": " << (j == N ? "agree" : to_string(j+1)) << endl;
    }

    return 0;
}
