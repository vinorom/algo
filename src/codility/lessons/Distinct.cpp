/**
 * Link: https://codility.com/programmers/lessons/6-sorting/distinct/
 */

#include <bits/stdc++.h>

using namespace std;

static const int MAXN = 1000000;

int solution(vector<int>& a)
{
    bitset<MAXN*2+1> mask;
    for (auto ai : a) mask[ai + MAXN] = true;
    int count = 0;
    for (int i = 0; i < mask.size(); ++i)
    {
        if (mask[i]) ++count;
    }
    return count;
}

int main()
{
    return 0;
}
