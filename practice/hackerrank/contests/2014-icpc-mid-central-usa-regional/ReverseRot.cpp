/**
 * https://www.hackerrank.com/contests/2014-icpc-mid-central-usa-regional-practice/challenges/reverse-rot
 */

#include <iostream>

using namespace std;

string ALPHA("ABCDEFGHIJKLMNOPQRSTUVWXYZ_.");

string encode(const string& msg, int N)
{
    static int ALPHA_SIZE = (int)ALPHA.size();

    int len = (int)msg.size();
    string out(msg);
    for (int i = 0; i < len; ++i)
    {
        char c = msg[len-1-i];
        int pos = c == '_' ? ALPHA_SIZE - 2 : (c == '.' ? ALPHA_SIZE - 1 : c - 'A');
        out[i] = ALPHA[(pos + N) % ALPHA_SIZE];
    }
    return out;
}

int main()
{
    int N;
    while ((cin >> N) && N)
    {
        string msg;
        cin >> msg;
        cout << encode(msg, N) << endl;
    }

    return 0;
}
