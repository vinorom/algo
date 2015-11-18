/**
 * https://www.hackerrank.com/contests/round-1-acm-icpc-warmup-2015/challenges/height-ordering
 */

#include <iostream>

using namespace std;

int insertion_sort(int arr[], int N)
{
    int count = 0;
    for (int i = 1; i < N; ++i)
    {
        for (int j = i; j > 0 && arr[j-1] > arr[j]; --j)
        {
            swap(arr[j-1], arr[j]);
            ++count;
        }
    }
    return count;
}

int main()
{
    const int N = 20;

    int P;
    cin >> P;

    while (P--)
    {
        int K;
        cin >> K;

        int arr[N];
        for (int i = 0; i < N; ++i) cin >> arr[i];

        cout << K << ' ' << insertion_sort(arr, N) << endl;
    }

    return 0;
}
