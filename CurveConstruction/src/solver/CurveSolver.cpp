#include "solver/CurveSolver.h"
#include "LevenbergMarquardt.h"


void CurveSolver::solve()
{
	auto guess = vector<double>();
	auto solver_algo =  LevenbergMarquardt();
	auto knot_points = solver_algo.solve(initial_guess, *this);
}

CurveSolver::CurveSolver(InstrumentSet& _instrument_set, CurveSet& _curve_set, const std::string& _solver_method, const double& _solver_threshold) :
	instrument_set(_instrument_set), curve_set(_curve_set), solver_method(_solver_method), solver_threshold(_solver_threshold)
{
	for (size_t i = 0; i < instrument_set.instrumentCnt; i++) {
			initial_guess.push_back(0.0424* i / 365);
	}
}

vector<double> CurveSolver::operator()(std::vector<double>& _initial_guess)
{
	return this->objectiveFunction(_initial_guess);
}

std::vector<double> CurveSolver::objectiveFunction(std::vector<double> _initial_guess)
{
	auto residuals = vector<double>();

	// set curveset with initial guess
	curve_set.setKnotPoints(_initial_guess);
	auto& rate_functor_map = curve_set.get_rate_functor_map();
	// price each instrument set objective function to return the residuals
	for (auto& instrument_pricer : instrument_set.getInstrumentPricers()) {
		auto instrument_residuals = instrument_pricer->objectiveFunction(rate_functor_map);
		residuals.insert(residuals.end(), instrument_residuals.begin(), instrument_residuals.end());
	}

	return residuals;
}

