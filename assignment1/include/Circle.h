#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <SFML/Graphics.hpp>
#include <string>

class Circle : public Shape {
private:
  sf::RenderWindow
      *window;            // Pointer to the window where the shape will be drawn
  std::string name;       // Name of the circle
  float init_x, init_y;   // Initial position of the circle
  float speed_x, speed_y; // Speed of the circle
  int Rcol, Gcol, Bcol;   // RGB color components
  float radius;           // Radius of the circle
  sf::CircleShape circle; // SFML CircleShape object

public:
  // Constructor declaration
  Circle(sf::RenderWindow *window, std::string name, float init_x, float init_y,
         float speed_x, float speed_y, int Rcol, int Gcol, int Bcol,
         float radius);

  // Overriding the draw method from Shape class to draw the circle
  void draw() override;
};

#endif // CIRCLE_H
