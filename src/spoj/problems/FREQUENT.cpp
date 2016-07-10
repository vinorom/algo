/**
 * Source: http://www.spoj.com/problems/FREQUENT
 * Technique: segment tree
 * Complexity: O( N + Q*log(N) )
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

    while (true)
    {
        int N, Q;
        cin >> N;
        if (N == 0) break;

        cin >> Q;

        vector<int> arr(N);
        vector<int> counts(N, 0);
        for (int i = 0, last_idx = 0; i < N; ++i)
        {
            cin >> arr[i];
            if (i == 0 || arr[i] != arr[last_idx])
            {
                last_idx = i;
                counts[last_idx] = 1;
            }
            else
            {
                counts[last_idx]++;
            }
        }

        RMQ<int> rmq(counts.begin(), counts.end());

        for (int i = 0; i < Q; ++i)
        {
            int l, r;
            cin >> l >> r;
            --l, --r;

            int answer;
            if (rmq.query(l, r) == 0)
            {
                answer = r - l + 1;
            }
            else
            {
                int count_left = 0;
                int count_right = 0;
                for (; counts[l] == 0; ++l) ++count_left;
                for (; counts[r] == 0; --r) ++count_right;
                --r, ++count_right;
                answer = max(rmq.query(l, r), max(count_left, count_right));
            }

            cout << answer << '\n';
        }
    }

    return 0;
}
