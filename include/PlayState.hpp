#pragma once

#include "GameState.hpp"
#include "AnchorPoint.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

class PlayState : public GameState {
public:
    PlayState(unsigned int windowWidth, unsigned int windowHeight);

    void handleEvent(sf::RenderWindow& window, const std::optional<sf::Event>& event) override;
    void update(sf::RenderWindow& window, float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    unsigned int window_x, window_y;
    std::vector<AnchorPoint> anchors;
    Player player;
};

