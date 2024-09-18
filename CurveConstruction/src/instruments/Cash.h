#ifndef CASH_H
#define CASH_H

#include "../src/instruments/InstrumentPricer.h"
#include "../data/CustomTypes.h"

class Cash : public InstrumentPricer {

private:
	VectorOfDictionaries instruments;

public:

	Cash(){};

	std::vector <double> objectiveFunction();

};

#endif // CASH_H
