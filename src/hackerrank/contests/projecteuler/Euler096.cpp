/**
 * Problem:
 *      Su Doku
 *
 * Links:
 *      https://projecteuler.net/problem=96
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler096
 */

#include <iostream>
#include <vector>

using namespace std;

class sudoku
{
public:
    static const char GAP = '0';

    char grid[9][9];

public:
    void read()
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j) cin >> grid[i][j];
        }
    }

    void dump() const
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j) cout << grid[i][j];
            cout << endl;
        }
    }

    bool solve()
    {
        vector<char> values;
        int row_gap = -1, col_gap = -1;
        for (int i = 0; i < 9 && row_gap < 0; ++i)
        {
            for (int j = 0; j < 9 && col_gap < 0; ++j)
            {
                if (grid[i][j] == GAP)
                {
                    row_gap = i;
                    col_gap = j;
                }
            }
        }

        if (row_gap < 0) return true;

        find_possible_values(row_gap, col_gap, values);
        for (char v : values)
        {
            grid[row_gap][col_gap] = v;
            if (solve()) return true;
            grid[row_gap][col_gap] = GAP;
        }

        return false;
    }

private:
    void find_possible_values(int row, int col, vector<char>& values) const
    {
        values.clear();
        int mask = 0;
        for (int i = 0; i < 9; ++i)
        {
            if (grid[row][i] != GAP) mask |= 1 << to_digit(grid[row][i]);
            if (grid[i][col] != GAP) mask |= 1 << to_digit(grid[i][col]);
            if (grid[row/3*3+i/3][col/3*3+i%3] != GAP) mask |= 1 << to_digit(grid[row/3*3+i/3][col/3*3+i%3]);
        }
        mask = ~mask & ((1 << 10) - 1);
        for (int i = 1; i <= 9; ++i)
        {
            if ((mask & (1 << i)) != 0) values.push_back(to_char(i));
        }
    }

    static int to_digit(char c) { return c - '0'; }
    static char to_char(int d)  { return '0' + d; }
};

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    sudoku s;

#ifdef ORIGINAL_EULER_PROBLEM
    int T;
    string test;
    cin >> T;
    int sum = 0;
    for (int i = 1; i <= T; ++i)
    {
        s.read();
        s.solve();
        cout << i << ':' << endl;
        s.dump();
        sum += std::stoi(string(s.grid[0], 3));
    }
    cout << "sum=" << sum << endl;
#else
    s.read();
    s.solve();
    s.dump();
#endif

    return 0;
}
