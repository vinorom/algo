/**
 * Problem:
 *      Cracking the Coding Interview: Heaps: Find the Running Median
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-find-the-running-median
 */

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class CRunningMedian
{
    vector<int> heap_max;
    vector<int> heap_min;

public:
    void add(int a)
    {
        if ((heap_max.empty() && heap_min.empty()) || a <= heap_max.front())
        {
            heap_max.push_back(a);
            push_heap(heap_max.begin(), heap_max.end(), less<int>());
        }
        else
        {
            heap_min.push_back(a);
            push_heap(heap_min.begin(), heap_min.end(), greater<int>());
        }

        if (heap_max.size() > heap_min.size() + 1)
        {
            heap_min.push_back(heap_max.front());
            push_heap(heap_min.begin(), heap_min.end(), greater<int>());
            pop_heap(heap_max.begin(), heap_max.end(), less<int>());
            heap_max.pop_back();
        }
        else if (heap_min.size() > heap_max.size() + 1)
        {
            heap_max.push_back(heap_min.front());
            push_heap(heap_max.begin(), heap_max.end(), less<int>());
            pop_heap(heap_min.begin(), heap_min.end(), greater<int>());
            heap_min.pop_back();
        }
    }

    double getMedian() const
    {
        if (heap_max.size() > heap_min.size()) return heap_max.front();
        else if (heap_max.size() < heap_min.size()) return heap_min.front();
        return heap_max.size() == 0 ? -1 : (heap_max.front() + heap_min.front()) / 2.0;
    }
};

int main()
{
    CRunningMedian median;
    int n;
    cin >> n;
    while (n--)
    {
        int a;
        cin >> a;
        median.add(a);
        cout << fixed << setprecision(1) << median.getMedian() << '\n';
    }

    return 0;
}