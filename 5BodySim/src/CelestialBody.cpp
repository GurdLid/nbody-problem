#include "CelestialBody.hpp"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(double x, double y, double z, double v_x, const double v_y, double v_z, double mass, double radius)
: mMass(mass), mRadius(radius)
{
    mPosition = {x,y,z};
    mVelocity = {v_x,v_y,v_z};
}

CelestialBody::~CelestialBody()
{
}

std::vector<double> CelestialBody::GetPosition()
{
    return mPosition;
}

std::vector<double> CelestialBody::GetVelocity()
{
    return mVelocity;
}

double CelestialBody::GetMass()
{
    return mMass;
}

double CelestialBody::GetRadius()
{
    return mRadius;
}