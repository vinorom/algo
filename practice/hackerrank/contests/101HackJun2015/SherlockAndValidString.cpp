/**
 * https://www.hackerrank.com/contests/101hack26/challenges/sherlock-and-valid-string
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string str;
    cin >> str;

    static const int LETTERS = 26;
    int count[LETTERS] = {0};
    for (int i = 0; i < str.size(); ++i) ++count[str[i] - 'a'];
    std::sort(count, count + LETTERS);

    int pos = 0;
    while (count[pos] == 0 && pos < LETTERS) ++pos;

    int* min = count + pos;
    int* max = count + LETTERS - 1;
    if (min[0] == max[0] ||                             // nothing to remove
        (min[0] == 1 && min[1] == max[0]) ||            // remove least frequent letter
        (min[0] == max[-1] && max[0] == max[-1] + 1))   // remove most frequent letter
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
