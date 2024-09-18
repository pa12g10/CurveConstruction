#include "CurveData.h"

std::map<std::string, DictionaryOfVectors> rfr_model_curve_data = {
		{"1D",
			{
				{"Interpolators", {"Linear", "Cubic"}},
				{"SeperationPoints", {"3Y"} },
				{"DayCount", {"A365"}},
				{"Currency", {"GBP"}},
				{"Calendar", {"LON"}},
			}
		},
		{"1M",
			{
				{"Interpolators", {"Linear", "Cubic"}},
				{"SeperationPoints", {"3Y"} },
				{"DayCount", {"A365"}},
				{"Currency", {"GBP"}},
				{"Calendar", {"LON"}},
			}
		},
		{"3M",
			{
				{"Interpolators", {"Linear", "Cubic"}},
				{"SeperationPoints", {"3Y"} },
				{"DayCount", {"A365"}},
				{"Currency", {"GBP"}},
				{"Calendar", {"LON"}},
			}
		},
		{"6M",
			{
				{"Interpolators", {"Linear", "Cubic"}},
				{"SeperationPoints", {"3Y"} },
				{"DayCount", {"A365"}},
				{"Currency", {"GBP"}},
				{"Calendar", {"LON"}},
			}
		},
		{"12M",
			{
				{"Interpolators", {"Linear", "Cubic"}},
				{"SeperationPoints", {"3Y"} },
				{"DayCount", {"A365"}},
				{"Currency", {"GBP"}},
				{"Calendar", {"LON"}},
			}
		}
};