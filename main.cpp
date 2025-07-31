#include <SFML/Graphics.hpp>

int main() {

  // Render Window
  unsigned window_x = 800;
  unsigned window_y = 800;
  sf::RenderWindow window(sf::VideoMode({window_x, window_y}), "Loop");

  // Main loop
  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }
  }

  return 0;
}
