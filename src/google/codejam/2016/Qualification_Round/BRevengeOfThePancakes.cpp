/**
 * http://code.google.com/codejam/contest/6254486/dashboard#s=p1
 */

#include <iostream>
#include <cassert>

using namespace std;

int solve(const string& s)
{
    int count = 0;
    for (size_t i = 1; i < s.size(); ++i)
    {
        if (s[i] != s[i-1]) ++count;
    }
    if (s.back() == '-') ++count;
    return count;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        string s;
        cin >> s;
        assert(!s.empty());
        cout << "Case #" << t << ": " << solve(s) << '\n';
    }

    return 0;
}
