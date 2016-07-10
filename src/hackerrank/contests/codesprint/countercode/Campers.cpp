/**
 * https://www.hackerrank.com/contests/countercode/challenges/campers
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    int snipers[K];
    for (int i = 0; i < K; ++i)
    {
        cin >> snipers[i];
    }
    std::sort(snipers, snipers + K);

    int count = 0;
    for (int sniper = -1, i = 0; i < K; sniper = snipers[i++])
    {
        count += (snipers[i] - sniper - 2) / 2 + 1;
    }
    count += (N - snipers[K-1]) / 2;

    cout << count << endl;

    return 0;
}
