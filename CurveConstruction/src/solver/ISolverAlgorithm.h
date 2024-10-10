#ifndef ISOLVER_ALGORITHM
#define ISOLVER_ALGORITHM

#include <vector>
#include "Isolver.h"

class ISolverAlgorithm {

public:
	virtual std::vector<double> solve(std::vector<double>& initial_guess, ISolver& solver_obj) = 0;
	virtual ~ISolverAlgorithm() = default;

};

#endif // ISOLVER_ALGORITHM