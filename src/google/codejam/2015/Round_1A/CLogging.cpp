/**
 * http://code.google.com/codejam/contest/4224486/dashboard#s=p2
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Point
{
    int x, y;

    Point(): x(0), y(0) {}
    Point(int _x, int _y): x(_x), y(_y) {}
};

#if 1 // optimized

const double PI = 2. * asin(1.);
const double EPS = 1e-7;

int main()
{
    int T;
    cin >> T;

    vector<double> angles;
    angles.reserve(3000);
    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;

        vector<Point> points(N);
        for (int i = 0; i < N; ++i) cin >> points[i].x >> points[i].y;

        cout << "Case #" << t << ":" << endl;

        for (int i = 0; i < N; ++i)
        {
            angles.clear();
            for (int j = 0; j < N; ++j)
            {
                if (i == j) continue;
                double atan = atan2(points[j].y - points[i].y, points[j].x - points[i].x);
                angles.push_back(atan);
                angles.push_back(atan + 2. * PI);
            }

            sort(angles.begin(), angles.end());

            int max_count = 0; // max number of points on one side and right on the line
            for (int start_idx = 0, end_idx = 0; end_idx < angles.size(); ++end_idx)
            {
                while (start_idx < angles.size() && angles[end_idx] - angles[start_idx] > PI + EPS) ++start_idx;
                max_count = max(max_count, end_idx - start_idx + 1);
                //cout << "start=" << angles[start_idx] << " end=" << angles[end_idx] << " count=" << max_count << endl;
            }

            int min_count = N - 1 - max_count; // min number of points that lie strictly on one side
            cout << min_count << endl;
        }
    }

    return 0;
}

#else // brute force

enum LineSide { ON_LINE, LEFT_UP, RIGHT_DOWN };

struct Line
{
    Point p1, p2;

    Line(Point _p1, Point _p2): p1(_p1), p2(_p2) {}

    LineSide where(Point p3)
    {
        if (p1.x == p2.x)
        {
            return (p3.x == p1.x) ? ON_LINE : (p3.x < p1.x ? LEFT_UP : RIGHT_DOWN);
        }

        if ((p3.x - p1.x) * (p3.y - p2.y) == (p3.x - p2.x) * (p3.y - p1.y)) return ON_LINE;

        double k = (double)(p2.y - p1.y) / (p2.x - p1.x);
        double y0 = p2.y - p2.x * k;
        double y3l = k * p3.x + y0;
        return y3l < p3.y ? LEFT_UP : RIGHT_DOWN;
    }
};

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int N;
        cin >> N;
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) cin >> points[i].x >> points[i].y;

        cout << "Case #" << t << ":" << endl;

        for (int i = 0; i < N; ++i)
        {
            if (N <= 3)
            {
                cout << 0 << endl;
                continue;
            }

            int count = N - 2;
            for (int j = 0; j < N; ++j)
            {
                if (i == j) continue;

                Line line(points[i], points[j]);
                int count_left_up = 0;
                int count_right_down = 0;
                for (int k = 0; k < N; ++k)
                {
                    if (k == i || k == j) continue;
                    LineSide side = line.where(points[k]);
                    switch (side)
                    {
                        case ON_LINE: break;
                        case LEFT_UP: ++count_left_up; break;
                        case RIGHT_DOWN: ++count_right_down; break;
                    }
                }

                count = min(count, min(count_left_up, count_right_down));
                if (count == 0) break;
            }
            cout << count << endl;
        }
    }

    return 0;
}

#endif
