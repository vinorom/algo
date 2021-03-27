/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1155
 */

#include <cassert>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const size_t N = 100;
const size_t M = 10000;

double sigm(double x)
{
  return 1.0 / (1 + exp(-x));
}

size_t detect_cheater(const vector<string>& a)
{
  vector<double> Q(M);
  for (size_t j = 0; j < M; ++j)
  {
    size_t count = 0;
    for (size_t i = 0; i < N; ++i)
      count += a[i][j] == '1' ? 1 : 0;
    Q[j] = 3.0 - 6.0 * count / N;
  }

  vector<double> S(N);
  for (size_t i = 0; i < N; ++i)
  {
    size_t count = 0;
    for (size_t j = 0; j < M; ++j)
      count += a[i][j] == '1' ? 1 : 0;
    S[i] = 6.0 * count / M - 3.0;
  }

  size_t idx = 0;
  double maxp = 0.0;
  for (size_t i = 0; i < N; ++i)
  {
    double sump = 0;
    for (size_t j = 0; j < M; ++j)
      sump += sigm(S[i]- Q[j]);
    double avgp = sump / M;

    if (avgp > maxp)
    {
      maxp = avgp;
      idx = i;
    }
  }

  return idx + 1;
}

int main()
{
  int T;
  double P;
  cin >> T >> P;

  vector<string> a(N);
  for (int t = 1; t <= T; ++t)
  {
    for (size_t i = 0; i < N; ++i)
    {
      cin >> a[i];
      assert(a[i].length() == M);
    }

    size_t cheater = detect_cheater(a);

    cout << "Case #" << t << ": " << cheater << "\n";
  }

  return 0;
}
