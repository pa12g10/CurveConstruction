#ifndef INSTRUMENT_DATA_H
#define INSTRUMENT_DATA_H

#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

using namespace std;

class OISSwapInstrumentStaticData {
	public:
		static vector < map<string, variant<string, double>>> get() {
			return  {

		{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "1Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
		{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "2Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
						{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "3Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
						{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "4Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
						{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "5Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
						{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "10Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
										{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "12Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
										{
			{"InstrumentType", "OISSwap"},
			{"Startdate", "0B"},
			{"Maturity", "15Y"},
			{"Fixedlegfrequency", "1Y"},
			{"Floatlegfrequency", "1Y"},
			{"Rate", 0.0342},
			{"FixedLegDCC", "A365"},
			{"FloatLegDCC", "A365"},
			{"AccrualCalendar", "LON"}

		},
			};

		};
};

class CashInstrumentStaticData {
public:
	static vector < map<string, variant<string, double>>> get() {
		return  {

	{
		{"InstrumentType", "Cash"},
		{"Startdate", "0B"},
		{"Maturity", "1B"},
		{"Rate", 0.0342},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	}};

	};
};

class CBSwapInstrumentStaticData {
public:
	static vector < map<string, variant<string, double>>> get() {
		return  {

	{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "21-03-24"},
		{"Maturity", "09-05-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	},
	{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "09-05-24"},
		{"Maturity", "20-06-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "20-06-24"},
		{"Maturity", "01-08-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "01-08-24"},
		{"Maturity", "19-09-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	},
					{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "19-09-24"},
		{"Maturity", "07-11-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}

	},
	{
		{"InstrumentType", "CBSwap"},
		{"Startdate", "07-11-24"},
		{"Maturity", "19-12-24"},
		{"Fixedlegfrequency", "1Y"},
		{"Floatlegfrequency", "1Y"},
		{"Rate", 0.0342},
		{"FixedLegDCC", "A365"},
		{"FloatLegDCC", "A365"},
		{"AccrualCalendar", "LON"}
	}
	};

	};
};

#endif // INSTRUMENT_DATA_H