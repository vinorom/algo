/**
 * http://code.google.com/codejam/contest/4314486/dashboard#s=p0
 */

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

vector<string> evacuate(const vector<int>& senators)
{
    int sum = accumulate(senators.begin(), senators.end(), 0);

    deque<PII> s(senators.size());
    for (int i = 0; i < (int)senators.size(); ++i) s[i] = PII(senators[i], i);

    sort(s.begin(), s.end(), [](PII lhv, PII rhv) { return lhv.first > rhv.first; });

    vector<string> plan;
    while (!s.empty())
    {
        string step;
        step += char('A' + s[0].second);
        s[0].first--;
        if (s[0].first == 0) // all are 1s
        {
            if (s.size() % 2 == 0)
            {
                step += char('A' + s[1].second);
                s[1].first--;
            }
        }
        else // s[0].first > 0
        {
            if (s[1].first <= (sum - 2) / 2)
            {
                step += char('A' + s[0].second);
                s[0].first--;
            }
            else
            {
                step += char('A' + s[1].second);
                s[1].first--;
            }
        }

        plan.push_back(step);
        sum -= step.size();

        if (s[1].first == 0)
        {
            PII front = s.front();
            s.pop_front();
            s.pop_front();
            s.push_front(front);
        }
        else
        {
            for (int i = 2; i < (int)s.size() && s[i-1].first < s[i].first; ++i) swap(s[i-1], s[i]);
        }

        if (s[0].first == 0)
        {
            s.pop_front();
        }
        else
        {
            for (int i = 1; i < (int)s.size() && s[i-1].first < s[i].first; ++i) swap(s[i-1], s[i]);
        }
    }

    return plan;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        vector<int> senators(N);
        for (int i = 0; i < N; ++i) cin >> senators[i];

        vector<string> plan = evacuate(senators);
        cout << "Case #" << t << ":";
        for (const auto& step: plan) cout << ' ' << step;
        cout << '\n';
    }

    return 0;
}
