/**
 * Problem:
 *       Lexicographic permutations
 *
 * Links:
 *      https://projecteuler.net/problem=24
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler024
 */

#include <iostream>
#include <sstream>

using namespace std;

typedef long long ll;

//#define ORIGINAL_EULER_PROBLEM

// input word (assumed it is sorted, i.e. it is 1st permutation in alphabetical order)
#ifdef ORIGINAL_EULER_PROBLEM
const string WORD = "0123456789";
#else
const string WORD = "abcdefghijklm";
#endif

ll factorial(int n)
{
    static const int MAX = 26;
    static ll cache[MAX] = {0};

    if (n == 0) return 1;
    if (n < MAX && cache[n] != 0) return cache[n];
    cache[n] = factorial(n - 1) * n;
    return cache[n];
}

string nth_lexgraph_permutation(ll N)
{
    stringstream res;
    string word(WORD); // remaining elements

    if (N < 1 || N > factorial((int)word.size())) return "ERROR";

    --N; // count from zero
    while (!word.empty())
    {
        ll perms = factorial((int)word.size() - 1);
        ll pos = N / perms;
        N %= perms;
        res << word[pos];
        word.erase((size_t)pos, 1);
    }

    return res.str();
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        cout << nth_lexgraph_permutation(N) << endl;
    }
    return 0;
}
