/**
 * https://www.hackerrank.com/contests/code-cpp-september-2015/challenges/feighbours
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<int /*factor*/, int /*feighbour*/> factor2feighbour_map;
factor2feighbour_map f2f;

void update_feighbour_for_factor(int factor, int idx, int& feighbour)
{
    // find feighbour and store current mapping
    factor2feighbour_map::iterator it = f2f.find(factor);
    if (it != f2f.end())
    {
        feighbour = min(feighbour, it->second + 1);
        it->second = idx;
    }
    else
    {
        f2f[factor] = idx;
    }
}

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    vector<int> f(N, N + 1); // feighbours, fill in with max

    // back to front
    for (int i = N - 1; i >= 0; --i)
    {
        int v = a[i];
        // factorization
        for (int j = 2; j*j <= v; ++j)
        {
            if (v % j == 0)
            {
                while (v % j == 0) v /= j;
                update_feighbour_for_factor(j, i, f[i]);
            }
        }
        if (v != 1) update_feighbour_for_factor(v, i, f[i]);
        if (f[i] == N + 1) f[i] = -1;
    }

    for (int i = 0; i < N; ++i) cout << f[i] << ' ';
    cout << endl;

    return 0;
}
