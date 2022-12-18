#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
using namespace std;

struct Date {
    int d, m, y;
};

class Calendar
{
private:
    const int monthDays[12]
        = { 31, 28, 31, 30, 31, 30,
           31, 31, 30, 31, 30, 31 };
    int countLeapYears(Date d);


public:
    Calendar();
    int getDifference(Date dt1, Date dt2);
};

#endif // CALENDAR_H
