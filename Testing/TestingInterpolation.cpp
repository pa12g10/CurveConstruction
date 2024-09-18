#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <iomanip> // for std::fixed, std::setprecision


#include <interpolators/Linear.h>
#include <interpolators/CubicSpline.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestingInterpolation
{

	TEST_CLASS(Curves)
	{
	public:

		TEST_METHOD(TestLinearInterpolators)
		{

			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, 1, -1, 1, -1 };

			auto linear_interpolator = LinearInterpolator(x_vals, y_vals);
			Logger::WriteMessage("Linear Interpolation \n");
			Logger::WriteMessage("t, y \n");
			for (double i = 0; i <= 3; i += 0.05)
			{
				std::string result;
				{
					std::stringstream ss;
					ss << i << "," << std::fixed << linear_interpolator.interpolate(i) << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}

		}

		TEST_METHOD(TestCubicInterpolators)
		{

			std::vector<double> x_vals{ 0 , 0.25, 0.5, 0.75, 1, 2, 3 };
			std::vector<double> y_vals{ 1.0 , .93, .915, 1, -1, 1, -1 };
			Logger::WriteMessage("Cubic Interpolation \n");
			Logger::WriteMessage("t, y \n");
			auto cubic_interpolator = CubicSpline(x_vals, y_vals);
			for (double i = 0; i <= 3; i += 0.05)
			{
				std::string result;
				{
					std::stringstream ss;
					ss << i << "," << std::fixed << cubic_interpolator.interpolate(i) << "\n";
					result = ss.str();
					Logger::WriteMessage(result.c_str());
				}
			}
		}
	};
}