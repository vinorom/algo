/**
 * Problem:
 *      Longest Collatz sequence
 *
 * Links:
 *      https://projecteuler.net/problem=14
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler014
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MAX = 10000000;
ll collatz_cache[MAX] = {0};

ll get_collatz_next(ll n)
{
    return n % 2 == 0 ? n / 2 : 3 * n + 1;
}

ll get_collatz_chain_len(ll n)
{
    if (n < MAX && collatz_cache[n] > 0) return collatz_cache[n];
    ll len = 1 + get_collatz_chain_len(get_collatz_next(n));
    if (n < MAX) collatz_cache[n] = len;
    return len;
}

struct IndexSorter
{
    const vector<int>& values;
    IndexSorter(const vector<int>& values_): values(values_) {}
    bool operator()(int lhv, int rhv) { return values[lhv] < values[rhv]; }
};

int main()
{
    collatz_cache[1] = 1;

    int T;
    cin >> T;
    vector<int> tc(T);
    vector<int> indices(T);
    vector<int> res(T);
    for (int i = 0; i < T; ++i)
    {
        cin >> tc[i];
        indices[i] = i;
    }
    sort(indices.begin(), indices.end(), IndexSorter(tc));

    int start_longest_chain = 1;
    ll max_chain_length = get_collatz_chain_len(1);
    for (int i = 0, start = 2; i < T; ++i)
    {
        int N = tc[indices[i]];
        for (; start <= N; ++start)
        {
            ll chain_length = get_collatz_chain_len(start);
            if (chain_length >= max_chain_length)
            {
                max_chain_length = chain_length;
                start_longest_chain = start;
            }
        }
        res[indices[i]] = start_longest_chain;
    }

    for (int i = 0; i < T; ++i) cout << res[i] << endl;

    return 0;
}
