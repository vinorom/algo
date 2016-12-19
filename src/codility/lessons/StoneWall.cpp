/**
 * Link: https://codility.com/programmers/lessons/7-stacks_and_queues/stone_wall/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& heights)
{
    int count = 0;
    stack<int> s;
    for (auto h : heights)
    {
        while (!s.empty() && s.top() > h) s.pop();

        if (s.empty() || s.top() < h) s.push(h), ++count;
    }
    return count;
}

int main()
{
    return 0;
}
