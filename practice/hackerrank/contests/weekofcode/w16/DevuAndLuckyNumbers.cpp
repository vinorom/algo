/**
 * https://www.hackerrank.com/contests/w16/challenges/devu-and-lucky-numbers
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int MOD = 1000000007;
const int MAX = 101;

ll pow_mod(ll a, ll b, ll m) // = a^b (mod m)
{
    if (b == 0) return 1;
    ll res = pow_mod(a, b / 2, m);
    res *= res;
    res %= m;
    if (b & 1) res *= a;
    return res % m;
}

ll pow11_mod(ll b, ll m) // = 10^b + 10^(b-1) + ... + 10^0 (mod m)
{
    static ll pow11[MAX * 3 + 1] = {0};
    if (pow11[b]) return pow11[b];

    if (b == 0) return 0;

    ll res = pow11_mod(b - 1, m) * 10 + 1;
    pow11[b] = res % m;
    return pow11[b];
}

ll fact_mod(ll n, ll m) // = n! (mon m)
{
    static ll fact[MAX * 3 + 1] = {0};
    if (fact[n]) return fact[n];

    if (n == 0) return 1;

    ll res = fact_mod(n - 1, m) * n;
    fact[n] = res % m;
    return fact[n];
}

ll inv_mod_prime(ll a, ll m) // = a^(-1) (mod m) (for prime m only)
{
    // if m is prime then (https://en.wikipedia.org/wiki/Modular_multiplicative_inverse):
    // a^(-1) = a^(m-2) (mod m)
    return pow_mod(a, m - 2, m);
}

ll div_mod(ll a, ll b, ll m) // = a/b (mod m)
{
    return (a * inv_mod_prime(b, m)) % m;
}

struct coef
{
    ll x, y, z;
    coef(): x(), y(), z() {}
    coef(ll x_, ll y_, ll z_): x(x_ % MOD), y(y_ % MOD), z(z_ % MOD) {}

    coef& operator+=(const coef& rhv)
    {
        x += rhv.x, x %= MOD;
        y += rhv.y, y %= MOD;
        z += rhv.z, z %= MOD;
        return *this;
    }

    coef& operator-=(const coef& rhv)
    {
        x += MOD - rhv.x, x %= MOD;
        y += MOD - rhv.y, y %= MOD;
        z += MOD - rhv.z, z %= MOD;
        return *this;
    }

    coef& operator*=(const coef& rhv)
    {
        x *= rhv.x, x %= MOD;
        y *= rhv.y, y %= MOD;
        z *= rhv.z, z %= MOD;
        return *this;
    }
};

coef c[MAX][MAX][MAX];

int solve(int x, int y, int z)
{
    ll xf = 1; // = xi!
    for (int xi = 0; xi <= x; ++xi, xf = (xf * xi) % MOD)
    {
        ll yf = 1; // = yi!
        for (int yi = 0; yi <= y; ++yi, yf = (yf * yi) % MOD)
        {
            ll zf = 1; // zi!
            for (int zi = 0; zi <= z; ++zi, zf = (zf * zi) % MOD)
            {
                // C[x,y,z] = C[x-1,y,z] + C[x,y-1,z] + C[x,y,z-1]          // 1 digit less numbers
                //          - C[x-1,y-1,z] - C[x-1,y,z-1] - C[x,y-1,z-1]    // 2 digits less numbers are counted twice
                //          + C[x-1,y-1,z-1]                                // 3 digits less numbers are missed now
                //          + (k*x,k*y,k*z)                                 // new (x+y+z) digit numbers,
                //                                                          // there are A=(x+y+z)!/(x!*y!*z!) such numbers,
                //                                                          // k=11.11*A/(x+y+z)

                ll s = xi + yi + zi;
                c[xi][yi][zi] = coef();
                if (s == 0) continue;

                if (xi > 0) c[xi][yi][zi] += c[xi - 1][yi][zi];
                if (yi > 0) c[xi][yi][zi] += c[xi][yi - 1][zi];
                if (zi > 0) c[xi][yi][zi] += c[xi][yi][zi - 1];
                if (xi * yi > 0) c[xi][yi][zi] -= c[xi - 1][yi - 1][zi];
                if (xi * zi > 0) c[xi][yi][zi] -= c[xi - 1][yi][zi - 1];
                if (yi * zi > 0) c[xi][yi][zi] -= c[xi][yi - 1][zi - 1];
                if (xi * yi * zi > 0) c[xi][yi][zi] += c[xi - 1][yi - 1][zi - 1];

                ll sf = fact_mod(s - 1, MOD);
                ll pf = ((((xf * yf) % MOD) * zf) % MOD);
                ll k = (pow11_mod(s, MOD) * div_mod(sf, pf, MOD)) % MOD;
                c[xi][yi][zi] += coef((k * xi) % MOD, (k * yi) % MOD, (k * zi) % MOD);
            }
        }
    }

    coef co = c[x][y][z];
    co *= coef(4, 5, 6);
    return int((co.x + co.y + co.z) % MOD);
}

int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    cout << solve(x, y, z) << endl;
    return 0;
}
