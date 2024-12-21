#include "../include/ConfigReader.h"
#include "../include/Shape.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

int main() {

  // INITIALIZE-------------------------------------------------------------
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
  std::vector<Shape *> shapes = readConfig("assets/config.txt", &window);
  sf::Clock clock;
  // INITIALIZE-------------------------------------------------------------

  // Print details of all shapes
  std::cout << "Shapes read from config:" << std::endl;
  for (Shape *shape : shapes) {
    shape->info(); // Call the info method for each shape
  }

  // MAIN GAME LOOP
  while (window.isOpen()) {

    // Get the elapsed time since the last frame
    sf::Time deltaTime = clock.restart();

    // UPDATE---------------------------------------------------------------
    sf::Event event;
    while (window.pollEvent(event)) {

      // When window is closed
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    for (Shape *shape : shapes) {
      shape->update(); // Update speed for each shape
    }
    // UPDATE---------------------------------------------------------------

    // DRAW-----------------------------------------------------------------
    window.clear(); // Clear the window before drawing again

    for (Shape *shape : shapes) {
      shape->draw(); // Draw Each shape
    }

    window.display(); // Display the updated window
    // DRAW-----------------------------------------------------------------

    // Control the frame rate to be around 60 fps (16ms per frame)
    sf::sleep(sf::milliseconds(16) - deltaTime); // Sleep for the remaining time
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
