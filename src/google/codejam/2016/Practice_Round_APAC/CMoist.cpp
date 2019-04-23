/**
 * http://code.google.com/codejam/contest/6234486/dashboard#s=p2
 */

#include <string>
#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;
        string s;
        getline(cin, s);

        string a[N];
        for (int i = 0; i < N; ++i) getline(cin, a[i]);

        int count = 0;
        string maxa = a[0];
        for (int i = 1; i < N; ++i)
        {
            if (a[i] < maxa) ++count; else maxa = a[i];
        }

        cout << "Case #" << t << ": " << count << '\n';
    }

    return 0;
}
