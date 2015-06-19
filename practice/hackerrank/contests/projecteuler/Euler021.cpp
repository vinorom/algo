/**
 * Problem:
 *       Amicable numbers
 *
 * Links:
 *      https://projecteuler.net/problem=21
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler021
 */

#include <iostream>

using namespace std;

const int MAX = 100001;
const int MAX4 = 4 * MAX;
int sum_divisors[MAX4] = {0};
int prefix_sum_amicable[MAX] = {0};

void pre_calculate_amicables()
{
    std::fill(sum_divisors + 2, sum_divisors + MAX, 1);
    for (int i = 2; i < MAX4 / 2; ++i)
    {
        for (int j = i + i; j < MAX4; j += i) sum_divisors[j] += i;
    }

    for (int i = 1; i < MAX; ++i)
    {
        prefix_sum_amicable[i] = prefix_sum_amicable[i - 1];
        if (sum_divisors[i] != i && sum_divisors[sum_divisors[i]] == i) prefix_sum_amicable[i] += i;
    }
}

int main()
{
    pre_calculate_amicables();

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        cout << prefix_sum_amicable[N - 1] << endl;
    }

    return 0;
}
