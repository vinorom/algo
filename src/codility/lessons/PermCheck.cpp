/**
 * Link: https://codility.com/programmers/lessons/4-counting_elements/perm_check/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a)
{
    int n = (int)a.size();
    bool visited[n + 1];
    fill(visited, visited + n + 1, false);
    for (auto ai : a)
    {
        if (ai < 1 || ai > n || visited[ai]) return 0;
        visited[ai] = true;
    }
    return 1;
}

int main()
{
    return 0;
}
