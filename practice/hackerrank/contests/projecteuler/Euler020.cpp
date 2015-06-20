/**
 * Problem:
 *       Factorial digit sum
 *
 * Links:
 *      https://projecteuler.net/problem=20
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler020
 */

#include <iostream>

using namespace std;

class BigInt
{
    string value;

public:
    static const BigInt ZERO;

    BigInt(): value("0") {}
    BigInt(const string& str): value(str) {}
    BigInt(const BigInt& rhv): value(rhv.value) {}

    const string& to_string() const { return value; }

    BigInt& operator+=(const BigInt& rhv)
    {
        int dl = (int)value.size();
        int dr = (int)rhv.value.size();
        for (int off = 1, next_order = 0; off <= max(dl, dr) || next_order != 0; ++off)
        {
            int s = next_order;
            if (off <= dl) s += value[dl - off] - '0';
            if (off <= dr) s += rhv.value[dr - off] - '0';
            if (off > dl) { value = string(1, ' ') + value; ++dl; } // resize
            value[dl - off] = char('0' + (s % 10));
            next_order = s / 10;
        }
        return *this;
    }

    BigInt& operator*=(int n)
    {
        if (n == 0)
        {
            value = "0";
            return *this;
        }
        if (n == 1) return *this;

        BigInt v(*this);
        (*this) *= (n / 2);
        (*this) += (*this);
        if (n % 2 == 1) (*this) += v;

        return *this;
    }

    bool operator==(const BigInt& rhv) { return value == rhv.value; }
    bool operator!=(const BigInt& rhv) { return !((*this) == rhv); }
};

const BigInt BigInt::ZERO;

BigInt factorial(int N)
{
    static const int MAX_CACHE = 1001;
    static BigInt cache[MAX_CACHE];
    static const BigInt ONE("1");

    if (N == 0) return ONE;
    if (N < MAX_CACHE && cache[N] != BigInt::ZERO) return cache[N];

    BigInt f = factorial(N - 1);
    f *= N;

    if (N < MAX_CACHE) cache[N] = f;

    return f;
}

int sum_digits(const BigInt& n)
{
    int sum = 0;
    const string& v = n.to_string();
    for (int i = 0; i < v.size(); ++i)
    {
        sum += v[i] - '0';
    }
    return sum;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << sum_digits(factorial(N)) << endl;
    }
    return 0;
}
