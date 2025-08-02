#include "MenuState.hpp"
#include <iostream>

void MenuState::handleEvent(sf::RenderWindow &window, const std::optional<sf::Event> &eventOpt) {
    if (!eventOpt.has_value()) return;

    const sf::Event& event = *eventOpt;

    if (event.is<sf::Event::Closed>())
        window.close();

    // Add more menu input handling here
}

void MenuState::update(sf::RenderWindow &window, float dt) {
    // Update menu logic (animations, selection, etc.)
}

void MenuState::draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Blue);
    // Draw menu UI here (e.g., title text, buttons, etc.)
    window.display();
}

