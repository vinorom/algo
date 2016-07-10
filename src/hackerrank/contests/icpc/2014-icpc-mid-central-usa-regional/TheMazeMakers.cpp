/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/the-maze-makers
 */

#include <iostream>
#include <cassert>
#include <set>

using namespace std;

typedef pair<int, bool> PIB;
typedef pair<int, int> PII;

const int MAXH = 50;
const int MAXW = 50;

int H, W;
PIB maze[MAXH+1][MAXW+1];

bool dfs(PII pos, PII prev)
{
    if (pos.first < 0 || pos.first >= H || pos.second < 0 || pos.second >= W) return true;

    PIB& cell = maze[pos.first][pos.second];

    if (cell.second) return false; // already visited => multiple simple paths

    cell.second = true; // mark visisted

    PII top = PII(pos.first-1, pos.second);
    PII right = PII(pos.first, pos.second+1);
    PII bottom = PII(pos.first+1, pos.second);
    PII left = PII(pos.first, pos.second-1);

    bool res = true;

    if (top != prev && !(cell.first & 8)) res = dfs(top, pos) && res; // go up
    if (right != prev && !(cell.first & 4)) res = dfs(right, pos) && res; // go right
    if (bottom != prev && !(cell.first & 2)) res = dfs(bottom, pos) && res; // go down
    if (left != prev && !(cell.first & 1)) res = dfs(left, pos) && res; // go left

    return res;
}

string verify_maze()
{
    // mark all cells unvisited
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j) maze[i][j].second = false;
    }

    // find two exists
    set<PII> exits;
    for (int i = 0; i < W; ++i)
    {
        if (!(maze[0][i].first & 8)) exits.insert(PII(0, i)); // top
        if (!(maze[H-1][i].first & 2)) exits.insert(PII(H-1, i)); // bottom
    }
    for (int i = 0; i < H; ++i)
    {
        if (!(maze[i][0].first & 1)) exits.insert(PII(i, 0)); // left
        if (!(maze[i][W-1].first & 4)) exits.insert(PII(i, W-1)); // right
    }

    assert(exits.size() == 2);

    PII entry = *exits.begin();
    PII exit = *exits.rbegin();

    // find all reachable cells
    bool multiple_path = !dfs(entry, PII(-1, -1));

    if (!maze[exit.first][exit.second].second) return "NO SOLUTION";

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (!maze[i][j].second) return "UNREACHABLE CELL";
        }
    }

    if (multiple_path) return "MULTIPLE PATHS";

    return "MAZE OK";
}

int main()
{
    char h;
    while ((cin >> H >> W) && H * W != 0)
    {
        for (int i = 0; i < H; ++i)
        {
            for (int j = 0; j < W; ++j)
            {
                cin >> h;
                h = toupper(h);
                maze[i][j].first = h >= '0' && h <= '9' ? h - '0' : (h - 'A') + 10;
            }
        }

        cout << verify_maze() << endl;
    }
    return 0;
}
