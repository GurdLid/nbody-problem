#ifndef SIMULATE
#define SIMULATE

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "CelestialBody.hpp"
#include "NBodyInterface.hpp"
#include "SymplecticEuler.hpp"
#include "PhysicsConstants.h"

namespace Simulate
{
	std::vector<std::shared_ptr<CelestialBody>> InitialiseBodies(std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies, int resultsRows);

	//void SymplecticEulerSim(std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies, int Results_Rows, int Steps);
}

#endif // SIMULATE