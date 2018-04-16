/**
 * https://codejam.withgoogle.com/2018/challenges
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n, i;
        cin >> n;

        vector<int> a[2];
        a[0].reserve(size_t(n+1)/2);
        a[1].reserve(size_t(n+1)/2);

        for (i = 0; i < n; ++i)
        {
            int v;
            cin >> v;
            a[i%2].push_back(v);
        }

        std::sort(a[0].begin(), a[0].end());
        std::sort(a[1].begin(), a[1].end());

        cout << "Case #" << t << ": ";

        for (i = 0; i < n - 1; ++i)
        {
            int cur = a[i%2][i/2];
            int next = a[(i+1)%2][(i+1)/2];

            if (cur > next)
            {
                cout << i << '\n';
                break;
            }
        }

        if (i == n - 1) cout << "OK\n";
    }

    return 0;
}
