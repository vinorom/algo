/**
 * Problem:
 *       Power digit sum
 *
 * Links:
 *      https://projecteuler.net/problem=16
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler016
 */

#include <iostream>

using namespace std;

void mult2(string& value) // = value * 2
{
    int next_order = 0;
    for (int pos = value.size() - 1; pos >= 0; --pos)
    {
        int d = value[pos] - '0';
        d *= 2;
        d += next_order;
        value[pos] = char('0' + (d % 10));
        next_order = d / 10;
    }
    if (next_order != 0)
    {
        value = std::to_string(next_order) + value;
    }
}

const string pow2(int d) // = 2 ^ d
{
    static string cache_pow2[10001];

    if (d == 0) return "1";
    if (!cache_pow2[d].empty()) return cache_pow2[d];
    cache_pow2[d] = pow2(d - 1);
    mult2(cache_pow2[d]);
    return cache_pow2[d];
}

int sum_digits(const string& value)
{
    int sum = 0;
    for (int i = 0; i < value.size(); ++i) sum += value[i] - '0';
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
        cout << sum_digits(pow2(N)) << endl;
    }
    return 0;
}
