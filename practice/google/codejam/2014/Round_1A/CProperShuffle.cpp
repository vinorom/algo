/**
 * Problem: http://code.google.com/codejam/contest/2984486/dashboard#s=p2
 */

#include <iostream>
#include <vector>

using namespace std;

struct Permutation
{
    vector<int> perm;

    Permutation(int n) : perm(n)
    {
        srand(time(0));
    }

    int measure_less(void(Permutation::*gen)())
    {
        const int iterations = 10000;
        int count = 0;
        for (int i = 0; i < iterations; ++i)
        {
            (this->*gen)();
            count += count_less();
        }
        return count / iterations;
    }

    void good()
    {
        clear();
        for (int i = 0; i < perm.size(); ++i)
        {
            int r = i + rand() % (perm.size() - i);
            swap(perm[i], perm[r]);
        }
    }

    void bad()
    {
        clear();
        for (int i = 0; i < perm.size(); ++i)
        {
            int r = rand() % perm.size();
            swap(perm[i], perm[r]);
        }
    }

    void clear()
    {
        for (int i = 0; i < perm.size(); ++i) perm[i] = i;
    }

    int count_less()
    {
        int count = 0;
        for (int i = 0; i < perm.size(); ++i)
        {
            if (perm[i] <= i) count++;
        }
        return count;
    }

};

int main()
{
    //Permutation perm(1000);
    //cout << "Good: " << perm.measure_less(&Permutation::good) << endl; // 500
    //cout << "Bad:  " << perm.measure_less(&Permutation::bad) << endl; // 472
    //return 0;

    double good_ratio = 500. / 1000;
    double bad_ratio = 472. / 1000;
    double check_ratio = (good_ratio + bad_ratio) / 2;

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        int count = 0;
        for (int i = 0; i < N; ++i)
        {
            int a;
            cin >> a;

            if (a <= i) count++;
        }

        double ratio = (double)count / N;

        cout << "Case #" << t << ": " << (ratio < check_ratio ? "BAD" : "GOOD") << endl;
    }

    return 0;
}
