/**
 * https://www.hackerrank.com/contests/2014-icpc-central-europe-regional-contest-practice/challenges/bricks
 */

#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    if (a > b) swap(a, b);
    return a == 0 ? b : gcd(b % a, a);
}

int main()
{
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;

        typedef pair<int /*count*/, int /*color*/> PII;
        vector<PII> seq(n);
        int total_count[2] = {0, 0};
        for (int i = 0; i < n; ++i)
        {
            char c;
            cin >> seq[i].first >> c;
            int color = c == 'W' ? 0 : 1;
            seq[i].second = color;
            total_count[color] += seq[i].first;
        }

        int g = gcd(total_count[0], total_count[1]);
        int step_count[2] = {total_count[0] / g, total_count[1] / g};

        int blocks = 0;
        if (step_count[0] == 0 || step_count[1] == 0)
        {
            blocks = total_count[0] + total_count[1];
        }
        else
        {
            int count[2] = {0, 0};
            for (int i = 0; i < n; ++i)
            {
                int k = seq[i].first;
                int color = seq[i].second;
                int prev_steps = count[color] / step_count[color];
                int next_steps = (count[color] + k) / step_count[color];
                int another_steps = count[color^1] / step_count[color^1];

                if (count[color^1] % step_count[color^1] == 0 && prev_steps < another_steps && another_steps <= next_steps)
                {
                    ++blocks;
                }

                count[color] += k;
            }
        }

        cout << blocks << '\n';
    }

    return 0;
}
