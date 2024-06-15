#include "CubicSpline.h"
#include <cmath>
#include <cassert>
#include <algorithm>

CubicSpline::CubicSpline(const std::vector<double>& time, const std::vector<double>& value)
    : time_(time), value_(value) {
    if (time_.size() != value_.size()) {
        throw std::invalid_argument("The size of time and value vectors must be equal.");
    }

    size_t n = time_.size();
    a_.resize(n);
    b_.resize(n);
    c_.resize(n);
    d_.resize(n);

    std::vector<double> h(n - 1);
    for (size_t i = 0; i < n - 1; ++i) {
        h[i] = time_[i + 1] - time_[i];
    }

    std::vector<double> alpha(n);
    for (size_t i = 1; i < n - 1; ++i) {
        alpha[i] = 3.0 / h[i] * (value_[i + 1] - value_[i]) - 3.0 / h[i - 1] * (value_[i] - value_[i - 1]);
    }
    alpha[0] = 1.0;
    alpha[n - 1] = 1.0;

    std::vector<double> l(n);
    std::vector<double> mu(n);
    l[0] = 1.0;
    mu[0] = 0.0;
    for (size_t i = 1; i < n; ++i) {
        l[i] = 2.0 * (time_[i] - time_[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
    }

    c_[n - 1] = 0.0;
    for (int i = n - 2; i >= 0; --i) {
        c_[i] = (alpha[i] - h[i] * c_[i + 1]) / l[i];
    }

    for (size_t i = 0; i < n - 1; ++i) {
        b_[i] = (value_[i + 1] - value_[i]) / h[i] - h[i] * (c_[i + 1] + 2.0 * c_[i]) / 3.0;
        d_[i] = (c_[i + 1] - c_[i]) / (3.0 * h[i]);
    }
    b_[n - 1] = 0.0;
    d_[n - 1] = 0.0;
}

double CubicSpline::interpolate(double t) const {
    size_t n = time_.size();
    size_t index = std::distance(time_.begin(), std::lower_bound(time_.begin(), time_.end(), t));
    if (index == 0) {
        index = 1;
    }
    else if (index == n) {
        index = n - 1;
    }

    double h = time_[index] - time_[index - 1];
    double t_ = (t - time_[index - 1]) / h;
    double t2 = t_ * t_;
    double t3 = t2 * t_;

    return a_[index - 1] * t3 + b_[index - 1] * t2 + c_[index - 1] * t_ + d_[index - 1];
}