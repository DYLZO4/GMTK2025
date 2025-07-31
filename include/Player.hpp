#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
  sf::CircleShape shape;
  sf::Vector2f position;
  float radius;
  bool attached;

public:
  Player(sf::Vector2f startPos, float r = 10.0f);

  void draw(sf::RenderWindow &window) const;

  void setPosition(sf::Vector2f pos);
  sf::Vector2f getPosition() const;

  void attach();
  void detach();
  bool isAttached() const;
  void update(float dt);
  void attatchTo(sf::Vector2f anchorPos);

  void toggleAttach(); // Called on spacebar press
  
};
