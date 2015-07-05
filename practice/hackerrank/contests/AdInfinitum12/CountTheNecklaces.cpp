/**
 * https://www.hackerrank.com/contests/infinitum12/challenges/count-the-necklaces
 */

#include <iostream>
#include <assert.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
const int MOD = 1000000007;

ll pows_mod[MAX] = {0};

int gcd(int a, int b)
{
    if (a > b) swap(a, b);
    if (a == 0) return b;
    return gcd(a, b % a);
}

ll mult_mod(ll a, ll b, ll mod) // = a*b % mod
{
    if (b == 0) return 0;
    return (mult_mod(a, b / 2, mod) * 2 + (b % 2 != 0 ? a : 0)) % mod;
}

ll pow_mod(int a, int n, ll mod) // = a^n % mod
{
    if (pows_mod[n]) return pows_mod[n];
    if (n == 0) return 1;

    ll res = pow_mod(a, n / 2, mod);
    res = mult_mod(res, res, mod);
    if (n % 2 == 1) res = mult_mod(res, a, mod);

    pows_mod[n] = res;
    return pows_mod[n];
}

ll solve(int N, int K)
{
    // Use Burnside's lemma:
    // https://en.wikipedia.org/wiki/Burnside%27s_lemma

    const ll rotation_count = N; // each <i> rotation rotates i beads, i=-N/2..N/2
    ll necklace_count = 0; // number of distinct necklaces
    ll invariants_mod = 0; // intermediate remainder, should be zero at the end

    // one identity <0> rotation that leaves all K^N elements unchanged
    ll res = pow_mod(K, N, rotation_count * MOD);
    necklace_count += res / rotation_count;
    invariants_mod += res % rotation_count;

    // all remaining N-1 rotations
    for (int i = 1; i <= N / 2; ++i)
    {
        // each rotation leaves K^GCD(i,N) elements unchanged
        int g = gcd(i, N);
        res = pow_mod(K, g, rotation_count * MOD);
        if (g == N / 2) // single <N/2> rotation
        {
            necklace_count += res / rotation_count;
            invariants_mod += res % rotation_count;
        }
        else // two rotations <i> and <-i> (clockwise and counterclockwise)
        {
            necklace_count += res / rotation_count * 2;
            invariants_mod += res % rotation_count * 2;
        }
    }

    // count the reminder
    necklace_count += invariants_mod / rotation_count;
    invariants_mod %= rotation_count;
    necklace_count %= MOD;

    assert(invariants_mod == 0);

    return necklace_count;
}

int main()
{
    int N, K;
    cin >> N >> K;
    cout << solve(N, K) << endl;
    return 0;
}
