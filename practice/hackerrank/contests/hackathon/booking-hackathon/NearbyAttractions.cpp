/**
 * https://www.hackerrank.com/contests/booking-hackathon/challenges/nearby-attractions
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <math.h>

using namespace std;

enum transport { METRO = 0, BIKE, FOOT, UNKNOWN };
const int speeds[] = { 20, 15, 5 }; // km/h

template <typename T>
struct point
{
    T latitude;
    T longitude;
    point(T lat_ = T(), T long_ = T()): latitude(lat_), longitude(long_) {}
};
typedef point<double> dpoint;

template <typename T>
istream& operator>>(istream& istr, point<T>& p)
{
    istr >> p.latitude >> p.longitude;
    return istr;
}

double degree2radians(double deg)
{
    return deg * M_PI / 180;
}

dpoint degree2radians(dpoint pdeg)
{
    return dpoint(degree2radians(pdeg.latitude), degree2radians(pdeg.longitude));
}

double distance(dpoint p1deg, dpoint p2deg)
{
    static const int EARTH_RADIUS = 6371; //in km
    dpoint p1rad = degree2radians(p1deg);
    dpoint p2rad = degree2radians(p2deg);
    return acos(sin(p1rad.latitude) * sin(p2rad.latitude) +
                cos(p1rad.latitude) * cos(p2rad.latitude) * cos(p2rad.longitude - p1rad.longitude))
           * EARTH_RADIUS;
}

struct attraction
{
    int id;
    dpoint pdeg;
    attraction(): id(-1) {}
};

int main()
{
    int N;
    cin >> N;

    deque<attraction> attractions(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> attractions[i].id >> attractions[i].pdeg;
    }

    int M;
    cin >> M;

    deque<pair<double /*distance*/, int /*id*/>> nearby;
    while (M--)
    {
        dpoint hotel;
        string tports;
        double max_tm;

        cin >> hotel >> tports >> max_tm;

        transport tport = UNKNOWN;
        if (tports == "metro") tport = METRO;
        else if (tports == "bike") tport = BIKE;
        else if (tports == "foot") tport = FOOT;
        else continue;

        double speed = speeds[tport]; // km/h
        speed /= 60; // km/min

        nearby.clear();
        for (int i = 0; i < N; ++i)
        {
            double dist = distance(hotel, attractions[i].pdeg);
            dist = int(dist * 100 + 0.5) / 100.0;
            if (dist / speed <= max_tm)
            {
                nearby.push_back(make_pair(dist, attractions[i].id));
            }
        }
        sort(begin(nearby), end(nearby));
        for (auto n : nearby)
        {
            cout << n.second << ' ';
        }
        cout << '\n';
    }

    return 0;
}
