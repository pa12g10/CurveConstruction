#include "pch.h"
#include "CppUnitTest.h"
#include "../CurveConstruction/src/curves/Curve.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision


#include <interpolators/Linear.h>
#include <interpolators/CubicSpline.h>
#include <curves/CurveSet.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingCurves
{

	TEST_CLASS(Curves)
	{
	public:

		TEST_METHOD(TestCreateCurve)
		{
			Date curve_date = Date(12, 9, 2024);
			std::string tenor = "1D", currency = "GBP", exchange = "LIBOR";
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
			Date curve_date = Date(12, 9, 2024);
			std::string tenor = "1D", currency = "GBP", exchange = "LIBOR";
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
			std::vector<std::shared_ptr<Interpolator>> interpolators;

			//// Create instances of interpolators
			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));

			curve.set_knotPoints(x_vals, y_vals);
			curve.set_seperationPoints(seperation_points);
			curve.set_interpolators(interpolators);
		
			double df1 = curve(Date(12, 9, 2024));
			double df2 = curve(Date(12, 9, 2025));
			double df3 = curve(Date(12, 9, 2026));

			Assert::AreEqual(1.0, df1);
			Assert::AreEqual(.87, df2);
			Assert::AreEqual(.82, df3);
		}


		TEST_METHOD(TestCreateCurvesetSingleCurve)
		{
			Date curve_date = Date(12, 9, 2024);
			std::string currency = "GBP", exchange = "LIBOR";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			Curve curve = Curve(curve_date, "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE);
			
			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79 };

			std::vector<double> seperation_points{ 1.0 };
			std::vector<std::shared_ptr<Interpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));
			curve.set_knotPoints(x_vals, y_vals);
			curve.set_seperationPoints(seperation_points);
			curve.set_interpolators(interpolators);

			CurveSet curve_set = CurveSet({ curve });
			curve_set.configureRateMapping();

			Date date = Date(10, 1, 2025);
			auto& rate_functor_map = curve_set.get_rate_functor_map();
			auto df = rate_functor_map["IR_GBP_LIBOR_1D_DF"](date);
			auto fwd = rate_functor_map["IR_GBP_LIBOR_1D_FWD"](date);

			std::string result;
			{
				std::stringstream ss;
				ss << date.date_str << "," << std::fixed << df << "\n";
				ss << date.date_str << "," << std::fixed << fwd << "\n";
				result = ss.str();
				Logger::WriteMessage(result.c_str());
			}


		}

		TEST_METHOD(TestCreateCurvesetMultiCurve)
		{
			Date curve_date = Date(12, 9, 2024);
			std::string currency = "GBP", exchange = "LIBOR";
			CalendarKey calendar_key = CalendarKey::LON;
			BusinessDayConv bdc = BusinessDayConv::MOD_FOLLOWING;
			DayCountConv dcc = DayCountConv::ACT365;
			CurveCategory curve_category = CurveCategory::IR;
			CurveType curve_type = CurveType::DISCOUNT;
			std::vector curves = {
				Curve(curve_date,  "1D", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::DISC_BASE),
				Curve(curve_date,  "1M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				Curve(curve_date,  "3M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				Curve(curve_date,  "6M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
				Curve(curve_date, "12M", currency, exchange, calendar_key, bdc, dcc, curve_category, curve_type, CurveSplineType::TENOR),
			};

			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, .89, 0.87, 0.82, .79 };

			std::vector<double> seperation_points{ 1.0 };
			std::vector<std::shared_ptr<Interpolator>> interpolators;

			interpolators.push_back(std::make_shared<LinearInterpolator>(x_vals, y_vals));
			interpolators.push_back(std::make_shared<CubicSpline>(x_vals, y_vals));

			for (Curve& curve : curves)
			{
				curve.set_knotPoints(x_vals, y_vals);
				curve.set_seperationPoints(seperation_points);
				curve.set_interpolators(interpolators);
			}

			CurveSet curve_set = CurveSet(curves);
			curve_set.configureRateMapping();

			Date date = Date(10, 1, 2025);
			auto& rate_functor_map = curve_set.get_rate_functor_map();
			auto df = rate_functor_map["IR_GBP_LIBOR_1D_DF"](date);
			auto fwd = rate_functor_map["IR_GBP_LIBOR_1D_FWD"](date);

			std::string result;
			{
				std::stringstream ss;
				ss << date.date_str << "," << std::fixed << df << "\n";
				ss << date.date_str << "," << std::fixed << fwd << "\n";
				result = ss.str();
				Logger::WriteMessage(result.c_str());
			}


		}
	};
}