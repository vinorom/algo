/**
 * https://www.hackerrank.com/contests/round-2-acm-icpc-warmup-2015/challenges/game-of-peace
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 72;

ll fibonacci[MAXN];

void precompute_fibonacci()
{
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    for (int i = 2; i < MAXN; ++i)
    {
        fibonacci[i] = fibonacci[i-2] + fibonacci[i-1];
    }
}

ll gcd(ll a, ll b)
{
    if (a > b) swap(a, b);
    return a == 0 ? b : gcd(b % a, a);
}

ll solve(int X, int N, int Y, int /*M*/)
{
    return gcd(fibonacci[N+1] * X + Y, fibonacci[N] * X);
}

int main()
{
    precompute_fibonacci();

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        int X, N, Y, M;
        cin >> X >> N >> Y >> M;
        cout << "Case " << t << ": " << solve(X, N, Y, M) << endl;
    }

    return 0;
}
