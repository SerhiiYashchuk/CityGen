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
  Tensor(float a, float b);

  static Tensor fromRTheta(float r, float theta);
  static Tensor fromPos(Vector pos);

  Tensor operator+(const Tensor &rhs) const
  {
    return Tensor(_a + rhs._a, _b + rhs._b);
  }

  Tensor operator*(const Tensor &rhs) const
  {
    return Tensor(_a * rhs._a, _b * rhs._b);
  }

  void normalize();

  // Returns major and minor eigen values
  std::pair<float, float> eigenValues() const;
  // Returns major and minor eigen vectors
  std::pair<Vector, Vector> eigenVectors() const;

private:
  float _a = 0;
  float _b = 0;
};
}

#endif
