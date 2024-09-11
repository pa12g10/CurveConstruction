#include "CashflowScheduler.h"
#include "../data/Calendars.h"
#include "../src/utils/Date.h"

vector<CashflowDates> CashflowScheduler::generateCashflows(const Date& start_date, const Date& end_date, const CalendarKey& calendar, const string& stub_type,
	const string& frequency, const BusinessDayConv& business_day_conv, const RollConv& roll_conv)
{
	int num_cfs = Date::countFrequencyUnits(start_date, end_date, frequency);
	int cf_cnter = 0;
	Date date_marker = Date(end_date.dd, end_date.mm, end_date.yyyy);
	string frequency_shift = "-" + frequency;
	vector<CashflowDates> cfs(num_cfs);

	do {
		Date unadjusted_accural_end_date = date_marker;
		date_marker = date_marker.addDuration(frequency_shift);
		Date unadjusted_accural_start_date = date_marker;

		Date adjusted_accural_start_date = unadjusted_accural_start_date.businessDayAdjusted(calendar, business_day_conv);
		Date adjusted_accural_end_date = unadjusted_accural_end_date.businessDayAdjusted(calendar, business_day_conv);
		auto cf = CashflowDates(unadjusted_accural_start_date, unadjusted_accural_end_date, unadjusted_accural_start_date, unadjusted_accural_end_date);
		cfs[cf_cnter] = cf;
		cf_cnter++;
	} while (date_marker > start_date);

	std::reverse(cfs.begin(), cfs.end());
	return cfs;
}
