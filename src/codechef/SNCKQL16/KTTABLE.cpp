/**
 * http://www.codechef.com/SNCKQL16/problems/KTTABLE
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        int A[N+1], B[N+1];
        A[0] = 0;
        for (int i = 1; i <= N; ++i) cin >> A[i];
        for (int i = 1; i <= N; ++i) cin >> B[i];

        int count = 0;
        for (int i = 1; i <= N; ++i)
        {
            if (A[i] - A[i-1] >= B[i]) ++count;
        }

        cout << count << '\n';
    }

    return 0;
}
