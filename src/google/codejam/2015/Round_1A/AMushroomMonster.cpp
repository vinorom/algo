/**
 * http://code.google.com/codejam/contest/4224486/dashboard#s=p0
 */

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;
        vector<int> mushrooms(N, 0);
        for (int i = 0; i < N; ++i) cin >> mushrooms[i];

        int eaten1 = 0;
        int rate = 0;
        for (int i = 1; i < N; ++i) {
            if (mushrooms[i - 1] > mushrooms[i]) {
                int m = mushrooms[i - 1] - mushrooms[i];
                eaten1 += m;
                rate = max(rate, m);
            }
        }

        int eaten2 = 0;
        for (int i = 0; i < N - 1; ++i)
        {
            eaten2 += min(rate, mushrooms[i]);
        }

        cout << "Case #" << t << ": " << eaten1 << " " << eaten2 << endl;
    }

    return 0;
}
