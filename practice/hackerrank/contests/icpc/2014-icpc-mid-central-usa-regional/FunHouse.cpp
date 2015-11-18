/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/fun-house
 */

#include <iostream>

using namespace std;

typedef pair<int, int> PII;

void find_exit(string room[], int W, int L)
{
    int i;
    size_t pose;
    for (i = 0; (pose = room[i].find('*')) == string::npos; ++i);
    PII cur(i, (int)pose);

    int dv = (cur.first > 0 && cur.first < L - 1) ? 0 : (cur.first == 0 ? 1 : -1);
    int dh = (cur.second > 0 && cur.second < W - 1) ? 0 : (cur.second == 0 ? 1 : -1);

    while (room[cur.first][cur.second] != 'x')
    {
        cur.first += dv;
        cur.second += dh;
        char c = room[cur.first][cur.second];
        switch (c)
        {
            case '/': dv = -dv, dh = -dh;
            case '\\': swap(dv, dh);
                break;
        }
    }

    room[cur.first][cur.second] = '&';
}

int main()
{
    int t = 1;
    int W, L;
    while ((cin >> W >> L) && W * L != 0)
    {
        string room[L];
        for (int i = 0; i < L; ++i) cin >> room[i];

        find_exit(room, W, L);

        cout << "HOUSE " << t++ << '\n';
        for (int i = 0; i < L; ++i) cout << room[i] << '\n';
    }
    return 0;
}
