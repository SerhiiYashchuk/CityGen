#ifndef CITYGEN_I_SCALAR_FIELD_H
#define CITYGEN_I_SCALAR_FIELD_H

#include "GenericTypes.h"

namespace CityGen
{
class IScalarField
{
public:
  virtual ~IScalarField() = default;

  virtual float sample(Vector2 pos) const = 0;
};
}

#endif
