#ifndef CURVESET_H
#define CURVESET_H

#include "../data/CustomTypes.h"
#include "../src/curves/Curve.h"
#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(Date)>>;

class CurveSet
{
private:
	std::map<std::string, Curve> curve_map;
	std::vector<Curve> curves;
	std::map<std::string, std::function<double(Date)>> rate_functor_map;


public:
	CurveSet(const std::vector<Curve>& _curves) : curves(_curves) {};


	void configureRateMapping();
	std::map<std::string, std::function<double(Date)>>& get_rate_functor_map() { return rate_functor_map; };
	static double getDiscountFactor(const Date& discount_date, Curve& curve);
	static double getForwardRate(const Date& reset_start_date, Curve& curve);
	static double getForwardRate(const Date& reset_start_date, Curve& curve, Curve& spread_curve);
};


#endif // CURVESET_H

