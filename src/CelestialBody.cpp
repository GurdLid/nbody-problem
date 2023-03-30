#include "CelestialBody.hpp"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(const double &x, const double &y, const double &z, const double &v_x, const double &v_y, const double &v_z, const double &mass, const double &radius)
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