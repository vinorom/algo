/**
 * Problem:
 *      Large sum
 *
 * Links:
 *      https://projecteuler.net/problem=13
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler013
 */

#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;
    string sum;
    string number;
    for (int i = 0; i < N; ++i)
    {
        cin >> number;
        int dn = number.size();
        int next_order = 0;
        int off = 1;
        for (; off <= dn || next_order != 0; ++off)
        {
            int s = next_order;
            if (off <= dn) s += number[dn - off] - '0';
            if (off <= sum.size()) s += sum[sum.size() - off] - '0';
            if (off > sum.size()) sum = string(1, ' ') + sum; // resize
            sum[sum.size() - off] = char('0' + (s % 10));
            next_order = s / 10;
        }
    }

    cout << sum.substr(0, 10) << endl;

    return 0;
}
