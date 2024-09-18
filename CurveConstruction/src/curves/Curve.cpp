#include "Curve.h"
#include <memory>

Curve::Curve(const Date& _curve_date, const std::string& _tenor, const std::string& _currency, const std::string& _exchange, const CalendarKey& _calendar_key,
	const BusinessDayConv _bdc, const DayCountConv _dcc, const CurveCategory _curve_category, const CurveType _curve_type,
	const CurveSplineType _curve_spline_type)
	: curve_date(_curve_date), tenor(_tenor), currency(_currency), exchange(_exchange), calendar_key(_calendar_key), bdc(_bdc), dcc(_dcc),
	curve_category(_curve_category), curve_type(_curve_type), curve_spline_type(_curve_spline_type)
{
	name = "IR_" + currency + "_" + exchange + "_" + tenor;
	is_base = (curve_spline_type == CurveSplineType::BASE || curve_spline_type == CurveSplineType::DISC_BASE) ? true : false;
}


double Curve::operator()(const Date& date)
{
	double t = Date::yearFraction(curve_date, date, dcc);
	return this->operator()(t);
}

double Curve::operator()(const double& t) 
{
	// Recursive calling of Operator function needs to be fixed!
	if (curve_values.find(t) != curve_values.end()) {
		return curve_values[t];
	}

	size_t index = 0;
	auto it = std::lower_bound(seperation_points.begin(), seperation_points.end(), t);
	if (it != seperation_points.end()) {
		index = std::distance(seperation_points.begin(), it);
	}
	curve_values[t] = interpolators[index]->interpolate(t);

	return curve_values[t];

}

