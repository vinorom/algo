/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/wet-tiles
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

enum cell { DRY, LEAKED, WALL };

const int MAXN = 1000;

cell house[MAXN][MAXN];

void dump(int X, int Y)
{
    for (int j = Y - 1; j >= 0; --j)
    {
        for (int i = 0; i < X; ++i)
        {
            cell c = house[i][j];
            char ch = '.';
            if (c == WALL) ch = 'W';
            else if (c == LEAKED) ch = 'X';
            cout << ch;
        }
        cout << '\n';
    }
    cout << endl;
}

int count_wet_tiles_in_house(int X, int Y, const vector<PII>& leaks, int T)
{
    vector<PII> leakline[2];
    vector<PII>* cur = &leakline[0];
    vector<PII>* next = &leakline[1];

    *cur = leaks;
    for (int i = 0; i < (int)cur->size(); ++i)
    {
        PII p = (*cur)[i];
        house[p.first][p.second] = LEAKED;
    }

    //dump(X, Y);

    for (int i = 1; i < T && !cur->empty(); ++i, swap(cur, next))
    {
        next->clear();
        for (int j = 0; j < (int)cur->size(); ++j)
        {
            PII p = (*cur)[j];
            int x = p.first, y = p.second;

            if (x > 0 && house[x-1][y] == DRY) house[x-1][y] = LEAKED, next->push_back(PII(x-1, y));
            if (x < X - 1 && house[x+1][y] == DRY) house[x+1][y] = LEAKED, next->push_back(PII(x+1, y));
            if (y > 0 && house[x][y-1] == DRY) house[x][y-1] = LEAKED, next->push_back(PII(x, y-1));
            if (y < Y - 1 && house[x][y+1] == DRY) house[x][y+1] = LEAKED, next->push_back(PII(x, y+1));
        }

        //dump(X, Y);
    }

    int leaks_count = 0;
    for (int i = 0; i < X; ++i)
    {
        leaks_count += count_if(house[i], house[i] + Y, [](cell c) { return c == LEAKED; });
    }

    return leaks_count;
}

int main()
{
    int X, Y; // X - width, Y - height
    int T, L, W;
    while ((cin >> X) && X != -1)
    {
        cin >> Y >> T >> L >> W;

        for (int i = 0; i < X; ++i) fill(house[i], house[i] + Y, DRY);

        vector<PII> leaks(L);
        for (int i = 0; i < L; ++i)
        {
            cin >> leaks[i].first >> leaks[i].second;
            --leaks[i].first, --leaks[i].second;
        }


        for (int i = 0; i < W; ++i)
        {
            PII ws, we;
            cin >> ws.first >> ws.second >> we.first >> we.second;
            --ws.first, --ws.second, --we.first, --we.second;

            int dh = (we.first - ws.first);
            int dv = (we.second - ws.second);
            dh = dh ? dh / abs(dh) : 0;
            dv = dv ? dv / abs(dv) : 0;

            for (; ws != we; ws.first += dh, ws.second += dv) house[ws.first][ws.second] = WALL;
            house[we.first][we.second] = WALL;
        }

        cout << count_wet_tiles_in_house(X, Y, leaks, T) << endl;
    }

    return 0;
}
