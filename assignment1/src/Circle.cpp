#include "../include/Circle.h"

// Constructor definition
Circle::Circle(sf::RenderWindow *window, std::string name, float init_x,
               float init_y, float speed_x, float speed_y, int Rcol, int Gcol,
               int Bcol, float radius)
    : window(window), name(name), init_x(init_x), init_y(init_y),
      speed_x(speed_x), speed_y(speed_y), Rcol(Rcol), Gcol(Gcol), Bcol(Bcol),
      radius(radius), circle(radius) {
  // Initialize position and color
  circle.setPosition(init_x, init_y);
  circle.setFillColor(sf::Color(Rcol, Gcol, Bcol));
}

// Draw method to render the circle onto the window
void Circle::draw() { window->draw(circle); }

void Circle::info() {
  std::cout << "Circle: " << name << " Position: (" << init_x << ", " << init_y
            << ")"
            << " Speed: (" << speed_x << ", " << speed_y << ")"
            << " Color: (" << Rcol << ", " << Gcol << ", " << Bcol << ")"
            << " Radius: " << radius << std::endl;
}
