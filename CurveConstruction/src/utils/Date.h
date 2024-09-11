#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>
#include <unordered_map>

#include "../data/Calendars.h"

class Date {
public:
    // Constructor
    Date(int day = 1, int month = 1, int year = 1900);
    Date(const std::string& dateString);

    // Operators for comparison
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator<=(const Date& other) const;

    // Arithmetic operator for date subtraction
    int operator-(const Date& other) const;

    // Function to manipulate Dates
    Date addDuration(int amount, char type) const;
    Date addDuration(const std::string& duration);
    Date businessDayAdjusted(const CalendarKey& calendar, const BusinessDayConv& business_day_conv);
    Date prevBusinessDay(const CalendarKey& calendar);
    Date nextBusinessDay(const CalendarKey& calendar);
    bool isHoliday(const CalendarKey& calendar_key);
    int  getWeekday() const;
    bool isWeekend();
    bool isBusinessDay(const CalendarKey& calendar_key) { return !(this->isHoliday(calendar_key) || this->isWeekend()); }

    // Helper functions
    void normalize();
    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);
    static int countFrequencyUnits(const Date& start, const Date& end, const std::string& frequency);
    static std::string normalizeDate(const std::string& date_str);
    static std::string dateToString(const int& day, const int& month, const int& year);

    // Member variables
    int yyyy, mm, dd;
    std::string date_str;

private:
    // Constants for days in each month (non-leap year)
    static const int daysInMonthNonLeap[12];
};

#endif // DATE_H