#include "pch.h"
#include "CppUnitTest.h"
#include "../CurveConstruction/src/utils/Date.h"
#include "../CurveConstruction/data/Calendars.h"
#include "../CurveConstruction/src/cashflows/CashflowScheduler.h"
#include "../CurveConstruction/src/curve_models/RFRModel.h"
#include "../CurveConstruction/data/CurveData.h"
#include "../CurveConstruction/data/InstrumentData.h"
#include <utils/DateUtilities.h>

static std::string formatDate(int year, int month, int day) {
	std::stringstream ss;

	// Add the year as is
	ss << year;

	// Add the month with leading zero if needed
	ss << std::setw(2) << std::setfill('0') << month;

	// Add the day with leading zero if needed
	ss << std::setw(2) << std::setfill('0') << day;

	return ss.str();
}

std::string formatDateDDMMYYYY(int day, int month, int year) {
	std::stringstream ss;

	// Add the day with leading zero if needed
	ss << std::setw(2) << std::setfill('0') << day << "-";

	// Add the month with leading zero if needed
	ss << std::setw(2) << std::setfill('0') << month << "-";

	// Add the year as is
	ss << year;

	return ss.str();
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using std::vector;

namespace TestingDates
{

	TEST_CLASS(CppFeatures)
	{
	public:

		void printName(const string&& value) {
			cout << "[rvalue]" << value << endl;
		}

		void printName(const string& value) {
			cout << "[lvalue]" << value << endl;
		}

		TEST_METHOD(TestLValueRValue)
		{
			string first_name = "Peter";
			string last_name = "Allen";
			string full_name = first_name + last_name;

			printName(full_name);
			printName(first_name + last_name);

		}
	};

	TEST_CLASS(CashflowSchedule)
	{
	public:

		TEST_METHOD(TestGenerateCashflowSchdule)
		{
			int start_date = 20240210; 
			std::string pay_delay = "0B";
			int end_date = DateUtilities::addDuration(start_date, "5Y");
			string frequency = "3M";
			CalendarKey calendar = CalendarKey::LON;
			BusinessDayConv business_day_conv = BusinessDayConv::MOD_FOLLOWING;
			RollConv roll_conv = RollConv::BEOM;
			StubType stub_type = StubType::ShortStart;

			vector<CashflowDates> cfs = CashflowScheduler::generateCashflows(start_date, end_date, pay_delay, calendar, stub_type, frequency,
				business_day_conv, roll_conv);
			int cf_size = cfs.size();
			Assert::AreEqual(20, cf_size);
		}
	};

	TEST_CLASS(InputData)
	{
	public:
		
		TEST_METHOD(TestInstrumentDataLoads)
		{
			int cash_size = cash_instrument_data.size();
			int oisswaps_size = ois_swap_instrument_data.size();
			int cbswaps_size = cbswap_instrument_data.size();

			Assert::AreEqual(1, cash_size);
			Assert::AreEqual(8, oisswaps_size);
			Assert::AreEqual(6, cbswaps_size);
			
		}
	};

	TEST_CLASS(Dates)
	{
	public:
	

		TEST_METHOD(TestDifferenceBetweenTwoDatesEx1)
		{
			int earlier_date = 20010101;
			int later_date= 20010102;
			int result = DateUtilities::subtractDates(later_date, earlier_date);
			Assert::AreEqual(1, result);

		}

		TEST_METHOD(TestDifferenceBetweenTwoDatesEx2)
		{
			int earlier_date = 20210302;
			int later_date = 20230101;
			int result = DateUtilities::subtractDates(later_date, earlier_date);
			Assert::AreEqual(670, result);

		}

		TEST_METHOD(TestGetCalendars)
		{
			std::map <int, std::string> lon_cal = Calendar::get(CalendarKey::LON);
			size_t result_len = 625;
			Assert::AreEqual(result_len, lon_cal.size());

			std::map <int, std::string> us_cal = Calendar::get(CalendarKey::USD);
			result_len = 710;
			Assert::AreEqual(result_len, us_cal.size());

			std::map <int, std::string> eur_cal = Calendar::get(CalendarKey::EUR);
			result_len = 497;
			Assert::AreEqual(result_len, eur_cal.size());


			auto holiday = 20241226;
			auto iterator = lon_cal.find(holiday);
			bool isHoliday = (iterator != lon_cal.end()) ?  true : false;
			Assert::AreEqual(true, isHoliday);

			auto not_holiday = 20241227;
			iterator = lon_cal.find(not_holiday);
			isHoliday = (iterator != lon_cal.end()) ? true : false;
			Assert::AreEqual(false, isHoliday);
		}


		TEST_METHOD(TestAddDurationToDate)
		{
			int  date = 20220227;
			string tenor_3D = "3D";
			int new_date_plus_3D = DateUtilities::addDuration(date, tenor_3D);

			Assert::AreEqual(20220302, new_date_plus_3D);


			string tenor_3M = "3M";
			int new_date_plus_3M = DateUtilities::addDuration(date, tenor_3M);

			Assert::AreEqual(20220527, new_date_plus_3M);

			string tenor_12M = "12M";
			int new_date_plus_12M = DateUtilities::addDuration(date, tenor_12M);

			Assert::AreEqual(20230227, new_date_plus_12M);

			string tenor_1Y = "1Y";
			int new_date_plus_1Y = DateUtilities::addDuration(date, tenor_1Y);

			Assert::AreEqual(20230227, new_date_plus_1Y);

			// Leap Year 
			// Add days
			int date_pre_leap_year = 19991120;
			string tenor_101D = "101D";
			int new_date_plus_101D = DateUtilities::addDuration(date_pre_leap_year, tenor_101D);

			Assert::AreEqual(20000229, new_date_plus_101D);

			// Add Months
			date_pre_leap_year = 19991129; 
			new_date_plus_3M = DateUtilities::addDuration(date_pre_leap_year, tenor_3M);

			Assert::AreEqual(20000229, new_date_plus_3M);

			//Add Years
			int date_leap_year_str = 19960229;
			string tenor_4Y = "4Y";
			int new_date_plus_4Y = DateUtilities::addDuration(date_leap_year_str, tenor_4Y);

			Assert::AreEqual(20000229, new_date_plus_4Y);

		}

		TEST_METHOD(TestSubtractDurationToDate)
		{
			int date = 20220227;
			int new_date_minus5D = DateUtilities::addDuration(date, "-5D");
			Assert::AreEqual(20220222, new_date_minus5D);

			date = 20220101;
			new_date_minus5D = DateUtilities::addDuration(date, "-5D");
			Assert::AreEqual(20211227, new_date_minus5D);

			date = 20040229;
			int new_date_minus36M = DateUtilities::addDuration(date, "-36M");
			Assert::AreEqual(20010301, new_date_minus36M);


			date = 20041231;
			int new_date_minus1M = DateUtilities::addDuration(date, "-1M");
			Assert::AreEqual(20041130, new_date_minus1M);

			date = 20020331;
			int new_date_minus13M = DateUtilities::addDuration(date, "-13M");
			Assert::AreEqual(20010228, new_date_minus13M);
		}

		TEST_METHOD(TestWeekendHolidayDates)
		{
			int saturday = 20240907; 
			int sunday = 20240908; 
			int monday = 20231016; 
			int tuesday = 20231017; 

			Assert::AreEqual(true, DateUtilities::isWeekend(saturday));
			Assert::AreEqual(true, DateUtilities::isWeekend(sunday));
			Assert::AreEqual(false, DateUtilities::isWeekend(monday));
			Assert::AreEqual(false, DateUtilities::isWeekend(tuesday));

			int xmas_date = 20231225; 
			int jan_1st_date = 20240101; 
			Assert::AreEqual(true, DateUtilities::isHoliday(xmas_date, CalendarKey::LON));
			Assert::AreEqual(true, DateUtilities::isHoliday(jan_1st_date, CalendarKey::LON));
		}

		TEST_METHOD(TestIsBusinessDay)
		{
			int saturday = 20240907; 
			int xmas_date = 20231225; 
			int jan_1st_date = 20240101; 
			int jan_2nd_date = 20240102; 

			Assert::AreEqual(false, DateUtilities::isBusinessDay(saturday, CalendarKey::LON));
			Assert::AreEqual(false, DateUtilities::isBusinessDay(xmas_date, CalendarKey::LON));
			Assert::AreEqual(false, DateUtilities::isBusinessDay(jan_1st_date, CalendarKey::LON));
			Assert::AreEqual(true, DateUtilities::isBusinessDay(jan_2nd_date, CalendarKey::LON));

		}

		TEST_METHOD(TestBusinessDayConventionAdjustments)
		{
			int saturday = 20240907; 
			int monday_9th = 20240909; 
			int friday_6th = 20240906; 
			

			int next_bizz_day = DateUtilities::businessDayAdjusted(saturday, CalendarKey::LON, BusinessDayConv::FOLLOWING);
			Assert::AreEqual(monday_9th, next_bizz_day);

			int prev_bizz_day = DateUtilities::businessDayAdjusted(saturday, CalendarKey::LON, BusinessDayConv::PRECEDING);
			Assert::AreEqual(friday_6th, prev_bizz_day);


			int eom_1B_prior_date = 20240831; 
			int bom_1B_post_date = 20240901; 
			int mod_follow_eom_date = 20240830; 
			int mod_prec_eom_date = 20240902; 

			next_bizz_day = DateUtilities::businessDayAdjusted(eom_1B_prior_date, CalendarKey::LON, BusinessDayConv::MOD_FOLLOWING);
			Assert::AreEqual(mod_follow_eom_date, next_bizz_day);

			prev_bizz_day = DateUtilities::businessDayAdjusted(bom_1B_post_date, CalendarKey::LON, BusinessDayConv::MOD_PRECEDING);
			Assert::AreEqual(mod_prec_eom_date, prev_bizz_day);

			int xmas_date = 20231226; 
			int next_date_after_xmas = 20231227; 
			next_bizz_day = DateUtilities::businessDayAdjusted(xmas_date, CalendarKey::LON, BusinessDayConv::FOLLOWING);
			Assert::AreEqual(next_date_after_xmas, next_bizz_day);
			
		}

	};
}
