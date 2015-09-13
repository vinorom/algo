/**
 * Source: http://www.spoj.com/problems/KGSS
 * Technique: segment tree
 * Complexity: O( (N+Q)*log(N) )
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
    static const T INF = (T)2e9;

    RMQ(int n) { init(n); }

    template <typename InputIterator>
    RMQ(InputIterator first, InputIterator last) { init(first, last); }

    void init(int n)
    {
        for (size = 1; size < n; size *= 2);
        tree.assign(size*2, -INF);
    }

    template <typename InputIterator>
    void init(InputIterator first, InputIterator last)
    {
        int n = (int)distance(first, last);
        init(n);

        for (int i = 0; i < n; ++i, ++first)
        {
            tree[size+i] = (*first);
        }
        for (int i = size-1; i > 0; --i)
        {
            tree[i] = max(tree[i*2], tree[i*2+1]);
        }
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

        T m = -INF;
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

int main()
{
    std::ios_base::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) cin >> arr[i];

    int Q;
    cin >> Q;

    RMQ<int> rmq(arr.begin(), arr.end());

    vector<pair<int,int>> iarr(N);
    for (int i = 0; i < N; ++i) iarr[i] = make_pair(arr[i], i);
    sort(begin(iarr), end(iarr));

    for (int i = 0; i < Q; ++i)
    {
        char t;
        cin >> t;
        switch (t)
        {
            case 'U':
            {
                int idx, val;
                cin >> idx >> val;
                rmq.update(--idx, val);
                break;
            }
            case 'Q':
            {
                int x, y;
                cin >> x >> y;
                --x, --y;
                int answer = rmq.query(x, y);
                int idx = lower_bound(iarr.begin(), iarr.end(), make_pair(answer, -1)) - iarr.begin();
                while (iarr[idx].second < x) ++idx;
                rmq.update(iarr[idx].second, -RMQ<int>::INF);
                answer += rmq.query(x, y);
                rmq.update(iarr[idx].second, iarr[idx].first);
                cout << answer << '\n';
                break;
            }
        }
    }

    return 0;
}
