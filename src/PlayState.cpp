#include "PlayState.hpp"
#include "Utils.hpp"
#include <iostream>

// Constructor: initialize window size and player + anchors
PlayState::PlayState(unsigned int windowWidth, unsigned int windowHeight)
    : window_x(windowWidth), window_y(windowHeight),
      player({100.f, 100.f}), // initialize player position here
      scoreText(font) {
  // Load font
  if (!font.openFromFile(
          "assets/fonts/PressStart2P-Regular.ttf")) {
    std::cerr << "Error loading font\n";
  }
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({10.f, 10.f}); // Top-left corner
  // Set player velocity, just like in your main gameplay loop
  player.setVelocity({100.f, 0.f});

  // Add some anchors
  anchors.emplace_back(sf::Vector2f(window_x / 2.f, window_y / 2.f));
  anchors.emplace_back(sf::Vector2f(window_x / 4.f, window_y / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x * 3 / 4.f, window_y / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x / 4.f, window_y * 3 / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x * 3 / 4.f, window_y * 3 / 4.f));

  aliens.emplace_back(90.f);
}

// Handle events, e.g. keyboard, window close
void PlayState::handleEvent(sf::RenderWindow &window,
                            const std::optional<sf::Event> &event) {
  if (!event.has_value())
    return;
  const sf::Event &e = *event;

  if (e.is<sf::Event::Closed>())
    window.close();
  if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
    if (key->scancode == sf::Keyboard::Scancode::Space &&
        player.getCanAnchor()) {
      if (!player.isAttached()) {
        player.attachTo();
      }
    }
  }
  if (auto *key = event->getIf<sf::Event::KeyReleased>()) {
    if (key->scancode == sf::Keyboard::Scancode::Space) {
      player.detach();
    }
  }
}

// Update the game state each frame
void PlayState::update(sf::RenderWindow &window, float dt) {
  player.update(dt, window_x, window_y);
  for (Alien &alien : aliens) {
    alien.update(player.getPosition(), dt);
  }
  elapsedTime += dt;
  score = static_cast<unsigned int>(elapsedTime);
  scoreText.setString("Score: " + std::to_string(score));
}

// Draw the game objects
void PlayState::draw(sf::RenderWindow &window) {

  const AnchorPoint *nearby =
      findNearestAnchor(anchors, player.getPosition(), 150.f);
  if (nearby && !player.isAttached()) {
    player.setAnchor(nearby);
    player.setCanAnchor(true);
  } else {
    player.setCanAnchor(false);
  }
  if (nearby && !player.isAttached()) {
    std::array<sf::Vertex, 2> line = {
        sf::Vertex(player.getPosition(), sf::Color::Blue),
        sf::Vertex(nearby->getPosition(), sf::Color::Blue),
    };
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
  }

  player.draw(window);
  for (const auto &anchor : anchors)
    anchor.draw(window);
  for (const auto &alien : aliens)
    alien.draw(window);
  window.draw(scoreText);
}

