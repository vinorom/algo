/**
 * Problem:
 *      Pentagon numbers
 *
 * Links:
 *      https://projecteuler.net/problem=44
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler044
 */

#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;

ll get_pentagonal(int n)
{
    return (ll)n * (3 * n - 1) / 2;
}

bool is_pentagonal(ll p)
{
    int n = (int)(sqrt(p * 24 + 1) + 1) / 6;
    return get_pentagonal(n) == p;
}

#define ORIGINAL_EULER_PROBLEM

int main()
{
#ifdef ORIGINAL_EULER_PROBLEM
    for (int i = 1; ; ++i)
    {
        ll pi = get_pentagonal(i);
        for (int j = i - 1; j > 0; --j)
        {
            ll pj = get_pentagonal(j);
//            if (is_pentagonal(pn + get_))
        }
    }

#else
    int N, K;
    cin >> N >> K;
    for (int n = K + 1; n < N; ++n)
    {
        ll pn = get_pentagonal(n);
        ll pnk = get_pentagonal(n - K);
        if (is_pentagonal(pn - pnk) || is_pentagonal(pn + pnk)) cout << pn << endl;
    }
#endif
    return 0;
}
