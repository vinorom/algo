/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d0a5c
 */

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

size_t calc_reverse_cost(vector<size_t>& L)
{
  const size_t N = L.size();
  vector<size_t> pos(N + 1);
  for (size_t i = 0; i < N; ++i)
  {
    assert(L[i] >= 1 && L[i] <= N);
    pos[L[i]] = i + 1;
  }

  size_t cost = 0;
  for (size_t i = 1; i < N; ++i)
  {
    size_t pos_min = pos[i];
    assert(pos[i] >= i);
    cost += pos_min - i + 1;
    for (size_t j = 0; j <= (pos_min - i) / 2; ++j)
    {
      swap(pos[L[i + j - 1]], pos[L[pos_min - j - 1]]);
      swap(L[i + j - 1], L[pos_min - j - 1]);
    }
  }
  return cost;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N;
    cin >> N;

    vector<size_t> L(N);
    for (int i = 0; i < N; ++i)
      cin >> L[i];

    size_t cost = calc_reverse_cost(L);
    cout << "Case #" << t << ": " << cost << "\n";
  }

  return 0;
}
