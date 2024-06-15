#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include <vector>
#include <stdexcept>

class CubicSpline {
public:
    CubicSpline(const std::vector<double>& time, const std::vector<double>& value);
    double interpolate(double t) const;

private:
    std::vector<double> time_;
    std::vector<double> value_;
    std::vector<double> a_;
    std::vector<double> b_;
    std::vector<double> c_;
    std::vector<double> d_;
};

#endif // CUBICSPLINE_H