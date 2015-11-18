/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/continued-fractions
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

template <typename T>
T gcd(T a, T b)
{
    if (a > b) swap(a, b);
    if (a == 0) return b;
    return gcd(b % a, a);
}

template <typename>
struct continued_fraction;

template <typename T>
struct rational
{
    T p, q;

    rational(T p = 0, T q = 1): p(p), q(q) { T d = gcd(p, q); p /= d; q /= d; }
    rational(const continued_fraction<T>& cf);

    rational operator+(rational r) { return rational(p*r.q + r.p*q, q*r.q); }
    rational operator-(rational r) { return rational(p*r.q - r.p*q, q*r.q); }
    rational operator*(rational r) { return rational(p*r.p, q*r.q); }
    rational operator/(rational r) { return rational(p*r.q, q*r.p); }
};

/**
 * Representation: a0+1/(a1+1/(a2+1/(a3+...)))
 */
template <typename T>
struct continued_fraction
{
    vector<T> quotients;

    continued_fraction(T a[], int n) { quotients.assign(a, a + n); }
    continued_fraction(rational<T> r);
};

template <typename T>
rational<T>::rational(const continued_fraction<T>& cf)
{
    rational r;
    for (int i = (int)cf.quotients.size() - 1; i > 0; --i)
    {
        r = r + cf.quotients[i];
        r = rational(r.q, r.p); // inverse
    }
    *this = r + cf.quotients[0];
}

template <typename T>
continued_fraction<T>::continued_fraction(rational<T> r)
{
    T p = r.p, q = r.q;
    do
    {
        quotients.push_back(p / q);
        p %= q;
        swap(p, q);
    }
    while (q);
}

template <typename T>
ostream& operator<<(ostream& os, rational<T> r)
{
    os << r.p;
    if (r.q != 1) os << '/' << r.q;
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const continued_fraction<T>& cf)
{
    for (int i = 0; i < cf.quotients.size(); ++i)
    {
        os << (i == 0 ? "" : " ") << cf.quotients[i];
    }
    return os;
}

int main()
{
    int n1, n2, t = 1;
    while (cin >> n1)
    {
        cin >> n2;
        ll a1[n1], a2[n2];
        for (int i = 0; i < n1; ++i) cin >> a1[i];
        for (int i = 0; i < n2; ++i) cin >> a2[i];

        rational<ll> r1(continued_fraction<ll>(a1, n1));
        rational<ll> r2(continued_fraction<ll>(a2, n2));

        cout << "Case " << t++ << ":\n"
            << continued_fraction<ll>(r1+r2) << '\n'
            << continued_fraction<ll>(r1-r2) << '\n'
            << continued_fraction<ll>(r1*r2) << '\n'
            << continued_fraction<ll>(r1/r2) << '\n';
    }

    return 0;
}
