#ifndef CASHFLOW_SCHEDULER_H
#define CASHFLOW_SCHEDULER_H

#include "../utils/Date.h"	

class CashflowScheduler
{
	


public:
	Date start_date;
	Date end_date;

	CashflowScheduler(const Date& _start_date, const Date&  _end_date, const string& _calendar, const string& _stub_type) : start_date(_start_date), end_date(_end_date) {};

	CashflowScheduler& generateCashflows(const string& frequency);

};

#endif // CASHFLOW_SCHEDULER_H