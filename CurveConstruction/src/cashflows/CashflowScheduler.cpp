#include "CashflowScheduler.h"
#include "../data/Calendars.h"

vector<CashflowDates> CashflowScheduler::generateCashflows(const Date& start_date, const Date& end_date, string& calendar, string& stub_type,
	const string& frequency, const string& roll_conv)
{
	Date date_marker = Date(end_date.dd, end_date.mm, end_date.yyyy);
	string frquency_shift = "-" + frequency;

	/*Date unadjusted_accural_end_date = date_marker;
	Date unadjusted_accural_start_date = Date::addDurationToDate(date_marker, frquency_shift);


	Date adjusted_accural_start_date = Date::adjusted_date(unadjusted_accural_start_date);
	Date adjusted_accural_end_date = Date::adjusted_date(unadjusted_accural_end_date);

	CashflowDates cf = CashflowDates(unadjusted_accural_start_date, adjusted_accural_start_date, unadjusted_accural_end_date, adjusted_accural_end_date);*/


	while (date_marker > start_date) {

		/*unadjusted_accural_start_date;
		unadjusted_accural_end_date ;

		adjusted_accural_start_date;
		adjusted_accural_end_date;
		
		cf = CashflowDates(unadjusted_accural_start_date, adjusted_accural_start_date, unadjusted_accural_end_date, adjusted_accural_end_date);*/


	}

	return {};
}
