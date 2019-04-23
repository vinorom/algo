/**
 * Link: https://codility.com/programmers/lessons/5-prefix_sums/genomic_range_query/
 */

#include <vector>
#include <string>

using namespace std;

vector<int> solution(string& s, vector<int>& p, vector<int>& q)
{
    assert(p.size() == q.size());
    int n = (int)s.size();

    struct Count
    {
        int a = 0, c = 0, g = 0, t = 0;
    };

    vector<Count> prefix_sum(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        prefix_sum[i] = prefix_sum[i-1];
        switch (s[i-1])
        {
            case 'A': case 'a': prefix_sum[i].a++; break;
            case 'C': case 'c': prefix_sum[i].c++; break;
            case 'G': case 'g': prefix_sum[i].g++; break;
            case 'T': case 't': prefix_sum[i].t++; break;
            default: assert(false); break;
        }
    }

    vector<int> answer(p.size(), 0);
    for (int i = 0; i < (int)p.size(); ++i)
    {
        const auto& s = prefix_sum[p[i]];
        const auto& e = prefix_sum[q[i]+1];


        if (e.a - s.a > 0) answer[i] = 1;
        else if (e.c - s.c > 0) answer[i] = 2;
        else if (e.g - s.g > 0) answer[i] = 3;
        else answer[i] = 4;
    }

    return answer;
}

int main()
{
    return 0;
}
