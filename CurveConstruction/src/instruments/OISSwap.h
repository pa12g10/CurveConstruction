#ifndef OISSWAP_H
#define OISSWAP_H

#include "../src/instruments/InstrumentPricer.h"
#include "../data/CustomTypes.h"
#include "../src/utils/Date.h"

#include <functional>

using DictionaryOfFunctors = std::map<std::string, std::function<double(Date)>>;


class OISSwap : public InstrumentPricer {

private:
	VectorOfDictionaries instruments;
	Date value_date;

public:
	
	OISSwap(const Date& _value_date, VectorOfDictionaries& _ois_instruments);

	void setInstrumentMaturity(Dictionary& instrument);
	VectorOfDictionaries getInstruments() { return instruments; };

	std::vector <double> objectiveFunction() override;
	Dictionary price(const Dictionary& instrument, const DictionaryOfFunctors& rates_map) override;


};

#endif // OISSWAP_H
