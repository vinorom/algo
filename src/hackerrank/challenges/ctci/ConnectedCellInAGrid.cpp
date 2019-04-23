/**
 * Problem:
 *      Cracking the Coding Interview: DFS: Connected Cell in a Grid
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid
 */

#include <vector>
#include <iostream>

using namespace std;

using grid_t=vector<vector<bool>>;


bool is_filled(const grid_t& grid, int x, int y)
{
    auto n = grid.size();
    auto m = grid[0].size();

    if (x < 0 || x >= n || y < 0 || y >= m) return false;

    return grid[x][y];
}

int dfs(const grid_t& grid, int x, int y, grid_t& visited)
{
    if (!is_filled(grid, x, y) || visited[x][y]) return 0;

    visited[x][y] = true;

    int count = 1 + dfs(grid, x - 1, y - 1, visited) + dfs(grid, x - 1, y, visited) + dfs(grid, x - 1, y + 1, visited) +
                dfs(grid, x, y - 1, visited) + dfs(grid, x, y + 1, visited) +
                dfs(grid, x + 1, y - 1, visited) + dfs(grid, x + 1, y, visited) + dfs(grid, x + 1, y + 1, visited);

    return count;
}

int solve(const grid_t& grid)
{
    auto n = grid.size();
    if (n == 0) return 0;
    auto m = grid[0].size();

    grid_t visited(n, vector<bool>(m, false));

    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (grid[i][j] && !visited[i][j]) res = max(res, dfs(grid, i, j, visited));
        }
    }

    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;

    grid_t grid(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int a;
            cin >> a;
            grid[i][j] = a;
        }
    }

    cout << solve(grid) << '\n';

    return 0;
}

