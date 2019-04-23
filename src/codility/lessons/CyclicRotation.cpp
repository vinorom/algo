/**
 * Link: https://codility.com/programmers/lessons/2-arrays/cyclic_rotation/
 */

#include <vector>
#include <iostream>

using namespace std;

void rotate(vector<int>& a, int l, int r, int k)
{
    if (abs(k) == 0) return;
    auto len = r - l;
    if (abs(k) > len/2) return rotate(a, l, r, k > 0 ? -(len-k) : len+k);
    for (int i = 0; i < abs(k); ++i) swap(a[l+i], a[r-abs(k)+i]);
    if (k > 0) rotate(a, l + k, r, k);
    else rotate(a, l, r + k, k);
}

vector<int> solution(vector<int>& a, int k)
{
    if (!a.empty()) rotate(a, 0, (int)a.size(), k % a.size());
    return a;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    solution(a, k);
    assert(a.size() == n);
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
