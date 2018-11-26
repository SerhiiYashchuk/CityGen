#ifndef CITYGEN_GRIDLINE_TENSOR_FIELD_H
#define CITYGEN_GRIDLINE_TENSOR_FIELD_H

#include "Fields/ITensorField.h"

namespace CityGen
{
class GridlineTensorField : public ITensorField
{
public:
  GridlineTensorField(float angle, float length) : _basis(Tensor::fromRTheta(angle, length)) {}

  Tensor sample(Vector pos) override
  {
    return _basis;
  }

private:
  const Tensor _basis;
};
}

#endif
