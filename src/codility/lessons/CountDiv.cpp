/**
 * Link: https://codility.com/programmers/lessons/5-prefix_sums/count_div/
 */

using namespace std;

int solution(int A, int B, int K)
{
    int base = A % K == 0 ? A : (A / K + 1) * K;
    if (B < base) return 0;
    return (B - base) / K + 1;
}

int main()
{
    return 0;
}
