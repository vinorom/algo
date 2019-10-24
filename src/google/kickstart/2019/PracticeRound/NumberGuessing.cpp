/**
 * https://codingcompetitions.withgoogle.com/kickstart/round/0000000000051060/00000000000588f4
 */

#include <iostream>

using namespace std;

bool solve(int a, int b, int n)
{
  string answer;
  for (int i = 0; i < n; ++i)
  {
    int m = b - (b - a) / 2;
    cout << m << endl;
    cin >> answer;

    if (answer == "WRONG_ANSWER") return false;
    else if (answer == "CORRECT") return true;
    else if (answer == "TOO_SMALL")
    {
      a = m;
    }
    else if (answer == "TOO_BIG")
    {
      b = m - 1;
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int a, b, n;
    cin >> a >> b >> n;
    solve(a, b, n);
  }

  return 0;
}
