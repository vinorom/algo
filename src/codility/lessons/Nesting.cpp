/**
 * Link: https://codility.com/programmers/lessons/7-stacks_and_queues/nesting/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(string& s)
{
    int count_open = 0;
    for (auto c : s)
    {
        if (c == '(') ++count_open;
        else if (count_open) --count_open;
        else return 0;
    }
    return count_open == 0;
}

int main()
{
    return 0;
}
