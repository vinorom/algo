/**
 * http://code.google.com/codejam/contest/4224486/dashboard#s=p1
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
        int B, N;
        cin >> B >> N;

        vector<int> times(B, 0);
        for (int i = 0; i < B; ++i) cin >> times[i];

        // find exact minute when N-th client will be served
        int64_t low = -1;
        int64_t high = (int64_t)100000 * N;
        while (low + 1 < high)
        {
            //cout << "low=" << low << " high=" << high << endl;

            int64_t mid = (low + high) / 2;
            int64_t clients = 0;
            if (mid >= 0)
            {
                for (int i = 0; i < B; ++i) clients += mid / times[i] + 1;
            }

            if (clients < N)
            {
                low = mid;
            }
            else
            {
                high = mid;
            }
        }

        int64_t tm = high;
        int64_t clients_so_far = 0; // number of clients served up to including T-1 minute
        if (tm > 0)
        {
            for (int i = 0; i < B; ++i) clients_so_far += (tm - 1) / times[i] + 1;
        }
        //cout << "tm=" << tm << " clients_so_far=" << clients_so_far << endl;

        int64_t clients_to_serve = (int64_t)N - clients_so_far;
        int res_idx = -1;
        for (int i = 0; i < B; ++i)
        {
            if (tm % times[i] == 0)
            {
                if (--clients_to_serve == 0)
                {
                    res_idx = i;
                    break;
                }
            }
        }

        cout << "Case #" << t << ": " << (res_idx + 1) << endl;
    }

    return 0;
}
