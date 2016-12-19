/**
 * Link: https://codility.com/programmers/lessons/4-counting_elements/frog_river_one/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(int x, vector<int>& a)
{
    bool leaves[x + 1];
    fill(leaves, leaves + x + 1, false);

    int dist = 0;
    for (int i = 0; i < (int)a.size(); ++i)
    {
        leaves[a[i]] = true;
        while (dist < x && leaves[dist+1]) ++dist;
        if (dist == x) return i;
    }

    return -1;
}

int main()
{
    return 0;
}
