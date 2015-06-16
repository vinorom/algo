/**
 * Problem:
 *      Lattice paths
 *
 * Links:
 *      https://projecteuler.net/problem=15
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler015
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MOD = 1000000007;
const int MAX = 500;

ll paths[MAX + 1][MAX + 1]; // [X][Y] = [Y][X] = number of paths in X x Y grid

ll count_lattice_paths(int N, int M)
{
    if (paths[N][M] != 0) return paths[N][M];
    ll count = count_lattice_paths(N-1, M) + count_lattice_paths(N, M-1);
    count %= MOD;
    paths[N][M] = paths[M][N] = count;
    return count;
}

int main()
{
    paths[0][0] = 0;
    for (int i = 1; i <= MAX; ++i)
    {
        paths[i][0] = paths[0][i] = 1;
        for (int j = 1; j <= MAX; ++j) paths[i][j] = paths[j][i] = 0;
    }

    int T;
    cin >> T;
    while (T--)
    {
        int N, M;
        cin >> N >> M;
        cout << count_lattice_paths(N, M) << endl;
    }

    return 0;
}
