/**
 * Problem:
 *       Integer right triangles
 *
 * Links:
 *      https://projecteuler.net/problem=39
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler039
 */

#include <iostream>

using namespace std;

const int MAXN = 5000001;

int counts[MAXN]; // number of pythagorean triples for a given perimeter
int answers[MAXN];

int gcd(int a, int b)
{
    if (a > b) swap(a, b);
    return a == 0 ? b : gcd(b % a, a);
}

bool coprime(int a, int b)
{
    return gcd(a, b) == 1;
}

void precompute()
{
    // https://en.wikipedia.org/wiki/Pythagorean_triple

    fill(counts, counts + MAXN, 0);
    for (int m = 2; m*m < MAXN / 3; ++m)
    {
        for (int n = 1; n < m; ++n)
        {
            if ((m-n) % 2 && coprime(m, n))
            {
                int a = m*m - n*n;
                int b = 2*m*n;
                int c = m*m + n*n;
                int p = a+b+c;

                for (int k = 1; k*p < MAXN; ++k) ++counts[k*p];
            }
        }
    }

    int max_count = -1;
    int maxp = -1;
    for (int i = 0; i < MAXN; ++i)
    {
        if (max_count < counts[i])
        {
            max_count = counts[i];
            maxp = i;
        }
        answers[i] = maxp;
    }
}

int main()
{
    precompute();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << answers[N] << endl;
    }

    return 0;
}
