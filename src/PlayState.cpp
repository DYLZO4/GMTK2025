#include "PlayState.hpp"
#include "Utils.hpp"
#include <cmath>
#include <iostream>
#include <string>

// Constructor: initialize window size and player + anchors
PlayState::PlayState(unsigned int windowWidth, unsigned int windowHeight)
    : window_x(windowWidth), window_y(windowHeight),
      player({100.f, 100.f}), // initialize player position here
      scoreText(font), speedText(font), livesText(font) {
  // Load font
  if (!font.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
    std::cerr << "Error loading font\n";
  }
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({10.f, 10.f}); 
  speedText.setCharacterSize(24);
  speedText.setFillColor(sf::Color::White);
  speedText.setPosition({10.f, 50.f}); 

  livesText.setCharacterSize(24);
  livesText.setFillColor(sf::Color::White);
  livesText.setPosition({10.f, 150.f}); 
  player.setVelocity({100.f, 0.f});

  // Add some anchors
  anchors.emplace_back(sf::Vector2f(window_x / 2.f, window_y / 2.f));
  anchors.emplace_back(sf::Vector2f(window_x / 4.f, window_y / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x * 3 / 4.f, window_y / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x / 4.f, window_y * 3 / 4.f));
  anchors.emplace_back(sf::Vector2f(window_x * 3 / 4.f, window_y * 3 / 4.f));
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
  spawnTimer += dt;
  if (spawnTimer >= spawnInterval) {
    spawnTimer = 0.f;

    // Spawn alien
    sf::Vector2f spawnPos = getOffscreenSpawnPosition(window_x, window_y);
    float alienRadius = 30.f;
    float alienSpeed = 90.f;

    aliens.emplace_back(spawnPos, alienSpeed, alienRadius);
  }

  const float separationDistance = 100.f;
  const float repulsionStrength = 200.f;

  for (size_t i = 0; i < aliens.size(); ++i) {
    sf::Vector2f repulsion(0.f, 0.f);
    int count = 0;

    for (size_t j = 0; j < aliens.size(); ++j) {
      if (i == j)
        continue;

      sf::Vector2f diff = aliens[i].getPosition() - aliens[j].getPosition();
      float distSq = diff.x * diff.x + diff.y * diff.y;

      if (distSq < separationDistance * separationDistance && distSq > 0.01f) {
        float dist = std::sqrt(distSq);
        sf::Vector2f away = diff / dist; // normalized
        repulsion += away / dist;        // stronger when closer
        ++count;
      }
    }

    if (count > 0) {
      repulsion *= repulsionStrength;

      aliens[i].addVelocity(repulsion); 
    }
  }

  player.update(dt, window_x, window_y);
  float playerSpeed = player.getSpeed();
  for (Alien &alien : aliens) {
    alien.update(player.getPosition(), dt);
  }
  for (auto it = aliens.begin(); it != aliens.end();) {
    if (checkCollision(player.getPosition(), player.getRadius(),
                       it->getPosition(), it->getRadius())) {

      if (playerSpeed > 700.0f) {
        score += 50;
        it = aliens.erase(it); // safely erase alien and continue
      } else {
        player.removeLives(1); 
        if (player.getLives()<1){ 
        // TODO: switch to game over state
        }
        sf::Vector2f diff = player.getPosition() - it->getPosition();
        float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (length != 0) {
          player.detach();
          sf::Vector2f normal = diff / length;
          sf::Vector2f newVelocity =
              bounceVelocity(player.getVelocity(), normal);
          player.setVelocity(newVelocity);
        }
        player.setPosition(player.getPosition() + diff * 0.05f);
        break;
      }
    } else {
      ++it;
    }
  }

  elapsedTime += dt;
  if (elapsedTime >= 1) {
    score += 1;
    elapsedTime = 0;
  }
  scoreText.setString("Score: " + std::to_string(score));
  speedText.setString("Speed: " +
                      std::to_string(static_cast<int>(playerSpeed)));

  livesText.setString("Lives: " + std::to_string(player.getLives()));
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
  window.draw(livesText);
  window.draw(speedText);
}
