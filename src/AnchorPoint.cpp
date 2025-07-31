#include "AnchorPoint.hpp"
#include <cmath>

AnchorPoint::AnchorPoint(sf::Vector2f pos, float r) : position(pos), radius(r) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Yellow);
  shape.setOrigin({radius, radius});
  shape.setPosition(position);
}

void AnchorPoint::draw(sf::RenderWindow &window) const { window.draw(shape); }

sf::Vector2f AnchorPoint::getPosition() const { return position; }

bool AnchorPoint::isPlayerInRange(const sf::Vector2f &playerPos,
                                  float range) const {
  float dx = playerPos.x - position.x;
  float dy = playerPos.y - position.y;
  float distance = std::sqrt(dx * dx + dy * dy);
  return distance <= range;
}
