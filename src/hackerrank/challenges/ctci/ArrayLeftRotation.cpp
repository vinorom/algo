/**
 * Problem:
 *      Cracking the Coding Interview: Left Rotation
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-array-left-rotation
 */

#include <bits/stdc++.h>

using namespace std;

void rotate_impl(int* a, int l, int r, int d)
{
    while (d != 0)
    {
        int len = r - l;
        if (d < 0 && -d > len / 2) d = len + d;
        else if (d > 0 && d > len / 2) d = -(len - d);

        for (int i = 0; i < abs(d); ++i) swap(a[l+i], a[r-abs(d)+i]);

        if (d < 0) r += d;
        else l += d;
    }
}

void rotate(int a[], int n, int d)
{
    rotate_impl(a, 0, n, -(d % n));
}

int main()
{
    int n, d;
    cin >> n >> d;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    rotate(a, n, d);
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
