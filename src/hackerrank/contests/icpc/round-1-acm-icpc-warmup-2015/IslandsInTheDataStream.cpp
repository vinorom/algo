/**
 * https://www.hackerrank.com/contests/round-1-acm-icpc-warmup-2015/challenges/islands-in-the-data-stream
 */

#include <iostream>
#include <stack>

using namespace std;

int main()
{
    const int N = 12;

    int P;
    cin >> P;

    while (P--)
    {
        int K;
        cin >> K;

        int count = 0;
        stack<int> s;
        s.push(0);
        for (int i = 0; i < N; ++i)
        {
            int a;
            cin >> a; // a >= 0

            while (s.top() > a) s.pop();

            if (s.top() < a)
            {
                s.push(a);
                ++count;
            }
        }

        cout << K << ' ' << count << endl;
    }

    return 0;
}
