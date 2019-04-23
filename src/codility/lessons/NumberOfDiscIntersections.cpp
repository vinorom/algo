/**
 * Link: https://codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/
 */

#include <vector>

using namespace std;

int solution(vector<int>& a)
{
    using bound_t = pair<long long, bool>;
    vector<bound_t> bounds;
    for (long long i = 0; i < (int)a.size(); ++i)
    {
        bounds.emplace_back(i - a[i], false); // left bound
        bounds.emplace_back(i + a[i], true); // right bound
    }

    sort(bounds.begin(), bounds.end(), [](bound_t lhv, bound_t rhv) {
        if (lhv.first != rhv.first) return lhv.first < rhv.first;
        return lhv.second < rhv.second; // left bound first
    });

    int count_open = 0;
    int count = 0;

    for (auto b : bounds)
    {
        if (b.second)
        {
            --count_open;
            count += count_open;

            if (count > 10000000) return -1;
        }
        else
        {
            ++count_open;
        }
    }

    assert(count_open == 0);

    return count;
}

int main()
{
    return 0;
}
