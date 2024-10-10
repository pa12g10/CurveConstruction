#ifndef SOLVE_H
#define SOLVER_H

#include "../curves/CurveSet.h"
#include "../instruments/InstrumentSet.h"
#include "ISolver.h"

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
	std::vector<double> initial_guess = std::vector<double>();

public:
	CurveSolver(InstrumentSet& _instrument_set, CurveSet& _curve_set, const std::string& _solver_method, const double& _solver_threshold);
	std::vector<double> operator()(std::vector<double>& _initial_guess);
	std::vector<double> objectiveFunction(std::vector<double> _initial_guess) override;
	void solve();
};

#endif // SOLVER_H
