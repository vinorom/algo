/**
 * Link: https://codility.com/programmers/lessons/1-iterations/binary_gap/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(int n)
{
    int max_gap = 0;
    int pos1 = -1;
    for (int i = 0; n; ++i, n >>= 1)
    {
        int d = n % 2;
        if (pos1 >= 0 && d == 1) max_gap = max(max_gap, i - pos1 - 1);
        if (d == 1) pos1 = i;
    }
    return max_gap;
}

int main()
{
    return 0;
}
