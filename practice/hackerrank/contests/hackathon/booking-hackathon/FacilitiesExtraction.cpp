/**
 * https://www.hackerrank.com/contests/booking-hackathon/challenges/facilities-extraction
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin >> N;

    string s;
    vector<string> facilities;
    while (N)
    {
        getline(cin, s);
        if (!s.empty())
        {
            facilities.push_back(s);
            --N;
        }
    }

    sort(begin(facilities), end(facilities));

    stringstream ss;
    while (!cin.eof())
    {
        getline(cin, s);
        ss << s;
    }

    s.assign(ss.str());
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    for (string f : facilities)
    {
        string fu(f);
        transform(fu.begin(), fu.end(), fu.begin(), ::toupper);
        if (s.find(fu) != string::npos) cout << f << endl;
    }

    return 0;
}
