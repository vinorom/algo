/**
 * https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/0000000000088231
 */

#include <string>
#include <iostream>
#include <cassert>

using namespace std;

pair<int, int> solve(int N)
{
  int a = 0;
  int b = 0;
  int deg = 1;

  while (N)
  {
    int d = N % 10;
    N /= 10;

    if (d != 4)
    {
      a += deg * d;
    }
    else
    {
      a += deg * 3;
      b += deg * 1;
    }

    deg *= 10;
  }

  return {a, b};
}

pair<string, string> solve(const string& N)
{
  int len = (int)N.size();
  assert(len);

  string a(len, '0'), b(len, '0');

  for (int i = len - 1; i >= 0; --i)
  {
    auto d = N[i];

    if (d != '4')
    {
      a[i] = d;
    }
    else
    {
      a[i] = '3';
      b[i] = '1';
    }
  }

  b = b.substr(b.find_first_not_of("0"));

  return {a, b};
}

int main()
{
  int T;
  string s;
  cin >> T;
  getline(cin, s);

  for (int t = 1; t <= T; ++t)
  {
//    int N;
//    cin >> N;

    string N;
    getline(cin, N);

    auto res = solve(N);

    cout << "Case #" << t << ": " << res.first << " " << res.second << "\n";
  }

  return 0;
}
