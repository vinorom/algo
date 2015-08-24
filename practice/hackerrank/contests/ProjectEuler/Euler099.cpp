/**
 * Problem:
 *      Largest exponential
 *
 * Links:
 *      https://projecteuler.net/problem=99
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler099
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct exp_num // base ^ exponent
{
    int base;
    int exponent;
};

bool operator<(const exp_num& lhv, const exp_num& rhv)
{
    return log10((double)lhv.base) * lhv.exponent < log10((double)rhv.base) * rhv.exponent;
}

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    int N;
    cin >> N;
    exp_num a[N];
    for (int i = 0; i < N; ++i) cin >> a[i].base >> a[i].exponent;

#ifdef ORIGINAL_EULER_PROBLEM
    cout << (std::max_element(a, a + N) - a + 1) << endl;
#else
    int K;
    cin >> K; --K;
    std::nth_element(a, a + K, a + N);
    cout << a[K].base << ' ' << a[K].exponent << endl;
#endif

    return 0;
}
