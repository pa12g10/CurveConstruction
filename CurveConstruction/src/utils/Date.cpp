#include "Date.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <vector>

Date::Date(const std::string& dateString) {
    date_str = Date::normalizeDate(dateString);
    std::istringstream iss(dateString);
    std::vector<int> dateParts;
    char separator;


    int part;
    while (iss >> part) {
        dateParts.push_back(part);
        if (iss.peek() == '-' || iss.peek() == '/') {
            separator = iss.get(); 
        }
    }

    if (dateParts.size() != 3) {
        throw std::invalid_argument("Invalid date format. Expected YYYY-MM-DD or DD-MM-YYYY");
    }

    // Check if the first part is a year or a day
    if (dateParts[0] > 31) { // Assuming it's YYYY-MM-DD
        yyyy = dateParts[0];
        mm = dateParts[1];
        dd = dateParts[2];
    }
    else { // It's DD-MM-YYYY
        dd = dateParts[0];
        mm = dateParts[1];
        yyyy = dateParts[2];
    }

    normalize();
}

Date::Date(int d, int m, int y) : yyyy(y), mm(m), dd(d) {
    normalize();
}


void Date::normalize() {
    
    // Normalize month
    while (mm < 1) {
        mm += 12;
        yyyy--;
    }
    while (mm > 12) {
        mm -= 12;
        yyyy++;
    }
    
    while (dd < 1) {
        mm--;
        if (mm < 1) {
            mm = 12;
            yyyy--;
        }
        dd += daysInMonth(mm, yyyy);
    }

    // Normalize day
    while (dd > daysInMonth(mm, yyyy)) {
        dd -= daysInMonth(mm, yyyy);
        mm++;
        if (mm > 12) {
            mm = 1;
            yyyy++;
        }
    }
    date_str = Date::dateToString(dd, mm, yyyy);
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int month, int year) {
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    month = (month - 1) % 12 + 1; 
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

// Comparison operators
bool Date::operator>(const Date& other) const {
    return std::tie(yyyy, mm, dd) > std::tie(other.yyyy, other.mm, other.dd);
}

bool Date::operator<(const Date& other) const {
    return std::tie(yyyy, mm, dd) < std::tie(other.yyyy, other.mm, other.dd);
}

bool Date::operator==(const Date& other) const {
    return std::tie(yyyy, mm, dd) == std::tie(other.yyyy, other.mm, other.dd);
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

// Subtraction operator
int Date::operator-(const Date& other) const {
    Date start = other, end = *this;
    if (start > end) std::swap(start, end);

    int days = 0;
    while (start < end) {
        start.dd++;
        start.normalize();
        days++;
    }
    return days;
}

// Addition function for duration
Date Date::addDuration(int amount, char type) const {
    Date result = *this;
    switch (std::tolower(type)) {
    case 'd': case 'b':
        result.dd += amount;
        break;
    case 'm':
        result.mm += amount;
        break;
    case 'y':
        result.yyyy += amount;
        break;
    default:
        throw std::invalid_argument("Invalid duration type");
    }
    result.normalize();
    return result;
}

// Utility for converting string duration to Date operation
Date Date::addDuration(const std::string& duration) {
    int amount = std::stoi(duration.substr(0, duration.size() - 1));
    char type = duration.back();
    int sign = 1; // Default to addition

    // Check if it's subtraction
    if (duration[0] == '-') {
        sign = -1;
        amount = std::stoi(duration.substr(1, duration.size() - 2)); // Skip the '-' sign
    }

    return addDuration(amount * sign, type);
}

Date Date::businessDayAdjusted(const CalendarKey& calendar, const BusinessDayConv& business_day_conv) {
    int orig_month = mm; 
    if (this->isBusinessDay(calendar)) {
        return *this; 
    }

    switch (business_day_conv) {
        case BusinessDayConv::FOLLOWING:
            return this->nextBusinessDay(calendar); 

        case BusinessDayConv::PRECEDING:
            return this->prevBusinessDay(calendar); 

        case BusinessDayConv::MOD_FOLLOWING: {
            Date next_bizz_day = this->nextBusinessDay(calendar);
            if (next_bizz_day.mm > orig_month) {
                return this->prevBusinessDay(calendar); 
            }
            return next_bizz_day; 
        }

        case BusinessDayConv::MOD_PRECEDING: {
            Date prev_bizz_day = this->prevBusinessDay(calendar);
            if (prev_bizz_day.mm < orig_month) {
                return this->nextBusinessDay(calendar); 
            }
            return prev_bizz_day; 
        }

        default:
            return *this; 
        }
}

Date Date::prevBusinessDay(const CalendarKey& calendar){
    Date adjusted_date = *this;
    while (!adjusted_date.isBusinessDay(calendar))
    {
        adjusted_date = adjusted_date.addDuration("-1D");
    }
    return adjusted_date;
}

Date Date::nextBusinessDay(const CalendarKey& calendar){
    Date adjusted_date = *this;
    while (!(adjusted_date.isBusinessDay(calendar)))
    {
        adjusted_date = adjusted_date.addDuration("1D");
    }
    return adjusted_date;
}

int Date::getWeekday() const {
    int d = dd;
    int m = mm;
    int y = yyyy;

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
    return weekday;
}

bool Date::isWeekend() {
    int dayOfWeek = getWeekday();
    return dayOfWeek == 0 || dayOfWeek == 1;
}

bool Date::isHoliday(const CalendarKey& calendar_key){
    auto calendar = Calendar::get(calendar_key);
    return (calendar.find(date_str) != calendar.end()) ? true : false;
}

int Date::countFrequencyUnits(const Date& start, const Date& end, const std::string& frequency) {
    // Ensure end is later than start
    if (end < start) {
        throw std::invalid_argument("End date must be later than start date");
    }

    // Parse frequency
    int amount = std::stoi(frequency.substr(0, frequency.length() - 1));
    char unit = std::tolower(frequency.back());

    if (unit == 'd' || unit == 'm' || unit == 'y') {
        Date next_frequency = start.addDuration(amount, unit);

        int units = 0;
        while (next_frequency <= end) {
            units++;
            next_frequency = next_frequency.addDuration(amount, unit);
        }
        return units;
    }
    else {
        throw std::invalid_argument("Frequency should end with 'D' for days, 'M' for months, or 'Y' for years");
    }
}

std::string Date::normalizeDate(const std::string& date_str) {
    std::stringstream ss(date_str);
    int day, month, year;
    char delimiter;

    ss >> day >> delimiter >> month >> delimiter >> year;

    // Create a normalized date string in DD-MM-YYYY format
    std::ostringstream normalized_date;
    normalized_date << std::setw(2) << std::setfill('0') << day << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << year;

    return normalized_date.str();
}

std::string Date::dateToString(const int& day, const int& month, const int& year) {
    std::ostringstream normalized_date;
    normalized_date << std::setw(2) << std::setfill('0') << day << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << year;
    return normalized_date.str();
}