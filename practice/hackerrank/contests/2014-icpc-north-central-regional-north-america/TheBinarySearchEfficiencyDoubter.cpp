/**
 * https://www.hackerrank.com/contests/2014-icpc-north-central-regional-north-america-practice/challenges/the-binary-search-efficiency-doubter
 */

#include <iostream>

using namespace std;

const int MAXN = 10000000;
int cache[MAXN];

int bscount(int n)
{
    if (n < 2) return n;
    if (cache[n]) return cache[n];
    cache[n] = ((n-1)/2 + bscount((n-1)/2)) + 1 + (n/2 + bscount(n/2));
    return cache[n];
}

int main()
{
    int n, t = 1;
    while (cin >> n)
    {
        cout << "Case " << t++ << ": " << bscount(n) << endl;
    }
    return 0;
}
