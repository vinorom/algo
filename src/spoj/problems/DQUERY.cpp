/**
 * Source: http://www.spoj.com/problems/DQUERY
 * Technique: MO's algorithm
 * Complexity: O( (N+Q)*sqrt(N) )
 */

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Query
{
    int l, r;
    int answer;
    Query(): l(), r(), answer() {}
};

typedef vector<Query> QueryVec;

const int SQRT_N = 173; // sqrt(30000)
const int MAX = 1000001;
int counter[MAX] = {0};

struct IndexMoSorter
{
    const QueryVec& values;
    IndexMoSorter(const QueryVec& v): values(v) {}
    bool operator()(int lhv, int rhv)
    {
        const Query& q1 = values[lhv];
        const Query& q2 = values[rhv];
        const int a = q1.l / SQRT_N;
        const int b = q2.l / SQRT_N;
        if (a != b) return a < b;
        return (a & 1) ? q1.r < q2.r : q1.r > q2.r;
    }
};

void solve(int arr[], const vector<int>& indices, QueryVec& queries)
{
    int answer = 0;
    int current_left = 0;
    int current_right = -1;
    for (int i = 0; i < indices.size(); ++i)
    {
        Query& q = queries[indices[i]];
        while (current_left < q.l)
        {
            if (--counter[arr[current_left]] == 0) answer--;
            ++current_left;
        }
        while (current_left > q.l)
        {
            if (++counter[arr[current_left - 1]] == 1) answer++;
            --current_left;
        }
        while (current_right < q.r)
        {
            if (++counter[arr[current_right + 1]] == 1) answer++;
            ++current_right;
        }
        while (current_right > q.r)
        {
            if (--counter[arr[current_right]] == 0) answer--;
            --current_right;
        }
        q.answer = answer;
    }
}

int main()
{
    int n, q;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

    scanf("%d", &q);
    QueryVec queries(q);
    vector<int> indices(q);
    for (int i = 0; i < q; ++i)
    {
        scanf("%d %d", &queries[i].l, &queries[i].r);
        --queries[i].l;
        --queries[i].r;
        indices[i] = i;
    }

    sort(indices.begin(), indices.end(), IndexMoSorter(queries));
    solve(arr, indices, queries);

    for (int i = 0; i < q; ++i)
    {
        printf("%d\n", queries[i].answer);
    }

    return 0;
}
