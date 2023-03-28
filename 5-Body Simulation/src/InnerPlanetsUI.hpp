#ifndef INNER_PLANETS_UI
#define INNER_PLANETS_UI

#include "imgui.h"

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "simulation/Simulate.hpp"
#include "simulation/MathsFunctions.hpp"

namespace InnerPlanetsUI
{
    void RenderUI(std::vector<std::shared_ptr<std::pair<std::string, bool>>> &CelestialBodies, std::vector<double> &initialPositions, std::vector<double>& finalPositions);
}


#endif // INNER_PLANETS_UI