#ifndef INSTRUMENTPRICER_H
#define INSTRUMENTPRICER_H

#include "../data/CustomTypes.h"
#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(int)>>;


class IInstrumentPricer {
public:
    virtual  std::vector<double> objectiveFunction(DictionaryOfFunctors& _rates_map) = 0;
    virtual  Dictionary price(Dictionary& instrument, DictionaryOfFunctors& _rates_map) = 0;
    virtual ~IInstrumentPricer() = default;
};

#endif // INSTRUMENTPRICER_H

