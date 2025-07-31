#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Touch.hpp>

class AnchorPoint {
private:
  sf::CircleShape shape;
  float radius;
  sf::Vector2f position;

public:
  AnchorPoint(sf::Vector2f pos, float r = 10.0f);
  void draw(sf::RenderWindow &window) const;
  sf::Vector2f getPosition() const;
  bool isPlayerInRange(const sf::Vector2f &playerPos, float range) const;
};
