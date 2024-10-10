#include "LevenbergMarquardt.h"

std::vector<std::vector<double>> LevenbergMarquardt::computeJacobian(const std::vector<double>& params, 
    ISolver& solver_obj_ref)
{
    std::vector<std::vector<double>> J(params.size(), std::vector<double>(params.size(), 0.0));
    auto orig_residuals = solver_obj_ref.objectiveFunction(params);
    for (size_t i = 0; i < params.size(); ++i) {
        auto bumped_params = params;
        bumped_params[i] = params[i] + _1BASIS_POINT;
        auto bumped_residuals = solver_obj_ref.objectiveFunction(bumped_params);
        for (size_t j = 0; j < params.size(); ++j) {
            J[i][j] = (bumped_residuals[j]- orig_residuals[j]) / _1BASIS_POINT; // Simplified assumption: derivative is 1 for matching indices
        }
        
    }
    return J;
}

std::vector<double> LevenbergMarquardt::matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<double>& B) {
    std::vector<double> result(A.size(), 0.0); 
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[0].size(); ++j) {
            result[i] += A[i][j] * B[j];
        }
    }
    return result;
}

std::vector<std::vector<double>> LevenbergMarquardt::matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
    std::vector<std::vector<double>> result(A.size(), std::vector<double>(B[0].size(), 0.0));
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B[0].size(); ++j) {
            for (size_t k = 0; k < A[0].size(); ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

std::vector<std::vector<double>> LevenbergMarquardt::matrixTranspose(const std::vector<std::vector<double>>& A)
{
    std::vector<std::vector<double>> result(A[0].size(), std::vector<double>(A.size(), 0.0));
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[0].size(); ++j) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}

std::vector<std::vector<double>> LevenbergMarquardt::matrixAdd(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B)
{
    std::vector<std::vector<double>> result(A.size(), std::vector<double>(A[0].size(), 0.0));
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

std::vector<double> LevenbergMarquardt::solveLinearSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& b)
{
    int n = A.size();
    std::vector<std::vector<double>> augmented = A;
    for (int i = 0; i < n; ++i) {
        augmented[i].push_back(b[i]);
    }

    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(augmented[k][i]) > std::abs(augmented[maxRow][i])) {
                maxRow = k;
            }
        }
        std::swap(augmented[i], augmented[maxRow]);

        for (int k = i + 1; k < n; ++k) {
            double factor = augmented[k][i] / augmented[i][i];
            for (int j = i; j <= n; ++j) {
                augmented[k][j] -= augmented[i][j] * factor;
            }
        }
    }

    std::vector<double> solution(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += solution[j] * augmented[i][j];
        }
        solution[i] = (augmented[i][n] - sum) / augmented[i][i];
    }

    return solution;
}

std::vector<double> LevenbergMarquardt::solve(std::vector<double>& initial_guess, ISolver& solver_obj_ref)
{
    std::vector<double> params = initial_guess;
    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        std::vector<double> residuals = solver_obj_ref.objectiveFunction(params);
        std::vector<std::vector<double>> J = computeJacobian(params, solver_obj_ref);
        std::vector<std::vector<double>> Jt = matrixTranspose(J);
        std::vector<std::vector<double>> JtJ = matrixMultiply(Jt, J);
        std::vector<std::vector<double>> I(JtJ.size(), std::vector<double>(JtJ[0].size(), 0.0));
        for (size_t i = 0; i < I.size(); ++i) {
            I[i][i] = lambda;
        }
        std::vector<std::vector<double>> H = matrixAdd(JtJ, I);
        std::vector<double> r = matrixMultiply(Jt, residuals);

        // Solve for the increment
        std::vector<double> dp = solveLinearSystem(H, r);

        // Update parameters
        for (size_t i = 0; i < params.size(); ++i) {
            params[i] -= dp[i];
        }

        // Check for convergence
        if (std::inner_product(dp.begin(), dp.end(), dp.begin(), 0.0) < EPSILON * EPSILON) {
            break;
        }

        // Adjust lambda (simplified)
        std::vector<double> new_residuals = solver_obj_ref.objectiveFunction(params);
        if (std::inner_product(new_residuals.begin(), new_residuals.end(), new_residuals.begin(), 0.0) <
            std::inner_product(residuals.begin(), residuals.end(), residuals.begin(), 0.0)) {
            lambda /= 10.0;
        }
        else {
            lambda *= 10.0;
        }

        iterations++;
    }

    return params;
}
