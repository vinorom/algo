/**
 * Link: https://codility.com/programmers/lessons/8-leader/equi_leader/
 */

#include <bits/stdc++.h>

using namespace std;

bool find_leader(const vector<int>& a, int& leader)
{
    int n = (int)a.size();

    int size = 0;
    int candidate = 0;
    for (auto ai : a)
    {
        if (size == 0)
        {
            candidate = ai;
            ++size;
        }
        else if (ai == candidate)
        {
            ++size;
        }
        else
        {
            --size;
        }
    }

    if (size == 0) return false;

    int count = 0;
    for (auto ai : a) if (ai == candidate) ++count;

    if (count <= n / 2) return false;

    leader = candidate;
    return true;
}

int solution(vector<int>& a)
{
    int n = (int)a.size();

    int leader = 0;
    if (!find_leader(a, leader)) return 0;

    vector<int> prefix_count(a.size() + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        prefix_count[i] = prefix_count[i-1];
        if (a[i-1] == leader) ++prefix_count[i];
    }

    int count = 0;
    for (int i = 1; i < n; ++i)
    {
        if (prefix_count[i] > i / 2 && (prefix_count.back() - prefix_count[i]) > (n - i) / 2) ++count;
    }

    return count;
}

int main()
{
    vector<int> a{4, 3, 4, 4, 4, 2};
    cout << solution(a) << endl;
    return 0;
}
