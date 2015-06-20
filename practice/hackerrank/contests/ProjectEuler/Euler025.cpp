/**
 * Problem:
 *       N-digit Fibonacci number
 *
 * Links:
 *      https://projecteuler.net/problem=25
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler025
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

    int count_digits() const { return value.size(); }

    BigInt& operator=(const BigInt& rhv)
    {
        value = rhv.value;
        return *this;
    }

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

    bool operator==(const BigInt& rhv) { return value == rhv.value; }
    bool operator!=(const BigInt& rhv) { return !((*this) == rhv); }
};

const BigInt BigInt::ZERO;

const int MAX = 5001;
int first_fib_term_by_digits_count[MAX] = {0};

void precompute_fibonacci()
{
    int fib_term = 2;
    for (BigInt a("1"), b("1"), tmp; b.count_digits() < MAX; tmp = b, b += a, a = tmp, ++fib_term)
    {
        int count = b.count_digits();
        if (first_fib_term_by_digits_count[count] == 0 && count > a.count_digits())
        {
            first_fib_term_by_digits_count[count] = fib_term;
        }
    }
}

int main()
{
    precompute_fibonacci();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << first_fib_term_by_digits_count[N] << endl;
    }
    return 0;
}
