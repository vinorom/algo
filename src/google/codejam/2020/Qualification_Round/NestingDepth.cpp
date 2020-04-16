/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9f
 */

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string solve(const string& s)
{
  stringstream res;
  int curr_depth = 0;
  for (char c : s)
  {
    assert(c >= '0' && c <= '9');
    int depth = c - '0';
    if (curr_depth > depth)
    {
      res << string(curr_depth - depth, ')');
    }
    if (curr_depth < depth)
    {
      res << string(depth - curr_depth, '(');
    }
    res << c;
    curr_depth = depth;
  }

  if (curr_depth > 0)
  {
    res << string(curr_depth, ')');
  }

  return res.str();
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    string s;
    cin >> s;

    cout << "Case #" << t << ": " << solve(s) << "\n";
  }

  return 0;
}
