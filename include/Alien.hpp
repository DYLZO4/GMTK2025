#pragma once

#include <SFML/Graphics.hpp>

class Alien {
public:
  Alien(sf::Vector2f position, float speed, float radius);

  void update(const sf::Vector2f &playerPos, float deltaTime);
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() const;
  const sf::CircleShape &getShape() const;
  void draw(sf::RenderWindow &window) const;
  float getRadius() const;
  sf::Vector2f getVelocity() const;
  void setVelocity(const sf::Vector2f &v);
  void addVelocity(const sf::Vector2f &dv);

private:
  sf::CircleShape shape; // The visual representation of the AI
  float speed;           // Movement speed in pixels per second
  float radius;
  sf::Vector2f velocity{0.f, 0.f};
};
