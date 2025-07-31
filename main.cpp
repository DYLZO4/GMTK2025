#include "AnchorPoint.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

int main() {

  // Render Window
  unsigned window_x = 800;
  unsigned window_y = 800;
  sf::RenderWindow window(sf::VideoMode({window_x, window_y}), "Loop");

  // Create an Anchor Point
  AnchorPoint anchor({400.f, 400.f});

  // Create Player
  Player player({100.f, 100.f});

  // Main loop
  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();

      if (auto *key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::Space) {
          player.toggleAttach();
        }
      }
    }
    window.clear();

    // Draw the anchor point
    anchor.draw(window);
    player.draw(window);
    window.display();
  }

  return 0;
}
