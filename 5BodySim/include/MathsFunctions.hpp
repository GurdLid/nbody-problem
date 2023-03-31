#ifndef MATHS_FUNC
#define MATHS_FUNC

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>  
#include <sstream>
#include <iomanip>

const double G = 6.674e-11;

namespace MathsFunctions
{
    double CalculateNorm(int p, const std::vector<double>& vector); //Calculate vector norm

    double roundDouble(double x, int n); //Rounding a double to n sig figs

    std::string toScientificString(double x);
}

#endif // MATHS_FUNC