#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main() {
  // INITIALIZE
  sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game");
  // INITIALIZE

  // MAIN GAME LOOP
  while (window.isOpen()) {

    // UPDATE
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    // UPDATE

    // DRAW
    window.clear(sf::Color::Yellow);
    window.display();
    // DRAW
  }
}
