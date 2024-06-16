#include "pch.h"
#include "CppUnitTest.h"
#include "./data/instrument_data.h"
#include "../CurveConstruction/src/utils/Date.h"
#include "../CurveConstruction/data/Calendars.h"
#include "../CurveConstruction/src/cashflows/CashflowScheduler.h"

#include <string>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{

	TEST_CLASS(CashflowSchedule)
	{
	public:

		TEST_METHOD(TestGenerateCashflowSchdule)
		{
			Date start_date = Date(10, 2, 2024), end_date = Date(10, 2, 2034);
		/*	string cal = "LON", stub_type = "SS";
			CashflowScheduler cf_schedule = CashflowScheduler(start_date, end_date, cal, stub_type);*/

			//Assert::AreEqual(1, cash_size);

		}
	};

	TEST_CLASS(InputData)
	{
	public:
		
		TEST_METHOD(TestInstrumentDataLoads)
		{
			auto ois_cash = CashInstrumentStaticData().get();
			auto ois_swaps = OISSwapInstrumentStaticData().get();
			auto cb_swaps = CBSwapInstrumentStaticData().get();

			int cash_size = ois_cash.size();
			int oisswaps_size = ois_swaps.size();
			int cbswaps_size = cb_swaps.size();

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
			map<Date, string> lon_cal = Calendar::get("LON");
			size_t result_len = 625;
			Assert::AreEqual(result_len, lon_cal.size());

			map<Date, string> us_cal = Calendar::get("USD");
			result_len = 710;
			Assert::AreEqual(result_len, us_cal.size());

			map<Date, string> eur_cal = Calendar::get("EUR");
			result_len = 497;
			Assert::AreEqual(result_len, eur_cal.size());

			Date holiday = Date(26, 12, 2024);
			auto iterator = lon_cal.find(holiday);
			bool isHoliday = (iterator != lon_cal.end()) ?  true : false;
			Assert::AreEqual(true, isHoliday);

			Date not_holiday = Date(27, 12, 2024);
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
			Date new_date_plus_3D = Date::addDurationToDate(date, tenor_3D);

			Assert::AreEqual(2, new_date_plus_3D.dd);
			Assert::AreEqual(3, new_date_plus_3D.mm);
			Assert::AreEqual(2022, new_date_plus_3D.yyyy);


			string tenor_3M = "3M";
			Date new_date_plus_3M = Date::addDurationToDate(date, tenor_3M);

			Assert::AreEqual(27, new_date_plus_3M.dd);
			Assert::AreEqual(5, new_date_plus_3M.mm);
			Assert::AreEqual(2022, new_date_plus_3M.yyyy);

			string tenor_12M = "12M";
			Date new_date_plus_12M = Date::addDurationToDate(date, tenor_12M);

			Assert::AreEqual(27, new_date_plus_12M.dd);
			Assert::AreEqual(2, new_date_plus_12M.mm);
			Assert::AreEqual(2023, new_date_plus_12M.yyyy);

			// Leap Year 
			// Add days
			string date_pre_leap_year_str = "20-11-1999";
			Date date_pre_leap_year = Date(date_pre_leap_year_str);

			string tenor_101D = "101D";
			Date new_date_plus_101D = Date::addDurationToDate(date_pre_leap_year, tenor_101D);

			Assert::AreEqual(29, new_date_plus_101D.dd);
			Assert::AreEqual(2, new_date_plus_101D.mm);
			Assert::AreEqual(2000, new_date_plus_101D.yyyy);

			// Add Months
			date_pre_leap_year_str = "29-11-1999";
			date_pre_leap_year = Date(date_pre_leap_year_str);

			new_date_plus_3M = Date::addDurationToDate(date_pre_leap_year, tenor_3M);

			Assert::AreEqual(29, new_date_plus_3M.dd);
			Assert::AreEqual(2, new_date_plus_3M.mm);
			Assert::AreEqual(2000, new_date_plus_3M.yyyy);

			//Add Years
			string date_leap_year_str = "29-02-1996";
			Date date_leap_year = Date(date_leap_year_str);
			string tenor_4Y = "4Y";

			Date new_date_plus_4Y = Date::addDurationToDate(date_leap_year, tenor_4Y);

			Assert::AreEqual(29, new_date_plus_4Y.dd);
			Assert::AreEqual(2, new_date_plus_4Y.mm);
			Assert::AreEqual(2000, new_date_plus_4Y.yyyy);

		}

		TEST_METHOD(TestSubtractDurationToDate)
		{
			string date_str = "27-02-2022";
			Date date = Date(date_str);

			Date new_date_minus5D = Date::addDurationToDate(date, "-5D");

			Assert::AreEqual(22, new_date_minus5D.dd);
			Assert::AreEqual(2, new_date_minus5D.mm);
			Assert::AreEqual(2022, new_date_minus5D.yyyy);

			date_str = "01-01-2022";
			date = Date(date_str);

			new_date_minus5D = Date::addDurationToDate(date, "-5D");

			Assert::AreEqual(27, new_date_minus5D.dd);
			Assert::AreEqual(12, new_date_minus5D.mm);
			Assert::AreEqual(2021, new_date_minus5D.yyyy);

			date_str = "29-02-2004";
			date = Date(date_str);

			Date new_date_minus24M = Date::addDurationToDate(date, "-36M");

			Assert::AreEqual(28, new_date_minus24M.dd);
			Assert::AreEqual(2, new_date_minus24M.mm);
			Assert::AreEqual(2001, new_date_minus24M.yyyy);

		}

	};
}
