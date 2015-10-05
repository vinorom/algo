/**
 * https://www.hackerrank.com/contests/godaddy-hackathon/challenges/serbland
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class RMQ
{
    int size;
    vector<T> tree;

public:
    RMQ(int n) { init(n); }

    void init(int n)
    {
        for (size = 1; size < n; size *= 2);
        tree.assign(size*2, 0);
    }

    void update(int i, T x) // [i]=x
    {
        tree[size+i] = x;
        for(int p = (size+i)/2; p > 0; p >>= 1)
        {
            tree[p] = max(tree[p*2], tree[p*2+1]);
        }
    }

    T operator[](int i) const // [i]
    {
        return tree[size+i];
    }

    T query(int l, int r) const // [l,r]
    {
        ++r; //[l, r)

        T m = 0;
        for(; l && l + (l&-l) <= r; l += l&-l)
        {
            m = max(m, tree[(size+l) / (l&-l)]);
        }
        for(; l < r; r -= r&-r)
        {
            m = max(m, tree[(size+r) / (r&-r) - 1]);
        }
        return m;
    }
};

typedef long long ll;

struct dset
{
    int x, y;
    ll w;
    int ycomp; // compressed y
    dset(): x(), y(), w(), ycomp() {}
};

int main()
{
    int n, i;
    cin >> n;
    vector<dset> dsets(n);
    for (int i = 0; i < n; ++i) cin >> dsets[i].x >> dsets[i].y >> dsets[i].w;

    vector<int> xindices(n), yindices(n);
    i = 0, generate(begin(xindices), end(xindices), [&i] { return i++; });
    i = 0, generate(begin(yindices), end(yindices), [&i] { return i++; });

    // O(n log n)
    sort(begin(xindices), end(xindices),
         [&dsets](int l, int r)
         {
             return dsets[l].x != dsets[r].x ? dsets[l].x < dsets[r].x : dsets[l].y < dsets[r].y;
         });
    sort(begin(yindices), end(yindices),
         [&dsets](int l, int r)
         {
             return dsets[l].y != dsets[r].y ? dsets[l].y < dsets[r].y : dsets[l].x < dsets[r].x;
         });

    // y compression
    dsets[yindices[0]].ycomp = 0;
    for (i = 1; i < n; ++i)
    {
        dsets[yindices[i]].ycomp = dsets[yindices[i-1]].ycomp;
        if (dsets[yindices[i]].y != dsets[yindices[i-1]].y) ++dsets[yindices[i]].ycomp;
    }
    int max_ycomp = dsets[yindices.back()].ycomp;

    // use RMQ to calculate max on the passed 2D interval [0,x] x [0,ycomp]
    ll answer = 0;
    RMQ<ll> rmqy(max_ycomp + 1);

    // O(n log n)
    for (i = 0; i < n; ++i)
    {
        ll curr_max = rmqy.query(0, dsets[xindices[i]].ycomp) + dsets[xindices[i]].w;
        answer = max(answer, curr_max);
        rmqy.update(dsets[xindices[i]].ycomp, curr_max);
    }

    cout << answer << endl;

    return 0;
}
