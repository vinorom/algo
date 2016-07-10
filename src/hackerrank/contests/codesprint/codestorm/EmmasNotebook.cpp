/**
 * https://www.hackerrank.com/contests/codestorm/challenges/emmas-notebook
 */

#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ll t;
    cin >> t;

    ll answer = (t & 1) ? (t+3)*(t+1)/4-1 : (t+2)*(t+2)/4-1;

    cout << answer << endl;

    return 0;
}
