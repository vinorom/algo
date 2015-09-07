/**
 * https://www.hackerrank.com/contests/w17/challenges/count-fridays-the-13-th
 */

#include <iostream>

using namespace std;

const int DAYS_IN_MONTH[] = { 31, 28 /*29*/, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Date
{
    int year, month, day;

    Date(): year(1900), month(1), day(1) {}

    void next_month()
    {
        if (++month == 13)
        {
            month %= 12;
            ++year;
        }
    }

    int days_since_epoch() const
    {
        int years = year - 1900;
        int leap_years = 0;
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

        int days = years * (31 * 7 + 30 * 4 + 28) + leap_years;
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

int count_fridays_13th(Date from, Date to)
{
    int count = 0;

    // set <from> to the 13th day of the month
    if (from.day > 13) from.next_month();
    from.day = 13;

    int days_since_epoch_from = from.days_since_epoch();
    int days_since_epoch_to = to.days_since_epoch();

    while (days_since_epoch_from <= days_since_epoch_to)
    {
        if (days_since_epoch_from % 7 == 5) ++count; // friday 13th

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
        cin >> from.day >> from.month >> from.year >> to.day >> to.month >> to.year;
        cout << count_fridays_13th(from, to) << endl;
    }
    return 0;
}
