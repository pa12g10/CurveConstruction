#include "InstrumentData.h"
// Market Rates taken from https://www.chathamfinancial.com/technology/European-market-rates with value date 19th September for Swaps, ON Deposit 17th September 
 

VectorOfDictionaries ois_swap_instrument_data = {
		{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "1Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.04258},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B"},
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
		{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "2Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03831},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
		{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "3Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03663},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{ "PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
		{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "5Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03514},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
	{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "7Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03470},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
		{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "10Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03506},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
										{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "15Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03616},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		},
										{
			{"InstrumentType", "OISSwap"},
			{"StartDate", "0B"},
			{"Maturity", "30Y"},
			{"FixedLegFrequency", "1Y"},
			{"FloatLegFrequency", "1Y"},
			{"Rate", 0.03648},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"},
			{"FixingCalendar", "LON"},
			{"PayDelay", "0B" },
			{"ReferenceRate", "1D"},
			{"Currency", "GBP"},
			{"Exchange", "SONIA"},
			{"RollConvention", "BEOM"},
			{"BusinessDayConvention", "ModifiedFollowing"},
			{"StubType", "SS"},
			{"TargetCurveSpline" , "1D"}

		}
};

VectorOfDictionaries cash_instrument_data = {
	{
		{"InstrumentType", "Cash"},
		{"StartDate", "0B"},
		{"Maturity", "1B"},
		{"Rate", 0.0495},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"},
		{"PayDelay", "0B" },
		{"ReferenceRate", "1D"},
		{"Currency", "GBP"},
		{"Exchange", "SONIA"},
		{"RollConvention", "BEOM"},
		{"BusinessDayConvention", "ModifiedFollowing"},
		{"StubType", "SS"},
		{"TargetCurveSpline" , "1D"}

	}
};

VectorOfDictionaries cbswap_instrument_data = {
	{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "21-03-24"},
		{"Maturity", "09-05-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}

	},
	{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "09-05-24"},
		{"Maturity", "20-06-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "20-06-24"},
		{"Maturity", "01-08-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "01-08-24"},
		{"Maturity", "19-09-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "19-09-24"},
		{"Maturity", "07-11-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}

	},
	{
		{"InstrumentType", "CBSwap"},
		{"StartDate", "07-11-24"},
		{"Maturity", "19-12-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"},
		{"FixingCalendar", "LON"}
	}
};