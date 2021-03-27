/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1284
 */

#include <cassert>
#include <iostream>
#include <deque>

using namespace std;

// -1 - before left, +1 - after right, 0 - in between left and right
int query(int& Q, int l, int r, int a)
{
  if (--Q < 0)
  {
    cerr << "max queries exceeded" << endl;
    //return -200;
  }

  cout << l << ' ' << r << ' ' << a << endl;
  int answer;
  cin >> answer;
  if (answer == -1)
    return -100;
  assert(answer == l || answer == r || answer == a);

  if (answer == l)
    return -1;
  else if (answer == r)
    return 1;
  return 0;
}

bool insert(deque<int>& arr, int& Q, int a)
{
  int l = 0;
  int r = static_cast<int>(arr.size()) - 1;
  int where = 0;
  while (l < r)
  {
    int mid = (l + r) / 2;
    where = query(Q, arr[mid], arr[r], a);
    if (where < -1)
      return false;
    else if (where == -1) // search in left half
    {
      r = mid;
      if (l + 1 < r)
        --r;
    }
    else if (where == 1) // value is just after right
      break; // l = r;
    else if (l == mid) // nothing to search any more
      break;
    else // search in right half
    {
      l = mid;
      if (l + 1 < r)
        ++l;
      if (l + 1 < r)
        --r;
    }
  }

  if (where == -1)
    arr.insert(arr.begin() + l, a);
  else if (where == 1)
    arr.insert(arr.begin() + r + 1, a);
  else
    arr.insert(arr.begin() + r, a);

#if 0
  cerr << "curr:";
  for (int a : arr) cerr << ' ' << a;
  cerr << endl;
#endif

  return true;
}

bool solve(int N, int& Q)
{
  assert(N > 3);

  deque<int> arr;
  arr.push_back(1);
  arr.push_back(2);

  for (int a = 3; a <= N; ++a)
  {
    if (!insert(arr, Q, a))
      return false;
  }

  // found
  for (size_t i = 0; i < arr.size(); ++i)
    cout << (i > 0 ? " " : "") << arr[i];
  cout << endl;

  int answer;
  cin >> answer;
  return answer == 1;
}

int main()
{
  int T, N, Q;
  cin >> T >> N >> Q;

  for (int t = 1; t <= T; ++t)
  {
    if (!solve(N, Q))
      return 1;
  }

  return 0;
}
