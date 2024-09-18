#include "CubicSpline.h"
#include <cmath>
#include <cassert>
#include <algorithm>

CubicSpline::CubicSpline(const std::vector<double>& _times, const std::vector<double>& _values)
    : times(_times), values(_values) {
    if (times.size() != values.size()) {
        throw std::invalid_argument("The size of time and value vectors must be equal.");
    }
    computeCoefficients();
}

std::vector<double> CubicSpline::solve_tridiagonal(const std::vector<double>& lower, const std::vector<double>& diag, const std::vector<double>& upper, const std::vector<double>& rhs) {
    size_t n = diag.size();
    if (lower.size() != n - 1 || upper.size() != n - 1 || rhs.size() != n) {
        throw std::invalid_argument("Vector sizes do not match for tridiagonal system.");
    }

    std::vector<double> gamma(n, 0.0), delta(n, 0.0);

    gamma[0] = upper[0] / diag[0];
    delta[0] = rhs[0] / diag[0];

    // Loop from 1 to n-1
    for (size_t i = 1; i < n - 1; ++i) {
        gamma[i] = upper[i] / (diag[i] - lower[i] * gamma[i - 1]);
        delta[i] = (rhs[i] - lower[i] * delta[i - 1]) / (diag[i] - lower[i] * gamma[i - 1]);
    }

    std::vector<double> c(n);
    c[n - 1] = delta[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        c[i] = delta[i] - gamma[i] * c[i + 1];
    }

    return c;
}

void CubicSpline::computeCoefficients() {
    size_t n = times.size();
    std::vector<double> lower(n - 1, 1.0), diag(n, 2.0), upper(n - 1, 1.0), rhs(n);
    for (size_t i = 1; i < n - 1; ++i) {
        lower[i - 1] = (times[i] - times[i - 1]) / (times[i + 1] - times[i - 1]);
        upper[i - 1] = (times[i + 1] - times[i]) / (times[i + 1] - times[i - 1]);
        rhs[i] = 3.0 * ((values[i + 1] - values[i]) / (times[i + 1] - times[i]) - (values[i] - values[i - 1]) / (times[i] - times[i - 1]));
    }

    // Natural spline boundary conditions
    rhs[0] = 0.0;
    rhs[n - 1] = 0.0;
    diag[0] = diag[n - 1] = 1.0;

    std::vector<double> c = solve_tridiagonal(lower, diag, upper, rhs);

    // Compute coefficients for each segment
    a.resize(n - 1);
    b.resize(n - 1);
    this->c.resize(n - 1);
    d.resize(n - 1);
    for (size_t i = 0; i < n - 1; ++i) {
        d[i] = (c[i + 1] - c[i]) / (3.0 * (times[i + 1] - times[i]));
        b[i] = c[i];
        a[i] = values[i];
        this->c[i] = (values[i + 1] - values[i]) / (times[i + 1] - times[i]) - (2.0 * c[i] + c[i + 1]) * (times[i + 1] - times[i]) / 3.0;
    }
}

double CubicSpline::interpolate(double time) const {
    size_t n = times.size();
    for (size_t i = 0; i < n - 1; ++i) {
        if (time < times[i + 1]) {
            double dt = time - times[i];
            return a[i] + b[i] * dt + c[i] * dt * dt + d[i] * dt * dt * dt;
        }
    }
    // If time is out of bounds, return the last or first value depending on the direction
    return time < times[0] ? values[0] : values[n - 1];
}