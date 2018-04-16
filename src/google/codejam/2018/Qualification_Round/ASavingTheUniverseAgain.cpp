/**
 * https://codejam.withgoogle.com/2018/challenges
 */

#include <iostream>
#include <assert.h>

using namespace std;

int calc_damage(const string& program)
{
    int d = 0;
    int l = 1;
    for (auto c : program)
    {
        switch (c)
        {
            case 'C':
                l <<= 1;
                break;
            case 'S':
                d += l;
                break;
            default:
                assert(false);
                break;
        }
    }
    return d;
}

bool hack(string& program)
{
    auto pos = program.rfind('S');
    if (pos == string::npos) return false;
    pos = program.rfind('C', pos);
    if (pos == string::npos) return false;
    swap(program[pos], program[pos+1]);
    return true;
}

int solve(int damage, string program)
{
    int hacks = 0;
    while (calc_damage(program) > damage)
    {
        if (!hack(program)) return -1;
        ++hacks;
    }
    return hacks;
}

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int damage;
        string program;
        cin >> damage >> program;

        auto res = solve(damage, program);

        cout << "Case #" << t << ": ";
        if (res < 0) cout << "IMPOSSIBLE\n";
        else cout << res << '\n';
    }

    return 0;
}
