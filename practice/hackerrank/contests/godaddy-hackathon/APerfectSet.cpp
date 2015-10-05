/**
 * https://www.hackerrank.com/contests/godaddy-hackathon/challenges/a-perfect-set
 */

#include <iostream>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;

    int answer = (n + 1) / 2 + d;
    cout << answer << endl;

    return 0;
}
