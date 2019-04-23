/**
 * Problem:
 *      Cracking the Coding Interview: Binary Search: Ice Cream Parlor
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-ice-cream-parlor
 */

#include <vector>
#include <iostream>

using namespace std;

struct IceCream
{
    int flavor;
    int cost;
};

int binary_search(const vector<IceCream>& ices, int left, int right, int cost)
{
    int l = left;
    int r = right;

    while (l < r)
    {
        int mid = (l + r) / 2;

        if (cost > ices[mid].cost) l = mid + 1;
        else r = mid;
    }

    return l >= left && l <= right ? l : -1;
}

pair<int, int> solve(vector<IceCream>& ices, int m)
{
    sort(ices.begin(), ices.end(), [](const IceCream& lhv, const IceCream& rhv) { return lhv.cost < rhv.cost; });

    int n = (int)ices.size();

    for (int i = 0; i < n - 1; ++i)
    {
        const auto& ice = ices[i];

        int oth_cost = m - ice.cost;
        int pos = binary_search(ices, i + 1, n, oth_cost);

        if (pos != -1 && ices[pos].cost == oth_cost)
        {
            auto a = ice.flavor;
            auto b = ices[pos].flavor;
            if (a > b) swap(a, b);
            return {a, b};
        }
    }

    return {-1, -1};
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int m, n, cost;
        cin >> m >> n;

        vector<IceCream> ices;
        for (int i = 1; i <= n; ++i)
        {
            cin >> cost;
            ices.push_back({i, cost});
        }

        auto res = solve(ices, m);

        cout << res.first << ' ' << res.second << '\n';
    }

    return 0;
}