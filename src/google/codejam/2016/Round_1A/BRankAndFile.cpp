/**
 * http://code.google.com/codejam/contest/4304486/dashboard#s=p1
 */

#include <vector>
#include <iostream>

using namespace std;

const int MAXH = 2501;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N, h;
        cin >> N;

        int counts[MAXH];
        fill(counts, counts + MAXH, 0);
        for (int i = 0; i < 2 * N - 1; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> h;
                counts[h]++;
            }
        }

        vector<int> missing;
        for (int i = 0; i < MAXH; ++i)
        {
            if ((counts[i] & 1)) missing.push_back(i);
        }
        assert((int)missing.size() == N);

        sort(missing.begin(), missing.end());

        cout << "Case #" << t << ":";
        for (int i = 0; i < N; ++i) cout << ' ' << missing[i];
        cout << '\n';
    }

    return 0;
}
