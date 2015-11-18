/**
 * https://www.hackerrank.com/contests/godaddy-hackathon/challenges/hexagonal-war
 */

#include <iostream>
#include <vector>

using namespace std;

enum owner { NONE = 0, ROMANS, PERSIANS };

const int dr[] = { -1, 1,  0, 0, -1,  1 };
const int dc[] = {  0, 0, -1, 1,  1, -1 };

typedef vector<short> row;
typedef vector<row> grid;

int N;
grid g, visited;

bool dfs(short owner, int r, int c, bool horiz)
{
    visited[r][c] = 1;

    if ((horiz && c == N - 1) || (!horiz && r == N - 1)) return true;

    for (int i = 0; i < 6; ++i)
    {
        int rn = r + dr[i];
        int cn = c + dc[i];
        if (rn >= 0 && rn < N && cn >= 0 && cn < N && g[rn][cn] == owner && !visited[rn][cn])
        {
            if (dfs(owner, rn, cn, horiz)) return true;
        }
    }
    return false;
}

bool dfs_loop(short owner, bool horiz)
{
    visited.resize(N, row(N, 0));
    for (int i = 0; i < N; ++i)
    {
        int r = horiz ? i : 0;
        int c = horiz ? 0 : i;
        if (g[r][c] == owner && !visited[r][c] && dfs(owner, r, c, horiz)) return true;
    }
    return false;
}

int main()
{
    int M;
    cin >> N >> M;

    g.assign(N, row(N, NONE));
    for (int i = 0, parity = 0; i < M; ++i, parity ^= 1)
    {
        int row, col;
        cin >> row >> col;
        --row, --col;
        g[row][col] = parity == 0 ? ROMANS : PERSIANS;
    }

    string answer("NEITHER");
    if (dfs_loop(ROMANS, true))
    {
        answer = "ROMANS";
    }
    else if (dfs_loop(PERSIANS, false))
    {
        answer = "PERSIANS";
    }
    cout << answer << endl;

    return 0;
}
