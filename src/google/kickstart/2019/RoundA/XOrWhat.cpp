/**
 * https://codingcompetitions.withgoogle.com/kickstart/round/0000000000051061/0000000000161426
 */

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

int count1(int a)
{
  int count = 0;
  while (a)
  {
    a &= a - 1;
    ++count;
  }
  return count;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N, Q;
    cin >> N >> Q;

    vector<int> xor_adj(N); // whether A[i] changes the (xor-sum % 2) or not
    list<int> ones; // indices of 1s
    int xor_even = 0; // xor-sum % 2: 0 - even, 1 - odd

    int a;
    for (int i = 0; i < N; ++i)
    {
      cin >> a;

      xor_adj[i] = count1(a) % 2;
      xor_even += xor_adj[i];
      xor_even %= 2;

      if (xor_adj[i] == 1) ones.push_back(i);
    }

    auto update = [&](int p, int v)
    {
      int xor_adj_p = count1(v) % 2;
      if (xor_adj_p == xor_adj[p]) return;

      xor_adj[p] = xor_adj_p;
      ++xor_even;
      xor_even %= 2;

      auto it = ones.begin();
      for (; it != ones.end() && *it < p; ++it);

      if (xor_adj_p == 0)
      {
        assert(it != ones.end() && *it == p);
        ones.erase(it);
      }
      else
      {
        ones.insert(it, p);
      }
    };

    auto find_max_xor_even_int = [&]() -> pair<int, int>
    {
      if (xor_even == 0) return {0, N};
      if (ones.empty()) return {0, 0};

      int A = 0;
      int B = 0;
      if (N - ones.front() - 1 > B - A)
      {
        A = ones.front() + 1;
        B = N;
      }
      if (ones.back() > B - A)
      {
        A = 0;
        B = ones.back();
      }

      return {A, B};
    };

    auto dist = [](const pair<int, int>& p) { return p.second - p.first; };

    cout << "Case #" << t << ":";

    int p, v;
    for (int i = 0; i < Q; ++i)
    {
      cin >> p >> v;

      update(p, v);

      cout << ' ' << dist(find_max_xor_even_int());
    }

    cout << "\n";
  }

  return 0;
}
