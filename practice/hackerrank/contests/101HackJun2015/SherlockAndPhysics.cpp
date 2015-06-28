/**
 * https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-physics
 */

#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if (a > b) swap(a, b);
    if (a == 0) return b;
    return gcd(a, b % a);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int R, S;
        cin >> R >> S;

        int cycles = R / S;
        int rest = R % S;
        int steps = 0, x = 0, y = 0;
        if (rest <= S / 4)
        {
            // hit B at t = 0, A and B collide as soon as B reaches circle (angle = rest * (2*pi / S))
            steps = R;
            x = rest;
            y = S;
        }
        else
        {
            // hit B at t = S - rest, A and B collide in point (R, 0)
            steps = R + (S - rest);
            x = 0;
            y = 1;
        }

        // make irreducible fraction
        int g = gcd(x, y);
        x /= g;
        y /= g;

        cout << steps << ' ' << x << '/' << y << endl;
    }
    return 0;
}
