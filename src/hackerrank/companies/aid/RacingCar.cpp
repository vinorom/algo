/**
 * Problem:
 *      Racing Car
 *
 * Links:
 *      TBD
 */

#include <iostream>
#include <vector>

int minimumMovement(std::vector<int> obstacleLanes)
{
  int init_lane = 2; // initial lane where the car is located

  // detect number of lanes automatically
  int num_lanes = init_lane;
  for (auto obstacle_lane : obstacleLanes)
  {
    assert(obstacle_lane > 0);
    num_lanes = std::max(num_lanes, obstacle_lane);
  }

  // DP algorithm: find min number of moves to reach every lane at step i if the problem is solved for step (i-1)
  // complexity: time = O(N * L^2); space = O(L)
  // where N - number of steps, L - number of lanes
  // -1 means the lane is unreachable
  // since we don't have to reconstruct the path of the car the back tracking information (array of size N)
  // is not needed and we use only two arrays (for previous step and current step)

  int prev_step_idx = 0;
  std::vector<int> min_num_moves[2];
  min_num_moves[0].assign(num_lanes, -1); // all lanes are unreachable before the start
  min_num_moves[0][init_lane - 1] = 0; // except for the initial position - 0 moves to reach that lane
  min_num_moves[1].resize(num_lanes);

  // find min number of moves to reach given lane from previous step
  auto get_min_num_moves_from_prev_step = [&num_lanes](const std::vector<int>& prev_min_num_moves, bool finish, int curr_lane)
  {
    int min_num_moves = -1; // curr_lane is unreachable by default
    for (int prev_lane = 1; prev_lane <= num_lanes; ++prev_lane)
    {
      if (prev_min_num_moves[prev_lane - 1] != -1)
      {
        int num_moves = prev_min_num_moves[prev_lane - 1] + (finish || curr_lane == prev_lane ? 0 : 1);
        if (min_num_moves == -1 || num_moves < min_num_moves)
        {
          min_num_moves = num_moves;
        }
      }
    }
    assert(min_num_moves != -1); // otherwise it would mean at prev step there is obstacle on each lane (should not be)
    return min_num_moves;
  };

  for (auto step = 0; step < obstacleLanes.size(); ++step)
  {
    int obstacle_lane = obstacleLanes[step];
    int curr_step_idx = (prev_step_idx + 1) % 2;

    for (int curr_lane = 1; curr_lane <= num_lanes; ++curr_lane)
    {
      if (obstacle_lane == curr_lane)
      {
        // obstacle => curr_lane is unreachable
        min_num_moves[curr_step_idx][curr_lane - 1] = -1;
      }
      else
      {
        // not obstacle => calculate result for current step using the solution for previous step (sub-problem)
        min_num_moves[curr_step_idx][curr_lane - 1] = get_min_num_moves_from_prev_step(min_num_moves[prev_step_idx], false, curr_lane);
      }
    }

    prev_step_idx = curr_step_idx;
  }

  // get min number of moves from the last step to finish
  return get_min_num_moves_from_prev_step(min_num_moves[prev_step_idx], true, 0 /*unused*/);
}

int main()
{
  int N;
  std::cin >> N;

  std::vector<int> obstacles(N);
  for (int i = 0; i < N; ++i) std::cin >> obstacles[i];

  std::cout << minimumMovement(obstacles) << std::endl;

  return 0;
}
