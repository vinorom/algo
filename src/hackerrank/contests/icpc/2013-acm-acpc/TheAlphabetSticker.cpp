/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/the-alphabet-sticker
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MOD = 1000000007;

int mul_mod(int a, int b, int m)
{
    if (b == 0) return 0;
    ll res = mul_mod(a, b/2, m);
    res *= 2;
    if (b & 1) res += a;
    return int(res % m);
}

int solve(string& s)
{
    int count = 1;

    size_t pos = s.find_first_of('?', s.find_first_not_of('?'));
    size_t end = s.find_last_of('?', s.find_last_not_of('?'));

    if (pos == string::npos || end == string::npos) return count;

    for (size_t posn = s.find_first_not_of('?', pos); posn <= end + 1; posn = s.find_first_not_of('?', pos))
    {
        if (s[pos-1] != s[posn]) count = mul_mod(count, posn - pos + 1, MOD);
        pos = s.find_first_of('?', posn);
    }

    return count;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        string s;
        cin >> s;
        cout << solve(s) << endl;
    }

    return 0;
}
