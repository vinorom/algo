/**
 * Problem:
 *       Names scores
 *
 * Links:
 *      https://projecteuler.net/problem=22
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler022
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string> StrVec;

int binary_search(const StrVec& vec, const string value)
{
    int left = 0;
    int right = (int)vec.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int res = value.compare(vec[mid]);
        if (res == 0) return mid;
        if (res < 0)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

int get_alpha_value(const string& value)
{
    int res = 0;
    for (int i = 0; i < value.size(); ++i) res += toupper(value[i]) - int('A') + 1;
    return res;
}

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    int N;
    cin >> N;
    StrVec names(N);
    for (int i = 0; i < N; ++i) cin >> names[i];

    std::sort(names.begin(), names.end());

#ifdef ORIGINAL_EULER_PROBLEM

    int total_score = 0;
    for (int i = 0; i < N; ++i)
    {
        total_score += (i + 1) * get_alpha_value(names[i]);
    }
    cout << total_score << endl;

#else

    int Q;
    cin >> Q;
    string name;
    while (Q--)
    {
        cin >> name;
        int pos = binary_search(names, name);
        int score = (pos + 1) * get_alpha_value(name);
        cout << score << endl;
    }

#endif

    return 0;
}
