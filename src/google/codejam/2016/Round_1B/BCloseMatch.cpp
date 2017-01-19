/**
 * http://code.google.com/codejam/contest/11254486/dashboard#s=p1
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

pair<string, string> solve(const string& a, const string& b, ll& diff)
{
    assert(a.size() == b.size());

    auto ra = a;
    auto rb = b;

    size_t i = 0;
    for (; i < a.size(); ++i)
    {
        if (diff == 0)
        {
            if (a[i] == '?' || b[i] == '?') break;
            diff = a[i] - b[i];
        }
        else
        {
            auto ai = a[i];
            auto bi = b[i];
            if (diff < 0) // a < b
            {
                if (ai == '?') ai = '9';
                if (bi == '?') bi = '0';
            }
            else // a > b
            {
                if (ai == '?') ai = '0';
                if (bi == '?') bi = '9';
            }

            ra[i] = ai;
            rb[i] = bi;

            diff *= 10;
            diff += ai - bi;
        }
    }

    if (i == a.size()) return {ra, rb};

    pair<string, string> res;

    if (a[i] != '?')
    {
        res = solve(a.substr(i), string(1, a[i]) + b.substr(i+1), diff);

        auto bi1 = a[i] - 1;
        auto bi2 = a[i] + 1;

        if (bi1 >= '0')
        {
            ll diff1 = 0;
            auto res1 = solve(a.substr(i), string(1, bi1) + b.substr(i+1), diff1);
            if (abs(diff1) < abs(diff) || (abs(diff1) == abs(diff) && res1 < res)) res = res1, diff = diff1;
        }
        if (bi2 <= '9')
        {
            ll diff2 = 0;
            auto res2 = solve(a.substr(i), string(1, bi2) + b.substr(i+1), diff2);
            if (abs(diff2) < abs(diff)) res = res2, diff = diff2;
        }
    }
    else if (b[i] != '?')
    {
        res = solve(string(1, b[i]) + a.substr(i+1), b.substr(i), diff);

        auto ai1 = b[i] - 1;
        auto ai2 = b[i] + 1;

        if (ai1 >= '0')
        {
            ll diff1 = 0;
            auto res1 = solve(string(1, ai1) + a.substr(i+1), b.substr(i), diff1);
            if (abs(diff1) < abs(diff) || (abs(diff1) == abs(diff) && res1 < res)) res = res1, diff = diff1;
        }
        if (ai2 <= '9')
        {
            ll diff2 = 0;
            auto res2 = solve(string(1, ai2) + a.substr(i+1), b.substr(i), diff2);
            if (abs(diff2) < abs(diff)) res = res2, diff = diff2;
        }
    }
    else
    {
        res = solve(string("0") + a.substr(i+1), string("0") + b.substr(i+1), diff);

        ll diff01 = 0;
        auto res01 = solve(string("0") + a.substr(i+1), string("1") + b.substr(i+1), diff01);
        if (abs(diff01) < abs(diff)) res = res01, diff = diff01;

        ll diff10 = 0;
        auto res10 = solve(string("1") + a.substr(i+1), string("0") + b.substr(i+1), diff10);
        if (abs(diff10) < abs(diff)) res = res10, diff = diff10;
    }

    return {ra.substr(0, i) + res.first, rb.substr(0, i) + res.second};
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        string C, J;
        cin >> C >> J;

        ll diff = 0;
        auto answer = solve(C, J, diff);
        cout << "Case #" << t << ": " << answer.first << ' ' << answer.second << '\n';
    }

    return 0;
}
