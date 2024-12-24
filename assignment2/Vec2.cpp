#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

Vec2 Vec2::operator+(const Vec2 &rhs) const {
  return Vec2(rhs.x + x, rhs.y + y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const {
  return Vec2(rhs.x - x, rhs.y - y);
}

Vec2 Vec2::operator*(const float val) const { return Vec2(x * val, y * val); }

Vec2 Vec2::operator/(const float val) const { return Vec2(x / val, y / val); }

bool Vec2::operator==(const Vec2 &rhs) const {
  return fabs(x - rhs.x) < 1e-6 && fabs(y - rhs.y) < 1e-6;
}

bool Vec2::operator!=(const Vec2 &rhs) const { return !(*this == rhs); }

void Vec2::operator+=(const Vec2 &rhs) {
  x += rhs.x;
  y += rhs.y;
}
void Vec2::operator-=(const Vec2 &rhs) {
  x -= rhs.x;
  y -= rhs.y;
}

void Vec2::operator*=(const float val) {
  x *= val;
  y *= val;
}

void Vec2::operator/=(const float val) {
  x /= val;
  y /= val;
}

float Vec2::dist(const Vec2 &rhs) const {
  return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
}

float Vec2::length() const { return sqrt(x * x + y * y); }

void Vec2::normalize() {
  float len = length();
  if (len > 0) {
    x /= len;
    y /= len;
  }
}
