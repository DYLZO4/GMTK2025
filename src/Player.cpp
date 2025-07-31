// src/Player.cpp
#include "Player.hpp"

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

void update(float dt) {
}

void attachTo(sf::Vector2f anchorPos);
