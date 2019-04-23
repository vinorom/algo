/**
 * Problem:
 *      Cracking the Coding Interview: Sorting: Comparator
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-comparator-sorting
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Player
{
    string name;
    int score;
};

void sort_players(vector<Player>& players)
{
    auto cmp = [](const Player& l, const Player& r) { return l.score != r.score ? l.score > r.score : l.name < r.name; };
    sort(players.begin(), players.end(), cmp);
}

int main()
{
    int n;
    cin >> n;

    vector<Player> players(n);
    for (auto& p : players) cin >> p.name >> p.score;

    sort_players(players);

    for (auto p : players) cout << p.name << " " << p.score << '\n';

    return 0;
}

