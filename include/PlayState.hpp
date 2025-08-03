#pragma once

#include "Alien.hpp"
#include "AnchorPoint.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <optional>
#include <vector>

class PlayState : public GameState {
public:
  PlayState(unsigned int windowWidth, unsigned int windowHeight);

  void handleEvent(sf::RenderWindow &window,
                   const std::optional<sf::Event> &event) override;
  void update(sf::RenderWindow &window, float dt) override;
  void draw(sf::RenderWindow &window) override;
  
  std::optional<StateTransition> getRequestedTransition() override;
  void clearRequestedTransition() override;

private:
  std::optional<StateTransition> requested;

  unsigned int window_x, window_y;
  std::vector<AnchorPoint> anchors;
  std::vector<Alien> aliens;
  Player player;
  float elapsedTime = 0.f;
  unsigned int score = 0;
  sf::Font font;
  sf::Text scoreText;
  sf::Text speedText;
  sf::Text livesText;
  float spawnTimer;
  float spawnInterval = 3.f;
};
