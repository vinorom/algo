/**
 * https://www.hackerrank.com/contests/w15/challenges/sudoku-swap
 */
#include <cmath>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> Cell;
typedef set<Cell> Cells;
typedef pair<Cell, Cell> Swap;
typedef set<Swap> Swaps;

int sudoku[9][9];

Cell make_cell(int x, int y) { return make_pair(x, y); }
Swap make_swap(Cell from, Cell to) { return make_pair(from, to); }

template <class T>
bool operator==(pair<T,T> lhv, pair<T,T> rhv)
{
    return lhv.first == rhv.first && lhv.second == rhv.second;
}

template <class T>
bool operator!=(pair<T,T> lhv, pair<T,T> rhv)
{
    return !operator==(lhv, rhv);
}

template <class T>
bool operator<(pair<T,T> lhv, pair<T,T> rhv)
{
    if (lhv.first < rhv.first) return true;
    if (lhv.first == rhv.first && lhv.second < rhv.second) return true;
    return false;
}

template <class O>
O& operator<<(O& os, Cell c)
{
    os << '(' << (c.first+1) << ',' << (c.second+1) << ')';
    return os;
}

template <class O>
O& operator<<(O& os, Swap s)
{
    if (s.second < s.first) swap(s.first, s.second);

    os << s.first << " <-> " << s.second;
    return os;
}

bool check_cell(Cell c, Cells* dups = 0)
{
    bool mismatch = false;
    for (int i = 0; i < 9; ++i)
    {
        // row
        if (i != c.second && sudoku[c.first][i] == sudoku[c.first][c.second])
        {
            mismatch = true;
            if (dups) dups->insert(make_cell(c.first, i));
        }

        // column
        if (i != c.first && sudoku[i][c.second] == sudoku[c.first][c.second])
        {
            mismatch = true;
            if (dups) dups->insert(make_cell(i, c.second));
        }
    }

    // block
    Cell corner = make_cell((c.first/3)*3, (c.second/3)*3);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Cell c1 = make_cell(corner.first+i, corner.second+j);
            if (c != c1 && sudoku[c1.first][c1.second] == sudoku[c.first][c.second])
            {
                mismatch = true;
                if (dups) dups->insert(c1);
            }
        }
    }

    if (mismatch && dups) dups->insert(c);

    return !mismatch;
}

bool apply_swap(const Swap& s)
{
    int& a = sudoku[s.first.first][s.first.second];
    int& b = sudoku[s.second.first][s.second.second];
    if (a == b) return false;
    swap(a, b);
    return true;
}

void solve(Swaps& swaps)
{
    Cells set_dups;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            check_cell(make_cell(i, j), &set_dups);
        }
    }

    vector<Cell> dups(set_dups.begin(), set_dups.end());
    for (int d = 0; d < dups.size(); ++d)
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                Cell c = make_cell(i, j);
                Swap s = make_swap(dups[d], c);
                if (apply_swap(s))
                {
                    bool mismatch = !check_cell(c);
                    for (int d1 = 0; d1 < dups.size() && !mismatch; ++d1)
                    {
                        if (!check_cell(dups[d1])) mismatch = true;
                    }
                    if (!mismatch && swaps.find(make_swap(s.second, s.first)) == swaps.end()) swaps.insert(s);
                    apply_swap(s); // revert back
                }
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j) cin >> sudoku[i][j];
        }

        Swaps swaps;
        solve(swaps);

        cout << "Case #" << t << ":" << endl;
        if (swaps.empty())
        {
            cout << "Serendipity" << endl;
        }
        else
        {
            for (Swaps::iterator it = swaps.begin(); it != swaps.end(); ++it)
            {
                cout << (*it) << endl;
            }
        }
    }
    return 0;
}
