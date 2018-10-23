#ifndef CITYGEN_I_EIGEN_FIELD_H
#define CITYGEN_I_EIGEN_FIELD_H

#include "IVector2Field.h"

namespace CityGen
{
class IEigenField
{
public:
  virtual ~IEigenField() = default;

  const IVector2Field &majorEigenVectors() const = 0;
  const IVector2Field &minorEigenVectors() const = 0;
};
}

#endif
