#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Overlap of some functions needs tidy up.

class Date
{

public:

	int dd;
	int mm;
	int yyyy;
	bool isLeapYear;

	int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Constructors
	Date(const int& _dd, const int& _mm, const int& _yyyy) : dd(_dd), mm(_mm), yyyy(_yyyy) {

        isDateALeapYear();
	}

    Date(const string& date_string){

        if (!(date_string.size() == 10)) {
            throw ("Date string format must be in form DD-MM-YYYY or DD/MM/YYYY");
        }

        dd = stoi(date_string.substr(0, 2));
        mm = stoi(date_string.substr(3, 5));
        yyyy = stoi(date_string.substr(6, 10));

        isDateALeapYear();
    }

    // Operator Overload Functions
    bool operator>(const Date& rhs_date) const;

    bool operator<(const Date& rhs_date) const;

    bool operator==(const Date& rhs_date) const;

    bool operator!=(const Date& rhs_date) const;

    bool operator>=(const Date& rhs_date) const;

    bool operator<=(const Date& rhs_date) const;

    int operator-(const Date& rhs_date) const;

    // Member Functions
    void checkYearChange() {
        isDateALeapYear();
        if (mm == 2 && dd == 29 && !isLeapYear) {
            dd = 28;
        }
    }

    void isDateALeapYear() {
        if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)) {
            isLeapYear = true;
            monthDays[1] = 29;
        }
        else {
            isLeapYear = false;
            monthDays[1] = 28;
        }
    };

    static bool isYearALeapYear(const int& year) {
        if (year % 400 == 0) return true;
        if (year % 100 == 0) return false;
        if (year % 4 == 0) return true;
        return false;
    }

    static int daysInMonth(int year, int month) {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isYearALeapYear(year) ? 29 : 28;
        default:
            return 0;
        }
    }

    static Date addDurationToDate(Date date, string duration);
    static int dateToSerialNumber(const int& year, const int& month, const int& day);
    static bool isBusinessDay(const string& calendar) {};
    static void adjusted_date(const string& calendar, const string& roll_conv) {};

};

#endif // DATE_H

