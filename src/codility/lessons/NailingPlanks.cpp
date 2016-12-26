/**
 * Link: https://codility.com/programmers/lessons/14-binary_search_algorithm/nailing_planks/
 */

#include <bits/stdc++.h>

using namespace std;

bool are_all_planks_nailed(vector<int>& a, vector<int>& b, vector<int>& c, int num_nails)
{
    if (num_nails == 0) return false;

    assert(a.size() == b.size());

    int n = (int)a.size();
    int m = (int)c.size();

    assert(num_nails <= m);

    bitset<60002> nails;
    for (int i = 0; i < num_nails; ++i) nails[c[i]] = true;

    vector<int> prefix_num_nails(m*2+2, 0);
    prefix_num_nails[0] = 0;
    for (int i = 1; i < m*2+2; ++i)
    {
        prefix_num_nails[i] = prefix_num_nails[i-1] + (nails[i-1] ? 1 : 0);
    }

    for (int i = 0; i < n; ++i)
    {
        if (prefix_num_nails[b[i]+1] - prefix_num_nails[a[i]] == 0) return false;
    }

    return true;
}

int solution(vector<int>& a, vector<int>& b, vector<int>& c)
{
    int min_nails = 0;
    int max_nails = (int)c.size();

    while (min_nails < max_nails)
    {
        int mid_nails = (min_nails + max_nails) / 2;

        if (!are_all_planks_nailed(a, b, c, mid_nails))
        {
            min_nails = mid_nails + 1;
        }
        else
        {
            max_nails = mid_nails;
        }
    }

    return are_all_planks_nailed(a, b, c, min_nails) ? min_nails : -1;
}

int main()
{
    vector<int> a{1, 4, 5, 8};
    vector<int> b{4, 5, 9, 10};
    vector<int> c{4, 6, 7, 10, 2};
    cout << solution(a, b, c) << endl;
    return 0;
}
