#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include "Circle.h"
#include "Shape.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Shape *> readConfig(const std::string filename,
                                sf::RenderWindow *window);
#endif // !CONFIGREADER_H
