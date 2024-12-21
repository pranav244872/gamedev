#include "../include/ConfigReader.h"

// This function is going to take the path to the config file and window object
// reference as input It is going to return a vector of shapes which can be
// iterated over
std::vector<Shape *> readConfig(const std::string filename,
                                sf::RenderWindow *window) {
  std::vector<Shape *> shapes;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Could not open the config file" << std::endl;
    return shapes;
  }

  std::string line;
  while (std::getline(file, line)) {

    std::stringstream ss(line);
    std::string firstWord;

    // Skip empty lines or lines that fail to provide the firstWord
    if (!(ss >> firstWord))
      continue;

    // When the first word is Circle create a circle class and push it into
    // shapes
    if (firstWord == "Circle") {

      std::string circleName;
      float init_x, init_y, speed_x, speed_y, radius;
      int RCol, GCol, BCol;

      // Extract the circle attributes
      ss >> circleName >> init_x >> init_y >> speed_x >> speed_y >> RCol >>
          GCol >> BCol >> radius;

      // When we create object with new Keyword, then it is allocated in heap
      // memory which goes beyond the scope of stack memory and doesnt go out
      // of scope
      Shape *newCircle = new Circle(window, circleName, init_x, init_y, speed_x,
                                    speed_y, RCol, GCol, BCol, radius);

      shapes.push_back(newCircle);
      continue;
    } else if (firstWord == "Rectangle") {

      std::string rectName;
      float init_x, init_y, speed_x, speed_y, length, breadth;
      int Rcol, Gcol, Bcol;

      // Extract the Rectangle attributes
      ss >> rectName >> init_x >> init_y >> speed_x >> speed_y >> Rcol >>
          Gcol >> Bcol >> length >> breadth;

      Shape *newRect =
          new Rectangle(window, rectName, init_x, init_y, speed_x, speed_y,
                        Rcol, Gcol, Bcol, length, breadth);
      shapes.push_back(newRect);
      continue;
    }
  }

  file.close();
  return shapes;
}
