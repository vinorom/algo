/**
 * http://code.google.com/codejam/contest/11254486/dashboard#s=p0
 */

#include <bits/stdc++.h>

using namespace std;

#define IDX(c) (int)(c - 'A')
#define SUB(counts, s, iters) for (auto c: s) counts[IDX(c)] -= iters;

string solve(const string& str)
{
    int counts[27];
    fill(counts, counts + 27, 0);
    for (auto c: str) counts[IDX(c)]++;

    int digits[10];
    fill(digits, digits + 10, 0);

    digits[0] = counts[IDX('Z')];
    SUB(counts, "ZERO", digits[0]);

    digits[2] = counts[IDX('W')];
    SUB(counts, "TWO", digits[2]);

    digits[4] = counts[IDX('U')];
    SUB(counts, "FOUR", digits[4]);

    digits[5] = counts[IDX('F')];
    SUB(counts, "FIVE", digits[5]);

    digits[6] = counts[IDX('X')];
    SUB(counts, "SIX", digits[6]);

    digits[7] = counts[IDX('S')];
    SUB(counts, "SEVEN", digits[7]);

    digits[8] = counts[IDX('G')];
    SUB(counts, "EIGHT", digits[8]);

    digits[1] = counts[IDX('O')];
    SUB(counts, "ONE", digits[1]);

    digits[3] = counts[IDX('T')];
    SUB(counts, "THREE", digits[3]);

    digits[9] = counts[IDX('I')];
    SUB(counts, "NINE", digits[9]);

    for (auto c: counts) assert(c == 0);

    stringstream ss;
    for (int i = 0; i < 10; ++i) ss << string(digits[i], '0' + i);

    return ss.str();
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        string s;
        cin >> s;

        cout << "Case #" << t << ": " << solve(s) << '\n';
    }

    return 0;
}
