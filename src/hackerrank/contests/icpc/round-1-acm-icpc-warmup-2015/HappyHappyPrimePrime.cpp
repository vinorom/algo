/**
 * https://www.hackerrank.com/contests/round-1-acm-icpc-warmup-2015/challenges/happy-happy-prime-prime
 */

#include <iostream>
#include <set>

using namespace std;

bool is_prime(int m)
{
    if (m == 1) return false;

    for (int i = 2; i * i <= m; ++i)
    {
        if (m % i == 0) return false;
    }

    return true;
}

bool is_happy(int m)
{
    set<int> s;
    while (m != 1)
    {
        if (s.count(m)) return false; // found infinite chain
        s.insert(m);

        int mm = 0;
        while (m)
        {
            int d = m % 10;
            mm += d * d;
            m /= 10;
        }
        m = mm;
    }

    return true;
}

int main()
{
    int P;
    cin >> P;

    while (P--)
    {
        int K, m;
        cin >> K >> m;

        cout << K << ' ' << m << ' ' << (is_happy(m) && is_prime(m) ? "YES" : "NO") << endl;
    }

    return 0;
}
