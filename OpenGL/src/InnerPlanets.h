#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>

namespace InnerPlanetsUI
{
    void RenderUI(std::vector<std::shared_ptr<std::pair<std::string, bool>>> &CelestialBodies);
}