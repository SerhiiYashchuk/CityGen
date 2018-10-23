#ifndef CITYGEN_RADIAL_TENSOR_FIELD_H
#define CITYGEN_RADIAL_TENSOR_FIELD_H

#include "Fields/ITensorField.h"

namespace CityGen
{
class RadialTensorField : public ITensorField
{
public:
  RadialTensorField(Vector center) : _center(center) {}

  Tensor sample(Vector pos) override
  {
    return Tensor::fromPos(pos - _center);
  }

private:
  const Vector _center;
};
}

#endif
