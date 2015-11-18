/**
 * https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-unique-substrings
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct suffix_array
{
    string s;
    int N, gap;
    vector<int> sa, pos, tmp, lcp;

public:
    suffix_array(): N(), gap() {}

    void create(const string& str, bool need_lcp)
    {
        s = str;
        N = (int)s.size();
        sa.resize(N, 0);
        pos.resize(N, 0);
        tmp.resize(N, 0);
        lcp.resize(N, 0);

        build();
        if (need_lcp) build_lcp();
    }

    int to_digit(char c) { return c - '0'; }
    char from_digit(int digit) { return char('0' + digit); }

    void build()
    {
        for (int i = 0; i < N; ++i)
        {
            sa[i] = i;
            pos[i] = to_digit(s[i]);
        }
        for (gap = 1; ; gap *= 2)
        {
            sort(sa.begin(), sa.end(), [&](int i, int j) -> bool { return compare(i, j); });
            for (int i = 0; i < N - 1; ++i) tmp[i + 1] = tmp[i] + compare(sa[i], sa[i + 1]);
            for (int i = 0; i < N; ++i) pos[sa[i]] = tmp[i];
            if (tmp[N - 1] == N - 1) break;
        }
    }

    void build_lcp()
    {
        for (int i = 0, k = 0; i < N; ++i)
        {
            if (pos[i] != N - 1)
            {
                for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ++k);
                lcp[pos[i]] = k;
                if (k) --k;
            }
        }
    }

    bool compare(int i, int j)
    {
        if (pos[i] != pos[j]) return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < N && j < N) ? pos[i] < pos[j] : i > j;
    }

    void dump()
    {
        for (int i = 0; i < N; ++i) cout << "suffix[" << i << "]=" << sa[i] << ": " << s.substr(sa[i]) << endl;
        for (int i = 0; i < N; ++i) cout << "LCP[" << i << "]=" << lcp[i] << endl;
    }
};

typedef long long ll;

vector<ll> pf, pr;

namespace MO
{
const int MAX = 100001;
const int BLOCK = sqrt(MAX);

struct query
{
    int l, r;
    ll answer;
    query(): l(), r(), answer() {}
};

bool operator<(const query& lhv, const query& rhv)
{
    if (lhv.l / BLOCK != rhv.l / BLOCK) return lhv.l / BLOCK < rhv.l / BLOCK;
    return ((lhv.l / BLOCK) & 1) ? lhv.r > rhv.r : lhv.r < rhv.r;
}

template<typename T, typename Comp = std::less<T>>
struct IndexSorter
{
    const vector<T>& values;
    Comp op;

    IndexSorter(const vector<T>& values_, Comp op_ = Comp()): values(values_), op(op_) {}
    bool operator()(int lhv, int rhv) { return op(values[lhv], values[rhv]); }
};

void add_left(int l, int r, ll& answer)
{
    // add number of unique substrings that start at position L-1 and finish at most at position R
    if (pf[l - 1] <= r) answer += (ll)r - pf[l - 1] + 1;
}

void delete_left(int l, int r, ll& answer)
{
    // delete number of unique substrings that start at position L and finish at most at position R
    if (pf[l] <= r) answer -= (ll)r - pf[l] + 1;
}

void add_right(int l, int r, ll& answer)
{
    // add number of unique substrings that start at least at position L and finish at position R+1
    if (pr[r + 1] >= l) answer += pr[r + 1] - l + 1;
}

void delete_right(int l, int r, ll& answer)
{
    // delete number of unique substrings that start at least at position L and finish at position R
    if (pr[r] >= l) answer -= pr[r] - l + 1;
}

void solve_offline(vector<query>& queries)
{
    // index sorting according to MO's comparison
    vector<int> indices(queries.size());
    for (int i = 0; i < indices.size(); ++i) indices[i] = i;
    sort(indices.begin(), indices.end(), IndexSorter<query>(queries));

    ll answer = 0;
    int l = 0;
    int r = -1;
    for (int i = 0; i < indices.size(); ++i)
    {
        query& q = queries[indices[i]];
        while (l < q.l) delete_left(l++, r, answer);
        while (l > q.l) add_left(l--, r, answer);
        while (r < q.r) add_right(l, r++, answer);
        while (r > q.r) delete_right(l, r--, answer);
        q.answer = answer;
    }
}

} // namespace MO

string reverse(const string& s)
{
    string res(s);
    int N = (int)s.size();
    for (int i = 0; i < N / 2; ++i) swap(res[i], res[N - 1 - i]);
    return res;
}

int main()
{
    string str;
    cin >> str;

    int Q;
    cin >> Q;
    vector<MO::query> queries(Q);
    for (int i = 0; i < Q; ++i)
    {
        cin >> queries[i].l >> queries[i].r;
        --queries[i].l;
        --queries[i].r;
    }

    // build suffix and LCP arrays for string and its reverse
    suffix_array saf, sar;
    saf.create(str, true);
    string strr = reverse(str);
    sar.create(strr, true);
    //saf.dump();
    //sar.dump();

    // build array that maps index i to position p such that all substrings S[i,p], S[i,p+1], ..., S[i,N] are unique
    // build similar array for reversed string so that for given index i we know position p such that S[p,i], S[p-1,i], ..., S[0, i] are unique
    pf.resize(saf.N);
    pr.resize(sar.N);
    for (int i = 0; i < saf.N; ++i)
    {
        int p = saf.lcp[i];
        if (i > 0) p = max(p, saf.lcp[i - 1]);
        pf[saf.sa[i]] = saf.sa[i] + p;
        //cout << "pf[" << saf.sa[i] << "]=" << pf[saf.sa[i]] << endl;
    }
    for (int i = 0; i < sar.N; ++i)
    {
        int p = sar.lcp[i];
        if (i > 0) p = max(p, sar.lcp[i - 1]);
        pr[sar.N - 1 - sar.sa[i]] = sar.N - 1 - (sar.sa[i] + p);
        //cout << "pr[" << saf.sa[i] << "]=" << pr[saf.sa[i]] << endl;
    }

    // answer all queries by using MO's offline algorithm
    MO::solve_offline(queries);

    for (int i = 0; i < Q; ++i) cout << queries[i].answer << endl;

    return 0;
}
