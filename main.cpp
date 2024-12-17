#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main() {
  // INITIALIZE-----------------------------------------------
  sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game");
  sf::CircleShape shape(50.0f);
  // INITIALIZE-----------------------------------------------

  // MAIN GAME LOOP
  while (window.isOpen()) {

    // UPDATE-----------------------------------------------
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    // UPDATE-----------------------------------------------

    // DRAW-----------------------------------------------
    window.draw(shape);
    window.display();
    // DRAW-----------------------------------------------
  }
}
