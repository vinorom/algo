/**
 * Problem:
 *      Cracking the Coding Interview: Hash Tables: Ransom Note
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-ransom-note
 */

#include <unordered_map>
#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    unordered_map<string, int> words;
    string word;
    while (m--)
    {
        cin >> word;
        words[word]++;
    }

    bool possible = true;
    while (n--)
    {
        cin >> word;
        auto it = words.find(word);
        if (it == words.end() || it->second == 0)
        {
            possible = false;
            break;
        }

        --it->second;
    }

    cout << (possible ? "Yes" : "No") << '\n';

    return 0;
}

