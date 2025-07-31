#include "AnchorPoint.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include <SFML/Graphics.hpp>
int main() {

  // Render Window
  unsigned window_x = 800;
  unsigned window_y = 800;
  sf::RenderWindow window(sf::VideoMode({window_x, window_y}), "Loop");

  // Create an Anchor Point
  std::vector<AnchorPoint> anchors;

  // Add some anchors to the vector
  anchors.emplace_back(sf::Vector2f(400.f, 400.f));
  anchors.emplace_back(sf::Vector2f(600.f, 200.f));
  anchors.emplace_back(sf::Vector2f(200.f, 500.f));
  anchors.emplace_back(sf::Vector2f(50.f, 100.f));
  anchors.emplace_back(sf::Vector2f(350.f, 75.f));

  // Create Player
  Player player({100.f, 100.f});
  player.setVelocity({50.f, 0});
  sf::Clock clock;
  // Main loop
  while (window.isOpen()) {
    const AnchorPoint *nearby =
        findNearestAnchor(anchors, player.getPosition(), 150.0f);
    window.clear();

    float dt =
        clock.restart()
            .asSeconds(); // gets time since last restart and restarts the clock
    player.update(dt);
    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();

      if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::Space && nearby) {
          player.toggleAttach();
          if (player.isAttached()) {
            player.attachTo(nearby->getPosition());
          }
        }
      }
    }

    if (nearby) {
      std::array<sf::Vertex, 2> line = {
          sf::Vertex(player.getPosition(), sf::Color::Blue),
          sf::Vertex(nearby->getPosition(), sf::Color::Blue),
      };
      window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    }
    // Draw the anchor point
    player.draw(window);
    for (const auto &anchor : anchors) {
      anchor.draw(window);
    }
    window.display();
  }

  return 0;
}
