#include "../include/ConfigReader.h"
#include "../include/Shape.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

int main() {

  // INITIALIZE-------------------------------------------------------------
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
  std::vector<Shape *> shapes = readConfig("assets/config.txt", &window);
  // INITIALIZE-------------------------------------------------------------

  // MAIN GAME LOOP
  while (window.isOpen()) {

    // UPDATE---------------------------------------------------------------
    sf::Event event;
    while (window.pollEvent(event)) {

      // When window is closed
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    // UPDATE---------------------------------------------------------------

    // DRAW-----------------------------------------------------------------
    for (Shape *shape : shapes) {
      shape->draw();
    }
    window.display();
    // DRAW-----------------------------------------------------------------
  }

  // CLEANUP----------------------------------------------------------------
  // Free each shape in shape when window is closed
  for (Shape *shape : shapes) {
    delete shape;
  }
  shapes.clear();
  // CLEANUP----------------------------------------------------------------

  return 0;
}
