/**
 * https://www.hackerrank.com/contests/round-2-acm-icpc-warmup-2015/challenges/lets-play-tawla
 */

#include <iostream>

using namespace std;

string single_dice_names[] = { "", "Yakk", "Doh", "Seh", "Ghar", "Bang", "Sheesh" };
string double_dice_names[] = { "", "Habb Yakk", "Dobara", "Dousa", "Dorgy", "Dabash", "Dosh" };
string dice_5_6_name("Sheesh Beesh");

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        int a, b;
        cin >> a >> b;
        if (a < b) swap(a, b);

        string answer;
        if (a == b)
        {
            answer = double_dice_names[a];
        }
        else if (a == 6 && b == 5)
        {
            answer = dice_5_6_name;
        }
        else
        {
            answer = single_dice_names[a] + ' ' + single_dice_names[b];
        }
        cout << "Case " << t << ": " << answer << endl;
    }
    return 0;
}
