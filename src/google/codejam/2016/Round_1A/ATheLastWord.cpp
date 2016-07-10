/**
 * http://code.google.com/codejam/contest/4304486/dashboard#s=p0
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        string S;
        cin >> S;

        string ans;
        for (int i = 0; i < (int)S.size(); ++i)
        {
            if (i == 0 || S[i] < ans[0])
            {
                ans += S[i];
            }
            else
            {
                ans = S[i] + ans;
            }
        }

        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}
