#pragma once

#include <SFML/Graphics.hpp>

class Alien {
public:
    Alien(float speed);

    void update(const sf::Vector2f& playerPos, float deltaTime);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    const sf::CircleShape& getShape() const;
    void draw(sf::RenderWindow &window) const;

private:
    sf::CircleShape shape;  // The visual representation of the AI
    float speed;            // Movement speed in pixels per second
};
