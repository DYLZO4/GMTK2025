#pragma once
#include "GameState.hpp"

class MenuState : public GameState {
public:
    void handleEvent(sf::RenderWindow& window, const std::optional<sf::Event>& event) override;
    void update(sf::RenderWindow& window, float dt) override;
    void draw(sf::RenderWindow& window) override;
};

