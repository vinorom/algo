/**
 * Problem:
 *      XOR decryption
 *
 * Links:
 *      https://projecteuler.net/problem=59
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler059
 */

#include <iostream>
#include <vector>

using namespace std;

bool is_allowed_char(int code)
{
    static string common("()[]{}<>;:,.'\"?-! \t\n\r");
    if (code <= 0 || code > 127) return false;
    char ch(code);
    return ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') ||
            common.find_first_of(ch) != string::npos);
}

string solve(const vector<int>& msg, int key_size)
{
    string key;
    while (key.size() < key_size)
    {
        for (char key_ch = 'a'; key_ch <= 'z'; ++key_ch)
        {
            int i;
            for (i = (int)key.size(); i < msg.size(); i += key_size)
            {
                int decoded = msg[i] ^ (int)key_ch;
                if (!is_allowed_char(decoded)) break;
            }
            if (i >= msg.size())
            {
                key += key_ch;
                break;
            }
        }
    }
    return key;
}

int find_ascii_sum(const vector<int>& msg, const string& key)
{
    int sum = 0;
    for (int i = 0; i < msg.size(); ++i)
    {
        sum += msg[i] ^ int(key[i % key.size()]);
    }
    return sum;
}

//#define ORIGINAL_EULER_PROBLEM

int main()
{
    int N;
    cin >> N;
    vector<int> msg(N);
    for (int i = 0; i < N; ++i) cin >> msg[i];

    string key = solve(msg, 3);
#ifdef ORIGINAL_EULER_PROBLEM
    cout << find_ascii_sum(msg, key) << endl;
#else
    cout << key << endl;
#endif

    return 0;
}
