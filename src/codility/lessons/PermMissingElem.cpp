/**
 * Link: https://codility.com/programmers/lessons/3-time_complexity/perm_missing_elem/
 */

#include <vector>

using namespace std;

int solution(vector<int>& a)
{
    long long n = (int)a.size();
    long long sum = 0;
    for (auto ai : a) sum += ai;
    return (n + 2) * (n + 1) / 2 - sum;
}

int main()
{
    return 0;
}
