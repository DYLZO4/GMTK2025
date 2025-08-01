#pragma once
#include "AnchorPoint.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>

class Player {
private:
  sf::CircleShape shape;
  sf::Vector2f position;
  float radius;
  bool attached;
  sf::Vector2f velocity;
  sf::Vector2f anchorPosition;
  float orbitRadius;
  float angularSpeed = 5.f;
  float angle = 0.f;
  int rotationDirection;

public:
  Player(sf::Vector2f startPos, float r = 10.0f);

  void draw(sf::RenderWindow &window) const;

  void setPosition(sf::Vector2f pos);
  sf::Vector2f getPosition() const;

  void attach();
  void detach();
  bool isAttached() const;
  void update(float dt, unsigned screen_x, unsigned screen_y);
  void attachTo(sf::Vector2f anchorPos);
  void setVelocity(sf::Vector2f velocity);
  void toggleAttach(); // Called on spacebar press
};
