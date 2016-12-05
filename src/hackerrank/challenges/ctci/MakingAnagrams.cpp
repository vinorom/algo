/**
 * Problem:
 *      Cracking the Coding Interview: Strings: Making Anagrams
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-making-anagrams
 */

#include <bits/stdc++.h>

using namespace std;

int solve(const string& s1, const string& s2)
{
    int count[26];
    fill(count, count + 26, 0);
    for (auto c : s1) count[c - 'a']++;
    for (auto c : s2) count[c - 'a']--;
    int res = 0;
    for (int i = 0; i < 26; ++i) res += abs(count[i]);
    return res;
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << solve(a, b) << '\n';
    return 0;
}
