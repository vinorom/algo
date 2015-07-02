/**
 * Problem:
 *      Palindrome Index
 *
 * Links:
 *      https://www.hackerrank.com/companies/vmware/challenges/palindrome-index
 */

#include <iostream>

using namespace std;

bool is_palindrome(const string& s, int l, int r)
{
    for (; l < r; ++l, --r)
    {
        if (s[l] != s[r]) return false;
    }
    return true;
}

int solve(const string& s) // return index of character whose removal will make palindrome
{
    for (int l = 0, r = (int)s.size() - 1; l < r; ++l, --r)
    {
        if (s[l] != s[r]) return is_palindrome(s, l + 1, r) ? l : r; // there may be only one char
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        cout << solve(s) << endl;
    }
    return 0;
}
