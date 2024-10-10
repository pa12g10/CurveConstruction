#ifndef CURVESET_H
#define CURVESET_H

#include "../data/CustomTypes.h"
#include "../src/curves/Curve.h"
#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(int)>>;

class CurveSet
{
private:
	std::map<std::string, Curve> curve_map;
	std::vector<std::shared_ptr<Curve>> curves;
	std::map<std::string, std::function<double(int)>> rate_functor_map;
	bool is_rates_map_configured = false;


public:
	CurveSet(const std::vector<std::shared_ptr<Curve>>& _curves) : curves(_curves) {};


	void configureRateMapping();
	std::map<std::string, std::function<double(int)>>& get_rate_functor_map() { return rate_functor_map; };
	void setKnotPoints(const vector<double>& _initial_guess);

	static double getDiscountFactor(const int& discount_date, Curve& curve);
	static double getForwardRate(const int& reset_start_date, Curve& curve);
	static double getForwardRate(const int& reset_start_date, Curve& curve, Curve& spread_curve);

};


#endif // CURVESET_H

