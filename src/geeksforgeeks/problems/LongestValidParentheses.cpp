/**
 * Link: http://www.practice.geeksforgeeks.org/problem-page.php?pid=1247
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

int solve(const string& str)
{
    int max_len = 0;
    int count = 0;
    stack<int> s;

    for (int i = 0; i < (int)str.length(); ++i)
    {
        if (str[i] == '(')
        {
            s.push(count);
            count = 0;
        }
        else if (str[i] == ')')
        {
            if (s.empty())
            {
                count = 0;
            }
            else
            {
                count += 2 + s.top();
                s.pop();
                max_len = max(max_len, count);
            }
        }
    }

    if (!s.empty()) max_len = max(max_len, s.top());

    return max_len;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        cout << solve(s) << '\n';
    }
    return 0;
}