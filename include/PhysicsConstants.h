#ifndef PHYSICS_CONSTANTS
#define PHYSICS_CONSTANTS

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace PhysicsConstants
{
    //Initial data- sourced from NASA's planetary database
    constexpr double earthMass = 5.972e24;
    constexpr double earthRadius = 6.378e6;
    constexpr double moonMass = 7.342e22;
    constexpr double moonRadius = 1.737e6;
    constexpr double sunMass = 1.989e30;
    constexpr double sunRadius = 696340e3;
    constexpr double mercuryMass = 0.330e24;
    constexpr double mercuryRadius = 2439.5e3;
    constexpr double venusMass = 4.87e24;
    constexpr double venusRadius = 6052e3;

    constexpr double moon_earth_r0 = 3.844e8;
    constexpr double earth_sun_r0 = 1.495978707e11;
    constexpr double moon_sun_r0 = earth_sun_r0 + moon_earth_r0;
    constexpr double mercury_sun_r0 = 57.9e6;
    constexpr double venus_sun_r0 = 108.2e6;

    const double moon_T0 = pow(((4.0*pow(M_PI,2.0)*pow(moon_earth_r0,3.0))/(G*earthMass)),0.5);
    const double earth_T0 = pow(((4.0*pow(M_PI,2.0)*pow(earth_sun_r0,3.0))/(G*sunMass)),0.5);
    const double mercury_T0 = pow(((4.0*pow(M_PI,2.0)*pow(mercury_sun_r0,3.0))/(G*sunMass)),0.5);
    const double venus_T0 = pow(((4.0*pow(M_PI,2.0)*pow(venus_sun_r0,3.0))/(G*sunMass)),0.5);
}

#endif //PHYSICS_CONSTANTS