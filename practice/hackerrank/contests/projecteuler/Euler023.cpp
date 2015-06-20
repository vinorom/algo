/**
 * Problem:
 *       Non-abundant sums
 *
 * Links:
 *      https://projecteuler.net/problem=23
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler023
 */

#include <iostream>
#include <set>

using namespace std;

typedef set<int> IntSet;

const int MAX = 100001;
int sum_divisors[MAX] = {0};
IntSet abundants;

void precompute_abundants()
{
    for (int i = 2; i < MAX / 2; ++i)
    {
        for (int j = i + i; j < MAX; j += i) sum_divisors[j] += i;
        if (sum_divisors[i] > i) abundants.insert(i);
    }
}

bool is_abundant_sum(int N)
{
    for (IntSet::const_iterator it = abundants.begin(), end = abundants.end(); it != end && (*it) < N; ++it)
    {
        if (abundants.find(N - (*it)) != abundants.end()) return true;
    }
    return false;
}

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    precompute_abundants();

#ifdef ORIGINAL_EULER_PROBLEM

    int sum = 0;
    for (int i = 1; i <= 28123; ++i)
    {
        if (!is_abundant_sum(i)) sum += i;
    }
    cout << sum << endl;

#else

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << (is_abundant_sum(N) ? "YES" : "NO") << endl;
    }

#endif

    return 0;
}
