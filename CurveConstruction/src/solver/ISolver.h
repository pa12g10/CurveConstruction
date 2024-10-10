#ifndef ISOLVER_H
#define ISOLVER_H

#include <vector>

class ISolver {

public:
	virtual void solve() = 0;
	virtual std::vector<double> objectiveFunction(std::vector<double> guess) = 0;
	virtual ~ISolver() = default;

};

#endif // ISOLVER_H