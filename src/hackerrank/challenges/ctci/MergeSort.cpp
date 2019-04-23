/**
 * Problem:
 *      Cracking the Coding Interview: Merge Sort: Counting Inversions
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-merge-sort
 */

#include <vector>
#include <iostream>

using namespace std;

using ll = long long;

ll merge_halves(vector<int>& a, vector<int>& tmp, int l, int mid, int r)
{
    int li = l;
    int ri = mid + 1;
    int i = li;
    ll inversions = 0;

    while (li <= mid && ri <= r)
    {
        if (a[li] <= a[ri])
        {
            tmp[i++] = a[li++];
        }
        else
        {
            tmp[i++] = a[ri++];
            inversions += mid - li + 1;
        }
    }

    while (li <= mid) tmp[i++] = a[li++];
    while (ri <= r) tmp[i++] = a[ri++];

    assert(i == r + 1);

    for (i = l; i <= r; ++i) a[i] = tmp[i];

    return inversions;
}

ll merge_sort(vector<int>& a, vector<int>& tmp, int l, int r)
{
    if (l >= r) return 0;

    int mid = (l + r) / 2;

    // sort both halves
    ll inversions = merge_sort(a, tmp, l, mid);
    inversions += merge_sort(a, tmp, mid + 1, r);

    // merge
    inversions += merge_halves(a, tmp, l, mid, r);

    return inversions;
}

ll merge_sort(vector<int>& a)
{
    auto tmp = a;
    return merge_sort(a, tmp, 0, (int)a.size() - 1);
}

int main()
{
    int d;
    cin >> d;

    while (d--)
    {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        auto inversions = merge_sort(a);

        cout << inversions << '\n';
    }

    return 0;
}
