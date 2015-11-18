/**
 * https://www.hackerrank.com/contests/2014-icpc-central-europe-regional-contest-practice/challenges/wheels
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

struct point
{
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct circle: public point
{
    int r;
};

double distance(point p1, point p2)
{
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return sqrt(dx * dx + dy * dy);
}

ll gcd(ll a, ll b)
{
    if (a > b) swap(a, b);
    return a == 0 ? b : gcd(b % a, a);
}

struct rational
{
    ll p, q; //  q > 0
    rational(ll p_ = 0, ll q_ = 1): p(p_), q(q_)
    {
        ll g = gcd(abs(p), q);
        p /= g;
        q /= g;
    }
};

const double EPS = 1e-9;
const int MAXN = 1001;

circle wheels[MAXN];
vector<int> connected_with[MAXN];
rational rates[MAXN];

void dfs(int wheel, rational rate)
{
    rates[wheel] = rate;
    for (int w : connected_with[wheel])
    {
        if (rates[w].p == 0) // not visited
        {
            rational r(-rates[wheel].p * wheels[wheel].r, rates[wheel].q * wheels[w].r);
            dfs(w, r);
        }
    }
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) connected_with[i].clear();
        fill(rates, rates + n, rational());

        for (int i = 0; i < n; ++i)
        {
            cin >> wheels[i].x >> wheels[i].y >> wheels[i].r;

            for (int j = 0; j < i; ++j)
            {
                if (abs(distance(wheels[j], wheels[i]) - (wheels[j].r + wheels[i].r)) < EPS)
                {
                    connected_with[i].push_back(j);
                    connected_with[j].push_back(i);
                }
            }
        }

        dfs(0, 1); // rotate all connected wheels

        for (int i = 0; i < n; ++i)
        {
            rational r = rates[i];
            if (r.p == 0)
            {
                cout << "not moving\n";
            }
            else
            {
                cout << abs(r.p);
                if (r.q != 1) cout << '/' << r.q;
                cout << ' ' << (r.p > 0 ? "clockwise" : "counterclockwise") << '\n';
            }
        }
    }

    return 0;
}
