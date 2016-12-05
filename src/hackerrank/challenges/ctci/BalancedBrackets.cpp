/**
 * Problem:
 *      Cracking the Coding Interview: Stacks: Balanced Brackets
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-balanced-brackets
 */

#include <bits/stdc++.h>

using namespace std;

bool solve(const string& str)
{
    stack<char> s;
    for (auto c : str)
    {
        switch (c)
        {
            case '(':
            case '[':
            case '{':
                s.push(c);
                break;
            case ')':
                if (s.empty() || s.top() != '(') return false;
                s.pop();
                break;
            case ']':
                if (s.empty() || s.top() != '[') return false;
                s.pop();
                break;
            case '}':
                if (s.empty() || s.top() != '{') return false;
                s.pop();
                break;
        }
    }
    return s.empty();
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        cout << (solve(s) ? "YES" : "NO") << '\n';
    }
    return 0;
}

