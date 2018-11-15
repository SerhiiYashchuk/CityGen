#ifndef CITYGEN_GENERIC_TYPES_H
#define CITYGEN_GENERIC_TYPES_H

#include <cmath>
#include <type_traits>
#include <limits>

namespace CityGen
{
namespace Utils
{
constexpr float floatEpsilon = 0.0000001f;

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almostEqual(T x, T y, float epsilon = floatEpsilon)
{
  return std::abs(x - y) < epsilon;
}
}

struct Vector
{
  float x = 0;
  float y = 0;

  bool operator==(const Vector &rhs) const
  {
    return Utils::almostEqual(x, rhs.x) && Utils::almostEqual(y, rhs.y);
  }

  bool operator!=(const Vector &rhs) const
  {
    return !(*this == rhs);
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

    if (!Utils::almostEqual(l, 0.f))
    {
      x /= l;
      y /= l;
    }
  }
};

namespace Utils
{
float dotProduct(Vector v1, Vector v2);
}
}

#endif