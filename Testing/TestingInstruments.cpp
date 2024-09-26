#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision

#include "../data/InstrumentData.h"
#include "../src/instruments/OISSwap.h"
#include <curves/Curve.h>
#include <curves/CurveSet.h>
#include <interpolators/Linear.h>
#include <interpolators/CubicSpline.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingInstruments
{

	TEST_CLASS(OISSwaps)
	{
	public:

		TEST_METHOD(TestOISSwapDateSetting)
		{

			auto value_date = 20240916;
			auto ois_swap_set = OISSwapPricer(value_date, ois_swap_instrument_data);
			auto ois_swap_instruments = ois_swap_set.getInstruments();
			Logger::WriteMessage("instrument effective date, instrument unadjusted maturity");
			for (auto& instrument : ois_swap_instruments) {
				std::string result;
				{
					std::stringstream ss;
					ss  << getValueFromVariant<int>(instrument["EffectiveDate"])
						<< "," 
						<< getValueFromVariant<int>(instrument["UnadjustedMaturityDate"]) << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}
		}

		TEST_METHOD(TestOISSwapPricer)
		{

			// Curve Set Up
			int curve_date = 20240912;
			std::string currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			Curve curve = Curve(curve_date, "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE);

			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79 };

			std::vector<double> seperation_points{ 1.0 };
			std::vector<std::shared_ptr<IInterpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));
			curve.set_knotPoints(x_vals, y_vals);
			curve.set_seperationPoints(seperation_points);
			curve.set_interpolators(interpolators);

			CurveSet curve_set = CurveSet({ curve });
			curve_set.configureRateMapping();
			auto& rate_functor_map = curve_set.get_rate_functor_map();

			// Instrument Pricing 
			Dictionary instrument_results = Dictionary();
			auto ois_swap_pricer = OISSwapPricer(curve_date, ois_swap_instrument_data);
			auto ois_swap_instruments = ois_swap_pricer.getInstruments();
			Logger::WriteMessage("Maturity, CalculatedRate, InstrumentRate \n");
			for (auto& instrument : ois_swap_instruments) {
				std::string result;
				{
					instrument_results = ois_swap_pricer.price(instrument, rate_functor_map);
					std::stringstream ss;
					ss << getValueFromVariant<std::string>(instrument["Maturity"])
						<< ","
						<< getValueFromVariant<double>(instrument["Rate"])
						<< ","
						<< getValueFromVariant<double>(instrument_results["CalculatedRate"]) << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}
		}


	};
}