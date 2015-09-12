/**
 * Problem:
 *      Largest product in a grid
 *
 * Links:
 *      https://projecteuler.net/problem=11
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler011
 */

#include <iostream>

using namespace std;

int dr[] = { 1, 1, 1, 0 };
int dc[] = { -1, 0, 1, 1 };

int main()
{
    const int N = 20;
    int grid[N][N];

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j) cin >> grid[i][j];
    }

    int max_product = -1;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int dir = 0; dir < 4; ++dir)
            {
                int r = i+dr[dir]*3;
                int c = j+dc[dir]*3;
                if (r < 0 || r >= N || c < 0 || c >= N) continue;

                int product = 1;
                for (int step = 0; step < 4; product *= grid[i+dr[dir]*step][j+dc[dir]*step], ++step);
                max_product = max(max_product, product);
            }
        }
    }

    cout << max_product << endl;

    return 0;
}
