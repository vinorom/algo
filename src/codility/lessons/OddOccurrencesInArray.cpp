/**
 * Link: https://codility.com/programmers/lessons/2-arrays/odd_occurrences_in_array/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> &a)
{
    int xor_res = 0;
    for (auto ai: a) xor_res ^= ai;
    return xor_res;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int answer = solution(a);
    cout << answer << '\n';
    return 0;
}
