#include "../src/curve_models/RFRModel.h"
#include "../src/curves/Curve.h"
#include "../src/curves/CurveSet.h"

RFRModel::RFRModel(const std::vector<VectorOfDictionaries>& _instrument_data,
	const std::map<std::string, DictionaryOfVectors>& _curve_data)
	: curve_data(_curve_data), instrument_data(_instrument_data) 
{
	for (const auto& pair : curve_data) {
		auto tenor = pair.first;
		auto curve_dict = pair.second ;
		int a = 1;
	}




}