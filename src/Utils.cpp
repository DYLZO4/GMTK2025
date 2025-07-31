#include "Utils.hpp"
#include <cmath>

const AnchorPoint *findNearestAnchor(const std::vector<AnchorPoint> &anchors,
                                     const sf::Vector2f &playerPos,
                                     float maxRange) {
  const AnchorPoint *closest = nullptr;
  float minDistSq = maxRange * maxRange;

  for (const auto &anchor : anchors) {
    float dx = anchor.getPosition().x - playerPos.x;
    float dy = anchor.getPosition().y - playerPos.y;
    float distSq = dx * dx + dy * dy;

    if (distSq <= minDistSq) {
      closest = &anchor;
      minDistSq = distSq;
    }
  }

  return closest;
}
