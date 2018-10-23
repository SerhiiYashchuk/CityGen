#ifndef CITYGEN_SCALED_SCALAR_FIELD_H
#define CITYGEN_SCALED_SCALAR_FIELD_H

#include "IScalarField.h"
#include <type_traits>

namespace CityGen
{
template<class T>
class ScaledScalarField : public IScalarField
{
public:
  ScaledScalarField(T scalar, float scale) : _scalar(scalar), _scale(scale)
  {
    static_assert(std::is_base_of<IScalarField, T>(), "T should conform to IScalarField interface.");
  }

  float sample(Vector2 pos) const override
  {
    return _scalar.sample(pos) * _scale;
  }

private:
  const T _scalar;
  const float _scale = 0;
};
}

#endif
