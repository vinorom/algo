/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/preorder-traversals
 */

#include <iostream>
#include <stack>
#include <limits>

using namespace std;

const int MAXN = 1000;

bool is_preorder_traversal(int arr[], int N)
{
    stack<int> s;
    int left = numeric_limits<int>::min();
    for (int i = 0; i < N; ++i)
    {
        while (!s.empty() && s.top() < arr[i]) // values on left side should be less than or equal to root
        {
            left = s.top();
            s.pop();
        }

        if (arr[i] <= left) return false; // values on the right side should be greater than root

        s.push(arr[i]);
    }
    return true;
}

int main()
{
    int arr[MAXN];
    int t = 1;
    while (cin >> arr[0])
    {
        int N = 1;
        while (cin >> arr[N] && arr[N] > 0) ++N;

        bool answer = is_preorder_traversal(arr, N);
        cout << "Case " << t++ << ": " << (answer ? "yes" : "no") << endl;
    }
    return 0;
}
