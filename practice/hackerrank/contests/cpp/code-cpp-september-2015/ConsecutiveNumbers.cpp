/**
 * https://www.hackerrank.com/contests/code-cpp-september-2015/challenges/consecutive-numbers
 */

#include <iostream>

using namespace std;

const int MAX = 10000;

int main()
{
    int T;
    cin >> T;
    bool counts[MAX+1];
    while (T--)
    {
        int N;
        cin >> N;

        fill(begin(counts), end(counts), false);
        for (int i = 0; i < N; ++i)
        {
            int a;
            cin >> a;
            counts[a] = true;
        }

        int max_count = 0, count = 0;
        for (int i = 0; i <= MAX; ++i)
        {
            if (counts[i])
            {
                ++count;
            }
            else
            {
                max_count = max(max_count, count);
                count = 0;
            }
        }
        max_count = max(max_count, count);

        cout << max_count << '\n';
    }
    return 0;
}
