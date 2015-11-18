/**
 * https://www.hackerrank.com/contests/infinitum12/challenges/a-birthday-party
 */

#include <iostream>
#include <iomanip>

using namespace std;

//#define TRACE

typedef long long ll;

const int MOD = 1000000007;
const int MOD2 = 99991; // prime

int mul_mod(int a, int b, int m) // a*b (mod m)
{
    if (b == 0) return 0;
    ll res = mul_mod(a, b / 2, m);
    res += res;
    if (b & 1) res += a;
    return int(res % m);
}

int pow_mod(int a, int b, int m) // a^b (mod m)
{
    if (b == 0) return 1;
    ll res = pow_mod(a, b / 2, m);
    res *= res;
    res %= m;
    if (b & 1) res *= a;
    return int(res % m);
}

int inv_mod_prime(int a, int m) // a^(-1) (mod m) (for prime m only)
{
    // if m is prime then (https://en.wikipedia.org/wiki/Modular_multiplicative_inverse):
    // a^(-1) = a^(m-2) (mod m)
    return pow_mod(a, m - 2, m);
}

int main()
{
    // solve the system of linear equations in field MOD2
    // Gaussian elimination: https://en.wikipedia.org/wiki/Gaussian_elimination

    int N;
    cin >> N;
    int eq[N][N] = {0};
    for (int i = 0; i < N; ++i)
    {
        int K;
        cin >> K;
        std::fill(eq[i], eq[i] + N, 0);
        eq[i][i] = 1;
        while (K--)
        {
            int c;
            cin >> c;
            --c;
            eq[i][c] = (-1 + MOD2) % MOD2;
        }
    }

#ifdef TRACE
#define DUMP \
    for (int ii = 0; ii < N; ++ii) \
    { \
        for (int jj = 0; jj < N; ++jj) cerr << " " << std::setw(7) << eq[ii][jj]; \
        cerr << endl; \
    } \
    cerr << endl;
#else
#define DUMP
#endif

    DUMP;
    for (int i = 0; i < N; ++i)
    {
        if (eq[i][i] == 0)
        {
            int j;
            for (j = i + 1; j < N && eq[j][i] == 0; ++j);
            if (j < N)
            {
                for (int k = i; k < N; ++k) swap(eq[i][k], eq[j][k]);
            }
            else
            {
                continue;
            }
        }
        DUMP;
        if (eq[i][i] != 1)
        {
            int inv = inv_mod_prime(eq[i][i], MOD2);
            for (int k = i; k < N; ++k) eq[i][k] = mul_mod(eq[i][k], inv, MOD2);
        }
        DUMP;
        for (int j = 0; j < N; ++j)
        {
            if (i == j || eq[j][i] == 0) continue;
            int inv = inv_mod_prime(eq[j][i], MOD2);
            for (int k = i; k < N; ++k) eq[j][k] = (mul_mod(eq[j][k], inv, MOD2) - eq[i][k] + MOD2) % MOD2;
        }
        DUMP;
    }

#undef DUMP

    int k = 0; // count number of non zero Ci
    for (int i = 0; i < N; ++i)
    {
        if (eq[i][i] == 0) ++k;
    }

    cout << pow_mod(MOD2, k, MOD) << endl;

    return 0;
}
