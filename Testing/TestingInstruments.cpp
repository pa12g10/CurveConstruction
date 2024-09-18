#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision

#include "../data/InstrumentData.h"
#include "../src/instruments/OISSwap.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingInstruments
{

	TEST_CLASS(OISSwaps)
	{
	public:

		TEST_METHOD(TestOISSwapDateSetting)
		{

			auto value_date = Date(16, 9, 2024);
			auto ois_swap_set = OISSwap(value_date, ois_swap_instrument_data);
			auto ois_swap_instruments = ois_swap_set.getInstruments();
			Logger::WriteMessage("instrument effective date, instrument unadjusted maturity");
			for (auto& instrument : ois_swap_instruments) {
				std::string result;
				{
					std::stringstream ss;
					ss  << getValueFromVariant<std::string>(instrument["EffectiveDate"])
						<< "," 
						<< getValueFromVariant<std::string>(instrument["UnadjustedMaturityDate"]) << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}
		}


	};
}