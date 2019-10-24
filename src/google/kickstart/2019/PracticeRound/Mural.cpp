/**
 * https://codingcompetitions.withgoogle.com/kickstart/round/0000000000051060/0000000000058b89
 */

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t)
  {
    int N;
    cin >> N;

    vector<int> score(N);
    for (int i = 0; i < N; ++i)
    {
      char c;
      cin >> c;
      score[i] = c - '0';
    }

    vector<int> prefix_sum(N+1, 0);
    for (int i = 1; i <= N; ++i)
    {
      prefix_sum[i] = prefix_sum[i-1] + score[i-1];
    }

    int p = (N + 1) / 2;
    int max_total_score = 0;
    for (int i = p; i <= N; ++i)
    {
      max_total_score = max(max_total_score, prefix_sum[i] - prefix_sum[i-p]);
    }

    cout << "Case #" << t << ": " << max_total_score << "\n";
  }

  return 0;
}
