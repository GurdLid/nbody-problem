#ifndef CELESTIAL
#define CELESTIAL

#include <vector>
#include <iostream>
#include <array>
#include <type_traits>

#include "MathsFunctions.hpp"

extern const double G;

class CelestialBody
{
public:
    //Constructor for doubles 
    CelestialBody(double x, double y, double z, double v_x, const double v_y, double v_z, double mass, double radius);
    //Constructor for arrays/vectors 
    template<typename T>
    CelestialBody(T pos, T vel, double mass, double radius)
        : mMass(mass), mRadius(radius)
    {
        if (std::is_same<T, std::vector<double>>::value || std::is_same<T, std::array<double,3>>::value )
        {
            for(int i=0;i<3;i++)
            {
                mPosition.emplace_back(pos[i]);
                mVelocity.emplace_back(vel[i]);
            }
        }
        else
        {
            std::cout << "Incorrect Position and or Velocity type" << std::endl;
        } 
    }
    ~CelestialBody();

    std::vector<double> GetPosition();
    std::vector<double> GetVelocity();
    double GetMass();
    double GetRadius();

private:
    std::vector<double> mPosition;
    std::vector<double> mVelocity;

    double mMass;
    double mRadius;

    CelestialBody(); //Hidden default constructor 

};


#endif //CELESTIAL