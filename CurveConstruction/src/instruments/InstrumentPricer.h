#ifndef INSTRUMENTPRICER_H
#define INSTRUMENTPRICER_H

#include "../data/CustomTypes.h"
#include "../src/utils/Date.h"

#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(Date)>>;


class InstrumentPricer {
public:
    virtual  std::vector<double> objectiveFunction() = 0;
    virtual  Dictionary price(const Dictionary& instrument, const DictionaryOfFunctors& rates_map) = 0;
    virtual ~InstrumentPricer() = default;
};

#endif // INSTRUMENTPRICER_H

