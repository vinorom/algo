/**
 * Source: http://www.spoj.com/problems/KQUERY
 * Technique: segment tree
 * Complexity: O( (N+Q)*log(N) )
 */

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Value>
struct segment_tree
{
    int size;
    vector<Value> tree;

    void init(int n)
    {
        for (size = 1; size < n; size *= 2);
        tree.assign(size*2, 0);
    }

    void update(int i, Value x) // [i]=x
    {
        tree[size+i] = x;
        for(int k = (size+i)/2; k > 0; k >>= 1)
        {
            tree[k] = tree[k*2] + tree[k*2+1];
        }
    }

    Value operator[](int i) const // [i]
    {
        return tree[size+i];
    }

    Value query(int l, int r) const // [l,r]
    {
        ++r; //[l, r)

        Value m = 0;
        for(; l && l + (l&-l) <= r; l += l&-l)
        {
            m += tree[(size+l) / (l&-l)];
        }
        for(; l < r; r -= r&-r)
        {
            m += tree[(size+r) / (r&-r) - 1];
        }
        return m;
    }
};


struct query
{
    int l, r, k;
    int answer;
    query(): l(), r(), k(), answer() {}
    bool operator>(const query& that) { return k > that.k; }
};

int main()
{
    int i, j;
    int N;
    scanf("%d", &N);

    vector<pair<int,int>> arr(N);
    for (i = 0; i < N; ++i)
    {
        scanf("%d", &arr[i].first);
        arr[i].second = i;
    }

    int Q;
    scanf("%d", &Q);

    vector<query> queries(Q);
    vector<int> qindices(Q);
    for (i = 0; i < Q; ++i)
    {
        query& q = queries[i];
        scanf("%d %d %d", &q.l, &q.r, &q.k);
        --q.l, --q.r;
    }

    sort(begin(arr), end(arr), greater<pair<int,int>>());
    i = 0, generate(begin(qindices), end(qindices), [&i]() { return i++; });
    sort(begin(qindices), end(qindices), [&queries](int lhv, int rhv) { return queries[lhv].k > queries[rhv].k; });

    segment_tree<int> st;
    st.init(N);
    for (i = 0, j = 0; i < Q; ++i)
    {
        query& q = queries[qindices[i]];
        for (; j < N && arr[j].first > q.k; ++j)
        {
            st.update(arr[j].second, 1);
        }
        q.answer = st.query(q.l, q.r);
    }

    for (i = 0; i < Q; ++i)
    {
        const query& q = queries[i];
        printf("%d\n", q.answer);
    }

    return 0;
}
