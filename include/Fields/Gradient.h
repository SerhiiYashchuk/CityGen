#ifndef CITYGEN_GRADIENT_H
#define CITYGEN_GRADIENT_H

#include "Fields/IVectorField.h"
#include "Fields/IScalarField.h"
#include <type_traits>

namespace CityGen
{
template<class T>
class Gradient : public IVectorField
{
public:
  Gradient(T scalar) : _scalar(scalar)
  {
    static_assert(std::is_base_of<IScalarField, T>(), "T should conform to IScalarField interface.");
  }

  Vector sample(Vector pos) override
  {
    const float v = _scalar.sample(pos);
    const float x = _scalar.sample({ pos.x + 1, pos.y });
    const float y = _scalar.sample({ pos.x, pos.y + 1 });

    return { v - x, v - y };
  }

private:
  const T _scalar;
};
}

#endif
