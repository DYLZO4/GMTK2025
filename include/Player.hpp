#pragma once
#include "AnchorPoint.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>

class Player {
private:
  int lives = 3;
  sf::CircleShape shape;
  sf::Vector2f position;
  float radius;
  bool attached;
  sf::Vector2f velocity;
  sf::Vector2f anchorPosition;
  float orbitRadius;
  float angularSpeed;
  float angle = 0.f;
  int rotationDirection;
  bool canAnchor;
  float decayFactor = 0.1f;
  float baseSpeed = 1.0f;
  float speedBoostFactor = 100.0f;

public:
  Player(sf::Vector2f startPos, float r = 10.0f);

  void draw(sf::RenderWindow &window) const;

  void setPosition(sf::Vector2f pos);
  sf::Vector2f getPosition() const;

  void attach();
  void detach();
  bool isAttached() const;
  void update(float dt, unsigned screen_x, unsigned screen_y);
  void attachTo();
  void setVelocity(sf::Vector2f velocity);
  void toggleAttach(); // Called on spacebar press
  void setAnchor(const AnchorPoint *anchor);
  void setCanAnchor(bool canAnchor);
  bool getCanAnchor();
  float getRadius();
  float getSpeed();
  sf::Vector2f getVelocity();
  int getLives();
  void removeLives(int amount);
};
