#include "Alien.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

Alien::Alien(float speed)
    : speed(speed)
{
    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Magenta);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
    shape.setPosition({0, 0});
}

void Alien::update(const sf::Vector2f& playerPos, float deltaTime) {
    sf::Vector2f aiPos = shape.getPosition();
    sf::Vector2f direction = playerPos - aiPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 0.1f) { // Prevent jittering
        direction /= distance; // Normalize
        shape.move(direction * speed * deltaTime);
    }
}

void Alien::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
}

sf::Vector2f Alien::getPosition() const {
    return shape.getPosition();
}

const sf::CircleShape& Alien::getShape() const {
    return shape;
}

void Alien::draw(sf::RenderWindow &window) const { window.draw(shape); }

