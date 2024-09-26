#include "CashflowScheduler.h"
#include "../src/utils/DateUtilities.h"

vector<CashflowDates> CashflowScheduler::generateCashflows(const int& start_date, const int& end_date, const std::string& pay_delay,
	const CalendarKey& calendar_key, const StubType& stub_type, const string& frequency, const BusinessDayConv& business_day_conv, const RollConv& roll_conv)
{
	int num_cfs = DateUtilities::countFrequencyUnits(start_date, end_date, frequency);
	int cf_cnter = 0;
	int date_marker = end_date;
	string frequency_shift = "-" + frequency;
	vector<CashflowDates> cfs(num_cfs);

	do {
		int unadjusted_accural_end_date = date_marker;
		int adjusted_accural_end_date = DateUtilities::businessDayAdjusted(unadjusted_accural_end_date, calendar_key, business_day_conv);
		int payment_date = DateUtilities::addDurationBusinessDay(adjusted_accural_end_date, pay_delay, calendar_key, business_day_conv);
		
		date_marker = DateUtilities::addDuration(date_marker, frequency_shift);

		int unadjusted_accural_start_date = date_marker;
		int adjusted_accural_start_date = DateUtilities::businessDayAdjusted(unadjusted_accural_start_date, calendar_key, business_day_conv);
		
		auto cf = CashflowDates(unadjusted_accural_start_date, adjusted_accural_start_date, unadjusted_accural_end_date, adjusted_accural_end_date,
			payment_date);

		cfs[cf_cnter] = cf;
		cf_cnter++;

	} while (date_marker > start_date);

	std::reverse(cfs.begin(), cfs.end());
	return cfs;
}
