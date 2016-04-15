/**
 * http://code.google.com/codejam/contest/6234486/dashboard#s=p1
 */

#include <bits/stdc++.h>

using namespace std;

const double g = 9.8;
const double eps = 10e-7;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int V, D;
        cin >> V >> D;
        double y = g * D / V / V;
        double alfa_rad = abs(y - 1.0) < eps ? M_PI / 4 : asin(y) / 2;
        double alfa_deg = alfa_rad * 180 / M_PI;

        cout << "Case #" << t << ": " << std::fixed << std::setprecision(9) << alfa_deg << '\n';
    }

    return 0;
}
