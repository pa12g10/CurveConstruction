#include "pch.h"
#include "CppUnitTest.h"
#include "data/instrument_data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(InputData)
	{
	public:
		
		TEST_METHOD(TestInstrumentDataLoads)
		{
			auto ois_cash = CashInstrumentStaticData().get();
			auto ois_swaps = OISSwapInstrumentStaticData().get();
			auto cb_swaps = CBSwapInstrumentStaticData().get();

			int cash_size = ois_cash.size();
			int oisswaps_size = ois_swaps.size();
			int cbswaps_size = cb_swaps.size();

			Assert::AreEqual(1, cash_size);
			Assert::AreEqual(8, oisswaps_size);
			Assert::AreEqual(6, cbswaps_size);
			
		}
	};
}
