/**
 * https://www.hackerrank.com/contests/2014-icpc-southeastern-europe/challenges/banks
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> PII;

int main()
{
    int n;
    cin >> n;

    set<PII, greater<PII>> banks;
    vector<int> capitals(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> capitals[i];
        if (capitals[i] < 0) banks.insert(PII(capitals[i], i));
    }

    int count = 0;
    while (!banks.empty())
    {
        PII cur = *banks.begin();

        int li = (cur.second + n - 1) % n;
        int ri = (cur.second + 1) % n;
        PII left = PII(capitals[li], li);
        PII right = PII(capitals[ri], ri);

        banks.erase(cur);
        banks.erase(left);
        banks.erase(right);

        cur.first = capitals[cur.second] = -cur.first;
        left.first = capitals[li] = left.first - cur.first;
        right.first = capitals[ri] = right.first - cur.first;

        if (left.first < 0) banks.insert(left);
        if (right.first < 0) banks.insert(right);

        ++count;
    }

    cout << count << endl;

    return 0;
}
