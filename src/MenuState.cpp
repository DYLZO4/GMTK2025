#include "MenuState.hpp"
#include "PlayState.hpp"
#include <iostream>

MenuState::MenuState() : startText(font) {
  if (!font.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
    std::cerr << "Error loading font\n";
  }
  startText.setCharacterSize(24);
  startText.setFillColor(sf::Color::White);
  startText.setPosition({10.f, 400.f});
  startText.setString("Press Space to Start");
}
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

void MenuState::update(sf::RenderWindow &window, float dt) {}

void MenuState::draw(sf::RenderWindow &window) { window.draw(startText); }

std::optional<StateTransition> MenuState::getRequestedTransition() {
  return std::move(requested);
}

void MenuState::clearRequestedTransition() {
  if (requested.has_value()) {
    requested.reset();
  }
}
