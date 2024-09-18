#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include <vector>
#include <stdexcept>
#include "Interpolator.h"

class CubicSpline : public Interpolator {
public:

    CubicSpline(const std::vector<double>& _times, const std::vector<double>& _values);

    double interpolate(double time) const override;

    void setValues(const std::vector<double>& _times, const std::vector<double>& _values) override {
        times = _times;
        values = _values;
        computeCoefficients();
    }
    std::vector<double> solve_tridiagonal(const std::vector<double>& lower, const std::vector<double>& diag, const std::vector<double>& upper, const std::vector<double>& rhs);
    void computeCoefficients();

private:
    // Vectors to hold the spline coefficients and data points
    std::vector<double> times;
    std::vector<double> values;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;
};

#endif // CUBICSPLINE_H