/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020bdf9
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity
{
    int startTime;
    int endTime;
};

string solve(const vector<Activity>& activities)
{
  if (activities.empty()) return "";

  vector<int> indices(activities.size());
  for (int i = 0; i < activities.size(); ++i) indices[i] = i;
  sort(indices.begin(), indices.end(), [&](int& lhv, int& rhv) { return activities[lhv].startTime < activities[rhv].startTime; });

  string assignment(activities.size(), '?');

  Activity cameron{-1, -1};
  Activity jamie{-1, -1};
  for (int idx : indices)
  {
    const Activity& a = activities[idx];
    if (cameron.endTime <= a.startTime)
    {
      assignment[idx] = 'C';
      cameron = a;
    }
    else if (jamie.endTime <= a.startTime)
    {
      assignment[idx] = 'J';
      jamie = a;
    }
    else
    {
      return "IMPOSSIBLE";
    }
  }

  return assignment;
}

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N;
    cin >> N;

    vector<Activity> activities(N);
    for (int i = 0; i < N; ++i)
    {
      cin >> activities[i].startTime >> activities[i].endTime;
      assert(activities[i].startTime < activities[i].endTime);
    }

    cout << "Case #" << t << ": " << solve(activities) << "\n";
  }

  return 0;
}
