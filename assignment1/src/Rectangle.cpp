#include "../include/Rectangle.h"

// Constructor definition
Rectangle::Rectangle(sf::RenderWindow *window, std::string name, float init_x,
                     float init_y, float speed_x, float speed_y, int Rcol,
                     int Gcol, int Bcol, float length, float breadth)
    : window(window), name(name), init_x(init_x), init_y(init_y),
      speed_x(speed_x), speed_y(speed_y), Rcol(Rcol), Gcol(Gcol), Bcol(Bcol),
      length(length), breadth(breadth),
      rectangle(sf::Vector2f(length, breadth)) {
  rectangle.setPosition(init_x, init_y);
  rectangle.setFillColor(sf::Color(Rcol, Gcol, Bcol));
}

void Rectangle::draw() { window->draw(rectangle); }

void Rectangle::info() {
  std::cout << "Rectangle: " << name << " Position: (" << init_x << ", "
            << init_y << ")"
            << " Speed: (" << speed_x << ", " << speed_y << ")"
            << " Color: (" << Rcol << ", " << Gcol << ", " << Bcol << ")"
            << " Dimensions: " << length << " x " << breadth << std::endl;
}
