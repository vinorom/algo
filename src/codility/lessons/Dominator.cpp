/**
 * Link: https://codility.com/programmers/lessons/8-leader/dominator/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a)
{
    int n = (int)a.size();

    int size = 0;
    int candidate = 0;
    int pos = -1;

    for (int i = 0; i < n; ++i)
    {
        if (size == 0)
        {
            ++size;
            candidate = a[i];
            pos = i;
        }
        else
        {
            if (a[i] != candidate)
                --size;
            else
                ++size;
        }
    }

    if (size == 0) return -1;

    int count = 0;
    for (auto ai : a)
    {
        if (ai == candidate) ++count;
    }

    if (count > n / 2) return pos;

    return -1;
}

int main()
{
    return 0;
}
