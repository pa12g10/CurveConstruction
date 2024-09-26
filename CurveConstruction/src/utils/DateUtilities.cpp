#include "DateUtilities.h"

int DateUtilities::addDuration(const int& date, const std::string& duration)
{
    if (!isValidDate(date)) {
        throw std::invalid_argument("Invalid date format. Use YYYYMMDD.");
    }

    std::regex duration_regex("([+-])?(\\d+)([DMYdmyBb])");
    std::smatch match;
    if (!std::regex_match(duration, match, duration_regex)) {
        throw std::invalid_argument("Invalid duration format. Use '[+-]nD', '[+-]nM', or '[+-]nY' where n is an integer.");
    }

    bool isAddition = match[1].str().empty() || match[1].str() == "+";
    int amount = std::stoi(match[2].str());
    char unit = match[3].str()[0];

    if (!isAddition) amount = -amount; // Convert to subtraction

    switch (unit) {
    case 'D': case 'd':case 'B':case 'b':
        return addDays(date, amount);
    case 'M':case 'm':
        return addMonths(date, amount);
    case 'Y':case 'y':
        return addYears(date, amount);
    default:
        throw std::invalid_argument("Invalid duration unit.");
    }
}

int DateUtilities::addDurationBusinessDay(const int& date, const std::string& tenor, const CalendarKey& calendar_key, const BusinessDayConv& bdc)
{
    int unadjusted_date = DateUtilities::addDuration(date, tenor);
    unadjusted_date = DateUtilities::businessDayAdjusted(unadjusted_date, calendar_key, bdc);
    return unadjusted_date;
}

int DateUtilities::subtractDates(const int& later_data, const int& earlier_date)
{
    if (!isValidDate(later_data) || !isValidDate(earlier_date)) {
        throw std::invalid_argument("Invalid date format. Use YYYYMMDD.");
    }

    // Ensure date1 is the later date
    if (later_data < earlier_date) {
        throw std::invalid_argument("Earlier date is later than the later date in subtractDates.");
    }

    int days = 0;
    int currentDate = earlier_date;

    while (currentDate < later_data) {
        currentDate = addDays(currentDate, 1);
        days++;
    }

    return days;
}

std::string DateUtilities::toString(const int& date)
{
    if (!isValidDate(date)) {
        throw std::invalid_argument("Invalid date format. Use YYYYMMDD.");
    }

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << (date / 10000) << "-"
        << std::setw(2) << ((date % 10000) / 100) << "-"
        << std::setw(2) << (date % 100);
    return oss.str();
}

bool DateUtilities::isWeekend(const int& date)
{
    int y = date / 10000;
    int m = (date % 10000) / 100;
    int d = date % 100;

    // Zeller's Congruence algorithm adjustment for January and February
    if (m < 3) {
        m += 12;
        y -= 1;
    }

    int K = y % 100;  // Year of the century
    int J = y / 100;  // Zero-based century (actually floor(y / 100))

    int f = d + ((13 * (m + 1)) / 5) + K + (K / 4) + (J / 4) + 5 * J;
    int weekday = f % 7;

    // Convert Zeller's output to match 0 = Sat, 1 = Sun, 2 = Monday, etc...
    return weekday == 0 || weekday == 1;
}

bool DateUtilities::isHoliday(const int& date, const CalendarKey& calendar_key)
{
    auto calendar = Calendar::get(calendar_key);
    return (calendar.find(date) != calendar.end()) ? true : false;
}

bool DateUtilities::isBusinessDay(const int& date, const CalendarKey& calendar_key)
{
     return !(DateUtilities::isHoliday(date, calendar_key) || DateUtilities::isWeekend(date)); 
}

int DateUtilities::prevBusinessDay(const int& date, const CalendarKey& calendar_key){
    int temp_day = date;
    while (!DateUtilities::isBusinessDay(temp_day, calendar_key))
    {
        temp_day = DateUtilities::addDuration(temp_day, "-1D");
    }
    return temp_day;
}

int DateUtilities::nextBusinessDay(const int& date, const CalendarKey& calendar_key){
    int temp_day = date;
    while (!DateUtilities::isBusinessDay(temp_day, calendar_key))
    {
        temp_day = DateUtilities::addDuration(temp_day, "1D");
    }
    return temp_day;
}

int DateUtilities::businessDayAdjusted(const int& date, const CalendarKey& calendar_key, const BusinessDayConv& business_day_conv) {
    int orig_month = (date % 10000) / 100;
    
    if (DateUtilities::isBusinessDay(date, calendar_key)) {
        return date;
    }

    switch (business_day_conv) {
        case BusinessDayConv::FOLLOWING:
            return DateUtilities::nextBusinessDay(date, calendar_key);

        case BusinessDayConv::PRECEDING:
            return DateUtilities::prevBusinessDay(date, calendar_key);

        case BusinessDayConv::MOD_FOLLOWING: {
            int next_bizz_day = DateUtilities::nextBusinessDay(date, calendar_key);
            int month = (next_bizz_day % 10000) / 100;
            if (month > orig_month) {
                return  DateUtilities::prevBusinessDay(date, calendar_key);
            }
            return next_bizz_day; 
        }

        case BusinessDayConv::MOD_PRECEDING: {
            int prev_bizz_day = DateUtilities::prevBusinessDay(date, calendar_key);
            int month = (prev_bizz_day % 10000) / 100;
            if (month < orig_month) {
                return DateUtilities::nextBusinessDay(date, calendar_key);
            }
            return prev_bizz_day; 
        }

        default:
            return date; 
        }
}

int DateUtilities::addDays(const int& date, int days)
{
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    while (days != 0) {
        if (days > 0) {
            day++;
            days--;
        }
        else {
            day--;
            days++;
        }
        if (day > daysInMonth(year, month)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        else if (day == 0) {
            month--;
            if (month == 0) {
                month = 12;
                year--;
            }
            day = daysInMonth(year, month);
        }
    }

    return year * 10000 + month * 100 + day;
}

int DateUtilities::addMonths(const int& date, const int& months)
{
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    // Calculate new year and month
    int totalMonths = year * 12 + month + months;
    year = totalMonths / 12;
    month = totalMonths % 12;
    if (month == 0) {
        month = 12;
        year--;
    }

    // Adjust day if it exceeds the days in the new month
    int newDay = day;
    int daysInNewMonth = daysInMonth(year, month);

    // Special handling for February 29 when subtracting to a non-leap year
    if (month == 2 && day == 29 && !isLeapYear(year)) {
        // If the target year is not a leap year, set the date to March 1
        month = 3;
        newDay = 1;
    }
    else if (day > daysInNewMonth) {
        newDay = daysInNewMonth;
    }

    return year * 10000 + month * 100 + newDay;
}

int DateUtilities::addYears(const int& date, const int& years)
{
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    year += years;

    // Adjust for leap years
    if (day == 29 && month == 2 && !isLeapYear(year)) {
        day = 28;
    }

    return year * 10000 + month * 100 + day;
}

bool DateUtilities::isValidDate(const int& date)
{
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;
    return (year > 0 && month > 0 && month <= 12 && day > 0 && day <= daysInMonth(year, month));
}

int DateUtilities::daysInMonth(const int& year, const int& month)
{
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

bool DateUtilities::isLeapYear(const int& year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateUtilities::countFrequencyUnits(const int& start, const int& end, const std::string& frequency) {
    // Ensure end is later than start
    if (end < start) {
        throw std::invalid_argument("End date must be later than start date");
    }

    // Parse frequency
    int amount = std::stoi(frequency.substr(0, frequency.length() - 1));
    char unit = std::tolower(frequency.back());

    if (unit == 'b' || unit == 'd' || unit == 'm' || unit == 'y') {
        int next_frequency = DateUtilities::addDuration(start, frequency);

        int units = 0;
        while (next_frequency <= end) {
            units++;
            next_frequency = DateUtilities::addDuration(next_frequency, frequency);
        }
        return units;
    }
    else {
        throw std::invalid_argument("Frequency should end with 'D' for days, 'M' for months, or 'Y' for years");
    }
}

double DateUtilities::yearFraction(int& curve_date, const int& date, const DayCountConv& dcc)
{
    double year_frac = 0.0;
    int days_between = DateUtilities::subtractDates(date, curve_date);
    switch (dcc)
    {
    case DayCountConv::ACT360:
        year_frac = days_between / 360.0;
        break;
    case DayCountConv::ACT365:
        year_frac = days_between / 365.0;
        break;
    default:
        break;
    }
    return year_frac;
}
