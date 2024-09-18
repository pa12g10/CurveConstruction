#ifndef RFRMODEL_H
#define RFRMODEL_H

#include "../data/CustomTypes.h"

class RFRModel {
public:

	std::map<std::string, DictionaryOfVectors> curve_data;
	std::vector<VectorOfDictionaries> instrument_data;

	RFRModel(const std::vector<VectorOfDictionaries>& _instrument_data,
		const std::map<std::string, DictionaryOfVectors>& _curve_data);

};


#endif // RFRMODEL_H