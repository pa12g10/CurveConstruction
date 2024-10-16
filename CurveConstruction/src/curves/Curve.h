#ifndef CURVE_H 
#define CURVE_H

#include "../data/Enums.h"
#include <interpolators/Interpolator.h>
#include "../src/utils/DateUtilities.h"


class Curve
{
private:
	std::vector <double> y_values;
	std::vector <double> x_values;
	std::map<double, double> curve_values;
	std::vector <double> seperation_points;

public:
	int curve_date;
	std::string name = "";
	std::string tenor = "";
	std::string currency = "";
	std::string exchange = "";
	CalendarKey calendar_key = CalendarKey::NONE;
	BusinessDayConv bdc =  BusinessDayConv::NONE;
	DayCountConv dcc = DayCountConv::NONE;
	CurveCategory curve_category = CurveCategory::NONE;
	CurveType curve_type = CurveType::NONE;
	CurveSplineType curve_spline_type = CurveSplineType::NONE;
	std::vector<std::shared_ptr<IInterpolator>> interpolators;
	bool is_base = false;


	Curve(const int& curve_date, const std::string& tenor, const std::string& currency, const std::string& exchange, const CalendarKey& calendar_key,
		const BusinessDayConv& bdc, const DayCountConv& dcc, const CurveCategory& curve_category, const CurveType& curve_type,
		const CurveSplineType& curve_spline_type);

	// Copy Constructor
	//Curve(const Curve& other) {}

	// Recursive calling of Operator function needs to be fixed!
	double operator()(const double& t);
	double operator()(const int& date);

	// Setters
	inline void set_seperationPoints(std::vector <double> _seperation_points) { seperation_points = _seperation_points; };
	inline void set_xValues(std::vector <double> _x_values) { y_values = _x_values; };
	inline void set_yValues(std::vector <double> _y_values) { y_values = _y_values; };
	inline void set_interpolators(const std::vector<std::shared_ptr<IInterpolator>>& _interpolators) { interpolators =_interpolators;};
	inline void resetCurveCache() { curve_values = std::map<double, double>(); };

	// Getters
	inline std::vector <double> get_xValues() { return x_values; };
	inline std::vector <double> get_yValues() { return y_values; };

	void set_knotPoints(const std::vector <double>& _x_values, std::vector <double>& _y_values) {
		x_values =  _x_values;
		y_values = _y_values;
	};

	void set_interpolator_values() {
		for (const auto& interpolator : interpolators)
		{
			interpolator->setValues(x_values, y_values);
		}
	};

};

#endif // CURVE_H

