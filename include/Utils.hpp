#pragma once
#include <vector>
#include "AnchorPoint.hpp"

const AnchorPoint* findNearestAnchor(const std::vector<AnchorPoint>& anchors, const sf::Vector2f& playerPos, float maxRange);
