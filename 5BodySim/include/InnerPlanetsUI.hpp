#ifndef INNER_PLANETS_UI
#define INNER_PLANETS_UI

#include "imgui.h"

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "Simulate.hpp"
#include "MathsFunctions.hpp"

namespace InnerPlanetsUI
{
    void RenderUI(std::vector<std::shared_ptr<std::pair<std::string, bool>>> &CelestialBodies, std::vector<double> &initialPositions, std::vector<double>& finalPositions);
}


#endif // INNER_PLANETS_UI