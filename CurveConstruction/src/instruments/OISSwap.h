#ifndef OISSWAP_H
#define OISSWAP_H

#include "../src/instruments/InstrumentPricer.h"
#include "../data/CustomTypes.h"
#include "../src/cashflows/CashflowScheduler.h"
#include "../src/utils/DateUtilities.h"

#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(int)>>;


class OISSwapPricer : public IInstrumentPricer {

private:
	VectorOfDictionaries instruments;
	int value_date;

public:
	
	OISSwapPricer(const int& _value_date, VectorOfDictionaries& _ois_instruments);

	void setInstrumentMaturity(Dictionary& instrument);

	std::vector <double> objectiveFunction(DictionaryOfFunctors& _rates_map) override;
	Dictionary getCurveKeys(Dictionary& instrument);
	Dictionary price(Dictionary& instrument, DictionaryOfFunctors& _rates_map) override;
	inline VectorOfDictionaries getInstruments() override { return instruments; };



};

#endif // OISSWAP_H
