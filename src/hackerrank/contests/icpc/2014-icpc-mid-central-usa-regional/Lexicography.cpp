/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/lexicography
 */

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MAXN = 17;
ll fact[MAXN];

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) fact[i] = fact[i-1] * i;
}

string kth_anagram(const string& word, ll k)
{
    int n = (int)word.size();

    int count[26] = {0};
    for (int i = 0; i < n; ++i) count[word[i] - 'A']++;

    typedef pair<char, int /*count*/> PCI;
    vector<PCI> letters;
    ll pif = 1;
    for (int i = 0; i < 26; ++i)
    {
        if (count[i])
        {
            letters.push_back(PCI('A' + i, count[i]));
            pif *= fact[count[i]];
        }
    }

    stringstream anagram;

    ll s = fact[n] / pif;
    while (!letters.empty())
    {
        ll sum = 0;
        int i = 0, letters_count = (int)letters.size();
        for (; i < letters_count && sum + s * letters[i].second / n < k; ++i)
        {
            sum += s * letters[i].second / n;
        }
        if (i == letters_count) --i;

        k -= sum;
        s = s * letters[i].second / n--;
        anagram << letters[i].first;

        if (--letters[i].second == 0) letters.erase(letters.begin() + i);
    }

    return anagram.str();
}

int main()
{
    precompute();

    string word;
    ll k;
    while ((cin >> word >> k) && word != "#" && k != 0)
    {
        cout << kth_anagram(word, k) << endl;
    }

    return 0;
}
