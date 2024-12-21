#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
  virtual ~Shape() = default; // Virtual destructor
  virtual void draw() = 0;
  virtual void info() = 0;
};

#endif // ! SHAPE_H
