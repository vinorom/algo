/**
 * Source: http://www.spoj.com/problems/RATING
 * Technique: segment tree
 * Complexity: O( N*log(N) )
 */

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

class RSQ
{
private:
    int size;
    vector<int> tree;

public:
    RSQ(int n)
    {
        for (size = 1; size < n; size <<= 1);
        tree.assign(size*2, 0);
    }

    void update(int i, int v)
    {
        tree[size+i] = v;
        for (int p = (size+i)/2; p > 0; p >>= 1)
        {
            tree[p] = tree[p*2] + tree[p*2+1];
        }
    }

    int operator[](int i) const { return tree[size+i]; }

    int query(int l, int r) // [l,r]
    {
        ++r; // [l,r)

        int sum = 0;
        for (; l > 0 && l + (l&-l) <= r; l += l&-l)
        {
            sum += tree[(size+l) / (l&-l)];
        }
        for (; l < r; r -= r&-r)
        {
            sum += tree[(size+r) / (r&-r) - 1];
        }
        return sum;
    }
};

const int MAX = 100001;

int main()
{
    int N;
    scanf("%d", &N);

    typedef pair<int,int> rating;

    vector<rating> ratings(N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &ratings[i].first, &ratings[i].second);
    }

    int i;
    vector<int> indices(N);
    i = 0, generate(begin(indices), end(indices), [&i]() { return i++; });
    sort(begin(indices), end(indices), [&ratings](int l, int r) { return ratings[l] < ratings[r]; });

    vector<int> counts(N, 0);
    rating r(0, 0);
    int dups = 0;
    RSQ rsq(MAX);
    for (i = 0; i < N; ++i)
    {
        rating ri = ratings[indices[i]];
        dups = ri == r ? dups + 1 : 1;
        counts[indices[i]] = rsq.query(0, ri.second) - (dups - 1);
        rsq.update(ri.second, rsq[ri.second]+1);
        r = ri;
    }

    for (i = 0; i < N; ++i)
    {
        printf("%d\n", counts[i]);
    }

    return 0;
}
