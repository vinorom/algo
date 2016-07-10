/**
 * http://code.google.com/codejam/contest/6254486/dashboard#s=p0
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MASK_ALL = (1 << 10) - 1;

ll solve(ll n)
{
    ll nn = 0;
    int mask = 0;
    while (mask != MASK_ALL)
    {
        nn += n;
        ll m = nn;
        while (m)
        {
            ll d = m % 10;
            mask |= (1 << d);
            m /= 10;
        }
    }
    return nn;
}

void brute_force()
{
    const ll maxn = 1000000;
    for (ll n = 1; n <= maxn; ++n)
    {
        cout << n << '\t';
        ll answer = solve(n);
        cout << answer << '\n';
    }
}

int main()
{
    //brute_force();

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n;
        cin >> n;

        cout << "Case #" << t << ": ";
        if (n == 0)
            cout << "INSOMNIA\n";
        else
            cout << solve(n) << '\n';
    }

    return 0;
}
