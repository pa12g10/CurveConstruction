#ifndef DATE_UTILITIES_H
#define DATE_UTILITIES_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <regex>
#include "../data/Enums.h"
#include "../data/Calendars.h"

class DateUtilities {
public:
    static int addDuration(const int& date, const std::string& duration);
    static int addDurationBusinessDay(const int& date, const std::string& tenor, const CalendarKey& calendar_key,
        const BusinessDayConv& bdc);
    static int subtractDates(const int& later_data, const int& earlier_date);
    static std::string toString(const int& date);
    static bool isWeekend(const int& date);
    static bool isHoliday(const int& date, const CalendarKey& calendar_key);
    static bool isBusinessDay(const int& date, const CalendarKey& calendar_key);
    static int businessDayAdjusted(const int& date, const CalendarKey& calendar_key, const BusinessDayConv& business_day_conv);
    static int nextBusinessDay(const int& date, const CalendarKey& calendar_key);
    static int prevBusinessDay(const int& date, const CalendarKey& calendar_key);
    static int countFrequencyUnits(const int& start, const int& end, const std::string& frequency);
    static double yearFraction(int& curve_date, const int& date, const DayCountConv& dcc);



private:
    static int addDays(const int& date, int days);
    static int addMonths(const int& date, const int& months);
    static int addYears(const int& date, const int& years);
    static bool isValidDate(const int& date);
    static int daysInMonth(const int& year, const int& month);
    static bool isLeapYear(const int& year);
};

#endif DATE_UTILITIES_H
