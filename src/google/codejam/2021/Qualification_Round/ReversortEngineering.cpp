/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d12d7
 */

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

bool find_solution(int N, int C, vector<int>& arr)
{
  if (C < N - 1 || C > (N + 2) * (N - 1) / 2)
    return false;

  arr.resize(N);
  for (int i = 0; i < N; ++i)
    arr[i] = i + 1;

  for (int i = N - 2; i >= 0; --i)
  {
    int len = max(1, min(C - i, N - i));
    assert(len <= C);
    C -= len;
    for (int j = 0; j < len / 2; ++j)
      swap(arr[i + j], arr[i + len - j - 1]);
  }
  assert(C == 0);

  return true;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N, C;
    cin >> N >> C;

    cout << "Case #" << t << ":";

    vector<int> arr;
    if (find_solution(N, C, arr))
    {
      for (int a : arr) cout << " " << a;
      cout << "\n";
    }
    else
    {
      cout << " IMPOSSIBLE\n";
    }
  }

  return 0;
}
