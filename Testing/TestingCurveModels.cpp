#include "pch.h"
#include "CppUnitTest.h"
#include "../CurveConstruction/src/curves/Curve.h"
#include "../CurveConstruction/data/CustomTypes.h"
#include "../CurveConstruction/data/InstrumentData.h"
#include "../CurveConstruction/data/CurveData.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision
#include <curve_models/RFRModel.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingCurveModels
{

	TEST_CLASS(CurveModels)
	{
	public:

		TEST_METHOD(TestRFRModel)
		{
			std::map<std::string, DictionaryOfVectors> curve_data = rfr_model_curve_data;
			std::vector<VectorOfDictionaries> instrument_data = {
				cash_instrument_data,
				ois_swap_instrument_data,
				cbswap_instrument_data
			};
			RFRModel rfr_model = RFRModel(instrument_data, curve_data);
		}
	};
}