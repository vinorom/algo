/**
 * Source: http://www.spoj.com/problems/GSS3
 * Technique: segment tree
 * Complexity: O( M*log(N) )
 */

#include <stdio.h>
#include <vector>

using namespace std;

template <typename T, typename Merge>
class segtree
{
    Merge       _merge;
    const T     _undefined;

    int         _size;
    vector<T>   _tree;

public:
    segtree(int n, Merge merge, T undefined) : _merge(merge), _undefined(undefined) { init(n); }

    template <typename InputIterator>
    segtree(InputIterator first, InputIterator last, Merge merge, T undefined): _merge(merge), _undefined(undefined) { init(first, last); }

    segtree(T arr[], Merge merge, T undefined): _merge(merge), _undefined(undefined) { init(arr, arr + sizeof(arr)/sizeof(T)); }

    void init(int n)
    {
        for (_size = 1; _size < n; _size *= 2);
        _tree.assign(_size*2, _undefined);
    }

    template <typename InputIterator>
    void init(InputIterator first, InputIterator last)
    {
        int n = (int)distance(first, last);
        init(n);

        for (int i = 0; i < n; ++i, ++first)
        {
            _tree[_size+i] = (*first);
        }
        for (int i = _size-1; i > 0; --i)
        {
            _tree[i] = _merge(_tree[i*2], _tree[i*2+1]);
        }
    }

    void update(int i, T x) // [i]=x
    {
        _tree[_size+i] = x;
        for(int p = (_size+i)/2; p > 0; p >>= 1)
        {
            _tree[p] = _merge(_tree[p*2], _tree[p*2+1]);
        }
    }

    T operator[](int i) const // [i]
    {
        return _tree[_size+i];
    }

    T query(int l, int r) const // [l,r]
    {
        ++r; //[l, r)

        T answer_left = _undefined;
        for(; l && l + (l&-l) <= r; l += l&-l)
        {
            answer_left = _merge(answer_left, _tree[(_size+l) / (l&-l)]);
        }
        T answer_right = _undefined;
        for(; l < r; r -= r&-r)
        {
            answer_right = _merge(_tree[(_size+r) / (r&-r) - 1], answer_right);
        }
        return _merge(answer_left, answer_right);
    }
};

struct GSS1_data
{
    static const GSS1_data UNDEFINED;
    int best, max_prefix, max_suffix, sum;
    GSS1_data() { *this = UNDEFINED; }
    GSS1_data(int val): best(val), max_prefix(val), max_suffix(val), sum(val) {}
    GSS1_data(int b, int mp, int ms, int s): best(b), max_prefix(mp), max_suffix(ms), sum(s) {}
    bool undefined() const { return best == UNDEFINED.best; }
};

const int INF = (int)2e9;

const GSS1_data GSS1_data::UNDEFINED(-INF);

int main()
{
    int N;
    scanf("%d", &N);

    vector<GSS1_data> arr(N);
    for (int i = 0; i < N; ++i)
    {
        int a;
        scanf("%d", &a);
        arr[i] = GSS1_data(a);
    }

    auto merge = [](const GSS1_data& l, const GSS1_data& r) -> GSS1_data
    {
        if (l.undefined()) return r;
        if (r.undefined()) return l;
        return GSS1_data(
                max(max(l.best, r.best), l.max_suffix + r.max_prefix),
                max(l.max_prefix, l.sum + r.max_prefix),
                max(r.max_suffix, r.sum + l.max_suffix),
                l.sum + r.sum);
    };

    segtree<GSS1_data, decltype(merge)> st(arr.begin(), arr.end(), merge, GSS1_data::UNDEFINED);

    int M;
    scanf("%d", &M);

    while (M--)
    {
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);

        if (t == 0)
        {
            st.update(--x, y);
        }
        else
        {
            printf("%d\n", st.query(--x, --y).best);
        }
    }

    return 0;
}
