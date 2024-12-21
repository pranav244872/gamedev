#include "../include/Rectangle.h"
#include <SFML/System/Vector2.hpp>

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

void Rectangle::update() {
  const sf::Vector2f currentPos = rectangle.getPosition();

  if ((currentPos.x + length) > window->getSize().x || currentPos.x < 0) {
    speed_x = -speed_x;
  }
  if ((currentPos.y + breadth) > window->getSize().y || currentPos.y < 0) {
    speed_y = -speed_y;
  }

  rectangle.setPosition(currentPos.x + speed_x, currentPos.y + speed_y);
}
