/**
 * Link: https://codility.com/programmers/lessons/6-sorting/max_product_of_three/
 */

#include <vector>

using namespace std;

int solution(vector<int>& a)
{
    int max1 = -1001;
    int max2 = -1001;
    int max3 = -1001;
    int min1 = 1001;
    int min2 = 1001;

    for (auto ai : a)
    {
        if (ai > max1) max3 = max2, max2 = max1, max1 = ai;
        else if (ai > max2) max3 = max2, max2 = ai;
        else if (ai > max3) max3 = ai;

        if (ai < min1) min2 = min1, min1 = ai;
        else if (ai < min2) min2 = ai;
    }

    return max(max1 * max2 * max3, min1 * min2 * max1);
}

int main()
{
    return 0;
}
