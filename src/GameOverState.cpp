#include "GameOverState.hpp"
#include "PlayState.hpp"
#include <iostream>

GameOverState::GameOverState(unsigned int score)
    : gameOverText(font), scoreText(font) {
  if (!font.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
    std::cerr << "Error loading font\n";
  }
  gameOverText.setCharacterSize(24);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setPosition({10.f, 200.f});
  gameOverText.setString("Game Over\nPress Space to Retry");
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({10.f, 250.f});
  scoreText.setString("Score: " + std::to_string(score));
}

void GameOverState::handleEvent(sf::RenderWindow &window,
                                const std::optional<sf::Event> &event) {
  if (!event.has_value())
    return;
  const sf::Event &e = *event;

  if (e.is<sf::Event::Closed>())
    window.close();
  if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
    if (key->scancode == sf::Keyboard::Scancode::Space) {

      requested = StateTransition{.action = StateAction::Change,
                                  .newState = std::make_unique<PlayState>(
                                      window.getSize().x, window.getSize().y)};
    }
  }
  if (auto *key = event->getIf<sf::Event::KeyReleased>()) {
    if (key->scancode == sf::Keyboard::Scancode::Space) {
    }
  }
}

void GameOverState::update(sf::RenderWindow &window, float dt) {}

void GameOverState::draw(sf::RenderWindow &window) {
  window.draw(gameOverText);
  window.draw(scoreText);
}

std::optional<StateTransition> GameOverState::getRequestedTransition() {
  return std::move(requested);
}

void GameOverState::clearRequestedTransition() {
  if (requested.has_value()) {
    requested.reset();
  }
}
