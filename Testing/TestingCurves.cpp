#include "pch.h"
#include "CppUnitTest.h"
#include "../CurveConstruction/src/curves/Curve.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision
#include <memory>

#include <interpolators/Linear.h>
#include <interpolators/CubicSpline.h>
#include <curves/CurveSet.h>
#include <instruments/OISSwap.h>
#include "../CurveConstruction/data/InstrumentData.h"
#include "../CurveConstruction/src/instruments/InstrumentSet.h"
#include <solver/CurveSolver.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingCurves
{

	TEST_CLASS(Curves)
	{
	public:

		TEST_METHOD(TestCreateCurve)
		{
			int curve_date = 20240912;
			std::string tenor = "1D", currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			CurveSplineType curve_spline_type = CurveSplineType::DISC_BASE;

			Curve* curve = new Curve(curve_date, tenor, currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, curve_spline_type);
			Assert::IsNotNull(curve);
			delete curve;
		}


		TEST_METHOD(TestSetCurveInterpolators)
		{
			int curve_date = 20240912; 
			std::string tenor = "1D", currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			CurveSplineType curve_spline_type = CurveSplineType::DISC_BASE;

			Curve curve = Curve(curve_date, tenor, currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, curve_spline_type);

			std::vector<double> x_vals{0 , 0.25, 0.5, 0.75, 1, 2, 3};
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79};

			std::vector<double> seperation_points{1.0};
			std::vector<std::shared_ptr<IInterpolator>> interpolators;

			//// Create instances of interpolators
			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));

			curve.set_knotPoints(x_vals, y_vals);
			curve.set_seperationPoints(seperation_points);
			curve.set_interpolators(interpolators);
		
			int date1 = 20240912;
			int date2 = 20250912;
			int date3 = 20260912;

			double df1 = curve(date1);
			double df2 = curve(date2);
			double df3 = curve(date3);

			Assert::AreEqual(1.0, df1);
			Assert::AreEqual(.87, df2);
			Assert::AreEqual(.82, df3);
		}


		TEST_METHOD(TestCreateCurvesetSingleCurve)
		{
			int curve_date = 20240912; 
			std::string currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			auto curve = std::make_shared<Curve>(curve_date, "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE);
			
			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79 };

			std::vector<double> seperation_points{ 1.0 };
			std::vector<std::shared_ptr<IInterpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));
			curve->set_knotPoints(x_vals, y_vals);
			curve->set_seperationPoints(seperation_points);
			curve->set_interpolators(interpolators);

			CurveSet curve_set = CurveSet({ curve });
			curve_set.configureRateMapping();

			int date = 20250110; 
			auto& rate_functor_map = curve_set.get_rate_functor_map();
			auto df = rate_functor_map["IR_GBP_SONIA_1D_DF"](date);
			auto fwd = rate_functor_map["IR_GBP_SONIA_1D_FWD"](date);

			std::string result;
			{
				std::stringstream ss;
				ss << DateUtilities::toString(date) << "," << std::fixed << df << "\n";
				ss << DateUtilities::toString(date) << "," << std::fixed << fwd << "\n";
				result = ss.str();
				Logger::WriteMessage(result.c_str());
			}


		}

		TEST_METHOD(TestCreateCurvesetMultiCurve)
		{
			int curve_date = 20240912;  
			std::string currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			std::vector curves = {
				std::make_shared<Curve>(curve_date,  "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE),
				std::make_shared<Curve>(curve_date,  "1M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				std::make_shared<Curve>(curve_date,  "3M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				std::make_shared<Curve>(curve_date,  "6M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				std::make_shared<Curve>(curve_date, "12M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
			};

			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79 };

			std::vector<double> seperation_points{ 1.0 };
			std::vector<std::shared_ptr<IInterpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));

			for (auto& curve : curves)
			{
				curve->set_knotPoints(x_vals, y_vals);
				curve->set_seperationPoints(seperation_points);
				curve->set_interpolators(interpolators);
			}

			CurveSet curve_set = CurveSet(curves);
			curve_set.configureRateMapping();

			int date = 20250110; 
			auto& rate_functor_map = curve_set.get_rate_functor_map();
			auto df = rate_functor_map["IR_GBP_SONIA_1D_DF"](date);
			auto fwd = rate_functor_map["IR_GBP_SONIA_1D_FWD"](date);

			std::string result;
			{
				std::stringstream ss;
				ss << DateUtilities::toString(date) << "," << std::fixed << df << "\n";
				ss << DateUtilities::toString(date) << "," << std::fixed << fwd << "\n";
				result = ss.str();
				Logger::WriteMessage(result.c_str());
			}
		}

		TEST_METHOD(TestCurveSolver) {

			// Instrument Set Up
			int curve_date = 20240912;
			auto ois_swap_set = OISSwapPricer(curve_date, ois_swap_instrument_data);
			auto ois_swap_instruments = ois_swap_set.getInstruments();

			std::vector<double> x_vals;
			std::vector<double> y_vals;

			for (auto& instrument : ois_swap_instruments)
			{
				int maturity_date = getValueFromVariant<int>(instrument["MaturityDate"]);
				double knot_year_fraction = DateUtilities::yearFraction(curve_date, maturity_date, DayCountConv::ACT365);
				x_vals.push_back(knot_year_fraction);
				y_vals.push_back(0.03);
			}

			// Need to fix
			std::vector<std::shared_ptr<IInstrumentPricer>> instrument_set_pricers;

			//// Create instances of interpolators
			instrument_set_pricers.push_back(std::make_shared<OISSwapPricer>(ois_swap_set));
			InstrumentSet instrument_set = InstrumentSet(instrument_set_pricers);

			// Curve Set Up
			std::string currency = "GBP", exchange = "SONIA";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			std::shared_ptr<Curve> curve = std::make_shared<Curve>(curve_date, "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE);

			std::vector<double> seperation_points{ 2.0 };
			std::vector<std::shared_ptr<IInterpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));
			curve->set_knotPoints(x_vals, y_vals);
			curve->set_seperationPoints(seperation_points);
			curve->set_interpolators(interpolators);

			CurveSet curve_set = CurveSet({ curve });
			curve_set.configureRateMapping();
			auto& rate_functor_map = curve_set.get_rate_functor_map();

			// Solver 

			auto solver = std::make_shared<CurveSolver>(instrument_set, curve_set, "LM", 1e-12);
			solver->solve();

			// print Knot Points
			auto x_values = curve->get_xValues();
			auto y_values = curve->get_yValues();

			for (size_t i = 0; i < x_values.size(); i++)
			{
				std::string result;
				{
					std::stringstream ss;
					ss << "x," << x_values[i] << ",y," << y_values[i] << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}

			auto instrument_residuals = instrument_set_pricers[0]->objectiveFunction(rate_functor_map);
			for (size_t i = 0; i < instrument_residuals.size(); i++)
			{
				std::string result;
				{
					std::stringstream ss;
					ss << "x," << x_values[i] << ",par-calc_par," << instrument_residuals[i] << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}

		}

	};
}