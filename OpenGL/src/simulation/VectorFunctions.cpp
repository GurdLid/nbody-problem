#include "VectorFunctions.hpp"

double VectorFunctions::CalculateNorm(int p, const std::vector<double>& vector)
{
    double norm = 0.0;
    double sum = 0.0;
    for (const auto &i : vector)
    {
        sum += pow(fabs(i), p);
    }
    norm = pow(sum, 1.0/((double)(p)));
    return norm;
}