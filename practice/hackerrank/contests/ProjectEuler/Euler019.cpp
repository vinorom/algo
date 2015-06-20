/**
 * Problem:
 *       Counting Sundays
 *
 * Links:
 *      https://projecteuler.net/problem=19
 *      https://www.hackerrank.com/contests/projecteuler/challenges/euler019
 */

#include <iostream>

using namespace std;

typedef long long ll;

const int DAYS_IN_MONTH[] = { 31, 28 /*29*/, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Date
{
    ll year;
    int month, day;

    Date(): year(1900), month(1), day(1) {}

    void next_month()
    {
        if (++month == 13)
        {
            month %= 12;
            ++year;
        }
    }

    ll days_since_epoch() const
    {
        ll years = year - 1900;
        ll leap_years = 0;
        if (years > 0)
        {
            leap_years = (years - 1) / 4 + 1;
            leap_years -= (years - 1) / 100 + 1;
        }
        years = year - 2000;
        if (years > 0)
        {
            leap_years += (years - 1) / 400 + 1;
        }
        years = year - 1900;

        ll days = years * (31 * 7 + 30 * 4 + 28) + leap_years;
        for (int i = 0; i < month - 1; ++i) days += DAYS_IN_MONTH[i];
        if (month > 2 && is_leap_year()) ++days;
        days += day;

        return days;
    }

    bool is_leap_year() const
    {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }
};

ll count_1st_sundays(Date from, Date to)
{
    ll count = 0;
    ll days_since_epoch_from = from.days_since_epoch();
    ll days_since_epoch_to = to.days_since_epoch();

    if (from.day == 1 && days_since_epoch_from % 7 == 0) ++count; // first day of month is sunday

    // set <from> to the first day of next month
    from.day = 1;
    from.next_month();
    days_since_epoch_from = from.days_since_epoch();

    while (days_since_epoch_from <= days_since_epoch_to)
    {
        if (days_since_epoch_from % 7 == 0) ++count; // first day of month is sunday

        // shift <from> to the next month
        int days_in_month = DAYS_IN_MONTH[from.month - 1];
        if (from.month == 2 && from.is_leap_year()) ++days_in_month;
        days_since_epoch_from += days_in_month;
        from.next_month();
    }

    return count;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        Date from, to;
        cin >> from.year >> from.month >> from.day;
        cin >> to.year >> to.month >> to.day;
        cout << count_1st_sundays(from, to) << endl;
    }
    return 0;
}
