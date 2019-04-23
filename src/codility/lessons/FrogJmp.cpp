/**
 * Link: https://codility.com/programmers/lessons/3-time_complexity/frog_jmp/
 */

int solution(int x, int y, int d)
{
    int dist = y - x;
    int jumps = dist / d;
    if (dist % d != 0) ++jumps;
    return jumps;
}

int main()
{
    return 0;
}
