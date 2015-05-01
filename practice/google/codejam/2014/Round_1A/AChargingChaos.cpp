/**
 * Problem: http://code.google.com/codejam/contest/2984486/dashboard#s=p0
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <bitset>

using namespace std;

int64_t read_bin()
{
    int64_t val = 0;
    string str;
    cin >> str;
    for (int i = 0; i < str.length(); ++i)
    {
        val <<= 1;
        if (str[i] == '1') val |= 1;
    }
    return val;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N, L;
        cin >> N >> L;
        vector<int64_t> outlets(N);
        vector<int64_t> devices(N);
        unordered_set<int64_t> devices_set(N * 7);
        for (int i = 0; i < N; ++i) outlets[i] = read_bin();
        for (int i = 0; i < N; ++i)
        {
            devices[i] = read_bin();
            devices_set.insert(devices[i]);
        }

        int min_count1 = L + 1;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                int64_t mask = devices[i] ^ outlets[j];
                int k;
                for (k = 0; k < N; ++k)
                {
                    if (devices_set.find(outlets[k] ^ mask) == devices_set.end()) break;
                }
                if (k == N) // full match
                {
                    int count1 = bitset<40>(mask).count();
                    min_count1 = min(min_count1, count1);
                }
            }
        }

        if (min_count1 == L + 1)
        {
            cout << "Case #" << t << ": NOT POSSIBLE" << endl;
        }
        else
        {
            cout << "Case #" << t << ": " << min_count1 << endl;
        }
    }

    return 0;
}
