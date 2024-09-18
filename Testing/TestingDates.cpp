#include "pch.h"
#include "CppUnitTest.h"
#include "../CurveConstruction/src/utils/Date.h"
#include "../CurveConstruction/data/Calendars.h"
#include "../CurveConstruction/src/cashflows/CashflowScheduler.h"
#include "../CurveConstruction/src/curve_models/RFRModel.h"
#include "../CurveConstruction/data/CurveData.h"
#include "../CurveConstruction/data/InstrumentData.h"



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
			Date start_date = Date(10, 2, 2024);
			Date end_date = start_date.addDuration("5Y");
			string stub_type = "SS", frequency = "3M";
			CalendarKey calendar = CalendarKey::LON;
			BusinessDayConv business_day_conv = BusinessDayConv::MOD_FOLLOWING;
			RollConv roll_conv = RollConv::BEOM;

			vector<CashflowDates> cfs = CashflowScheduler::generateCashflows(start_date, end_date, calendar, stub_type, frequency, business_day_conv, roll_conv);
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

		TEST_METHOD(TestDateStringToDate)
		{
			string date_str = "11-01-2022";
			Date date = Date(date_str);

			Assert::AreEqual(11, date.dd);
			Assert::AreEqual(1, date.mm);
			Assert::AreEqual(2022, date.yyyy);


			string date_str_2 = "11/11/2024";
			Date date2 = Date(date_str_2);

			Assert::AreEqual(11, date2.dd);
			Assert::AreEqual(11, date2.mm);
			Assert::AreEqual(2024, date2.yyyy);


		}

		TEST_METHOD(TestDifferenceBetweenTwoDates)
		{
			Date date1 = Date(1, 1, 2001);
			Date date2 = Date(2, 1, 2001);
			int result = date2 - date1;
			Assert::AreEqual(1, result);

		}

		TEST_METHOD(TestGetCalendars)
		{
			std::unordered_map <std::string, std::string> lon_cal = Calendar::get(CalendarKey::LON);
			size_t result_len = 625;
			Assert::AreEqual(result_len, lon_cal.size());

			std::unordered_map <std::string, std::string> us_cal = Calendar::get(CalendarKey::USD);
			result_len = 710;
			Assert::AreEqual(result_len, us_cal.size());

			std::unordered_map <std::string, std::string> eur_cal = Calendar::get(CalendarKey::EUR);
			result_len = 497;
			Assert::AreEqual(result_len, eur_cal.size());


			auto holiday = "26-12-2024";
			auto iterator = lon_cal.find(holiday);
			bool isHoliday = (iterator != lon_cal.end()) ?  true : false;
			Assert::AreEqual(true, isHoliday);

			auto not_holiday = "27-12-2024";
			iterator = lon_cal.find(not_holiday);
			isHoliday = (iterator != lon_cal.end()) ? true : false;
			Assert::AreEqual(false, isHoliday);



		}


		TEST_METHOD(TestDateGreaterThanOperator)
		{
			Date date1 = Date(1, 1, 2001);
			Date date2 = Date(2, 1, 2001);
			bool result =  date2 > date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2001);
			date2 = Date(1, 2, 2001);
			result = date2 > date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2001);
			date2 = Date(1, 1, 2002);
			result = date2 > date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2002);
			date2 = Date(1, 1, 2002);
			result = date2 > date1;
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestDateLessThanOperator)
		{
			Date date1 = Date(2, 1, 2001);
			Date date2 = Date(1, 1, 2001);
			bool result = date2 < date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 2, 2001);
			date2 = Date(1, 1, 2001);
			result = date2 < date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2002);
			date2 = Date(1, 1, 2001);
			result = date2 < date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2002);
			date2 = Date(1, 1, 2002);
			result = date2 < date1;
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestDateEqualOperator)
		{
			Date date1 = Date(1, 1, 2001);
			Date date2 = Date(1, 1, 2001);
			bool result = date2 == date1;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestDateNotEqualOperator)
		{
			Date date1 = Date(1, 1, 2001);
			Date date2 = Date(2, 1, 2001);
			bool result = date2 != date1;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestDateGreaterThanEqualOperator)
		{
			Date date1 = Date(1, 1, 2001);
			Date date2 = Date(2, 1, 2001);
			bool result = date2 >= date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2001);
			date2 = Date(1, 1, 2001);
			result = date2 >= date1;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(TestDateLessThanEqualOperator)
		{
			Date date1 = Date(2, 1, 2001);
			Date date2 = Date(1, 1, 2001);
			bool result = date2 <= date1;
			Assert::AreEqual(true, result);

			date1 = Date(1, 1, 2001);
			date2 = Date(1, 1, 2001);
			result = date2 <= date1;
			Assert::AreEqual(true, result);
		}

		/*TEST_METHOD(TestDateToString)
		{
			string date_str = "11-01-2022";
			Date date = Date(date_str);
			Assert::AreEqual(date_str, date.toString());
		}*/

		/*TEST_METHOD(TestDateDurationTypeNotRecognised)
		{
			string date_str = "11-01-2022";
			Date date = Date(date_str);
			string duration = "3Q";
			auto add_duration_func = [date, duration](){Date::addDurationToDate(date, duration);};
		}*/

		TEST_METHOD(TestAddDurationToDate)
		{
			string date_str = "27-02-2022";
			Date date = Date(date_str);

			string tenor_3D = "3D";
			Date new_date_plus_3D = date.addDuration(tenor_3D);

			Assert::AreEqual(2, new_date_plus_3D.dd);
			Assert::AreEqual(3, new_date_plus_3D.mm);
			Assert::AreEqual(2022, new_date_plus_3D.yyyy);


			string tenor_3M = "3M";
			Date new_date_plus_3M = date.addDuration(tenor_3M);

			Assert::AreEqual(27, new_date_plus_3M.dd);
			Assert::AreEqual(5, new_date_plus_3M.mm);
			Assert::AreEqual(2022, new_date_plus_3M.yyyy);

			string tenor_12M = "12M";
			Date new_date_plus_12M = date.addDuration(tenor_12M);

			Assert::AreEqual(27, new_date_plus_12M.dd);
			Assert::AreEqual(2, new_date_plus_12M.mm);
			Assert::AreEqual(2023, new_date_plus_12M.yyyy);

			// Leap Year 
			// Add days
			string date_pre_leap_year_str = "20-11-1999";
			Date date_pre_leap_year = Date(date_pre_leap_year_str);

			string tenor_101D = "101D";
			Date new_date_plus_101D = date_pre_leap_year.addDuration(tenor_101D);

			Assert::AreEqual(29, new_date_plus_101D.dd);
			Assert::AreEqual(2, new_date_plus_101D.mm);
			Assert::AreEqual(2000, new_date_plus_101D.yyyy);

			// Add Months
			date_pre_leap_year_str = "29-11-1999";
			date_pre_leap_year = Date(date_pre_leap_year_str);

			new_date_plus_3M = date_pre_leap_year.addDuration(tenor_3M);

			Assert::AreEqual(29, new_date_plus_3M.dd);
			Assert::AreEqual(2, new_date_plus_3M.mm);
			Assert::AreEqual(2000, new_date_plus_3M.yyyy);

			//Add Years
			string date_leap_year_str = "29-02-1996";
			Date date_leap_year = Date(date_leap_year_str);
			string tenor_4Y = "4Y";

			Date new_date_plus_4Y = date_leap_year.addDuration(tenor_4Y);

			Assert::AreEqual(29, new_date_plus_4Y.dd);
			Assert::AreEqual(2, new_date_plus_4Y.mm);
			Assert::AreEqual(2000, new_date_plus_4Y.yyyy);

		}

		TEST_METHOD(TestSubtractDurationToDate)
		{
			string date_str = "27-02-2022";
			Date date = Date(date_str);

			Date new_date_minus5D = date.addDuration("-5D");

			Assert::AreEqual(22, new_date_minus5D.dd);
			Assert::AreEqual(2, new_date_minus5D.mm);
			Assert::AreEqual(2022, new_date_minus5D.yyyy);

			date_str = "01-01-2022";
			date = Date(date_str);

			new_date_minus5D = date.addDuration("-5D");

			Assert::AreEqual(27, new_date_minus5D.dd);
			Assert::AreEqual(12, new_date_minus5D.mm);
			Assert::AreEqual(2021, new_date_minus5D.yyyy);

			date_str = "29-02-2004";
			date = Date(date_str);

			Date new_date_minus24M = date.addDuration("-36M");

			Assert::AreEqual(1, new_date_minus24M.dd);
			Assert::AreEqual(3, new_date_minus24M.mm);
			Assert::AreEqual(2001, new_date_minus24M.yyyy);

		}

		TEST_METHOD(TestWeekendHolidayDates)
		{
			Date saturday = Date("7-9-2024");
			Date sunday = Date("8-9-2024");
			Date monday = Date("16-10-2023");
			Date tuesday = Date("17-10-2023");

			bool isSatWeekend = saturday.isWeekend();
			bool isSunWeekend = sunday.isWeekend();

			Assert::AreEqual(true, saturday.isWeekend());
			Assert::AreEqual(true, sunday.isWeekend());
			Assert::AreEqual(false, monday.isWeekend());
			Assert::AreEqual(false, tuesday.isWeekend());

			Date xmas_date = Date("25-12-2023");
			Date jan_1st_date = Date("1-1-2024");
			Assert::AreEqual(true, xmas_date.isHoliday(CalendarKey::LON));
			Assert::AreEqual(true, jan_1st_date.isHoliday(CalendarKey::LON));
		}

		TEST_METHOD(TestIsBusinessDay)
		{
			Date saturday = Date("7-9-2024");
			Date xmas_date = Date("25-12-2023");
			Date jan_1st_date = Date("1-1-2024");
			Date jan_2nd_date = Date("2-1-2024");

			Assert::AreEqual(false, saturday.isBusinessDay(CalendarKey::LON));
			Assert::AreEqual(false, xmas_date.isBusinessDay(CalendarKey::LON));
			Assert::AreEqual(false, jan_1st_date.isBusinessDay(CalendarKey::LON));
			Assert::AreEqual(true, jan_2nd_date.isBusinessDay(CalendarKey::LON));

		}

		TEST_METHOD(TestBusinessDayConventionAdjustments)
		{
			Date saturday = Date("7-9-2024");
			Date monday_9th = Date("9-9-2024");
			Date friday_6th = Date("6-9-2024");
			

			Date next_bizz_day = saturday.businessDayAdjusted(CalendarKey::LON, BusinessDayConv::FOLLOWING);
			Assert::AreEqual(monday_9th.date_str, next_bizz_day.date_str);

			Date prev_bizz_day = saturday.businessDayAdjusted(CalendarKey::LON, BusinessDayConv::PRECEDING);
			Assert::AreEqual(friday_6th.date_str, prev_bizz_day.date_str);


			Date eom_1B_prior_date = Date("31-08-2024");
			Date bom_1B_post_date = Date("01-09-2024");
			Date mod_follow_eom_date = Date("30-08-2024");
			Date mod_prec_eom_date = Date("02-09-2024");

			next_bizz_day = eom_1B_prior_date.businessDayAdjusted(CalendarKey::LON, BusinessDayConv::MOD_FOLLOWING);
			Assert::AreEqual(mod_follow_eom_date.date_str, next_bizz_day.date_str);

			prev_bizz_day = bom_1B_post_date.businessDayAdjusted(CalendarKey::LON, BusinessDayConv::MOD_PRECEDING);
			Assert::AreEqual(mod_prec_eom_date.date_str, prev_bizz_day.date_str);

			Date xmas_date = Date("26-12-2023");
			Date next_date_after_xmas = Date("27-12-2023");
			next_bizz_day = xmas_date.businessDayAdjusted(CalendarKey::LON, BusinessDayConv::FOLLOWING);
			Assert::AreEqual(next_date_after_xmas.date_str, next_bizz_day.date_str);
			
		}

	};
}
