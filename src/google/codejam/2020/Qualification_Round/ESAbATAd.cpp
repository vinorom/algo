/**
 * https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9e
 */

#include <cassert>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

void reverse(string& s)
{
  for (size_t i = 0; i < s.size() / 2; ++i)
  {
    swap(s[i], s[s.size() - 1 - i]);
  }
}

void complement(string& s)
{
  for (char& c : s)
  {
    switch (c)
    {
      case '0': c = '1'; break;
      case '1': c = '0'; break;
      default: break;
    }
  }
}

string ask(const string& query)
{
  string reply;
  cout << query << endl;
  cin >> reply;
  if (reply == "N")
  {
    throw runtime_error("Unexpected reply");
  }
  return reply;
}

bool solve(int B)
{
  string answer;
  string a(B, '?');
  int step = 1;
  int curr_bit = 0;
  int sim_bit = -1;
  int asim_bit = -1;

  auto is_flipped = [&](int bit)
  {
    ++step;
    if (bit == -1)
    {
      ask(to_string(1)); // unknown bit => just query something
      return false;
    }
    else
    {
      answer = ask(to_string(bit + 1));
      assert(answer.size() == 1);
      return answer[0] != a[bit];
    }
  };

  auto get_bit = [&](int bit)
  {
    ++step;
    answer = ask(to_string(bit + 1));
    assert(answer.size() == 1);
    return answer[0];
  };

  while (step <= 150 && curr_bit <= B / 2)
  {
    if (step % 10 == 1)
    {
      // quantum fluctuation
      bool is_sim_bit_flipped = is_flipped(sim_bit);
      bool is_asim_bit_flipped = is_flipped(asim_bit);
      if (is_sim_bit_flipped && is_asim_bit_flipped)
      {
        complement(a);
      }
      else if (is_sim_bit_flipped)
      {
        reverse(a);
        complement(a);
      }
      else if (is_asim_bit_flipped)
      {
        reverse(a);
      }
    }
    else
    {
      a[curr_bit] = get_bit(curr_bit);
      a[B - 1 - curr_bit] = get_bit(B - 1 - curr_bit);

      if (a[curr_bit] == a[B - 1 - curr_bit])
      {
        sim_bit = curr_bit;
      }
      else
      {
        asim_bit = curr_bit;
      }
      ++curr_bit;
    }
  }

  answer = ask(a);
  return answer == "Y";
}

int main()
{
  int T;
  int B;
  cin >> T >> B;

  try
  {
    for (int t = 1; t <= T; ++t)
    {
      solve(B);
    }
  }
  catch (const runtime_error& e)
  {
    cerr << "FAILED" << endl;
  }

  return 0;
}
