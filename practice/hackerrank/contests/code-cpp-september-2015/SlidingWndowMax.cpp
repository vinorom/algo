/**
 * https://www.hackerrank.com/contests/code-cpp-september-2015/challenges/deque-stl
 */

#include <iostream>
#include <deque>

using namespace std;

void sliding_window_max(int a[], int n, int w)
{
    deque<int> q;
    for (int i = 0; i < n; ++i)
    {
        while (!q.empty() && q.front() <= i - w) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= w - 1) cout << a[q.front()] << ' ';
    }
    cout << '\n';
}

int main() 
{
    ios_base::sync_with_stdio(false); 
    
    int T;
    cin >> T;
    while (T--)
    {
        int N, W;
        cin >> N >> W;
        int a[N];
        for (int i = 0; i < N; ++i) cin >> a[i];
        sliding_window_max(a, N, W);
    }
    return 0;
}
