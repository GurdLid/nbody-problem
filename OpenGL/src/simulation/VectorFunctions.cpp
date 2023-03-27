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

double VectorFunctions::roundDouble(double x, int n)
{
    std::stringstream ss;
    ss << std::scientific << std::setprecision(n - 1) << x;
    return stod(ss.str());
}

std::string VectorFunctions::toScientificString(double x)
{
    // Create an output string stream
    std::ostringstream streamObj;
    //Add double to stream
    streamObj << x;
    // Get string from output string stream
    std::string strObj = streamObj.str();
    return strObj;
}