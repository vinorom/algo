/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/more-multiplication
 */

#include <iostream>

using namespace std;

void solve(const int A, const int B)
{
    int a = A, b = B;
    int da[4] = {0}, db[4] = {0};
    int na = 0, nb = 0;
    for (; a; da[na++] = a % 10, a /= 10);
    for (; b; db[nb++] = b % 10, b /= 10);

    int n = nb * 4 + 5, m = na * 4 + 5;
    string grid[n];
    for (int i = 0; i < n; ++i) grid[i].assign(m, ' ');

    for (int i = 1; i < m - 1; ++i) grid[0][i] = grid[n-1][i] = '-';
    for (int i = 1; i < n - 1; ++i) grid[i][0] = grid[i][m-1] = '|';
    grid[0][0] = grid[0][m-1] = grid[n-1][0] = grid[n-1][m-1] = '+';
    for (int i = 0; i < nb; ++i)
    {
        for (int j = 0; j < na; ++j)
        {
            for (int k = 1; k < 4; ++k)
            {
                grid[2+i*4][2+j*4+k] = grid[2+(i+1)*4][2+j*4+k] = '-';
                grid[2+i*4+k][2+j*4] = grid[2+i*4+k][2+(j+1)*4] = '|';
            }
            grid[2+i*4][2+j*4] = grid[2+i*4][2+(j+1)*4] = grid[2+(i+1)*4][2+j*4] = grid[2+(i+1)*4][2+(j+1)*4] = '+';
            grid[2+i*4+1][2+(j+1)*4-1] = grid[2+i*4+2][2+(j+1)*4-2] = grid[2+i*4+3][2+(j+1)*4-3] = '/';
        }
    }

    for (int i = 0; i < na; ++i) grid[1][2+i*4+2] = '0' + da[na-1-i];
    for (int i = 0; i < nb; ++i) grid[2+i*4+2][m-2] = '0' + db[nb-1-i];

    for (int i = 0; i < nb; ++i)
    {
        for (int j = 0; j < na; ++j)
        {
            int p = db[nb-1-i] * da[na-1-j];
            grid[2+i*4+1][2+j*4+1] = '0' + (p / 10);
            grid[2+i*4+3][2+j*4+3] = '0' + (p % 10);
        }
    }

    int p = A * B;
    for (int i = 0; p && i < na; ++i)
    {
        grid[n-2][2+(na-1-i)*4+1] = '0' + (p % 10);
        if (i > 0) grid[n-2][2+(na-1-i)*4+3] = '/';
        p /= 10;
    }
    for (int i = 0; p && i < nb; ++i)
    {
        grid[2+(nb-1-i)*4+3][1] = '0' + (p % 10);
        grid[2+(nb-1-i)*4+5][1] = '/';
        p /= 10;
    }

    for (int i = 0; i < n; ++i)
    {
        cout << grid[i] << '\n';
    }
}

int main()
{
    int A, B;
    while ((cin >> A >> B) && A * B != 0)
    {
        solve(A, B);
    }
    return 0;
}
