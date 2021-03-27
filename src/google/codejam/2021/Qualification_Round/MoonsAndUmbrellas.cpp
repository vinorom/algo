/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1145
 */

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int get_cost(int X, int Y, char first, char last, size_t spaces)
{
  int cost = 0;
  if (first == last)
    cost += min<int>(0, (spaces + 1) / 2 * (X + Y));
  else
    cost += min<int>(0, spaces / 2 * (X + Y)) + (first == 'C' ? X : Y);
  return cost;
}

int calc_cost(int X, int Y, const string& s)
{
  int cost = 0;
  char lastCh = 0;
  size_t countSpaces = 0;
  for (size_t i = 0; i < s.length(); ++i)
  {
    assert(s[i] == 'C' || s[i] == 'J' || s[i] == '?');

    if (s[i] == '?')
    {
      ++countSpaces;
      continue;
    }

    if (lastCh == 0)
    {
      if (countSpaces > 0)
        cost += min(
                get_cost(X, Y, 'C', s[i], countSpaces - 1),
                get_cost(X, Y, 'J', s[i], countSpaces - 1));
    }
    else
    {
      cost += get_cost(X, Y, lastCh, s[i], countSpaces);
    }

    lastCh = s[i];
    countSpaces = 0;
  }

  if (countSpaces > 0)
  {
    if (lastCh != 0)
      cost += min(
              get_cost(X, Y, lastCh, 'C', countSpaces - 1),
              get_cost(X, Y, lastCh, 'J', countSpaces - 1));
    else if (countSpaces > 1)
      cost += min(
              min(
                      get_cost(X, Y, 'C', 'J', countSpaces - 2),
                      get_cost(X, Y, 'C', 'C', countSpaces - 2)),
              min(
                      get_cost(X, Y, 'J', 'C', countSpaces - 2),
                      get_cost(X, Y, 'J', 'J', countSpaces - 2)));
  }

  return cost;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int X, Y;
    string S;
    cin >> X >> Y >> S;

    cout << "Case #" << t << ": " << calc_cost(X, Y, S) << "\n";
  }

  return 0;
}
