/**
 * https://www.hackerrank.com/contests/infinitum12/challenges/marbles
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MOD = 1000000007;

ll pow2(int n)
{
    if (n == 0) return 1;
    ll res = pow2(n / 2);
    res *= res;
    if (n % 2 == 1) res *= 2;
    res %= MOD;
    return res;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;

        // number of ways taking marbles is sum of C(N-1,k) for all k=0..N-1
        // this sum equals to 2^(N-1) according to Newton's binomial formula
        // C(N-1,k) is number of ways taking remaining marbles once first one is taken from (k+1) position

        cout << pow2(N - 1) << endl;
    }
    return 0;
}
