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

void Circle::update() {
  // Get the current position of the circle
  sf::Vector2f currentPos = circle.getPosition();

  // Check for collisions with window boundaries and reverse speed
  if ((currentPos.x + 2 * radius) > window->getSize().x || currentPos.x < 0) {
    speed_x = -speed_x;
  }
  if ((currentPos.y + 2 * radius) > window->getSize().y || currentPos.y < 0) {
    speed_y = -speed_y;
  }

  // Update the position of the circle
  circle.setPosition(currentPos.x + speed_x, currentPos.y + speed_y);
}
