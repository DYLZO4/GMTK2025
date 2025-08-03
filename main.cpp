#include "PlayState.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

int main() {
  unsigned int window_x = 800;
  unsigned int window_y = 800;
  sf::RenderWindow window(sf::VideoMode({window_x, window_y}), "Loop");
  window.setFramerateLimit(60);
  StateManager stateManager;
  stateManager.pushState(std::make_unique<MenuState>());
  sf::Clock frameClock;

  while (window.isOpen()) {
    GameState *currentState = stateManager.getCurrentState();
    if (!currentState)
      break; // exit if no state is active
    while (const std::optional event = window.pollEvent()) {
      currentState->handleEvent(window, event);
    }

    float dt = frameClock.restart().asSeconds();

    currentState->update(window, dt);
    window.clear();
    currentState->draw(window);
    window.display();
    if (auto transition = currentState->getRequestedTransition()) {
      switch (transition->action) {
      case StateAction::Push:
        stateManager.pushState(std::move(transition->newState));
        break;
      case StateAction::Pop:
        stateManager.popState();
        break;
      case StateAction::Change:
        stateManager.changeState(std::move(transition->newState));
        break;
      case StateAction::None:
      default:
        break;
      }
    }
  }

  return 0;
}
