/**
 * http://www.codechef.com/SNCKQL16/problems/MMSUM
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        ll A[N];
        for (int i = 0; i < N; ++i) cin >> A[i];

        ll max_sum = std::numeric_limits<ll>::min();
        ll max_sum_ending[N];
        ll max_sum_starting[N];
        for (int i = 0; i < N; ++i)
        {
            max_sum_ending[i] = (i == 0) ? A[i] : max(A[i], max_sum_ending[i-1] + A[i]);
            max_sum = max(max_sum, max_sum_ending[i]);
        }
        for (int i = N - 1; i >= 0; --i)
        {
            max_sum_starting[i] = (i == N - 1) ? A[N-1] : max(A[i], max_sum_starting[i+1] + A[i]);
        }

        for (int i = 1; i < N - 1; ++i)
        {
            max_sum = max(max_sum, max_sum_ending[i-1] + max_sum_starting[i+1]);
        }

        cout << max_sum << '\n';
    }

    return 0;
}
