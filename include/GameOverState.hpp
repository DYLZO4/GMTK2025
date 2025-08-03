#pragma once
#include "GameState.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameOverState : public GameState {
private:
  std::optional<StateTransition> requested;
  sf::Text gameOverText;
  sf::Text scoreText;
  sf::Font font;

public:
  GameOverState(unsigned int score);
  void handleEvent(sf::RenderWindow &window,
                   const std::optional<sf::Event> &event) override;
  void update(sf::RenderWindow &window, float dt) override;
  void draw(sf::RenderWindow &window) override;
  std::optional<StateTransition> getRequestedTransition() override;
  void clearRequestedTransition() override;
};
