#include "InstrumentSet.h"


InstrumentSet::InstrumentSet(std::vector<std::shared_ptr<IInstrumentPricer>> _instrument_pricers) : instrument_pricers(_instrument_pricers)
{
	for (auto& instrument_pricer : instrument_pricers) {
		instrumentCnt += instrument_pricer->getInstruments().size();
	}
}
