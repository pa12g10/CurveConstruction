#include "Date.h"
#include <algorithm>


bool Date::operator>(const Date& rhs_date) const
{
    if (yyyy > rhs_date.yyyy) {
        return true;
    }

    if (yyyy < rhs_date.yyyy) {
        return false;
    }

    if (mm > rhs_date.mm) {
        return true;
    }

    if (mm < rhs_date.mm) {
        return false;
    }

    if (dd > rhs_date.dd) {
        return true;
    }

    if (dd < rhs_date.dd) {
        return false;
    }

    return false;
}

bool Date::operator<(const Date& rhs_date) const
{
    return !(*this >= rhs_date);
}

bool Date::operator==(const Date& rhs_date) const
{
    return (dd == rhs_date.dd) && (mm == rhs_date.mm) && (yyyy == rhs_date.yyyy);
}

bool Date::operator!=(const Date& rhs_date) const
{
    return !(*this == rhs_date);
}

bool Date::operator>=(const Date& rhs_date) const
{
    return (*this > rhs_date) || (*this == rhs_date);
}

bool Date::operator<=(const Date& rhs_date) const
{
    return (*this < rhs_date) || (*this == rhs_date);
}

Date Date::addDurationToDate(Date date, string duration) {
    transform(duration.begin(), duration.end(), duration.begin(), ::tolower);
    int duration_size = stoi(duration.substr(0, duration.size() - 1));
    string tenor_type = duration.substr(duration.size() - 1, duration.size());
    int add_subtract = (duration.substr(0, 1) == "-") ? -1 : 1;

    size_t found_d = duration.find("d"), found_b = duration.find("b");
    size_t found_m = duration.find("m"), found_y = duration.find("y");

    if (!(found_d != std::string::npos || found_b != std::string::npos || found_m != std::string::npos || found_y != std::string::npos )) {
        throw("Tenor type not recognised: " + tenor_type);
    }

    if (add_subtract == 1) {
        if (tenor_type == "d" || tenor_type == "b") {
            date.dd += duration_size;
            while (date.dd > date.monthDays[date.mm - 1]) {
                date.dd -= date.monthDays[date.mm - 1];
                date.mm++;
                if (date.mm > 12) {
                    date.mm -= 12;
                    date.yyyy++;
                    date.checkYearChange();
                }
            }
        }
        else if (tenor_type == "m") {
            date.mm += duration_size;
            while (date.mm > 12) {
                date.mm -= 12;
                date.yyyy++;
                date.checkYearChange();
            }
        }
        else if (tenor_type == "y") {
            date.yyyy += duration_size;
            date.checkYearChange();
        }
    }
    else {
        if (tenor_type == "d" || tenor_type == "b") {
            date.dd += duration_size;
            while (date.dd <= 0 )
            {
                date.dd += date.monthDays[date.mm - 1];
                date.mm--;
                if (date.mm <= 0) {
                    date.mm += 12;
                    date.yyyy--;
                    date.checkYearChange();
                }
            }
        }
        else if (tenor_type == "m") {
            date.mm += duration_size;
            while (date.mm <= 0) {
                date.mm += 12;
                date.yyyy--;
                date.checkYearChange();
            }
        }
        else if (tenor_type == "y") {
            date.yyyy += duration_size;
            date.checkYearChange();
        }
    }

    return date;
}