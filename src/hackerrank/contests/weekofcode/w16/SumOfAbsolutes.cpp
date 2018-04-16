/**
 * https://www.hackerrank.com/contests/w16/challenges/sum-of-absolutes
 */

#include <iostream>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    int prefix_odd_sum[N + 1]; // prefix sum modulo 2
    prefix_odd_sum[0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        int v;
        cin >> v;
        prefix_odd_sum[i] = prefix_odd_sum[i - 1];
        prefix_odd_sum[i] ^= std::abs(v) % 2;
    }
    while (Q--)
    {
        int l, r;
        cin >> l >> r;
        int odd = prefix_odd_sum[r] ^ prefix_odd_sum[l - 1];
        cout << (odd ? "Odd" : "Even") << endl;
    }
    return 0;
}
