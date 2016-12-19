/**
 * Link: https://codility.com/programmers/lessons/7-stacks_and_queues/fish/
 */

#include <bits/stdc++.h>

using namespace std;

int solution(vector<int>& a, vector<int>& b)
{
    int count = 0;
    vector<int> fishes;
    for (int i = 0; i < (int)a.size(); ++i)
    {
        if (b[i])
        {
            fishes.push_back(a[i]);
        }
        else
        {
            while (!fishes.empty() && fishes.back() < a[i]) fishes.pop_back();
            if (fishes.empty()) ++count;
        }
    }
    count += fishes.size();
    return count;
}

int main()
{
    return 0;
}
