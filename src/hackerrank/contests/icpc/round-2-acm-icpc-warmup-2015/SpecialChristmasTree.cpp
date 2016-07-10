/**
 * https://www.hackerrank.com/contests/round-2-acm-icpc-warmup-2015/challenges/special-christmas-tree
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll solve(int H, int L)
{
    ll nodes = H + 1;
    ll n = H;
    ll pow2 = 2;
    for (; pow2 <= L; pow2 <<= 1, --n)
    {
        nodes += (pow2 >> 1) * n;
    }
    nodes += (L - (pow2 >> 1)) * n;
    return nodes;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        int H, L;
        cin >> H >> L;
        cout << "Case " << t << ": " << solve(H, L) << endl;
    }
    return 0;
}
