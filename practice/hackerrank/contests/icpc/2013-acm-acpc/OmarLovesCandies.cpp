/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/omar-loves-candies
 */

#include <iostream>

using namespace std;

const int MAXN = 1001;

int grid[MAXN][MAXN];
int suffix_raw[MAXN][MAXN];

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, M;
        cin >> N >> M;

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j) cin >> grid[i][j];
        }

        for (int i = N - 1; i >= 0; --i)
        {
            for (int j = M - 1; j >= 0; --j)
            {
                suffix_raw[i][j] = grid[i][j] + (j < M - 1 ? suffix_raw[i][j+1] : 0);
            }
        }

        int max_score = suffix_raw[N-1][M-1];
        for (int j = 0; j < M; ++j)
        {
            int score = suffix_raw[N-1][j];
            for (int i = N - 2; i >= 0 && suffix_raw[i][j] > 0; --i)
            {
                score += suffix_raw[i][j];
            }
            max_score = max(max_score, score);
        }

        cout << max_score << endl;
    }

    return 0;
}
