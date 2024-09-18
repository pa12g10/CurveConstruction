#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <iostream>
#include <fstream>
#include <vector>

#include "../data/InstrumentData.h"

using namespace std;

int main() {

	
	std::cout <<  _MSC_VER << endl;
	std::cout << "Hello world!!" << endl;

	string valuation_date = "03-06-2024";

	double rate_1 = std::get<double>(ois_swap_instrument_data[0]["Rate"]);
	cout << rate_1 << endl;


	return 0;
}