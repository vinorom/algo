/**
 * https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/00000000000881da
 */

#include <string>
#include <iostream>
#include <cassert>

using namespace std;

string solve(const string& path)
{
  auto res = path;
  for (auto& c : res)
  {
    c = c == 'E' ? 'S' : 'E';
  }
  return res;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N;
    string path;

    cin >> N;
    getline(cin, path);
    getline(cin, path);
    assert(path.size() == 2 * N - 2);

    cout << "Case #" << t << ": " << solve(path) << "\n";
  }

  return 0;
}
