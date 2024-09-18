#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "../data/CustomTypes.h"

class Interpolator {
public:
    virtual double interpolate(double t) const = 0;
    virtual void setValues(const std::vector<double>& _times, const std::vector<double>& _values) = 0;
    virtual ~Interpolator() = default;
};

#endif // INTERPOLATOR_H