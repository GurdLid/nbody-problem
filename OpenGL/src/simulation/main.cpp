#include <cmath>
#include <random>
#include <chrono>
#include "CelestialBody.hpp"
#include "NBodyInterface.hpp"
#include "SymplecticEuler.hpp"
#include "PhysicsConstants.h"

int main(void)
{
    extern const double G;
    double Steps = 10000;


    //Bools for selecting specific celestial bodies
    const size_t totalNoOfBodies = 5;
    const bool defaultBodySelected = true;
    std::vector<bool> BodyTrue(totalNoOfBodies, defaultBodySelected);
    int celestialVectorSize;


    //BodyTrue[3] = false;


    for(const auto &i : BodyTrue)
    {
        celestialVectorSize += i;
    }

    //Position data from JPL Horizons database dated: 01/01/2005
    std::shared_ptr<CelestialBody> Moon_ = std::make_shared<CelestialBody>(-27440663.8165208e3, 144729193.335639e3, 24808.236184314e3,
                                                                        -30.074128500212e3, -6.5095675566316e3, -0.057508367552749e3, PhysicsConstants::moonMass, PhysicsConstants::moonRadius);

    std::shared_ptr<CelestialBody> Earth_ = std::make_shared<CelestialBody>(-27067884.6257174e3, 144587718.527863e3, -1969.59490492195e3,
                                                                        -29.7609559402974e3, -5.58170729426966e3, 7.82453662445448e-1, PhysicsConstants::earthMass, PhysicsConstants::earthRadius);

    std::shared_ptr<CelestialBody> Sun_ = std::make_shared<CelestialBody>(0.0, 0.0, 0.0,
                                                                        0.0, 0.0, 0.0, PhysicsConstants::sunMass, PhysicsConstants::sunRadius);

    std::shared_ptr<CelestialBody> Mercury_ = std::make_shared<CelestialBody>(-5.912134174085139e10, -1.122619296617797e10, 4.544945202497724e9,
                                                                        4.014526967381349e2, -4.597153609729074e4, -3.849231669600432e3, PhysicsConstants::mercuryMass, PhysicsConstants::mercuryRadius);

    std::shared_ptr<CelestialBody> Venus_ = std::make_shared<CelestialBody>(-7.094183693077585e10, -8.250232669178858e10, 2.956505086981911e9,
                                                                        2.819437134554216e4, -2.321446579433773e4, -2.076543268683134e3, PhysicsConstants::venusMass, PhysicsConstants::venusRadius);


    //Instantiating an ODE system for the 5 planetary bodies
    std::vector<std::shared_ptr<CelestialBody>> InnerPlanets(5);
    InnerPlanets = {Moon_, Earth_, Sun_, Mercury_, Venus_};
    for(int i=0; i<5; i++)
    {
        if(!BodyTrue[i])
        {
            InnerPlanets.erase(InnerPlanets.begin()+i);
        }
    }

    std::unique_ptr<NBodyInterface> InnerPlanetInterface = std::make_unique<NBodyInterface>(InnerPlanets);

    std::unique_ptr<SymplecticEuler> InnerPlanetSolver = std::make_unique<SymplecticEuler>(*InnerPlanetInterface,0,PhysicsConstants::earth_T0,PhysicsConstants::earth_T0/Steps,"output_InnerPlanets.dat");
    InnerPlanetSolver->Solve();

    return 0;

}








 /*    //c(i)
    //Initial data
    double earthMass = 5.972e24;
    double earthRadius = 6.378e6;
    double moonMass = 7.342e22;
    double moonRadius = 1.737e6;
    double r0 = 3.844e8;
    double v0 = 0.0;
    double T0 = 0.0;


    //Initial conditions
    v0 = pow(((G * earthMass)/r0),0.5);
    T0 = pow(((4.0*pow(M_PI,2.0)*pow(r0,3.0))/(G*earthMass)),0.5);

    std::shared_ptr<CelestialBody> Moon = std::make_shared<CelestialBody>(r0,0,0,0,v0,0,moonMass,moonRadius);
    std::shared_ptr<CelestialBody> Earth = std::make_shared<CelestialBody>(0,0,0,0,0,0,earthMass,earthRadius);

    std::vector<std::shared_ptr<CelestialBody>> PlanetList(2);
    PlanetList[0] = Moon;
    PlanetList[1] = Earth;

    std::unique_ptr<NBodyInterface> MoonOrbit = std::make_unique<NBodyInterface>(PlanetList);
    std::unique_ptr<SymplecticEuler> LunarSolver = std::make_unique<SymplecticEuler>(*MoonOrbit, 0, T0, T0/Steps, "output_SE_5.dat");
    LunarSolver->Solve(); */
