#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <iostream>
#include <fstream>
#include <vector>

#include "../data/instrument_data.h"

using namespace std;

int main() {

	
	std::cout <<  _MSC_VER << endl;
	std::cout << "Hello world!!" << endl;

	string valuation_date = "03-06-2024";

	auto ois_cash = CashInstrumentStaticData().get();
	auto ois_swaps = OISSwapInstrumentStaticData().get();
	auto cb_swaps = CBSwapInstrumentStaticData().get();

	double rate_1 = std::get<double>(ois_cash[0]["Rate"]);
	cout << rate_1 << endl;


	return 0;
}