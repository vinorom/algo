/**
 * Problem:
 *      Special Pythagorean triplet
 *
 * Links:
 *      https://projecteuler.net/problem=9
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler009
 */

#include <iostream>

using namespace std;

typedef long long ll;

ll solve(int N)
{
    ll max_product = -1;
    for (int a = 1; a < N/3; ++a) //  a+b+c=N, a<b<c
    {
        // b+c=N-A => c = N-A-b => (N-A)^2-2(N-A)b+b^2-b^2=A^2 => b=((N-A)^2-A^2)/(2(N-A))
        // c^2-b^2=A^2

        int na = N-a;
        int b = (na*na-a*a)/(2*na);
        int c = na-b;
        if (a < b && b < c && a*a+b*b == c*c)
        {
            max_product = max(max_product, (ll)a*b*c);
        }
    }

    return max_product;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        ll answer = solve(N);
        cout << answer << endl;
    }
    return 0;
}
