/**
 * https://www.hackerrank.com/contests/booking-hackathon/challenges/travel-profiles
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <map>
#include <algorithm>

using namespace std;

const size_t MAXF = 1000;
typedef bitset<MAXF> mask;

struct hotel
{
    int id;
    int price;
    mask facilities;

    hotel(): id(-1), price() {}
};

int main()
{
    int N;
    cin >> N;

    int bits = 1;
    hotel hotels[N];
    map<string, int> all_facilities;
    for (int i = 0; i < N; ++i)
    {
        cin >> hotels[i].id >> hotels[i].price;
        string facilities;
        getline(cin, facilities);
        stringstream ss(facilities);
        string facility;
        while (ss.good())
        {
            ss >> facility;
            int& bit = all_facilities[facility];
            if (!bit) bit = bits++;
            hotels[i].facilities[bit] = true;
        }
    }

    int M;
    cin >> M;

    vector<int> profile;
    while (M--)
    {
        int budget;
        mask requirements;
        cin >> budget;
        string facilities;
        getline(cin, facilities);
        stringstream ss(facilities);
        string facility;
        while (ss.good())
        {
            ss >> facility;
            int& bit = all_facilities[facility];
            if (!bit) bit = bits++;
            requirements[bit] = true;
        }

        profile.clear();
        for (int i = 0; i < N; ++i)
        {
            mask res = requirements & hotels[i].facilities;
            if (budget >= hotels[i].price && res == requirements)
            {
                profile.push_back(i);
            }
        }

        sort(begin(profile), end(profile),
             [&hotels](int lhv, int rhv)
             {
                 const hotel& l = hotels[lhv];
                 const hotel& r = hotels[rhv];
                 size_t lc = l.facilities.count();
                 size_t rc = r.facilities.count();
                 if (lc != rc) return lc > rc;
                 if (l.price != r.price) return l.price < r.price;
                 return l.id < r.id;
             });

        for (int i : profile)
        {
            cout << hotels[i].id << ' ';
        }
        cout << '\n';
    }

    return 0;
}
