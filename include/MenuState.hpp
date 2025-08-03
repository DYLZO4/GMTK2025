#pragma once
#include "GameState.hpp"

class MenuState : public GameState {
private:
  std::optional<StateTransition> requested;

public:
  void handleEvent(sf::RenderWindow &window,
                   const std::optional<sf::Event> &event) override;
  void update(sf::RenderWindow &window, float dt) override;
  void draw(sf::RenderWindow &window) override;
  std::optional<StateTransition> getRequestedTransition() override;
void clearRequestedTransition() override;
};
