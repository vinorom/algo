/**
 * https://www.hackerrank.com/contests/countercode/challenges/poisonous-plants
 */

#include <iostream>
#include <stack>

using namespace std;

int solve(int N, int p[])
{
    struct plant
    {
        int v;
        int day;
    };
    stack<plant> s;

    int max_days = 0;
    for (int i = 0; i < N; ++i)
    {
        if (s.empty())
        {
            s.push({p[i], 0});
        }
        else
        {
            plant t = s.top();
            if (t.v < p[i])
            {
                s.push({p[i], 1});
                max_days = max(max_days, 1);
            }
            else
            {
                int days = 0;
                while (!s.empty() && t.v >= p[i])
                {
                    s.pop();
                    if (s.empty()) break;
                    days = max(days, t.day);
                    t = s.top();
                }

                if (s.empty())
                {
                    s.push({p[i], 0});
                }
                else
                {
                    s.push({p[i], days + 1});
                    max_days = max(max_days, days + 1);
                }
            }
        }
    }

    return max_days;
}

int main()
{
    int N;
    cin >> N;
    int p[N];
    for (int i = 0; i < N; ++i) cin >> p[i];
    cout << solve(N, p) << endl;
    return 0;
}
