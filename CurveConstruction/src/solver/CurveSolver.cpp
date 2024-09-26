#include "solver/CurveSolver.h"

void CurveSolver::solve()
{
	auto guess = vector<double>();
	auto solver_algo = LevenbergMarquardt();
	//auto knot_points = solver_algo.solve(initial_guess, *this);
}

vector<double> CurveSolver::operator()(std::vector<double>& _initial_guess)
{
	return this->objectiveFunction(_initial_guess);
}

vector<double> CurveSolver::objectiveFunction(std::vector<double>& _initial_guess)
{
	auto residuals = vector<double>();

	// set curveset with initial guess
	//curve_set.setKnotPoints(_initial_guess);
	//curve_set

	// price each instrument set objective function to return the residuals

	return residuals;
}
