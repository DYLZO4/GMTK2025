#include "Alien.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

Alien::Alien(sf::Vector2f position, float speed, float radius) : speed(speed), radius(radius) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Magenta);
  shape.setOrigin({shape.getRadius(), shape.getRadius()});
  shape.setPosition(position);
}

void Alien::update(const sf::Vector2f &playerPos, float deltaTime) {
  sf::Vector2f aiPos = shape.getPosition();
  sf::Vector2f direction = playerPos - aiPos;

  float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (distance > 0.1f) {
    direction /= distance; // Normalize
    // Accelerate toward player
    sf::Vector2f desiredVelocity = direction * speed;

    // Simple steering: accelerate velocity toward desired velocity
    float steeringStrength = 5.f; // tweak for smoothness
    sf::Vector2f steering = desiredVelocity - velocity;
    velocity += steering * steeringStrength * deltaTime;

    // Optionally clamp max speed
    float maxSpeed = speed;
    float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (currentSpeed > maxSpeed) {
      velocity = (velocity / currentSpeed) * maxSpeed;
    }

    shape.move(velocity * deltaTime);
  }
}

void Alien::setPosition(const sf::Vector2f &pos) { shape.setPosition(pos); }

sf::Vector2f Alien::getPosition() const { return shape.getPosition(); }

const sf::CircleShape &Alien::getShape() const { return shape; }

void Alien::draw(sf::RenderWindow &window) const { window.draw(shape); }

float Alien::getRadius() const { return radius; }

void Alien::addVelocity(const sf::Vector2f& dv) {
    velocity += dv;
}


