#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    bool operator>(const Date& other_date) const;

    bool operator<(const Date& other_date) const;

    bool operator==(const Date& other_date) const;

    bool operator!=(const Date& other_date) const;

    bool operator>=(const Date& other_date) const;

    bool operator<=(const Date& other_date) const;

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

    static Date addDurationToDate(Date date, string duration);

};

#endif // DATE_H

