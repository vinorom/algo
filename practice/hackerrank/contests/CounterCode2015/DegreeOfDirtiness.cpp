/**
 * https://www.hackerrank.com/contests/countercode/challenges/degree-of-dirtiness
 */

#include <iostream>

using namespace std;

pair<int, int> solve(int N, int M)
{
    int round = N & 1 ? 2 * N : N;
    int round_dirtiness = N & 1 ? 2 : 1;
    int dirtiness = (M / round) * round_dirtiness;
    int rem = M % round;

    if (rem == 0) return make_pair(N / 2 + 1, dirtiness - 1); // last person occupied the middle one

    if (rem <= N) return make_pair(rem & 1 ? rem / 2 + 1 : N - rem / 2 + 1, dirtiness);

    rem -= N;
    return make_pair(rem & 1 ? N - rem / 2 : rem / 2, dirtiness + 1);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, M;
        cin >> N >> M;
        pair<int, int> res = solve(N, M);
        cout << res.first << ' ' << res.second << endl;
    }
    return 0;
}
