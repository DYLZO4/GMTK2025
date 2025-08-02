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

private:
  unsigned int window_x, window_y;
  std::vector<AnchorPoint> anchors;
  std::vector<Alien> aliens;
  Player player;
  float elapsedTime = 0.f;
  unsigned int score = 0;
  sf::Font font;
  sf::Text scoreText;
};
