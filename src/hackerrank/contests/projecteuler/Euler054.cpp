/**
 * Problem:
 *      Poker hands
 *
 * Links:
 *      https://projecteuler.net/problem=54
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler054
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct card
{
    int value;
    char suite;
};
using hand = vector<card>;

card get_card(const string& c)
{
    assert(c.size() == 2);

    if (c[0] >= '2' && c[0] <= '9') return {c[0] - '0', c[1]};
    else if (c[0] == 'T') return {10, c[1]};
    else if (c[0] == 'J') return {11, c[1]};
    else if (c[0] == 'Q') return {12, c[1]};
    else if (c[0] == 'K') return {13, c[1]};
    else if (c[0] == 'A') return {14, c[1]};

    assert(false);
    return {};
}

int count_value(const hand& h, int num, int& max_val)
{
    int count = 0;
    int value = 0;
    int len = 0;
    max_val = 0;

    for (auto c : h)
    {
        if (c.value != value)
        {
            if (len == num) ++count, max_val = max(max_val, value);
            value = c.value;
            len = 1;
        }
        else len++;
    }
    if (len == num) ++count, max_val = max(max_val, value);

    return count;
}

bool is_high_card(const hand& h, int& score)
{
    score = 0;
    for (int i = 4; i >= 0; --i) score = score * 10 + h[i].value;
    return true;
}

bool is_pair(const hand& h, int& score) // Two cards of the same value
{
    int pair_value;
    if (count_value(h, 2, pair_value) == 1)
    {
        score = pair_value;
        for (int i = 4; i >= 0; --i)
        {
            if (h[i].value != pair_value) score = score * 10 + h[i].value;
        }
        score += 1000000;
        return true;
    }
    return false;
}

bool is_two_pairs(const hand& h, int& score) // Two different pairs
{
    if (count_value(h, 2, score) == 2)
    {
        score = 2000000 + (h[3].value * 10 + h[1].value) * 10;
        if (h[0].value != h[1].value) score += h[0].value;
        else if (h[3].value != h[4].value) score += h[4].value;
        else score += h[2].value;
        return true;
    }
    return false;
}

bool is_three_of_kind(const hand& h, int& score) // Three cards of the same value
{
    if (count_value(h, 3, score) == 1)
    {
        score = 3000000 + h[2].value;
        return true;
    }
    return false;
}

bool is_straight(const hand& h, int& score) // All cards are consecutive values
{
    auto value = h[0].value;
    auto it = std::find_if(h.begin(), h.end(), [&value](card c) { return c.value != value++; });
    if (it == h.end())
    {
        score = 4000000 + h[4].value;
        return true;
    }
    else if (it == h.begin() + 4 && h[4].value == 14 && h[0].value == 2)
    {
        score = 4000000 + h[3].value;
        return true;
    }
    return false;
}

bool is_flush(const hand& h, int& score) // All cards of the same suit
{
    auto suite = h[0].suite;
    auto it = std::find_if(h.begin(), h.end(), [suite](card c) { return c.suite != suite; });
    if (it == h.end())
    {
        score = 0;
        for (int i = 4; i >= 0; --i) score = score * 10 + h[i].value;
        score += 5000000;
        return true;
    }
    return false;
}

bool is_full_house(const hand& h, int& score) // Three of a kind and a pair
{
    if (is_three_of_kind(h, score) && is_pair(h, score))
    {
        score = 6000000 + h[2].value;
        return true;
    }
    return false;
}

bool is_four_of_kind(const hand& h, int& score) // Four cards of the same value
{
    if (count_value(h, 4, score) == 1)
    {
        score = 7000000 + h[2].value;
        return true;
    }
    return false;
}

bool is_straight_flush(const hand& h, int& score) // All cards are consecutive values of same suit
{
    if (is_straight(h, score) && is_flush(h, score))
    {
        score = 8000000 + h[4].value;
        return true;
    }
    return false;
}

bool is_royal_flush(const hand& h, int& score) // Ten, Jack, Queen, King, Ace, in same suit
{
    if (h.at(0).value == 10 && is_straight_flush(h, score))
    {
        score = 9000000 + h[4].value;
        return true;
    }
    return false;
}

int get_score(const hand& h)
{
    int score = 0;
    if (is_royal_flush(h, score)) return score;
    else if (is_straight_flush(h, score)) return score;
    else if (is_four_of_kind(h, score)) return score;
    else if (is_full_house(h, score)) return score;
    else if (is_flush(h, score)) return score;
    else if (is_straight(h, score)) return score;
    else if (is_three_of_kind(h, score)) return score;
    else if (is_two_pairs(h, score)) return score;
    else if (is_pair(h, score)) return score;
    is_high_card(h, score);
    return score;
}

int get_winner(const hand& p1, const hand& p2)
{
    auto score1 = get_score(p1);
    auto score2 = get_score(p2);
    assert(score1 != score2);
    return score1 < score2 ? 2 : 1;
}

int main()
{
    int T;
    cin >> T;

    hand p1(5), p2(5);
    string s;
    while (T--)
    {
        for (auto& c : p1) cin >> s, c = get_card(s);
        for (auto& c : p2) cin >> s, c = get_card(s);

        sort(p1.begin(), p1.end(), [](card c1, card c2) { return c1.value < c2.value; });
        sort(p2.begin(), p2.end(), [](card c1, card c2) { return c1.value < c2.value; });

        cout << "Player " << get_winner(p1, p2) << '\n';
    }

    return 0;
}
