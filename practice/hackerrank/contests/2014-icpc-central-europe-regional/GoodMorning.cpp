/**
 * https://www.hackerrank.com/contests/2014-icpc-central-europe-regional-contest-practice/challenges/good-morning
 */

#include <iostream>

using namespace std;

const int MAXN = 201;
bool is_possible[MAXN];

bool is_typing_possible(int a, int b)
{
    if (a == b) return true;
    if (b == 0) return a % 3 != 0;
    if (a == 0) return b == 0;
    return (a-1) % 3 <= (b-1) % 3 && (a-1) / 3 <= (b-1) / 3;
}

bool is_code_possible(int c)
{
    int d = c % 10;
    for (c /= 10; c; d = c % 10, c /= 10)
    {
        if (!is_typing_possible(c % 10, d)) return false;
    }
    return true;
}

void precompute()
{
    for (int i = 0; i < MAXN; ++i)
    {
        is_possible[i] = is_code_possible(i);
    }
}

int solve(int k)
{
    for (int i = 0; i <= k; ++i)
    {
        if (is_possible[k+i]) return k + i;
        if (is_possible[k-i]) return k - i;
    }
    return -1;
}

int main()
{
    precompute();

    int T;
    cin >> T;
    while (T--)
    {
        int k;
        cin >> k;
        cout << solve(k) << endl;
    }

    return 0;
}
