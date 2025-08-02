#include "PlayState.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

int main() {
  unsigned int window_x = 800;
  unsigned int window_y = 800;
  sf::RenderWindow window(sf::VideoMode({window_x, window_y}), "Loop");
  window.setFramerateLimit(60);

  PlayState playState(window_x, window_y);
  sf::Clock frameClock;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      playState.handleEvent(window, event);
    }

    float dt = frameClock.restart().asSeconds();
    playState.update(window, dt);

    window.clear();
    playState.draw(window);
    window.display();
  }

  return 0;
}
