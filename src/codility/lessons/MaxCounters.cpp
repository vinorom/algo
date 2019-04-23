/**
 * Link: https://codility.com/programmers/lessons/4-counting_elements/max_counters/
 */

#include <vector>

using namespace std;

vector<int> solution(int n, vector<int>& a)
{
    vector<int> counters(n, 0);
    int cur_max = 0;
    int base_min = cur_max;

    for (auto ai : a)
    {
        --ai;
        if (ai == n) // update all counters with max value of any counter
        {
            base_min = cur_max;
        }
        else // increment given counter
        {
            counters[ai] = max(base_min, counters[ai]);
            ++counters[ai];
            cur_max = max(cur_max, counters[ai]);
        }
    }

    for (auto& c : counters) c = max(c, base_min);

    return counters;
}

int main()
{
    return 0;
}
