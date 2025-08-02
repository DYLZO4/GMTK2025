#pragma once
#include <vector>
#include "AnchorPoint.hpp"

const AnchorPoint* findNearestAnchor(const std::vector<AnchorPoint>& anchors, const sf::Vector2f& playerPos, float maxRange);

bool checkCollision(const sf::Vector2f& aPos, float aRadius,
                    const sf::Vector2f& bPos, float bRadius); 
sf::Vector2f getOffscreenSpawnPosition(unsigned screenWidth, unsigned screenHeight);
sf::Vector2f bounceVelocity(const sf::Vector2f& velocity, const sf::Vector2f& normal);
