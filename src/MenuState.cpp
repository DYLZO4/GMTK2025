#include "MenuState.hpp"
#include "PlayState.hpp"
#include <iostream>

// Handle events, e.g. keyboard, window close
void MenuState::handleEvent(sf::RenderWindow &window,
                            const std::optional<sf::Event> &event) {
  if (!event.has_value())
    return;
  const sf::Event &e = *event;

  if (e.is<sf::Event::Closed>())
    window.close();
  if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
    requested = StateTransition{.action = StateAction::Change,
                                .newState = std::make_unique<PlayState>(
                                    window.getSize().x, window.getSize().y)};
  }
  if (auto *key = event->getIf<sf::Event::KeyReleased>()) {
    if (key->scancode == sf::Keyboard::Scancode::Space) {
    }
  }
}

void MenuState::update(sf::RenderWindow &window, float dt) {
  // Update menu logic (animations, selection, etc.)
}

void MenuState::draw(sf::RenderWindow &window) {
}

std::optional<StateTransition> MenuState::getRequestedTransition() {
  return std::move(requested);
}

void MenuState::clearRequestedTransition() {
  if (requested.has_value()) {
    requested.reset();
  }
}
