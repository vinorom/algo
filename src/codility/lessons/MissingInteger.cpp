/**
 * Link: https://codility.com/programmers/lessons/4-counting_elements/missing_integer/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a)
{
    unordered_set<int> values;
    for (auto ai : a) values.insert(ai);
    for (int i = 1; i <= (int)a.size() + 1; ++i)
    {
        if (values.count(i) == 0) return i;
    }
    assert(false);
    return -1;
}

int main()
{
    return 0;
}
