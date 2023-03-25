#ifndef VECTOR_FUNC
#define VECTOR_FUNC


#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>  

const double G = 6.674e-11;

namespace VectorFunctions
{
    double CalculateNorm(int p, const std::vector<double>& vector);
}

#endif // VECTOR_FUNC