#ifndef CASHFLOW_SCHEDULER_H
#define CASHFLOW_SCHEDULER_H

#include "../utils/Date.h"	


#include <vector>
#include <string>
using std::vector;
using std::string;


struct CashflowDates{
	Date unadjusted_start_date;
	Date adjusted_start_date ;
	Date unadjusted_end_date;
	Date adjusted_end_date;
	
	CashflowDates() {

	}

	CashflowDates(const Date& _unadjusted_start_date, const Date& _adjusted_start_date,
		const Date& _unadjusted_end_date, const Date& _adjusted_end_date) : unadjusted_start_date(_unadjusted_start_date), adjusted_start_date(_adjusted_start_date)
		, unadjusted_end_date(_unadjusted_end_date), adjusted_end_date(_adjusted_end_date) {}
};

class CashflowScheduler
{
	
public:

	static vector<CashflowDates> generateCashflows(const Date& start_date, const Date& end_date, const CalendarKey& calendar, const string& stub_type,
		const string& frequency, const BusinessDayConv& business_day_conv, const RollConv& roll_conv);

};

#endif // CASHFLOW_SCHEDULER_H