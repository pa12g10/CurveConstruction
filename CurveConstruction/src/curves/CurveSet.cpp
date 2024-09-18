#include "CurveSet.h"
#include <memory>

void CurveSet::configureRateMapping()
{
	auto it = std::find_if(curves.begin(), curves.end(),
		[](const Curve& curve) { return curve.is_base == true; });
	
	int index = 0;
	if (it != curves.end()) {
		int index = std::distance(curves.begin(), it);
	}
	else {
		throw std::invalid_argument("Cannot find a base curve in the input curves vector.");
	};

	Curve base_curve = curves[index];

	for (Curve& curve : curves)
	{
		if (curve.curve_spline_type == CurveSplineType::DISCOUNT || curve.curve_spline_type == CurveSplineType::DISC_BASE) {
			rate_functor_map[curve.name + "_DF"] = [&](const Date& date) {
				return CurveSet::getDiscountFactor(date, curve);
				};
			rate_functor_map[curve.name + "_FWD"] = [&](const Date& date) {
				return CurveSet::getForwardRate(date, curve);
				};
		}
		else if (curve.curve_spline_type == CurveSplineType::TENOR) {
			rate_functor_map[curve.name + "_FWD"] = [&](const Date& date) {
				return CurveSet::getForwardRate(date, base_curve, curve);
				};
		}
		else {
			throw std::invalid_argument("Curve spline type not recognised cannot allocate rate mapping!");
		}

	}
}

double CurveSet::getDiscountFactor(const Date& discount_date, Curve& curve)
{
	return curve(discount_date);
}

double CurveSet::getForwardRate(const Date& reset_start_date, Curve& curve)
{
	Date reset_end_date = reset_start_date.addDurationBusinessDay(curve.tenor, curve.calendar_key, curve.bdc);

	auto df_start = curve(reset_start_date);
	auto df_end = curve(reset_end_date);

	double year_fraction = Date::yearFraction(reset_start_date, reset_end_date, curve.dcc);
	double fwd = 1 / year_fraction * (df_start / df_end - 1);
	return fwd;
}

double CurveSet::getForwardRate(const Date& reset_start_date, Curve& curve,Curve& spread_curve)
{
	Date reset_end_date = reset_start_date.addDurationBusinessDay(curve.tenor, curve.calendar_key, curve.bdc);
	
	auto df_start = curve(reset_start_date);
	auto df_end = curve(reset_end_date);

	double year_fraction = Date::yearFraction(reset_start_date, reset_end_date, curve.dcc);
	double fwd = 1 / year_fraction * (df_start / df_end - 1);
	return fwd + spread_curve(reset_start_date);
}

