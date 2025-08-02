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

bool checkCollision(const sf::Vector2f& aPos, float aRadius,
                    const sf::Vector2f& bPos, float bRadius) {
    float dx = aPos.x - bPos.x;
    float dy = aPos.y - bPos.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = aRadius + bRadius;
    return distanceSquared <= radiusSum * radiusSum;
}

sf::Vector2f getOffscreenSpawnPosition(unsigned screenWidth, unsigned screenHeight) {
    float buffer = 40.f; // how far off-screen to spawn
    int side = rand() % 4; // 0=top, 1=right, 2=bottom, 3=left

    switch (side) {
        case 0: // top
            return sf::Vector2f(rand() % screenWidth, -buffer);
        case 1: // right
            return sf::Vector2f(screenWidth + buffer, rand() % screenHeight);
        case 2: // bottom
            return sf::Vector2f(rand() % screenWidth, screenHeight + buffer);
        case 3: // left
            return sf::Vector2f(-buffer, rand() % screenHeight);
    }

    return sf::Vector2f(0.f, 0.f); // fallback
}
sf::Vector2f bounceVelocity(const sf::Vector2f& velocity, const sf::Vector2f& normal) {
    // Reflect velocity vector: V' = V - 2(V ⋅ N)N
    float dot = velocity.x * normal.x + velocity.y * normal.y;
    return velocity - 2.f * dot * normal;
}

