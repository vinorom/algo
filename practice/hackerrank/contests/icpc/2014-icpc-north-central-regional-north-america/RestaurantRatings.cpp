/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/restaurant-ratings
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 16; // 15
const int MAXS = 30;

ll cache[MAXN+1][MAXS+1];

void precompute()
{
    for (int j = 1; j <= MAXS; ++j) cache[0][j] = 0;
    for (int i = 0; i <= MAXN; ++i) cache[i][0] = 1;

    for (int i = 1; i <= MAXN; ++i)
    {
        for (int j = 1; j <= MAXS; ++j)
        {
            cache[i][j] = cache[i][j-1] + cache[i-1][j];
        }
    }
}

ll solve(int ratings[], int N)
{
    int S = accumulate(ratings, ratings + N, 0);
    ll count = S == 0 ? 0 : cache[N+1][S-1]; // worse rating sum
    for (int i = 1; i <= N; ++i) // equal sum but worse score based on individual critic check
    {
        count += cache[N-i+1][S] - cache[N-i+1][S-ratings[i-1]];
        S -= ratings[i-1];
    }
    ++count; // equal score
    return count;
}

int main()
{
    precompute();

    int N, t = 1;
    while ((cin >> N) && N > 0)
    {
        int ratings[N];
        for (int i = 0; i < N; ++i) cin >> ratings[i];

        ll answer = solve(ratings, N);
        cout << "Case " << t++ << ": " << answer << endl;
    }
    return 0;
}
