#ifndef INSTRUMENTSET_H
#define INSTRUMENTSET_H
#include "InstrumentPricer.h"
#include<memory>





class InstrumentSet
{

private:
	std::vector<std::shared_ptr<IInstrumentPricer>> instrument_pricers;

public:

	InstrumentSet(std::vector<std::shared_ptr<IInstrumentPricer>> _instrument_pricers);
	inline std::vector<std::shared_ptr<IInstrumentPricer>> getInstrumentPricers() { return instrument_pricers; };

	int instrumentCnt = 0;


};

#endif // INSTRUMENTSET_H