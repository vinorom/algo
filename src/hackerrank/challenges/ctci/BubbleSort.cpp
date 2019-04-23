/**
 * Problem:
 *      Cracking the Coding Interview: Sorting: Bubble Sort
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-bubble-sort
 */

#include <vector>
#include <iostream>

using namespace std;

int bubble_sort(vector<int>& a)
{
    int n = (int)a.size();

    int total_num_swaps = 0;
    for (int i = 0; i < n; ++i)
    {
        int swaps = 0;
        for (int j = 0; j < n - 1; ++j)
        {
            if (a[j] > a[j+1])
            {
                swap(a[j], a[j+1]);
                ++swaps;
            }
        }

        total_num_swaps += swaps;

        if (swaps == 0) break;
    }

    return total_num_swaps;
}

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int swaps = bubble_sort(a);

    cout << "Array is sorted in " << swaps << " swaps.\n";
    cout << "First Element: " << a.front() << '\n';
    cout << "Last Element: " << a.back() << endl;

    return 0;
}
