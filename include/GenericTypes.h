#ifndef CITYGEN_GENERIC_TYPES_H
#define CITYGEN_GENERIC_TYPES_H

#include <cmath>

namespace CityGen
{
struct Vector2
{
  float x = 0;
  float y = 0;

  Vector2 operator+(Vector2 rhs) const
  {
    return { x + rhs.x, y + rhs.y };
  }

  Vector2 operator-(Vector2 rhs) const
  {
    return { x - rhs.x, y - rhs.y };
  }

  Vector2 operator*(Vector2 rhs) const
  {
    return { x * rhs.x, y * rhs.y };
  }

  Vector2 operator/(Vector2 rhs) const
  {
    return { x / rhs.x, y / rhs.y };
  }

  Vector2 operator*(float rhs) const
  {
    return { x * rhs, y * rhs };
  }

  Vector2 operator/(float rhs) const
  {
    return { x / rhs, y / rhs };
  }

  float length() const
  {
    return std::sqrt(x * x + y * y);
  }
};

namespace Utils
{
float dotProduct(Vector2 v1, Vector2 v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
}
}

#endif