#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date
{
	int dd;
	int mm;
	int yyyy;
	bool isLeapYear;

	const int monthDays[12]
		= { 31, 28, 31, 30, 31, 30,
		   31, 31, 30, 31, 30, 31 };

public:
	Date(const int& _dd, const int& _mm, const int& _yyyy) : dd(_dd), mm(_mm), yyyy(_yyyy) {

		// Is Leap Year
		if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)) {
			isLeapYear = true; 
		}
		else {
			isLeapYear = false; 
		}
	}

    static void addDurationToDate(Date date, string duration) {
        int duration_size = stoi(duration.substr(duration.size() - 1));
        if (duration.find('D') != std::string::npos || duration.find('B') != std::string::npos 
            || duration.find('d') != std::string::npos || duration.find('b') != std::string::npos ) {
            date.dd += duration_size;
            while (date.dd > 31) {
                date.dd -= 31;
                date.mm++;
            }
        }
        else if (duration.find('M') != std::string::npos || duration.find('m') != std::string::npos) {
            date.mm += duration_size;
            while (date.mm > 12) {
                date.mm -= 12;
                date.yyyy++;
            }
        }
        else if (duration.find('y') != std::string::npos || duration.find('Y') != std::string::npos) {
            date.yyyy += duration_size;
            if (date.mm == 2 && date.dd == 29 && !date.isLeapYear) {
                date.dd = 28;
            }
        }
    }



};

#endif // DATE_H

