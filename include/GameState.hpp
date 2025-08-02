#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class GameState {
public:
  virtual ~GameState() = default;

  // State lifecycle hooks
  virtual void onEnter() {}
  virtual void onExit() {}

  // Core state interface
  virtual void handleEvent(sf::RenderWindow &window,
                           const std::optional<sf::Event> &event) = 0;
  virtual void update(sf::RenderWindow &window, float dt) = 0;
  virtual void draw(sf::RenderWindow &window) = 0;
};
