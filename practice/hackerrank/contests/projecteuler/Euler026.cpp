/**
 * Problem:
 *       Reciprocal cycles
 *
 * Links:
 *      https://projecteuler.net/problem=26
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler026
 */

#include <iostream>
#include <unordered_map>

using namespace std;

const int MAX = 10000;
int longest_recurring_cycle[MAX] = {0};
int answers[MAX] = {0};

void precompute_fractions()
{
    typedef unordered_map<int /*MAX*digit+overhead*/, int /*last index*/> digit_map;
    for (int denom = 1; denom < MAX; ++denom)
    {
        if (denom % 5 == 0 || (denom & (denom - 1)) == 0) continue;

        digit_map digits(MAX * 10);
        int overhead = 10;
        int idx = 0, d;
        for (; overhead % denom != 0; ++idx)
        {
            d = overhead / denom;
            overhead %= denom;
            if (digits.find(MAX * d + overhead) != digits.end()) break;
            digits[MAX * d + overhead] = idx;
            overhead *= 10;
        }
        digit_map::const_iterator it = digits.find(MAX * d + overhead);
        longest_recurring_cycle[denom] = it != digits.end() ? idx - it->second : 0;
    }

    for (int i = 1; i < MAX; ++i)
    {
        if (longest_recurring_cycle[i] > longest_recurring_cycle[answers[i - 1]])
        {
            answers[i] = i;
        }
        else
        {
            answers[i] = answers[i - 1];
        }
    }
}

int main()
{
    precompute_fractions();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << answers[N - 1] << endl;
    }
    return 0;
}
