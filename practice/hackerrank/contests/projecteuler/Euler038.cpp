/**
 * Problem:
 *       Pandigital multiples
 *
 * Links:
 *      https://projecteuler.net/problem=38
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler038
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_pandigital_multiple(int m, int K)
{
    bool is_pandigital = true;
    const int target_dmask = ((1 << K) - 1) << 1; // 111111110 for K=8, 1111111110 for K=9
    for (int i = 1, dmask = 0; is_pandigital && dmask != target_dmask; ++i)
    {
        int p = m * i;
        while (p)
        {
            int d = p % 10;
            p /= 10;
            if (d < 1 || d > K || (dmask & (1 << d))) is_pandigital = false;
            dmask |= 1 << d;
        }
    }
    return is_pandigital;
}

template <typename Iterator>
void solve(int N, int K, Iterator out)
{
    for (int i = 2; i < N; ++i)
    {
        if (is_pandigital_multiple(i, K)) out = i;
    }
}

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> pandigital_multiples;
    solve(N, K, std::back_inserter(pandigital_multiples));
    std::for_each(pandigital_multiples.begin(), pandigital_multiples.end(), [](int v) { cout << v << endl; });

    return 0;
}
