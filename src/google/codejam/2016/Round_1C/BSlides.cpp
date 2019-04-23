/**
 * http://code.google.com/codejam/contest/4314486/dashboard#s=p1
 */

#include <vector>
#include <iostream>

using namespace std;

using ll = long long;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int B;
        ll M;
        cin >> B >> M;

        if (M > (1LL << (B-2)))
        {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        }
        else
        {
            cout << "Case #" << t << ": POSSIBLE\n";

            std::vector<int> adj(B, 0);

            int bit_pos = 0;
            int slide_pos = B;
            ll num = M;
            while (num)
            {
                if (num & 1)
                {
                    slide_pos = B - bit_pos - 2;

                    if (slide_pos != 0) adj[slide_pos] = 1;
                }
                num >>= 1;
                ++bit_pos;
            }

            for (int i = 0; i < B; ++i)
            {
                if (i == 0 && slide_pos > 0)
                {
                    for (auto a0j : adj) cout << a0j;
                }
                else
                {
                    for (int j = 0; j < B; ++j) cout << ((i >= slide_pos && i < j) ? 1 : 0);
                }
                cout << '\n';
            }
        }
    }

    return 0;
}
