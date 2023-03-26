#include "Simulate.hpp"
namespace Simulate
{
    std::vector<std::shared_ptr<CelestialBody>> InitialiseBodies(std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies, int resultsRows)
    {
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
        std::vector<std::shared_ptr<CelestialBody>> InnerPlanets(resultsRows);
        int PlanetVector_counter = 0;
        if (CelestialBodies[0]->second)
        {
            InnerPlanets[PlanetVector_counter] = Moon_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[1]->second)
        {
            InnerPlanets[PlanetVector_counter] = Earth_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[2]->second)
        {
            InnerPlanets[PlanetVector_counter] = Sun_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[3]->second)
        {
            InnerPlanets[PlanetVector_counter] = Mercury_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[4]->second)
        {
            InnerPlanets[PlanetVector_counter] = Venus_;
        }
        return InnerPlanets;
    }
 /*
    void SymplecticEulerSim(std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies, int Results_Rows, int Steps)
    {
        
        std::unique_ptr<NBodyInterface> InnerPlanetInterface = std::make_unique<NBodyInterface>(InnerPlanets);

        std::unique_ptr<SymplecticEuler> InnerPlanetSolver = std::make_unique<SymplecticEuler>(*InnerPlanetInterface, 0, PhysicsConstants::earth_T0, PhysicsConstants::earth_T0 / Steps, "output_InnerPlanets.dat");
        InnerPlanetSolver->Solve();


        //std::vector<double> Output(3*Results_Rows);
        //return Output;
    }
*/
}
