/**
 * Problem:
 *      Roman numerals
 *
 * Links:
 *      https://projecteuler.net/problem=89
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler089
 */

#include <bits/stdc++.h>

using namespace std;

void read_roman_number_part(const char*& str, int& n, int u10, char c10, char c5, char c1)
{
    int u1 = u10 / 10;
    int u5 = u10 / 2;

    while (str[0] == c10) n += u10, ++str;
    if (str[0] == c1 && str[1] == c5) n += u5 - u1, str += 2;
    if (str[0] == c1 && str[1] == c10) n += u10 - u1, str += 2;
    while (str[0] == c5) n += u5, ++str;
}

int read_roman_number(const char* str)
{
    int n = 0;
    const char* s = str;
    read_roman_number_part(s, n, 1000, 'M', 'D', 'C');
    read_roman_number_part(s, n, 100, 'C', 'L', 'X');
    read_roman_number_part(s, n, 10, 'X', 'V', 'I');
    read_roman_number_part(s, n, 1, 'I', '?', '?');
    return n;
}

string get_roman_number_part(int& n, int u10, char c10, char c5, char c1)
{
    int u1 = u10 / 10;
    int u5 = u10 / 2;

    stringstream ss;
    ss << string(n / u10, c10);
    n %= u10;

    if (n >= u10 - u1)
    {
        ss << c1 << c10;
        n -= u10 - u1;
    }
    else if (n >= u10 - u5)
    {
        ss << c5;
        n -= u10 - u5;
    }
    else if (n >= u5 - u1)
    {
        ss << c1 << c5;
        n -= u5 - u1;
    }

    return ss.str();
}

string get_roman_number(int n)
{
    stringstream ss;
    ss << get_roman_number_part(n, 1000, 'M', 'D', 'C');
    ss << get_roman_number_part(n, 100, 'C', 'L', 'X');
    ss << get_roman_number_part(n, 10, 'X', 'V', 'I');
    ss << string(n, 'I');
    return ss.str();
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string n;
        cin >> n;
        cout << get_roman_number(read_roman_number(n.c_str())) << '\n';
    }

    return 0;
}
