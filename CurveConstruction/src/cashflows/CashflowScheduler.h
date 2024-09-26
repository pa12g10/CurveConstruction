#ifndef CASHFLOW_SCHEDULER_H
#define CASHFLOW_SCHEDULER_H

#include "../data/Enums.h"	


#include <vector>
#include <string>
using std::vector;
using std::string;


struct CashflowDates{
	int unadjusted_start_date;
	int adjusted_start_date ;
	int unadjusted_end_date;
	int adjusted_end_date;
	int payment_date;
	
	CashflowDates() {

	}

	CashflowDates(const int& _unadjusted_start_date, const int& _adjusted_start_date,
		const int& _unadjusted_end_date, const int& _adjusted_end_date, const int& _payment_date) : unadjusted_start_date(_unadjusted_start_date), adjusted_start_date(_adjusted_start_date)
		, unadjusted_end_date(_unadjusted_end_date), adjusted_end_date(_adjusted_end_date), payment_date(_payment_date) {}
};

class CashflowScheduler
{
	
public:

	static vector<CashflowDates> generateCashflows(const int& start_date, const int& end_date, const std::string& pay_delay, 
		const CalendarKey& calendar, const StubType& stub_type, const string& frequency, const BusinessDayConv& business_day_conv,
		const RollConv& roll_conv);

};

#endif // CASHFLOW_SCHEDULER_H