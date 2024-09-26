#ifndef ISOLVE_H
#define ISOLVER_H

#include "vector"
#include "../src/curves/CurveSet.h" 


class ISolver
{
public:
	virtual vector<double> operator()(std::vector<double>& _initial_guess) = 0;
	virtual  std::vector<double> objectiveFunction(std::vector<double>& _initial_guess) = 0;
	virtual  std::vector<double> solve(std::vector<double>& _initial_guess) = 0;
	virtual ~ISolver() = default;
};

#endif // ISOLVER_H
