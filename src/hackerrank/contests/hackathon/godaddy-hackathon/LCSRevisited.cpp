/**
 * https://www.hackerrank.com/contests/godaddy-hackathon/challenges/lcs3
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 3001;

int a[3][MAXN];
vector<int> indices[3][MAXN];

struct triplet
{
    int x, y, z;
    int max_lcs;
    triplet(int x_ = 0, int y_ = 0, int z_ = 0): x(x_), y(y_), z(z_), max_lcs(1) {}
    bool operator<(const triplet& r) { return x < r.x && y < r.y && z < r.z; }
};
triplet triplets[MAXN*100];

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                indices[i][j+1].clear();
                cin >> a[i][j];
            }
        }

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                indices[i][a[i][j]].push_back(j);
            }
        }

        // find all triplets (x, y, z) such that a[0][x] = a[1][y] = a[2][z]
        // there should be O(N) such triplets: O(N^3) possible triplets, each with probability 1/N^2
        int tcount = 0;
        for (int t = 1; t <= N; ++t)
        {
            for (int i = 0; i < indices[0][t].size(); ++i)
            {
                for (int j = 0; j < indices[1][t].size(); ++j)
                {
                    for (int k = 0; k < indices[2][t].size(); ++k)
                    {
                        triplets[tcount++] = triplet(indices[0][t][i], indices[1][t][j], indices[2][t][k]);
                    }
                }
            }
        }

        // sort triplets: O(N log N)
        sort(triplets, triplets + tcount,
             [](triplet l, triplet r)
             {
                 if (l.x != r.x) return l.x < r.x;
                 if (l.y != r.y) return l.y < r.y;
                 return l.z < r.z;
             });

        // LCS DP approach
        int max_lcs = 0;
        for (int i = 0; i < tcount; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (triplets[j] < triplets[i])
                {
                    triplets[i].max_lcs = max(triplets[i].max_lcs, triplets[j].max_lcs + 1);
                }
            }
            max_lcs = max(max_lcs, triplets[i].max_lcs);
        }

        cout << max_lcs << endl;
    }

    return 0;
}
