#include "Player.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "AnchorPoint.hpp"

Player::Player(sf::Vector2f startPos, float r)
    : position(startPos), radius(r), attached(false) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Red);
  shape.setOrigin({radius, radius}); // center origin
  shape.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) const { window.draw(shape); }

void Player::setPosition(sf::Vector2f pos) {
  position = pos;
  shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const { return position; }

void Player::attach() { attached = true; }

void Player::detach() { attached = false; }

void Player::toggleAttach() { attached = !attached; }

bool Player::isAttached() const { return attached; }
void Player::setVelocity(sf::Vector2f v){
  velocity = v;
}
void Player::update(float dt) {
  if (!attached) {
    position += velocity * dt;
    shape.setPosition(position);
  } else{
     angle += rotationDirection * angularSpeed * dt;

    position.x = anchorPosition.x + orbitRadius * std::cos(angle);
    position.y = anchorPosition.y + orbitRadius * std::sin(angle);
    shape.setPosition(position);
    // Compute tangential velocity
    velocity.x = -rotationDirection * orbitRadius * angularSpeed * std::sin(angle);
    velocity.y = rotationDirection * orbitRadius * angularSpeed * std::cos(angle);
  }
}

void Player::attachTo(sf::Vector2f anchorPos){
  anchorPosition = anchorPos;
  attached = true;
  sf::Vector2f diff = position - anchorPosition;
  angle = std::atan2(diff.y, diff.x);
  orbitRadius = std::sqrt(diff.x * diff.x + diff.y * diff.y);
  float cross = diff.x * velocity.y - diff.y * velocity.x;
  rotationDirection = (cross >= 0) ? 1 : -1;
}
