/**
 * https://www.hackerrank.com/contests/codestorm/challenges/ilia
 */

#include <iostream>
#include <cmath>

typedef long long ll;

using namespace std;

int main()
{
    int N;
    cin >> N;

    int arr[N];
    for (int i = 0; i < N; ++i) cin >> arr[i];

    ll count_acute = 0;
    ll count_right = 0;
    ll count_obtuse = 0;
    for (int* a = arr; a < arr + N - 2; ++a)
    {
        for (int* b = a + 1; b < arr + N - 1; ++b)
        {
            int* r = lower_bound(b + 1, arr + N, *a + *b);

            int sumsq = *a * *a + *b * *b;
            int* c = lower_bound(b + 1, r, (int)sqrt(sumsq));

            count_acute += c - b - 1;
            if (c < r)
            {
                count_obtuse += r - c - 1;
                int sqc = *c * *c;
                if (sumsq == sqc)
                {
                    ++count_right;
                }
                else if (sumsq < sqc)
                {
                    ++count_obtuse;
                }
                else // sumsq > sqc
                {
                    ++count_acute;
                }
            }
        }
    }

    cout << count_acute << ' ' << count_right << ' ' << count_obtuse << endl;

    return 0;
}
