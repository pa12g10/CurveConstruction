#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "../data/CustomTypes.h"

class IInterpolator {
public:
    virtual double interpolate(double t) const = 0;
    virtual void setValues(const std::vector<double>& _times, const std::vector<double>& _values) = 0;
    virtual ~IInterpolator() = default;
};

#endif // INTERPOLATOR_H