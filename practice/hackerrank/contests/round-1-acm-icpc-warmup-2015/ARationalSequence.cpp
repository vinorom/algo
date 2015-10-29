/**
 * https://www.hackerrank.com/contests/round-1-acm-icpc-warmup-2015/challenges/a-rational-sequence
 */

#include <iostream>

using namespace std;

struct rational
{
    int p, q;
    rational(int p = 0, int q = 1): p(p), q(q) {}
};

rational get_next(rational r)
{
    rational next;
    if (r.q == 1)
    {
        next = rational(1, r.p + 1);
    }
    else if (r.p < r.q)
    {
        next = rational(r.q, r.q - r.p);
    }
    else // p > q
    {
        int steps_up = r.p / r.q;
        rational ancestor(r.p % r.q, r.q);
        rational ancestor_next = get_next(ancestor);
        next = rational(ancestor_next.p, ancestor_next.q + ancestor_next.p * steps_up);
    }
    return next;
}

int main()
{
    int P;
    cin >> P;

    while (P--)
    {
        char ch;
        int K;
        rational r;
        cin >> K >> r.p >> ch >> r.q;

        rational next = get_next(r);

        cout << K << ' ' << next.p << '/' << next.q << endl;
    }

    return 0;
}
