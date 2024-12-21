#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include <string>

class Rectangle : public Shape {
private:
  sf::RenderWindow *window;
  std::string name;
  float init_x, init_y;
  float speed_x, speed_y;
  int Rcol, Gcol, Bcol;
  float length, breadth;
  sf::RectangleShape rectangle;

public:
  // Constructor declaration
  Rectangle(sf::RenderWindow *window, std::string name, float init_x,
            float init_y, float speed_x, float speed_y, int Rcol, int Gcol,
            int Bcol, float length, float breadth);

  // Overriding the draw method from Shape class to draw the circle
  void draw() override;
  void info() override;
  void update() override;
};

#endif // RECTANGLE_H
