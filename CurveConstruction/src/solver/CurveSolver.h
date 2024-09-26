#ifndef SOLVE_H
#define SOLVER_H

#include "../curves/CurveSet.h"
#include "../instruments/InstrumentSet.h"
#include "LevenbergMarquardt.h"
#include <vector>
#include <cmath>
#include <iostream>


class CurveSolver : public ISolver
{
private:
	InstrumentSet instrument_set;
	CurveSet curve_set;
	std::string solver_method;
	double solver_threshold;
	vector<double> initial_guess = vector<double>();

public:
	CurveSolver(InstrumentSet& _instrument_set, CurveSet& _curve_set, const std::string& _solver_method, const double& _solver_threshold) :
		instrument_set(_instrument_set), curve_set(_curve_set), solver_method(_solver_method), solver_threshold(_solver_threshold) {};
	void solve();
	vector<double> operator()(std::vector<double>& _initial_guess) override;
	vector<double> objectiveFunction(std::vector<double>& _initial_guess) override;
};

#endif // SOLVER_H
