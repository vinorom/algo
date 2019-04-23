/**
 * http://www.codechef.com/SNCKQL16/problems/KGOOD
 */

#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        string word;
        int K;
        cin >> word >> K;

        const int LETTERS = 26;
        int counts[LETTERS];
        fill(counts, counts + LETTERS, 0);
        for (auto c: word) counts[c - 'a']++;

        sort(counts, counts + LETTERS);

        int sum_prefix[LETTERS];
        int sum_suffix[LETTERS];
        for (int i = 0; i < LETTERS; ++i) sum_prefix[i] = i == 0 ? counts[i] : sum_prefix[i-1] + counts[i];
        for (int i = LETTERS - 1; i >= 0; --i) sum_suffix[i] = i == LETTERS - 1 ? counts[i] : sum_suffix[i+1] + counts[i];

        int min_remove_count = sum_suffix[0];
        int x = -1;
        for (int i = 0; i < LETTERS; ++i)
        {
            if (counts[i] == x) continue;

            x = counts[i];
            auto y = x + K;
            auto remove_count = sum_prefix[i] - x;
            auto it = upper_bound(begin(counts) + i, end(counts), y);
            if (it != end(counts))
            {
                int pos = it - begin(counts);
                remove_count += sum_suffix[pos] - y * (LETTERS - pos);
            }

            min_remove_count = min(min_remove_count, remove_count);
        }

        cout << min_remove_count << '\n';
    }

    return 0;
}
