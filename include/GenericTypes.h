#ifndef CITYGEN_GENERIC_TYPES_H
#define CITYGEN_GENERIC_TYPES_H

#include <cmath>

namespace CityGen
{
struct Vector
{
  float x = 0;
  float y = 0;

  bool operator==(const Vector &rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  Vector operator+(const Vector &rhs) const
  {
    return { x + rhs.x, y + rhs.y };
  }

  Vector operator-(const Vector &rhs) const
  {
    return { x - rhs.x, y - rhs.y };
  }

  Vector operator*(const Vector &rhs) const
  {
    return { x * rhs.x, y * rhs.y };
  }

  Vector operator/(const Vector &rhs) const
  {
    return { x / rhs.x, y / rhs.y };
  }

  Vector &operator+=(const Vector &rhs)
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  Vector &operator-=(const Vector &rhs)
  {
    x -= rhs.x;
    y -= rhs.y;

    return *this;
  }

  Vector &operator*=(const Vector &rhs)
  {
    x *= rhs.x;
    y *= rhs.y;

    return *this;
  }

  Vector &operator/=(const Vector &rhs)
  {
    x /= rhs.x;
    y /= rhs.y;

    return *this;
  }

  Vector operator*(float rhs) const
  {
    return { x * rhs, y * rhs };
  }

  Vector operator/(float rhs) const
  {
    return { x / rhs, y / rhs };
  }

  Vector &operator*=(float rhs)
  {
    x *= rhs;
    y *= rhs;

    return *this;
  }

  Vector &operator/=(float rhs)
  {
    x /= rhs;
    y /= rhs;

    return *this;
  }

  float length() const
  {
    return std::sqrt(x * x + y * y);
  }

  void normalize()
  {
    const float l = length();

    if (l != 0)
    {
      x /= l;
      y /= l;
    }
  }
};

namespace Utils
{
float dotProduct(Vector v1, Vector v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
}
}

#endif