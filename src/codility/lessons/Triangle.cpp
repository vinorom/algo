/**
 * Link: https://codility.com/programmers/lessons/6-sorting/triangle/
 */

#include <vector>

using namespace std;

int solution(vector<int>& a)
{
    if (a.size() < 3) return 0;

    sort(a.begin(), a.end());

    int n = (int)a.size();
    for (int i = 2; i < n; ++i)
    {
        if ((long long)a[i-2] + a[i-1] > a[i]) return 1;
    }

    return 0;
}

int main()
{
    return 0;
}
