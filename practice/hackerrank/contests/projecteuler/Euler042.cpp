/**
 * Problem:
 *       Coded triangle numbers
 *
 * Links:
 *      https://projecteuler.net/problem=42
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler042
 */

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

typedef long long ll;

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll tn;

#ifdef ORIGINAL_EULER_PROBLEM
        string word;
        cin >> word;
        tn = 0;
        for (size_t i = 0; i < word.size(); ++i) tn += word[i] - 'A' + 1;
#else
        cin >> tn;
#endif

        // check if tn = n(n+1)/2
        ll tn2 = tn * 2;
        ll n = (ll)sqrt(tn2);
        cout << ((tn2 % n == 0 && tn2 / n == n + 1) ? n : -1) << endl;
    }

    return 0;
}
