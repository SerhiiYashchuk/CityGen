#include "Fields/Tensor.h"

namespace CityGen
{
Tensor Tensor::fromRTheta(float r, float theta)
{
  return { r * std::cos(2 * theta), r * std::sin(2 * theta) };
}

Tensor Tensor::fromPos(Vector pos)
{
  const float xy2 = -2 * pos.x * pos.y;
  const float diffSqr = pos.y * pos.y - pos.x * pos.x;
  Tensor res = { diffSqr, xy2 };

  res.normalize();

  return res;
}

Tensor::Tensor(float a, float b)
  : _a(a), _b(b)
{
}

void Tensor::normalize()
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

std::pair<float, float> Tensor::eigenValues() const
{
  const float res = std::sqrt(_a * _a + _b * _b);

  return { res, -res };
}

std::pair<Vector, Vector> Tensor::eigenVectors() const
{
  Vector major;
  Vector minor;

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
}