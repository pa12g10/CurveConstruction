#ifndef  LEVENBERGMARQUARDT_H 
#define  LEVENBERGMARQUARDT_H 

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include "../solver/ISolver.h"
#include "../solver/ISolverAlgorithm.h"


class LevenbergMarquardt : public ISolverAlgorithm {
private:
    double EPSILON = 1e-6;
    double _1BASIS_POINT = 1e-5;
    int MAX_ITERATIONS = 1000;
    double lambda = 0.01;

    std::vector<std::vector<double>> computeJacobian(const std::vector<double>& params, ISolver& solver_obj_ref);
    std::vector<double> matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<double>& B);
    std::vector<std::vector<double>> matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B);
    std::vector<std::vector<double>> matrixTranspose(const std::vector<std::vector<double>>& A);
    std::vector<std::vector<double>> matrixAdd(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B);
    std::vector<double> solveLinearSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& b);

public:
    LevenbergMarquardt(const double& _epsilion = 1e-6, const int& _max_iterations = 1000, const double& _lambda = 0.01) : EPSILON(_epsilion), 
        MAX_ITERATIONS(_max_iterations), lambda(_lambda) {};
    std::vector<double> solve(std::vector<double>& initial_guess, ISolver& solver_obj_ref);
};
#endif // LEVENBERGMARQUARDT_H 
