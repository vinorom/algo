#include <bits/stdc++.h>

using namespace std;

class AlternatingString
{
public:
    int maxLength(const string& s)
    {
        if (s.empty()) return 0;
        char c = s[0];
        int max_len = 1;
        int len = 1;

        for (int i = 1; i < (int)s.length(); ++i)
        {
            if (s[i] != c)
            {
                ++len;
            }
            else
            {
                max_len = max(max_len, len);
                len = 1;
            }
        }
        max_len = max(max_len, len);

        return max_len;
    }
};

int main()
{
    return 0;
}