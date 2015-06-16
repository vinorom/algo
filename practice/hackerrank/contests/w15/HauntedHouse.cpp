/**
 * https://www.hackerrank.com/contests/w15/challenges/haunted-house
 */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int /*min*/, int /*max*/> Person;
typedef vector<Person> Persons;

bool operator<(Person lhv, Person rhv) { return lhv.first < rhv.first; }

int solve(Persons& persons)
{
    sort(persons.begin(), persons.end());
    int max_right = 0;
    for (int p = 0; p < persons.size(); ++p) max_right = max(max_right, persons[p].second);

    vector<int> sat(max_right + 1, 0); // intersections, i.e. number of satisfied constraints
    for (int s = 1, p = 0; s <= sat.size(); ++s)
    {
        sat[s] += sat[s - 1];
        for (; p < persons.size() && persons[p].first == s; ++p)
        {
            ++sat[s];
            --sat[persons[p].second + 1];
        }
    }

    //for (int i = 0; i < sat.size(); ++i) cout << " " << sat[i];
    //cout << endl;

    // find max that doesn't violate constraints
    for (int s = sat.size()-1; s >= 1; --s)
    {
        if (s <= sat[s]) return s;
    }
    return 0;
}

int main()
{
    int N;
    cin >> N;
    Persons persons(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> persons[i].first >> persons[i].second;
        persons[i].first++;
        persons[i].second++;
    }

    int max = solve(persons);
    cout << max << endl;
    return 0;
}
