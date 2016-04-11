/**
 * http://code.google.com/codejam/contest/6254486/dashboard#s=p3
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

bool solve(int k, int c, int s, vector<ll>& tiles)
{
    if (s * c < k) return false;

    for (int i = 0; i < k; i += c)
    {
        ll powk = 1, tile = 1;
        for (int j = 1; j < c; ++j, powk *= k);
        for (int j = i; j < min(i + c, k); ++j, powk /= k)
        {
            tile += powk * j;
        }
        tiles.push_back(tile);
    }

    return true;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int k, c, s;
        cin >> k >> c >> s;

        cout << "Case #" << t << ": ";

        vector<ll> tiles;
        if (solve(k, c, s, tiles))
        {
            for (auto t : tiles) cout << t << ' ';
            cout << '\n';
        }
        else
        {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}
