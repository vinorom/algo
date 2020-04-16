/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020993c
 */

#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void solve(int N, const vector<vector<int>>& m, int& k, int& r, int& c)
{
  static constexpr int MAX_N = 101;
  assert(N < MAX_N);

  k = 0;
  for (int i = 0; i < N; ++i)
  {
    k += m[i][i];
  }

  r = 0;
  for (int i = 0; i < N; ++i)
  {
    bitset<MAX_N> mask;
    for (int j = 0; j < N; ++j)
    {
      if (mask.test(m[i][j]))
      {
        ++r;
        break;
      }
      else
      {
        mask.set(m[i][j]);
      }
    }
  }

  c = 0;
  for (int j = 0; j < N; ++j)
  {
    bitset<MAX_N> mask;
    for (int i = 0; i < N; ++i)
    {
      if (mask.test(m[i][j]))
      {
        ++c;
        break;
      }
      else
      {
        mask.set(m[i][j]);
      }
    }
  }
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N;
    cin >> N;

    vector<vector<int>> m(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < N; ++j)
      {
        cin >> m[i][j];
        //assert(m[i][j] > 0 && m[i][j] <= N);
      }
    }

    int k, r, c;
    solve(N, m, k, r, c);

    cout << "Case #" << t << ": " << k << ' ' << r << ' ' << c << "\n";
  }

  return 0;
}
