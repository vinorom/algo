/**
 * https://www.hackerrank.com/contests/2013-acm-acpc/challenges/modified-lcs
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
    if (a > b) swap(a, b);
    return a == 0 ? b : gcd(b % a, a);
}

ll lcm(ll a, ll b)
{
    return a * b / gcd(a, b);
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        ll  na, nb, a0, b0, da, db;
        cin >> na >> a0 >> da >> nb >> b0 >> db;

        if (da > db)
        {
            swap(a0, b0);
            swap(da, db);
            swap(na, nb);
        }

        ll m = lcm(da, db);

        while (b0 + db <= a0) b0 += db, --nb;

        for (ll i = 0; i < m / db + 1 && a0 != b0; ++i)
        {
            b0 += db, --nb;
            while (a0 + da <= b0) a0 += da, --na;
        }

        ll lcs = 0;
        if (na > 0 && nb > 0 && a0 == b0)
        {
            ll an = a0 + (na - 1) * da;
            ll bn = b0 + (nb - 1) * db;
            lcs += min(an - a0, bn - b0) / m + 1;
        }

        cout << lcs << endl;
    }

    return 0;
}
