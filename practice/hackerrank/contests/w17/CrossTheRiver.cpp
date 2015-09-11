/**
 * https://www.hackerrank.com/contests/w17/challenges/cross-the-river
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace segment_tree
{

const int INF = (int)2e9;

#define ST_HEIGHT(n) (int)ceil(log2(n))
#define ST_SIZE(n) (2*(1<<ST_HEIGHT(n))-1)

//int st[ST_SIZE(N)];
//int st[1 << 20]; // size=2*2^ceil(log2(n))-1

namespace RMQ
{

void construct_empty(int* st, int si, int sl, int sr)
{
    st[si] = -INF;

    if (sl == sr) return;

    int mid = (sl+sr)/2;
    construct_empty(st, si*2+1, sl, mid);
    construct_empty(st, si*2+2, mid+1, sr);
}

void update(int* st, int si, int sl, int sr, int idx, int val)
{
    if (sl == sr)
    {
        st[si] = val;
        return;
    }

    int mid = (sl+sr)/2;
    if (idx <= mid)
    {
        update(st, si*2+1, sl, mid, idx, val);
    }
    else
    {
        update(st, si*2+2, mid+1, sr, idx, val);
    }
    st[si] = std::max(st[si*2+1], st[si*2+2]);
}

int get(int* st, int si, int sl, int sr, int l, int r)
{
    if (l > r) return -INF;

    if (sl == l && sr == r) return st[si];

    int mid = (sl+sr)/2;
    return std::max(get(st, si*2+1, sl, mid, l, min(mid, r)),
                    get(st, si*2+2, mid+1, sr, max(mid+1, l), r));
}

} // namespace RMQ
} // namespace segment tree


struct rock
{
    int x, y, z;
    rock(int x_ = 0, int y_ = 0, int z_ = 0): x(x_), y(y_), z(z_) {}
    bool operator<(const rock& rhv) { return x < rhv.x; }
};

const int MAXN = 100000;

rock rocks[MAXN];
int ans[MAXN] = {0};
int st[ST_SIZE(MAXN)];

int main()
{
    using namespace segment_tree::RMQ;

    int N, H, dh, dw;
    cin >> N >> H >> dh >> dw;
    for (int i = 0; i < N; ++i) cin >> rocks[i].y >> rocks[i].x >> rocks[i].z;

    // sort by X to construct segment tree
    sort(rocks, rocks + N);
    construct_empty(st, 0, 0, N-1);

    // construct event queue and sort it by <Y,id>:
    //   Y, 0 <= id < N: event to calculate best score for rock with index = id
    //   Y, id >= N: event to add rock with index = id-N to segment tree (should go last for the same Y)
    //   Y+dH+1, id < 0: event to remove rock with index = -id-1 from segment tree
    vector<pair<int /*y*/, int /*id*/>> events;
    for (int i = 0; i < N; ++i)
    {
        events.push_back(make_pair(rocks[i].y, i));
        events.push_back(make_pair(rocks[i].y, N+i));
        events.push_back(make_pair(rocks[i].y+dh+1, -i-1));
    }

    sort(begin(events), end(events));
    for (int i = 0; i < events.size(); ++i)
    {
        int id = events[i].second;
        if (id < 0) // remove rock
        {
            id = -id - 1;
            update(st, 0, 0, N-1, id, -segment_tree::INF);
            continue;
        }
        else if (id >= N) // add rock
        {
            id -= N;
            update(st, 0, 0, N-1, id, ans[id]);
            continue;
        }
        // calc best score
        int l = (int)(lower_bound(rocks, rocks + N, rock(rocks[id].x-dw, -1, -1)) - rocks);
        int r = (int)(lower_bound(rocks, rocks + N, rock(rocks[id].x+dw+1 , -1, -1)) - rocks);
        int best = get(st, 0, 0, N-1, l, r-1);
        ans[id] = (best < 0 && rocks[id].y <= dh ? 0 : best) + rocks[id].z;
    }

    // find the best reachable from oppiste shore
    int best = -segment_tree::INF;
    for (int i = 0; i < N; ++i)
    {
        if (H - rocks[i].y <= dh) best = max(best, ans[i]);
    }

    cout << best << endl;

    return 0;
}
