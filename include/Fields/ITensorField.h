#ifndef CITYGEN_I_TENSOR_FIELD_H
#define CITYGEN_I_TENSOR_FIELD_H

#include "GenericTypes.h"
#include "Fields/Tensor.h"

namespace CityGen
{
class ITensorField
{
public:
  virtual ~ITensorField() = default;

  virtual Tensor sample(Vector2 pos) = 0;
};
}

#endif
