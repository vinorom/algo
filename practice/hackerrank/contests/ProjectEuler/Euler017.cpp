/**
 * Problem:
 *       Number to Words
 *
 * Links:
 *      https://projecteuler.net/problem=17
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler017
 */

#include <iostream>
#include <sstream>
#include <deque>

using namespace std;

typedef long long ll;

const string THOUSANDS[] = { "", "Thousand", "Million", "Billion", "Trillion" };
const string HUNDRED = "Hundred";
const string ZERO = "Zero";
const string VALUES20[] =
{
    "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
    "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
};
const string TENS[] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
const string AND = "and";
const char DELIM = ' ';

void to_words_within_thousand(ll N, bool add_and, deque<string>& words) // [0, 1000)
{
    words.clear();

    if (N / 100 != 0)
    {
        words.push_back(VALUES20[N / 100]);
        words.push_back(HUNDRED);
    }

    N %= 100;

    if (N != 0)
    {
        if (!words.empty() && add_and) words.push_back(AND);
        if (N < 20)
        {
            words.push_back(VALUES20[N]);
        }
        else
        {
            words.push_back(TENS[N / 10]);
            words.push_back(VALUES20[N % 10]);
        }
    }
}

string to_words(ll N, bool add_and)
{
    if (N == 0) return ZERO;

    deque<string> words;
    deque<string> words_within_thousand;
    for (int i = 0; i <= 4 && N != 0; ++i, N /= 1000)
    {
        to_words_within_thousand(N % 1000, add_and, words_within_thousand);
        if (!words_within_thousand.empty()) words.insert(words.begin(), THOUSANDS[i]);
        words.insert(words.begin(), words_within_thousand.begin(), words_within_thousand.end());
    }

    stringstream ss;
    bool empty = true;
    for (int i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        if (!empty) ss << DELIM;
        ss << words[i];
        empty = false;
    }

    return ss.str();
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        ll N;
        cin >> N;
        cout << to_words(N, false) << endl;
    }
    return 0;
}
