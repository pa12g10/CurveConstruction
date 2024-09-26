#ifndef LINEAR_H
#define LINEAR_H

#include "../data/CustomTypes.h"
#include "../interpolators/Interpolator.h"

#include <algorithm>
#include <stdexcept>

class LinearInterpolator : public IInterpolator {
public:

    LinearInterpolator(const std::vector<double>& _times, const std::vector<double>& _values)
        : times(_times), values(_values) {
        if (times.size() != values.size()) {
            throw std::invalid_argument("Times and values vectors must have the same size");
        }
        if (times.size() < 2) {
            throw std::invalid_argument("At least two points are required for interpolation");
        }
        // Ensure times are in ascending order
        if (!std::is_sorted(times.begin(), times.end())) {
            throw std::invalid_argument("Times must be in ascending order");
        }
    }

    double interpolate(double t) const override {
        // Handle edge cases
        if (t <= times.front()) return values.front();
        if (t >= times.back()) return values.back();

        // Find the correct interval
        auto it = std::lower_bound(times.begin(), times.end(), t);
        if (it == times.end()) return values.back();

        size_t index = std::distance(times.begin(), it);
        if (index == 0) return values.front();

        // Perform linear interpolation
        double t0 = times[index - 1];
        double t1 = times[index];
        double v0 = values[index - 1];
        double v1 = values[index];

        return v0 + (v1 - v0) * (t - t0) / (t1 - t0);
    }

    void setValues(const std::vector<double>& _times, const std::vector<double>& _values) override {
        times = _times;
        values = _values;
    }

private:
    std::vector<double> times;
    std::vector<double> values;
};
#endif // LINEAR_H



