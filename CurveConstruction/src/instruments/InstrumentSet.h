#ifndef INSTRUMENTSET_H
#define INSTRUMENTSET_H
#include "InstrumentPricer.h"
#include<memory>





class InstrumentSet
{

private:

	std::vector<std::shared_ptr<IInstrumentPricer>> instrument_pricers;

public:

	InstrumentSet(std::vector<std::shared_ptr<IInstrumentPricer>> instrument_pricers);



};

#endif // INSTRUMENTSET_H