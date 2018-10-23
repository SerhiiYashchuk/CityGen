#ifndef CITYGEN_TENSOR_H
#define CITYGEN_TENSOR_H

#include "GenericTypes.h"

#include <limits>
#include <utility>

namespace CityGen
{
// A tensor is a 2x2 symmetric and traceless matrix of the form
// R * | cos(2theta)  sin(2theta) |  = | a b |
//     | sin(2theta) -cos(2theta) |    | _ _ |
// where R >= 0 and theta is [0, 2pi)

class Tensor
{
public:
  Tensor(float a, float b) : _a(a), _b(b) {}

  static Tensor fromRTheta(float r, float theta)
  {
    return { r * std::cos(2 * theta), r * std::sin(2 * theta) };
  }

  static Tensor fromPos(Vector2 pos)
  {
    const float xy2 = -2 * pos.x * pos.y;
    const float diffSqr = pos.y * pos.y - pos.x * pos.x;
    Vector2 res = { diffSqr, xy2 };
    
    res.normalize();

    return res;
  }

  Tensor operator+(const Tensor &rhs) const
  {
    return Tensor(_a + rhs._a, _b + rhs._b);
  }

  Tensor operator*(const Tensor &rhs) const
  {
    return Tensor(_a * rhs._a, _b * rhs._b);
  }

  void normalize()
  {
    const float l = std::sqrt(_a * _a + _b * _b);

    if (l < std::numeric_limits<float>::epsilon())
    {
      _a = 0;
      _b = 0;
    }
    else
    {
      _a /= l;
      _b /= l;
    }
  }

  std::pair<float, float> eigenValues() const
  {
    const float res = std::sqrt(_a * _a + _b * _b);

    return { res, -res };
  }

  // Returns major and minor eigen vectors
  std::pair<Vector2, Vector2> eigenVectors() const
  {
    Vector2 major;
    Vector2 minor;

    if (std::abs(_b) == 0)
    {
      if (std::abs(_a) != 0)
      {
        major = { 1, 0 };
        minor = { 0, 1 };
      }
    }
    else
    {
      const auto values = eigenValues();

      major = { _b, values.first - _a };
      minor = { _b, values.second - _a };
    }

    return { major, minor };
  }

private:
  float _a = 0;
  float _b = 0;
};
}

#endif
