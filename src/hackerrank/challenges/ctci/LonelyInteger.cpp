/**
 * Problem:
 *      Cracking the Coding Interview: Bit Manipulation: Lonely Integer
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-lonely-integer
 */

#include <bitset>
#include <iostream>

using namespace std;

int solve(int a[], int n)
{
    bitset<101> mask;
    for (int i = 0; i < n; ++i) mask[a[i]] = mask[a[i]] ^ 1;
    for (int i = 0; i < 101; ++i) if (mask[i]) return i;
    return -1;
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve(a, n) << '\n';
    return 0;
}
