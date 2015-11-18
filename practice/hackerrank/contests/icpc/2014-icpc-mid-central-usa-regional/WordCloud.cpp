/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/word-cloud
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef pair<int, int> PII;

int main()
{
    int W, N, t = 1;
    while ((cin >> W >> N) && W * N != 0)
    {
        int C, maxC = 0;
        string stag;
        vector<PII> tags(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> stag >> C;
            tags[i] = PII((int)stag.size(), C);
            maxC = max(maxC, C);
        }

        int height = 0, width = 0, maxP = 0;

        for (int i = 0; i < N; ++i)
        {
            PII tag = tags[i];
            int P = 8 + (int)ceil(40. * (tag.second - 4) / (maxC - 4));
            int w = (int)ceil(9. * tag.first * P / 16);
            width += (width ? 10 : 0) + w;
            if (width <= W)
            {
                maxP = max(maxP, P);
            }
            else
            {
                width = w;
                height += maxP;
                maxP = P;
            }
        }

        if (width) height += maxP;

        cout << "CLOUD " << t++ << ": " << height << endl;
    }
    return 0;
}
